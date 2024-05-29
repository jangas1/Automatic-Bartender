#include "shotHolder.h"
#include <stdio.h>

void drinkChange(drinkpos_t* self, int position){
	switch(position){
	case(1):
		self->postitionOfDrinks[0] = 1;
		break;
	case(11):
		self->postitionOfDrinks[0] = 0;
		break;
	case(2):
		self->postitionOfDrinks[1] = 1;
		break;
	case(22):
		self->postitionOfDrinks[1] = 0;
		break;
	case(3):
		self->postitionOfDrinks[2] = 1;
		break;
	case(33):
		self->postitionOfDrinks[2] = 0;
		break;
	case(4):
		self->postitionOfDrinks[3] = 1;
		break;
	case(44):
		self->postitionOfDrinks[3] = 0;
		break;
	default:
	    for (int i = 0; i < 4; ++i) {
	        self->postitionOfDrinks[i] = 0;
	    }
	}
}
void drinkReset(drinkpos_t* self){
    for (int i = 0; i < 4; ++i) {
        self->postitionOfDrinks[i] = 0;
    }
}

