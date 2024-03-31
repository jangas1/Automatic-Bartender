#include "menuHandler.h"
#include "liquidcrystal_i2c.h"

char FirstOpt[] = "Capacity";
char SecondOpt[] = "Drink Counter";
char FirstOptsub3[] = "Reset";
char SecondOptsub3[] = "Back";
uint8_t XD = 0;

void defaultMenu(){
	  HD44780_Clear();
	  HD44780_SetCursor(0,0);
	  HD44780_PrintStr(FirstOpt);
	  HD44780_SetCursor(0,1);
	  HD44780_PrintStr(SecondOpt);
}

void sub3Menu(){
	  HD44780_Clear();
	  HD44780_SetCursor(0,4);
	  HD44780_PrintStr(FirstOptsub3);
	  HD44780_SetCursor(10,4);
	  HD44780_PrintStr(SecondOptsub3);
	  HD44780_SetCursor(0,0);
	  HD44780_PrintStr("First:");
	  HD44780_SetCursor(10,0);
	  HD44780_PrintStr("Second:");
	  HD44780_SetCursor(0,1);
	  HD44780_PrintStr("Third:");
	  HD44780_SetCursor(10,1);
	  HD44780_PrintStr("Forth:");
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
	/*
	HD44780_SetCursor(sizeof(SecondOptsub3) + 10,4);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(FirstOptsub3),4);
	HD44780_PrintStr("<-");
	*/
	XD = 2;
}

void rightReact3(){
	/*
	HD44780_SetCursor(sizeof(FirstOptsub3),0);
	HD44780_PrintStr("  ");
	HD44780_SetCursor(sizeof(SecondOptsub3) + 10,1);
	HD44780_PrintStr("<-");
	*/
	XD = 1;
}

void handleLeft(menu_t* self){
    self->currentMenu->leftReact();
    self->currentMenu = self->currentMenu->last;
}

void handleRight(menu_t* self){
    self->currentMenu->rightReact();
    self->currentMenu = self->currentMenu->next;
}

