/**
 * @file aipl_image.h
 *
 */

#ifndef AIPL_IMAGE_H
#define AIPL_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "aipl_color_formats.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    void* data;
    uint32_t pitch;
    uint32_t width;
    uint32_t height;
    aipl_color_format_t format;
} aipl_image_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * Create AIPL image structure. Allocate image buffer in videomemory
 *
 * @param pitch  image pitch
 * @param width  image width
 * @param height image height
 * @param format image format
 * @return AIPL image structure
 */
aipl_image_t aipl_image_create(uint32_t pitch, uint32_t width,
                               uint32_t height, aipl_color_format_t format);

/**
 * Deallocate image buffer
 *
 * @param image image pointer
 */
void aipl_image_destroy(aipl_image_t* image);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  /* AIPL_IMAGE_H */
