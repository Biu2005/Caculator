/*
 * app_main.c
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

#include "app_main.h"

void App_RunCalculatorMode() {
	keypad[0][3] = '*';
	keypad[2][4] = 'B';
	char keyToDisplay;
	char buffer[17] = "";
	char bufferToShow[2] = "";
	int i = 0;
	int exit = 0;
	while (1) {
		keyToDisplay = keyPad_scan();
		if (keyToDisplay != 'c') {
			if (keyToDisplay == '=') {
				if (exit == 0) {
					buffer[i] = '\0';
					if (i > 0) { // chỉ xử lý khi có dữ liệu
						float result = Calculate(buffer);
						char ketqua[17];
						if (fabs(result - (int) result) < 1e-9) {
							int_to_str((long) result, ketqua, 10);
						} else {
							float_to_str(result, ketqua, 2);
						}
						LCD_setCursor(1, 16 - strlen(ketqua));
						LCD_puts(ketqua);
					}
					i = 0;
					exit = 1;
				} else {
					LCD_clear();
					row = 0;
					col = 0;
					break;
				}
			}

			else if (keyToDisplay == 'C') {
				LCD_clear();
				buffer[0] = '\0';
				bufferToShow[0] = '\0';
				row = 0;
				col = 0;
				exit = 0;
				continue;
			}

			else if (keyToDisplay == 'B') {
				if (i > 0) {
					i--;
					col--;
					buffer[i] = '\0';

					LCD_setCursor(0, col);
					LCD_sendChar(' ');
					LCD_setCursor(0, col);
				}
			} else {
				buffer[i] = keyToDisplay;
				bufferToShow[0] = keyToDisplay;
				bufferToShow[1] = '\0';
				LCD_setCursor(0, col);
				LCD_puts(bufferToShow);
				col++;
				i++;
				if (col >= 16) {
					col = 0;
				}
				if (i >= sizeof(buffer) - 1) {
					i = 0;
				}
			}
		}
	}
}

void App_RunSolverMode() {
	keypad[0][3] = 'x';
	keypad[2][4] = '*';
	char keyMode2;
	int exit = 0;
	int i = 0;
	char buffer[17] = "";
	char bufferToShow[2] = "";
	while (1) {
		keyMode2 = keyPad_scan();
		if (keyMode2 != 'c') {
			if (keyMode2 == '=') {
				if (exit == 0) {
					if (i > 0) {
						solve_the_equation(buffer);
					}
					exit = 1;
				} else {
					LCD_clear();
					col = 0;
					row = 0;
					break;
				}
			} else if (keyMode2 == 'C') {
				LCD_clear();
				buffer[0] = '\0';
				bufferToShow[0] = '\0';
				row = 0;
				col = 0;
				i = 0;
				exit = 0;
				continue;
			} else {
				buffer[i] = keyMode2;
				bufferToShow[0] = keyMode2;
				bufferToShow[1] = '\0';
				LCD_setCursor(0, col);
				LCD_puts(bufferToShow);
				col++;
				i++;
				if (col >= 16) {
					col = 0;
				}
				if (i >= sizeof(buffer) - 1) {
					i = 0;
				}
			}
		}
	}
}
