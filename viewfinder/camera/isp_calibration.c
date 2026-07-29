/* Copyright (C) 2026 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

 /*******************************************************************************
 * @file     isp_calibration.c
 * @brief    Project-local, editable ISP calibration and configuration
 *
 *           The Ensemble pack ships default ISP tuning in
 *           Alif_CMSIS/Source/<sensor>_isp_param.c, whose header states the
 *           parameters are "not yet sensor-calibrated". That pack file is a
 *           plain (non-config) source, so editing it is overwritten on every
 *           pack update, and its globals (calibration_data / port_attr /
 *           chan_attr) cannot be redefined in the project without a duplicate-
 *           symbol link error.
 *
 ******************************************************************************/

#include "RTE_Components.h"
#include "RTE_Device.h"

#if RTE_ISP == 1

#include "isp_param.h"
#include "isp_calibration.h"

/* ---------------------------------------------------------------------------
 * Camera sensor pixel format and resolution
 * Map resolution from RTE config to ISP port_attr_user below.
 * --------------------------------------------------------------------------- */
#if defined(RTE_Drivers_CAMERA_SENSOR_ARX3A0)
#define CAMERA_SENSOR_FRAME_WIDTH   RTE_ARX3A0_CAMERA_SENSOR_FRAME_WIDTH
#define CAMERA_SENSOR_FRAME_HEIGHT  RTE_ARX3A0_CAMERA_SENSOR_FRAME_HEIGHT
#define CAMERA_SENSOR_PIXEL_FORMAT  PIXEL_FORMAT_GRBG10
#elif defined(RTE_Drivers_CAMERA_SENSOR_MT9M114)
#define CAMERA_SENSOR_FRAME_WIDTH   RTE_MT9M114_CAMERA_SENSOR_FRAME_WIDTH
#define CAMERA_SENSOR_FRAME_HEIGHT  RTE_MT9M114_CAMERA_SENSOR_FRAME_HEIGHT
#define CAMERA_SENSOR_PIXEL_FORMAT  PIXEL_FORMAT_GRBG10
#elif defined(RTE_Drivers_CAMERA_SENSOR_OV5675)
#define CAMERA_SENSOR_FRAME_WIDTH   RTE_OV5675_CAMERA_SENSOR_FRAME_WIDTH
#define CAMERA_SENSOR_FRAME_HEIGHT  RTE_OV5675_CAMERA_SENSOR_FRAME_HEIGHT
#define CAMERA_SENSOR_PIXEL_FORMAT  PIXEL_FORMAT_GRBG10
#else
#error "No supported ISP camera sensor enabled."
#endif

/* ---------------------------------------------------------------------------
 * ISP Port Attribute
 * Describes what is coming through the pipeline into the ISP IP.
 *
 * snsRect, inFormRect, iSRect: set to full sensor native resolution.
 *   Note: snsRect.width and snsRect.height are further overridden at runtime
 *   by the camera sensor driver's reported dimensions.
 *
 * outFormRect: set to full sensor dimensions (cropping disabled).
 * --------------------------------------------------------------------------- */

static const ISP_PORT_ATTR_S port_attr_user = {
    .ispInputType = INPUT_TYPE_SENSOR,
    .ispMode      = ISP_MODE_RAW,
    .hdrMode      = HDR_MODE_LINEAR,
    .pixelFormat  = CAMERA_SENSOR_PIXEL_FORMAT,
    .snsRect = {
        .top    = 0,
        .left   = 0,
        .width  = CAMERA_SENSOR_FRAME_WIDTH,
        .height = CAMERA_SENSOR_FRAME_HEIGHT,
    },
    .inFormRect = {
        .top    = 0,
        .left   = 0,
        .width  = CAMERA_SENSOR_FRAME_WIDTH,
        .height = CAMERA_SENSOR_FRAME_HEIGHT,
    },
    .iSRect = {
        .top    = 0,
        .left   = 0,
        .width  = CAMERA_SENSOR_FRAME_WIDTH,
        .height = CAMERA_SENSOR_FRAME_HEIGHT,
    },
    .outFormRect = {
        .top    = 0,
        .left   = 0,
        .width  = CAMERA_SENSOR_FRAME_WIDTH,
        .height = CAMERA_SENSOR_FRAME_HEIGHT,
    },
};

void isp_set_user_configuration(void)
{
    calibration_data = calibration_data_user;
    port_attr = port_attr_user;
}

void isp_param_set_crop(vsi_u32_t top, vsi_u32_t left, vsi_u32_t width, vsi_u32_t height)
{
    /* RECT_S field naming is swapped in the libisp:
     * RECT_S.top  -> ISP_OUT_H_OFFS (horizontal/left offset)
     * RECT_S.left -> ISP_OUT_V_OFFS (vertical/top offset)
     * We swap here so our API uses conventional image coordinates. */
    port_attr.outFormRect.top    = left;
    port_attr.outFormRect.left   = top;
    port_attr.outFormRect.width  = width;
    port_attr.outFormRect.height = height;

    /* Set the AE measurement block to match the crop region */
    calibration_data.modules.aem.blockWin.hOffs = 0;
    calibration_data.modules.aem.blockWin.vOffs = 0;
    calibration_data.modules.aem.blockWin.hSize = width;
    calibration_data.modules.aem.blockWin.vSize = height;
}


void isp_param_set_square_crop(void)
{
    vsi_u32_t side = CAMERA_SENSOR_FRAME_WIDTH < CAMERA_SENSOR_FRAME_HEIGHT
                   ? CAMERA_SENSOR_FRAME_WIDTH
                   : CAMERA_SENSOR_FRAME_HEIGHT;
    vsi_u32_t top  = (CAMERA_SENSOR_FRAME_HEIGHT - side) / 2;
    vsi_u32_t left = (CAMERA_SENSOR_FRAME_WIDTH - side) / 2;
    isp_param_set_crop(top, left, side, side);
}

void isp_param_set_output_dimensions(vsi_u32_t width, vsi_u32_t height)
{
    chan_attr.chnFormat.width  = width;
    chan_attr.chnFormat.height = height;
}

#endif  // RTE_ISP