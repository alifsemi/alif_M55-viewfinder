/**
 * @file disp.h
 *
 */

#ifndef DISP_H
#define DISP_H

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
#define MY_DISP_HOR_RES      (RTE_PANEL_HACTIVE_TIME)
#define MY_DISP_VER_RES      (RTE_PANEL_VACTIVE_LINE)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* Initialize low level display driver */
int display_init(void);

/* Set next frame display duration */
void disp_set_next_frame_duration(uint32_t duration);

/* Display the next prerendered frame frame buffer */
void disp_next_frame(void);

/* Get pointer to display active buffer */
void* disp_active_buffer(void);

/* Get pointer to display inactive buffer */
void* disp_inactive_buffer(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*DISP_H*/
