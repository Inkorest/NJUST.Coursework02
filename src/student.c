#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "utils.h"
#include "student_input.h"

Student *head = NULL;

static Student *merge(Student *left, Student *right, int (*sort_by)(Student *, Student *));

void add_student(Student **head)
{
    Student *new_student = (Student *)malloc(sizeof(Student));
    input_data(new_student, *head);
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

void display_student_list(Student *head)
{
    system("cls");
    printf("学号\t姓名\t专业\n");
    while (head)
    {
        printf("%s\t%s\t%s\n", head->id, head->name, head->major);
        head = head->next;
    }
    system("pause");
}

static Student *merge(Student *left, Student *right, int (*sort_by)(Student *, Student *))
{
    if (!left)
        return right;
    if (!right)
        return left;
    Student *result;
    if (sort_by(left, right))
    {
        result = left;
        result->next = merge(left->next, right, sort_by);
    }
    else
    {
        result = right;
        result->next = merge(left, right->next, sort_by);
    }
    return result;
}

Student *merge_sort(Student *head, int (*sort_by)(Student *, Student *))
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
    return merge(merge_sort(head, sort_by), merge_sort(mid, sort_by), sort_by);
}
