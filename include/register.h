#ifndef REGISTER_H
#define REGISTER_H

typedef struct User
{
    char username[20];
    char password[20];
    char phone[15];
    struct User *next;
} User;

User *g_user_head;

void user_register(User *head, User *target);

#endif
