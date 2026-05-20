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

int is_digit_or_letter_str(char *str)
{
    do
        if (!isalnum(*str))
            return 0;
    while (*++str);
    return 1;
}

int is_digit_str(char *str)
{
    do
        if (!isdigit(*str))
            return 0;
    while (*++str);
    return 1;
}

int check_unique_id(const char *id, Student *head)
{
    while (head)
    {
        if (strcmp(head->id, id) == 0)
            return 0;
        head = head->next;
    }
    return 1;
}
