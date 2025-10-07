/*
 * keypad.c
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

#include "keypad.h"

// Private Data
char keypad[4][5] = { { '1', '5', '9', 'x', ')' }, { '2', '6', '0', ':', 'C' },
		{ '3', '7', '+', '=', 'B' }, { '4', '8', '-', '(', '.' } };
static GPIO_TypeDef *colPort[5] = { GPIOB, GPIOB, GPIOB, GPIOB, GPIOB };
static uint16_t colPin[5] = { PA0_Pin, PA1_Pin, PA2_Pin, PA3_Pin, PA4_Pin };

static GPIO_TypeDef *rowPort[4] = { GPIOA, GPIOA, GPIOA, GPIOA };
static uint16_t rowPin[4] = { PA5_Pin, PA6_Pin, PA7_Pin, PA8_Pin };

//Private function
static void set_all_row_high() {
	for (int i = 0; i < 4; i++) {
		HAL_GPIO_WritePin(rowPort[i], rowPin[i], GPIO_PIN_SET);
	}
}

//Public function
char keyPad_scan(void) {
	for (int i = 0; i < 4; i++) {
		set_all_row_high();
		HAL_GPIO_WritePin(rowPort[i], rowPin[i], GPIO_PIN_RESET);

		for (int j = 0; j < 5; j++) {
			if (HAL_GPIO_ReadPin(colPort[j], colPin[j]) == GPIO_PIN_RESET) {
				vTaskDelay(pdMS_TO_TICKS(20));
				if (HAL_GPIO_ReadPin(colPort[j], colPin[j]) == GPIO_PIN_RESET) {
					while (HAL_GPIO_ReadPin(colPort[j], colPin[j])
							== GPIO_PIN_RESET) {
						vTaskDelay(pdMS_TO_TICKS(5));
					}
					return keypad[i][j];
				}
			}
		}
	}
	return 'c';
}
