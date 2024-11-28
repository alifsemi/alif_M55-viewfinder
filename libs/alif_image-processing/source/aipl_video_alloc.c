/**
 * @file aipl_video_alloc.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "aipl_config.h"

#if !AIPL_CUSTOM_VIDEO_ALLOC
#include "aipl_video_alloc.h"

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
void* aipl_video_alloc(uint32_t size)
{
    return malloc(size);
}

void aipl_video_free(void* ptr)
{
    free(ptr);
}
/**********************
 *   STATIC FUNCTIONS
 **********************/
#endif
