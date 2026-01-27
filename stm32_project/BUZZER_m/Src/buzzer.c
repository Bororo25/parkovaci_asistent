/*
 * buzzer.c
 *
 *  Created on: Jan 27, 2026
 *      Author: marti
 */

#include "buzzer.h"

/* ---- Internal helper ---- */
static void buzzer_set(uint8_t state)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/* ---- Public API ---- */

void Buzzer_Init(void)
{
    Buzzer_Off();
}

void Buzzer_On(void)
{
    buzzer_set(1);  // HIGH = bzučiak pípa
}

void Buzzer_Off(void)
{
    buzzer_set(0);  // LOW = ticho
}

