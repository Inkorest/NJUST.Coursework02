#include "utils.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

// 安全输入函数
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

// 将终端光标移至位置 (x,y) 
void gotoxy(int x, int y)
{
    static HANDLE hConsole = NULL;
    if (hConsole == NULL)
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(short)x, (short)y};
    SetConsoleCursorPosition(hConsole, pos);
}

// 检查字符串 str 是否仅由字母、数字或空格组成
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

// 检查字符串 str 是否仅由字母或数字组成
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

// 检查字符串 str 是否仅由数字组成
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

// 检查 username 在链表 head 中是否不重复
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

// 检查 id 在链表 head 中是否不重复
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
