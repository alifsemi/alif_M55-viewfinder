/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#ifndef LEDS_H_
#define LEDS_H_

#include <stdint.h>
#include <stdbool.h>

int leds_init(void);
void leds_set_green(bool state);
void leds_set_red(bool state);
void leds_toggle_green(void);

#endif
