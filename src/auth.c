#include "auth.h"
#include <stdio.h>
#include <windows.h>
#include "utils.h"

static char username[20];
static char password[20];
static char confirm_password[20];
static char phone[20];

void gotoxy(int, int);
int user_register();
int is_digit_or_letter_str(char *);
int is_digit_str(char *);
void display();

int user_register()
{
    const char users_file[] = "data/users.txt";
    FILE *fp = fopen(users_file, "w");
    if (fp == NULL)
    {
        printf("无法创建数据文件。\n");
        return 1;
    }

    system("cls");

    while (1)
    {
        display();
        gotoxy(12, 2);
        scanf("%s", username);
        if (strlen(username) >= 6 && strlen(username) <= 16 && is_digit_or_letter_str(username))
        {
            fprintf(fp, "username: %s\n", username);
            break;
        }
        username[0] = '\0';
        display();
        gotoxy(12, 2);
        printf("请输入合法的用户名。");
        Sleep(1000);
        gotoxy(12, 2);
        printf("                   ");
    }

    while (1)
    {
        display();
        gotoxy(12, 3);
        scanf("%s", password);
        if (strlen(password) >= 4 && strlen(password) <= 16 && is_digit_or_letter_str(password))
        {
            fprintf(fp, "password: %s\n", password);
            break;
        }
        password[0] = '\0';
        display();
        gotoxy(12, 3);
        printf("请输入合法的密码。");
        Sleep(1000);
        gotoxy(12, 3);
        printf("                 ");
    }

    while (1)
    {
        display();
        gotoxy(12, 4);
        scanf("%s", confirm_password);
        if (strcmp(password, confirm_password) == 0)
            break;
        confirm_password[0] = '\0';
        display();
        gotoxy(12, 4);
        printf("两次输入的密码不一致，请重新输入。");
        Sleep(1000);
        gotoxy(12, 4);
        printf("                                 ");
    }

    while (1)
    {
        display();
        gotoxy(12, 5);
        scanf("%s", phone);
        if (strlen(phone) == 11 && is_digit_str(phone))
        {
            fprintf(fp, "phone: %s\n", phone);
            break;
        }
        phone[0] = '\0';
        display();
        gotoxy(12, 5);
        printf("请输入合法的手机号。");
        Sleep(1000);
        gotoxy(12, 5);
        printf("                   ");
    }

    display();
    printf("\n注册成功！\n");
    Sleep(1000);
    fclose(fp);
    return 0;
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

void display()
{
    gotoxy(0, 7);
    printf("\33[K\n\33[K");
    gotoxy(0, 0);
    printf("用户注册\n\n");
    printf("%-16s%s\n", "用户昵称", username);
    printf("%-16s%s\n", "登录密码", password);
    printf("%-16s%s\n", "确认密码", confirm_password);
    printf("%-15s%s\n", "手机号", phone);
    if (!*username)
        printf("\n信息\n  用户名只能由字母或数字组成，且位数在 6-16 位之间。\n");
    else if (!*password)
        printf("\n信息\n  密码位数在 4-16 位之间。\n");
    else if (*confirm_password && !*phone)
        printf("\n信息\n  请输入 11 位手机号。\n");
}
