#include "menuHandler.h"
#include "liquidcrystal_i2c.h"

char FirstOpt[] = "Capacity";
char SecondOpt[] = "Drink Counter";
char FirstOptsub3[] = "Reset";
char SecondOptsub3[] = "Back";
uint8_t XD = 0;
uint8_t volatile cursorPos;

void defaultMenu(){
	  HD44780_Clear();
	  HD44780_SetCursor(0,0);
	  HD44780_PrintStr(FirstOpt);
	  HD44780_SetCursor(0,1);
	  HD44780_PrintStr(SecondOpt);
}

void sub3Menu(){
	  HD44780_Clear();
	  HD44780_SetCursor(0,0);
	  HD44780_PrintStr(FirstOptsub3);
	  HD44780_SetCursor(0,1);
	  HD44780_PrintStr(SecondOptsub3);
	  HD44780_SetCursor(8,0);
	  HD44780_PrintStr("1st:");
	  HD44780_SetCursor(14,0);
	  HD44780_PrintStr("2nd:");
	  HD44780_SetCursor(8,1);
	  HD44780_PrintStr("3rd:");
	  HD44780_SetCursor(14,1);
	  HD44780_PrintStr("4th:");
}

void leftReact1(){
	HD44780_SetCursor(sizeof(SecondOpt),1);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOpt),0);
	HD44780_PrintStr("<-");
}

void rightReact1(){
	HD44780_SetCursor(sizeof(FirstOpt),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(SecondOpt),1);
	HD44780_PrintStr("<-");
}
void leftReact2(){
	XD = 3;
}

void rightReact2(){
	XD = 4;
}

void leftReact3(){
	HD44780_SetCursor(sizeof(SecondOptsub3),1);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOptsub3),0);
	HD44780_PrintStr("<-");
	//  cursorPos--
}

void rightReact3(){
	HD44780_SetCursor(sizeof(FirstOptsub3),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(SecondOptsub3),1);
	HD44780_PrintStr("<-");
	// cursorPos++
}

void clickedReact1(menu_t* self){
	//Do stuff
	//self->currentMenu->
	// cursorPos++
}


void handleLeft(menu_t* self){
    self->currentMenu->leftReact();
    //self->currentMenu = self->currentMenu->last;
}

void handleRight(menu_t* self){
    self->currentMenu->rightReact();
    //self->currentMenu = self->currentMenu->next;
}

void handleClicked(menu_t* self){
    self->clickedReact(self);
}

