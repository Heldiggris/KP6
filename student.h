#ifndef _STUDENT_H_
#include <stdint.h>
#define _STUDENT_H_

#define STR_SIZE 24
#define MAX_GROUP 524288

typedef int32_t Item;


typedef struct {
    char ob[20][STR_SIZE];
    Item mark[20];
} SubjectMark;

typedef struct {
    char surname[STR_SIZE];
    char initials[STR_SIZE];
    char gender[STR_SIZE];
    char group[STR_SIZE];
    Item marks_qty;
    SubjectMark marks;
} Student;

typedef struct {
    double sum_mark;
    int capacity;
    char group[STR_SIZE];
} StudentStatistics;

typedef struct _list{
    StudentStatistics students;
    struct _list *next;
} List;


int hash(char *group);

int hash_find_group(char *group, List **l);

List *list_create();

void list_destroy(List *l);

int hash_add_group(char *group, List **l);

double avg_mark(Student *s);

void group_max_avg_mark(FILE *in, List **l, char *group_max_mark, double *max_mark, int *index_qty, int *index_group);

void remove_student(char *file, char *surname, char *initials, List **l, char *group_max_mark, double *max_mark, int *index_qty, int *index_group);

void info_student(FILE *in, char *surname, char *initials);

void add_student(FILE *add_file, List **l, char *group_max_mark, double *max_mark, int *index_qty, int *index_group);


#endif