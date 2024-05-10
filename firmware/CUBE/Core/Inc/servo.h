#define HOME_RAW_POS 90
#define MAX_RAW_POS 451

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32f0xx_hal.h"

//typedef struct servo servo_t;

typedef struct servo{
	unsigned int rawPos;
	int rotation;
	void (*setRotation)(int);
	void (*initServo)();
} servo_t ;

double map_range(double value, double old_min, double old_max, double new_min, double new_max);
unsigned int degreeToRaw(double degrees);
void setRotation(int desiredDegrees);
void initServo();

extern servo_t servo;

#endif
