/**
 * @file aipl_config.h
 *
 */

#ifndef AIPL_CONFIG_H
#define AIPL_CONFIG_H

#ifdef __cplusplus
extern "C" {
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
 * Use M-Profile Vector Extension setting
 *
 */
#define AIPL_USE_MVE (__ARM_FEATURE_MVE & 1)
//  #define AIPL_USE_MVE 0

/**
 * Use D/AVE2D GPU
 */
#define AIPL_USE_DAVE2D 1

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
 */
// #define AIPL_CONVERT_ALPHA8
#define AIPL_CONVERT_ARGB8888
#define AIPL_CONVERT_ARGB4444
#define AIPL_CONVERT_ARGB1555
// #define AIPL_CONVERT_RGBA8888
#define AIPL_CONVERT_RGBA4444
#define AIPL_CONVERT_RGBA5551
#define AIPL_CONVERT_RGB888
#define AIPL_CONVERT_RGB565
// #define AIPL_CONVERT_YV12
#define AIPL_CONVERT_I420
// #define AIPL_CONVERT_I422
#define AIPL_CONVERT_I444
// #define AIPL_CONVERT_I400
// #define AIPL_CONVERT_NV12
// #define AIPL_CONVERT_NV21
// #define AIPL_CONVERT_YUY2
// #define AIPL_CONVERT_UYVY

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  /* AIPL_CONFIG_H */
