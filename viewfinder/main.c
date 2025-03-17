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

// DAVE
#include "aipl_dave2d.h"
#include "dave_cfg.h"
#include "dave_d0lib.h"

// Alif Image Processing Library
#include "aipl_color_correction.h"
#include "aipl_crop.h"
#include "aipl_image.h"
#include "aipl_lut_transform.h"
#include "aipl_resize.h"
#include "aipl_rotate.h"
#include "board.h"
#include "camera.h"
#include "disp.h"
#include "image.h"

#include "power_management.h"
#include "se_services_port.h"
#include "alif_logo.h"

void clock_init(void);   // Enables needed SoC clocks
extern void clk_init();  // time.h clock functionality (from retarget.c)

// DAVE heap
#define D1_HEAP_SIZE 0x00230000
static uint8_t d0_heap[D1_HEAP_SIZE] __attribute__((section(".bss.video_mem_heap")));

// Check if UART trace is disabled
#if !defined(DISABLE_UART_TRACE)
#include <stdio.h>

#include "uart_tracelib.h"

static void uart_callback(uint32_t event) {}
#else
#define printf(fmt, ...) (0)
#endif

// Print measurements
#define PRINT_INTERVAL_SEC    (1)
#define PRINT_INTERVAL_CLOCKS (PRINT_INTERVAL_SEC * CLOCKS_PER_SEC)
extern uint32_t SystemCoreClock;

int main(void) {
    BOARD_Pinmux_Init();

    /* Initialize the SE services */
    se_services_port_init();

    /* Enable MIPI power */
    bool pm_ok = init_power_management();
    if (!pm_ok) {
        printf("\r\nError: power management init failed.\r\n");
        __BKPT(0);
    }

    clock_init();

#if !defined(DISABLE_UART_TRACE)
    tracelib_init(NULL, uart_callback);
#endif

#if (D1_MEM_ALLOC == D1_MALLOC_D0LIB)
    /*-------------------------
     * Initialize D/AVE D0 heap
     * -----------------------*/
    if (!d0_initheapmanager(d0_heap, sizeof(d0_heap), d0_mm_fixed_range, NULL, 0, 0, 0, d0_ma_unified)) {
        printf("\r\nError: Heap manager initialization failed\n");
    }
#endif

    // Initialize D/AVE2D
    if (aipl_dave2d_init() != D2_OK) {
        printf("\r\nError: D/AVE2D initialization falied\n");
        __BKPT(0);
    }

    clk_init();  // for time.h clock()

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

    // Set Logo CLUT
    aipl_dave2d_set_clut(get_alif_lut(), AIPL_COLOR_ARGB8888);

    // Enable PMU cycle counter for measurements
    DCB->DEMCR |= DCB_DEMCR_TRCENA_Msk;
    ARM_PMU_Enable();
    ARM_PMU_CNTR_Enable(PMU_CNTENSET_CCNTR_ENABLE_Msk);

    // Capture frames in loop
    printf("\r\n Let's Start Capturing Camera Frame...\r\n");
    clock_t print_ts = clock();
    while (ret == ARM_DRIVER_OK) {
        // Blink green LED
        BOARD_LED2_Control(BOARD_LED_STATE_TOGGLE);
        // Reset cycle counter
        ARM_PMU_CYCCNT_Reset();

        uint32_t capture_time = ARM_PMU_Get_CCNTR();
        ret = camera_capture();
        if (ret == ARM_DRIVER_OK) {
            capture_time = ARM_PMU_Get_CCNTR() - capture_time;

            // Do Bayer conversion
            uint32_t bayer_time = ARM_PMU_Get_CCNTR();
            // The buffer for cam_image is static, so it should not be destroyed
            aipl_image_t cam_image = camera_post_capture_process();
            bayer_time = ARM_PMU_Get_CCNTR() - bayer_time;

            // Do color correction for the ARX3A0 camera
            aipl_error_t aipl_ret = AIPL_ERR_OK;
#if CAM_COLOR_CORRECTION
            // See camera.c for coefficients
            uint32_t cc_time = ARM_PMU_Get_CCNTR();
            aipl_ret = aipl_color_correction_rgb_img(&cam_image, &cam_image, camera_get_color_correction_matrix());
            if (aipl_ret != AIPL_ERR_OK) {
                printf("Error: color correction aipl_ret = %s\r\n", aipl_error_str(aipl_ret));
                __BKPT(0);
            }

            aipl_ret = aipl_lut_transform_rgb_img(&cam_image, &cam_image, camera_get_gamma_lut());
            if (aipl_ret != AIPL_ERR_OK) {
                printf("Error: gamma correction aipl_ret = %s\r\n", aipl_error_str(aipl_ret));
                __BKPT(0);
            }
            cc_time = ARM_PMU_Get_CCNTR() - cc_time;
#endif

            // Measure the image processing time (crop and resize)
            uint32_t ip_time = ARM_PMU_Get_CCNTR();

            // Crop image to a square using the smaller of the camera dimensions
            const uint32_t crop_dim = cam_image.width > cam_image.height ? cam_image.height : cam_image.width;
            const uint32_t crop_border = (cam_image.width - crop_dim) / 2;
            const uint32_t crop_header = (cam_image.height - crop_dim) / 2;

            aipl_image_t crop_image;
            aipl_ret = aipl_image_create(&crop_image, crop_dim, crop_dim, crop_dim, cam_image.format);
            if (aipl_ret != AIPL_ERR_OK) {
                printf("Error: Failed allocating crop image\r\n");
                __BKPT(0);
            }

            aipl_ret = aipl_crop_img(&cam_image, &crop_image, crop_border, crop_header, cam_image.width - crop_border,
                                     cam_image.height - crop_header);
            if (aipl_ret != AIPL_ERR_OK) {
                printf("Error: crop aipl_ret = %s\r\n", aipl_error_str(aipl_ret));
                __BKPT(0);
            }

            // Resize the cropped image so that it fits to full display width
            aipl_image_t res_image;
            aipl_ret = aipl_image_create(&res_image, MY_DISP_HOR_RES, MY_DISP_HOR_RES, MY_DISP_HOR_RES, crop_image.format);
            if (aipl_ret != AIPL_ERR_OK) {
                printf("Error: Failed allocating resize temp image\r\n");
                __BKPT(0);
            }

            aipl_ret = aipl_resize_img(&crop_image, &res_image,
                                       true);  // interpolate

            aipl_image_destroy(&crop_image);

            if (aipl_ret != AIPL_ERR_OK) {
                printf("Error: resize aipl_ret = %s\r\n", aipl_error_str(aipl_ret));
                __BKPT(0);
            }

            // Draw the resized image to display
            aipl_image_t *draw_image = &res_image;

            // Rotate image 180 on AppKit (Camera connected to the connector on the other side than the display)
#ifdef BOARD_IS_ALIF_APPKIT_B1_VARIANT
            aipl_image_t rot_image;
            aipl_ret = aipl_image_create(&rot_image, res_image.width, res_image.width, res_image.height, res_image.format);
            if (aipl_ret != AIPL_ERR_OK) {
                printf("Error: Failed allocating rotate temp image\r\n");
                __BKPT(0);
            }

            aipl_ret = aipl_rotate_img(&res_image, &rot_image, AIPL_ROTATE_180);
            if (aipl_ret != AIPL_ERR_OK) {
                printf("Error: rotate aipl_ret = %s\r\n", aipl_error_str(aipl_ret));
                __BKPT(0);
            }
            aipl_image_destroy(&res_image);
            draw_image = &rot_image;
#endif

            ip_time = ARM_PMU_Get_CCNTR() - ip_time;

            uint32_t render_time = ARM_PMU_Get_CCNTR();
            aipl_dave2d_prepare();
            aipl_image_draw(0, 0, draw_image);
            aipl_image_draw_clut(100, 600, get_alif_logo());
            aipl_dave2d_render();
            aipl_image_destroy(draw_image);
            render_time = ARM_PMU_Get_CCNTR() - render_time;

            if (clock() - print_ts >= PRINT_INTERVAL_CLOCKS) {
                print_ts = clock();
                printf("Frame capture took %.3fms\r\n", capture_time * 1000.0f / SystemCoreClock);

#if !CAM_USE_RGB565
                float bayer_time_s = (float)bayer_time / SystemCoreClock;
                printf("Bayer conversion %.3fms (throughput=%.2fMpix/s)\r\n", bayer_time_s * 1000.0f,
                                                                            CAM_MPIX / bayer_time_s);
#endif

#if CAM_COLOR_CORRECTION
                float cc_time_s = (float)cc_time / SystemCoreClock;
                printf("Color correction %.3fms (throughput=%.2fMpix/s)\r\n", cc_time_s * 1000.0f,
                                                                              CAM_MPIX / cc_time_s);
#endif

                float ip_time_s = (float)ip_time / SystemCoreClock;
                printf("Image processing %.3fms (throughput=%.2fMpix/s)\r\n", ip_time_s * 1000.0f,
                                                                              CAM_MPIX / ip_time_s);

                float render_time_s = (float)render_time / SystemCoreClock;
                printf("Rendering to display %.3fms (throughput=%.2fMpix/s)\r\n", render_time_s * 1000.0f,
                                                                                  CAM_MPIX / render_time_s);
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

void clock_init(void) {
    uint32_t service_error_code = 0;
    /* Enable Clocks */
    uint32_t error_code = SERVICES_clocks_enable_clock(se_services_s_handle, CLKEN_CLK_100M, true, &service_error_code);
    if (error_code || service_error_code) {
        printf("SE: 100MHz clock enable error_code=%u se_error_code=%u\n", error_code, service_error_code);
        return;
    }

    error_code = SERVICES_clocks_enable_clock(se_services_s_handle, CLKEN_HFOSC, true, &service_error_code);
    if (error_code || service_error_code) {
        printf("SE: HFOSC enable error_code=%u se_error_code=%u\n", error_code, service_error_code);
        return;
    }
}
