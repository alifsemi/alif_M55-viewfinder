/**
 * @file aipl_white_balance.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "aipl_white_balance.h"
#include <RTE_Device.h>
#include "aipl_config.h"
#if AIPL_USE_MVE
#include "aipl_mve_utils.h"
#else
#include "aipl_utils.h"
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

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
aipl_error_t aipl_white_balance_rgb(const void* input, void* output,
                                    uint32_t pitch,
                                    uint32_t width, uint32_t height,
                                    aipl_color_format_t format,
                                    float ar, float ag, float ab)
{
    switch (format)
    {
        case AIPL_COLOR_ARGB8888:
            return aipl_white_balance_argb8888(input, output, pitch,
                                               width, height, ar, ag, ab);
        case AIPL_COLOR_RGBA8888:
            return aipl_white_balance_rgba8888(input, output, pitch,
                                               width, height, ar, ag, ab);
        case AIPL_COLOR_ARGB4444:
            return aipl_white_balance_argb4444(input, output, pitch,
                                               width, height, ar, ag, ab);
        case AIPL_COLOR_ARGB1555:
            return aipl_white_balance_argb1555(input, output, pitch,
                                               width, height, ar, ag, ab);
        case AIPL_COLOR_RGBA4444:
            return aipl_white_balance_rgba4444(input, output, pitch,
                                               width, height, ar, ag, ab);
        case AIPL_COLOR_RGBA5551:
            return aipl_white_balance_rgba5551(input, output, pitch,
                                               width, height, ar, ag, ab);
        case AIPL_COLOR_RGB888:
            return aipl_white_balance_rgb888(input, output, pitch,
                                             width, height, ar, ag, ab);
        case AIPL_COLOR_RGB565:
            return aipl_white_balance_rgb565(input, output, pitch,
                                             width, height, ar, ag, ab);

        default:
            return AIPL_UNSUPPORTED_FORMAT;
    }

    return AIPL_OK;
}

aipl_error_t aipl_white_balance_rgb_img(const aipl_image_t* input,
                                        aipl_image_t* output,
                                        float ar, float ag, float ab)
{
    if (input->width != output->width || input->height != output->height)
    {
        return AIPL_SIZE_MISMATCH;
    }

    if (input->format != output->format)
    {
        return AIPL_FORMAT_MISMATCH;
    }

    return aipl_white_balance_rgb(input->data, output->data, input->pitch,
                                  input->width, input->height, input->format,
                                  ar, ag, ab);

    return AIPL_OK;
}

aipl_error_t aipl_white_balance_argb8888(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         float ar, float ag, float ab)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + (i * pitch) * 4;
        uint8_t* dst = dst_ptr + (i * pitch) * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb8888_16px(&pix, src, tail_p);

            aipl_mve_white_balance_argb_x16(&pix, ar, ag, ab);

            aipl_mve_storea_argb8888_16px(dst, &pix, tail_p);

            src += 64;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_argb8888_px_t* src_ptr = input;
    aipl_argb8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb8888_px_t* src = src_ptr + (i * pitch);
        aipl_argb8888_px_t* dst = dst_ptr + (i * pitch);

        for (uint32_t j = 0; j < width; ++j)
        {
            int16_t r = src->r * ar;
            int16_t g = src->g * ag;
            int16_t b = src->b * ab;

            dst->a = src->a;
            dst->r = aipl_channel_cap(r);
            dst->g = aipl_channel_cap(g);
            dst->b = aipl_channel_cap(b);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_white_balance_argb4444(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         float ar, float ag, float ab)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + (i * pitch);
        uint16_t* dst = dst_ptr + (i * pitch);

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_white_balance_argb_x16(&pix, ar, ag, ab);

            aipl_mve_storea_argb4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb4444_px_t* src_ptr = input;
    aipl_argb4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb4444_px_t* src = src_ptr + (i * pitch);
        aipl_argb4444_px_t* dst = dst_ptr + (i * pitch);

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_argb4444_px(&px, src);

            int16_t r = px.r * ar;
            int16_t g = px.g * ag;
            int16_t b = px.b * ab;

            px.r = aipl_channel_cap(r);
            px.g = aipl_channel_cap(g);
            px.b = aipl_channel_cap(b);

            aipl_packa_argb4444_px(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_white_balance_argb1555(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         float ar, float ag, float ab)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + (i * pitch);
        uint16_t* dst = dst_ptr + (i * pitch);

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_argb1555_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_white_balance_argb_x16(&pix, ar, ag, ab);

            aipl_mve_storea_argb1555_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_argb1555_px_t* src_ptr = input;
    aipl_argb1555_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_argb1555_px_t* src = src_ptr + (i * pitch);
        aipl_argb1555_px_t* dst = dst_ptr + (i * pitch);

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_argb1555_px(&px, src);

            int16_t r = px.r * ar;
            int16_t g = px.g * ag;
            int16_t b = px.b * ab;

            px.r = aipl_channel_cap(r);
            px.g = aipl_channel_cap(g);
            px.b = aipl_channel_cap(b);

            aipl_packa_argb1555_px(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif
    return AIPL_OK;
}

aipl_error_t aipl_white_balance_rgba8888(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         float ar, float ag, float ab)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + (i * pitch) * 4;
        uint8_t* dst = dst_ptr + (i * pitch) * 4;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba8888_16px(&pix, src, tail_p);

            aipl_mve_white_balance_argb_x16(&pix, ar, ag, ab);

            aipl_mve_storea_rgba8888_16px(dst, &pix, tail_p);

            src += 64;
            dst += 64;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba8888_px_t* src_ptr = input;
    aipl_rgba8888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba8888_px_t* src = src_ptr + (i * pitch);
        aipl_rgba8888_px_t* dst = dst_ptr + (i * pitch);

        for (uint32_t j = 0; j < width; ++j)
        {
            int16_t r = src->r * ar;
            int16_t g = src->g * ag;
            int16_t b = src->b * ab;

            dst->r = aipl_channel_cap(r);
            dst->g = aipl_channel_cap(g);
            dst->b = aipl_channel_cap(b);
            dst->a = src->a;

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_white_balance_rgba4444(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         float ar, float ag, float ab)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + (i * pitch);
        uint16_t* dst = dst_ptr + (i * pitch);

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba4444_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_white_balance_argb_x16(&pix, ar, ag, ab);

            aipl_mve_storea_rgba4444_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba4444_px_t* src_ptr = input;
    aipl_rgba4444_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba4444_px_t* src = src_ptr + (i * pitch);
        aipl_rgba4444_px_t* dst = dst_ptr + (i * pitch);

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_rgba4444_px(&px, src);

            int16_t r = px.r * ar;
            int16_t g = px.g * ag;
            int16_t b = px.b * ab;

            px.r = aipl_channel_cap(r);
            px.g = aipl_channel_cap(g);
            px.b = aipl_channel_cap(b);

            aipl_packa_rgba4444_px(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_white_balance_rgba5551(const void* input, void* output,
                                         uint32_t pitch,
                                         uint32_t width, uint32_t height,
                                         float ar, float ag, float ab)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + (i * pitch);
        uint16_t* dst = dst_ptr + (i * pitch);

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_argb_x16_t pix;
            aipl_mve_loada_rgba5551_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_white_balance_argb_x16(&pix, ar, ag, ab);

            aipl_mve_storea_rgba5551_16px((uint8_t*)dst, &pix, tail_p);

            src += 16;
            dst += 16;
            cnt -= 16;
        }
    }
#else
    const aipl_rgba5551_px_t* src_ptr = input;
    aipl_rgba5551_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgba5551_px_t* src = src_ptr + (i * pitch);
        aipl_rgba5551_px_t* dst = dst_ptr + (i * pitch);

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_argb8888_px_t px;
            aipl_loada_rgba5551_px(&px, src);

            int16_t r = px.r * ar;
            int16_t g = px.g * ag;
            int16_t b = px.b * ab;

            px.r = aipl_channel_cap(r);
            px.g = aipl_channel_cap(g);
            px.b = aipl_channel_cap(b);

            aipl_packa_rgba5551_px(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_white_balance_rgb888(const void* input, void* output,
                                       uint32_t pitch,
                                       uint32_t width, uint32_t height,
                                       float ar, float ag, float ab)
{
#if AIPL_USE_MVE
    const uint8_t* src_ptr = input;
    uint8_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint8_t* src = src_ptr + (i * pitch) * 3;
        uint8_t* dst = dst_ptr + (i * pitch) * 3;

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb888_16px(&pix, src, tail_p);

            aipl_mve_white_balance_rgb_x16(&pix, ar, ag, ab);

            aipl_mve_store_rgb888_16px(dst, &pix, tail_p);

            src += 48;
            dst += 48;
            cnt -= 16;
        }
    }
#else
    const aipl_rgb888_px_t* src_ptr = input;
    aipl_rgb888_px_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        const aipl_rgb888_px_t* src = src_ptr + (i * pitch);
        aipl_rgb888_px_t* dst = dst_ptr + (i * pitch);

        for (uint32_t j = 0; j < width; ++j)
        {
            int16_t r = src->r * ar;
            int16_t g = src->g * ag;
            int16_t b = src->b * ab;

            dst->r = aipl_channel_cap(r);
            dst->g = aipl_channel_cap(g);
            dst->b = aipl_channel_cap(b);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

aipl_error_t aipl_white_balance_rgb565(const void* input, void* output,
                                       uint32_t pitch,
                                       uint32_t width, uint32_t height,
                                       float ar, float ag, float ab)
{
#if AIPL_USE_MVE
    const uint16_t* src_ptr = input;
    uint16_t* dst_ptr = output;

    for (uint32_t i = 0; i < height; ++i)
    {
        int32_t cnt = width;
        const uint16_t* src = src_ptr + (i * pitch);
        uint16_t* dst = dst_ptr + (i * pitch);

        while (cnt > 0)
        {
            mve_pred16_t tail_p = vctp8q(cnt);

            aipl_mve_rgb_x16_t pix;
            aipl_mve_load_rgb565_16px(&pix, (uint8_t*)src, tail_p);

            aipl_mve_white_balance_rgb_x16(&pix, ar, ag, ab);

            aipl_mve_store_rgb565_16px((uint8_t*)dst, &pix, tail_p);

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
        const aipl_rgb565_px_t* src = src_ptr + (i * pitch);
        aipl_rgb565_px_t* dst = dst_ptr + (i * pitch);

        for (uint32_t j = 0; j < width; ++j)
        {
            aipl_rgb888_px_t px;
            aipl_load_rgb565_px(&px, src);

            int16_t r = px.r * ar;
            int16_t g = px.g * ag;
            int16_t b = px.b * ab;

            px.r = aipl_channel_cap(r);
            px.g = aipl_channel_cap(g);
            px.b = aipl_channel_cap(b);

            aipl_pack_rgb565_px(dst, &px);

            ++src;
            ++dst;
        }
    }
#endif

    return AIPL_OK;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
