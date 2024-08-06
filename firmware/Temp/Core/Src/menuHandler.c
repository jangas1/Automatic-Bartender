/**
 * @file menuHandler.c
 * @brief Implementation file the menu on the LCD display.
 *
 * This file contains the implementation of the functions declared in menuHandler.c.
 *
 * Created on: May 10, 2024
 * Author: Mateusz
 */
#include "menuHandler.h"
#include "liquidcrystal_i2c.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "servo.h"

/**
 * @brief Declaration of variables used in menu display functions for easier change during testing.
 *
 * Variables to avoid hardcoding char variables in code and to make it simple to change them
 */
char FirstOpt[] = "Capacity";
char SecondOpt[] = "Drink Counter";
char ThirdOpt[] = "Pour";
char FirstOptsub2[] = "Change Cap";
char SecondOptsub2[] = "Back";
char FirstOptsub3[] = "Reset";
char SecondOptsub3[] = "Back";
char Ml[2];
char DrnCnt1[2];
char DrnCnt2[2];
char DrnCnt3[2];
char DrnCnt4[2];
uint16_t drinkCounter1;
uint16_t drinkCounter2;
uint16_t drinkCounter3;
uint16_t drinkCounter4;

/**
* @brief Error handler in form of displaying "Menu Display Error" on LCD, usefull for menu testing 
* @retval None
*/
void menuError(){
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintStr("Menu Display Error");
}

/**
* @brief Display main menu
* @retval None
*/
void defaultMenu(){
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintStr(FirstOpt);
	HD44780_SetCursor(0,1);
	HD44780_PrintStr(SecondOpt);
	HD44780_SetCursor(13,0);
	HD44780_PrintStr(ThirdOpt);
}

/**
* @brief Display capacity menu
* @retval None
*/
void sub2Menu(menu_t* self){
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintStr(FirstOptsub2);
	HD44780_SetCursor(0,1);
	HD44780_PrintStr(SecondOptsub2);
	HD44780_SetCursor(16,0);
	sprintf(Ml, "%d", self->mililiters);
	HD44780_PrintStr(Ml);
	HD44780_SetCursor(18,0);
	HD44780_PrintStr("ml");
}

/**
* @brief Display drink counter menu
* @retval None
*/
void sub3Menu(){
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintStr(FirstOptsub3);
	HD44780_SetCursor(0,1);
	HD44780_PrintStr(SecondOptsub3);
	HD44780_SetCursor(8,0);
	HD44780_PrintStr("1st:");
	HD44780_SetCursor(12,0);
	sprintf(DrnCnt1, "%d", drinkCounter1);
	HD44780_PrintStr(DrnCnt1);
	HD44780_SetCursor(14,0);
	HD44780_PrintStr("2nd:");
	HD44780_SetCursor(18,0);
	sprintf(DrnCnt2, "%d", drinkCounter2);
	HD44780_PrintStr(DrnCnt2);
	HD44780_SetCursor(8,1);
	HD44780_PrintStr("3rd:");
	HD44780_SetCursor(12,1);
	sprintf(DrnCnt3, "%d", drinkCounter3);
	HD44780_PrintStr(DrnCnt3);
	HD44780_SetCursor(14,1);
	HD44780_PrintStr("4th:");
	HD44780_SetCursor(18,1);
	sprintf(DrnCnt4, "%d", drinkCounter4);
	HD44780_PrintStr(DrnCnt4);
}

/**
* @brief Display cursor position in main menu on first position
* @retval None
*/
void defaultMenuCursorPos1(){
	HD44780_SetCursor(sizeof(SecondOpt),1);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(ThirdOpt)+ 13,0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOpt),0);
	HD44780_PrintStr("<-");
}

/**
* @brief Display cursor position in main menu on second position
* @retval None
*/
void defaultMenuCursorPos2(){
	HD44780_SetCursor(sizeof(FirstOpt),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(ThirdOpt)+ 13,0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(SecondOpt),1);
	HD44780_PrintStr("<-");
}

/**
* @brief Display cursor position in main menu on third position
* @retval None
*/
void defaultMenuCursorPos3(){
	HD44780_SetCursor(sizeof(SecondOpt),1);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOpt),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(ThirdOpt)+ 13,0);
	HD44780_PrintStr("<-");
}

/**
* @brief Display cursor position in capacity menu on first position
* @retval None
*/
void sub2MenuCursorPos1(){
	HD44780_SetCursor(sizeof(SecondOptsub2),1);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOptsub2),0);
	HD44780_PrintStr("<-");
}

/**
* @brief Display cursor position in capacity menu on second position
* @retval None
*/
void sub2MenuCursorPos2(){
	HD44780_SetCursor(sizeof(FirstOptsub2),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(SecondOptsub2),1);
	HD44780_PrintStr("<-");
}

/**
* @brief Display cursor position in drink counter menu on first position
* @retval None
*/
void sub3MenuCursorPos1(){
	HD44780_SetCursor(sizeof(SecondOptsub3),1);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOptsub3),0);
	HD44780_PrintStr("<-");
}

/**
* @brief Display cursor position in drink counter menu on first position
* @retval None
*/
void sub3MenuCursorPos2(){
	HD44780_SetCursor(sizeof(FirstOptsub3),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(SecondOptsub3),1);
	HD44780_PrintStr("<-");
}

/**
* @brief Increment drink counter on first position
* @retval None
*/
void drinkAddCounter1(){
	drinkCounter1++;
}

/**
* @brief Increment drink counter on second position
* @retval None
*/
void drinkAddCounter2(){
	drinkCounter2++;
}

/**
* @brief Increment drink counter on third position
* @retval None
*/
void drinkAddCounter3(){
	drinkCounter3++;
}

/**
* @brief Increment drink counter on fourth position
* @retval None
*/
void drinkAddCounter4(){
	drinkCounter4++;
}

/**
* @brief Reset drink counter on all positions
* @retval None
*/
void drinkCounterReset(){
	drinkCounter1 = 0;
	drinkCounter2 = 0;
	drinkCounter3 = 0;
	drinkCounter4 = 0;
}

/**
* @brief Handles turning the encoder to the left in first menu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void leftReact1(menu_t* self){
	self->menuChanged = 1;
	self->cursorPos--;
	if (self->cursorPos < 0){
		self->cursorPos = 2;
	}
}

/**
* @brief Handles turning the encoder to the right in first menu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void rightReact1(menu_t* self){
	self->menuChanged = 1;
	self->cursorPos++;
	if (self->cursorPos > 2){
		self->cursorPos = 0;
	}
}

/**
* @brief Handles turning the encoder to the left in second menu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void leftReact2(menu_t* self){
	self->menuChanged = 1;
	switch(self->cursorPos){
		case 0:
			self->cursorPos = 1;
			break;
		case 1:
			self->cursorPos = 0;
			break;
		case 2:
			self->mililiters = self->mililiters - 5;
			if(self->mililiters < 10){
				self->mililiters = 10;
			}
			break;
	}
}

/**
* @brief Handles turning the encoder to the right in second menu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void rightReact2(menu_t* self){
	self->menuChanged = 1;
	switch(self->cursorPos){
		case 0:
			self->cursorPos = 1;
			break;
		case 1:
			self->cursorPos = 0;
			break;
		case 2:
			self->mililiters = self->mililiters + 5;
			if(self->mililiters > 95){
				self->mililiters = 95;
			}
			break;
		//default:
		//	menuError();
	}
}

/**
* @brief Handles turning the encoder to the left in third menu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void leftReact3(menu_t* self){
	self->menuChanged = 1;
	self->cursorPos--;
	if (self->cursorPos < 0){
		self->cursorPos = 1;
	}
}

/**
* @brief Handles turning the encoder to the right in third menu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void rightReact3(menu_t* self){
	self->menuChanged = 1;
	self->cursorPos++;
	if (self->cursorPos > 1){
		self->cursorPos = 0;
	}
}

/**
* @brief Handles encoder click in the first menu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void clickedReact1(menu_t* self){
	self->menuChanged = 1;
	switch(self->cursorPos){
		case 0:
			self->subMenuFlag = 2;
			break;
		case 1:
			self->subMenuFlag = 3;
			break;
		case 2:
			self->pourChanged = 1;
			break;
	}
	self->cursorPos = 0;
}

/**
* @brief Handles encoder click in the second menu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void clickedReact2(menu_t* self){
	self->menuChanged = 1;
	switch(self->cursorPos){
		case 0:
			self->cursorPos = 2;
			break;
		case 1:
			self->subMenuFlag = 1;
			self->cursorPos = 0;
			break;
		case 2:
			self->cursorPos = 0;
			break;
	}
}

/**
* @brief Handles encoder click in the third menu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void clickedReact3(menu_t* self){
	self->menuChanged = 1;
	switch(self->cursorPos){
		case 0:
			drinkCounterReset();
			break;
		case 1:
			self->subMenuFlag = 1;
			self->cursorPos = 0;
			break;
		//default:
		//	menuError();
	}
}

/**
* @brief Handles left reactions to each menu based on their submenu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void handleLeft(menu_t* self){
    self->currentMenu->leftReact(self);
}

/**
* @brief Handles right reactions to each menu based on their submenu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void handleRight(menu_t* self){
    self->currentMenu->rightReact(self);
}

/**
* @brief Handles click reactions to each menu based on their submenu
* @param self: calls to menu structure for use of its functions and variables
* @retval None
*/
void handleClicked(menu_t* self){
    self->currentMenu->clickedReact(self);
}
