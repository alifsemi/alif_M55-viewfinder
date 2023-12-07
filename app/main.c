/* Copyright (C) 2023 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#include "RTE_Components.h"
#include CMSIS_device_header

#include "Driver_GPIO.h"
#include "Driver_CPI.h"    // Camera
#include "Driver_CDC200.h" // Display
#include "board.h"
#include "bayer.h"
#include "power.h"

// From color_correction.c
void white_balance(int ml_width, int ml_height, const uint8_t *sp, uint8_t *dp);

// Disable printf
#define printf(fmt, ...) (0)

#define BAYER_FORMAT DC1394_COLOR_FILTER_GRBG

/* Camera Controller Resolution. */
#define CAM_RESOLUTION                   CAM_RESOLUTION_560x560
#if (CAM_RESOLUTION == CAM_RESOLUTION_560x560)
#define CAM_FRAME_WIDTH        (560)
#define CAM_FRAME_HEIGHT       (560)
#elif (CAM_RESOLUTION == CAM_RESOLUTION_480x480)
#define CAM_FRAME_WIDTH        (480)
#define CAM_FRAME_HEIGHT       (480)
#endif
#define BYTES_PER_PIXEL        (3)

#define CAM_FRAME_SIZE (CAM_FRAME_WIDTH * CAM_FRAME_HEIGHT)
static uint8_t camera_buffer[CAM_FRAME_SIZE] __attribute__((aligned(32), section(".bss.camera_frame_buf")));
static uint8_t image_buffer[CAM_FRAME_SIZE * BYTES_PER_PIXEL] __attribute__((aligned(32), section(".bss.camera_frame_bayer_to_rgb_buf")));

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
    enable_cgu_clk38p4m();
    enable_cgu_clk160m();
    enable_cgu_clk100m();
    enable_cgu_clk20m();
}

void main (void)
{
    BOARD_Pinmux_Init();

    /* Enable MIPI power. TODO: To be changed to aiPM call */
    enable_mipi_dphy_power();
    disable_mipi_dphy_isolation();

    clock_init();

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

    // Capture frames in loop
    printf("\r\n Let's Start Capturing Camera Frame...\r\n");
    while (ret == ARM_DRIVER_OK &&
           !(g_cb_events & (CAM_CB_EVENT_ERROR | DISP_CB_EVENT_ERROR))) {

        // Blink green LED
        BOARD_LED2_Control(BOARD_LED_STATE_TOGGLE);

        g_cb_events = CAM_CB_EVENT_NONE;
        ret = CAMERAdrv->CaptureFrame(camera_buffer);
        if(ret == ARM_DRIVER_OK) {
            // Wait for capture
            while (!(g_cb_events & CAM_CB_EVENT_CAPTURE_STOPPED)) {
            }

            dc1394_bayer_Simple(camera_buffer, image_buffer, CAM_FRAME_WIDTH, CAM_FRAME_HEIGHT, BAYER_FORMAT);
            white_balance(CAM_FRAME_WIDTH, CAM_FRAME_HEIGHT, image_buffer, image_buffer);

            const uint8_t (*src)[CAM_FRAME_HEIGHT][BYTES_PER_PIXEL] = (const uint8_t (*)[CAM_FRAME_HEIGHT][BYTES_PER_PIXEL]) image_buffer;            
            for (int i = 0; i < CAM_FRAME_WIDTH && i < DISPLAY_FRAME_WIDTH; i++) {
                for (int j = 0; j < CAM_FRAME_HEIGHT && j < DISPLAY_FRAME_HEIGHT; j++)
                {
                    lcd_image[i][j][0] = src[i][j][2]; // blue
                    lcd_image[i][j][1] = src[i][j][1]; // green
                    lcd_image[i][j][2] = src[i][j][0]; // red
                }
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

void SysTick_Handler (void)
{
}

// Stubs to suppress missing stdio definitions for nosys
#define TRAP_RET_ZERO  {__BKPT(0); return 0;}
int _close(int val) TRAP_RET_ZERO
int _lseek(int val0, int val1, int val2) TRAP_RET_ZERO
int _read(int val0, char * val1, int val2) TRAP_RET_ZERO
int _write(int val0, char * val1, int val2) TRAP_RET_ZERO