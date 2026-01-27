#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_

#include "main.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void LCD1602_Init(void);
void LCD1602_Clear(void);
void LCD1602_Home(void);

void LCD1602_SetCursor(uint8_t row, uint8_t col);
void LCD1602_Print(const char *s);

void LCD1602_WriteChar(char c);

#ifdef __cplusplus
}
#endif

#endif
