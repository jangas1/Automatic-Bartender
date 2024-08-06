/**
 * @file shotHolder.h
 * @brief Header file for the shot holder module.
 *
 * This file contains the definitions and function prototypes for the shot holder module.
 *
 * Created on: May 10, 2024
 * Author: Mateusz
 */
#ifndef INC_SHOTHOLDER_H_
#define INC_SHOTHOLDER_H_

typedef struct drink_position drinkpos_t;
/**
 * @brief Drink position structure.
 *
 * This structure holds reaction functions for each possible action for each sub menu.
 */
typedef struct drink_position
{
	int postitionOfDrinks[4];
    void (*drinkChange)(drinkpos_t*, int);
    void (*drinkReset)(drinkpos_t*);
} drinkpos_t;

/**
 * @brief Changes drink counter on detected positions 
 *
 * This function checks glass detection change on each position 
 */
void drinkChange(drinkpos_t* self, int position);

/**
 * @brief Resets drink counter on every position 
 *
 * This function resets the number of drinks on every position to 0.
 */
void drinkReset(drinkpos_t* self);

#endif
