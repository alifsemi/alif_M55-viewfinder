/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#include "power_profile.h"
#include "aipm_109.h"

static run_profile_t default_runprof;
static off_profile_t default_offprof;

void* get_runprof_109(void)
{
    #include "run_profile.inc"
    return &default_runprof;
}

void* get_offprof_109(void)
{
    #include "off_profile.inc"
    return &default_offprof;
}
