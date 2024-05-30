/*
 * encoder.c
 *
 *  Created on: May 10, 2024
 *      Author: Daniel
 */

#include "encoder.h"

encoder enc;
extern menu_t menu;


void LeftReact(){

	//HAL_UART_Transmit(&huart2, (uint8_t*)"LEFT\n", 5, 100);
	menu.handleLeft(&menu);

}

void RightReact(){

	//HAL_UART_Transmit(&huart2, (uint8_t*)"RIGHT\n", 6, 100);
	menu.handleRight(&menu);
}

void ClickedReact(){
	menu.clickedReact(&menu);
}


void ISR(){
	  enc.lastClock = enc.newClock;
	  enc.lastDir = enc.direction;
	  enc.lastClicked = enc.Clicked;
	  enc.newClock = HAL_GPIO_ReadPin(enc_CLK_GPIO_Port, enc_CLK_Pin);
	  enc.direction = HAL_GPIO_ReadPin(enc_DATA_GPIO_Port, enc_DATA_Pin);
	  enc.Clicked = !HAL_GPIO_ReadPin(enc_CLICK_GPIO_Port, enc_CLICK_Pin);
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
	  if ((enc.Clicked == 1)&&(enc.lastClicked==0)) {
		enc.ClickedCallback();
	  }
}

void encoderInit(){
	enc.ISR = ISR;
	enc.RightCallback = RightReact;
	enc.LeftCallback = LeftReact;
	enc.ClickedCallback = ClickedReact;
	enc.direction=1;
	enc.lastClock=1;
	enc.lastDir =1;
	enc.newClock=1;
}


