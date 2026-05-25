#include "register.h"
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

static void edit_data(User *head, User *target, int current_choice);
static void display_info(const int current_choice);

void user_register(User *head, User *target)
{
    User cache;
    int added = 0;

    system("cls");
    printf("注册\n正在注册新的用户。\n\n");
    printf("    %-17s\n", "用户名");
    printf("    %-16s\n", "密码");
    printf("    %-18s\n", "确认密码");
    printf("    %-17s\n", "手机号");
    printf("\n");

    int current_choice = 0;
    while (1)
    {
        gotoxy(0, 8);
        if (added == 15)
            printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ S ] 完成注册  [ Esc ] 放弃注册");
        else if (added & 1 << current_choice)
            printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 放弃注册");
        else
            printf("[ ↑/↓ ] 选择  [ Enter ] 键入  [ Esc ] 放弃注册");
        printf("\n\33[K\n\n\33[K");

        int key;
        gotoxy(0, current_choice + 3);
        printf("-> ");
        do
        {
            key = _getch();
            if (added == 15 && (key == S || key == s))
            {
                *target = cache;
                return;
            }
        } while (key != 224 && key != ENTER && key != ESC);
        if (key == 224)
        {
            key = _getch();
            gotoxy(0, current_choice + 3);
            printf("   ");
            if (key == UP)
                current_choice = current_choice ? (current_choice - 1) : 3;
            if (key == DOWN)
                current_choice = current_choice != 3 ? (current_choice + 1) : 0;
        }
        else if (key == ENTER)
        {
            gotoxy(0, 11);
            printf("\33[K[ Enter ] 确定\n");
            edit_data(head, &cache, current_choice);
            added |= 1 << current_choice;
            if (current_choice != 3)
            {
                gotoxy(0, current_choice + 3);
                printf("   ");
                current_choice++;
            }
        }
        else
            return;
    }
}

static void edit_data(User *head, User *target, int current_choice)
{
    display_info(current_choice);
    gotoxy(18, current_choice + 3);
    printf("\33[K");
    switch (current_choice)
    {
    case 0:
    {
        char new_username[20];
        while (1)
        {
            scanf("%s", new_username);
            gotoxy(18, 3);
            if (strlen(new_username) >= 6 && strlen(new_username) <= 16 && is_digit_or_letter_str(new_username))
            {
                if (!strcmp(target->username, new_username) || check_unique_username(new_username, head))
                {
                    strcpy(target->username, new_username);
                    break;
                }
                printf("\33[K用户名已存在，请重新输入。");
            }
            else
                printf("\33[K请输入 6 到 16 位之间的合法用户名。");
            Sleep(1000);
            gotoxy(18, 3);
            printf("\33[K");
        }
        strcpy(target->username, new_username);
        break;
    }
    case 1:
    {
        char new_password[20];
        while (1)
        {
            safe_input(new_password, sizeof(new_password));
            if (strlen(new_password) < 20 && is_digit_or_letter_str(new_password))
                break;
            gotoxy(18, 4);
            printf("\33[K请输入 4 到 16 位之间的合法密码。");
            Sleep(1000);
            gotoxy(18, 4);
            printf("\33[K");
        }
        strcpy(target->password, new_password);
        break;
    }
    case 2:
    {
        char new_confirm_password[20];
        while (1)
        {
            safe_input(new_confirm_password, sizeof(new_confirm_password));
            if (!strcmp(new_confirm_password, target->password))
                break;
            gotoxy(18, 5);
            printf("\33[K密码不匹配，请重新输入。");
            Sleep(1000);
            gotoxy(18, 5);
            printf("\33[K");
        }
        break;
    }
    case 3:
    {
        char new_phone[20];
        while (1)
        {
            safe_input(new_phone, sizeof(new_phone));
            if (strlen(new_phone) == 11 && is_digit_str(new_phone))
                break;
            gotoxy(18, 6);
            printf("\33[K请输入 11 位的合法手机号。");
            Sleep(1000);
            gotoxy(18, 6);
            printf("\33[K");
        }
        strcpy(target->phone, new_phone);
        break;
    }
    }
}

static void display_info(const int current_choice)
{
    gotoxy(0, 8);
    printf("\33[K信息\n  ");
    switch (current_choice)
    {
    case 0:
        printf("输入 6 到 16 位之间的用户名，用户名由字母和数字组成。");
        break;
    case 1:
        printf("输入 4 到 16 位之间的密码，密码由字母和数字组成。");
        break;
    case 2:
        printf("再次输入密码。");
        break;
    case 3:
        printf("输入 11 位的手机号。");
        break;
    }
}

/*
注册
正在注册新的用户。

    用户名
    密码
    确认密码
    手机号

信息
  <Info Message>

[ ↑/↓ ] 选择  [ Enter ] 键入  [ Esc ] 放弃注册
*/
