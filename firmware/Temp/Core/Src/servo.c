/**
 * @file servo.c
 * @brief Implementation file for the servo module.
 *
 * This file contains the implementation of the functions declared in servo.h.
 */

#include "servo.h"
#include <math.h>

/**
 * @brief Global servo instance.
 *
 * Initialized with default values and function pointers.
 */
servo_t servo = {.rotation=0, .setRotation=setRotation, .initServo=initServo};

/**
 * @brief Converts degrees to raw servo position.
 *
 * This function maps the degrees (0 to 180) to the corresponding raw position
 * for the servo (HOME_RAW_POS to MAX_RAW_POS).
 *
 * @param degrees The desired rotation in degrees.
 * @return The corresponding raw position.
 */
unsigned int degreeToRaw(double degrees){
    return round(map_range(degrees, 0.0, 180.0, 90.0, 451.0));
}

/**
 * @brief Sets the servo rotation to the desired degrees.
 *
 * This function converts the desired degrees to the raw position and updates
 * the servo's position.
 *
 * @param desiredDegrees The desired rotation in degrees.
 */
void setRotation(int desiredDegrees){
    servo.rawPos = degreeToRaw(desiredDegrees);
    servo.rotation = desiredDegrees;
    TIM9->CCR1 = servo.rawPos;
}

/**
 * @brief Initializes the servo to the home position.
 *
 * This function sets the servo to the home position (90 degrees) and updates
 * the raw position.
 */
void initServo(){
    servo.rawPos = degreeToRaw(90);
    servo.rotation = 90;
    TIM9->CCR1 = servo.rawPos;
}

/**
 * @brief Maps a value from one range to another.
 *
 * This function maps a value from the old range (old_min to old_max) to the new range
 * (new_min to new_max).
 *
 * @param value The value to be mapped.
 * @param old_min The minimum value of the original range.
 * @param old_max The maximum value of the original range.
 * @param new_min The minimum value of the new range.
 * @param new_max The maximum value of the new range.
 * @return The mapped value in the new range.
 */
double map_range(double value, double old_min, double old_max, double new_min, double new_max) {
    return ((value - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
}
