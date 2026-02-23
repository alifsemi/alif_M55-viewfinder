/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#include "leds.h"

#include "Driver_IO.h"
#include "board_defs.h"

// Green LED
extern ARM_DRIVER_GPIO ARM_Driver_GPIO_(BOARD_LEDRGB0_G_GPIO_PORT);
ARM_DRIVER_GPIO       *gpioDrvLedG = &ARM_Driver_GPIO_(BOARD_LEDRGB0_G_GPIO_PORT);

// Red LED
#if (BOARD_LEDRGB_COUNT > 1)
#define LEDS_RED_GPIO_PORT BOARD_LEDRGB1_R_GPIO_PORT
#define LEDS_RED_GPIO_PIN  BOARD_LEDRGB1_R_GPIO_PIN
#else
#define LEDS_RED_GPIO_PORT BOARD_LEDRGB0_R_GPIO_PORT
#define LEDS_RED_GPIO_PIN  BOARD_LEDRGB0_R_GPIO_PIN
#endif

extern ARM_DRIVER_GPIO ARM_Driver_GPIO_(LEDS_RED_GPIO_PORT);
ARM_DRIVER_GPIO       *gpioDrvLedR = &ARM_Driver_GPIO_(LEDS_RED_GPIO_PORT);

int leds_init(void)
{
    int32_t ret = gpioDrvLedG->Initialize(BOARD_LEDRGB0_G_GPIO_PIN, NULL);
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
    ret = gpioDrvLedR->Initialize(LEDS_RED_GPIO_PIN, NULL);
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }

    ret = gpioDrvLedG->PowerControl(BOARD_LEDRGB0_G_GPIO_PIN, ARM_POWER_FULL);
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
    ret = gpioDrvLedR->PowerControl(LEDS_RED_GPIO_PIN, ARM_POWER_FULL);
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }

    return ret;
}

void leds_set_green(bool state)
{
    gpioDrvLedG->SetValue(BOARD_LEDRGB0_G_GPIO_PIN, state ? GPIO_PIN_OUTPUT_STATE_HIGH : GPIO_PIN_OUTPUT_STATE_LOW);
}

void leds_set_red(bool state)
{
    gpioDrvLedR->SetValue(LEDS_RED_GPIO_PIN, state ? GPIO_PIN_OUTPUT_STATE_HIGH : GPIO_PIN_OUTPUT_STATE_LOW);
}

void leds_toggle_green(void)
{
    gpioDrvLedG->SetValue(BOARD_LEDRGB0_G_GPIO_PIN, GPIO_PIN_OUTPUT_STATE_TOGGLE);
}
