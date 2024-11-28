/**
 * @file aipl_video_alloc.h
 *
 */

#ifndef AIPL_VIDEO_ALLOC_H
#define AIPL_VIDEO_ALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * Allocate a buffer in the video memory
 *
 * In the case config option AIPL_CUSTOM_VIDEO_ALLOC is set to 1,
 * should be provided by the user
 *
 * @param size desired buffer size
 * @return pointer to the allocated memory; NULL on failure
 */
void* aipl_video_alloc(uint32_t size);

/**
 * Free a buffer in the video memory
 *
 * In the case config option AIPL_CUSTOM_VIDEO_ALLOC is set to 1,
 * should be provided by the user
 *
 * @param ptr buffer pointer
 */
void aipl_video_free(void* ptr);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  /* AIPL_VIDEO_ALLOC_H */
