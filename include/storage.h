#ifndef STORAGE_H
#define STORAGE_H
#include "user.h"
#include "student.h"

extern char g_logged_username[20];

void load_user_data();
void save_user_data(User *target);
void load_student_data(const char *username, Student **head);
void save_student_data(const char *username, const Student *head);

#endif
