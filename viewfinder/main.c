/* Copyright (C) 2023-2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#include <time.h>

#include "RTE_Components.h"
#include CMSIS_device_header

#include "Driver_GPIO.h"
#include "Driver_CPI.h"    // Camera
#include "Driver_CDC200.h" // Display
#include "board.h"
#include "bayer.h"
#include "image_processing.h"
#include "power.h"

#include "se_services_port.h"

// From color_correction.c
void white_balance(int ml_width, int ml_height, const uint8_t *sp, uint8_t *dp);
extern void clk_init(); // retarget.c

// Check if UART trace is disabled
#if !defined(DISABLE_UART_TRACE)
#include <stdio.h>
#include "uart_tracelib.h"

static void uart_callback(uint32_t event)
{
}
#else
#define printf(fmt, ...) (0)
#endif

// Print measurements
#define PRINT_INTERVAL_SEC (1)
#define PRINT_INTERVAL_CLOCKS (PRINT_INTERVAL_SEC * CLOCKS_PER_SEC)
extern uint32_t SystemCoreClock;

#define BAYER_FORMAT DC1394_COLOR_FILTER_GRBG

/* Camera Controller Resolution. */
#if RTE_Drivers_CAMERA_SENSOR_MT9M114
#define CAM_FRAME_WIDTH        (RTE_MT9M114_CAMERA_SENSOR_MIPI_FRAME_WIDTH)
#define CAM_FRAME_HEIGHT       (RTE_MT9M114_CAMERA_SENSOR_MIPI_FRAME_HEIGHT)
#define CAM_COLOR_CORRECTION   (0)
#define RGB_BUFFER_SECTION     ".bss.camera_frame_bayer_to_rgb_buf_at_sram0"
#elif RTE_Drivers_CAMERA_SENSOR_ARX3A0
#define CAM_FRAME_WIDTH        (RTE_ARX3A0_CAMERA_SENSOR_FRAME_WIDTH)
#define CAM_FRAME_HEIGHT       (RTE_ARX3A0_CAMERA_SENSOR_FRAME_HEIGHT)
#define CAM_COLOR_CORRECTION   (1)
#define RGB_BUFFER_SECTION     ".bss.camera_frame_bayer_to_rgb_buf"
#endif

#define BYTES_PER_PIXEL        (3)
#define CAM_FRAME_SIZE (CAM_FRAME_WIDTH * CAM_FRAME_HEIGHT)
#define CAM_MPIX (CAM_FRAME_SIZE / 1000000.0f)

static uint8_t camera_buffer[CAM_FRAME_SIZE] __attribute__((aligned(32), section(".bss.camera_frame_buf")));

static uint8_t image_buffer[CAM_FRAME_SIZE * BYTES_PER_PIXEL] __attribute__((aligned(32), section(RGB_BUFFER_SECTION)));

/* Camera  Driver instance 0 */
extern ARM_DRIVER_CPI Driver_CPI;
static ARM_DRIVER_CPI *CAMERAdrv = &Driver_CPI;

/* LCD */
#define DISPLAY_FRAME_WIDTH       (RTE_PANEL_HACTIVE_TIME)
#define DISPLAY_FRAME_HEIGHT      (RTE_PANEL_VACTIVE_LINE)
static uint8_t lcd_image[DISPLAY_FRAME_HEIGHT][DISPLAY_FRAME_WIDTH][BYTES_PER_PIXEL] __attribute__((section(".bss.lcd_frame_buf"))) = {0};
extern ARM_DRIVER_CDC200 Driver_CDC200;
static ARM_DRIVER_CDC200 *CDCdrv = &Driver_CDC200;

typedef enum {
    CAM_CB_EVENT_NONE            = 0,
    CAM_CB_EVENT_ERROR           = (1 << 0),
    DISP_CB_EVENT_ERROR          = (1 << 1),
    CAM_CB_EVENT_CAPTURE_STOPPED = (1 << 2)
} CB_EVENTS;

static volatile CB_EVENTS g_cb_events = CAM_CB_EVENT_NONE;

static void camera_callback(uint32_t event)
{
    switch (event)
    {
    case ARM_CPI_EVENT_CAMERA_CAPTURE_STOPPED:
        g_cb_events |= CAM_CB_EVENT_CAPTURE_STOPPED;
        break;
    case ARM_CPI_EVENT_CAMERA_FRAME_HSYNC_DETECTED:
        break;
    case ARM_CPI_EVENT_CAMERA_FRAME_VSYNC_DETECTED:
        break;

    case ARM_CPI_EVENT_ERR_CAMERA_INPUT_FIFO_OVERRUN:
    case ARM_CPI_EVENT_ERR_CAMERA_OUTPUT_FIFO_OVERRUN:
    case ARM_CPI_EVENT_ERR_HARDWARE:
    case ARM_CPI_EVENT_MIPI_CSI2_ERROR:
    default:
        g_cb_events |= CAM_CB_EVENT_ERROR;
        break;
    }
}


static void display_callback(uint32_t event)
{
    if(event & ARM_CDC_DSI_ERROR_EVENT)
    {
        g_cb_events |= DISP_CB_EVENT_ERROR;
    }
}

int camera_init()
{
    int ret = CAMERAdrv->Initialize(camera_callback);
    if(ret != ARM_DRIVER_OK)
    {
        printf("\r\n Error: CAMERA Initialize failed.\r\n");
        return ret;
    }

    /* Power up Camera peripheral */
    ret = CAMERAdrv->PowerControl(ARM_POWER_FULL);
    if(ret != ARM_DRIVER_OK)
    {
        printf("\r\n Error: CAMERA Power Up failed.\r\n");
        return ret;
    }

    /* Control configuration for camera controller */
    ret = CAMERAdrv->Control(CPI_CONFIGURE, 0);
    if(ret != ARM_DRIVER_OK)
    {
        printf("\r\n Error: CPI Configuration failed.\r\n");
        return ret;
    }

    /* Control configuration for camera sensor */
    ret = CAMERAdrv->Control(CPI_CAMERA_SENSOR_CONFIGURE, 0);
    if(ret != ARM_DRIVER_OK)
    {
        printf("\r\n Error: CAMERA SENSOR Configuration failed.\r\n");
        return ret;
    }

    /*Control configuration for camera events */
    ret = CAMERAdrv->Control(CPI_EVENTS_CONFIGURE,
                             ARM_CPI_EVENT_CAMERA_CAPTURE_STOPPED |
                             ARM_CPI_EVENT_ERR_CAMERA_INPUT_FIFO_OVERRUN |
                             ARM_CPI_EVENT_ERR_CAMERA_OUTPUT_FIFO_OVERRUN |
                             ARM_CPI_EVENT_ERR_HARDWARE);
    if(ret != ARM_DRIVER_OK)
    {
        printf("\r\n Error: CAMERA SENSOR Event Configuration failed.\r\n");
        return ret;
    }

    return ret;
}

int display_init()
{
    /* Initialize CDC driver */
    int ret = CDCdrv->Initialize(display_callback);
    if(ret != ARM_DRIVER_OK){
        printf("\r\n Error: CDC init failed\n");
        return ret;
    }

    /* Power control CDC */
    ret = CDCdrv->PowerControl(ARM_POWER_FULL);
    if(ret != ARM_DRIVER_OK){
        printf("\r\n Error: CDC Power up failed\n");
        return ret;
    }

    /* configure CDC controller */
    ret = CDCdrv->Control(CDC200_CONFIGURE_DISPLAY, (uint32_t)lcd_image);
    if(ret != ARM_DRIVER_OK){
        printf("\r\n Error: CDC controller configuration failed\n");
        return ret;
    }

    printf(">>> Allocated memory buffer Address is 0x%X <<<\n",(uint32_t)lcd_image);

    /* Start CDC */
    ret = CDCdrv->Start();
    if(ret != ARM_DRIVER_OK){
        printf("\r\n Error: CDC Start failed\n");
        return ret;
    }

    return ret;
}

void clock_init()
{
    uint32_t service_error_code = 0;
    /* Enable Clocks */
    uint32_t error_code = SERVICES_clocks_enable_clock(se_services_s_handle, CLKEN_CLK_100M, true, &service_error_code);
    if(error_code || service_error_code){
        printf("SE: 100MHz clock enable error_code=%u se_error_code=%u\n", error_code, service_error_code);
        return;
    }

    error_code = SERVICES_clocks_enable_clock(se_services_s_handle, CLKEN_HFOSC, true, &service_error_code);
    if(error_code || service_error_code){
        printf("SE: HFOSC enable error_code=%u se_error_code=%u\n", error_code, service_error_code);
        return;
    }
}

void main (void)
{
    BOARD_Pinmux_Init();

    /* Initialize the SE services */
    se_services_port_init();

    /* Enable MIPI power. TODO: To be changed to aiPM call */
    enable_mipi_dphy_power();
    disable_mipi_dphy_isolation();

    clock_init();

#if !defined(DISABLE_UART_TRACE)
    tracelib_init(NULL, uart_callback);
#endif
    clk_init(); // for time.h clock()

    // Init camera
    int ret = camera_init();
    if (ret != ARM_DRIVER_OK) {
        __BKPT(0);
    } else {
        // Camera init OK --> init display
        ret = display_init();
        if (ret != ARM_DRIVER_OK) {
            __BKPT(0);
        }
    }

    // Enable PMU cycle counter for measurements
    DCB->DEMCR |= DCB_DEMCR_TRCENA_Msk;
    ARM_PMU_Enable();
    ARM_PMU_CNTR_Enable(PMU_CNTENSET_CCNTR_ENABLE_Msk);

    // Capture frames in loop
    printf("\r\n Let's Start Capturing Camera Frame...\r\n");
    clock_t print_ts = clock();
    while (ret == ARM_DRIVER_OK &&
           !(g_cb_events & (CAM_CB_EVENT_ERROR | DISP_CB_EVENT_ERROR))) {

        // Blink green LED
        BOARD_LED2_Control(BOARD_LED_STATE_TOGGLE);
        // Reset cycle counter
        ARM_PMU_CYCCNT_Reset();

        g_cb_events = CAM_CB_EVENT_NONE;
        uint32_t capture_time = ARM_PMU_Get_CCNTR();
        ret = CAMERAdrv->CaptureFrame(camera_buffer);
        if(ret == ARM_DRIVER_OK) {
            // Wait for capture
            while (!(g_cb_events & CAM_CB_EVENT_CAPTURE_STOPPED)) {
                __WFI();
            }
            // Invalidate cache before reading the camera_buffer
            SCB_CleanInvalidateDCache();
            capture_time = ARM_PMU_Get_CCNTR() - capture_time;


            uint32_t bayer_time = ARM_PMU_Get_CCNTR();
            dc1394_bayer_Simple(camera_buffer, image_buffer, CAM_FRAME_WIDTH, CAM_FRAME_HEIGHT, BAYER_FORMAT);
            bayer_time = ARM_PMU_Get_CCNTR() - bayer_time;

// Do color correction for the ARX3A0 camera
// White balance function does also RGB --> BGR conversion so when skipping color correction
// the RGB --> BGR is done in the resize phase
#if CAM_COLOR_CORRECTION
            uint32_t wb_time = ARM_PMU_Get_CCNTR();
            white_balance(CAM_FRAME_WIDTH, CAM_FRAME_HEIGHT, image_buffer, image_buffer);
            wb_time = ARM_PMU_Get_CCNTR() - wb_time;
#endif

            const int rescaleWidth = DISPLAY_FRAME_WIDTH;
            const int rescaleHeight = (int)(CAM_FRAME_HEIGHT * (float)rescaleWidth / CAM_FRAME_WIDTH);

            uint32_t resize_time = ARM_PMU_Get_CCNTR();
            resize_image_A(image_buffer,
                           CAM_FRAME_WIDTH,
                           CAM_FRAME_HEIGHT,
                           (uint8_t*)lcd_image,
                           rescaleWidth,
                           rescaleHeight,
                           BYTES_PER_PIXEL,
                           CAM_COLOR_CORRECTION == 0); // Swap to BGR in resize phase when using MT9M114

            resize_time = ARM_PMU_Get_CCNTR() - resize_time;

            if (clock() - print_ts >= PRINT_INTERVAL_CLOCKS) {
                print_ts = clock();
                printf("Frame capture took %.3fms\n", capture_time * 1000.0f / SystemCoreClock);
                float bayer_time_s = (float)bayer_time / SystemCoreClock;
                printf("Bayer conversion %.3fms (throughput=%.2fMpix/s)\n", bayer_time_s * 1000.0f,
                                                                            CAM_MPIX / bayer_time_s);
#if CAM_COLOR_CORRECTION
                float wb_time_s = (float)wb_time / SystemCoreClock;
                printf("White balance %.3fms (throughput=%.2fMpix/s)\n", wb_time_s * 1000.0f,
                                                                         CAM_MPIX / wb_time_s);
#endif
                float resize_time_s = (float)resize_time / SystemCoreClock;
                printf("Resize to display %.3fms (throughput=%.2fMpix/s)\n", resize_time_s * 1000.0f,
                                                                             CAM_MPIX / resize_time_s);
            }
        } else {
            printf("\r\n Error: CAMERA Capture Frame failed.\r\n");
        }
    } 

    // Set RED LED in error case
    BOARD_LED1_Control(BOARD_LED_STATE_HIGH);

    while (1) {
        __WFI();
    }
}
