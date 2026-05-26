#include "db_storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "student.h"

char g_logged_username[20] = {0};
static const char users_file[] = "data/users.txt";

// 将 head 指向的链表保存到用户数据文件
void load_user_data(User **head)
{
    FILE *fp = fopen(users_file, "r");
    if (!fp)
    {
        printf("无法加载用户数据文件。\n");
        exit(EXIT_FAILURE);
    }
    char line[60];
    *head = NULL;
    while (fgets(line, sizeof(line), fp))
    {
        User *new_user = (User *)malloc(sizeof(*new_user));
        if (!new_user)
        {
            printf("内存分配失败。\n");
            exit(EXIT_FAILURE);
        }
        sscanf(line, "%[^,], %[^,], %[^\n]", new_user->username, new_user->password, new_user->phone);
        new_user->next = *head;
        *head = new_user;
    }
    fclose(fp);
    return;
}

// 将 target 指向的用户数据从内存追加保存到用户数据文件
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

// 读取 username 对应的保存数据文件，并创建以 head 为头节点的链表
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
    *head = NULL;
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

// 将 head 指向的链表保存到 username 对应的保存数据文件
void save_student_data(const char *username, Student *head)
{
    char filename[50];
    snprintf(filename, sizeof(filename), "data/student_data/data_%s.txt", username);
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("无法保存学生数据文件。\n");
        exit(EXIT_FAILURE);
    }
    Student *current = head;
    while (current)
    {
        fprintf(fp, "%s, %s, %s, %d, %d, %d, %d, %d\n",
                current->id, current->name, current->major,
                current->score[0], current->score[1], current->score[2],
                current->score[3], current->score[4]);
        Student *temp = current;
        current = current->next;
        free(temp);
    }
    fclose(fp);
}
