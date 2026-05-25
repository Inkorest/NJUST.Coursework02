#include "db_storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "register.h"
#include "student.h"

char g_logged_username[20] = {0};
static const char users_file[] = "data/users.txt";

void load_user_data()
{
    FILE *fp = fopen(users_file, "r");
    if (!fp)
    {
        printf("无法加载用户数据文件。\n");
        exit(EXIT_FAILURE);
    }
    char line[60];
    g_user_head = NULL;
    while (fgets(line, sizeof(line), fp))
    {
        User *new_user = (User *)malloc(sizeof(*new_user));
        if (!new_user)
        {
            printf("内存分配失败。\n");
            exit(EXIT_FAILURE);
        }
        sscanf(line, "%[^,], %[^,], %[^\n]", new_user->username, new_user->password, new_user->phone);
        new_user->next = g_user_head;
        g_user_head = new_user;
    }
    fclose(fp);
    return;
}

void save_user_data(User *target)
{
    FILE *fp = fopen(users_file, "a");
    if (!fp)
    {
        printf("无法保存用户数据文件。\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s, %s, %s\n", target->username, target->password, target->phone);
    fclose(fp);
    return;
}

void load_student_data(const char *username, Student **head)
{
    char filename[50];
    snprintf(filename, sizeof(filename), "data/student_data/data_%s.txt", username);
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fp = fopen(filename, "w");
        fclose(fp);
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), fp))
    {
        Student *new_student = (Student *)malloc(sizeof(*new_student));
        if (!new_student)
        {
            printf("内存分配失败。\n");
            exit(EXIT_FAILURE);
        }
        sscanf(line, "%[^,], %[^,], %[^,], %d, %d, %d, %d, %d",
               new_student->id, new_student->name, new_student->major,
               &new_student->score[0], &new_student->score[1], &new_student->score[2],
               &new_student->score[3], &new_student->score[4]);
        new_student->total_score = new_student->score[0] + new_student->score[1] +
                                   new_student->score[2] + new_student->score[3] +
                                   new_student->score[4];
        new_student->next = *head;
        *head = new_student;
    }
    fclose(fp);
}

void save_student_data(const char *username, const Student *head)
{
    char filename[50];
    snprintf(filename, sizeof(filename), "data/student_data/data_%s.txt", username);
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("无法保存学生数据文件。\n");
        exit(EXIT_FAILURE);
    }
    const Student *current = head;
    while (current)
    {
        fprintf(fp, "%s, %s, %s, %d, %d, %d, %d, %d\n",
                current->id, current->name, current->major,
                current->score[0], current->score[1], current->score[2],
                current->score[3], current->score[4]);
        current = current->next;
    }
    fclose(fp);
}
