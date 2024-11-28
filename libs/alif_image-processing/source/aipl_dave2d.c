/**
 * @file aipl_dave2d.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "RTE_Components.h"
#include CMSIS_device_header
#include "aipl_dave2d.h"
#include <stdlib.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    int32_t x;
    int32_t y;
} point_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
#if !AIPL_CUSTOM_DAVE2D_INIT
static d2_device* d2_handle;
#endif

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
#if !AIPL_CUSTOM_DAVE2D_INIT
d2_s32 aipl_dave2d_init(void)
{
    if (d2_handle != NULL)
    {
        return D2_NOMEMORY;
    }

    d2_u32 flags = 0;

    d2_handle = d2_opendevice(flags);
    if (d2_handle == NULL)
    {
        return D2_NOMEMORY;
    }

    d2_s32 result = d2_inithw(d2_handle, flags);
    if (result != D2_OK)
    {
        d2_closedevice(d2_handle);
        d2_handle = NULL;
    }

    return result;
}

d2_device* aipl_dave2d_handle(void)
{
    return d2_handle;
}
#endif

bool aipl_dave2d_mode_has_alpha(d2_u32 mode)
{
    mode &= ~d2_mode_rle & ~d2_mode_clut;

    switch (mode)
    {
        case d2_mode_argb8888:
        case d2_mode_argb4444:
        case d2_mode_argb1555:
        case d2_mode_rgba8888:
        case d2_mode_rgba4444:
        case d2_mode_rgba5551:
        case d2_mode_ai44:
            return true;

        case d2_mode_alpha8:
        case d2_mode_alpha4:
        case d2_mode_alpha2:
        case d2_mode_alpha1:
        case d2_mode_i8:
        case d2_mode_i4:
        case d2_mode_i2:
        case d2_mode_i1:
        case d2_mode_rgb565:
        case d2_mode_rgb888:
        case d2_mode_rgb444:
        case d2_mode_rgb555:
        default:
            return false;
    }
}

bool aipl_dave2d_format_supported(aipl_color_format_t format)
{
    format &= ~AIPL_COLOR_RLE;

    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
        case AIPL_COLOR_RGBA8888:
        case AIPL_COLOR_ARGB4444:
        case AIPL_COLOR_ARGB1555:
        case AIPL_COLOR_RGBA4444:
        case AIPL_COLOR_RGBA5551:
        case AIPL_COLOR_RGB565:
            return true;

        default:
            return false;
    }
}

d2_u32 aipl_dave2d_format_to_mode(aipl_color_format_t format)
{
    bool rle = format & AIPL_COLOR_RLE;
    format &= ~AIPL_COLOR_RLE;

    d2_u32 res;
    switch (format)
    {
        /* Alpha color formats */
        case AIPL_COLOR_ALPHA8:
            res = d2_mode_alpha8;
            break;
        /* RGB color formats */
        case AIPL_COLOR_ARGB8888:
            res = d2_mode_argb8888;
            break;
        case AIPL_COLOR_RGBA8888:
            res = d2_mode_rgba8888;
            break;
        case AIPL_COLOR_ARGB4444:
            res = d2_mode_argb4444;
            break;
        case AIPL_COLOR_ARGB1555:
            res = d2_mode_argb1555;
            break;
        case AIPL_COLOR_RGBA4444:
            res = d2_mode_rgba4444;
            break;
        case AIPL_COLOR_RGBA5551:
            res = d2_mode_rgba5551;
            break;
        case AIPL_COLOR_RGB565:
            res = d2_mode_rgb565;
            break;

        default:
            return AIPL_COLOR_UNKNOWN;
    }

    if (rle)
    {
        res |= d2_mode_rle;
    }

    return res;
}

d2_u32 aipl_dave2d_mode_px_size(d2_u32 mode)
{
    switch (mode)
    {
        case d2_mode_argb8888:
        case d2_mode_rgba8888:
            return 4;

        case d2_mode_alpha8:
        case d2_mode_i8:
        case d2_mode_ai44:
            return 1;

        default:
            return 2;
    }
}

d2_u32 aipl_dave2d_color_mode_convert(const void* input, void* output,
                                      uint32_t pitch,
                                      uint32_t width, uint32_t height,
                                      d2_u32 input_mode,
                                      d2_u32 output_mode)
{
    SCB_CleanInvalidateDCache_by_Addr((volatile void*)input, pitch * height
                                             * aipl_dave2d_mode_px_size(input_mode));

    d2_device* handle = aipl_dave2d_handle();

    /* Start rendering current buffer */
    d2_startframe(handle);

    /* Get current framebuffer info */
    void* frmbf_ptr;
    d2_s32 frmbf_pitch;
    d2_u32 frmbf_width;
    d2_u32 frmbf_height;
    d2_s32 frmbf_format;
    d2_getframebuffer(handle, &frmbf_ptr, &frmbf_pitch,
                      &frmbf_width, &frmbf_height, &frmbf_format);

    /* Set output as framebuffer */
    d2_framebuffer(handle, output, pitch, width, height,
                    output_mode);

    d2_setblitsrc(handle, (void*)input, pitch, width, height,
                    input_mode);

    d2_blitcopy(handle, width, height, 0, 0,
                D2_FIX4(width), D2_FIX4(height), 0, 0, 0);

    /* Wait until the prevous render finishes */
    d2_endframe(handle);

    /* Start the convertion */
    d2_startframe(handle);

    /* Restore old framebuffer */
    d2_framebuffer(handle, frmbf_ptr, frmbf_pitch,
                   frmbf_width, frmbf_height, frmbf_format);

    /* Wait until convertion finishes */
    d2_endframe(handle);
}

d2_u32 aipl_dave2d_texturing(const void* input, void* output,
                             uint32_t pitch,
                             uint32_t width, uint32_t height,
                             d2_u32 format,
                             uint32_t output_width, uint32_t output_height,
                             int32_t rotation,
                             bool flip_u, bool flip_v,
                             bool interpolate)
{
    d2_device* handle = aipl_dave2d_handle();

    /* Start rendering current buffer */
    d2_startframe(handle);

    /* Get current framebuffer info */
    void* frmbf_ptr;
    d2_s32 frmbf_pitch;
    d2_u32 frmbf_width;
    d2_u32 frmbf_height;
    d2_s32 frmbf_format;
    d2_getframebuffer(handle, &frmbf_ptr, &frmbf_pitch,
                      &frmbf_width, &frmbf_height, &frmbf_format);

    /* Prepare input image as texture*/
    d2_u8 alpha_mode = aipl_dave2d_mode_has_alpha(format) ? d2_to_copy : d2_to_one;
    d2_settextureoperation(handle, alpha_mode, d2_to_copy, d2_to_copy, d2_to_copy);

    d2_settexture(handle, (void*)input,
                 pitch, width, height,
                 format);

    d2_settexturemode(handle, interpolate ? d2_tm_filter : 0);
    d2_setfillmode(handle, d2_fm_texture);

    /* Texture points in clockwise order and mapping parameters */
    point_t p[4];

    d2_s32 dxu; d2_s32 dxv;
    d2_s32 dyu; d2_s32 dyv;

    if (rotation == 0) {
        /* Set output as framebuffer */
        d2_framebuffer(handle, output,
                       output_width, output_width, output_height,
                       format);

        p[0].x =  0;                    p[0].y = 0;
        p[1].x = output_width - 1;      p[1].y = 0;
        p[2].x = output_width - 1;      p[2].y = output_height - 1;
        p[3].x = 0;                     p[3].y = output_height - 1;

        dxu = D2_FIX16(1);      dxv = 0;
        dyu = 0;                dyv = D2_FIX16(1);
    }
    if (rotation == 90) {
        /* Set output as framebuffer */
        d2_framebuffer(handle, output,
                       output_height, output_height, output_width,
                       format);

        p[0].x = output_height - 1;     p[0].y = 0;
        p[1].x = output_height - 1;     p[1].y = output_width - 1;
        p[2].x = 0;                     p[2].y = output_width - 1;
        p[3].x = 0;                     p[3].y = 0;

        dxu = 0;                dxv = D2_FIX16(1);
        dyu = -D2_FIX16(1);     dyv = 0;
    }
    if (rotation == 180)
    {
        /* Set output as framebuffer */
        d2_framebuffer(handle, output,
                       output_width, output_width, output_height,
                       format);

        p[0].x = output_width - 1;      p[0].y = output_height - 1;
        p[1].x = 0;                     p[1].y = output_height - 1;
        p[2].x = 0;                     p[2].y = 0;
        p[3].x = output_width - 1;      p[3].y = 0;

        dxu = -D2_FIX16(1);     dxv = 0;
        dyu = 0;                dyv = -D2_FIX16(1);
    }
    if (rotation == 270)
    {
        /* Set output as framebuffer */
        d2_framebuffer(handle, output,
                       output_height, output_height, output_width,
                       format);
        p[0].x = 0;                     p[0].y = output_width - 1;
        p[1].x = 0;                     p[1].y = 0;
        p[2].x = output_height - 1;     p[2].y = 0;
        p[3].x = output_height - 1;     p[3].y = output_width - 1;

        dxu = 0;                dxv = -D2_FIX16(1);
        dyv = 0;                dyu = D2_FIX16(1);
    }

    /* Apply scaling */
    if(width != output_width)
    {
        dxu = (dxu * width) / output_width;
        dxv = (dxv * width) / output_width;
    }
    if(height != output_height)
    {
        dyu = (dyu * height) / output_height;
        dyv = (dyv * height) / output_height;
    }

    /* Apply flipping */
    d2_s32 u0 = 0; d2_s32 v0 = 0;
    if(flip_u)
    {
        dxu = -dxu;
        u0 = D2_FIX16(output_width);
    }
    if(flip_v)
    {
        dyv = -dyv;
        v0 = D2_FIX16(output_height);
    }

    d2_setblendmode(handle, d2_bm_alpha, d2_bm_one_minus_alpha);
    d2_setalphablendmode(handle, d2_bm_one, d2_bm_one_minus_alpha);

    d2_settexturemapping(handle,
                         D2_FIX4(p[0].x), D2_FIX4(p[0].y),
                         u0, v0,
                         dxu, dxv,
                         dyu, dyv
                        );

    d2_renderquad(handle,
                  (d2_point)D2_FIX4(p[0].x),
                  (d2_point)D2_FIX4(p[0].y),
                  (d2_point)D2_FIX4(p[1].x),
                  (d2_point)D2_FIX4(p[1].y),
                  (d2_point)D2_FIX4(p[2].x),
                  (d2_point)D2_FIX4(p[2].y),
                  (d2_point)D2_FIX4(p[3].x),
                  (d2_point)D2_FIX4(p[3].y),
                  0);

    /* Wait until the prevous render finishes */
    d2_endframe(handle);

    /* Start the convertion */
    d2_startframe(handle);

    /* Restore old framebuffer */
    d2_framebuffer(handle, frmbf_ptr, frmbf_pitch,
                   frmbf_width, frmbf_height, frmbf_format);

    /* Wait until convertion finishes */
    d2_endframe(handle);
}

aipl_error_t aipl_dave2d_error_convert(d2_s32 error)
{
    switch (error)
    {
        case D2_OK:
            return AIPL_OK;

        case D2_NOMEMORY:
            return AIPL_NO_MEM;

        default:
            return AIPL_D2_ERROR;
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
