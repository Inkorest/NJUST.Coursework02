#include "list.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

Student *list(const char *overview[], Student *head)
{
    system("cls");
    if (!head)
    {
        printf("一个学生都没有嘛！\n");
        printf("按任意键返回…\n");
        _getch();
        return NULL;
    }

    int current_selected = 0;
    int key;
    int overview_count = 0;
    while (overview[overview_count])
        overview_count++;
    int student_count = 0;

    for (int i = 0; i < overview_count; i++)
        printf("%s\n", overview[i]);
    printf("\n");

    Student *current = head;
    printf("    %-12s%-12s%-14s%-12s%-12s%-12s%-12s%-12s%-13s\n", "学号", "姓名", "专业", "成绩1", "成绩2", "成绩3", "成绩4", "成绩5", "总成绩");
    while (current)
    {
        printf("    %-10s%-10s%-12s%-10d%-10d%-10d%-10d%-10d%-10d\n", current->id, current->name, current->major, current->score[0],
               current->score[1], current->score[2], current->score[3], current->score[4], current->total_score);
        student_count++;
        current = current->next;
    }
    printf("\n信息\n  选择记录以进行详细操作。\n\n");
    printf("[ ↑/↓ ] 选择  [ Enter ] 确定  [ Esc ] 返回\n");

    while (1)
    {
        gotoxy(0, overview_count + current_selected + 2);
        printf("->");
        do
            key = _getch();
        while (key != 224 && key != ENTER && key != ESC);
        if (key == 224)
        {
            key = _getch();
            printf("\b\b  ");
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
