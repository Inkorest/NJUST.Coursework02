#include "menu.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

int menu(const char *overview[], const char *choices[], const char *information[])
{
    int current_choice = 0;
    int key;
    int choice_count = 0;
    while (choices[choice_count])
        choice_count++;
    int overview_count = 0;
    while (overview[overview_count])
        overview_count++;

    system("cls");
    for (int i = 0; i < overview_count; i++)
        printf("%s\n", overview[i]);
    printf("\n");
    for (int i = 0; i < choice_count; i++)
        printf("    %s\n", choices[i]);
    printf("\n信息\n\n\n");
    printf("[ ↑/↓ ] 选择  [ Enter ] 确定  [ Esc ] 返回\n");

    while (1)
    {
        gotoxy(0, overview_count + current_choice + 1);
        printf("->");
        gotoxy(0, overview_count + choice_count + 3);
        printf("\33[2K  %s", information[current_choice]);
        do
            key = _getch();
        while (key != 224 && key != ENTER && key != ESC);
        if (key == 224)
        {
            key = _getch();
            gotoxy(0, overview_count + current_choice + 1);
            printf("  ");
            if (key == UP)
                current_choice = current_choice ? (current_choice - 1) : (choice_count - 1);
            if (key == DOWN)
                current_choice = current_choice != choice_count - 1 ? (current_choice + 1) : 0;
        }
        else if (key == ENTER)
            return current_choice;
        else if (key == ESC)
            return -1;
    }
}
