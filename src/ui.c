#include "ui.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menu.h"
#include "menu_edit.h"
#include "list.h"
#include "list_search.h"

typedef int (*MenuFunc)();

static int menu_main();
static int menu_search();
static int menu_display();
static int menu_sort(int sort_by);
static int list_sorted();
static int menu_statistics();

void ui(Student *head)
{
    int current_page = 0;

    MenuFunc menu_table[] = {menu_main, menu_search, menu_display, menu_statistics, list_sorted};

    while (current_page != -1)
        current_page = menu_table[current_page]();
}

static int menu_main() // Menu 0
{
    const char *overview[] = {
        "学生信息管理系统",
        "主菜单",
        NULL};
    const char *choices[] = {
        "录入学生信息",
        "查找学生信息",
        "输出学生信息",
        "统计学生成绩",
        "登出",
        NULL};
    const char *information[] = {
        "录入新的学生信息。",
        "通过学号或姓名查找学生信息。",
        "按指定的排序方式输出学生信息。",
        "统计所有学生的成绩。",
        "登出系统。",
    };

    while (1)
    {
        int choice = menu(overview, choices, information);
        if (choice == 4)
            return -1;
        if (choice == 0)
            add_student(&student_head);
        else
            return choice;
    }
}

static int menu_search() // Menu 1
{
    const char *overview[] = {
        "主菜单 -> 查找学生信息",
        "通过学号或姓名查找学生信息。",
        "你想通过什么方式查找？",
        NULL};
    const char *choices[] = {
        "学号",
        "姓名",
        NULL};
    const char *information[] = {
        "通过学号查找学生信息。",
        "通过姓名查找学生信息。",
        NULL};
    while (1)
    {
        int choice = menu(overview, choices, information);
        if (choice == -1)
            return 0;
        Student *target = list_search(choice);
        if (target)
            menu_edit(student_head, target);
        return 0;
    }
}

static int menu_display() // Menu 2
{
    const char *overview[] = {
        "主菜单 -> 输出学生信息",
        "按指定的排序方式输出学生信息。",
        "你想以何种数据作为排序依据？",
        NULL};
    const char *choices[] = {
        "学号",
        "姓名",
        "专业",
        "总成绩",
        NULL};
    const char *information[] = {
        "按学号排序。",
        "按姓名排序。",
        "按专业排序。",
        "按总成绩排序。",
        NULL};
    while (1)
    {
        int choice = menu(overview, choices, information);
        if (choice == -1)
            return 0;
        else if (menu_sort(choice))
            return 4;
    }
}

static int menu_sort(int sort_by)
{
    const char *breadcrumbs[] = {
        "主菜单 -> 输出学生信息 -> 按学号排序",
        "主菜单 -> 输出学生信息 -> 按姓名排序",
        "主菜单 -> 输出学生信息 -> 按专业排序",
        "主菜单 -> 输出学生信息 -> 按总成绩排序",
        NULL};
    const char *overview[] = {
        breadcrumbs[sort_by],
        "选择排序方式。",
        NULL};
    const char *choices[] = {
        "升序",
        "降序",
        NULL};
    const char *information[] = {
        "按升序排序。",
        "按降序排序。",
        NULL};
    while (1)
    {
        int choice = menu(overview, choices, information);
        if (choice == -1)
            return 0;
        switch (sort_by)
        {
        case 0:
            student_head = merge_sort(student_head, choice == 0, sort_by_id);
            break;
        case 1:
            student_head = merge_sort(student_head, choice == 0, sort_by_name);
            break;
        case 2:
            student_head = merge_sort(student_head, choice == 0, sort_by_major);
            break;
        case 3:
            student_head = merge_sort(student_head, choice == 0, sort_by_total_score);
            break;
        }
        return 1;
    }
}

static int list_sorted() // Menu 4
{
    const char *overview[] = {"输出学生信息", "正在按指定的排序方式输出学生信息列表。", NULL};
    Student *target = list(overview, student_head);
    if (target)
        menu_edit(student_head, target);
    return 0;
}

static int menu_statistics() // Menu 3
{
    system("cls");
    printf("学生成绩统计\n正在统计已录入的学生信息。\n\n");
    student_statistics(student_head);
    printf("\n[ Esc ] 退出\n");
    int key;
    do
        key = _getch();
    while (key != 27);
    return 0;
}
