/*
 * keypad.h
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

extern char keypad[4][5];

#ifdef __cplusplus
extern "C"
{
#endif
// Public Function
char keyPad_scan(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_KEYPAD_H_ */
