#include "login.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define S 83
#define s 115

static void edit_data(User *target, int current_choice);
static void display_info(const int current_choice);
static int verify_user(const User *head, const User *target);

void user_login(const User *head, char *logged_username)
{
    User cache;
    int added = 0;

    system("cls");
    printf("登入\n正在以现有的用户登入。\n\n");
    printf("    %-17s\n", "用户名");
    printf("    %-16s\n", "密码");
    printf("\n");

    int current_choice = 0;
    while (1)
    {
        gotoxy(0, 6);
        if (added == 3)
            printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ S ] 提交登入  [ Esc ] 放弃登入");
        else if (added & 1 << current_choice)
            printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 放弃登入");
        else
            printf("[ ↑/↓ ] 选择  [ Enter ] 键入  [ Esc ] 放弃登入");
        printf("\n\33[K\n\n\33[K");

        int key;
        gotoxy(0, current_choice + 3);
        printf("-> ");
        do
        {
            key = _getch();
            if (added == 3 && (key == S || key == s))
            {
                if (!verify_user(head, &cache))
                    break;
                strcpy(logged_username, cache.username);
                gotoxy(0, 6);
                printf("\33[K已登入\n  登入成功。");
                Sleep(1000);
                return;
            }
        } while (key != 224 && key != ENTER && key != ESC);
        if (key == 224)
        {
            key = _getch();
            gotoxy(0, current_choice + 3);
            printf("   ");
            if (key == UP || key == DOWN)
                current_choice = current_choice ? 0 : 1;
        }
        else if (key == ENTER)
        {
            gotoxy(0, 9);
            printf("\33[K[ Enter ] 确定\n");
            edit_data(&cache, current_choice);
            added |= 1 << current_choice;
            if (current_choice != 1)
            {
                gotoxy(0, current_choice + 3);
                printf("   ");
                current_choice++;
            }
        }
        else if (key == ESC)
            return;
    }
}

// 修改 target 的第 current_choice 条信息
static void edit_data(User *target, int current_choice)
{
    display_info(current_choice);
    gotoxy(18, current_choice + 3);
    printf("\33[K");
    if (current_choice == 0)
    {
        char new_username[20];
        safe_input(new_username, sizeof(new_username));
        strcpy(target->username, new_username);
    }
    else
    {
        char new_password[20];
        safe_input(new_password, sizeof(new_password));
        strcpy(target->password, new_password);
    }
}

static void display_info(const int current_choice)
{
    gotoxy(0, 6);
    printf("\33[K信息\n  ");
    if (current_choice == 0)
        printf("输入用户名。");
    else
        printf("输入密码。");
}

// 将用户输入的信息 target 与用户数据比对，返回比对结果
static int verify_user(const User *head, const User *target)
{
    for (const User *p = head; p; p = p->next)
    {
        if (strcmp(p->username, target->username) == 0)
            if (strcmp(p->password, target->password) == 0)
                return 1;
            else
            {
                gotoxy(0, 6);
                printf("\33[K无法登入\n  密码不正确，请重试。");
                Sleep(1000);
                return 0;
            }
    }
    gotoxy(0, 6);
    printf("\33[K无法登入\n  用户名不存在，请重试。");
    Sleep(1000);
    return 0;
}
