/**
 * @file aipl_crop.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <memory.h>

#include "RTE_Components.h"
#include CMSIS_device_header
#include <RTE_Device.h>

#include "aipl_crop.h"
#include "aipl_config.h"

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
aipl_error_t aipl_crop(const void* input, void* output,
                       uint32_t pitch,
                       uint32_t width, uint32_t height,
                       aipl_color_format_t format,
                       uint32_t left, uint32_t top,
                       uint32_t right, uint32_t bottom)
{
    // Check pointers
    if (input == NULL || output == NULL)
        return AIPL_ERROR;

	// Checking the boundary
	if( (left > right) || (right > width) || (top > bottom) || (bottom > height) )
		return AIPL_FRAME_OUT_OF_RANGE;

    uint32_t bpp = aipl_color_format_depth (format);

	// Check for no cropping
	if (left == 0 && top == 0 && right == width && bottom == height) {
	    // No-op if cropping and in-place
        size_t size = width * height * (bpp / 8);
	    if (input != output) {
	        memcpy(output, input, size);
	    }
        SCB_CleanInvalidateDCache_by_Addr(output, size);
	    return AIPL_OK;
	}

	// Updating the input frame column start
	uint8_t *ip_fb = (uint8_t *)input + (top * width * (bpp / 8));
    uint8_t *op_fb = (uint8_t *)output;

    uint32_t new_width = right - left;
    uint32_t new_hight = bottom - top;

    for(uint32_t i = 0; i < new_hight; ++i)
    {
        // Update row address
        const uint8_t *ip_fb_row = ip_fb + left * (bpp / 8);
        memmove(op_fb, ip_fb_row, new_width * (bpp / 8));

        // Update fb
        ip_fb += (width * (bpp / 8));
        op_fb += (new_width * (bpp / 8));
    }

    size_t size = new_width * new_hight * (bpp / 8);
    SCB_CleanInvalidateDCache_by_Addr(output, size);

	return AIPL_OK;
}

aipl_error_t aipl_crop_img(const aipl_image_t* input,
                       aipl_image_t* output,
                       uint32_t left, uint32_t top,
                       uint32_t right, uint32_t bottom)
{
    uint32_t new_width = right - left;
    uint32_t new_hight = bottom - top;
    if (new_width != output->width || new_hight != output->height)
    {
        return AIPL_SIZE_MISMATCH;
    }

    if (output->format != input->format) 
    { 
        return AIPL_FORMAT_MISMATCH;
    }

    return aipl_crop(input->data, output->data,
                     input->pitch,
                     input->width, input->height,
                     input->format,
                     left, top,
                     right, bottom);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
