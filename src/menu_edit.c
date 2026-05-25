#include "menu_edit.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27
#define S 83
#define s 115

static void edit_data(Student *head, Student *target, int current_choice);
static void display_info(const int current_choice);

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

    int current_choice = 0;
    while (1)
    {
        gotoxy(0, 12);
        if (mode)
        {
            if (added == 255)
                printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ S ] 完成录入  [ Esc ] 放弃录入");
            else if (added & 1 << current_choice)
                printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 放弃录入");
            else
                printf("[ ↑/↓ ] 选择  [ Enter ] 键入  [ Esc ] 放弃录入");
        }
        else
            printf("[ ↑/↓ ] 选择  [ Enter ] 修改  [ S ] 保存修改并退出  [ Esc ] 放弃修改");
        printf("\n\33[K\n\n\33[K");

        int key;
        gotoxy(0, current_choice + 3);
        printf("-> ");
        do
        {
            key = _getch();
            if ((!mode || added == 255) && (key == S || key == s))
            {
                cache.total_score = cache.score[0] + cache.score[1] + cache.score[2] + cache.score[3] + cache.score[4];
                *target = cache;
                return 1;
            }
        } while (key != 224 && key != ENTER && key != ESC);
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
            gotoxy(0, 15);
            printf("\33[K[ Enter ] 确定\n");
            edit_data(head, &cache, current_choice);
            if (mode)
            {
                added |= 1 << current_choice;
                if (current_choice != 7)
                {
                    gotoxy(0, current_choice + 3);
                    printf("   ");
                    current_choice++;
                }
            }
        }
        else
            return 0;
    }
}

static void edit_data(Student *head, Student *target, int current_choice)
{
    display_info(current_choice);
    gotoxy(18, current_choice + 3);
    printf("\33[K");
    switch (current_choice)
    {
    case 0:
    {
        char new_id[20];
        while (1)
        {
            safe_input(new_id, sizeof(new_id));
            gotoxy(18, 3);
            if (strlen(new_id) <= 16 && is_digit_str(new_id))
            {
                if (!strcmp(target->id, new_id) || check_unique_id(new_id, head))
                    break;
                printf("\33[K学号已存在，请重新输入。");
            }
            else
                printf("\33[K请输入 16 位以内的数字学号。");
            Sleep(1000);
            gotoxy(18, 3);
            printf("\33[K");
        }
        strcpy(target->id, new_id);
        break;
    }
    case 1:
    {
        char new_name[24];
        while (1)
        {
            safe_input(new_name, sizeof(new_name));
            if (strlen(new_name) < 20 && is_digit_or_letter_or_blank_str(new_name))
                break;
            gotoxy(18, 4);
            printf("\33[K请输入 20 位以内的合法姓名。");
            Sleep(1000);
            gotoxy(18, 4);
            printf("\33[K");
        }
        strcpy(target->name, new_name);
        break;
    }
    case 2:
    {
        char new_major[24];
        while (1)
        {
            safe_input(new_major, sizeof(new_major));
            if (strlen(new_major) < 20 && is_digit_or_letter_or_blank_str(new_major))
                break;
            gotoxy(18, 5);
            printf("\33[K请输入 20 位以内的合法专业。");
            Sleep(1000);
            gotoxy(18, 5);
            printf("\33[K");
        }
        strcpy(target->major, new_major);
        break;
    }
    default:
    {
        char new_score_str[5];
        int score_index = current_choice - 3;
        while (1)
        {
            safe_input(new_score_str, sizeof(new_score_str));
            if (strlen(new_score_str) <= 3 && is_digit_str(new_score_str))
                break;
            gotoxy(18, 3 + current_choice);
            printf("\33[K请输入 3 位以内的合法成绩。");
            Sleep(1000);
            gotoxy(18, 3 + current_choice);
            printf("\33[K");
        }
        target->score[score_index] = (int)strtol(new_score_str, NULL, 10);
        break;
    }
    }
}

static void display_info(const int current_choice)
{
    gotoxy(0, 12);
    printf("\33[K信息\n  ");
    switch (current_choice)
    {
    case 0:
        printf("输入 16 位以内的学号，学号由数字组成。");
        break;
    case 1:
        printf("输入 20 位以内的姓名，姓名由字母、数字或空格组成。");
        break;
    case 2:
        printf("输入 20 位以内的专业，专业由字母、数字或空格组成。");
        break;
    default:
        printf("输入 3 位以内的成绩，成绩由数字组成。");
        break;
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

信息
  <Info Message>

[ ↑/↓ ] 选择  [ Enter ] 修改  [ Esc ] 退出修改
*/
