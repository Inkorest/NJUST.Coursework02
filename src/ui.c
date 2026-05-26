#include "ui.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"
#include "menu.h"
#include "menu_edit.h"
#include "list.h"
#include "list_search.h"
#include "db_storage.h"

#define ENTER 13
#define DEL 83
#define ESC 27

typedef enum
{
    MENU_MAIN = 0,
    MENU_SEARCH,
    MENU_DISPLAY,
    MENU_STATISTICS,
    MENU_QUERY,
    MENU_SORT,
    LIST_SORTED,
    LIST_SEARCHED,
    DETAILS_STUDENT,
    CONFIRM_DELETE,
    SUCCEED_DELETE
} MenuId_t;

typedef MenuId_t (*MenuFunc_t)();

static Student *s_target = NULL;
static int s_menu_sort_sort_by = 0;
static int s_menu_edit_mode = 0;
static int s_menu_search_search_by = 0;
static char query[24];
Index *s_index_head = NULL;
static MenuId_t s_source_menu = 0;

static MenuId_t menu_main();       // Menu 0
static MenuId_t menu_search();     // Menu 1
static MenuId_t menu_display();    // Menu 2
static MenuId_t menu_statistics(); // Menu 3
// static MenuId_t menu_edit();   // Menu 4
static MenuId_t menu_query();      // Menu 4
static MenuId_t menu_sort();       // Menu 5
static MenuId_t list_sorted();     // Menu 6
static MenuId_t list_searched();   // Menu 7
static MenuId_t details_student(); // Menu 8
static MenuId_t confirm_delete();  // Menu 9
static MenuId_t succeed_delete();  // Menu 10

int ui()
{
    load_student_data(g_logged_username, &g_student_head);
    int current_page = 0;
    const MenuFunc_t menu_table[] = {menu_main,
                                     menu_search,
                                     menu_display,
                                     menu_statistics,
                                     menu_query,
                                     menu_sort,
                                     list_sorted,
                                     list_searched,
                                     details_student,
                                     confirm_delete,
                                     succeed_delete};
    while (current_page != -1)
        current_page = menu_table[current_page]();
    save_student_data(g_logged_username, g_student_head);
    system("cls");
    printf("已登出。");
    Sleep(1000);
    return 0;
}

static MenuId_t menu_main() // Menu 0
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
            add_student(&g_student_head);
        else
            return choice;
    }
}

static MenuId_t menu_search() // Menu 1
{
    if (!g_student_head)
    {
        system("cls");
        printf("查找学生信息\n\n");
        printf("一个学生都没有嘛！\n");
        printf("按任意键返回…\n");
        _getch();
        return 0;
    }
    const char *overview[] = {
        "主菜单 -> 查找学生信息",
        "通过学号或姓名查找学生信息。",
        "你想通过什么方式查找？",
        NULL};
    const char *choices[] = {
        "学号",
        "姓名",
        "专业",
        NULL};
    const char *information[] = {
        "通过学号查找学生信息。",
        "通过姓名查找学生信息。",
        "通过专业查找学生信息。",
        NULL};
    s_menu_search_search_by = menu(overview, choices, information);
    if (s_menu_search_search_by == -1)
        return MENU_MAIN;
    return MENU_QUERY;
}

static MenuId_t menu_query() // Menu 4
{
    system("cls");
    switch (s_menu_search_search_by)
    {
    case 0:
        printf("主菜单 -> 查找学生信息 -> 通过学号查找\n");
        printf("通过学号查找学生信息。\n\n");
        printf("请输入要查找的学号: ");
        while (1)
        {
            safe_input(query, sizeof(query));
            if (strlen(query) <= 16 && is_digit_str(query))
                break;
            gotoxy(20, 3);
            printf("请输入 16 位以内的合法学号。\n");
            Sleep(1000);
            gotoxy(20, 3);
            printf("\33[K");
        }
        break;
    case 1:
        printf("主菜单 -> 查找学生信息 -> 通过姓名查找\n");
        printf("通过姓名查找学生信息。\n\n");
        printf("请输入要查找的姓名: ");
        while (1)
        {
            safe_input(query, sizeof(query));
            if (strlen(query) <= 20 && is_digit_or_letter_or_blank_str(query))
                break;
            gotoxy(20, 3);
            printf("请输入 20 位以内的合法姓名。\n");
            Sleep(1000);
            gotoxy(20, 3);
            printf("\33[K");
        }
        break;
    case 2:
        printf("主菜单 -> 查找学生信息 -> 通过专业查找\n");
        printf("通过专业查找学生信息。\n\n");
        printf("请输入要查找的专业: ");
        while (1)
        {
            safe_input(query, sizeof(query));
            if (strlen(query) <= 20 && is_digit_or_letter_or_blank_str(query))
                break;
            gotoxy(20, 3);
            printf("请输入 20 位以内的合法专业。\n");
            Sleep(1000);
            gotoxy(20, 3);
            printf("\33[K");
        }
        break;
    }
    return LIST_SEARCHED;
}

static MenuId_t list_searched() // Menu 7
{
    s_index_head = search_student(s_menu_search_search_by, query);
    s_target = list_search(s_index_head, query);
    if (s_target)
    {
        s_source_menu = LIST_SEARCHED;
        return DETAILS_STUDENT;
    }
    else
        return MENU_MAIN;
}

static MenuId_t menu_display() // Menu 2
{
    if (!g_student_head)
    {
        system("cls");
        printf("输出学生信息\n\n");
        printf("一个学生都没有嘛！\n");
        printf("按任意键返回…\n");
        _getch();
        return 0;
    }
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
        s_menu_sort_sort_by = menu(overview, choices, information);
        if (s_menu_sort_sort_by == -1)
            return MENU_MAIN;
        return MENU_SORT;
    }
}

static MenuId_t menu_sort() // Menu 5
{
    const char *breadcrumbs[] = {
        "主菜单 -> 输出学生信息 -> 按学号排序",
        "主菜单 -> 输出学生信息 -> 按姓名排序",
        "主菜单 -> 输出学生信息 -> 按专业排序",
        "主菜单 -> 输出学生信息 -> 按总成绩排序",
        NULL};
    const char *overview[] = {
        breadcrumbs[s_menu_sort_sort_by],
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
            return MENU_DISPLAY;
        switch (s_menu_sort_sort_by)
        {
        case 0:
            g_student_head = merge_sort(g_student_head, choice == 0, sort_by_id);
            break;
        case 1:
            g_student_head = merge_sort(g_student_head, choice == 0, sort_by_name);
            break;
        case 2:
            g_student_head = merge_sort(g_student_head, choice == 0, sort_by_major);
            break;
        case 3:
            g_student_head = merge_sort(g_student_head, choice == 0, sort_by_total_score);
            break;
        }
        return LIST_SORTED;
    }
}

static MenuId_t list_sorted() // Menu 6
{
    s_target = list(g_student_head);
    if (s_target)
    {
        s_source_menu = LIST_SORTED;
        return DETAILS_STUDENT;
    }
    else
        return MENU_MAIN;
}

static MenuId_t menu_statistics() // Menu 3
{
    system("cls");
    printf("统计学生成绩\n正在统计已录入的学生信息。\n\n");
    student_statistics(g_student_head);
    printf("\n[ Esc ] 退出\n");
    int key;
    do
        key = _getch();
    while (key != ESC);
    return MENU_MAIN;
}

static MenuId_t details_student() // Menu 8
{
    system("cls");
    printf("查看学生信息\n正在查看此学生的详细信息。\n\n");
    printf("%-16s%s\n", "学号", s_target->id);
    printf("%-16s%s\n", "姓名", s_target->name);
    printf("%-16s%s\n", "专业", s_target->major);
    printf("%-16s%d\n", "成绩1", s_target->score[0]);
    printf("%-16s%d\n", "成绩2", s_target->score[1]);
    printf("%-16s%d\n", "成绩3", s_target->score[2]);
    printf("%-16s%d\n", "成绩4", s_target->score[3]);
    printf("%-16s%d\n", "成绩5", s_target->score[4]);
    printf("%-18s%.2f\n", "平均成绩", (double)s_target->total_score / 5);
    printf("%-17s%d\n", "总成绩", s_target->total_score);
    printf("\n");
    printf("[ Enter ] 修改  [ Delete ] 删除  [ Esc ] 返回\n");

    int key;
    do
    {
        key = _getch();
        if (key == 224 && _getch() == DEL)
            return CONFIRM_DELETE;
    } while (key != ENTER && key != ESC);
    if (key == ENTER)
    {
        s_menu_edit_mode = 0;
        menu_edit(g_student_head, s_target, s_menu_edit_mode);
        return DETAILS_STUDENT;
    }
    else
        return s_source_menu;
}

static MenuId_t confirm_delete() // Menu 9
{
    system("cls");
    printf("信息\n\n");
    printf("删除学生信息\n\n");
    printf("即将删除此学生的学生信息，可以吗？\n");
    printf("此操作不能撤销。\n\n");
    printf("[ Enter ] 确定  [ Esc ] 取消\n");
    int key;
    do
        key = _getch();
    while (key != ENTER && key != ESC);
    if (key == ENTER)
        return SUCCEED_DELETE;
    else
        return DETAILS_STUDENT;
}

static MenuId_t succeed_delete() // Menu 10
{
    delete_student(&g_student_head, s_target);
    if (s_source_menu == LIST_SEARCHED)
    {
        Index *current = s_index_head;
        Index *prev = NULL;
        while (current)
        {
            if (current->target == s_target)
            {
                if (prev)
                    prev->next = current->next;
                else
                    s_index_head = current->next;
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
    }
    system("cls");
    printf("信息\n\n");
    printf("删除学生信息\n\n");
    printf("成功删除了此学生的学生信息。\n");
    Sleep(1000);
    return s_source_menu;
}
