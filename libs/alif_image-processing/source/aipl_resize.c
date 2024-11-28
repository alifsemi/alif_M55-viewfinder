/**
 * @file aipl_resize.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "aipl_resize.h"
#include <RTE_Device.h>
#include "aipl_config.h"
#if AIPL_USE_DAVE2D
#include "aipl_dave2d.h"
#endif
#if AIPL_USE_MVE
#include <arm_mve.h>
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static aipl_error_t aipl_resize_rgb888(const void* input, void* output,
                                       int input_width, int input_height,
                                       int output_width, int output_height);

static aipl_error_t aipl_resize_rgb565(const void* input, void* output,
                                       int input_width, int input_height,
                                       int output_width, int output_height);

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
aipl_error_t aipl_resize(const void* input, void* output,
                         uint32_t pitch,
                         uint32_t width, uint32_t height,
                         aipl_color_format_t format,
                         uint32_t output_width, uint32_t output_height,
                         bool interpolate)
{
#if AIPL_USE_DAVE2D
    if (aipl_dave2d_format_supported(format))
    {
        d2_u32 ret = aipl_dave2d_texturing(input, output,
                                           pitch,
                                           width, height,
                                           aipl_dave2d_format_to_mode(format),
                                           output_width, output_height,
                                           0,
                                           false, false,
                                           interpolate);

        return aipl_dave2d_error_convert(ret);
    }
#endif

    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return AIPL_UNSUPPORTED_FORMAT;
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_RGBA8888:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_ARGB4444:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_ARGB1555:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_RGBA4444:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_RGBA5551:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_RGB565:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_RGB888:
            return aipl_resize_rgb888(input, output,
                                      width, height,
                                      output_width, output_height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_I420:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_NV12:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_NV21:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_I422:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_YUY2:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_UYVY:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_I444:
            return AIPL_UNSUPPORTED_FORMAT;
        case AIPL_COLOR_I400:
            return AIPL_UNSUPPORTED_FORMAT;

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }

}

aipl_error_t aipl_resize_img(const aipl_image_t* input,
                             aipl_image_t* output,
                             bool interpolate)
{
    if (output->format != input->format) 
    { 
        return AIPL_FORMAT_MISMATCH;
    }

    return aipl_resize(input->data, output->data,
                       input->pitch,
                       input->width, input->height,
                       input->format,
                       output->width, output->height,
                       interpolate);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static aipl_error_t aipl_resize_rgb888(const void* input, void* output,
                                       int srcWidth, int srcHeight,
                                       int dstWidth, int dstHeight)
{
    const bool swapRB = false;
    const uint32_t pixel_size_B = aipl_color_format_depth(AIPL_COLOR_RGB888)/8;

    const uint8_t* srcImage = (const uint8_t*)input;
    uint8_t* dstImage = (uint8_t*)output;

#if AIPL_USE_MVE & 1
    const uint32x4_t rgb_offset = {0,1,2,3};
    const uint32x4_t bgr_offset = {2,1,0,3};
    const uint32x4_t output_offset = swapRB ? bgr_offset : rgb_offset;
#endif

// Copied from ei_camera.cpp in firmware-eta-compute
// Modified for RGB888
// This needs to be < 16 or it won't fit. Cortex-M4 only has SIMD for signed multiplies
#define FRAC_BITS 14
    const int FRAC_VAL = (1 << FRAC_BITS);
    const int FRAC_MASK = (FRAC_VAL - 1);

    uint32_t src_x_accum, src_y_accum; // accumulators and fractions for scaling the image
    uint32_t x_frac, nx_frac, y_frac, ny_frac;
    int x, y, ty;

    if (srcHeight < 2) {
        return AIPL_FRAME_OUT_OF_RANGE;
    }

    // start at 1/2 pixel in to account for integer downsampling which might miss pixels
    src_y_accum = FRAC_VAL / 2;
    const uint32_t src_x_frac = (srcWidth * FRAC_VAL) / dstWidth;
    const uint32_t src_y_frac = (srcHeight * FRAC_VAL) / dstHeight;

    //from here out, *3 b/c RGB
    srcWidth *= pixel_size_B;
    //srcHeight not used for indexing
    //dstWidth still needed as is
    //dstHeight shouldn't be scaled

    const uint8_t *s;
    uint8_t *d;

    for (y = 0; y < dstHeight; y++) {
        // do indexing computations
        ty = src_y_accum >> FRAC_BITS; // src y
        y_frac = src_y_accum & FRAC_MASK;
        src_y_accum += src_y_frac;
        ny_frac = FRAC_VAL - y_frac; // y fraction and 1.0 - y fraction

        s = &srcImage[ty * srcWidth];
        d = &dstImage[y * dstWidth * pixel_size_B]; //not scaled above
        // start at 1/2 pixel in to account for integer downsampling which might miss pixels
        src_x_accum = FRAC_VAL / 2;
        for (x = 0; x < dstWidth; x++) {
            uint32_t tx;
            // do indexing computations
            tx = (src_x_accum >> FRAC_BITS) * pixel_size_B;
            x_frac = src_x_accum & FRAC_MASK;
            nx_frac = FRAC_VAL - x_frac; // x fraction and 1.0 - x fraction
            src_x_accum += src_x_frac;
            __builtin_prefetch(&s[tx + 64]);
            __builtin_prefetch(&s[tx + srcWidth + 64]);

#if AIPL_USE_MVE & 1
            uint32x4_t p00 = vldrbq_u32(&s[tx]);
            uint32x4_t p10 = vldrbq_u32(&s[tx + pixel_size_B]);
            uint32x4_t p01 = vldrbq_u32(&s[tx + srcWidth]);
            uint32x4_t p11 = vldrbq_u32(&s[tx + srcWidth + pixel_size_B]);
            p00 = vmulq(p00, nx_frac);
            p00 = vmlaq(p00, p10, x_frac);
            p00 = vrshrq(p00, FRAC_BITS);
            p01 = vmulq(p01, nx_frac);
            p01 = vmlaq(p01, p11, x_frac);
            p01 = vrshrq(p01, FRAC_BITS);
            p00 = vmulq(p00, ny_frac);
            p00 = vmlaq(p00, p01, y_frac);
            p00 = vrshrq(p00, FRAC_BITS);
            vstrbq_scatter_offset_p_u32(d, output_offset, p00, vctp32q(pixel_size_B));

            d += pixel_size_B;
#else
            //interpolate and write out
            if (swapRB) {
                for (int color = 0; color < pixel_size_B;
                    color++) // do pixel_size_B times for pixel_size_B colors
                {
                    uint32_t p00, p01, p10, p11;
                    p00 = s[tx];
                    p10 = s[tx + pixel_size_B];
                    p01 = s[tx + srcWidth];
                    p11 = s[tx + srcWidth + pixel_size_B];
                    p00 = ((p00 * nx_frac) + (p10 * x_frac) + FRAC_VAL / 2) >> FRAC_BITS; // top line
                    p01 = ((p01 * nx_frac) + (p11 * x_frac) + FRAC_VAL / 2) >> FRAC_BITS; // bottom line
                    p00 = ((p00 * ny_frac) + (p01 * y_frac) + FRAC_VAL / 2) >> FRAC_BITS; //top + bottom
                    d[pixel_size_B - color -1] = (uint8_t)p00; // store new pixel
                    //ready next loop
                    tx++;
                }
                d += 3;
            } else {
                for (int color = 0; color < pixel_size_B;
                    color++) // do pixel_size_B times for pixel_size_B colors
                {
                    uint32_t p00, p01, p10, p11;
                    p00 = s[tx];
                    p10 = s[tx + pixel_size_B];
                    p01 = s[tx + srcWidth];
                    p11 = s[tx + srcWidth + pixel_size_B];
                    p00 = ((p00 * nx_frac) + (p10 * x_frac) + FRAC_VAL / 2) >> FRAC_BITS; // top line
                    p01 = ((p01 * nx_frac) + (p11 * x_frac) + FRAC_VAL / 2) >> FRAC_BITS; // bottom line
                    p00 = ((p00 * ny_frac) + (p01 * y_frac) + FRAC_VAL / 2) >> FRAC_BITS; //top + bottom
                    *d++ = (uint8_t)p00; // store new pixel
                    //ready next loop
                    tx++;
                }
            }
#endif
        } // for x
    } // for y
    return AIPL_OK;
} // resizeImage()

