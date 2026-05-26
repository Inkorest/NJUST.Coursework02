#include "ui_auth.h"
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "login.h"
#include "register.h"
#include "db_storage.h"

static int menu_main();
static void menu_login();
static void menu_register();
static void free_user_data(User *head);

int ui_auth()
{
    load_user_data(&g_user_head);
    do
        switch (menu_main())
        {
        case 0:
            menu_login();
            break;
        case 1:
            menu_register();
            break;
        case 2:
        case -1:
            free_user_data(g_user_head);
            return -1;
        }
    while (!*g_logged_username);
    free_user_data(g_user_head);
    return 1;
}

static int menu_main()
{
    const char *overview[] = {
        "学生信息管理系统",
        "请登入系统。",
        NULL};
    const char *choices[] = {
        "登入",
        "注册",
        "退出系统",
        NULL};
    const char *information[] = {
        "以现有的用户登入。",
        "注册新的用户。",
        "退出系统并结束。",
        NULL};
    return menu(overview, choices, information);
}

static void menu_login()
{
    user_login(g_user_head, g_logged_username);
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

// 释放用户数据链表
static void free_user_data(User *head)
{
    while (head)
    {
        User *temp = head;
        head = head->next;
        free(temp);
    }
}
