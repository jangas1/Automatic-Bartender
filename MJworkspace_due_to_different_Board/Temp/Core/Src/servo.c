#include "servo.h"
#include <math.h>

 //For current clocks 90 is 0deg 451 is 180deg 270 is center
servo_t servo = {.rotation=0,.setRotation=setRotation,.initServo=initServo};


unsigned int degreeToRaw(double degrees){
	return round(map_range(degrees, 0.0, 180.0, 90.0, 451.0));
//	return round(miny + ((maxy-miny)/(maxx-minx))*(degrees-minx));
}
void setRotation(int desiredDegrees){
	servo.rawPos = degreeToRaw(desiredDegrees);
	servo.rotation=desiredDegrees;
	TIM9->CCR1 = servo.rawPos;

}

void initServo(){
	servo.rawPos=degreeToRaw(90);
	servo.rotation=90;
	TIM9->CCR1 = servo.rawPos;
}

double map_range(double value, double old_min, double old_max, double new_min, double new_max) {
    return ((value - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
}
