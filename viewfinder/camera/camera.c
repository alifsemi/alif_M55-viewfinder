/* Copyright (C) 2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#include "camera.h"

#include <math.h>
#include <stdio.h>

#include "Driver_CPI.h"
#include "bayer.h"
#include "aipl_color_conversion.h"

// Buffer for camera frame (RGB565 or Bayer depending on camera and configuration)
static uint8_t camera_buffer[CAM_FRAME_SIZE_BYTES] __attribute__((aligned(32), section(".bss.camera_frame_buf")));

// Buffer for bayer conversion to RGB is not needed when camera outputs RGB565
#if CAM_USE_RGB565
aipl_image_t camera_image = {camera_buffer,       // data
                             CAM_FRAME_WIDTH,     // pitch
                             CAM_FRAME_WIDTH,     // width
                             CAM_FRAME_HEIGHT,    // height
                             AIPL_COLOR_RGB565};  // format
#else
static uint8_t rgb_buffer[CAM_FRAME_SIZE * 3] __attribute__((aligned(32), section(RGB_BUFFER_SECTION)));
aipl_image_t camera_image = {rgb_buffer,          // data
                             CAM_FRAME_WIDTH,     // pitch
                             CAM_FRAME_WIDTH,     // width
                             CAM_FRAME_HEIGHT,    // height
                             AIPL_COLOR_BGR888};  // format
#endif

/* Camera  Driver instance 0 */
extern ARM_DRIVER_CPI Driver_CPI;
static ARM_DRIVER_CPI *CAMERAdrv = &Driver_CPI;

typedef enum { CAM_CB_EVENT_NONE = 0, CAM_CB_EVENT_ERROR = (1 << 0), CAM_CB_EVENT_CAPTURE_STOPPED = (1 << 1) } CAM_CB_EVENT;

static volatile CAM_CB_EVENT g_cam_cb_events = CAM_CB_EVENT_NONE;

static void camera_callback(uint32_t event) {
    switch (event) {
        case ARM_CPI_EVENT_CAMERA_CAPTURE_STOPPED:
            g_cam_cb_events |= CAM_CB_EVENT_CAPTURE_STOPPED;
            break;
        case ARM_CPI_EVENT_CAMERA_FRAME_HSYNC_DETECTED:
            break;
        case ARM_CPI_EVENT_CAMERA_FRAME_VSYNC_DETECTED:
            break;

        case ARM_CPI_EVENT_ERR_HARDWARE:
        case ARM_CPI_EVENT_MIPI_CSI2_ERROR:
        case ARM_CPI_EVENT_ERR_CAMERA_INPUT_FIFO_OVERRUN:
        case ARM_CPI_EVENT_ERR_CAMERA_OUTPUT_FIFO_OVERRUN:
        default:
            g_cam_cb_events |= CAM_CB_EVENT_ERROR | CAM_CB_EVENT_CAPTURE_STOPPED;  // Mark error always as stopped
            break;
    }
}

int camera_init(void) {
    int ret = CAMERAdrv->Initialize(camera_callback);
    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error: CAMERA Initialize failed.\r\n");
        return ret;
    }

    /* Power up Camera peripheral */
    ret = CAMERAdrv->PowerControl(ARM_POWER_FULL);
    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error: CAMERA Power Up failed.\r\n");
        return ret;
    }

    /* Control configuration for camera controller */
    ret = CAMERAdrv->Control(CPI_CONFIGURE, 0);
    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error: CPI Configuration failed.\r\n");
        return ret;
    }

    /* Control configuration for camera sensor */
    ret = CAMERAdrv->Control(CPI_CAMERA_SENSOR_CONFIGURE, 0);
    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error: CAMERA SENSOR Configuration failed.\r\n");
        return ret;
    }

    /*Control configuration for camera events */
    ret = CAMERAdrv->Control(CPI_EVENTS_CONFIGURE, ARM_CPI_EVENT_CAMERA_CAPTURE_STOPPED | ARM_CPI_EVENT_ERR_CAMERA_INPUT_FIFO_OVERRUN |
                                                       ARM_CPI_EVENT_ERR_CAMERA_OUTPUT_FIFO_OVERRUN | ARM_CPI_EVENT_ERR_HARDWARE);
    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error: CAMERA SENSOR Event Configuration failed.\r\n");
        return ret;
    }

    // NOTE: There is automatic gain control implemented for ARX3A0 in ML example repository
    //       https://github.com/alifsemi/alif_ml-embedded-evaluation-kit
#if RTE_Drivers_CAMERA_SENSOR_ARX3A0
    CAMERAdrv->Control(CPI_CAMERA_SENSOR_GAIN, 0x10000 * 5.0f);
#endif

    return ret;
}

int camera_capture(void) {
    g_cam_cb_events = CAM_CB_EVENT_NONE;

    int ret = CAMERAdrv->CaptureFrame(camera_buffer);

    // Wait for capture
    if (ret == ARM_DRIVER_OK) {
        while (!(g_cam_cb_events & CAM_CB_EVENT_CAPTURE_STOPPED)) {
            __WFI();
        }
    }

    // Invalidate cache before reading the camera_buffer
    SCB_CleanInvalidateDCache();

    if (g_cam_cb_events & CAM_CB_EVENT_ERROR) {
        ret = 0xFFFF;
    }

    return ret;
}

void camera_post_capture_process(void) {

    bool clean_cache = false;

    // ARX3A0 camera uses bayer output
    // MT9M114 can use bayer or RGB565 depending on RTE config
#if !CAM_USE_RGB565
    dc1394_bayer_Simple(camera_buffer, rgb_buffer, CAM_FRAME_WIDTH, CAM_FRAME_HEIGHT, CAM_BAYER_FORMAT);
    camera_get_image()->format = AIPL_COLOR_BGR888;
    clean_cache = true;
#endif

    // ARX3A0 is BGR888 after bayer conversion --> convert to RGB565
    // The rest of the pipeline and LCD buffer are in RGB565 format for both cameras
    if (camera_get_image()->format != AIPL_COLOR_RGB565) {
        aipl_image_t img_temp = *camera_get_image();
        img_temp.format = AIPL_COLOR_RGB565;
        aipl_error_t aipl_ret = aipl_color_convert_img(camera_get_image(),
                                                       &img_temp);
        if (aipl_ret == AIPL_ERR_OK) {
            camera_get_image()->format = img_temp.format;
        } else {
            printf("Error: Conversion to RGB565 failed.\r\n");
        }
        clean_cache = true;
    }

    if (clean_cache) {
        SCB_CleanDCache();
    }
}

aipl_image_t *camera_get_image() { return &camera_image; }

/* Revised matrix (BECP-1455)
 * Manual WB, Illuminant 6021, Relative Red 1.42, Relative Blue 1.47
 */
#define C_RR +2.2583f
#define C_RG -0.5501f
#define C_RB -0.1248f
#define C_GR -0.1606f
#define C_GG +1.4318f
#define C_GB -0.5268f
#define C_BR -0.6317f
#define C_BG -0.0653f
#define C_BB +2.3735f

const float *camera_get_color_correction_matrix(void) {
#if RTE_Drivers_CAMERA_SENSOR_ARX3A0
    static const float ccm[9] = {C_RR, C_GR, C_BR, C_RG, C_GG, C_BG, C_RB, C_GB, C_BB};
    return ccm;
#endif
    return NULL;
}

static inline float srgb_oetf(float lum) {
    if (lum <= 0.0031308f) {
        return 12.92f * lum;
    } else {
        return 1.055f * powf(lum, 1.0f / 2.4f) - 0.055f;
    }
}

uint8_t *camera_get_gamma_lut(void) {
    static bool inited = false;
    static uint8_t lut[256];

    if (inited) {
        return lut;
    }

    for (int i = 0; i < 256; i++) {
        lut[i] = (uint8_t)(255.0f * srgb_oetf(i * (1.0f / 255.0f)) + 0.5f);
    }

    inited = true;
    return lut;
}
