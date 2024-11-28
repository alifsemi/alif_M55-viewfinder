/**
 * @file aipl_image.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "aipl_image.h"
#include "aipl_video_alloc.h"
#include <stdlib.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void* aipl_image_allocate(uint32_t pitch, uint32_t height,
                                 aipl_color_format_t format);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
aipl_image_t aipl_image_create(uint32_t pitch, uint32_t width,
                               uint32_t height, aipl_color_format_t format)
{
    aipl_image_t image = { 0 };
    image.data = aipl_image_allocate(pitch, height, format);
    image.pitch = pitch;
    image.width = width;
    image.height = height;
    image.format = format;

    return image;
}

void aipl_image_destroy(aipl_image_t* image)
{
    aipl_video_free(image->data);
    image->data = NULL;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void* aipl_image_allocate(uint32_t pitch, uint32_t height,
                                 aipl_color_format_t format)
{
    /* YUV formats encode in 2x2 pixel so
       the image buffer has to have even pitch and height */
    if (aipl_color_format_space(format) == AIPL_SPACE_YUV)
    {
        pitch = pitch & 0x1 ? pitch + 1 : pitch;
        height = height & 0x1 ? height + 1 : height;
    }

    return aipl_video_alloc(pitch * height * aipl_color_format_depth(format) / 8);
}
