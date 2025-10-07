/*
 * app.h
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "calculator_engine.h"
#include "keypad.h"
#include "LCD_driver.h"

#ifdef __cplusplus
extern "C"
{
#endif

void App_RunCalculatorMode(void);
void App_RunSolverMode(void);

#ifdef __cplusplus
}
#endif
#endif /* INC_APP_H_ */
