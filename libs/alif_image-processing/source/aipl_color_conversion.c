/**
 * @file aipl_color_conversion.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "aipl_color_conversion.h"
#include <RTE_Device.h>
#include "aipl_config.h"
#if AIPL_USE_DAVE2D
#include "aipl_dave2d.h"
#endif
#include <string.h>
#if AIPL_USE_MVE
#include "aipl_mve_utils.h"
#else
#include "aipl_utils.h"
#endif

/*********************
 *      DEFINES
 *********************/
#define LUM_R 0.299f
#define LUM_G 0.587f
#define LUM_B 0.114f

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
aipl_error_t aipl_color_convert(const void* input, void* output,
                                uint32_t pitch,
                                uint32_t width, uint32_t height,
                                aipl_color_format_t input_format,
                                aipl_color_format_t output_format)
{
#if AIPL_USE_DAVE2D
    /* TODO: figure out what's wrong with ARGB1555, RGBA5551 and ALPHA8 */
    if (aipl_dave2d_format_supported(input_format)
        && aipl_dave2d_format_supported(output_format)
        && output_format != AIPL_COLOR_ARGB1555
        && output_format != AIPL_COLOR_RGBA5551
        && output_format != AIPL_COLOR_ALPHA8)
    {
        d2_s32 ret =
            aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                           aipl_dave2d_format_to_mode(input_format),
                                           aipl_dave2d_format_to_mode(output_format));

        return aipl_dave2d_error_convert(ret);
    }
#endif

    switch (input_format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
#ifdef AIPL_CONVERT_I400
            return aipl_color_convert_i400(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif

        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
#ifdef AIPL_CONVERT_ARGB8888
            return aipl_color_convert_argb8888(input, output, pitch,
                                               width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_RGBA8888:
#ifdef AIPL_CONVERT_RGBA8888
            return aipl_color_convert_rgba8888(input, output, pitch,
                                               width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_ARGB4444:
#ifdef AIPL_CONVERT_ARGB4444
            return aipl_color_convert_argb4444(input, output, pitch,
                                               width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_ARGB1555:
#ifdef AIPL_CONVERT_ARGB1555
            return aipl_color_convert_argb1555(input, output, pitch,
                                               width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_RGBA4444:
#ifdef AIPL_CONVERT_RGBA4444
            return aipl_color_convert_rgba4444(input, output, pitch,
                                               width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_RGBA5551:
#ifdef AIPL_CONVERT_RGBA5551
            return aipl_color_convert_rgba5551(input, output, pitch,
                                               width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_RGB565:
#ifdef AIPL_CONVERT_RGB565
            return aipl_color_convert_rgb565(input, output, pitch,
                                             width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_RGB888:
#ifdef AIPL_CONVERT_RGB888
            return aipl_color_convert_rgb888(input, output, pitch,
                                             width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif

        /* YUV color formats */
        case AIPL_COLOR_YV12:
#ifdef AIPL_CONVERT_YV12
            return aipl_color_convert_yv12(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_I420:
#ifdef AIPL_CONVERT_I420
            return aipl_color_convert_i420(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_NV12:
#ifdef AIPL_CONVERT_NV12
            return aipl_color_convert_nv12(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_NV21:
#ifdef AIPL_CONVERT_NV21
            return aipl_color_convert_nv21(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_I422:
#ifdef AIPL_CONVERT_I422
            return aipl_color_convert_i422(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_YUY2:
#ifdef AIPL_CONVERT_YUY2
            return aipl_color_convert_yuy2(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_UYVY:
#ifdef AIPL_CONVERT_UYVY
            return aipl_color_convert_uyvy(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_I444:
#ifdef AIPL_CONVERT_I444
            return aipl_color_convert_i444(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif
        case AIPL_COLOR_I400:
#ifdef AIPL_CONVERT_I400
            return aipl_color_convert_i400(input, output, pitch,
                                           width, height, output_format);
#else
            return AIPL_UNSUPPORTED_FORMAT;
#endif

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }

}

aipl_error_t aipl_color_convert_img(const aipl_image_t* input,
                                    aipl_image_t* output)
{
    if (input->width != output->width || input->height != output->height)
    {
        return AIPL_SIZE_MISMATCH;
    }

    return aipl_color_convert(input->data, output->data, input->pitch,
                              input->width, input->height,
                              input->format, output->format);
}

#ifdef AIPL_CONVERT_ARGB8888
aipl_error_t aipl_color_convert_argb8888(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_argb8888_to_alpha8(input, output,
                                                         pitch,
                                                         width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_argb8888_to_rgba8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_argb8888_to_argb4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_argb8888_to_argb1555(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_argb8888_to_rgba4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_argb8888_to_rgba5551(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_argb8888_to_rgb565(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_argb8888_to_rgb888(input, output,
                                                         pitch,
                                                         width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_argb8888_to_yv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_argb8888_to_i420(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_argb8888_to_nv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_argb8888_to_nv21(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_argb8888_to_i422(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_argb8888_to_yuy2(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_argb8888_to_uyvy(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_argb8888_to_i444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_argb8888_to_i400(input, output,
                                                       pitch,
                                                       width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_argb8888_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_argb8888, d2_mode_alpha8);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb8888_16px(&pix, src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_argb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_packa_yuv_y(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_argb8888_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb8888, d2_mode_argb4444);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb8888_16px(&pix, src, tail_p);

            aipl_mve_storea_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_packa_argb4444_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb8888_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_argb8888, d2_mode_argb1555);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb8888_16px(&pix, src, tail_p);

            aipl_mve_storea_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_packa_argb1555_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_argb8888_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb8888, d2_mode_rgba8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb8888_16px(&pix, src, tail_p);

            aipl_mve_storea_rgba8888_16px(dst, &pix, tail_p);

            src += 64;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->r = src->r;
            dst->g = src->g;
            dst->b = src->b;
            dst->a = src->a;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb8888_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb8888, d2_mode_rgba4444);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb8888_16px(&pix, src, tail_p);

            aipl_mve_storea_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_packa_rgba4444_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb8888_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_argb8888, d2_mode_rgba5551);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb8888_16px(&pix, src, tail_p);

            aipl_mve_storea_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_packa_rgba5551_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_argb8888_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_16px(&pix, src, tail_p);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            src += 64;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->r = src->r;
            dst->g = src->g;
            dst->b = src->b;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb8888_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb8888, d2_mode_rgb565);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_16px(&pix, src, tail_p);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_packa_rgb565_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb8888_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb8888_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb8888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_packa_yuv_y(y_dst0++, src0);
            aipl_packa_yuv_u(u_dst++, src0);
            aipl_packa_yuv_v(v_dst++, src0++);

            aipl_packa_yuv_y(y_dst0++, src0++);

            aipl_packa_yuv_y(y_dst1++, src1++);

            aipl_packa_yuv_y(y_dst1++, src1++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb8888_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb8888_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb8888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_packa_yuv_y(y_dst0++, src0);
            aipl_packa_yuv_u(u_dst++, src0);
            aipl_packa_yuv_v(v_dst++, src0++);

            aipl_packa_yuv_y(y_dst0++, src0++);

            aipl_packa_yuv_y(y_dst1++, src1++);

            aipl_packa_yuv_y(y_dst1++, src1++);
         }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb8888_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_p(u_dst, u, tail_p);
                u_dst += 16;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_p(v_dst, v, tail_p);
                v_dst += 16;
            }
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_packa_yuv_y(y_dst++, src);
            aipl_packa_yuv_u(u_dst++, src);
            aipl_packa_yuv_v(v_dst++, src++);

            aipl_packa_yuv_y(y_dst++, src++);
       }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb8888_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    const uint16x8_t input_pixel_offsets = vmulq_n_u16(vidupq_n_u16(0, 1), 4);

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_16px(&pix, src, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_p(y_dst, y, tail_p);

            uint8x16_t u;
            aipl_mve_calculate_u_rgb_x16(&u, &pix);

            vstrbq_p(u_dst, u, tail_p);

            uint8x16_t v;
            aipl_mve_calculate_v_rgb_x16(&v, &pix);

            vstrbq_p(v_dst, v, tail_p);

            src += 64;
            y_dst += 16;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_packa_yuv_y(y_dst++, src);
            aipl_packa_yuv_u(u_dst++, src);
            aipl_packa_yuv_v(v_dst++, src++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb8888_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_dst = output;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_16px(&pix, src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_packa_yuv_y(y_dst++, src++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb8888_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb8888_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb8888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_packa_yuv_y(y_dst0++, src0);
            aipl_packa_yuv_u(u_dst, src0);
            aipl_packa_yuv_v(v_dst, src0++);
            u_dst += 2;
            v_dst += 2;

            aipl_packa_yuv_y(y_dst0++, src0++);

            aipl_packa_yuv_y(y_dst1++, src1++);

            aipl_packa_yuv_y(y_dst1++, src1++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb8888_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb8888_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb8888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_packa_yuv_y(y_dst0++, src0);
            aipl_packa_yuv_u(u_dst, src0);
            aipl_packa_yuv_v(v_dst, src0++);
            u_dst += 2;
            v_dst += 2;

            aipl_packa_yuv_y(y_dst0++, src0++);

            aipl_packa_yuv_y(y_dst1++, src1++);

            aipl_packa_yuv_y(y_dst1++, src1++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb8888_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + 1;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                src += 4;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_packa_yuv_y(y_dst, src);
            aipl_packa_yuv_u(u_dst, src);
            aipl_packa_yuv_v(v_dst, src++);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_packa_yuv_y(y_dst, src++);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb8888_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output + 1;
    uint8_t* u_ptr = output;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                src += 4;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_packa_yuv_y(y_dst, src);
            aipl_packa_yuv_u(u_dst, src);
            aipl_packa_yuv_v(v_dst, src++);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_packa_yuv_y(y_dst, src++);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_ARGB4444
aipl_error_t aipl_color_convert_argb4444(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_argb4444_to_alpha8(input, output,
                                                         pitch,
                                                         width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_argb4444_to_argb8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_argb4444_to_rgba8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB4444:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_argb4444_to_argb1555(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_argb4444_to_rgba4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_argb4444_to_rgba5551(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_argb4444_to_rgb565(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_argb4444_to_rgb888(input, output,
                                                         pitch,
                                                         width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_argb4444_to_yv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_argb4444_to_i420(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_argb4444_to_nv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_argb4444_to_nv21(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_argb4444_to_i422(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_argb4444_to_yuy2(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_argb4444_to_uyvy(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_argb4444_to_i444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_argb4444_to_i400(input, output,
                                                       pitch,
                                                       width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_argb4444_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_argb4444, d2_mode_alpha8);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_argb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_argb4444_px(&px, src);
            aipl_packa_yuv_y(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_argb4444_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb4444, d2_mode_argb8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_loada_argb4444_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb4444_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_argb4444, d2_mode_argb1555);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = (src->ar & 0x80) | ((src->ar << 3) & 0x7c)
                     | (src->gb >> 6);
            dst->b = ((src->gb << 2) & 0xe0) | ((src->gb << 1) & 0x1f);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_argb4444_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb4444, d2_mode_rgba8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->r = src->ar << 4;
            dst->g = src->gb & 0xf0;
            dst->b = src->gb << 4;
            dst->a = src->ar & 0xf0;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb4444_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb4444, d2_mode_rgba4444);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->rg = (src->ar << 4) | (src->gb >> 4);
            dst->ba = (src->gb << 4) | (src->ar >> 4);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb4444_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_argb4444, d2_mode_rgba5551);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = (src->ar << 4) | (src->gb >> 5);
            dst->b = ((src->gb << 3) & 0x80) | ((src->gb << 2) & 0x3e)
                     | (src->ar >> 7);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_argb4444_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_load_argb4444_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb4444_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb4444, d2_mode_rgb565);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = (src->ar << 4) | (src->gb >> 5);
            dst->b = ((src->gb << 3) & 0x80) | ((src->gb << 1) & 0x1f);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb4444_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb4444_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb4444_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_argb4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_argb4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_argb4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb4444_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb4444_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb4444_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_argb4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_argb4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_argb4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
         }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb4444_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_p(u_dst, u, tail_p);
                u_dst += 16;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_p(v_dst, v, tail_p);
                v_dst += 16;
            }
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_argb4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
       }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb4444_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_p(y_dst, y, tail_p);

            uint8x16_t u;
            aipl_mve_calculate_u_rgb_x16(&u, &pix);

            vstrbq_p(u_dst, u, tail_p);

            uint8x16_t v;
            aipl_mve_calculate_v_rgb_x16(&v, &pix);

            vstrbq_p(v_dst, v, tail_p);

            src += 16;
            y_dst += 16;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb4444_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_dst = output;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb4444_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb4444_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb4444_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_argb4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_argb4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_argb4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb4444_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb4444_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb4444_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_argb4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_argb4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_argb4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb4444_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + 1;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_argb4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb4444_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output + 1;
    uint8_t* u_ptr = output;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_argb4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_ARGB1555
aipl_error_t aipl_color_convert_argb1555(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_argb1555_to_alpha8(input, output,
                                                         pitch,
                                                         width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_argb1555_to_argb8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_argb1555_to_rgba8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_argb1555_to_argb4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB1555:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_argb1555_to_rgba4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_argb1555_to_rgba5551(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_argb1555_to_rgb565(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_argb1555_to_rgb888(input, output,
                                                         pitch,
                                                         width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_argb1555_to_yv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_argb1555_to_i420(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_argb1555_to_nv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_argb1555_to_nv21(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_argb1555_to_i422(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_argb1555_to_yuy2(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_argb1555_to_uyvy(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_argb1555_to_i444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_argb1555_to_i400(input, output,
                                                       pitch,
                                                       width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_argb1555_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_argb1555, d2_mode_alpha8);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_argb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_argb1555_px(&px, src);
            aipl_packa_yuv_y(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_argb1555_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb1555, d2_mode_argb8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_loada_argb1555_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb1555_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_argb1555, d2_mode_argb4444);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->ar = ((src->t >> 7) * 0xf0) | ((src->t >> 3) & 0x0f);
            dst->gb = (src->t << 6) | ((src->b >> 2) & 0x30)
                      | ((src->b >> 1) & 0x0f);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_argb1555_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb1555, d2_mode_rgba8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->r = (src->t << 1) & 0xf8;
            dst->g = (src->t << 6) | ((src->b >> 2) & 0x38);
            dst->b = src->b << 3;
            dst->a = (src->t >> 7) * 0xff;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb1555_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb1555, d2_mode_rgba4444);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->rg = ((src->t << 1) & 0xf0) | ((src->t << 2) & 0x0f)
                      | (src->b >> 6);
            dst->ba = ((src->b << 3) & 0xf0) | (src->t >> 7) * 0x0f;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb1555_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_argb1555, d2_mode_rgba5551);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->h = (src->h << 1) | (src->h >> 15);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_argb1555_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_load_argb1555_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb1555_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_argb1555, d2_mode_rgb565);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = (src->t << 1) | (src->b >> 7);
            dst->b = ((src->b << 1) & 0xe0) | (src->b & 0x1f);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_argb1555_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb1555_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb1555_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb1555_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_argb1555_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_argb1555_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_argb1555_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb1555_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb1555_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb1555_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb1555_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_argb1555_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_argb1555_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_argb1555_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
         }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb1555_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_p(u_dst, u, tail_p);
                u_dst += 16;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_p(v_dst, v, tail_p);
                v_dst += 16;
            }
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb1555_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_argb1555_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
       }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb1555_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_p(y_dst, y, tail_p);

            uint8x16_t u;
            aipl_mve_calculate_u_rgb_x16(&u, &pix);

            vstrbq_p(u_dst, u, tail_p);

            uint8x16_t v;
            aipl_mve_calculate_v_rgb_x16(&v, &pix);

            vstrbq_p(v_dst, v, tail_p);

            src += 16;
            y_dst += 16;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb1555_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb1555_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_dst = output;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb1555_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb1555_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb1555_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb1555_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb1555_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_argb1555_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_argb1555_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_argb1555_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb1555_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_argb1555_px_t* src0 = src_ptr + i * pitch;
        const aipl_argb1555_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb1555_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_argb1555_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_argb1555_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_argb1555_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb1555_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + 1;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb1555_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_argb1555_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_argb1555_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output + 1;
    uint8_t* u_ptr = output;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_argb1555_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_argb1555_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_argb1555_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_RGBA8888
aipl_error_t aipl_color_convert_rgba8888(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_rgba8888_to_alpha8(input, output,
                                                         pitch,
                                                         width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_rgba8888_to_argb8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA8888:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_rgba8888_to_argb4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_rgba8888_to_argb1555(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_rgba8888_to_rgba4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_rgba8888_to_rgba5551(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_rgba8888_to_rgb565(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_rgba8888_to_rgb888(input, output,
                                                         pitch,
                                                         width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_rgba8888_to_yv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_rgba8888_to_i420(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_rgba8888_to_nv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_rgba8888_to_nv21(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_rgba8888_to_i422(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_rgba8888_to_yuy2(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_rgba8888_to_uyvy(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_rgba8888_to_i444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_rgba8888_to_i400(input, output,
                                                       pitch,
                                                       width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_rgba8888_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgba8888, d2_mode_alpha8);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba8888_16px(&pix, src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_argb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_rgba8888_px(&px, src);
            aipl_packa_yuv_y(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgba8888_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba8888, d2_mode_argb8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba8888_16px(&pix, src, tail_p);

            aipl_mve_storea_argb8888_16px(dst, &pix, tail_p);

            src += 64;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_loada_rgba8888_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba8888_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba8888, d2_mode_argb4444);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba8888_16px(&pix, src, tail_p);

            aipl_mve_storea_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->ar = (src->a & 0xf0) | (src->r >> 4);
            dst->gb = (src->g & 0xf0) | (src->b >> 4);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba8888_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgba8888, d2_mode_rgba8888);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba8888_16px(&pix, src, tail_p);

            aipl_mve_storea_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->h = ((uint16_t)(src->a & 0x80) << 8)
                     | ((uint16_t)(src->r & 0xf8) << 7)
                     | ((uint16_t)(src->g & 0xf8) << 2)
                     | (src->b >> 3);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgba8888_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba8888, d2_mode_rgba4444);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba8888_16px(&pix, src, tail_p);

            aipl_mve_storea_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->rg = (src->r & 0xf0) | (src->g >> 4);
            dst->ba = (src->b & 0xf0) | (src->a >> 4);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba8888_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgba8888, d2_mode_rgba5551);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba8888_16px(&pix, src, tail_p);

            aipl_mve_storea_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->h = ((uint16_t)(src->r & 0xf8) << 8)
                     | ((uint16_t)(src->g & 0xf8) << 3)
                     | ((src->b & 0xf8) >> 2)
                     | (src->a >> 7);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgba8888_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_16px(&pix, src, tail_p);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            src += 64;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->r = src->r;
            dst->g = src->g;
            dst->b = src->b;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba8888_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba8888, d2_mode_rgb565);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_16px(&pix, src, tail_p);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->h = ((uint16_t)(src->r & 0xf8) << 8)
                     | ((uint16_t)(src->g & 0xfc) << 3)
                     | (src->b >> 3);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba8888_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba8888_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba8888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba8888_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgba8888_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba8888_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba8888_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba8888_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba8888_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba8888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba8888_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgba8888_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba8888_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba8888_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
         }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba8888_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_p(u_dst, u, tail_p);
                u_dst += 16;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_p(v_dst, v, tail_p);
                v_dst += 16;
            }
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba8888_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgba8888_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
       }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba8888_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_16px(&pix, src, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_p(y_dst, y, tail_p);

            uint8x16_t u;
            aipl_mve_calculate_u_rgb_x16(&u, &pix);

            vstrbq_p(u_dst, u, tail_p);

            uint8x16_t v;
            aipl_mve_calculate_v_rgb_x16(&v, &pix);

            vstrbq_p(v_dst, v, tail_p);

            src += 64;
            y_dst += 16;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba8888_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba8888_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_dst = output;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 4;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_16px(&pix, src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 64;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba8888_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba8888_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba8888_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba8888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba8888_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_rgba8888_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba8888_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba8888_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba8888_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 4;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba8888_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba8888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba8888_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_rgba8888_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba8888_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba8888_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba8888_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + 1;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                src += 4;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba8888_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_rgba8888_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba8888_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output + 1;
    uint8_t* u_ptr = output;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 4;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba8888_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 124;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                src += 4;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba8888_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_rgba8888_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_RGBA4444
aipl_error_t aipl_color_convert_rgba4444(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_rgba4444_to_alpha8(input, output,
                                                         pitch,
                                                         width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_rgba4444_to_argb8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_rgba4444_to_rgba8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_rgba4444_to_argb4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_rgba4444_to_argb1555(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA4444:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_rgba4444_to_rgba5551(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_rgba4444_to_rgb565(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_rgba4444_to_rgb888(input, output,
                                                         pitch,
                                                         width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_rgba4444_to_yv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_rgba4444_to_i420(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_rgba4444_to_nv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_rgba4444_to_nv21(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_rgba4444_to_i422(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_rgba4444_to_yuy2(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_rgba4444_to_uyvy(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_rgba4444_to_i444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_rgba4444_to_i400(input, output,
                                                       pitch,
                                                       width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_rgba4444_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgba4444, d2_mode_alpha8);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_argb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_rgba4444_px(&px, src);
            aipl_packa_yuv_y(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgba4444_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba4444, d2_mode_argb8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_loada_rgba4444_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba4444_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgba4444, d2_mode_argb1555);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = ((src->ba << 4) & 0x80) | ((src->rg >> 1) & 0x78)
                     | ((src->rg >> 2) & 0x03);
            dst->b = (src->rg << 6) | (src->ba >> 3) | 0x01;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgba4444_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba4444, d2_mode_rgba8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->ar = (src->rg >> 4) | (src->ba << 4);
            dst->gb = (src->rg << 4) | (src->ba >> 4);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba4444_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba4444, d2_mode_rgba4444);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->r = src->rg & 0xf0;
            dst->g = src->rg << 4;
            dst->b = src->ba & 0xf0;
            dst->a = src->ba << 4;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba4444_to_rgba5551(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgba4444, d2_mode_rgba5551);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = (src->rg & 0xf0) | ((src->rg >> 1) & 0x07);
            dst->b = (src->rg << 7) | ((src->ba >> 2) & 0x38)
                     | ((src->ba >> 3) & 0x01);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgba4444_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_load_rgba4444_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba4444_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba4444, d2_mode_rgb565);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = (src->rg & 0xf0) | ((src->rg >> 1) & 0x07);
            dst->b = (src->rg << 7) | ((src->ba >> 3) & 0x1f) | 0x01;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba4444_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba4444_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba4444_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgba4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba4444_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba4444_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba4444_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgba4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
         }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba4444_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_p(u_dst, u, tail_p);
                u_dst += 16;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_p(v_dst, v, tail_p);
                v_dst += 16;
            }
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgba4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
       }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba4444_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_p(y_dst, y, tail_p);

            uint8x16_t u;
            aipl_mve_calculate_u_rgb_x16(&u, &pix);

            vstrbq_p(u_dst, u, tail_p);

            uint8x16_t v;
            aipl_mve_calculate_v_rgb_x16(&v, &pix);

            vstrbq_p(v_dst, v, tail_p);

            src += 16;
            y_dst += 16;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba4444_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_dst = output;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba4444_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba4444_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba4444_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_rgba4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba4444_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba4444_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba4444_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_rgba4444_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba4444_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba4444_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + 1;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_rgba4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba4444_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output + 1;
    uint8_t* u_ptr = output;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba4444_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_rgba4444_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_RGBA5551
aipl_error_t aipl_color_convert_rgba5551(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_rgba5551_to_alpha8(input, output,
                                                         pitch,
                                                         width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_rgba5551_to_argb8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_rgba5551_to_rgba8888(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_rgba5551_to_argb4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_rgba5551_to_argb1555(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_rgba5551_to_rgba4444(input, output,
                                                           pitch,
                                                           width, height);
        case AIPL_COLOR_RGBA5551:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_rgba5551_to_rgb565(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_rgba5551_to_rgb888(input, output,
                                                         pitch,
                                                         width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_rgba5551_to_yv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_rgba5551_to_i420(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_rgba5551_to_nv12(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_rgba5551_to_nv21(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_rgba5551_to_i422(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_rgba5551_to_yuy2(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_rgba5551_to_uyvy(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_rgba5551_to_i444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_rgba5551_to_i400(input, output,
                                                       pitch,
                                                       width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_rgba5551_to_alpha8(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgba5551, d2_mode_alpha8);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_argb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_rgba5551_px(&px, src);
            aipl_packa_yuv_y(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgba5551_to_argb8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba5551, d2_mode_argb8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_loada_rgba5551_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba5551_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgba5551, d2_mode_argb1555);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->h = (src->h >> 1) | (src->h << 15);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgba5551_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba5551, d2_mode_rgba8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->ar = ((src->b & 0x01) * 0xf0) | (src->t >> 4);
            dst->gb = (src->t << 5) | ((src->b >> 3) & 0x10) | ((src->b >> 2) & 0x0f);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba5551_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba5551, d2_mode_rgba5551);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->r = src->t & 0xf8;
            dst->g = (src->t << 5) | ((src->b >> 3) & 0x18);
            dst->b = (src->b << 2) & 0xf8;
            dst->a = (src->b & 0x01) * 0xff;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba5551_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba5551, d2_mode_rgba4444);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_storea_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->rg = (src->t & 0xf0) | ((src->t << 1) & 0x0f) | (src->b >> 7);
            dst->ba = ((src->b << 2) & 0xf0) | ((src->b & 0x01) * 0x0f);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba5551_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_load_rgba5551_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba5551_to_rgb565(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgba5551, d2_mode_rgb565);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = src->t;
            dst->b = (src->b & 0xc0) | ((src->b >> 1) & 0x1f);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgba5551_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba5551_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba5551_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba5551_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgba5551_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba5551_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba5551_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba5551_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba5551_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba5551_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba5551_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgba5551_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba5551_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba5551_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
         }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba5551_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_p(u_dst, u, tail_p);
                u_dst += 16;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_p(v_dst, v, tail_p);
                v_dst += 16;
            }
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba5551_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgba5551_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
       }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba5551_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_p(y_dst, y, tail_p);

            uint8x16_t u;
            aipl_mve_calculate_u_rgb_x16(&u, &pix);

            vstrbq_p(u_dst, u, tail_p);

            uint8x16_t v;
            aipl_mve_calculate_v_rgb_x16(&v, &pix);

            vstrbq_p(v_dst, v, tail_p);

            src += 16;
            y_dst += 16;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba5551_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba5551_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_dst = output;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba5551_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba5551_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba5551_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba5551_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba5551_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_rgba5551_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba5551_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba5551_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba5551_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgba5551_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgba5551_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba5551_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_rgba5551_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgba5551_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgba5551_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba5551_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + 1;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba5551_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_rgba5551_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgba5551_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output + 1;
    uint8_t* u_ptr = output;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgba5551_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgba5551_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_rgba5551_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_RGB888
aipl_error_t aipl_color_convert_rgb888(const void* input, void* output,
                                       uint32_t pitch,
                                       uint32_t width, uint32_t height,
                                       aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_rgb888_to_alpha8(input, output,
                                                       pitch,
                                                       width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_rgb888_to_argb8888(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_rgb888_to_rgba8888(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_rgb888_to_argb4444(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_rgb888_to_argb1555(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_rgb888_to_rgba4444(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_rgb888_to_rgba5551(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_rgb888_to_rgb565(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB888:
            return AIPL_FORMAT_MISMATCH;

        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_rgb888_to_yv12(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_rgb888_to_i420(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_rgb888_to_nv12(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_rgb888_to_nv21(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_rgb888_to_i422(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_rgb888_to_yuy2(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_rgb888_to_uyvy(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_rgb888_to_i444(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_rgb888_to_i400(input, output,
                                                     pitch,
                                                     width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_rgb888_to_alpha8(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 48;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_pack_yuv_y(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_argb8888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            aipl_mve_store_argb8888_16px(dst, &pix, tail_p);

            src += 48;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->a = 0xff;
            dst->r = src->r;
            dst->g = src->g;
            dst->b = src->b;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_argb1555(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            aipl_mve_store_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            src += 48;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_pack_argb1555_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_argb4444(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            aipl_mve_store_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 48;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_pack_argb4444_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_rgba8888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            aipl_mve_store_rgba8888_16px(dst, &pix, tail_p);

            src += 48;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->r = src->r;
            dst->g = src->g;
            dst->b = src->b;
            dst->a = 0xff;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_rgba4444(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            aipl_mve_store_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 48;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_pack_rgba4444_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_rgba5551(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            aipl_mve_store_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            src += 48;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_pack_rgba5551_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_rgb565(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

            src += 48;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_pack_rgb565_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_yv12(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 3;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 93;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 3;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgb888_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgb888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_pack_yuv_y(y_dst0++, src0);
            aipl_pack_yuv_u(u_dst++, src0);
            aipl_pack_yuv_v(v_dst++, src0++);

            aipl_pack_yuv_y(y_dst0++, src0++);

            aipl_pack_yuv_y(y_dst1++, src1++);

            aipl_pack_yuv_y(y_dst1++, src1++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_i420(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 3;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 93;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 3;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgb888_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgb888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_pack_yuv_y(y_dst0++, src0);
            aipl_pack_yuv_u(u_dst++, src0);
            aipl_pack_yuv_v(v_dst++, src0++);

            aipl_pack_yuv_y(y_dst0++, src0++);

            aipl_pack_yuv_y(y_dst1++, src1++);

            aipl_pack_yuv_y(y_dst1++, src1++);
         }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_i422(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 3;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 93;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 3;
                ++y_dst;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_p(u_dst, u, tail_p);
                u_dst += 16;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_p(v_dst, v, tail_p);
                v_dst += 16;
            }
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_pack_yuv_y(y_dst++, src);
            aipl_pack_yuv_u(u_dst++, src);
            aipl_pack_yuv_v(v_dst++, src++);

            aipl_pack_yuv_y(y_dst++, src++);
       }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_i444(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_p(y_dst, y, tail_p);

            uint8x16_t u;
            aipl_mve_calculate_u_rgb_x16(&u, &pix);

            vstrbq_p(u_dst, u, tail_p);

            uint8x16_t v;
            aipl_mve_calculate_v_rgb_x16(&v, &pix);

            vstrbq_p(v_dst, v, tail_p);

            src += 48;
            y_dst += 16;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_pack_yuv_y(y_dst++, src);
            aipl_pack_yuv_u(u_dst++, src);
            aipl_pack_yuv_v(v_dst++, src++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_i400(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_dst = output;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + i * pitch * 3;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 48;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_pack_yuv_y(y_dst++, src++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_nv21(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 3;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 93;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 3;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgb888_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgb888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_pack_yuv_y(y_dst0++, src0);
            aipl_pack_yuv_u(u_dst, src0);
            aipl_pack_yuv_v(v_dst, src0++);
            u_dst += 2;
            v_dst += 2;

            aipl_pack_yuv_y(y_dst0++, src0++);

            aipl_pack_yuv_y(y_dst1++, src1++);

            aipl_pack_yuv_y(y_dst1++, src1++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_nv12(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 3;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 93;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                src += 3;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgb888_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgb888_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_pack_yuv_y(y_dst0++, src0);
            aipl_pack_yuv_u(u_dst, src0);
            aipl_pack_yuv_v(v_dst, src0++);
            u_dst += 2;
            v_dst += 2;

            aipl_pack_yuv_y(y_dst0++, src0++);

            aipl_pack_yuv_y(y_dst1++, src1++);

            aipl_pack_yuv_y(y_dst1++, src1++);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_yuy2(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + 1;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 3;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 93;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                src += 3;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_pack_yuv_y(y_dst, src);
            aipl_pack_yuv_u(u_dst, src);
            aipl_pack_yuv_v(v_dst, src++);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_pack_yuv_y(y_dst, src++);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb888_to_uyvy(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output + 1;
    uint8_t* u_ptr = output;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint8_t* src = src_ptr + i * pitch * 3;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_offset_16px(&pix, src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 93;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                src += 3;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_pack_yuv_y(y_dst, src);
            aipl_pack_yuv_u(u_dst, src);
            aipl_pack_yuv_v(v_dst, src++);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_pack_yuv_y(y_dst, src++);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_RGB565
aipl_error_t aipl_color_convert_rgb565(const void* input, void* output,
                                       uint32_t pitch,
                                       uint32_t width, uint32_t height,
                                       aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_rgb565_to_alpha8(input, output,
                                                       pitch,
                                                       width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_rgb565_to_argb8888(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_rgb565_to_rgba8888(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_rgb565_to_argb4444(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_rgb565_to_argb1555(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_rgb565_to_rgba4444(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_rgb565_to_rgba5551(input, output,
                                                         pitch,
                                                         width, height);
        case AIPL_COLOR_RGB565:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_rgb565_to_rgb888(input, output,
                                                       pitch,
                                                       width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_rgb565_to_yv12(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_rgb565_to_i420(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_rgb565_to_nv12(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_rgb565_to_nv21(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_rgb565_to_i422(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_rgb565_to_yuy2(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_rgb565_to_uyvy(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_rgb565_to_i444(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_rgb565_to_i400(input, output,
                                                     pitch,
                                                     width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_rgb565_to_alpha8(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgb565, d2_mode_alpha8);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_rgb565_px(&px, src);
            aipl_packa_yuv_y(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgb565_to_argb8888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgb565, d2_mode_argb8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_argb8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_loada_rgb565_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgb565_to_argb1555(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgb565, d2_mode_argb1555);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = 0x80 | (src->t >> 1);
            dst->b = (src->t << 7) | ((src->b >> 1) & 0x60) | (src->b & 0x1f);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}

aipl_error_t aipl_color_convert_rgb565_to_argb4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgb565, d2_mode_rgba8888);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->ar = 0xf0 | (src->t >> 4);
            dst->gb = (src->t << 5) | ((src->b >> 3) & 0x10) | ((src->b >> 1) & 0x0f);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgb565_to_rgba8888(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgb565, d2_mode_rgb565);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgba8888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->r = src->t & 0xf8;
            dst->g = (src->h & 0x07e0) >> 3;
            dst->b = (src->b & 0x1f) << 3;
            dst->a = 0xff;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgb565_to_rgba4444(const void* input,
                                                     void* output,
                                                     uint32_t pitch,
                                                     uint32_t width,
                                                     uint32_t height)
{
#if AIPL_USE_DAVE2D
    d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
                                                d2_mode_rgb565, d2_mode_rgba4444);

    return aipl_dave2d_error_convert(ret);
#else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->rg = (src->t & 0xf0) | ((src->t << 1) & 0x0f) | (src->b >> 7);
            dst->ba = ((src->b << 3) & 0xf0) | 0x0f;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
#endif
}

aipl_error_t aipl_color_convert_rgb565_to_rgba5551(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
// #if AIPL_USE_DAVE2D
//     d2_s32 ret = aipl_dave2d_color_mode_convert(input, output, pitch, width, height,
//                                                 d2_mode_rgb565, d2_mode_rgb565);

//     return aipl_dave2d_error_convert(ret);
// #else
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            dst->t = src->t;
            dst->b = (src->b & 0xc0) | ((src->b << 1) & 0x3e) | 0x01;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
// #endif
}


aipl_error_t aipl_color_convert_rgb565_to_rgb888(const void* input,
                                                   void* output,
                                                   uint32_t pitch,
                                                   uint32_t width,
                                                   uint32_t height)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            src += 16;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_load_rgb565_px(dst, src);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb565_to_yv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgb565_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgb565_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgb565_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgb565_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgb565_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb565_to_i420(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_p(u_dst, u, tail_p);
                    u_dst += 16;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_p(v_dst, v, tail_p);
                    v_dst += 16;
                }
            }
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgb565_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgb565_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 4;
        uint8_t* u_dst = u_ptr + i * pitch / 4;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgb565_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgb565_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgb565_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
         }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb565_to_i422(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_p(u_dst, u, tail_p);
                u_dst += 16;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_p(v_dst, v, tail_p);
                v_dst += 16;
            }
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);

            aipl_load_rgb565_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
       }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb565_to_i444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_p(y_dst, y, tail_p);

            uint8x16_t u;
            aipl_mve_calculate_u_rgb_x16(&u, &pix);

            vstrbq_p(u_dst, u, tail_p);

            uint8x16_t v;
            aipl_mve_calculate_v_rgb_x16(&v, &pix);

            vstrbq_p(v_dst, v, tail_p);

            src += 16;
            y_dst += 16;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch;
        uint8_t* u_dst = u_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
            aipl_pack_yuv_u(u_dst++, &px);
            aipl_pack_yuv_v(v_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb565_to_i400(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_dst = output;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            uint8x16_t alpha;
            aipl_mve_calculate_y_rgb_x16(&alpha, &pix);

            aipl_mve_store_alpha8_16px(dst, &alpha, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src++);
            aipl_pack_yuv_y(y_dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb565_to_nv21(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* v_ptr = output + yuv_size;
    uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgb565_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgb565_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_rgb565_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgb565_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgb565_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb565_to_nv12(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + yuv_size;
    uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_2_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 31;
                cnt -= 16;
            }
            else
            {
                ++src;
                ++y_dst;

                if (!(i & 1))
                {
                    uint8x16_t u;
                    aipl_mve_calculate_u_rgb_x16(&u, &pix);

                    vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                    u_dst += 32;

                    uint8x16_t v;
                    aipl_mve_calculate_v_rgb_x16(&v, &pix);

                    vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                    v_dst += 32;
                }
            }
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const aipl_rgb565_px_t* src0 = src_ptr + i * pitch;
        const aipl_rgb565_px_t* src1 = src0 + pitch;

        uint8_t* y_dst0 = y_ptr + i * pitch;
        uint8_t* y_dst1 = y_dst0 + pitch;
        uint8_t* v_dst = v_ptr + i * pitch / 2;
        uint8_t* u_dst = u_ptr + i * pitch / 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            u_dst += 2;
            v_dst += 2;

            aipl_load_rgb565_px(&px, src0++);
            aipl_pack_yuv_y(y_dst0++, &px);

            aipl_load_rgb565_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);

            aipl_load_rgb565_px(&px, src1++);
            aipl_pack_yuv_y(y_dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb565_to_yuy2(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output;
    uint8_t* u_ptr = output + 1;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_rgb565_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_rgb565_to_uyvy(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = width * height;
    uint8_t* y_ptr = output + 1;
    uint8_t* u_ptr = output;
    uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;
        const uint16_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_offset_16px(&pix, (uint8_t*)src, 2, tail_p);

            uint8x16_t y;
            aipl_mve_calculate_y_rgb_x16(&y, &pix);

            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            if (j++ & 1)
            {
                src += 31;
                y_dst += 62;
                cnt -= 16;
            }
            else
            {
                ++src;
                y_dst += 2;

                uint8x16_t u;
                aipl_mve_calculate_u_rgb_x16(&u, &pix);

                vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);
                u_dst += 64;

                uint8x16_t v;
                aipl_mve_calculate_v_rgb_x16(&v, &pix);

                vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);
                v_dst += 64;
            }
        }
    }
#else
    const aipl_rgb565_px_t* src_ptr = input;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb565_px_t* src = src_ptr + i * pitch;

        uint8_t* y_dst = y_ptr + i * pitch * 2;
        uint8_t* v_dst = v_ptr + i * pitch * 2;
        uint8_t* u_dst = u_ptr + i * pitch * 2;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            aipl_pack_yuv_u(u_dst, &px);
            aipl_pack_yuv_v(v_dst, &px);
            y_dst += 2;
            u_dst += 4;
            v_dst += 4;

            aipl_load_rgb565_px(&px, src++);
            aipl_pack_yuv_y(y_dst, &px);
            y_dst += 2;
        }
    }
#endif

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_YV12
aipl_error_t aipl_color_convert_yv12(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_yv12_to_alpha8(input, output,
                                                     pitch,
                                                     width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_yv12_to_argb8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_yv12_to_rgba8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_yv12_to_argb4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_yv12_to_argb1555(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_yv12_to_rgba4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_yv12_to_rgba5551(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_yv12_to_rgb565(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_yv12_to_rgb888(input, output,
                                                     pitch,
                                                     width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_I420:
            return aipl_color_convert_yv12_to_i420(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_yv12_to_nv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_yv12_to_nv21(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_yv12_to_i422(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_yv12_to_yuy2(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_yv12_to_uyvy(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_yv12_to_i444(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_yv12_to_i400(input, output,
                                                   pitch,
                                                   width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_yv12_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input;
    uint8_t* dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(dst, y, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        memcpy(dst, y_src, width);
    }
#endif

    return AIPL_OK;
}


aipl_error_t aipl_color_convert_yv12_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint8_t* dst0 = dst_ptr + i * pitch * 4;
        uint8_t* dst1 = dst0 + pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst0 + 4, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst1 + 4, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 128;
            dst1 += 128;
            cnt -= 16;
        }
    }
#else
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_argb8888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb8888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->a = 0xff;
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->a = 0xff;
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->a = 0xff;
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            dst1->a = 0xff;
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_argb4444_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb4444_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_argb4444_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_argb1555_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb1555_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_argb1555_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint8_t* dst0 = dst_ptr + i * pitch * 4;
        uint8_t* dst1 = dst0 + pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst0 + 4, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst1 + 4, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 128;
            dst1 += 128;
            cnt -= 16;
        }
    }
#else
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgba8888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba8888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            dst0->a = 0xff;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            dst0->a = 0xff;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            dst1->a = 0xff;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            dst1->a = 0xff;
            ++dst1;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgba4444_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba4444_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_rgba4444_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgba5551_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba5551_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_rgba5551_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint8_t* dst0 = dst_ptr + i * pitch * 3;
        uint8_t* dst1 = dst0 + pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst0 + 3, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst1 + 3, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 96;
            dst1 += 96;
            cnt -= 16;
        }
    }
#else
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgb888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgb888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_yuv_to_rgb888(dst0++, *(y_src0++), *u_src, *v_src);

            aipl_yuv_to_rgb888(dst0++, *(y_src0++), *u_src, *v_src);

            aipl_yuv_to_rgb888(dst1++, *(y_src1++), *u_src, *v_src);

            aipl_yuv_to_rgb888(dst1++, *(y_src1++), *(u_src++), *(v_src++));
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgb565_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgb565_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_rgb565_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch / 4;
            uint8_t* u_dst = u_dst_ptr + i * width / 4;
            const uint8_t* v_src = v_src_ptr + i * pitch / 4;
            uint8_t* v_dst = v_dst_ptr + i * width / 4;

            memcpy(u_dst, u_src, width / 2);
            memcpy(v_dst, v_src, width / 2);
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width / 2;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width / 2;

        memcpy(y_dst, y_src, width);
        memcpy(u_dst, u_src, width / 2);
        memcpy(v_dst, v_src, width / 2);
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (i & 1)
        {
            memcpy(u_dst, u_dst - width, width);
            memcpy(v_dst, v_dst - width, width);
        }
        else
        {
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vld1q_z(u_src, tail_p);

                vstrbq_scatter_offset_p(u_dst + 1, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vld1q_z(v_src, tail_p);

                vstrbq_scatter_offset_p(v_dst + 1, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 16;
                v_src += 16;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; ++j)
            {
                u_dst[j] = u_src[j / 2];
                v_dst[j] = v_src[j / 2];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    uint8_t* y_dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 16;
            y_dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * pitch;

        memcpy(y_dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch / 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vld1q_z(u_src, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vld1q_z(v_src, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 16;
                v_src += 16;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j / 2];
                v_dst[j] = v_src[j / 2];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch / 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vld1q_z(u_src, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vld1q_z(v_src, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 16;
                v_src += 16;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j / 2];
                v_dst[j] = v_src[j / 2];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + yuv_size / 4;

    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i / 2* pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j];
            v_dst[j * 4] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yv12_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + yuv_size / 4;

    uint8_t* u_dst_ptr = output;
    uint8_t* y_dst_ptr = u_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i / 2* pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j];
            v_dst[j * 4] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_I420
aipl_error_t aipl_color_convert_i420(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_i420_to_alpha8(input, output,
                                                     pitch,
                                                     width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_i420_to_argb8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_i420_to_rgba8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_i420_to_argb4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_i420_to_argb1555(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_i420_to_rgba4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_i420_to_rgba5551(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_i420_to_rgb565(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_i420_to_rgb888(input, output,
                                                     pitch,
                                                     width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_i420_to_yv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I420:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_NV12:
            return aipl_color_convert_i420_to_nv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_i420_to_nv21(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_i420_to_i422(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_i420_to_yuy2(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_i420_to_uyvy(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_i420_to_i444(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_i420_to_i400(input, output,
                                                   pitch,
                                                   width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_i420_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input;
    uint8_t* dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(dst, y, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        memcpy(dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint8_t* dst0 = dst_ptr + i * pitch * 4;
        uint8_t* dst1 = dst0 + pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst0 + 4, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst1 + 4, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 128;
            dst1 += 128;
            cnt -= 16;
        }
    }
#else
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_argb8888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb8888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->a = 0xff;
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->a = 0xff;
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->a = 0xff;
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            dst1->a = 0xff;
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_argb4444_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb4444_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_argb4444_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_argb1555_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb1555_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_argb1555_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint8_t* dst0 = dst_ptr + i * pitch * 4;
        uint8_t* dst1 = dst0 + pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst0 + 4, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst1 + 4, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 128;
            dst1 += 128;
            cnt -= 16;
        }
    }
#else
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgba8888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba8888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            dst0->a = 0xff;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            dst0->a = 0xff;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            dst1->a = 0xff;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            dst1->a = 0xff;
            ++dst1;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgba4444_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba4444_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_rgba4444_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgba5551_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba5551_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_rgba5551_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint8_t* dst0 = dst_ptr + i * pitch * 3;
        uint8_t* dst1 = dst0 + pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst0 + 3, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst1 + 3, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 96;
            dst1 += 96;
            cnt -= 16;
        }
    }
#else
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgb888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgb888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_yuv_to_rgb888(dst0++, *(y_src0++), *u_src, *v_src);

            aipl_yuv_to_rgb888(dst0++, *(y_src0++), *u_src, *v_src);

            aipl_yuv_to_rgb888(dst1++, *(y_src1++), *u_src, *v_src);

            aipl_yuv_to_rgb888(dst1++, *(y_src1++), *(u_src++), *(v_src++));
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 4;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 16;
            v_src += 16;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 4;
        const uint8_t* u_src = u_ptr + i * pitch / 4;
        aipl_rgb565_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgb565_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *(u_src++), *(v_src++));
            aipl_pack_rgb565_px(dst1++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch / 4;
            uint8_t* u_dst = u_dst_ptr + i * width / 4;
            const uint8_t* v_src = v_src_ptr + i * pitch / 4;
            uint8_t* v_dst = v_dst_ptr + i * width / 4;

            memcpy(u_dst, u_src, width / 2);
            memcpy(v_dst, v_src, width / 2);
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width / 2;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width / 2;

        memcpy(y_dst, y_src, width);
        memcpy(u_dst, u_src, width / 2);
        memcpy(v_dst, v_src, width / 2);
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (i & 1)
        {
            memcpy(u_dst, u_dst - width, width);
            memcpy(v_dst, v_dst - width, width);
        }
        else
        {
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vld1q_z(u_src, tail_p);

                vstrbq_scatter_offset_p(u_dst + 1, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vld1q_z(v_src, tail_p);

                vstrbq_scatter_offset_p(v_dst + 1, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 16;
                v_src += 16;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; ++j)
            {
                u_dst[j] = u_src[j / 2];
                v_dst[j] = v_src[j / 2];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    uint8_t* y_dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 16;
            y_dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * pitch;

        memcpy(y_dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch / 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vld1q_z(u_src, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vld1q_z(v_src, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 16;
                v_src += 16;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j / 2];
                v_dst[j] = v_src[j / 2];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 4;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch / 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vld1q_z(u_src, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vld1q_z(v_src, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 16;
                v_src += 16;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j / 2];
                v_dst[j] = v_src[j / 2];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 4;

    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i / 2* pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j];
            v_dst[j * 4] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i420_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 4;

    uint8_t* u_dst_ptr = output;
    uint8_t* y_dst_ptr = u_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i / 2* pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j];
            v_dst[j * 4] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_I422
aipl_error_t aipl_color_convert_i422(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_i422_to_alpha8(input, output,
                                                     pitch,
                                                     width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_i422_to_argb8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_i422_to_rgba8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_i422_to_argb4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_i422_to_argb1555(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_i422_to_rgba4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_i422_to_rgba5551(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_i422_to_rgb565(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_i422_to_rgb888(input, output,
                                                     pitch,
                                                     width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_i422_to_yv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_i422_to_i420(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_i422_to_nv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_i422_to_nv21(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I422:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_i422_to_yuy2(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_i422_to_uyvy(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_i422_to_i444(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_i422_to_i400(input, output,
                                                   pitch,
                                                   width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_i422_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input;
    uint8_t* dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(dst, y, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        memcpy(dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst + 4, &pix, 2, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            dst += 128;
            cnt -= 16;
        }
    }
#else
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *u_src, *v_src);
            dst->a = 0xff;
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;

            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            dst->a = 0xff;
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_argb4444_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_argb1555_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst + 4, &pix, 2, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            dst += 128;
            cnt -= 16;
        }
    }
#else
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *u_src, *v_src);
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            dst->a = 0xff;
            ++dst;

            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            dst->a = 0xff;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_rgba4444_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_rgba5551_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst + 3, &pix, 2, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            dst += 96;
            cnt -= 16;
        }
    }
#else
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_yuv_to_rgb888(dst++, *(y_src++), *u_src, *v_src);

            aipl_yuv_to_rgb888(dst++, *(y_src++), *(u_src++), *(v_src++));
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size / 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch / 2;
        const uint8_t* u_src = u_ptr + i * pitch / 2;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_rgb565_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 2;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch / 2;
            uint8_t* u_dst = u_dst_ptr + i * width / 4;
            const uint8_t* v_src = v_src_ptr + i * pitch / 2;
            uint8_t* v_dst = v_dst_ptr + i * width / 4;

            memcpy(u_dst, u_src, width / 2);
            memcpy(v_dst, v_src, width / 2);
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 2;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch / 2;
            uint8_t* u_dst = u_dst_ptr + i * width / 4;
            const uint8_t* v_src = v_src_ptr + i * pitch / 2;
            uint8_t* v_dst = v_dst_ptr + i * width / 4;

            memcpy(u_dst, u_src, width / 2);
            memcpy(v_dst, v_src, width / 2);
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 2;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;
        const uint8_t* u_src = u_src_ptr + i * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width;
        const uint8_t* v_src = v_src_ptr + i * pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

#if AIPL_USE_MVE
        int32_t cnt = width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vld1q_z(u_src, tail_p);

            vstrbq_scatter_offset_p(u_dst + 1, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vld1q_z(v_src, tail_p);

            vstrbq_scatter_offset_p(v_dst + 1, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

            u_src += 16;
            v_src += 16;
            u_dst += 32;
            v_dst += 32;
            cnt -= 32;
        }
#else
        for (uint32_t j = 0; j < width; ++j)
        {
            u_dst[j] = u_src[j / 2];
            v_dst[j] = v_src[j / 2];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    uint8_t* y_dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 16;
            y_dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * pitch;

        memcpy(y_dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 2;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch / 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i * pitch / 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vld1q_z(u_src, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vld1q_z(v_src, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 16;
                v_src += 16;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j / 2];
                v_dst[j] = v_src[j / 2];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 2;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch / 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i * pitch / 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vld1q_z(u_src, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vld1q_z(v_src, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 16;
                v_src += 16;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j / 2];
                v_dst[j] = v_src[j / 2];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 2;

    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i * pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j];
            v_dst[j * 4] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i422_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size / 2;

    uint8_t* u_dst_ptr = output;
    uint8_t* y_dst_ptr = u_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i * pitch / 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i * pitch / 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 16;
            v_src += 16;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j];
            v_dst[j * 4] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_I444
aipl_error_t aipl_color_convert_i444(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_i444_to_alpha8(input, output,
                                                     pitch,
                                                     width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_i444_to_argb8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_i444_to_rgba8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_i444_to_argb4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_i444_to_argb1555(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_i444_to_rgba4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_i444_to_rgba5551(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_i444_to_rgb565(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_i444_to_rgb888(input, output,
                                                     pitch,
                                                     width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_i444_to_yv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_i444_to_i420(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_i444_to_nv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_i444_to_nv21(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_i444_to_i422(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_i444_to_yuy2(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_i444_to_uyvy(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I444:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_I400:
            return aipl_color_convert_i444_to_i400(input, output,
                                                   pitch,
                                                   width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_i444_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input;
    uint8_t* dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(dst, y, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        memcpy(dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_16px(dst, &pix, tail_p);

            y_src += 16;
            u_src += 16;
            v_src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            dst->a = 0xff;
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            u_src += 16;
            v_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_argb4444_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            u_src += 16;
            v_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_argb1555_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_16px(dst, &pix, tail_p);

            y_src += 16;
            u_src += 16;
            v_src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            dst->a = 0xff;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            u_src += 16;
            v_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_rgba4444_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            u_src += 16;
            v_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_rgba5551_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            y_src += 16;
            u_src += 16;
            v_src += 16;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_yuv_to_rgb888(dst++, *(y_src++), *(u_src++), *(v_src++));
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + yuv_size;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);
            uint8x16_t u = vldrbq_z_u8(u_src, tail_p);
            uint8x16_t v = vldrbq_z_u8(v_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            u_src += 16;
            v_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        const uint8_t* v_src = v_ptr + i * pitch;
        const uint8_t* u_src = u_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src++), *(u_src++), *(v_src++));
            aipl_pack_rgb565_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch;
            uint8_t* u_dst = u_dst_ptr + i * width / 4;
            const uint8_t* v_src = v_src_ptr + i * pitch;
            uint8_t* v_dst = v_dst_ptr + i * width / 4;

#if AIPL_USE_MVE
            int32_t cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(v_dst, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch;
            uint8_t* u_dst = u_dst_ptr + i * width / 4;
            const uint8_t* v_src = v_src_ptr + i * pitch;
            uint8_t* v_dst = v_dst_ptr + i * width / 4;

#if AIPL_USE_MVE
            int32_t cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(v_dst, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;
        const uint8_t* u_src = u_src_ptr + i * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width / 2;
        const uint8_t* v_src = v_src_ptr + i * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width / 2;

        memcpy(y_dst, y_src, width);

#if AIPL_USE_MVE
        int32_t cnt = width / 2;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vst1q_p(u_dst, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vst1q_p(v_dst, v, tail_p);

            u_src += 32;
            v_src += 32;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width; j += 2)
        {
            u_dst[j / 2] = u_src[j];
            v_dst[j / 2] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    uint8_t* y_dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 16;
            y_dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * pitch;

        memcpy(y_dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i * pitch;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j];
                v_dst[j] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i * pitch;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 32;
                v_dst += 32;
                cnt -= 32;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j];
                v_dst[j] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size;

    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 32;
            v_src += 32;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j * 2];
            v_dst[j * 4] = v_src[j * 2];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i444_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + yuv_size;

    uint8_t* u_dst_ptr = output;
    uint8_t* y_dst_ptr = u_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 32;
            v_src += 32;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j * 2];
            v_dst[j * 4] = v_src[j * 2];
        }
#endif
    }

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_NV12
aipl_error_t aipl_color_convert_nv12(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_nv12_to_alpha8(input, output,
                                                     pitch,
                                                     width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_nv12_to_argb8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_nv12_to_rgba8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_nv12_to_argb4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_nv12_to_argb1555(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_nv12_to_rgba4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_nv12_to_rgba5551(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_nv12_to_rgb565(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_nv12_to_rgb888(input, output,
                                                     pitch,
                                                     width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_nv12_to_yv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_nv12_to_i420(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV12:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_NV21:
            return aipl_color_convert_nv12_to_nv21(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_nv12_to_i422(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_nv12_to_yuy2(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_nv12_to_uyvy(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_nv12_to_i444(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_nv12_to_i400(input, output,
                                                   pitch,
                                                   width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_nv12_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input;
    uint8_t* dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(dst, y, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        memcpy(dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint8_t* dst0 = dst_ptr + i * pitch * 4;
        uint8_t* dst1 = dst0 + pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst0 + 4, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst1 + 4, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 128;
            dst1 += 128;
            cnt -= 16;
        }
    }
#else
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_argb8888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb8888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->a = 0xff;
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->a = 0xff;
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->a = 0xff;
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->a = 0xff;
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_argb4444_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb4444_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_argb1555_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb1555_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint8_t* dst0 = dst_ptr + i * pitch * 4;
        uint8_t* dst1 = dst0 + pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst0 + 4, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst1 + 4, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 128;
            dst1 += 128;
            cnt -= 16;
        }
    }
#else
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgba8888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba8888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            dst0->a = 0xff;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            dst0->a = 0xff;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            dst1->a = 0xff;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            dst1->a = 0xff;
            ++dst1;

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgba4444_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba4444_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgba5551_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba5551_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint8_t* dst0 = dst_ptr + i * pitch * 3;
        uint8_t* dst1 = dst0 + pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst0 + 3, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst1 + 3, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 96;
            dst1 += 96;
            cnt -= 16;
        }
    }
#else
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgb888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgb888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + yuv_size;
    const uint8_t* v_ptr = u_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgb565_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgb565_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;}

aipl_error_t aipl_color_convert_nv12_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;

#if AIPL_USE_MVE
            int32_t cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(v_dst, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;

#if AIPL_USE_MVE
            int32_t cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(v_dst, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width / 2;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width / 2;

        memcpy(y_dst, y_src, width);

#if AIPL_USE_MVE
        int32_t cnt = width / 2;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vst1q_p(u_dst, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vst1q_p(v_dst, v, tail_p);

            u_src += 32;
            v_src += 32;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width; j += 2)
        {
            u_dst[j / 2] = u_src[j];
            v_dst[j / 2] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    uint8_t* y_dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 16;
            y_dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * pitch;

        memcpy(y_dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width / 2;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 32;
                v_dst += 32;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j];
                v_dst[j] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width;
#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
            vstrbq_scatter_offset_p(u_dst + 1, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
            vstrbq_scatter_offset_p(v_dst + 1, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

            u_src += 32;
            v_src += 32;
            u_dst += 32;
            v_dst += 32;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width; j += 2)
        {
            u_dst[j] = u_dst[j + 1] = u_src[j];
            v_dst[j] = v_dst[j + 1] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + 1;

    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 32;
            v_src += 32;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j * 2];
            v_dst[j * 4] = v_src[j * 2];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv12_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* v_src_ptr = u_src_ptr + 1;

    uint8_t* u_dst_ptr = output;
    uint8_t* y_dst_ptr = u_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 32;
            v_src += 32;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j * 2];
            v_dst[j * 4] = v_src[j * 2];
        }
#endif
    }

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_NV21
aipl_error_t aipl_color_convert_nv21(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_nv21_to_alpha8(input, output,
                                                     pitch,
                                                     width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_nv21_to_argb8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_nv21_to_rgba8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_nv21_to_argb4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_nv21_to_argb1555(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_nv21_to_rgba4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_nv21_to_rgba5551(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_nv21_to_rgb565(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_nv21_to_rgb888(input, output,
                                                     pitch,
                                                     width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_nv21_to_yv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_nv21_to_i420(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV21:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_NV12:
            return aipl_color_convert_nv21_to_nv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_nv21_to_i422(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_nv21_to_yuy2(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_nv21_to_uyvy(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_nv21_to_i444(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_nv21_to_i400(input, output,
                                                   pitch,
                                                   width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_nv21_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input;
    uint8_t* dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(dst, y, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch;

        memcpy(dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint8_t* dst0 = dst_ptr + i * pitch * 4;
        uint8_t* dst1 = dst0 + pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst0 + 4, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst1 + 4, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 128;
            dst1 += 128;
            cnt -= 16;
        }
    }
#else
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_argb8888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb8888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->a = 0xff;
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->a = 0xff;
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->a = 0xff;
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->a = 0xff;
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_argb4444_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb4444_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb4444_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_argb1555_px_t* dst0 = dst_ptr + i * pitch;
        aipl_argb1555_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_argb1555_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint8_t* dst0 = dst_ptr + i * pitch * 4;
        uint8_t* dst1 = dst0 + pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst0 + 4, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst1 + 4, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 128;
            dst1 += 128;
            cnt -= 16;
        }
    }
#else
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgba8888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba8888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            dst0->a = 0xff;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            dst0->a = 0xff;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            dst1->a = 0xff;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            dst1->a = 0xff;
            ++dst1;

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgba4444_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba4444_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgba5551_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgba5551_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint8_t* dst0 = dst_ptr + i * pitch * 3;
        uint8_t* dst1 = dst0 + pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst0 + 3, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst1 + 3, &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 96;
            dst1 += 96;
            cnt -= 16;
        }
    }
#else
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgb888_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgb888_px_t* dst1 = dst0 + pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            dst0->r = px.r;
            dst0->g = px.g;
            dst0->b = px.b;
            ++dst0;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            dst1->r = px.r;
            dst1->g = px.g;
            dst1->b = px.b;
            ++dst1;

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* v_ptr = y_ptr + yuv_size;
    const uint8_t* u_ptr = v_ptr + 1;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        uint16_t* dst0 = dst_ptr + i * pitch;
        uint16_t* dst1 = dst0 + pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src0, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst0, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src0 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst0 + 1), &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst1, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src1 + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst1 + 1), &pix, 2, tail_p);

            y_src0 += 32;
            y_src1 += 32;
            u_src += 32;
            v_src += 32;
            dst0 += 32;
            dst1 += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; i += 2)
    {
        const uint8_t* y_src0 = y_ptr + i * pitch;
        const uint8_t* y_src1 = y_src0 + pitch;
        const uint8_t* v_src = v_ptr + i / 2 * pitch;
        const uint8_t* u_src = u_ptr + i / 2 * pitch;
        aipl_rgb565_px_t* dst0 = dst_ptr + i * pitch;
        aipl_rgb565_px_t* dst1 = dst0 + pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src0++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst0++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst1++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src1++), *u_src, *v_src);
            aipl_pack_rgb565_px(dst1++, &px);

            u_src += 2;
            v_src += 2;
        }
    }
#endif

    return AIPL_OK;}

aipl_error_t aipl_color_convert_nv21_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;

#if AIPL_USE_MVE
            int32_t cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(v_dst, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;

#if AIPL_USE_MVE
            int32_t cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vst1q_p(v_dst, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width / 2;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width / 2;

        memcpy(y_dst, y_src, width);

#if AIPL_USE_MVE
        int32_t cnt = width / 2;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vst1q_p(u_dst, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vst1q_p(v_dst, v, tail_p);

            u_src += 32;
            v_src += 32;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width; j += 2)
        {
            u_dst[j / 2] = u_src[j];
            v_dst[j / 2] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    uint8_t* y_dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 16;
            y_dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * pitch;

        memcpy(y_dst, y_src, width);
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;
#if AIPL_USE_MVE
            int32_t cnt = width / 2;

            uint32_t j = 0;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 32;
                v_src += 32;
                u_dst += 32;
                v_dst += 32;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width; j += 2)
            {
                u_dst[j] = u_src[j];
                v_dst[j] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + 1;

    yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width;
#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
            vstrbq_scatter_offset_p(u_dst + 1, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
            vstrbq_scatter_offset_p(v_dst + 1, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

            u_src += 32;
            v_src += 32;
            u_dst += 32;
            v_dst += 32;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width; j += 2)
        {
            u_dst[j] = u_dst[j + 1] = u_src[j];
            v_dst[j] = v_dst[j + 1] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + 1;

    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 32;
            v_src += 32;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j * 2];
            v_dst[j * 4] = v_src[j * 2];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_nv21_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_src_ptr = input;
    const uint8_t* v_src_ptr = y_src_ptr + yuv_size;
    const uint8_t* u_src_ptr = v_src_ptr + 1;

    uint8_t* u_dst_ptr = output;
    uint8_t* y_dst_ptr = u_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i / 2 * pitch;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i / 2 * pitch;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            u_src += 32;
            v_src += 32;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width / 2; ++j)
        {
            y_dst[j * 4] = y_src[j * 2];
            y_dst[j * 4 + 2] = y_src[j * 2 + 1];
            u_dst[j * 4] = u_src[j * 2];
            v_dst[j * 4] = v_src[j * 2];
        }
#endif
    }

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_YUY2
aipl_error_t aipl_color_convert_yuy2(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_yuy2_to_alpha8(input, output,
                                                     pitch,
                                                     width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_yuy2_to_argb8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_yuy2_to_rgba8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_yuy2_to_argb4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_yuy2_to_argb1555(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_yuy2_to_rgba4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_yuy2_to_rgba5551(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_yuy2_to_rgb565(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_yuy2_to_rgb888(input, output,
                                                     pitch,
                                                     width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_yuy2_to_yv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_yuy2_to_i420(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_yuy2_to_nv21(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_yuy2_to_nv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_yuy2_to_i422(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_YUY2:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_yuy2_to_uyvy(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_yuy2_to_i444(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_yuy2_to_i400(input, output,
                                                   pitch,
                                                   width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_yuy2_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input;
    uint8_t* dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(dst, y, tail_p);

            y_src += 32;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            dst[j / 2] = y_src[j];
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst + 4, &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 128;
            cnt -= 16;
        }
    }
#else
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            dst->a = 0xff;
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            dst->a = 0xff;
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_argb4444_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_argb4444_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_argb1555_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_argb1555_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst + 4, &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 128;
            cnt -= 16;
        }
    }
#else
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            dst->a = 0xff;
            ++dst;

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            dst->a = 0xff;
            ++dst;

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_rgba4444_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_rgba5551_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst + 3, &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 96;
            cnt -= 16;
        }
    }
#else
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* y_ptr = input;
    const uint8_t* u_ptr = y_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_rgb565_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_rgb565_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch * 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;
            const uint8_t* v_src = v_src_ptr + i * pitch * 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;

#if AIPL_USE_MVE
            cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_p_u8(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_p_u8(v_dst, v, tail_p);

                u_src += 64;
                v_src += 64;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width * 2; j += 4)
            {
                u_dst[j / 4] = u_src[j];
                v_dst[j / 4] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch * 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;
            const uint8_t* v_src = v_src_ptr + i * pitch * 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;

#if AIPL_USE_MVE
            cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_p_u8(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_p_u8(v_dst, v, tail_p);

                u_src += 64;
                v_src += 64;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width * 2; j += 4)
            {
                u_dst[j / 4] = u_src[j];
                v_dst[j / 4] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        const uint8_t* u_src = u_src_ptr + i * pitch * 2;
        uint8_t* u_dst = u_dst_ptr + i * width / 2;
        const uint8_t* v_src = v_src_ptr + i * pitch * 2;
        uint8_t* v_dst = v_dst_ptr + i * width / 2;

#if AIPL_USE_MVE
        cnt = width / 2;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(u_dst, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(v_dst, v, tail_p);

            u_src += 64;
            v_src += 64;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 4)
        {
            u_dst[j / 4] = u_src[j];
            v_dst[j / 4] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_ptr = input;
    uint8_t* y_dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch * 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i * pitch * 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;

#if AIPL_USE_MVE
            cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 64;
                v_src += 64;
                u_dst += 32;
                v_dst += 32;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width * 2; j += 4)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        const uint8_t* u_src = u_src_ptr + i * pitch * 2;
        uint8_t* u_dst = u_dst_ptr + i * width;
        const uint8_t* v_src = v_src_ptr + i * pitch * 2;
        uint8_t* v_dst = v_dst_ptr + i * width;

#if AIPL_USE_MVE
        cnt = width / 2;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
            vstrbq_scatter_offset_p(u_dst + 1, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
            vstrbq_scatter_offset_p(v_dst + 1, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

            u_src += 64;
            v_src += 64;
            u_dst += 32;
            v_dst += 32;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 4)
        {
            u_dst[j / 2] = u_dst[j / 2 + 1] = u_src[j];
            v_dst[j / 2] = v_dst[j / 2 + 1] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch * 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i * pitch * 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;

#if AIPL_USE_MVE
            cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 64;
                v_src += 64;
                u_dst += 32;
                v_dst += 32;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width * 2; j += 4)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_yuy2_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;
    const uint8_t* u_src_ptr = y_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint8_t* u_dst_ptr = output;
    uint8_t* y_dst_ptr = u_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i * pitch * 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i * pitch * 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 4)
        {
            y_dst[j] = y_src[j];
            y_dst[j + 2] = y_src[j + 2];
            u_dst[j] = u_src[j];
            v_dst[j] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_UYVY
aipl_error_t aipl_color_convert_uyvy(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return aipl_color_convert_uyvy_to_alpha8(input, output,
                                                     pitch,
                                                     width, height);
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_uyvy_to_argb8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_uyvy_to_rgba8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_uyvy_to_argb4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_uyvy_to_argb1555(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_uyvy_to_rgba4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_uyvy_to_rgba5551(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_uyvy_to_rgb565(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_uyvy_to_rgb888(input, output,
                                                     pitch,
                                                     width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_uyvy_to_yv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_uyvy_to_i420(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_uyvy_to_nv21(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_uyvy_to_nv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_uyvy_to_i422(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_UYVY:
            return AIPL_FORMAT_MISMATCH;
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_uyvy_to_yuy2(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_uyvy_to_i444(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I400:
            return aipl_color_convert_uyvy_to_i400(input, output,
                                                   pitch,
                                                   width, height);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_uyvy_to_alpha8(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input + 1;
    uint8_t* dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(dst, y, tail_p);

            y_src += 32;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            dst[j / 2] = y_src[j];
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* u_ptr = input;
    const uint8_t* y_ptr = u_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb8888_offset_16px(dst + 4, &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 128;
            cnt -= 16;
        }
    }
#else
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            dst->a = 0xff;
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            dst->a = 0xff;
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* u_ptr = input;
    const uint8_t* y_ptr = u_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb4444_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_argb4444_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_argb4444_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* u_ptr = input;
    const uint8_t* y_ptr = u_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_argb1555_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_argb1555_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_argb1555_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* u_ptr = input;
    const uint8_t* y_ptr = u_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba8888_offset_16px(dst + 4, &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 128;
            cnt -= 16;
        }
    }
#else
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            dst->a = 0xff;
            ++dst;

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            dst->a = 0xff;
            ++dst;

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* u_ptr = input;
    const uint8_t* y_ptr = u_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba4444_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_rgba4444_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_rgba4444_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* u_ptr = input;
    const uint8_t* y_ptr = u_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgba5551_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_rgba5551_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_rgba5551_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* u_ptr = input;
    const uint8_t* y_ptr = u_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb888_offset_16px(dst + 3, &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 96;
            cnt -= 16;
        }
    }
#else
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    uint32_t yuv_size = pitch * height;
    const uint8_t* u_ptr = input;
    const uint8_t* y_ptr = u_ptr + 1;
    const uint8_t* v_ptr = u_ptr + 2;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width / 2;

        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)dst, &pix, 2, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            aipl_mve_convert_yuv_to_rgb_x16(&pix, &y, &u, &v);

            aipl_mve_store_rgb565_offset_16px((uint8_t*)(dst + 1), &pix, 2, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            dst += 32;
            cnt -= 16;
        }
    }
#else
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        const uint8_t* v_src = v_ptr + i * pitch * 2;
        const uint8_t* u_src = u_ptr + i * pitch * 2;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;


        for (uint32_t j = 0; j < width; j += 2)
        {
            aipl_rgb888_px_t px;
            aipl_yuv_to_rgb888(&px, *y_src, *u_src, *v_src);
            aipl_pack_rgb565_px(dst++, &px);

            aipl_yuv_to_rgb888(&px, *(y_src + 2), *u_src, *v_src);
            aipl_pack_rgb565_px(dst++, &px);

            y_src += 4;
            u_src += 4;
            v_src += 4;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* u_src_ptr = input;
    const uint8_t* y_src_ptr = u_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch * 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;
            const uint8_t* v_src = v_src_ptr + i * pitch * 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;

#if AIPL_USE_MVE
            cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_p_u8(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_p_u8(v_dst, v, tail_p);

                u_src += 64;
                v_src += 64;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width * 2; j += 4)
            {
                u_dst[j / 4] = u_src[j];
                v_dst[j / 4] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* u_src_ptr = input;
    const uint8_t* y_src_ptr = u_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch * 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;
            const uint8_t* v_src = v_src_ptr + i * pitch * 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;

#if AIPL_USE_MVE
            cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_p_u8(u_dst, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_p_u8(v_dst, v, tail_p);

                u_src += 64;
                v_src += 64;
                u_dst += 16;
                v_dst += 16;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width * 2; j += 4)
            {
                u_dst[j / 4] = u_src[j];
                v_dst[j / 4] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* u_src_ptr = input;
    const uint8_t* y_src_ptr = u_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        const uint8_t* u_src = u_src_ptr + i * pitch * 2;
        uint8_t* u_dst = u_dst_ptr + i * width / 2;
        const uint8_t* v_src = v_src_ptr + i * pitch * 2;
        uint8_t* v_dst = v_dst_ptr + i * width / 2;

#if AIPL_USE_MVE
        cnt = width / 2;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(u_dst, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(v_dst, v, tail_p);

            u_src += 64;
            v_src += 64;
            u_dst += 16;
            v_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 4)
        {
            u_dst[j / 4] = u_src[j];
            v_dst[j / 4] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_i400(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_ptr = input + 1;
    uint8_t* y_dst_ptr = output;

#if AIPL_USE_MVE
    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

        uint32_t j = 0;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
    }
#else
    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* u_src_ptr = input;
    const uint8_t* y_src_ptr = u_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch * 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i * pitch * 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;

#if AIPL_USE_MVE
            cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 64;
                v_src += 64;
                u_dst += 32;
                v_dst += 32;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width * 2; j += 4)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* u_src_ptr = input;
    const uint8_t* y_src_ptr = u_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        const uint8_t* u_src = u_src_ptr + i * pitch * 2;
        uint8_t* u_dst = u_dst_ptr + i * width;
        const uint8_t* v_src = v_src_ptr + i * pitch * 2;
        uint8_t* v_dst = v_dst_ptr + i * width;

#if AIPL_USE_MVE
        cnt = width / 2;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);
            vstrbq_scatter_offset_p(u_dst + 1, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

            vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);
            vstrbq_scatter_offset_p(v_dst + 1, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

            u_src += 64;
            v_src += 64;
            u_dst += 32;
            v_dst += 32;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 4)
        {
            u_dst[j / 2] = u_dst[j / 2 + 1] = u_src[j];
            v_dst[j / 2] = v_dst[j / 2 + 1] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* u_src_ptr = input;
    const uint8_t* y_src_ptr = u_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint32_t yuv_size = width * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width;

#if AIPL_USE_MVE
        int32_t cnt = width;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);

            vstrbq_p_u8(y_dst, y, tail_p);

            y_src += 32;
            y_dst += 16;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 2)
        {
            y_dst[j / 2] = y_src[j];
        }
#endif

        if (!(i & 1))
        {
            const uint8_t* u_src = u_src_ptr + i * pitch * 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width;
            const uint8_t* v_src = v_src_ptr + i * pitch * 2;
            uint8_t* v_dst = v_dst_ptr + i / 2 * width;

#if AIPL_USE_MVE
            cnt = width / 2;
            while (cnt > 0)
            {
                mve_pred16_t tail_p = vctp8q(cnt);

                uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(u_dst, AIPL_2_BYTE_OFFSETS_U8, u, tail_p);

                uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);

                vstrbq_scatter_offset_p(v_dst, AIPL_2_BYTE_OFFSETS_U8, v, tail_p);

                u_src += 64;
                v_src += 64;
                u_dst += 32;
                v_dst += 32;
                cnt -= 16;
            }
#else
            for (uint32_t j = 0; j < width * 2; j += 4)
            {
                u_dst[j / 2] = u_src[j];
                v_dst[j / 2] = v_src[j];
            }
#endif
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_uyvy_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* u_src_ptr = input;
    const uint8_t* y_src_ptr = u_src_ptr + 1;
    const uint8_t* v_src_ptr = u_src_ptr + 2;

    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch * 2;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        const uint8_t* u_src = u_src_ptr + i * pitch * 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        const uint8_t* v_src = v_src_ptr + i * pitch * 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;
        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 2, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vldrbq_gather_offset_z(u_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vldrbq_gather_offset_z(v_src, AIPL_4_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 64;
            u_src += 64;
            v_src += 64;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 4)
        {
            y_dst[j] = y_src[j];
            y_dst[j + 2] = y_src[j + 2];
            u_dst[j] = u_src[j];
            v_dst[j] = v_src[j];
        }
#endif
    }

    return AIPL_OK;
}
#endif

#ifdef AIPL_CONVERT_I400
aipl_error_t aipl_color_convert_i400(const void* input, void* output,
                                     uint32_t pitch,
                                     uint32_t width, uint32_t height,
                                     aipl_color_format_t format)
{
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            return AIPL_FORMAT_MISMATCH;
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            return aipl_color_convert_i400_to_argb8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA8888:
            return aipl_color_convert_i400_to_rgba8888(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB4444:
            return aipl_color_convert_i400_to_argb4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_ARGB1555:
            return aipl_color_convert_i400_to_argb1555(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA4444:
            return aipl_color_convert_i400_to_rgba4444(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGBA5551:
            return aipl_color_convert_i400_to_rgba5551(input, output,
                                                       pitch,
                                                       width, height);
        case AIPL_COLOR_RGB565:
            return aipl_color_convert_i400_to_rgb565(input, output,
                                                     pitch,
                                                     width, height);
        case AIPL_COLOR_RGB888:
            return aipl_color_convert_i400_to_rgb888(input, output,
                                                     pitch,
                                                     width, height);
        /* YUV color formats */
        case AIPL_COLOR_YV12:
            return aipl_color_convert_i400_to_yv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I420:
            return aipl_color_convert_i400_to_i420(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV21:
            return aipl_color_convert_i400_to_nv21(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_NV12:
            return aipl_color_convert_i400_to_nv12(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I422:
            return aipl_color_convert_i400_to_i422(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_UYVY:
            return aipl_color_convert_i400_to_uyvy(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_YUY2:
            return aipl_color_convert_i400_to_yuy2(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I444:
            return aipl_color_convert_i400_to_i444(input, output,
                                                   pitch,
                                                   width, height);
        case AIPL_COLOR_I400:
            return AIPL_FORMAT_MISMATCH;

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }
}

aipl_error_t aipl_color_convert_i400_to_argb8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    const uint8_t* y_ptr = input;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_alpha_to_rgb_x16(&pix, &y);

            aipl_mve_store_argb8888_16px(dst, &pix, tail_p);

            y_src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        aipl_argb8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_alpha_to_rgb888(&px, *(y_src++));
            dst->a = 0xff;
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_argb4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    const uint8_t* y_ptr = input;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_alpha_to_rgb_x16(&pix, &y);

            aipl_mve_store_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        aipl_argb4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_alpha_to_rgb888(&px, *(y_src++));
            aipl_pack_argb4444_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_argb1555(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    const uint8_t* y_ptr = input;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_alpha_to_rgb_x16(&pix, &y);

            aipl_mve_store_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        aipl_argb1555_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_alpha_to_rgb888(&px, *(y_src++));
            aipl_pack_argb1555_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_rgba8888(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    const uint8_t* y_ptr = input;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_alpha_to_rgb_x16(&pix, &y);

            aipl_mve_store_rgba8888_16px(dst, &pix, tail_p);

            y_src += 16;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        aipl_rgba8888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_alpha_to_rgb888(&px, *(y_src++));
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            dst->a = 0xff;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_rgba4444(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    const uint8_t* y_ptr = input;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_alpha_to_rgb_x16(&pix, &y);

            aipl_mve_store_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        aipl_rgba4444_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_alpha_to_rgb888(&px, *(y_src++));
            aipl_pack_rgba4444_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_rgba5551(const void* input,
                                                 void* output,
                                                 uint32_t pitch,
                                                 uint32_t width,
                                                 uint32_t height)
{
    const uint8_t* y_ptr = input;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_alpha_to_rgb_x16(&pix, &y);

            aipl_mve_store_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        aipl_rgba5551_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_alpha_to_rgb888(&px, *(y_src++));
            aipl_pack_rgba5551_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_rgb888(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input;

#if AIPL_USE_MVE
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        uint8_t* dst = dst_ptr + i * pitch * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_alpha_to_rgb_x16(&pix, &y);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            y_src += 16;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        aipl_rgb888_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_alpha_to_rgb888(&px, *(y_src++));
            dst->r = px.r;
            dst->g = px.g;
            dst->b = px.b;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_rgb565(const void* input,
                                               void* output,
                                               uint32_t pitch,
                                               uint32_t width,
                                               uint32_t height)
{
    const uint8_t* y_ptr = input;

#if AIPL_USE_MVE
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;

        const uint8_t* y_src = y_ptr + i * pitch;
        uint16_t* dst = dst_ptr + i * pitch;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_z_u8(y_src, tail_p);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_convert_alpha_to_rgb_x16(&pix, &y);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

            y_src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    aipl_rgb565_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_ptr + i * pitch;
        aipl_rgb565_px_t* dst = dst_ptr + i * pitch;

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_alpha_to_rgb888(&px, *(y_src++));
            aipl_pack_rgb565_px(dst++, &px);
        }
    }
#endif

    return AIPL_OK;

}

aipl_error_t aipl_color_convert_i400_to_yv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;

    uint32_t yuv_size = pitch * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;

            memset(u_dst, 0x80, width / 2);
            memset(v_dst, 0x80, width / 2);
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_i420(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;

    uint32_t yuv_size = pitch * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 4;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            uint8_t* v_dst = v_dst_ptr + i / 2 * width / 2;
            uint8_t* u_dst = u_dst_ptr + i / 2 * width / 2;

            memset(u_dst, 0x80, width / 2);
            memset(v_dst, 0x80, width / 2);
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_i422(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;

    uint32_t yuv_size = pitch * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size / 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        uint8_t* v_dst = v_dst_ptr + i * width / 2;
        uint8_t* u_dst = u_dst_ptr + i * width / 2;

        memset(u_dst, 0x80, width / 2);
        memset(v_dst, 0x80, width / 2);
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_nv12(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;

    uint32_t yuv_size = pitch * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            uint16_t* v_dst = (uint16_t*)u_dst_ptr + width / 2;
            uint16_t* u_dst = (uint16_t*)v_dst_ptr + width / 2;

            memset(u_dst, 0x8080, width / 2);
            memset(v_dst, 0x8080, width / 2);
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_i444(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;

    uint32_t yuv_size = pitch * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* v_dst_ptr = u_dst_ptr + yuv_size;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        uint8_t* v_dst = v_dst_ptr + i * width;
        uint8_t* u_dst = u_dst_ptr + i * width;

        memset(u_dst, 0x80, width);
        memset(v_dst, 0x80, width);
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_nv21(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;

    uint32_t yuv_size = pitch * height;
    uint8_t* y_dst_ptr = output;
    uint8_t* v_dst_ptr = y_dst_ptr + yuv_size;
    uint8_t* u_dst_ptr = v_dst_ptr + 1;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width;

        memcpy(y_dst, y_src, width);

        if (!(i & 1))
        {
            uint16_t* v_dst = (uint16_t*)u_dst_ptr + width / 2;
            uint16_t* u_dst = (uint16_t*)v_dst_ptr + width / 2;

            memset(u_dst, 0x8080, width / 2);
            memset(v_dst, 0x8080, width / 2);
        }
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_yuy2(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;

    uint8_t* y_dst_ptr = output;
    uint8_t* u_dst_ptr = y_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;
        while(cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vdupq_n_u8(0x80);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vdupq_n_u8(0x80);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 4)
        {
            y_dst[j] = y_src[j / 2];
            y_dst[j + 2] = y_src[j / 2 + 1];
            u_dst[j] = 0x80;
            v_dst[j] = 0x80;
        }
#endif
    }

    return AIPL_OK;
}

aipl_error_t aipl_color_convert_i400_to_uyvy(const void* input,
                                             void* output,
                                             uint32_t pitch,
                                             uint32_t width,
                                             uint32_t height)
{
    const uint8_t* y_src_ptr = input;

    uint8_t* u_dst_ptr = output;
    uint8_t* y_dst_ptr = u_dst_ptr + 1;
    uint8_t* v_dst_ptr = u_dst_ptr + 2;

    for (uint32_t i = 0; i < height; ++i)
    {
        const uint8_t* y_src = y_src_ptr + i * pitch;
        uint8_t* y_dst = y_dst_ptr + i * width * 2;
        uint8_t* u_dst = u_dst_ptr + i * width * 2;
        uint8_t* v_dst = v_dst_ptr + i * width * 2;

#if AIPL_USE_MVE
        int32_t cnt = width / 2;
        while(cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            uint8x16_t y = vldrbq_gather_offset_z(y_src, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            y = vldrbq_gather_offset_z(y_src + 1, AIPL_2_BYTE_OFFSETS_U8, tail_p);
            vstrbq_scatter_offset_p(y_dst + 2, AIPL_4_BYTE_OFFSETS_U8, y, tail_p);

            uint8x16_t u = vdupq_n_u8(0x80);
            vstrbq_scatter_offset_p(u_dst, AIPL_4_BYTE_OFFSETS_U8, u, tail_p);

            uint8x16_t v = vdupq_n_u8(0x80);
            vstrbq_scatter_offset_p(v_dst, AIPL_4_BYTE_OFFSETS_U8, v, tail_p);

            y_src += 32;
            y_dst += 64;
            u_dst += 64;
            v_dst += 64;
            cnt -= 16;
        }
#else
        for (uint32_t j = 0; j < width * 2; j += 4)
        {
            y_dst[j] = y_src[j / 2];
            y_dst[j + 2] = y_src[j / 2 + 1];
            u_dst[j] = 0x80;
            v_dst[j] = 0x80;
        }
#endif
    }

    return AIPL_OK;
}

#endif


/**********************
 *   STATIC FUNCTIONS
 **********************/
