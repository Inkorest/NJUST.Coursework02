#include "ui.h"
#include <stdio.h>
#include <windows.h>
#include "menu.h"
#include "list.h"
#include "student.h"

static void main_menu();
static void display_student_menu();
static void sort_menu(int sort_by);
static void list_menu(Student *head);

void ui()
{
    main_menu();
}

static void main_menu()
{
    const char *overview[] = {
        "学生信息管理系统",
        "主菜单",
        NULL};
    const char *choices[] = {
        "录入学生信息",
        "查询学生信息",
        "输出学生信息",
        "统计学生成绩",
        "登出",
        NULL};
    const char *information[] = {
        "录入新的学生信息。",
        "通过学号或姓名查询学生信息。",
        "按指定的排序方式输出学生信息。",
        "统计所有学生的成绩。",
        "登出系统。",
    };
    while (1)
    {
        int choice = menu(overview, choices, information);
        switch (choice)
        {
        case 0:
            add_student(&head);
            break;
        case 1:
            break;
        case 2:
            display_student_menu();
            break;
        case 3:
            break;
        case 4:
        case -1:
            return;
        }
    }
}

static void display_student_menu()
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
            return;
        else
            sort_menu(choice);
    }
}

static void sort_menu(int sort_by)
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
            return;
        switch (sort_by)
        {
        case 0:
            head = merge_sort(head, choice == 0, sort_by_id);
            break;
        case 1:
            head = merge_sort(head, choice == 0, sort_by_name);
            break;
        case 2:
            head = merge_sort(head, choice == 0, sort_by_major);
            break;
        case 3:
            head = merge_sort(head, choice == 0, sort_by_total_score);
            break;
        }
        list_menu(head);
    }
}

static void list_menu(Student *head)
{
    const char *overview[] = {"学生信息", NULL};
    Student *target = list(overview, head);
    if (target)
        ;
    return;
}
