#include "handles.h"


void leftReact1(){
    printf("Left react1\n");
}

void rightReact1(){
    printf("Right react1\n");
}
void leftReact2(){
    printf("Left react2\n");
}

void rightReact2(){
    printf("Right react2\n");
}

void leftReact3(){
    printf("Left react3\n");
}

void rightReact3(){
    printf("Right react3\n");
}

void handleLeft(menu_t* self){
    self->currentMenu->leftReact();
    self->currentMenu = self->currentMenu->last;
}

void handleRight(menu_t* self){
    self->currentMenu->rightReact();
    self->currentMenu = self->currentMenu->next;
}