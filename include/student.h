#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student
{
    char id[20];
    char name[20];
    char major[20];
    int score[5];
    int total_score;
    struct Student *next;
} Student;

Student *head;

void add_student(Student **head);
void delete_student(Student **head, Student *target);
void display_student_list(Student *head);
Student *merge_sort(Student *head, int (*sort_by)(Student *, Student *));

#endif
