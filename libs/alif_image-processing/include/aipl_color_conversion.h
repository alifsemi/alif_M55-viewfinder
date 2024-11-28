/**
 * @file aipl_color_conversion.h
 *
 * @return error code
 */

#ifndef AIPL_COLOR_CONVERSION_H
#define AIPL_COLOR_CONVERSION_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "aipl_color_formats.h"
#include "aipl_error.h"
#include "aipl_image.h"
#include "aipl_config.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * Convert image color format using raw pointer interface
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param input_format  input image format
 * @param output_format output image format
 * @return error code
 */
aipl_error_t aipl_color_convert(const void* input, void* output,
                                uint32_t pitch,
                                uint32_t width, uint32_t height,
                                aipl_color_format_t input_format,
                                aipl_color_format_t output_format);

/**
 * Convert image color format using aipl_image_t interface
 *
 * @param input         input image
 * @param output        output image
 * @return error code
 */
aipl_error_t aipl_color_convert_img(const aipl_image_t* input,
                                    aipl_image_t* output);

#ifdef AIPL_CONVERT_ARGB8888
/**
 * Convert ARGB8888 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format);

/**
 * Convert ARGB8888 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);


/**
 * Convert ARGB8888 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB8888 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB8888 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB8888 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB8888 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB8888 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert ARGB8888 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert ARGB8888 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB8888 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB8888 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB8888 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB8888 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB8888 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB8888 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB8888 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB8888 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb8888_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);
#endif

#ifdef AIPL_CONVERT_ARGB4444
/**
 * Convert ARGB4444 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format);

/**
 * Convert ARGB4444 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);


/**
 * Convert ARGB4444 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB4444 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB4444 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB4444 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB4444 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB4444 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert ARGB4444 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert ARGB4444 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB4444 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB4444 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB4444 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB4444 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB4444 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB4444 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB4444 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB4444 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb4444_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);
#endif

#ifdef AIPL_CONVERT_ARGB1555
/**
 * Convert ARGB1555 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format);

/**
 * Convert ARGB1555 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);


/**
 * Convert ARGB1555 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB1555 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB1555 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB1555 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB1555 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert ARGB1555 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert ARGB1555 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert ARGB1555 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB1555 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB1555 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB1555 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB1555 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB1555 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB1555 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB1555 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert ARGB1555 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_argb1555_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);
#endif

#ifdef AIPL_CONVERT_RGBA8888
/**
 * Convert RGBA8888 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format);

/**
 * Convert RGBA8888 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);


/**
 * Convert RGBA8888 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA8888 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA8888 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA8888 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA8888 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA8888 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGBA8888 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGBA8888 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA8888 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA8888 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA8888 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA8888 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA8888 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA8888 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA8888 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA8888 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba8888_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);
#endif

#ifdef AIPL_CONVERT_RGBA4444
/**
 * Convert RGBA4444 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format);


/**
 * Convert RGBA4444 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);


/**
 * Convert RGBA4444 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA4444 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA4444 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA4444 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA4444 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA4444 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGBA4444 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGBA4444 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA4444 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA4444 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA4444 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA4444 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA4444 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA4444 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA4444 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA4444 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba4444_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);
#endif

#ifdef AIPL_CONVERT_RGBA5551
/**
 * Convert RGBA5551 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format);


/**
 * Convert RGBA5551 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);


/**
 * Convert RGBA5551 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA5551 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA5551 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA5551 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA5551 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height);

/**
 * Convert RGBA5551 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGBA5551 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGBA5551 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA5551 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA5551 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA5551 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA5551 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA5551 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA5551 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA5551 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGBA5551 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgba5551_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);
#endif

#ifdef AIPL_CONVERT_RGB888
/**
 * Convert RGB888 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888(const void* input, void* output,
                                       uint32_t pitch,
                                       uint32_t width, uint32_t height,
                                       aipl_color_format_t format);


/**
 * Convert RGB888 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_alpha8(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);


/**
 * Convert RGB888 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_argb8888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB888 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_argb4444(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB888 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_argb1555(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB888 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_rgba8888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB888 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_rgba4444(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB888 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_rgba5551(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB888 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_rgb565(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGB888 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_yv12(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB888 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_i420(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB888 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_i422(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB888 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_i444(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB888 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_i400(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB888 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_nv21(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB888 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_nv12(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB888 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_yuy2(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB888 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb888_to_uyvy(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);
#endif

#ifdef AIPL_CONVERT_RGB565
/**
 * Convert RGB565 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565(const void* input, void* output,
                                       uint32_t pitch,
                                       uint32_t width, uint32_t height,
                                       aipl_color_format_t format);


/**
 * Convert RGB565 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_alpha8(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);


/**
 * Convert RGB565 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_argb8888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB565 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_argb4444(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB565 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_argb1555(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB565 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_rgba8888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB565 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_rgba4444(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB565 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_rgba5551(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height);

/**
 * Convert RGB565 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_rgb888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert RGB565 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_yv12(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB565 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_i420(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB565 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_i422(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB565 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_i444(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB565 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_i400(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB565 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_nv21(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB565 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_nv12(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB565 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_yuy2(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert RGB565 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_rgb565_to_uyvy(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);
#endif

#ifdef AIPL_CONVERT_YV12
/**
 * Convert YV12 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format);


/**
 * Convert YV12 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);


/**
 * Convert YV12 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YV12 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YV12 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YV12 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YV12 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YV12 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YV12 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert YV12 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert YV12 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YV12 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YV12 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YV12 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YV12 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YV12 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YV12 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YV12 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yv12_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);
#endif

#ifdef AIPL_CONVERT_I420
/**
 * Convert I420 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_i420(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format);


/**
 * Convert I420 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);


/**
 * Convert I420 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I420 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I420 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I420 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I420 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I420 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I420 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert I420 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert I420 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I420 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I420 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I420 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I420 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I420 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I420 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I420 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i420_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);
#endif

#ifdef AIPL_CONVERT_I422
/**
 * Convert I422 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_i422(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format);


/**
 * Convert I422 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);


/**
 * Convert I422 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I422 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I422 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I422 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I422 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I422 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I422 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert I422 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert I422 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I422 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I422 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I422 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I422 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I422 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I422 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I422 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i422_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);
#endif

#ifdef AIPL_CONVERT_I444
/**
 * Convert I444 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_i444(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format);


/**
 * Convert I444 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);


/**
 * Convert I444 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I444 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I444 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I444 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I444 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I444 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I444 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert I444 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert I444 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I444 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I444 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I444 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I444 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I444 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I444 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I444 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i444_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);
#endif

#ifdef AIPL_CONVERT_NV12
/**
 * Convert NV12 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format);


/**
 * Convert NV12 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);


/**
 * Convert NV12 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV12 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV12 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV12 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV12 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV12 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV12 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert NV12 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert NV12 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV12 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV12 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV12 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV12 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV12 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV12 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV12 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv12_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);
#endif

#ifdef AIPL_CONVERT_NV21
/**
 * Convert NV21 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format);


/**
 * Convert NV21 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);


/**
 * Convert NV21 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV21 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV21 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV21 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV21 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV21 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert NV21 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert NV21 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert NV21 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV21 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV21 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV21 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV21 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV21 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV21 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert NV21 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_nv21_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);
#endif

#ifdef AIPL_CONVERT_YUY2
/**
 * Convert YUY2 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format);


/**
 * Convert YUY2 image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);


/**
 * Convert YUY2 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YUY2 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YUY2 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YUY2 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YUY2 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YUY2 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert YUY2 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert YUY2 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert YUY2 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YUY2 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YUY2 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YUY2 image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YUY2 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YUY2 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YUY2 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert YUY2 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_yuy2_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);
#endif

#ifdef AIPL_CONVERT_UYVY
/**
 * Convert UYVY image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format);


/**
 * Convert UYVY image to ALPHA8
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);


/**
 * Convert UYVY image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert UYVY image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert UYVY image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert UYVY image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert UYVY image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert UYVY image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert UYVY image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert UYVY image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert UYVY image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert UYVY image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert UYVY image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert UYVY image to I400
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert UYVY image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert UYVY image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert UYVY image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert UYVY image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_uyvy_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);
#endif

#ifdef AIPL_CONVERT_I400
/**
 * Convert I400 image to specified format
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @param format        desired color format
 * @return error code
 */
aipl_error_t aipl_color_convert_i400(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format);

/**
 * Convert I400 image to ARGB8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I400 image to ARGB4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I400 image to ARGB1555
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I400 image to RGBA8888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I400 image to RGBA4444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I400 image to RGBA5551
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height);

/**
 * Convert I400 image to RGB888
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert I400 image to RGB565
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height);

/**
 * Convert I400 image to YV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I400 image to I420
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I400 image to I422
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I400 image to I444
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I400 image to NV12
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I400 image to NV21
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I400 image to YUY2
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

/**
 * Convert I400 image to UYVY
 *
 * @param input         input image pointer
 * @param output        output image pointer
 * @param pitch         input image pitch
 * @param width         image width
 * @param height        image height
 * @return error code
 */
aipl_error_t aipl_color_convert_i400_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height);

#endif

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  /* AIPL_COLOR_CONVERSION_H
 */
