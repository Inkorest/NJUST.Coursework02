#include <stdio.h>
#include <windows.h>
#include "ui_auth.h"
#include "user.h"
#include "student.h"

int main()
{
    g_student_head = NULL;
    g_user_head = NULL;
    ui_auth();
    system("cls");
    printf("已退出系统。\n");
    return 0;
}
