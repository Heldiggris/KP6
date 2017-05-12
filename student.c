#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

int group_get_index(char *group, int qty, StudentStatistics *students)
{
    for (int i = 0; i < qty; i++) {
        if (strcmp(students[i].group, group) == 0) {
            return i;
        }
    }
    return qty;
}

double avg_mark(Student *s)
{
    double mdl = 0.0;
    for (int i = 0; i < s->marks_qty; ++i) {
                mdl += s->marks.mark[i];
            }
    return mdl / s->marks_qty;
}


void group_max_avg_mark(FILE *in, char gend[STR_SIZE])
{
    StudentStatistics students[200] = { { 0.0, 0, ' ' } };
    int students_qty = 0;
    Student student;
    int j_old = -1;
    while (student_read_bin(&student, in)) {
        if (!strcmp(student.gender, gend)) {
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
}

void remove_el(char *file, char *surname, char *initials)
{
    FILE *in = fopen(file, "rb");
        if (!in) {
            printf("I/O Error: can't open file.\n");
            exit(1);
        }
    FILE *tmp = fopen("tmp", "w");
    Student st;
    while (student_read_bin(&st, in)) {
        if (strcmp(st.surname, surname) != 0) {
            student_write_bin(&st, tmp);
        } else if (strcmp(st.initials, initials) != 0) {
            student_write_bin(&st, tmp);
        }
    }
    fclose(in);
    fclose(tmp);

    in = fopen(file, "w");
        if (!in) {
            printf("I/O Error: can't open file.\n");
            exit(1);
        }
    tmp = fopen("tmp", "r");
    while (student_read_bin(&st, tmp)) {
        if (strcmp(st.surname, surname) != 0) {
            student_write_bin(&st, in);
        } else if (strcmp(st.initials, initials) != 0) {
            student_write_bin(&st, in);
        }
    }
    fclose(in);
    fclose(tmp);
    remove("tmp");
}

void info_student(char *file, char *surname, char *initials)
{
    FILE *in = fopen(file, "r");
        if (!in) {
            printf("I/O Error: can't open file.\n");
            exit(1);
        }
    Student st;
    while (student_read_bin(&st, in)) {
        if (!strcmp(st.surname, surname) && !strcmp(st.initials, initials)) {
            printf("Имя: %s %s\nПол: %s\nГруппа: %s\nОценки: ", st.surname, st.initials, st.gender, st.group);
            for (int i = 0; i < st.marks_qty; ++i) {
                printf("%s ", &st.marks.ob[i]);
                printf("%d ", st.marks.mark[i]);
            }
            printf("\n");
        }
    }
    fclose(in);
}
