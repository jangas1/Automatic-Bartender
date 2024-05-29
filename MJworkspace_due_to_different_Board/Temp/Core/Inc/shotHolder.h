#ifndef INC_SHOTHOLDER_H_
#define INC_SHOTHOLDER_H_

typedef struct drink_position drinkpos_t;

typedef struct drink_position
{
	int postitionOfDrinks[4];
    void (*drinkChange)(drinkpos_t*, int);
    void (*drinkReset)(drinkpos_t*);
} drinkpos_t;

void drinkChange(drinkpos_t* self, int position);
void drinkReset(drinkpos_t* self);

#endif
