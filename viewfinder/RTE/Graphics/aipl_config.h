/**
 * @file aipl_config.h
 *
 */

#ifndef AIPL_CONFIG_H
#define AIPL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_RTE_)
#include <RTE_Components.h>
#include CMSIS_device_header
#endif

/**
 * Custom video alloc setting
 *
 * Options:
 *  0 - use default malloc()
 *  1 - the allocation and free functions should be
 *      provided by the user
 */
#define AIPL_CUSTOM_VIDEO_ALLOC  1

/**
 * Custom D/AVE2D initialization function
 *
 * Options:
 *  0 - use the default aipl_dave2d_init()
 *  1 - use user-defined initialization function;
 *      user must also provide aipl_dave2d_handle()
 */
#define AIPL_CUSTOM_DAVE2D_INIT 0

/**
 * Enable color format conversions
 *
 * Constants TO_<COLOR_FORMAT> can be used to
 * define conversions for each individual color format
 */
#define TO_ALPHA8_I400  BIT(0)
#define TO_ARGB8888     BIT(1)
#define TO_ARGB4444     BIT(2)
#define TO_ARGB1555     BIT(3)
#define TO_RGBA8888     BIT(4)
#define TO_RGBA4444     BIT(5)
#define TO_RGBA5551     BIT(6)
#define TO_BGR888       BIT(7)
#define TO_RGB888       BIT(8)
#define TO_RGB565       BIT(9)
#define TO_YV12         BIT(10)
#define TO_I420         BIT(11)
#define TO_I422         BIT(12)
#define TO_I444         BIT(13)
#define TO_NV12         BIT(14)
#define TO_NV21         BIT(15)
#define TO_YUY2         BIT(16)
#define TO_UYVY         BIT(17)
#define TO_ALL          (TO_ALPHA8_I400 | TO_ARGB8888 | TO_ARGB4444\
                         | TO_ARGB1555 | TO_RGBA8888 | TO_RGBA4444\
                         | TO_RGBA5551 | TO_BGR888 | TO_RGB565\
                         | TO_YV12 | TO_I420 | TO_I422 | TO_I444\
                         | TO_NV12 | TO_NV21 | TO_YUY2 | TO_UYVY)

/**
 * Set conversion from each color format using
 * the convstants above
 *
 * To complete disable color conversion the marco should
 * be defined as 0
 */
#define AIPL_CONVERT_ALPHA8_I400    0
#define AIPL_CONVERT_ARGB8888       0
#define AIPL_CONVERT_ARGB4444       0
#define AIPL_CONVERT_ARGB1555       0
#define AIPL_CONVERT_RGBA8888       0
#define AIPL_CONVERT_RGBA4444       0
#define AIPL_CONVERT_RGBA5551       0
#define AIPL_CONVERT_BGR888         TO_RGB565
#define AIPL_CONVERT_RGB888         TO_RGB565
#define AIPL_CONVERT_RGB565         0
#define AIPL_CONVERT_YV12           0
#define AIPL_CONVERT_I420           0
#define AIPL_CONVERT_I422           0
#define AIPL_CONVERT_I444           0
#define AIPL_CONVERT_NV12           0
#define AIPL_CONVERT_NV21           0
#define AIPL_CONVERT_YUY2           0
#define AIPL_CONVERT_UYVY           0

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  /* AIPL_CONFIG_H */
