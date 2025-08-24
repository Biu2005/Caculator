/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdarg.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "string.h"
#include "semphr.h"
#include "math.h"
#include "stdbool.h"
#include "math.h"
#include "ctype.h"
//#define EPS 1e-4f
//#define STEP 1.0f
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char keypad[4][5] = { { '1', '5', '9', 'x', ')' }, { '2', '6', '0', ':', 'C' },
		{ '3', '7', '+', '=', 'B' }, { '4', '8', '-', '(', '.' } };
GPIO_TypeDef *colPort[5] = { GPIOB, GPIOB, GPIOB, GPIOB, GPIOB };
uint16_t colPin[5] = { PA0_Pin, PA1_Pin, PA2_Pin, PA3_Pin, PA4_Pin };

GPIO_TypeDef *rowPort[4] = { GPIOA, GPIOA, GPIOA, GPIOA };
uint16_t rowPin[4] = { PA5_Pin, PA6_Pin, PA7_Pin, PA8_Pin };

int row = 0;
int col = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void LCD_sendCmd(uint8_t data);
void LCD_sendChar(uint8_t data);
void LCD_sendByte(uint8_t data);
void LCD_sendNibble(uint8_t data);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void vApplicationMallocFailedHook(void) {
	taskDISABLE_INTERRUPTS();
	for (;;)
		;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
	(void) xTask;
	(void) pcTaskName;
	taskDISABLE_INTERRUPTS();
	for (;;)
		;
}

void LCD_sendNibble_BareMetal(uint8_t data) {
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

void LCD_sendByte_BareMetal(uint8_t data) {
	LCD_sendNibble_BareMetal(data >> 4);
	LCD_sendNibble_BareMetal(data);
}

void LCD_init_BareMetal() {
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

void LCD_sendCmd(uint8_t data) {
	HAL_GPIO_WritePin(GPIOA, RS_Pin, GPIO_PIN_RESET);
	LCD_sendByte(data);
}

void LCD_sendChar(uint8_t data) {
	HAL_GPIO_WritePin(GPIOA, RS_Pin, GPIO_PIN_SET);
	LCD_sendByte(data);
}

void LCD_sendByte(uint8_t data) {
	LCD_sendNibble(data >> 4);
	LCD_sendNibble(data);
}

void LCD_sendNibble(uint8_t data) {
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

void LCD_clear() {
	LCD_sendCmd(0x01);
	vTaskDelay(pdMS_TO_TICKS(5));
}

void LCD_setCursor(char row, char col) {
	char val = (row == 0) ? 0x00 : 0x40;
	val += col;
	LCD_sendCmd(0x80 | val);
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

void set_all_row_high() {
	for (int i = 0; i < 4; i++) {
		HAL_GPIO_WritePin(rowPort[i], rowPin[i], GPIO_PIN_SET);
	}
}

char scan_key_pad(void) {
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

void reverse_str(char *str) {
	int i = 0;
	int j = strlen(str) - 1;
	char temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

void int_to_str(long num, char *str, int base) {
	int i = 0;
	bool is_negative = false;
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return;
	}
	if (num < 0 && base == 10) {
		is_negative = true;
		num = -num;
	}
	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}
	if (is_negative) {
		str[i++] = '-';
	}
	str[i] = '\0';
	reverse_str(str);
}

void float_to_str(float num, char *buffer, int precision)
{
    // Xử lý dấu âm
    int idx = 0;
    if (num < 0)
    {
        buffer[idx++] = '-';
        num = -num;
    }

    // Phần nguyên
    int int_part = (int)num;
    float frac_part = num - int_part;

    // Chuyển phần nguyên sang chuỗi
    char temp[20];
    int t = 0;
    if (int_part == 0)
    {
        temp[t++] = '0';
    }
    else
    {
        while (int_part > 0)
        {
            temp[t++] = (int_part % 10) + '0';
            int_part /= 10;
        }
    }
    // Đảo ngược
    for (int i = t - 1; i >= 0; i--)
        buffer[idx++] = temp[i];

    // Thêm dấu thập phân
    if (precision > 0)
    {
        buffer[idx++] = '.';

        // Xử lý phần thập phân
        for (int i = 0; i < precision; i++)
        {
            frac_part *= 10;
            int digit = (int)frac_part;
            buffer[idx++] = digit + '0';
            frac_part -= digit;
        }

        // Bỏ bớt số 0 dư ở cuối
        while (precision > 0 && buffer[idx - 1] == '0')
        {
            idx--;
            precision--;
        }
        if (buffer[idx - 1] == '.')
            idx--; // bỏ dấu "." nếu ko còn số thập phân
    }

    buffer[idx] = '\0';
}

float eval_simple(char *expr) {
	float nums[17];
	int n = 0;
	char last_op = '+';
	int i = 0, len = strlen(expr);
	while (i < len) {
		while (expr[i] == ' ')
			i++;
		float num = 0, neg = 1, frac = 0.1;
		int has_dot = 0;
		if (expr[i] == '-') {
			neg = -1;
			i++;
		}
		while (isdigit(expr[i]) || expr[i] == '.') {
			if (expr[i] == '.') {
				has_dot = 1;
				i++;
				continue;
			}
			if (!has_dot) {
				num = num * 10 + (expr[i++] - '0');
			} else {
				num = num + (expr[i++] - '0') * frac;
				frac *= 0.1;
			}
		}
		num *= neg;
		if (last_op == '*')
			nums[n - 1] *= num;
		else if (last_op == ':')
			nums[n - 1] /= num;
		else if (last_op == '-')
			nums[n++] = -num;
		else
			nums[n++] = num;
		while (expr[i] == ' ')
			i++;
		last_op = expr[i++];
	}
	float result = 0;
	for (int j = 0; j < n; j++) {
		result += nums[j];
	}
	return result;
}

float handle_input(char *data) {
	while (strchr(data, '(')) {
		int right = -1, left = -1;
		for (int i = 0; data[i]; i++) {
			if (data[i] == ')') {
				right = i;
				break;
			}
		}

		for (int i = right; i >= 0; i--) {
			if (data[i] == '(') {
				left = i;
				break;
			}
		}
		if (left == -1 || right == -1)
			break;
		char sub[64] = { 0 };
		strncpy(sub, data + left + 1, right - left - 1);
		double val = eval_simple(sub);

		char newdata[64] = { 0 };
		strncpy(newdata, data, left);
		char numbuf[64];
		float_to_str(val, numbuf, 2);
		strcat(newdata, numbuf);
		strcat(newdata, data + right + 1);
		strcpy(data, newdata);
	}

	float result = eval_simple(data);
	return result;
}

// Hàm binary search tìm nghiệm trong [l,r] với độ chính xác eps
float calc(char *expr, float x) {
	char buf[64], numbuf[32];
	buf[0] = '\0';
	for (int i = 0; expr[i]; i++) {
		if (expr[i] == 'x') {
			float_to_str(x, numbuf, 7);
			strcat(buf, numbuf);
		} else {
			char tmp[2] = { expr[i], '\0' };
			strcat(buf, tmp);
		}
	}
	return handle_input(buf);
}

int binary_search_root(char *expr, float l, float r, float eps, float *root) {
	float mid, f_l, f_mid;

	f_l = calc(expr, l);
	if (fabs(f_l) < eps) {
		*root = l;
		return 1;
	}

	while (r - l > eps) {
		mid = (l + r) / 2;
		f_mid = calc(expr, mid);

		if (fabs(f_mid) < eps) {
			*root = mid;
			return 1;
		}

		f_l = calc(expr, l);  // luôn tính lại
		if (f_l * f_mid < 0)
			r = mid;
		else
			l = mid;
	}
	*root = (l + r) / 2;
	return 1;
}

void solve_the_equation(char *expr) {
	float eps = 1e-4f;
	float step = 1.0f;
	float root;
	int found_root = 0;
	char kq[17];
	int col = 16;
	LCD_setCursor(1, 0);
	LCD_puts("tim");
	for (float l = -10000; l < 10000; l += step) {
		float r = l + step;
		float f_l = calc(expr, l);
		float f_r = calc(expr, r);

		if (fabs(f_l) < eps) {  // nghiệm ngay tại l
			found_root = 1;
			float_to_str(l, kq, 2);
			LCD_setCursor(1, col - strlen(kq));
			LCD_puts(kq);
			col-=col-strlen(kq)-1;
		} else if (f_l * f_r < 0 || fabs(f_r) < eps) {
			found_root = 1;
			if (binary_search_root(expr, l, r, eps, &root)) {
				if (fabs(root) < eps)
					root = 0;
				float_to_str(root, kq, 2);
				LCD_setCursor(1, col - strlen(kq));
				LCD_puts(kq);
				if (col - strlen(kq) > 0) {
					LCD_setCursor(1, col - strlen(kq) - 1);
					LCD_puts(" ");
					col -= (strlen(kq) + 1);
				} else {
					col -= strlen(kq);
				}
			}
		}
	}
	if (!found_root) {
		LCD_setCursor(1, 0);
		LCD_puts("Not found");
	} else {
		LCD_setCursor(1,0);
		LCD_puts("x: ");
	}
}

void Mode1() {
	keypad[0][3] = '*';
	keypad[2][4] = 'B';
	char keyToDisplay;
	char buffer[17] = "";
	char bufferToShow[2] = "";
	int i = 0;
	int exit = 0;
	while (1) {
		keyToDisplay = scan_key_pad();
		if (keyToDisplay != 'c') {
			if (keyToDisplay == '=') {
				if (exit == 0) {
					buffer[i] = '\0';
					if (i > 0) { // chỉ xử lý khi có dữ liệu
						float result = handle_input(buffer);
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

void Mode2() {
	keypad[0][3] = 'x';
	keypad[2][4] = '*';
	char keyMode2;
	int exit = 0;
	int i = 0;
	char buffer[17] = "";
	char bufferToShow[2] = "";
	while (1) {
		keyMode2 = scan_key_pad();
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
void vTask_UpdateDisplay(void *parameters) {
	char choice;
	LCD_setCursor(0, 0);
	LCD_puts("1.Tinh toan");
	LCD_setCursor(1, 0);
	LCD_puts("2.Giai pt");
	while (1) {
		choice = scan_key_pad();
		if (choice != 'c') {
			if (choice == '1') {
				LCD_setCursor(0, 15);
				LCD_puts(".");
				vTaskDelay(pdMS_TO_TICKS(500));
				LCD_clear();
				Mode1();
				LCD_setCursor(0, 0);
				LCD_puts("1.Tinh toan");
				LCD_setCursor(1, 0);
				LCD_puts("2.Giai pt");

			} else if (choice == '2') {
				LCD_setCursor(1, 15);
				LCD_puts(".");
				vTaskDelay(pdMS_TO_TICKS(500));
				LCD_clear();
				Mode2();
				LCD_setCursor(0, 0);
				LCD_puts("1.Tinh toan");
				LCD_setCursor(1, 0);
				LCD_puts("2.Giai pt");
			}
		}
	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	/* USER CODE BEGIN 2 */
	LCD_init_BareMetal();
	xTaskCreate(vTask_UpdateDisplay, "OUTPUT", 280, NULL, 1, NULL);
	vTaskStartScheduler();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
			PA6_Pin | PA7_Pin | PA8_Pin | RS_Pin | EN_Pin | D4_Pin | D5_Pin
					| D6_Pin | PA5_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : PA6_Pin PA7_Pin PA8_Pin RS_Pin
	 EN_Pin D4_Pin D5_Pin D6_Pin
	 PA5_Pin */
	GPIO_InitStruct.Pin = PA6_Pin | PA7_Pin | PA8_Pin | RS_Pin | EN_Pin | D4_Pin
			| D5_Pin | D6_Pin | PA5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : D7_Pin */
	GPIO_InitStruct.Pin = D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(D7_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PA4_Pin PA3_Pin PA2_Pin PA1_Pin
	 PA0_Pin */
	GPIO_InitStruct.Pin = PA4_Pin | PA3_Pin | PA2_Pin | PA1_Pin | PA0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM3 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM3) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
