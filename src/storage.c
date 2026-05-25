#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "student.h"

static const char users_file[] = "data/users.txt";
static const char students_file[] = "data/students.txt";

void load_user_data()
{
    FILE *fp = fopen(users_file, "r");
    if (!fp)
        return;
    char line[60];
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
    if (fp == NULL)
    {
        printf("无法读取用户数据文件。\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s, %s, %s\n", target->username, target->password, target->phone);
    fclose(fp);
    return;
}

int load_student_data()
{
}

int save_student_data()
{
}
