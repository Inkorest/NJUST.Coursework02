#ifndef UTILS_H
#define UTILS_H
#include "user.h"
#include "student.h"

void safe_input(char *buffer, int length);
void gotoxy(int x, int y);
int is_digit_or_letter_or_blank_str(char *str);
int is_digit_or_letter_str(char *str);
int is_digit_str(char *str);
int check_unique_username(const char *username, User *head);
int check_unique_id(const char *id, Student *head);

#endif
