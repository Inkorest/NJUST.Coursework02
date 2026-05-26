#include <stdio.h>
#include <windows.h>
#include "ui_auth.h"
#include "ui.h"

typedef int (*UiFunc_t)();

int main()
{
    int current_page = 0;
    const UiFunc_t menu_table[] = {ui_auth, ui};
    while (current_page != -1)
        current_page = menu_table[current_page]();
    system("cls");
    printf("已退出系统。\n");
    return 0;
}
