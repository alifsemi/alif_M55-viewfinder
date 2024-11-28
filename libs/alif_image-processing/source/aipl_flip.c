/**
 * @file aipl_flip.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "aipl_flip.h"
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

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
 aipl_error_t aipl_flip(const void* input, void* output,
                       uint32_t pitch,
                       uint32_t width, uint32_t height,
                       aipl_color_format_t format,
                       bool flip_horizontal, bool flip_vertical)
{
#if AIPL_USE_DAVE2D
    if (aipl_dave2d_format_supported(format))
    {
        d2_u32 ret = aipl_dave2d_texturing(input, output,
                            pitch,
                            width, height,
                            aipl_dave2d_format_to_mode(format),
                            width, height,
                            0,
                            flip_horizontal, flip_vertical,
                            false);

        return aipl_dave2d_error_convert(ret);
    }
#else
    // Software mode is not implemented
    return AIPL_ERROR;
#endif
}

aipl_error_t aipl_flip_img(const aipl_image_t* input,
                             aipl_image_t* output,
                             bool flip_horizontal, bool flip_vertical)
{
    if (output->format != input->format) 
    { 
        return AIPL_FORMAT_MISMATCH;
    }

    return aipl_flip(input->data, output->data,
                     input->pitch,
                     input->width, input->height,
                     input->format,
                     flip_horizontal, flip_vertical);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

