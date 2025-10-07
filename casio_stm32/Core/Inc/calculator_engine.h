/*
 * calcula_engineer.h
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

#ifndef INC_CALCULA_ENGINEER_H_
#define INC_CALCULA_ENGINEER_H_
#include "FreeRTOS.h"
#include "queue.h"
#include "string.h"
#include "semphr.h"
#include "stdbool.h"
#include "math.h"
#include "ctype.h"
#include "LCD_driver.h"

#ifdef __cplusplus
extern "C"
{
#endif

float Calculate(char *data);

void solve_the_equation(char *expr);

void int_to_str(long num, char *str, int base);

void float_to_str(float num, char *buffer, int precision);

#ifdef __cplusplus
}
#endif
#endif /* INC_CALCULA_ENGINEER_H_ */
