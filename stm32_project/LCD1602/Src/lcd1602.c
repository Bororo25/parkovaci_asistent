/*
 * lcd1602.c
 *
 *  Created on: Jan 26, 2026
 *      Author: boris
 */


#include "lcd1602.h"


static void lcd_short_delay(void)
{
	for(volatile int i = 0; i < 250; i++) { __NOP(); }
}

static void lcd_pulse_en(void)
{
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
	lcd_short_delay();
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
	lcd_short_delay();
}

static void lcd_write4(uint8_t nibble) // lower 4 bits
{
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (nibble & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (nibble & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (nibble & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (nibble & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	lcd_pulse_en();
}

static void lcd_send(uint8_t value, uint8_t rs)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, rs ? GPIO_PIN_SET : GPIO_PIN_RESET);

	lcd_write4((value >> 4) & 0x0F);
	lcd_write4(value & 0x0F);
}

static void lcd_cmd(uint8_t cmd)
{
	lcd_send(cmd, 0);

	if(cmd == 0x01 || cmd == 0x02)
	{
		HAL_Delay(2);
	}
	else
	{
		lcd_short_delay();
	}
}

static void lcd_data(uint8_t data)
{
	lcd_send(data, 1);
}

/* ---- Public API ---- */

void LCD1602_Init(void)
{
	// Po zapnutí potrebuje LCD ~40-50ms
	HAL_Delay(50);

	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_E_GPIO_Port,  LCD_E_Pin,  GPIO_PIN_RESET);

	lcd_write4(0x03); HAL_Delay(5);
	lcd_write4(0x03); HAL_Delay(5);
	lcd_write4(0x03); HAL_Delay(1);
	lcd_write4(0x02); HAL_Delay(1);

	lcd_cmd(0x28);

	lcd_cmd(0x0C);

	lcd_cmd(0x06);

	lcd_cmd(0x01);
}

void LCD1602_Clear(void)
{
	lcd_cmd(0x01);
}

void LCD1602_Home(void)
{
	lcd_cmd(0x02);
}

void LCD1602_SetCursor(uint8_t row, uint8_t col)
{
	static const uint8_t row_offsets[] = {0x00, 0x40};

	if(row > 1) row = 1;
	if(col > 15) col = 15;

	lcd_cmd(0x80 | (row_offsets[row] + col));
}

void LCD1602_WriteChar(char c)
{
	lcd_data((uint8_t)c);
}

void LCD1602_Print(const char *s)
{
	while(*s)
	{
		lcd_data((uint8_t)*s++);
	}
}
