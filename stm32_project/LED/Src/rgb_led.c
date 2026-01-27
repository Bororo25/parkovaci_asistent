/*
 * rgb_led.c
 *
 *  Created on: Jan 27, 2026
 *      Author: marti
 */

#include "rgb_led.h"

/* ---- Internal helper ---- */

static void rgb_set(uint8_t r, uint8_t g, uint8_t b)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, r ? GPIO_PIN_SET : GPIO_PIN_RESET); // R
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, g ? GPIO_PIN_SET : GPIO_PIN_RESET); // G
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, b ? GPIO_PIN_SET : GPIO_PIN_RESET); // B
}

/* ---- Public API ---- */

void RGB_LED_Init(void)
{
    RGB_LED_Off();
}

void RGB_LED_Off(void)
{
    rgb_set(0, 0, 0);
}

void RGB_LED_Red(void)
{
    rgb_set(1, 0, 0);
}

void RGB_LED_Green(void)
{
    rgb_set(0, 1, 0);
}

void RGB_LED_Blue(void)
{
    rgb_set(0, 0, 1);
}

void RGB_LED_Yellow(void)
{
    rgb_set(1, 1, 0);
}
