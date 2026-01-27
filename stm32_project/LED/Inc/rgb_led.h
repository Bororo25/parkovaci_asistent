/*
 * rgb_led.h
 *
 *  Created on: Jan 27, 2026
 *      Author: marti
 */

#ifndef INC_RGB_LED_H_
#define INC_RGB_LED_H_

#include "main.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void RGB_LED_Init(void);

void RGB_LED_Off(void);
void RGB_LED_Red(void);
void RGB_LED_Green(void);
void RGB_LED_Blue(void);
void RGB_LED_Yellow(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_RGB_LED_H_ */
