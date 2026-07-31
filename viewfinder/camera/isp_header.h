/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#ifndef ISP_HEADER_H_
#define ISP_HEADER_H_


#if RTE_ISP
#include "Driver_ISP.h"
#include "vsi_comm_video.h"

enum {
    ISP_PLANAR = 1,
    ISP_SEMIPLANAR,
    ISP_INTERLEAVED,
    ISP_NONE,
};


/* ISP Output image width */
#define ISP_OUTPUT_X    RTE_ISP_OUTPUT_WIDTH

/* ISP output image height */
#define ISP_OUTPUT_Y    RTE_ISP_OUTPUT_HEIGHT

#if (RTE_ISP_OUTPUT_FORMAT == 20)   // RAW8 output from ISP
#define ISP_OUTPUT_SIZE_Y  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_AUX_BUFFER_TYPE  ISP_NONE
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y)

#elif (RTE_ISP_OUTPUT_FORMAT == 21) // RAW10 output from ISP
#define ISP_OUTPUT_SIZE_Y  ((ISP_OUTPUT_X * ISP_OUTPUT_Y * 5) >> 2)
#define ISP_AUX_BUFFER_TYPE  ISP_NONE
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y)

#elif (RTE_ISP_OUTPUT_FORMAT == 22) // RAW12 output from ISP
#define ISP_OUTPUT_SIZE_Y  ((ISP_OUTPUT_X * ISP_OUTPUT_Y * 12) >> 3)
#define ISP_AUX_BUFFER_TYPE  ISP_NONE
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y)

#elif (RTE_ISP_OUTPUT_FORMAT == 23) // NV12 output from ISP
#define ISP_OUTPUT_SIZE_Y  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_AUX_BUFFER_TYPE  ISP_SEMIPLANAR
#define ISP_OUTPUT_SIZE_CBCR  ((ISP_OUTPUT_X * ISP_OUTPUT_Y) >>1 )
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y + ISP_OUTPUT_SIZE_CBCR)

#elif (RTE_ISP_OUTPUT_FORMAT == 25) // NV16 output from ISP
#define ISP_OUTPUT_SIZE_Y  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_AUX_BUFFER_TYPE  ISP_SEMIPLANAR
#define ISP_OUTPUT_SIZE_CBCR  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y + ISP_OUTPUT_SIZE_CBCR)

#elif (RTE_ISP_OUTPUT_FORMAT == 30) // YUV422P output from ISP
#define ISP_OUTPUT_SIZE_Y  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_AUX_BUFFER_TYPE  ISP_PLANAR
#define ISP_OUTPUT_SIZE_CB  ((ISP_OUTPUT_X * ISP_OUTPUT_Y) >> 1)
#define ISP_OUTPUT_SIZE_CR  ((ISP_OUTPUT_X * ISP_OUTPUT_Y) >> 1)
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y + ISP_OUTPUT_SIZE_CB + ISP_OUTPUT_SIZE_CR)

#elif (RTE_ISP_OUTPUT_FORMAT == 31) // YUV420P output from ISP
#define ISP_OUTPUT_SIZE_Y  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_AUX_BUFFER_TYPE  ISP_PLANAR
#define ISP_OUTPUT_SIZE_CB  ((ISP_OUTPUT_X * ISP_OUTPUT_Y) >> 2)
#define ISP_OUTPUT_SIZE_CR  ((ISP_OUTPUT_X * ISP_OUTPUT_Y) >> 2)
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y + ISP_OUTPUT_SIZE_CB + ISP_OUTPUT_SIZE_CR)

#elif (RTE_ISP_OUTPUT_FORMAT == 32) // YUYV (YUV422 packed) output from ISP
#define ISP_OUTPUT_SIZE_Y  (ISP_OUTPUT_X * ISP_OUTPUT_Y * 2)
#define ISP_PITCH          ISP_OUTPUT_X
#define ISP_AUX_BUFFER_TYPE  ISP_INTERLEAVED
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y)

#elif (RTE_ISP_OUTPUT_FORMAT == 37) // YUV400 (Grayscale) output from ISP
#define ISP_OUTPUT_SIZE_Y  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_AUX_BUFFER_TYPE  ISP_NONE
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y)

#elif (RTE_ISP_OUTPUT_FORMAT == 38) // RGB888 Interleaved output from ISP
#define ISP_OUTPUT_SIZE_Y  (ISP_OUTPUT_X * ISP_OUTPUT_Y * 3)
#define ISP_AUX_BUFFER_TYPE  ISP_INTERLEAVED
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y)

#elif (RTE_ISP_OUTPUT_FORMAT == 39) // RGB888 planar output from ISP
#define ISP_OUTPUT_SIZE_Y  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_AUX_BUFFER_TYPE  ISP_PLANAR
#define ISP_PITCH          ISP_OUTPUT_X
#define ISP_OUTPUT_SIZE_CB  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_OUTPUT_SIZE_CR  (ISP_OUTPUT_X * ISP_OUTPUT_Y)
#define ISP_OUTPUT_TOTAL_SIZE  (ISP_OUTPUT_SIZE_Y + ISP_OUTPUT_SIZE_CB + ISP_OUTPUT_SIZE_CR)
#endif

#if (ISP_OUTPUT_SIZE_Y)
struct isp_buffers {
    uint8_t y[ISP_OUTPUT_SIZE_Y];
#if defined(ISP_OUTPUT_SIZE_CB) && (ISP_OUTPUT_SIZE_CB)
    uint8_t cb[ISP_OUTPUT_SIZE_CB];
#endif
#if defined(ISP_OUTPUT_SIZE_CR) && (ISP_OUTPUT_SIZE_CR)
    uint8_t cr[ISP_OUTPUT_SIZE_CR];
#endif
#if defined(ISP_OUTPUT_SIZE_CBCR) && (ISP_OUTPUT_SIZE_CBCR)
    uint8_t cbcr[ISP_OUTPUT_SIZE_CBCR];
#endif
} __attribute__((packed));

struct isp_buffers isp_buf[RTE_ISP_BUFFER_COUNT]
    __attribute__((section(".bss.lcd_frame_buf"), aligned(32)));
#endif

VIDEO_BUF_S buffer_array[RTE_ISP_BUFFER_COUNT];
#endif  // RTE_ISP

#endif  // ISP_HEADER_H_
