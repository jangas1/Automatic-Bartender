/**
 * @file menuHandler.h
 * @brief Header file for the menu on the LCD display.
 *
 * This file contains the definitions and function prototypes for the menu on the LCD display.
 *
 * Created on: May 10, 2024
 * Author: Mateusz
 */

#ifndef INC_MENUHANDLER_H_
#define INC_MENUHANDLER_H_


/**
 * @brief Sets cursor position
 *
 * Those functions set cursor positions depending on cursorPos and currentMenu.
 */
void defaultMenuCursorPos1();
void defaultMenuCursorPos2();
void defaultMenuCursorPos3();
void sub2MenuCursorPos1();
void sub2MenuCursorPos2();
void sub3MenuCursorPos1();
void sub3MenuCursorPos2();

/**
 * @brief Menages drink Counting
 *
 * Those functions either increment drink counter on positions or resets them.
 */
void drinkAddCounter1();
void drinkAddCounter2();
void drinkAddCounter3();
void drinkAddCounter4();
void drinkCounterReset();

typedef struct Menu menu_t;

/**
 * @brief Sub menu structure.
 *
 * This structure holds reaction functions for each possible action for each sub menu.
 */
typedef struct sub_struct
{
    menu_t *menu;
    void (*leftReact)(menu_t*);
    void (*rightReact)(menu_t*);
    void (*clickedReact)(menu_t*);
} sub_t;

typedef struct sub_struct sub_t;

/**
 * @brief Menu structure.
 *
 * This structure holds variables connected with menu and reaction functions from the sub_struct structure.
 */
typedef struct Menu
{
    sub_t *currentMenu;
    int pourChanged;
    int cursorPos;
    int menuChanged;
    int subMenuFlag;
    int mililiters;
    void (*handleLeft)(menu_t*);
    void (*handleRight)(menu_t*);
    void (*clickedReact)(menu_t*);
} menu_t;

/**
 * @brief Changes current menu
 *
 * Depending on currentMenu those functions display that menu.
 */
void defaultMenu();
void sub2Menu(menu_t* self);
void sub3Menu();
void menuError();

/**
 * @brief Reacts to encoder left move, right move and click
 *
 * Depending on sub menu encoder moves and click have different functionality 
 */
void leftReact1(menu_t* self);
void rightReact1(menu_t* self);
void leftReact2(menu_t* self);
void rightReact2(menu_t* self);
void leftReact3(menu_t* self);
void rightReact3(menu_t* self);
void handleLeft(menu_t* self);
void handleRight(menu_t* self);
void clickedReact(menu_t* self);
void handleClicked(menu_t* self);
void clickedReact1(menu_t* self);
void clickedReact2(menu_t* self);
void clickedReact3(menu_t* self);

#endif
