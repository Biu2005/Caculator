/*
 * LCD_driver.c
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

/*
 * LCD_casio.c
 *
 *  Created on: Oct 3, 2025
 *      Author: ADMIN
 */
#include "LCD_driver.h"

int row = 0;
int col = 0;

// Privte function
static void LCD_sendNibble_BareMetal(uint8_t data) {
	HAL_GPIO_WritePin(GPIOA, D4_Pin,
			(data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, D5_Pin,
			(data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, D6_Pin,
			(data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, D7_Pin,
			(data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, EN_Pin, GPIO_PIN_RESET);
}

static void LCD_sendNibble(uint8_t data) {
	HAL_GPIO_WritePin(GPIOA, D4_Pin,
			(data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, D5_Pin,
			(data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, D6_Pin,
			(data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, D7_Pin,
			(data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, EN_Pin, GPIO_PIN_SET);
	vTaskDelay(pdMS_TO_TICKS(5));
	HAL_GPIO_WritePin(GPIOA, EN_Pin, GPIO_PIN_RESET);
}

static void LCD_sendByte(uint8_t data) {
	LCD_sendNibble(data >> 4);
	LCD_sendNibble(data);
}

static void LCD_sendByte_BareMetal(uint8_t data) {
	LCD_sendNibble_BareMetal(data >> 4);
	LCD_sendNibble_BareMetal(data);
}

static void LCD_sendCmd(uint8_t data) {
	HAL_GPIO_WritePin(GPIOA, RS_Pin, GPIO_PIN_RESET);
	LCD_sendByte(data);
}

// Public function
void LCD_init() {
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOA, RS_Pin, GPIO_PIN_RESET);
	LCD_sendByte_BareMetal(0x33);
	LCD_sendByte_BareMetal(0x32);
	LCD_sendByte_BareMetal(0x28);
	LCD_sendByte_BareMetal(0x06);
	LCD_sendByte_BareMetal(0x0C);
	LCD_sendByte_BareMetal(0x01);
	HAL_Delay(2);
}

void LCD_clear() {
	LCD_sendCmd(0x01);
	vTaskDelay(pdMS_TO_TICKS(5));
}

void LCD_setCursor(char row, char col) {
	char val = (row == 0) ? 0x00 : 0x40;
	val += col;
	LCD_sendCmd(0x80 | val);
}

void LCD_sendChar(uint8_t data) {
	HAL_GPIO_WritePin(GPIOA, RS_Pin, GPIO_PIN_SET);
	LCD_sendByte(data);
}

void LCD_puts(char *data) {
	while (data[0] != '\0') {
		LCD_sendChar(data[0]);
		data++;
	}
}

void LCD_scroll(char isScroll) {
	if (isScroll) {
		LCD_sendCmd(0x04 | 0x01);
	}
}

