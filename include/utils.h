#ifndef UTILS_H
#define UTILS_H
#include "student.h"

void gotoxy(int x, int y);
int is_digit_or_letter_str(char *str);
int is_digit_str(char *str);
int check_unique_id(const char *id, Student *head);

#endif
