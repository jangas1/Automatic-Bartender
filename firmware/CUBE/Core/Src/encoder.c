/*
 * encoder.c
 *
 *  Created on: May 10, 2024
 *      Author: Daniel
 */

#include "encoder.h"

encoder enc;



void LeftReact(){

	HAL_UART_Transmit(&huart2, (uint8_t*)"LEFT\n", 5, 100);

}

void RightReact(){

	HAL_UART_Transmit(&huart2, (uint8_t*)"RIGHT\n", 6, 100);

}

void ClickedReact(){

}


void ISR(){
	  enc.lastClock = enc.newClock;
	  enc.lastDir = enc.direction;
	  enc.newClock = HAL_GPIO_ReadPin(enc_CLK_GPIO_Port, enc_CLK_Pin);
	  enc.direction = HAL_GPIO_ReadPin(enc_DATA_GPIO_Port, enc_DATA_Pin);
	  //HAL_UART_Transmit(&huart2, (uint8_t*)"ISR\n", 6, 100);
	  if (((enc.lastClock != enc.newClock)&& enc.newClock == 1)) {
		if (enc.direction == 1) {
			enc.LeftCallback();
		}
		}else if((enc.lastDir != enc.direction)&& enc.direction == 1){
			if (enc.newClock == 1) {
				enc.RightCallback();
			}
	  }
}

void encoderInit(){
	enc.ISR = ISR;
	enc.RightCallback = RightReact;
	enc.LeftCallback = LeftReact;
	enc.direction=1;
	enc.lastClock=1;
	enc.lastDir =1;
	enc.newClock=1;
}


