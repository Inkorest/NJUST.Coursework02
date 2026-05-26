#ifndef LIST_SEARCH_H
#define LIST_SEARCH_H
#include "student.h"

typedef struct Index
{
    Student *target;
    struct Index *next;
} Index;

Student *list_search(Index *index_head, char *query);
Index *search_student(int search_by, char *query);

#endif
