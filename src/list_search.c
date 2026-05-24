#include "list_search.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

static void free_index_list(Index *head);

Student *list_search(int search_by)
{
    char query[20];
    if (search_by == 0)
    {
        printf("主菜单 -> 查找学生信息 -> 通过学号查找\n");
        printf("通过学号查找学生信息。\n\n");
        printf("请输入要查找的学号: ");
        while (1)
        {
            scanf("%s", query);
            if (strlen(query) <= 16 && is_digit_str(query))
                break;
            gotoxy(20, 3);
            printf("请输入16位以内的合法学号。\n");
            Sleep(1000);
            gotoxy(20, 3);
            printf("\33[K");
        }
    }
    else
    {
        printf("主菜单 -> 查找学生信息 -> 通过姓名查找\n");
        printf("通过姓名查找学生信息。\n\n");
        printf("请输入要查找的姓名: ");
        while (1)
        {
            scanf("%s", query);
            if (strlen(query) <= 16 && is_digit_or_letter_str(query))
                break;
            gotoxy(20, 3);
            printf("请输入16位以内的合法姓名。\n");
            Sleep(1000);
            gotoxy(20, 3);
            printf("\33[K");
        }
    }

    Index *index_head = search_student(search_by, query);

    system("cls");
    printf("查找学生信息\n");

    if (index_head == NULL)
    {
        printf("未能找到关于\"%s\"的结果。\n", query);
        printf("按任意键返回…\n");
        _getch();
        return NULL;
    }

    int current_selected = 0;
    int student_count = 0;
    Index *current = index_head;
    while (current)
    {
        student_count++;
        current = current->next;
    }

    printf("正在输出查找结果。\n");
    printf("找到关于\"%s\"的 %d 条结果。\n\n", query, student_count);

    current = index_head;
    printf("    %-12s%-12s%-14s%-12s%-12s%-12s%-12s%-12s%-13s\n", "学号", "姓名", "专业", "成绩1", "成绩2", "成绩3", "成绩4", "成绩5", "总成绩");
    while (current)
    {
        printf("    %-10s%-10s%-12s%-10d%-10d%-10d%-10d%-10d%-10d\n", current->target->id, current->target->name, current->target->major, current->target->score[0],
               current->target->score[1], current->target->score[2], current->target->score[3], current->target->score[4], current->target->total_score);
        current = current->next;
    }
    printf("\n信息\n  选择记录以查看详情。\n\n");
    printf("[ ↑/↓ ] 选择  [ Enter ] 确定  [ Esc ] 返回\n");

    while (1)
    {
        int key;
        gotoxy(0, current_selected + 5);
        printf("-> ");
        do
            key = _getch();
        while (key != 224 && key != ENTER && key != ESC);
        if (key == 224)
        {
            key = _getch();
            printf("\b\b\b  ");
            if (key == UP)
                current_selected = current_selected ? (current_selected - 1) : (student_count - 1);
            if (key == DOWN)
                current_selected = current_selected != student_count - 1 ? (current_selected + 1) : 0;
        }
        else if (key == ENTER)
        {
            Index *index_target = index_head;
            for (int i = 0; i < current_selected; i++)
                index_target = index_target->next;
            Student *result = index_target->target;
            free_index_list(index_head);
            return result;
        }
        else
        {
            free_index_list(index_head);
            return NULL;
        }
    }
}

static void free_index_list(Index *head)
{
    while (head)
    {
        Index *temp = head;
        head = head->next;
        free(temp);
    }
}
