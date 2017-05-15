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


void group_max_avg_mark(FILE *in, char gend[STR_SIZE])
{
    StudentStatistics students[MAX_GROUP] = { { 0.0, 0, ' ' } };
    int students_qty = 0;
    Student student;
    int index_group[MAX_GROUP];
    while (student_read_bin(&student, in)) {
        if (!strcmp(student.gender, gend)) {
            int j;
            if (j = hash_find_group(student.group, students) == -1) {
                j = hash_add_group(student.group, students);
                index_group[students_qty++] = j;
            }
            students[j].sum_mark += avg_mark(&student);
            students[j].capacity++;
            // int j = hash(student.group);
            // if (!strcmp(students[j].group, "" )) {
            //     strcpy(students[j].group, student.group);
                
            // } else if (strcmp(students[j].group, student.group )) {
            //     j = hash_create(student.group, students);
            //     strcpy(students[j].group, student.group);
            //     index_group[students_qty++] = j;
            // }
            
        }
    }
    int group_max_mark[MAX_GROUP];
    int group_max_mark_qty = 0;
    double max_mark = 0;
    for (int i = 0; i < students_qty; ++i) {
        if (students[index_group[i]].sum_mark / students[index_group[i]].capacity > max_mark) {
            max_mark = students[index_group[i]].sum_mark / students[index_group[i]].capacity;
            group_max_mark[group_max_mark_qty] = index_group[i];
            group_max_mark_qty = 0;
        } else if (students[index_group[i]].sum_mark / students[index_group[i]].capacity == max_mark) {
            group_max_mark_qty += 1;
            group_max_mark[group_max_mark_qty] = index_group[i];
        }
    }

    for (int i = 0; i <= group_max_mark_qty; ++i) {
        printf("Группа: %s. Балл: %.2lf\n", students[group_max_mark[i]].group, max_mark);
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
