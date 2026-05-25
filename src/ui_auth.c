#include "ui_auth.h"
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "register.h"
#include "storage.h"
#include "ui.h"

static void menu_main();
static void menu_login();
static void menu_register();
static void free_user_list(User *head);

void ui_auth()
{
    load_user_data();
    menu_main();
    free_user_list(g_user_head);
}

static void menu_main()
{
    const char *overview[] = {
        "学生信息管理系统",
        "请登入系统。",
        NULL};
    const char *choices[] = {
        "登录",
        "注册",
        "退出系统",
        NULL};
    const char *information[] = {
        "以现有的用户登录。",
        "注册新的用户。",
        "退出系统并结束。",
        NULL};

    while (1)
    {
        int choice = menu(overview, choices, information);
        switch (choice)
        {
        case 0:
            ui(g_student_head);
            // menu_login();
            break;
        case 1:
            menu_register();
            break;
        case 2:
        case -1:
            return;
        }
    }
}

static void menu_login()
{
}

static void menu_register()
{
    User *new_user = (User *)malloc(sizeof(*new_user));
    if (!new_user)
    {
        printf("内存分配失败。\n");
        return;
    }
    user_register(g_user_head, new_user);
    save_user_data(new_user);
    new_user->next = g_user_head;
    g_user_head = new_user;
}

static void free_user_list(User *head)
{
    while (head)
    {
        User *temp = head;
        head = head->next;
        free(temp);
    }
}
