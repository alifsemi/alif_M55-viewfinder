/**
 * @file aipl_rotate.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "aipl_rotate.h"
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
 aipl_error_t aipl_rotate(const void* input, void* output,
                       uint32_t pitch,
                       uint32_t width, uint32_t height,
                       aipl_color_format_t format,
                       aipl_rotation_t rotation)
{
#if AIPL_USE_DAVE2D
    if (aipl_dave2d_format_supported(format))
    {
        d2_u32 ret = aipl_dave2d_texturing(input, output,
                            pitch,
                            width, height,
                            aipl_dave2d_format_to_mode(format),
                            width, height,
                            rotation,
                            false, false,
                            false);

        return aipl_dave2d_error_convert(ret);
    }
#else
    // Software mode is not implemented
    return AIPL_ERROR;
#endif
}

aipl_error_t aipl_rotate_img(const aipl_image_t* input,
                             aipl_image_t* output,
                             aipl_rotation_t rotation)
{
    if (output->format != input->format)
    {
        return AIPL_FORMAT_MISMATCH;
    }

    if ((rotation == AIPL_ROTATE_0 || rotation == AIPL_ROTATE_180) &&
        input->width != output->width || input->height != output->height)
    {
        return AIPL_ERROR;
    }

    if ((rotation == AIPL_ROTATE_90 || rotation == AIPL_ROTATE_270) &&
        input->width != output->height || input->height != output->width)
    {
        return AIPL_ERROR;
    }

    return aipl_rotate(input->data, output->data,
                     input->pitch,
                     input->width, input->height,
                     input->format,
                     rotation);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

