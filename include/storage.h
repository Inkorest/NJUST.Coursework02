#ifndef STORAGE_H
#define STORAGE_H
#include "auth.h"

void load_user_data();
void save_user_data(User *target);
int load_student_data();
int save_student_data();

#endif
