#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"


int hash(char *group) {
    int a = 0;
    int pos = 1;
    for(int i = 0; group[i] != '\0'; ++i) {
        a += (int)group[i] * 1024 * pos++;
    }
    if (a < 0)
        a *= -1;
    return a % MAX_GROUP;
}

int hash_find_group(char *group, List **l)
{
    int j = hash(group);
    int pos = 0;
    List *l1 = l[j];
    while (l1) {
        if (!strcmp(l1->students.group, group)) {
            return pos;
        }
        pos++;
        l1 = l1->next;
    }
    return -1;
}

List *list_create()
{
    List *l = (List *)malloc(sizeof(List));
    // l->students = { 0.0, 0, ' ' };
    l->students.sum_mark = 0.0;
    l->students.capacity = 0;
    strcpy(l->students.group ," "); 
    l->next = NULL;
    return l;
}

void list_destroy(List *l)
{
    // if (l->next) {
    //     printf("1\n");
    //     list_destroy(l->next);
    // }
    free(l);
}



int hash_add_group(char *group, List **l) {
    int j = hash(group);
    int pos = 0;
    List *l1 = l[j];
    if (!l1) {
        l[j] = list_create();
        strcpy(l[j]->students.group, group);
        return pos;
    }
    while (l1->next) {
        if (!strcmp(l1->students.group, group )) {
            return pos;
        }
        l1 = l1->next;
        pos++;
    }
    l1->next = list_create();
    strcpy(l1->next->students.group, group);
    // l[j] = l1;
    return pos;
}

double avg_mark(Student *s)
{
    double mdl = 0.0;
    for (int i = 0; i < s->marks_qty; ++i) {
                mdl += s->marks.mark[i];
            }
    return mdl / s->marks_qty;
}

void group_max_avg_mark(FILE *in, List **l, char *group_max_mark, double *max_mark, int *index_qty, int *index_group)
{
    Student student;
    int add_pos = 0;
    long long int aaa = 0;
    while (student_read_bin(&student, in)) {
        if (!strcmp(student.gender, "F")) {
            int j = hash(student.group);
            if ((add_pos = hash_find_group(student.group, l)) == -1) {
                List *l2 = l[j];
                add_pos = hash_add_group(student.group, l);
                if (add_pos == 0) {
                    index_group[(*index_qty)++] = j;
                }
            }
            List *l2 = l[j];
            for (int i = 0; i < add_pos; ++i) {
                l[j] = l[j]->next;
            }
            l[j]->students.sum_mark += avg_mark(&student);
            l[j]->students.capacity++;
            l[j] = l2;
        }
    }
    for (int i = 0; i < (*index_qty); ++i) {
        List *l2 = l[index_group[i]];
        while (l[index_group[i]]) {
            if (l[index_group[i]]->students.sum_mark / l[index_group[i]]->students.capacity > *max_mark) {
                *max_mark = l[index_group[i]]->students.sum_mark / l[index_group[i]]->students.capacity;
                strcpy(group_max_mark, l[index_group[i]]->students.group);
            }
            l[index_group[i]] = l[index_group[i]]->next;
        }
        l[index_group[i]] = l2;
    }
}

void remove_student(char *file, char *surname, char *initials, List **l, char *group_max_mark, double *max_mark, int *index_qty, int *index_group)
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
                int j = hash(student.group);
                int add_pos = hash_find_group(student.group, l);

                for (int i = 0; i < (*index_qty); ++i) {
                    if (index_group[i] == j) {
                        index_group[i] = index_group[(*index_qty)--];
                    }
                }
                List *l1 = l[j];
                for (int i = 0; i < add_pos; ++i) {
                    l[j] = l[j]->next;
                }
                l[j]->students.sum_mark -= avg_mark(&student);
                l[j]->students.capacity--;
                if (!strcmp(group_max_mark, student.group)) {
                    *max_mark = -1;
                    for (int i = 0; i < (*index_qty); ++i) {
                        List *l2 = l[index_group[i]];
                        while (l[index_group[i]]) {
                            if (l[index_group[i]]->students.sum_mark / l[index_group[i]]->students.capacity > *max_mark) {
                                *max_mark = l[index_group[i]]->students.sum_mark / l[index_group[i]]->students.capacity;
                                strcpy(group_max_mark, l[index_group[i]]->students.group);
                            }
                            l[index_group[i]] = l[index_group[i]]->next;
                        }
                        l[index_group[i]] = l2;
                    }
                } else if (l[j]->students.sum_mark / l[j]->students.capacity > *max_mark) {
                        *max_mark = l[j]->students.sum_mark / l[j]->students.capacity;
                        strcpy(group_max_mark, l[j]->students.group);
                    }
                l[j] = l1;
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

void add_student(FILE *add_file, List **l, char *group_max_mark, double *max_mark, int *index_qty, int *index_group)
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

    int add_pos = 0;
    if (!strcmp(student.gender, "F")) {
        int j = hash(student.group);
        if (add_pos = hash_find_group(student.group, l) == -1) {
            List *l2 = l[j];
            add_pos = hash_add_group(student.group, l);
            if (add_pos == 0) {
                index_group[(*index_qty)++] = j;
            }
        }
        List *l1 = l[j];
        for (int i = 0; i < add_pos; ++i) {
            l[j] = l[j]->next;
        }
        l[j]->students.sum_mark += avg_mark(&student);
        l[j]->students.capacity++;
        if (l[j]->students.sum_mark / l[j]->students.capacity > *max_mark) {
                *max_mark = l[j]->students.sum_mark / l[j]->students.capacity;
                strcpy(group_max_mark, l[j]->students.group);
            }
        l[j] = l1;

    }
}
