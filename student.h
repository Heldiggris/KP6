#ifndef _STUDENT_H_
#include <stdint.h>
#define _STUDENT_H_

#define STR_SIZE 24
#define MAX_GROUP 200


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


int hash(char *group);

int hash_find_group(char *group, StudentStatistics *students);

int hash_add_group(char *group, StudentStatistics *students);

double avg_mark(Student *s);

void group_max_avg_mark(FILE *in, StudentStatistics *students, int *group_max_mark, double *max_mark, int *group_max_mark_qty, int *students_qty, int *index_group);

void remove_student(char *file, char *surname, char *initials, StudentStatistics *students, int *group_max_mark, double *max_mark, int *group_max_mark_qty, int *students_qty, int *index_group);

void add_student(FILE *add_file, StudentStatistics *students, int *group_max_mark, double *max_mark, int *group_max_mark_qty, int *students_qty, int *index_group);

void info_student(FILE *in, char *surname, char *initials);

#endif