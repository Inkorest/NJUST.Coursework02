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

// 输出查找后的学生信息列表，返回用户选定的学生的结构体指针
Student *list_search(Index *index_head, char *query)
{
    system("cls");
    printf("查找学生信息\n");

    if (index_head == NULL)
    {
        printf("\n未能找到关于\"%s\"的结果。\n", query);
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
    printf("    %-18s%-22s%-22s%-12s%-12s%-12s%-12s%-12s%-13s\n", "学号", "姓名", "专业", "成绩1", "成绩2", "成绩3", "成绩4", "成绩5", "总成绩");
    while (current)
    {
        printf("    %-16s%-20s%-20s%-10d%-10d%-10d%-10d%-10d%-10d\n", current->target->id, current->target->name, current->target->major, current->target->score[0],
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
            return result;
        }
        else
        {
            free_index_list(index_head);
            return NULL;
        }
    }
}

// 以 query 为关键词，search_by 为依据进行查找，返回查找结果索引 head
Index *search_student(int search_by, char *query)
{
    Student *current = g_student_head;
    Index *index_head = NULL;
    while (current)
    {
        int searched = 0;
        switch (search_by)
        {
        case 0:
            if (strstr(current->id, query))
                searched = 1;
            break;
        case 1:
            if (strstr(current->name, query))
                searched = 1;
            break;
        case 2:
            if (strstr(current->major, query))
                searched = 1;
            break;
        }
        if (searched)
        {
            Index *new_index = (Index *)malloc(sizeof(*new_index));
            new_index->target = current;
            new_index->next = index_head;
            index_head = new_index;
        }
        current = current->next;
    }
    return index_head;
}

// 释放查找结果索引
static void free_index_list(Index *head)
{
    while (head)
    {
        Index *temp = head;
        head = head->next;
        free(temp);
    }
}
