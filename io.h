#ifndef _IO_H_
#define _IO_H_

#include "student.h"

int  student_read_txt(Student *s, FILE *in);
void student_write_bin(Student *s, FILE *out);
void student_print(Student *s);
void student_write_txt(Student *s, FILE *file);

#endif
