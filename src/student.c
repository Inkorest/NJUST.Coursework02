#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "utils.h"
#include "student_input.h"

Student *head = NULL;

static Student *merge(Student *left, Student *right, int ascending, int (*sort_by)(const Student *, const Student *, int));

void add_student(Student **head)
{
    Student *new_student = (Student *)malloc(sizeof(Student));
    if (!new_student)
    {
        printf("内存分配失败。\n");
        return;
    }
    input_data(new_student, *head);
    new_student->total_score = 0;
    for (int i = 0; i < 5; i++)
        new_student->total_score += new_student->score[i];
    new_student->next = *head;
    *head = new_student;
}

void delete_student(Student **head, Student *target)
{
    if (*head == target)
    {
        *head = (*head)->next;
        free(target);
        return;
    }
    Student *current = *head;
    while (current->next && current->next != target)
        current = current->next;
    if (current->next)
    {
        current->next = target->next;
        free(target);
    }
}

static Student *merge(Student *left, Student *right, int ascending, int (*sort_by)(const Student *, const Student *, int))
{
    if (!left)
        return right;
    if (!right)
        return left;
    Student *result;
    if (sort_by(left, right, ascending) <= 0)
    {
        result = left;
        result->next = merge(left->next, right, ascending, sort_by);
    }
    else
    {
        result = right;
        result->next = merge(left, right->next, ascending, sort_by);
    }
    return result;
}

Student *merge_sort(Student *head, int ascending, int (*sort_by)(const Student *, const Student *, int))
{
    if (!head || !head->next)
        return head;
    Student *slow = head;
    Student *fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    Student *mid = slow->next;
    slow->next = NULL;
    return merge(merge_sort(head, ascending, sort_by), merge_sort(mid, ascending, sort_by), ascending, sort_by);
}

int sort_by_id(const Student *a, const Student *b, int ascending)
{
    int cmp = strcmp(a->id, b->id);
    return ascending ? cmp : -cmp;
}

int sort_by_name(const Student *a, const Student *b, int ascending)
{
    int cmp = strcmp(a->name, b->name);
    return ascending ? cmp : -cmp;
}

int sort_by_major(const Student *a, const Student *b, int ascending)
{
    int cmp = strcmp(a->major, b->major);
    return ascending ? cmp : -cmp;
}

int sort_by_total_score(const Student *a, const Student *b, int ascending)
{
    int cmp = a->total_score - b->total_score;
    return ascending ? cmp : -cmp;
}
