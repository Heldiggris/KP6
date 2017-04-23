#ifndef _STUDENT_H_
#define _STUDENT_H_

#define STR_SIZE 24

typedef struct {
    char surname[STR_SIZE];
    char initials[STR_SIZE];
    char gender[STR_SIZE];
    char group[STR_SIZE];
    int  dm, ma, la, cs, hi;
} Student;

#endif

