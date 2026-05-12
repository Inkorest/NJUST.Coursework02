#include "auth.h"
#include <stdio.h>
#include <windows.h>
#include "utils.h"

static char username[20];
static char password[20];
static char confirm_password[20];
static char phone[20];

static void register_display();

void user_register()
{
    const char users_file[] = "data/users.txt";
    FILE *fp = fopen(users_file, "w");
    if (fp == NULL)
    {
        printf("无法创建数据文件。\n");
        exit(1);
    }

    system("cls");
    register_display();

    gotoxy(0, 7);
    printf("信息\n  用户名只能由字母或数字组成，且位数在 6-16 位之间。\n");

    while (1)
    {
        gotoxy(12, 2);
        printf("\33[K");
        scanf("%s", username);
        if (strlen(username) >= 6 && strlen(username) <= 16 && is_digit_or_letter_str(username))
        {
            fprintf(fp, "username: %s\n", username);
            break;
        }
        gotoxy(12, 2);
        printf("\33[K请输入合法的用户名。");
        Sleep(1000);
    }
    gotoxy(0, 8);
    printf("\33[K  密码位数在 4-16 位之间。\n");

    while (1)
    {
        gotoxy(12, 3);
        printf("\33[K");
        scanf("%s", password);
        if (strlen(password) >= 4 && strlen(password) <= 16 && is_digit_or_letter_str(password))
        {
            fprintf(fp, "password: %s\n", password);
            break;
        }
        gotoxy(12, 3);
        printf("\33[K请输入合法的密码。");
        Sleep(1000);
    }

    gotoxy(0, 8);
    printf("\33[K  再次输入密码。\n");

    while (1)
    {
        gotoxy(12, 4);
        printf("\33[K");
        scanf("%s", confirm_password);
        if (strcmp(password, confirm_password) == 0)
            break;
        gotoxy(12, 4);
        printf("\33[K两次输入的密码不一致，请重新输入。");
        Sleep(1000);
    }

    gotoxy(0, 8);
    printf("\33[K  请输入 11 位手机号。\n");

    while (1)
    {
        gotoxy(12, 5);
        printf("\33[K");
        scanf("%s", phone);
        if (strlen(phone) == 11 && is_digit_str(phone))
        {
            fprintf(fp, "phone: %s\n", phone);
            break;
        }
        gotoxy(12, 5);
        printf("\33[K请输入合法的手机号。");
        Sleep(1000);
    }

    gotoxy(0, 7);
    printf("\33[K\n\33[K");
    gotoxy(0, 7);
    printf("\n注册成功。\n");
    Sleep(1000);
    fclose(fp);
}

void register_display()
{
    gotoxy(0, 0);
    printf("用户注册\n\n");
    printf("%-16s\n", "用户昵称");
    printf("%-16s\n", "登录密码");
    printf("%-16s\n", "确认密码");
    printf("%-15s\n", "手机号");
}
