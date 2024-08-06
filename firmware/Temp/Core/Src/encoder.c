/**
 * @file encoder.c
 * @brief Implementation file for the encoder module.
 *
 * This file contains the implementation of the functions declared in encoder.h.
 *
 * Created on: May 10, 2024
 * Author: Daniel
 */

#include "encoder.h"

/**
 * @brief Global encoder instance.
 */
encoder enc;

extern menu_t menu;

/**
 * @brief Reacts to a left turn of the encoder.
 *
 * This function is called when the encoder is turned left. It handles the left turn event.
 */
void LeftReact(){
    menu.handleLeft(&menu);
}

/**
 * @brief Reacts to a right turn of the encoder.
 *
 * This function is called when the encoder is turned right. It handles the right turn event.
 */
void RightReact(){
    menu.handleRight(&menu);
}

/**
 * @brief Reacts to a click of the encoder button.
 *
 * This function is called when the encoder button is clicked. It handles the click event.
 */
void ClickedReact(){
    menu.clickedReact(&menu);
}

/**
 * @brief Interrupt Service Routine for the encoder.
 *
 * This function is called in response to changes in the encoder's signals.
 * It updates the encoder state and calls the appropriate callback functions.
 */
void ISR(){
    enc.lastClock = enc.newClock;
    enc.lastDir = enc.direction;
    enc.lastClicked = enc.Clicked;
    enc.newClock = HAL_GPIO_ReadPin(enc_CLK_GPIO_Port, enc_CLK_Pin);
    enc.direction = HAL_GPIO_ReadPin(enc_DATA_GPIO_Port, enc_DATA_Pin);
    enc.Clicked = !HAL_GPIO_ReadPin(enc_CLICK_GPIO_Port, enc_CLICK_Pin);

    if (((enc.lastClock != enc.newClock) && enc.newClock == 1)) {
        if (enc.direction == 1) {
            enc.LeftCallback();
        }
    } else if ((enc.lastDir != enc.direction) && enc.direction == 1) {
        if (enc.newClock == 1) {
            enc.RightCallback();
        }
    }
    if ((enc.Clicked == 1) && (enc.lastClicked == 0)) {
        enc.ClickedCallback();
    }
}

/**
 * @brief Initializes the encoder.
 *
 * This function initializes the encoder structure and sets the default callback functions.
 */
void encoderInit(){
    enc.ISR = ISR;
    enc.RightCallback = RightReact;
    enc.LeftCallback = LeftReact;
    enc.ClickedCallback = ClickedReact;
    enc.direction = 1;
    enc.lastClock = 1;
    enc.lastDir = 1;
    enc.newClock = 1;
}
