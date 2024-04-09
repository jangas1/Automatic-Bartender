/*
 * menuHandler.h
 *
 *  Created on: Mar 31, 2024
 *      Author: 48791
 */

#ifndef INC_MENUHANDLER_H_
#define INC_MENUHANDLER_H_

void defaultMenu();
void sub3Menu();
void menuError();

void defaultMenuCursorPos1();
void defaultMenuCursorPos2();
void sub3MenuCursorPos1();
void sub3MenuCursorPos2();

void drinkAddCounter1();
void drinkAddCounter2();
void drinkAddCounter3();
void drinkAddCounter4();
void drinkResetCounter();

typedef struct Menu menu_t;

typedef struct sub_struct
{
    menu_t *menu;
    void (*leftReact)(menu_t*);
    void (*rightReact)(menu_t*);
    void (*clickedReact)(menu_t*);
} sub_t;

typedef struct sub_struct sub_t;

typedef struct Menu
{
    sub_t *currentMenu ;
    int cursorPos;
    int menuChanged;
    void (*handleLeft)(menu_t*);
    void (*handleRight)(menu_t*);
    void (*clickedReact)(menu_t*);
} menu_t;

void leftReact1(menu_t* self);
void rightReact1(menu_t* self);

void leftReact2(menu_t* self);
void rightReact2(menu_t* self);

void leftReact3(menu_t* self);
void rightReact3(menu_t* self);

void handleLeft(menu_t* self);
void handleRight(menu_t* self);

void clickedReact(menu_t*);
void handleClicked(menu_t* self);
void clickedReact1(menu_t* self);
void clickedReact2(menu_t* self);
void clickedReact3(menu_t* self);

#endif /* INC_MENUHANDLER_H_ */
