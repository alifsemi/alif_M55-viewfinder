/**
 * @file image.c
 */

/*********************
 *      INCLUDES
 *********************/
#include "RTE_Components.h"
#include CMSIS_device_header
#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "aipl_dave2d.h"
#include "disp.h"
#if __ARM_FEATURE_MVE & 3
#include "arm_mve.h"
#endif
#include "aipl_color_conversion.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    uint32_t x;
    uint32_t y;
    void* image;
    uint32_t pitch;
    uint32_t width;
    uint32_t height;
} graph_image_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void dave2d_image_draw(uint32_t format, const graph_image_t* image);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void aipl_dave2d_prepare(void)
{
    d2_device* handle = aipl_dave2d_handle();
    /* Prepare frame buffer */
    d2_framebuffer(handle, disp_inactive_buffer(),
                    RTE_PANEL_HACTIVE_TIME,
                    RTE_PANEL_HACTIVE_TIME,
                    RTE_PANEL_VACTIVE_LINE, d2_mode_rgb565);
    /* Set background */
    d2_clear(handle, 0x00fefefe);
}

void aipl_dave2d_render(void)
{
    d2_device* handle = aipl_dave2d_handle();

    /* Close render buffer which has just captured all render commands */
    d2_endframe(handle);
    /* Start HW rendering of the closed frame */
    d2_startframe(handle);
    /* Wait until the render finishes */
    d2_endframe(handle);

    /* Switch to the next display buffer */
    disp_next_frame();
}

void aipl_image_draw(uint32_t x, uint32_t y, const aipl_image_t* image)
{
    graph_image_t img = {
        .x = x,
        .y = y,
        .image = image->data,
        .pitch = image->pitch,
        .width = image->width,
        .height = image->height
    };

    // If format is not supported by D/AVE2D, convert it to RGB565
    if (aipl_dave2d_format_supported(image->format))
    {
        dave2d_image_draw(aipl_dave2d_format_to_mode(image->format), &img);
    }
    else
    {
        aipl_image_t cnv_img;
        aipl_error_t aipl_ret = aipl_image_create(&cnv_img, image->width,
                                                  image->width,
                                                  image->height,
                                                  AIPL_COLOR_RGB565);
        if (aipl_ret != AIPL_ERR_OK)
        {
            printf("\r\nError: Not enough memory to allocate conversion"
                    " buffer for image drawing\r\n");
            return;
        }

        aipl_ret = aipl_color_convert_img(image, &cnv_img);
        if (aipl_ret != AIPL_ERR_OK)
        {
            printf("\r\nError: Conversion to RGB565 during drawing falied (%s)\r\n",
                    aipl_error_str(aipl_ret));
        }

        img.image = cnv_img.data;

        dave2d_image_draw(d2_mode_rgb565, &img);

        aipl_image_destroy(&cnv_img);
    }
}

void aipl_image_draw_clut(uint32_t x, uint32_t y, const aipl_image_t* image)
{
    if (image->format != AIPL_COLOR_ALPHA8)
        return;

    graph_image_t img = {
        .x = x,
        .y = y,
        .image = image->data,
        .pitch = image->pitch,
        .width = image->width,
        .height = image->height
    };

    if (aipl_dave2d_format_supported(image->format))
    {
        dave2d_image_draw(d2_mode_i8 | d2_mode_clut, &img);
    }
}

void aipl_dave2d_set_clut(const uint8_t* clut, aipl_color_format_t format)
{
    if (format != AIPL_COLOR_ARGB8888 && format != AIPL_COLOR_RGB565)
        return;

    d2_device* handle = aipl_dave2d_handle();

    d2_s32 ret = d2_settexclut(handle, (d2_color*)clut);
    if (ret != D2_OK)
    {
        return;
    }

    d2_settexclut_format(handle, aipl_dave2d_format_to_mode(format));
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void dave2d_image_draw(uint32_t mode, const graph_image_t* image)
{
    int32_t dsize = image->pitch * image->height * aipl_dave2d_mode_px_size(mode);
    SCB_CleanInvalidateDCache_by_Addr(image->image, dsize);

    d2_device* handle = aipl_dave2d_handle();

    d2_cliprect(handle, (d2_border)image->x, (d2_border)image->y,
                (d2_border)image->x + image->width - 1,
                (d2_border)image->y + image->height - 1);

    d2_u8 alpha_mode = aipl_dave2d_mode_has_alpha(mode) ? d2_to_copy : d2_to_one;
    d2_settextureoperation(handle, alpha_mode, d2_to_copy, d2_to_copy, d2_to_copy);

    d2_settexture(handle, image->image, image->pitch, image->width,
                  image->height, mode);

    d2_settexturemode(handle, d2_tm_filter);
    d2_setfillmode(handle, d2_fm_texture);
    d2_setblendmode(handle, d2_bm_alpha, d2_bm_one_minus_alpha);
    d2_setalphablendmode(handle, d2_bm_one, d2_bm_one_minus_alpha);

    d2_settexturemapping(handle, D2_FIX4(image->x), D2_FIX4(image->y),
                         D2_FIX16(0), D2_FIX16(0),
                         D2_FIX16(1), D2_FIX16(0),
                         D2_FIX16(0), D2_FIX16(1));

    d2_renderquad(handle, D2_FIX4(image->x), D2_FIX4(image->y),
                  D2_FIX4(image->x + image->width - 1), D2_FIX4(image->y),
                  D2_FIX4(image->x + image->width - 1), D2_FIX4(image->y + image->height - 1),
                  D2_FIX4(image->x), D2_FIX4(image->y + image->height - 1),
                  0);
}
