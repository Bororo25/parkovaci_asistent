/*
 * buzzer.h
 *
 *  Created on: Jan 27, 2026
 *      Author: marti
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void Buzzer_Init(void);   // Inicializácia GPIO
void Buzzer_On(void);     // Zapni zvuk
void Buzzer_Off(void);    // Vypni zvuk

#ifdef __cplusplus
}
#endif

#endif /* INC_BUZZER_H_ */
