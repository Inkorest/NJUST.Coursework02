#include "list.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

// 输出学生信息列表，返回用户选定的学生的结构体指针
Student *list(Student *head)
{
    system("cls");
    printf("输出学生信息\n");

    if (!head)
    {
        printf("\n一个学生都没有嘛！\n");
        printf("按任意键返回…\n");
        _getch();
        return NULL;
    }

    int current_selected = 0;
    int student_count = 0;

    printf("正在按指定的排序方式输出学生信息列表。\n\n");

    Student *current = head;
    printf("    %-18s%-22s%-22s%-12s%-12s%-12s%-12s%-12s%-13s\n", "学号", "姓名", "专业", "成绩1", "成绩2", "成绩3", "成绩4", "成绩5", "总成绩");
    while (current)
    {
        printf("    %-16s%-20s%-20s%-10d%-10d%-10d%-10d%-10d%-10d\n", current->id, current->name, current->major, current->score[0],
               current->score[1], current->score[2], current->score[3], current->score[4], current->total_score);
        student_count++;
        current = current->next;
    }
    printf("\n信息\n  选择记录以查看详情。\n\n");
    printf("[ ↑/↓ ] 选择  [ Enter ] 确定  [ Esc ] 返回\n");

    while (1)
    {
        int key;
        gotoxy(0, current_selected + 4);
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
            Student *target = head;
            for (int i = 0; i < current_selected; i++)
                target = target->next;
            return target;
        }
        else
            return NULL;
    }
}
