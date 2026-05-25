#ifndef USER_H
#define USER_H

typedef struct User
{
    char username[20];
    char password[20];
    char phone[15];
    struct User *next;
} User;

User *g_user_head;

#endif
