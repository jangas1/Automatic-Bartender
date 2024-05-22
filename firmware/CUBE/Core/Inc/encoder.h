/*
 * encoder.h
 *
 *  Created on: May 10, 2024
 *      Author: Daniel
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f0xx_hal.h"
#include "main.h"
extern UART_HandleTypeDef huart2;
#include "cmsis_os.h"

typedef struct encoder{
	uint8_t lastClock;
	uint8_t direction;
	uint8_t newClock;
	uint8_t lastDir;
	void(*ISR)();
	void(*LeftCallback)();
	void(*RightCallback)();
	void(*ClickedCallback)();
} encoder ;

void encoderInit();

extern encoder enc;

#endif /* INC_ENCODER_H_ */
