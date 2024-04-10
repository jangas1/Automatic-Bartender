#include "servo.h"
#include <math.h>

 //For current clocks 90 is 0deg 451 is 180deg 270 is center
unsigned int degreeToRaw(double degrees){
	return round(map_range(degrees, 0.0, 180.0, 90.0, 451.0));
//	return round(miny + ((maxy-miny)/(maxx-minx))*(degrees-minx));
}
void setRotation(servo_t *self,int desiredDegrees){
	self->rawPos = degreeToRaw(desiredDegrees);
	self->rotation=desiredDegrees;
	TIM3->CCR2 = self->rawPos;

}

void initServo(servo_t *self){
	self->rawPos=degreeToRaw(90);
	self->rotation=90;
	TIM3->CCR2 = self->rawPos;
}

double map_range(double value, double old_min, double old_max, double new_min, double new_max) {
    return ((value - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
}
