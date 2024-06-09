/**
 * @file servo.h
 * @brief Header file for the servo module.
 *
 * This file contains the definitions and function prototypes for the servo module.
 *
 * Defines the servo structure and declares functions for servo control.
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32f4xx_hal.h"

/** @brief The raw position corresponding to the home position (0 degrees). */
#define HOME_RAW_POS 90

/** @brief The raw position corresponding to the maximum position (180 degrees). */
#define MAX_RAW_POS 451

/**
 * @brief Servo structure.
 *
 * This structure holds the state and function pointers for controlling a servo motor.
 */
typedef struct servo{
    unsigned int rawPos;          /**< The raw position of the servo. */
    int rotation;                 /**< The current rotation in degrees. */
    void (*setRotation)(int);     /**< Function pointer to set the servo rotation. */
    void (*initServo)();          /**< Function pointer to initialize the servo. */
} servo_t;

/**
 * @brief Maps a value from one range to another.
 *
 * @param value The value to be mapped.
 * @param old_min The minimum value of the original range.
 * @param old_max The maximum value of the original range.
 * @param new_min The minimum value of the new range.
 * @param new_max The maximum value of the new range.
 * @return The mapped value in the new range.
 */
double map_range(double value, double old_min, double old_max, double new_min, double new_max);

/**
 * @brief Converts degrees to raw servo position.
 *
 * @param degrees The desired rotation in degrees.
 * @return The corresponding raw position.
 */
unsigned int degreeToRaw(double degrees);

/**
 * @brief Sets the servo rotation to the desired degrees.
 *
 * @param desiredDegrees The desired rotation in degrees.
 */
void setRotation(int desiredDegrees);

/**
 * @brief Initializes the servo to the home position.
 *
 * This function sets the servo to the home position (90 degrees).
 */
void initServo();

/**
 * @brief Global servo instance.
 */
extern servo_t servo;

#endif /* INC_SERVO_H_ */
