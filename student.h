#ifndef _STUDENT_H_
#include <stdint.h>
#define _STUDENT_H_

#define STR_SIZE 24

typedef int32_t Item;

typedef struct {
    char *ob[20][STR_SIZE];
    Item mark[20];
} SubjectMark;

typedef struct {
    char surname[STR_SIZE];
    char initials[STR_SIZE];
    char gender[STR_SIZE];
    char group[STR_SIZE];
    Item marks_qty;
    SubjectMark *marks;
} Student;


#endif