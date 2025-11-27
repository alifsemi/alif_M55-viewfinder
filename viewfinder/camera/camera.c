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
#include "isp_header.h"

#include <math.h>
#include <stdio.h>

#include "Driver_CPI.h"
#include "aipl_color_conversion.h"
#include "aipl_demosaic.h"

// Camera frame buffer (can be bayer or RGB565 depending on camera module and camera module configuration)
// Raw buffer is not needed when using ISP and disabling the CPI AXI output
#if RTE_ISP
#if RTE_CPI_AXI_PORT
#error "RTE_CPI_AXI_PORT should be disabled in this example to save the raw camera frame buffer memory"
#endif
#define OUT_IMAGE_PITCH ISP_PITCH
#define OUT_IMAGE_WIDTH ISP_OUTPUT_X
#define OUT_IMAGE_HEIGHT ISP_OUTPUT_Y
#else
#if defined(RTE_CPI_AXI_PORT) && !RTE_CPI_AXI_PORT
#error "RTE_CPI_AXI_PORT should be enabled when ISP is disabled"
#endif
static uint8_t camera_raw_buffer[CAM_FRAME_SIZE * (CAM_USE_RGB565 ? 2 : 1)] __attribute__((aligned(32), section(".bss.camera_raw_frame_buf")));
#define OUT_IMAGE_PITCH CAM_FRAME_WIDTH
#define OUT_IMAGE_WIDTH CAM_FRAME_WIDTH
#define OUT_IMAGE_HEIGHT CAM_FRAME_HEIGHT
#endif

/* Camera  Driver instance 0 */
extern ARM_DRIVER_CPI Driver_CPI;
static ARM_DRIVER_CPI *CAMERAdrv = &Driver_CPI;

typedef enum { CAM_CB_EVENT_NONE = 0, CAM_CB_EVENT_ERROR = (1 << 0), CAM_CB_EVENT_CAPTURE_STOPPED = (1 << 1),
             ISP_VSYNC_CB_EVENT = (1 << 2), ISP_MI_FRAME_DUMP_EVENT = ( 1 << 3), ISP_FRAME_IN_DETECTED = (1 << 4) } CAM_CB_EVENT;

static volatile CAM_CB_EVENT g_cam_cb_events = CAM_CB_EVENT_NONE;

#if RTE_ISP
static volatile int isp_counter = 0;
static volatile int isp_mi_counter = 0;

static void isp_buffer_init(void) {
    for (int i = 0; i < RTE_ISP_BUFFER_COUNT; i++) {
        buffer_array[i].index = i;
        switch (ISP_AUX_BUFFER_TYPE) {
        case ISP_PLANAR:
            buffer_array[i].numPlanes = 3;
            break;
        case ISP_SEMIPLANAR:
            buffer_array[i].numPlanes = 2;
            break;
        case ISP_NONE:
        case ISP_INTERLEAVED:
        default:
            buffer_array[i].numPlanes = 1;
            break;
        }
        buffer_array[i].imageSize = ISP_OUTPUT_TOTAL_SIZE;
        buffer_array[i].planes[0].dmaPhyAddr = (vsi_dma_t)y_buffer[i];
#if ISP_OUTPUT_SIZE_CB
        buffer_array[i].planes[1].dmaPhyAddr = (vsi_dma_t)cb_buffer[i];
#endif
#if ISP_OUTPUT_SIZE_CR
        buffer_array[i].planes[2].dmaPhyAddr = (vsi_dma_t)cr_buffer[i];
#endif
#if ISP_OUTPUT_SIZE_CBCR
        buffer_array[i].planes[1].dmaPhyAddr = (vsi_dma_t)cbcr_buffer[i];
#endif
    }
}
#endif

static void camera_callback(uint32_t event) {
    switch (event) {
        case ARM_CPI_EVENT_CAMERA_CAPTURE_STOPPED:
            g_cam_cb_events |= CAM_CB_EVENT_CAPTURE_STOPPED;
            break;
#if RTE_ISP            
        case ARM_ISP_EVENT_FRAME_VSYNC_DETECTED:
            isp_counter++;
            g_cam_cb_events |= ISP_VSYNC_CB_EVENT;
            break;
        case ARM_ISP_EVENT_FRAME_IN_DETECTED:
            g_cam_cb_events |= ISP_FRAME_IN_DETECTED;
            break;            
        case ARM_ISP_MI_EVENT_MP_FRAME_END_DETECTED:
            isp_mi_counter++;
            g_cam_cb_events |= ISP_MI_FRAME_DUMP_EVENT;
            break;
        case ARM_ISP_MI_EVENT_FILL_MP_Y_DETECTED:
            g_cam_cb_events |= ISP_MI_FRAME_DUMP_EVENT;
            break;
        case ARM_ISP_MI_EVENT_MP_Y_WRAP_DETECTED:
            g_cam_cb_events |= ISP_MI_FRAME_DUMP_EVENT;
            break;
#endif
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
#if RTE_ISP
    isp_buffer_init();
#endif
    int ret = CAMERAdrv->Initialize(camera_callback);
    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error: CAMERA Initialize failed.\r\n");
        return ret;
    }
    printf("\r\n CAMERA Initialized.\r\n");

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
#if RTE_ISP
    for (int i = 0; i < RTE_ISP_BUFFER_COUNT; i++) {
        /* Control configuration for camera events */
        ret = CAMERAdrv->Control(ISP_CONTROL_QBUF, (uint32_t) &buffer_array[i]);
        if(ret != ARM_DRIVER_OK)
        {
            printf("\r\n Error: ISP buffer configuration failed.\r\n");
            return ret;
        }
    }
#endif
    // NOTE: There is automatic gain control implemented for ARX3A0 in ML example repository
    //       https://github.com/alifsemi/alif_ml-embedded-evaluation-kit
#if defined(RTE_Drivers_CAMERA_SENSOR_ARX3A0)
    CAMERAdrv->Control(CPI_CAMERA_SENSOR_GAIN, 0x10000 * 2.0f);
#endif
    printf("CPI camera Initialization Success\r\n");
    return ret;
}

int camera_capture(void) {
    g_cam_cb_events = CAM_CB_EVENT_NONE;
    int ret = ARM_DRIVER_OK;
#if RTE_ISP
    CAM_CB_EVENT callback_event = ISP_MI_FRAME_DUMP_EVENT;
    // It is safe to use dummy buffer address because RTE_CPI_AXI_PORT is disabled
    ret = CAMERAdrv->CaptureFrame((uint8_t*)0xABCDABCD);
#else
    CAM_CB_EVENT callback_event = CAM_CB_EVENT_CAPTURE_STOPPED;
    ret = CAMERAdrv->CaptureFrame(camera_raw_buffer);
#endif

    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error: CAMERA Capture Frame failed.\r\n");
        return ret;
    }

    // Wait for capture
    if (ret == ARM_DRIVER_OK) {
        while (!(g_cam_cb_events & callback_event)) {
            __WFI();
        }
    }

#if RTE_ISP
    ret = CAMERAdrv->Control(ISP_PROCESS_FRAME_END, 0);
    if (ret != ARM_DRIVER_OK){
        printf("\r\n Error: ISP Process Frame End failed.\r\n");
        return ret;
    }
#endif

    if (g_cam_cb_events & CAM_CB_EVENT_ERROR) {
        printf("\r\n Error: g_cam_cb_events = 0x%X\r\n", g_cam_cb_events);
        ret = 0xFFFF;
    }
    return ret;
}

aipl_image_t camera_post_capture_process(bool *buffer_is_dynamic)
{
#if CAM_USE_RGB565
    *buffer_is_dynamic = false;

    // Use RGB565 camera buffer as image data
    // No conversion required if the camera provides RGB565 image as output
    aipl_image_t cam_image = {
        .data = camera_raw_buffer,
        .pitch = CAM_FRAME_WIDTH,
        .width = CAM_FRAME_WIDTH,
        .height = CAM_FRAME_HEIGHT,
        .format = AIPL_COLOR_RGB565
    };
    return cam_image;
#else // !CAM_USE_RGB565
    // Convert camera or ISP output to dynamically allocated RGB565 image
    aipl_image_t cam_image;
    aipl_error_t aipl_ret = aipl_image_create(&cam_image,
                                              OUT_IMAGE_PITCH,
                                              OUT_IMAGE_WIDTH,
                                              OUT_IMAGE_HEIGHT,
                                              AIPL_COLOR_RGB565);
    if (aipl_ret != AIPL_ERR_OK) {
        printf("Error: Failed allocating camera image\r\n");
        cam_image.data = NULL;
        return cam_image;
    }
    *buffer_is_dynamic = true;

#if RTE_ISP
    aipl_ret = aipl_color_convert_yuy2_to_rgb565_default(y_buffer[0], cam_image.data,
                                                 cam_image.pitch, cam_image.width,
                                                 cam_image.height);
    if (aipl_ret != AIPL_ERR_OK)
    {
        printf("\r\nError: Camera format conversion from yuy2 to rgb565 failed (%s)\r\n",
                aipl_error_str(aipl_ret));
        __BKPT(0);
    }
#else // !RTE_ISP
    // ARX3A0 camera uses bayer output
    // MT9M114 can use bayer or RGB565 depending on RTE config
    // Convert raw image to RGB565 buffer using debayering method
    aipl_ret = aipl_demosaic(camera_raw_buffer, cam_image.data,
                             cam_image.pitch, cam_image.width,
                             cam_image.height, CAM_BAYER_FORMAT,
                             AIPL_COLOR_RGB565);
    if (aipl_ret != AIPL_ERR_OK)
    {
        printf("\r\nError: Camera output debayering failed (%s)\r\n",
                aipl_error_str(aipl_ret));
        __BKPT(0);
    }
#endif // RTE_ISP
#endif // CAM_USE_RGB565

    SCB_CleanDCache();
    return cam_image;
}

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
#if defined(RTE_Drivers_CAMERA_SENSOR_ARX3A0)
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
