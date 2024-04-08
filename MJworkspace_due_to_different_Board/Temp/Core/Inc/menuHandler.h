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

void leftReact1();
void rightReact1();

void leftReact2();
void rightReact2();

void leftReact3();
void rightReact3();

void handleLeft();
void handleRight();



typedef struct Menu menu_t;

typedef struct sub_struct
{
    menu_t *menu;
    void (*leftReact)();
    void (*rightReact)();
    void (*clickedReact)(menu_t*);
    void *next;
    void *last;
} sub_t;

typedef struct sub_struct sub_t;

typedef struct Menu
{
    sub_t *currentMenu ;
    int cursorPos;
    void (*handleLeft)(menu_t*);
    void (*handleRight)(menu_t*);
    void (*clickedReact)(menu_t*);
} menu_t;

void clickedReact(menu_t*);
void handleClicked(menu_t* self);
void clickedReact1(menu_t* self);
#endif /* INC_MENUHANDLER_H_ */
