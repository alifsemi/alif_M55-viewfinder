/* Copyright (C) 2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#ifndef CAMERA_H_
#define CAMERA_H_

#include "RTE_Components.h"
#include CMSIS_device_header

#include "aipl_image.h"

// Choose camera parameters based on RTE configuration
#if defined(RTE_Drivers_CAMERA_SENSOR_MT9M114)
#if (RTE_MT9M114_CAMERA_SENSOR_MIPI_IMAGE_CONFIG == 1)
#define CAM_FRAME_WIDTH      (1280)
#define CAM_FRAME_HEIGHT     (720)
#define CAM_COLOR_CORRECTION (0)
#define CAM_USE_RGB565       (0)
#define CAM_BYTES_PER_PIXEL  (1)
#define CAM_BAYER_FORMAT     (AIPL_BAYER_GRBG)
#elif (RTE_MT9M114_CAMERA_SENSOR_MIPI_IMAGE_CONFIG == 2)
#define CAM_FRAME_WIDTH      (1280)
#define CAM_FRAME_HEIGHT     (720)
#define CAM_COLOR_CORRECTION (0)
#define CAM_USE_RGB565       (1)
#define CAM_BYTES_PER_PIXEL  (2)
#elif (RTE_MT9M114_CAMERA_SENSOR_MIPI_IMAGE_CONFIG == 3)
#define CAM_FRAME_WIDTH      (640)
#define CAM_FRAME_HEIGHT     (480)
#define CAM_COLOR_CORRECTION (0)
#define CAM_USE_RGB565       (1)
#define CAM_BYTES_PER_PIXEL  (2)
#else
#error "Unsupported MT9M114 configuration"
#endif
#elif defined(RTE_Drivers_CAMERA_SENSOR_ARX3A0)
#define CAM_FRAME_WIDTH      (RTE_ARX3A0_CAMERA_SENSOR_FRAME_WIDTH)
#define CAM_FRAME_HEIGHT     (RTE_ARX3A0_CAMERA_SENSOR_FRAME_HEIGHT)
#define CAM_COLOR_CORRECTION (1)
#define CAM_USE_RGB565       (0)
#define CAM_BAYER_FORMAT     (AIPL_BAYER_GRBG)
#elif defined(RTE_Drivers_CAMERA_SENSOR_OV5675)
#define CAM_FRAME_WIDTH      (RTE_OV5675_CAMERA_SENSOR_FRAME_WIDTH)
#define CAM_FRAME_HEIGHT     (RTE_OV5675_CAMERA_SENSOR_FRAME_HEIGHT)
#define CAM_COLOR_CORRECTION (0)
#define CAM_USE_RGB565       (0)
#define CAM_BAYER_FORMAT     (AIPL_BAYER_GRBG)
#else
#error "Unsupported camera"
#endif

#define CAM_FRAME_SIZE       (CAM_FRAME_WIDTH * CAM_FRAME_HEIGHT)
#define CAM_MPIX             (CAM_FRAME_SIZE / 1000000.0f)
#define CAM_FRAME_SIZE_BYTES (CAM_FRAME_SIZE * CAM_BYTES_PER_PIXEL)

int camera_init(void);
int camera_capture(void);
aipl_image_t camera_post_capture_process(bool *buffer_is_dynamic);
const float* camera_get_color_correction_matrix(void);
uint8_t* camera_get_gamma_lut(void);

#endif  // CAMERA_H_
