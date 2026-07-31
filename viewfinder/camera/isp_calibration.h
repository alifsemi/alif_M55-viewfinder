/* Copyright (C) 2026 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#ifndef ISP_CALIBRATION_H_
#define ISP_CALIBRATION_H_

#include "RTE_Components.h"
#include "RTE_Device.h"

#if RTE_ISP == 1
#include "isp_param.h"

/* Editable, project-local ISP calibration for the selected sensor. Defined
 * (with external linkage) in the sensor-specific isp_calibration_<sensor>.c
 * that matches the RTE camera sensor component. */
extern const ISP_CALIB_DATA_S calibration_data_user;
#endif /* RTE_ISP */

void isp_set_user_configuration(void);

/* Set the ISP output crop rectangle */
void isp_param_set_crop(vsi_u32_t top, vsi_u32_t left, vsi_u32_t width, vsi_u32_t height);

/* Set a centred square crop using the maximum square that fits the sensor. (helpful for keeping the aspect ratio) */
void isp_param_set_square_crop(void);

/* Set the ISP channel output dimensions (rescaling) the cropped area */
void isp_param_set_output_dimensions(vsi_u32_t width, vsi_u32_t height);

#endif /* ISP_CALIBRATION_H_ */
