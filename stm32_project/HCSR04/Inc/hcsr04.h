/*
 * hcsr04.h
 *
 *  Created on: Jan 23, 2026
 *      Author: ivkov
 */

#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_

#include "main.h"
#include <stdint.h>

void  HCSR04_Init(TIM_HandleTypeDef *htim, uint32_t channel);
void  HCSR04_Trigger(void);
uint8_t HCSR04_IsReady(void);
uint32_t HCSR04_GetPulseUs(void);
float HCSR04_GetDistanceCm(void);
void  HCSR04_OnCaptureIRQ(TIM_HandleTypeDef *htim);
uint8_t HCSR04_HasTimedOut(uint32_t timeout_ms);

#endif /* INC_HCSR04_H_ */
