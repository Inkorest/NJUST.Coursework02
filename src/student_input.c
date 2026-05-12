#include "student_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "utils.h"

static char student_id[20];
static char student_name[20];
static char student_major[20];
static char student_score[5][5];

static int check_unique_id(const char *id, Student *head);
static void student_input_display();

void input_data(Student *new_student, Student *head)
{
    system("cls");
    student_input_display();

    while (1)
    {
        gotoxy(14, 2);
        printf("\33[K");
        scanf("%s", student_id);
        gotoxy(14, 2);
        if (strlen(student_id) <= 16 && is_digit_str(student_id))
        {
            if (check_unique_id(student_id, head))
            {
                strcpy(new_student->id, student_id);
                break;
            }
            printf("\33[K学号已存在，请重新输入。");
        }
        else
            printf("\33[K请输入16位以内的数字学号。");
        Sleep(1000);
    }

    /*
    while (1)
    {
        gotoxy(14, 3);
        printf("\33[K");
        scanf("%s", student_name);
        if (strlen(student_name) <= 16 && is_digit_or_letter_str(student_name))
            break;
        student_name[0] = '\0';
        gotoxy(14, 3);
        printf("\33[K请输入16位以内的姓名。");
        Sleep(1000);
    }
    */
    gotoxy(14, 3);
    scanf("%s", student_name);
    strcpy(new_student->name, student_name);

    gotoxy(14, 4);
    scanf("%s", student_major);
    strcpy(new_student->major, student_major);

    for (int i = 0; i < 5; i++)
        while (1)
        {
            gotoxy(14, 5 + i);
            printf("\33[K");
            scanf("%s", student_score[i]);
            if (strlen(student_score[i]) <= 3 && is_digit_str(student_score[i]))
            {
                new_student->score[i] = (int)strtol(student_score[i], NULL, 10);
                break;
            }
            gotoxy(14, 5 + i);
            printf("\33[K请输入3位以内的成绩。");
            Sleep(1000);
        }

    gotoxy(0, 11);
    printf("录入完毕。");
    Sleep(1000);
}

static int check_unique_id(const char *id, Student *head)
{
    while (head)
    {
        if (strcmp(head->id, id) == 0)
            return 0;
        head = head->next;
    }
    return 1;
}

static void student_input_display()
{
    gotoxy(0, 0);
    printf("录入新的学生信息\n\n");
    printf("%-16s\n", "学号");
    printf("%-16s\n", "姓名");
    printf("%-16s\n", "专业");
    printf("%-16s\n", "成绩1");
    printf("%-16s\n", "成绩2");
    printf("%-16s\n", "成绩3");
    printf("%-16s\n", "成绩4");
    printf("%-16s\n", "成绩5");
}
