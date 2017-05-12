#ifndef _STUDENT_H_
#include <stdint.h>
#define _STUDENT_H_

#define STR_SIZE 24

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


int group_get_index(char *group, int qty, StudentStatistics *students);

double avg_mark(Student *s);

void group_max_avg_mark(FILE *in, char gend[STR_SIZE]);

void remove_el(char *file, char *surname, char *initials);

void info_student(char *file, char *surname, char *initials);

#endif