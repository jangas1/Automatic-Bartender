#define HOME_RAW_POS 90
#define MAX_RAW_POS 451
#include "stm32f0xx_hal.h"

typedef struct servo servo_t;

typedef struct servo{
	unsigned int rawPos;
	int rotation;
	void (*setRotation)(servo_t*,int);
	void (*initServo)(servo_t*);
} servo_t ;
double map_range(double value, double old_min, double old_max, double new_min, double new_max);
unsigned int degreeToRaw(double degrees);
void setRotation(servo_t *self,int desiredDegrees);
void initServo(servo_t *self);
