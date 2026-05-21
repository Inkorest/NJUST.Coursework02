#include "menu_edit.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define Q 113
#define q 81

static void edit_data(Student *head, Student *target, int current_choice);

int menu_edit(Student *head, Student *target, int mode) // mode = 1: add
{
    Student cache = *target;
    int added = 0;

    system("cls");
    if (mode)
    {
        printf("录入学生信息\n正在录入新的学生信息。\n\n");
        printf("    %-16s\n", "学号");
        printf("    %-16s\n", "姓名");
        printf("    %-16s\n", "专业");
        printf("    %-16s\n", "成绩1");
        printf("    %-16s\n", "成绩2");
        printf("    %-16s\n", "成绩3");
        printf("    %-16s\n", "成绩4");
        printf("    %-16s\n", "成绩5");
    }
    else
    {
        printf("修改学生信息\n正在修改此学生的学生信息。\n\n");
        printf("    %-16s%s\n", "学号", cache.id);
        printf("    %-16s%s\n", "姓名", cache.name);
        printf("    %-16s%s\n", "专业", cache.major);
        printf("    %-16s%d\n", "成绩1", cache.score[0]);
        printf("    %-16s%d\n", "成绩2", cache.score[1]);
        printf("    %-16s%d\n", "成绩3", cache.score[2]);
        printf("    %-16s%d\n", "成绩4", cache.score[3]);
        printf("    %-16s%d\n", "成绩5", cache.score[4]);
    }
    printf("\n");
    if (mode)
        printf("[ ↑/↓ ] 选择  [ Enter ] 键入  [ Q ] 放弃录入");
    else
        printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 保存修改并退出  [ Q ] 放弃修改");

    int current_choice = 0;
    while (1)
    {
        int key;
        gotoxy(0, current_choice + 3);
        printf("-> ");
        do
        {
            key = _getch();
            if (added == 255 && key == ESC)
            {
                *target = cache;
                return 1;
            }
        } while (key != 224 && key != ENTER && key != Q && key != q);
        if (key == 224)
        {
            key = _getch();
            gotoxy(0, current_choice + 3);
            printf("   ");
            if (key == UP)
                current_choice = current_choice ? (current_choice - 1) : 7;
            if (key == DOWN)
                current_choice = current_choice != 7 ? (current_choice + 1) : 0;
            if (added & 1 << current_choice)
            {
                gotoxy(0, 12);
                printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Q ] 放弃录入");
            }
        }
        else if (key == ENTER)
        {
            gotoxy(0, 12);
            printf("\33[K[ Enter ] 确定\n");
            edit_data(head, &cache, current_choice);
            gotoxy(0, 12);
            if (mode)
            {
                added |= 1 << current_choice;
                if (added == 255)
                    printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 完成录入  [ Q ] 放弃录入");
                else
                    printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Q ] 放弃录入");
                if (current_choice != 7)
                {
                    gotoxy(0, current_choice + 3);
                    printf("   ");
                    current_choice++;
                }
            }
            else
                printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 保存修改并退出  [ Q ] 放弃修改");
        }
        else
        {
            return 0;
        }
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
