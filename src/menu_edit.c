#include "menu_edit.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

static void edit_data(Student *head, Student *target, int current_choice);

void menu_edit(Student *head, Student *target)
{
    int current_choice = 0;

    system("cls");
    printf("修改学生信息\n");
    printf("正在修改此学生的学生信息。\n\n");
    printf("    %-16s%s\n", "学号", target->id);
    printf("    %-16s%s\n", "姓名", target->name);
    printf("    %-16s%s\n", "专业", target->major);
    printf("    %-16s%d\n", "成绩1", target->score[0]);
    printf("    %-16s%d\n", "成绩2", target->score[1]);
    printf("    %-16s%d\n", "成绩3", target->score[2]);
    printf("    %-16s%d\n", "成绩4", target->score[3]);
    printf("    %-16s%d\n", "成绩5", target->score[4]);
    printf("\n");
    printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 退出修改\n");

    while (1)
    {
        gotoxy(0, 12);
        int key;
        gotoxy(0, current_choice + 3);
        printf("-> ");
        do
            key = _getch();
        while (key != 224 && key != ENTER && key != ESC);
        if (key == 224)
        {
            key = _getch();
            gotoxy(0, current_choice + 3);
            printf("   ");
            if (key == UP)
                current_choice = current_choice ? (current_choice - 1) : 7;
            if (key == DOWN)
                current_choice = current_choice != 7 ? (current_choice + 1) : 0;
        }
        else if (key == ENTER)
        {
            gotoxy(0, 12);
            printf("\33[K[ Enter ] 确定\n");
            edit_data(head, target, current_choice);
            gotoxy(0, 12);
            printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 退出修改\n");
        }
        else if (key == ESC)
            return;
    }
}

static void edit_data(Student *head, Student *target, int current_choice)
{
    gotoxy(18, current_choice + 3);
    printf("\33[K");
    if (current_choice == 0)
    {
        char new_id[20];
        while (1)
        {
            scanf("%s", new_id);
            gotoxy(18, 3);
            if (strlen(new_id) <= 16 && is_digit_str(new_id))
            {
                if (!strcmp(target->id, new_id) || check_unique_id(new_id, head))
                {
                    strcpy(target->id, new_id);
                    break;
                }
                printf("\33[K学号已存在，请重新输入。");
            }
            else
                printf("\33[K请输入16位以内的数字学号。");
            Sleep(1000);
            gotoxy(18, 3);
            printf("\33[K");
        }
        strcpy(target->id, new_id);
    }
    else if (current_choice == 1)
    {
        char new_name[20];
        scanf("%s", new_name);
        strcpy(target->name, new_name);
    }
    else if (current_choice == 2)
    {
        char new_major[20];
        scanf("%s", new_major);
        strcpy(target->major, new_major);
    }
    else
    {
        char new_score_str[5];
        int score_index = current_choice - 3;
        while (1)
        {
            scanf("%s", new_score_str);
            if (strlen(new_score_str) <= 3 && is_digit_str(new_score_str))
            {
                target->score[score_index] = (int)strtol(new_score_str, NULL, 10);
                break;
            }
            gotoxy(18, 3 + current_choice);
            printf("\33[K请输入3位以内的成绩。");
            Sleep(1000);
            gotoxy(18, 3 + current_choice);
            printf("\33[K");
        }
    }
}

/*
修改学生信息
正在修改此学生的学生信息。

学号
姓名
专业
成绩1
成绩2
成绩3
成绩4
成绩5

[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 退出修改
*/
