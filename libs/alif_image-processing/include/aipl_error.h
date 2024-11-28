/**
 * @file aipl_error.h
 *
 * TODO: expand and implement required functions
 */

#ifndef AIPL_ERROR_H
#define AIPL_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    AIPL_OK = 0,
    AIPL_NO_MEM,
    AIPL_UNSUPPORTED_FORMAT,
    AIPL_FORMAT_MISMATCH,
    AIPL_SIZE_MISMATCH,
    AIPL_FRAME_OUT_OF_RANGE,
    AIPL_ERROR,
    AIPL_D2_ERROR,
} aipl_error_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  /* AIPL_ERROR_H */
