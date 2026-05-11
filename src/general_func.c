#include "utils.h"
#include <windows.h>

void gotoxy(int x, int y)
{
    static HANDLE hConsole = NULL;
    if (hConsole == NULL)
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(short)x, (short)y};
    SetConsoleCursorPosition(hConsole, pos);
}
