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

void result(FILE *in)
{
    StudentStatistics students[200] = { { 0.0, 0, ' ' } };
    int students_qty = 0;

    Student student;
    int j_old = -1;
    while (student_read_txt(&student, in)) {
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
    FILE *in = fopen(file, "r");
        if (!in) {
            printf("I/O Error: can't open file.\n");
            exit(1);
        }
    FILE *tmp = fopen("tmp", "w");
    Student st;
    while (student_read_txt(&st, in)) {
        if (strcmp(st.surname, surname) != 0) {
            student_write_txt(&st, tmp);
        } else if (strcmp(st.initials, initials) != 0) {
            student_write_txt(&st, tmp);
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
    while (student_read_txt(&st, tmp)) {
        if (strcmp(st.surname, surname) != 0) {
            student_write_txt(&st, in);
        } else if (strcmp(st.initials, initials) != 0) {
            student_write_txt(&st, in);
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
    while (student_read_txt(&st, in)) {
        if (strcmp(st.surname, surname) == 0) {
            printf("Имя: %s %s\nПол: %s\nГруппа: %s\nОценки: дм - %d, ма - %d, ла - %d, инф - %d, ист - %d\n", st.surname, st.initials, st.gender, st.group, st.dm, st.ma, st.la, st.cs, st.hi);
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
        scanf("%s", what_do);
        if (strcmp(what_do, "result") == 0) {
            FILE *in = fopen(argv[1], "r");
            if (!in) {
                printf("I/O Error: can't open file.\n");
                exit(1);
            }
            result(in);
            fclose(in);
        } else if (strcmp(what_do, "add") == 0) {
            FILE *add_file = fopen(argv[1], "a");
            if (!add_file) {
            printf("I/O Error: can't open file.\n");
                exit(1);
            }
            Student student;
            scanf("%s", &student.surname);
            scanf("%s", &student.initials);
            scanf("%s", &student.gender);
            scanf("%s", &student.group);
            scanf("%d", &student.dm);
            scanf("%d", &student.ma);
            scanf("%d", &student.la);
            scanf("%d", &student.cs);
            scanf("%d", &student.hi);
            student_write_txt(&student, add_file);
            fclose(add_file);
        } else if (strcmp(what_do, "remove") == 0) {
            char surname[STR_SIZE];
            char initials[3];
            scanf("%s", &surname);
            scanf("%s", &initials);
            remove_el(argv[1], surname, initials);
        } else if (strcmp(what_do, "close") == 0 || strcmp(what_do, "exit") == 0) {
            break;
        } else if (strcmp(what_do, "info") == 0) {
            char surname[STR_SIZE];
            char initials[3];
            scanf("%s", &surname);
            scanf("%s", &initials);
            info(argv[1], surname, initials);
        }
        else {
            printf("Error: Invalid query\n");
            exit(2);
        }
    }

    return 0;
}
