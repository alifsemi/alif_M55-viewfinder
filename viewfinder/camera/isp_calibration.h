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

/* Applies the project-local, editable ISP calibration (see isp_calibration.c)
 * on top of the pack default. Must be called before the ISP is initialized
 * (i.e. before the camera controller is configured). No-op unless RTE_ISP is
 * enabled with the MT9M114 sensor. */
void isp_apply_calibration(void);

#endif /* ISP_CALIBRATION_H_ */
