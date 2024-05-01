#include "menuHandler.h"
#include "liquidcrystal_i2c.h"
#include <stdio.h>

char FirstOpt[] = "Capacity";
char SecondOpt[] = "Drink Counter";
char FirstOptsub2[] = "Change Cap";
char SecondOptsub2[] = "Back";
char FirstOptsub3[] = "Reset";
char SecondOptsub3[] = "Back";
char Ml[2];
char DrnCnt1[2];
char DrnCnt2[2];
char DrnCnt3[2];
char DrnCnt4[2];

uint8_t volatile cursorPos;
uint8_t volatile menuChanged;
uint16_t drinkCounter1;
uint16_t drinkCounter2;
uint16_t drinkCounter3;
uint16_t drinkCounter4;

void menuError(){
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintStr("Menu Display Error");
}

void defaultMenu(){
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintStr(FirstOpt);
	HD44780_SetCursor(0,1);
	HD44780_PrintStr(SecondOpt);
}

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

void defaultMenuCursorPos1(){
	HD44780_SetCursor(sizeof(SecondOpt),1);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOpt),0);
	HD44780_PrintStr("<-");
}

void defaultMenuCursorPos2(){
	HD44780_SetCursor(sizeof(FirstOpt),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(SecondOpt),1);
	HD44780_PrintStr("<-");
}

void sub2MenuCursorPos1(){
	HD44780_SetCursor(sizeof(SecondOptsub2),1);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOptsub2),0);
	HD44780_PrintStr("<-");
}

void sub2MenuCursorPos2(){
	HD44780_SetCursor(sizeof(FirstOptsub2),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(SecondOptsub2),1);
	HD44780_PrintStr("<-");
}

void sub3MenuCursorPos1(){
	HD44780_SetCursor(sizeof(SecondOptsub3),1);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOptsub3),0);
	HD44780_PrintStr("<-");
}

void sub3MenuCursorPos2(){
	HD44780_SetCursor(sizeof(FirstOptsub3),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(SecondOptsub3),1);
	HD44780_PrintStr("<-");
}

void drinkAddCounter1(){
	drinkCounter1++;
}

void drinkAddCounter2(){
	drinkCounter2++;
}

void drinkAddCounter3(){
	drinkCounter3++;
}

void drinkAddCounter4(){
	drinkCounter4++;
}

void drinkCounterReset(){
	drinkCounter1 = 0;
	drinkCounter2 = 0;
	drinkCounter3 = 0;
	drinkCounter4 = 0;
}

void leftReact1(menu_t* self){
	self->menuChanged = 1;
	self->cursorPos--;
	if (self->cursorPos < 0){
		self->cursorPos = 1;
	}
}

void rightReact1(menu_t* self){
	self->menuChanged = 1;
	self->cursorPos++;
	if (self->cursorPos > 1){
		self->cursorPos = 0;
	}
}

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
			if(self->mililiters > 10){
				self->mililiters = 10;
			}
			break;
		default:
			menuError();
	}
}

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
			if(self->mililiters < 95){
				self->mililiters = 95;
			}
			break;
		default:
			menuError();
	}
}

void leftReact3(menu_t* self){
	self->menuChanged = 1;
	self->cursorPos--;
	if (self->cursorPos < 0){
		self->cursorPos = 1;
	}
}

void rightReact3(menu_t* self){
	self->menuChanged = 1;
	self->cursorPos++;
	if (self->cursorPos > 1){
		self->cursorPos = 0;
	}
}

void clickedReact1(menu_t* self){
	self->menuChanged = 1;
	switch(self->cursorPos){
		case 0:
			self->subMenuFlag = 2;
			break;
			//self->currentMenu = &SUB2;
		case 1:
			self->subMenuFlag = 3;
			break;
			//self->currentMenu = &SUB3;
		default:
			menuError();
	}
	self->cursorPos = 0;
}

void clickedReact2(menu_t* self){
	self->menuChanged = 1;
	switch(self->cursorPos){
		case 0:
			drinkCounterReset();
			break;
		case 1:
			self->subMenuFlag = 1;
			//self->currentMenu = &SUB1;
			self->cursorPos = 0;
			break;
		default:
			menuError();
	}
}

void clickedReact3(menu_t* self){
	self->menuChanged = 1;
	switch(self->cursorPos){
		case 0:
			self->cursorPos = 2;
			break;
		case 1:
			self->subMenuFlag = 1;
			//self->currentMenu = &SUB1;
			self->cursorPos = 0;
			break;
		case 2:
			self->cursorPos = 0;
			break;
	}
}

void handleLeft(menu_t* self){
    self->currentMenu->leftReact(self);
}

void handleRight(menu_t* self){
    self->currentMenu->rightReact(self);
}

void handleClicked(menu_t* self){
    self->currentMenu->clickedReact(self);
}
