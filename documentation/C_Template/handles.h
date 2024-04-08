#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

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
    void *next;
    void *last;
} sub_t;

typedef struct sub_struct sub_t;

typedef struct Menu
{
    sub_t *currentMenu ;
    void (*handleLeft)(menu_t*);
    void (*handleRight)(menu_t*);
} menu_t;


