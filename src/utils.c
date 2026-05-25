#include "utils.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

void safe_input(char *buffer, int length)
{
    if (!fgets(buffer, length, stdin))
        return;
    int l = strlen(buffer);
    if (l > 0 && buffer[l - 1] == '\n')
        buffer[l - 1] = '\0';
    else
        while (getchar() != '\n')
            ;
}

void gotoxy(int x, int y)
{
    static HANDLE hConsole = NULL;
    if (hConsole == NULL)
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(short)x, (short)y};
    SetConsoleCursorPosition(hConsole, pos);
}

int is_digit_or_letter_or_blank_str(char *str)
{
    while (*str)
    {
        if (!isalnum(*str) && *str != ' ')
            return 0;
        str++;
    }
    return 1;
}

int is_digit_or_letter_str(char *str)
{
while (*str)
    {
        if (!isalnum(*str))
            return 0;
        str++;
    }
    return 1;
}

int is_digit_str(char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

int check_unique_username(const char *username, User *head)
{
    while (head)
    {
        if (strcmp(head->username, username) == 0)
            return 0;
        head = head->next;
    }
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
