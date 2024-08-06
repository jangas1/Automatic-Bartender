/**
 * @file shotHolder.c
 * @brief Implementation file for the shot holder module.
 *
 * This file contains the implementation of the functions declared in shotHolder.c.
 *
 * Created on: May 10, 2024
 * Author: Mateusz
 */

#include "shotHolder.h"
#include <stdio.h>

/**
* @brief Signals glass detection on each position
* @param self: calls to drink position structure for use of its functions and variables
* @param position: passed position of drink 1,2,3,4 means detection on those positions when 11,22,33,44 means no detection on those positions
* @retval None
*/
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

/**
* @brief Resets drink counter on each position
* @param self: calls to drink position structure for use of its functions and variables
* @retval None
*/
void drinkReset(drinkpos_t* self){
    for (int i = 0; i < 4; ++i) {
        self->postitionOfDrinks[i] = 0;
    }
}

