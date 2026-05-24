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

Student *g_student_head;

void add_student(Student **head);
void delete_student(Student **head, Student *target);
Student *merge_sort(Student *head, int ascending, int (*sort_by)(const Student *, const Student *, int));
int sort_by_id(const Student *a, const Student *b, int ascending);
int sort_by_name(const Student *a, const Student *b, int ascending);
int sort_by_major(const Student *a, const Student *b, int ascending);
int sort_by_total_score(const Student *a, const Student *b, int ascending);
void student_statistics(Student *head);

#endif
