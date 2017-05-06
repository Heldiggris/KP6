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
    double mdl = 0.0;
    for (int i = 0; i < s->marks_qty; ++i) {
                mdl += s->marks->mark[i];
            }
    return mdl / s->marks_qty;
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

void result(FILE *in)
{
    printf("00\n");
    StudentStatistics students[200] = { { 0.0, 0, ' ' } };
    int students_qty = 0;
    Student student;
    int j_old = -1;
    while (student_read_bin(&student, in)) {
        if (strcmp(student.gender, "F") == 0) {
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
    FILE *tmp = fopen("tmp", "wb");
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

    in = fopen(file, "wb");
        if (!in) {
            printf("I/O Error: can't open file.\n");
            exit(1);
        }
    tmp = fopen("tmp", "rb");
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

void info(char *file, char *surname, char *initials)
{
    FILE *in = fopen(file, "r");
        if (!in) {
            printf("I/O Error: can't open file.\n");
            exit(1);
        }
    Student st;
    while (student_read_bin(&st, in)) {
        if (strcmp(st.surname, surname) == 0) {
            printf("Имя: %s %s\nПол: %s\nГруппа: %s\nОценки: ", st.surname, st.initials, st.gender, st.group);
            for (int i = 0; i < st.marks_qty; ++i) {
                printf("%s ", &st.marks->ob[i]);
                printf("%lf ", &st.marks->mark[i]);
            }
            printf("\n");
        }
    }
    fclose(in);
}

int main(int argc, char *argv[])
{
    char what_do[STR_SIZE];
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }

    while (1) {
        fscanf(stdin, "%s", what_do);
        if (!strcmp(what_do, "result")) {
            FILE *in = fopen(argv[1], "rb");
            if (!in) {
                printf("I/O Error: can't open file.\n");
                exit(1);
            }
            result(in);
            fclose(in);
        } else if (!strcmp(what_do, "add")) {
            FILE *add_file = fopen(argv[1], "ab");
            if (!add_file) {
            printf("I/O Error: can't open file.\n");
                exit(1);
            }
            Student student;
            fscanf(stdin, "%s", &student.surname);
            fscanf(stdin, "%s", &student.initials);
            fscanf(stdin, "%s", &student.gender);
            fscanf(stdin, "%s", &student.group);
            fscanf(stdin, "%d", &student.marks_qty);
            for (int i = 0; i < student.marks_qty; ++i) {
                fscanf(stdin, "%s", &student.marks->ob[i]);
                fscanf(stdin, "%d", &student.marks->mark[i]);
            }
            student_write_bin(&student, add_file);
            fclose(add_file);
        } else if (!strcmp(what_do, "remove")) {
            char surname[STR_SIZE];
            char initials[3];
            fscanf(stdin, "%s", &surname);
            fscanf(stdin, "%s", &initials);
            remove_el(argv[1], surname, initials);
        } else if (!strcmp(what_do, "close") || !strcmp(what_do, "exit")) {
            break;
        } else if (!strcmp(what_do, "info")) {
            char surname[STR_SIZE];
            char initials[3];
            fscanf(stdin, "%s", &surname);
            fscanf(stdin, "%s", &initials);
            info(argv[1], surname, initials);
        } else if (!strcmp(what_do, "help")) {
            printf("\tresult - вывод результата\n");
            printf("\tadd    surname initials gender group dm ma la cs hi - добавить студента\n");
            printf("\tremove    surname initials - удалить студента\n");
            printf("\tinfo    surname initials - информация о студенте\n");
            printf("\texit - завершение программы\n");
        } else {
            printf("Error: Invalid query\n");
            // exit(2);
        }
    }

    return 0;
}