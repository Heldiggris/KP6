#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"


int hash(char *group) {
    int a = 0;
    for(int i = 0; group[i] != '\0'; ++i) {
        a += (int)group[i];
    }
    return a % MAX_GROUP;
}

int hash_find_group(char *group, StudentStatistics *students)
{
    int j = hash(group);
    if (!strcmp(students[j].group, group )) {
        return j;
    } else {
        for (int i = j; i < MAX_GROUP; i++) {
            if (!strcmp(students[i].group, group)) {
                return i;
            } else if(!strcmp(students[i].group, "")) {
                return -1;
            }
        }
        for (int i = 0; i < j; i++) {
            if (!strcmp(students[i].group, group)) {
                return i;
            } else if(!strcmp(students[i].group, "")) {
                return -1;
            }
        }
    }
    return -1;
}

int hash_add_group(char *group, StudentStatistics *students) {
    int j = hash(group);
    if (!strcmp(students[j].group, group )) {
        return j;
    } else {
        for (int i = j; i < MAX_GROUP; i++) {
            if (!strcmp(students[i].group, group)) {
                return i;
            } else if(!strcmp(students[i].group, "")) {
                 strcpy(students[j].group, group);
                 return j;
            }
        }
        for (int i = 0; i < j; i++) {
            if (!strcmp(students[i].group, group)) {
                return i;
            } else if(!strcmp(students[i].group, "")) {
                 strcpy(students[j].group, group);
                 return j;
            }
        }
    }
    return -1;
}

double avg_mark(Student *s)
{
    double mdl = 0.0;
    for (int i = 0; i < s->marks_qty; ++i) {
                mdl += s->marks.mark[i];
            }
    return mdl / s->marks_qty;
}

void group_max_avg_mark(FILE *in, StudentStatistics *students, int *group_max_mark, double *max_mark, int *group_max_mark_qty, int *students_qty, int *index_group)
{
    Student student;
    while (student_read_bin(&student, in)) {
        if (!strcmp(student.gender, "F")) {
            int j;
            if (j = hash_find_group(student.group, students) == -1) {
                j = hash_add_group(student.group, students);
                index_group[(*students_qty)++] = j;
            }
            students[j].sum_mark += avg_mark(&student);
            students[j].capacity++;
        }
    }
    for (int i = 0; i < (*students_qty); ++i) {
        if (students[index_group[i]].sum_mark / students[index_group[i]].capacity > *max_mark) {
            *max_mark = students[index_group[i]].sum_mark / students[index_group[i]].capacity;
            group_max_mark[*group_max_mark_qty] = index_group[i];
            *group_max_mark_qty = 0;
        } else if (students[index_group[i]].sum_mark / students[index_group[i]].capacity == *max_mark) {
            *group_max_mark_qty += 1;
            group_max_mark[*group_max_mark_qty] = index_group[i];
        }
    }
}

void remove_student(char *file, char *surname, char *initials, StudentStatistics *students, int *group_max_mark, double *max_mark, int *group_max_mark_qty, int *students_qty, int *index_group)
{
    FILE *in = fopen(file, "r");
        if (!in) {
            printf("I/O Error: can't open file.\n");
            exit(1);
        }
    FILE *tmp = fopen("tmp", "w");
    Student student;
    while (student_read_bin(&student, in)) {
        if (strcmp(student.surname, surname)) {
            student_write_bin(&student, tmp);
        } else if (strcmp(student.initials, initials)) {
            student_write_bin(&student, tmp);
        } else {
            int j = -1;
            if (!strcmp(student.gender, "F")) {
                int j = hash_find_group(student.group, students);
                students[j].sum_mark = 0.0;
                students[j].capacity = 0;
                strcpy(students[j].group, " ");

            }
            *max_mark = -1;
            *group_max_mark_qty = 0;
            for (int i = 0; i < (*students_qty); ++i) {
                if (index_group[i] == j) {
                    index_group[i] = index_group[--(*students_qty)];
                }
                if (students[index_group[i]].sum_mark / students[index_group[i]].capacity > *max_mark) {
                    *max_mark = students[index_group[i]].sum_mark / students[index_group[i]].capacity;
                    group_max_mark[*group_max_mark_qty] = index_group[i];
                    *group_max_mark_qty = 0;
                } else if (students[index_group[i]].sum_mark / students[index_group[i]].capacity == *max_mark) {
                    *group_max_mark_qty += 1;
                    group_max_mark[*group_max_mark_qty] = index_group[i];
                }
            }
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
    while (student_read_bin(&student, tmp)) {
        if (strcmp(student.surname, surname) != 0) {
            student_write_bin(&student, in);
        } else if (strcmp(student.initials, initials) != 0) {
            student_write_bin(&student, in);
        }
    }
    fclose(in);
    fclose(tmp);
    remove("tmp");
}

void info_student(FILE *in, char *surname, char *initials)
{
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
}

void add_student(FILE *add_file, StudentStatistics *students, int *group_max_mark, double *max_mark, int *group_max_mark_qty, int *students_qty, int *index_group)
{
    Student student;
    memset(&student, 0, sizeof(Student));
    fscanf(stdin, "%s", student.surname);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%s", student.initials);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%s", student.gender);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%s", student.group);
    if (feof(stdin)) {
        return;
    }
    fscanf(stdin, "%d", &student.marks_qty);
    if (feof(stdin)) {
        return;
    }
    for (int i = 0; i < student.marks_qty; ++i) {
        fscanf(stdin, "%s", student.marks.ob[i]);
        if (feof(stdin)) {
            return;
        }
        fscanf(stdin, "%d", &student.marks.mark[i]);
        if (feof(stdin)) {
            return;
        }
    }
    student_write_bin(&student, add_file);
    int j = -1;
    if (!strcmp(student.gender, "F")) {
        if (j = hash_find_group(student.group, students) == -1) {
            j = hash_add_group(student.group, students);
        }
        students[j].sum_mark += avg_mark(&student);
        students[j].capacity++;
        index_group[++(*students_qty)] = j;
    }
        if (students[index_group[(*students_qty)]].sum_mark / students[index_group[(*students_qty)]].capacity > *max_mark) {
            *max_mark = students[index_group[(*students_qty)]].sum_mark / students[index_group[(*students_qty)]].capacity;
            group_max_mark[*group_max_mark_qty] = index_group[(*students_qty)];
            *group_max_mark_qty = 0;
        } else if (students[index_group[(*students_qty)]].sum_mark / students[index_group[(*students_qty)]].capacity == *max_mark) {
            *group_max_mark_qty += 1;
            group_max_mark[*group_max_mark_qty] = index_group[(*students_qty)];
        }
}
