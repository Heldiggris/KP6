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

int group_get_index(char *group, int qty, StudentStatistics *students)
{
    for (int i = 0; i < qty; i++) {
        if (strcmp(students[i].group, group) == 0) {
            return i;
        }
    }
    return qty;
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

    StudentStatistics students[200] = { { 0.0, 0, ' ' } };
    int students_qty = 0;

    Student student;
    int j_old = -1;
    while (student_read_txt(&student, in)) {
        if (student.gender == 'F') {
            int j = group_get_index(student.group, students_qty, students);
            if (j_old != j) {
                students_qty += 1;
            }
            j_old = j;
            students[j].sum_mark += avg_mark(&student);
            students[j].capacity += 1;
            strcpy(students[j].group, student.group);
        }
    }
    char group_max_mark[200][STR_SIZE];
    int group_max_mark_qty = 0;
    double max_mark = 0;
    for (int i = 0; i < students_qty; ++i) {
        if (students[i].sum_mark / students[i].capacity > max_mark) {
            max_mark = students[i].sum_mark / students[i].capacity;
            strcpy(group_max_mark[group_max_mark_qty], students[i].group);
            group_max_mark_qty = 0;
        } else if (students[i].sum_mark / students[i].capacity == max_mark) {
            group_max_mark_qty += 1;
            strcpy(group_max_mark[group_max_mark_qty], students[i].group);
        }
    }

    for (int i = 0; i <= group_max_mark_qty; ++i) {
        printf("Группа: %s. Балл: %.2lf\n", group_max_mark[i], max_mark);
    }
    fclose(in);

    return 0;
}
