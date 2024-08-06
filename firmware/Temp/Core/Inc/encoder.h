/**
 * @file encoder.h
 * @brief Header file for the encoder module.
 *
 * This file contains the definitions and function prototypes for the encoder module.
 *
 * Created on: May 10, 2024
 * Author: Daniel
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "menuHandler.h"
#include "cmsis_os.h"

/**
 * @brief Encoder structure.
 *
 * This structure holds the state and callback functions for the encoder.
 */
typedef struct encoder{
    uint8_t lastClock;           /**< Last state of the clock signal. */
    uint8_t direction;           /**< Current direction of the encoder. */
    uint8_t newClock;            /**< New state of the clock signal. */
    uint8_t lastDir;             /**< Last direction of the encoder. */
    uint8_t lastClicked;         /**< Last state of the click button. */
    uint8_t Clicked;             /**< Current state of the click button. */
    void(*ISR)();                /**< Interrupt service routine for the encoder. */
    void(*LeftCallback)();       /**< Callback function for left turn. */
    void(*RightCallback)();      /**< Callback function for right turn. */
    void(*ClickedCallback)();    /**< Callback function for click. */
} encoder;

/**
 * @brief Initializes the encoder.
 *
 * This function initializes the encoder structure and sets the default callback functions.
 */
void encoderInit();

/**
 * @brief Global encoder instance.
 */
extern encoder enc;

#endif /* INC_ENCODER_H_ */
