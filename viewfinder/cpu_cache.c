/* Copyright (C) 2023-2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

#include "aipl_cache.h"
#include <RTE_Components.h>
#include CMSIS_device_header

void aipl_cpu_cache_clean(const void* ptr, uint32_t size)
{
    RTSS_CleanDCache_by_Addr((volatile void*)ptr, size);
}

void aipl_cpu_cache_invalidate(const void* ptr, uint32_t size)
{
    RTSS_InvalidateDCache_by_Addr((volatile void*)ptr, size);
}