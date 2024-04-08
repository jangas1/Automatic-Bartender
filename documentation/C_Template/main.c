#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif
#include "handles.h"
#include "windows.h"


sub_t SUB1 = { .leftReact=leftReact1, .rightReact = rightReact1};
sub_t SUB2 = { .leftReact=leftReact2, .rightReact = rightReact2};
sub_t SUB3 = { .leftReact=leftReact3, .rightReact = rightReact3};



menu_t menu = {.handleLeft=handleLeft,.handleRight=handleRight};

int main(int argc, char const *argv[])
{
    SUB1.last = &SUB3;
    SUB1.next = &SUB2;
    SUB2.last = &SUB1;
    SUB2.next = &SUB3;
    SUB3.last = &SUB2;
    SUB3.next = &SUB1;
    menu.currentMenu = &SUB1;

    int switchEroo=3;

    
    while (1)
    {
        scanf("%d",&switchEroo);
        if (switchEroo == 0)
        {
            menu.handleLeft(&menu);
            continue;
        }
        if (switchEroo == 1)
        {
            menu.handleRight(&menu);
            continue;
        }
        Sleep(100);
    }
    
    return 0;
}
