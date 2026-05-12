#include "ui.h"
#include <stdio.h>
#include <windows.h>
#include "menu.h"
#include "student.h"

static void main_menu();

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
            display_student_list(head);
            break;
        case 3:
            break;
        case 4:
            return;
        }
    }
}
