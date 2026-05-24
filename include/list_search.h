#ifndef LIST_SEARCH_H
#define LIST_SEARCH_H
#include "student.h"

typedef struct Index
{
    Student *target;
    struct Index *next;
} Index;

Index *menu_query(int search_by);
Student *list_search(Index *index_head);

#endif
