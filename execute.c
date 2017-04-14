#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "io.h"

typedef struct {
    double sum_mark;
    int capacity;
    char group[STR_SIZE];
} StudentStatistics;

double avg_mark(Student *s)
{
    return (s->dm + s->ma + s->la + s->cs + s->hi) / 5.0;
}


int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    double avg = 0.0, max_avg = 0.0;

    StudentStatistics students[200] = { { 0.0, 0, -1 } };
    int students_qty = 0;

    Student student;

    while (student_read_txt(&student, in)) {
        if(student.gender == 'F') {
            avg = avg_mark(&student);
            for(int i = 0; i <= students_qty; ++i) {
                if(strcmp(students[i].group, student.group) == 0) {
                    students[i].sum_mark += avg;
                    students[i].capacity += 1;
                    break;
                } else if (i == students_qty) {
                    students[students_qty].sum_mark = avg;
                    students[students_qty].capacity = 1;
                    strcpy(students[students_qty].group, student.group);
                    students_qty++;
                    break;
                }
            }
        }
    }

    double max_avg_mark = 0;

    for (int i = 0; i < students_qty; ++i)
    {
        students[i].sum_mark = students[i].sum_mark / students[i].capacity;
    }

    for (int i = 0; i < students_qty; ++i)
    {
        if(students[i].sum_mark > max_avg_mark) {
            max_avg_mark = students[i].sum_mark;
        }
    }

    for (int i = 0; i < students_qty; ++i)
    {
        if(students[i].sum_mark == max_avg_mark) {
            printf("Группа: %s. Балл: %.2lf\n", students[i].group, max_avg_mark);
        }
    }

    fclose(in);

    return 0;
}
