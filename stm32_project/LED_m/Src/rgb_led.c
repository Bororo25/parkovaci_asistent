/*
 * rgb_led.c
 *
 *  Created on: Jan 27, 2026
 *      Author: marti
 */

#include "rgb_led.h"

static void rgb_set(uint8_t r, uint8_t g, uint8_t b)
{
    HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, r ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, g ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, b ? GPIO_PIN_RESET : GPIO_PIN_SET);
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
