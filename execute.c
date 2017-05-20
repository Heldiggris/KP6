#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "io.h"

int main(int argc, char *argv[])
{
    StudentStatistics students[MAX_GROUP] = { { 0.0, 0, ' ' } };
    int group_max_mark[MAX_GROUP] = { 0 };
    double max_mark = 0;
    int group_max_mark_qty = 0;
    int students_qty = 0;
    int index_group[MAX_GROUP] = { 0 };

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }
    group_max_avg_mark(in, &students, group_max_mark, &max_mark, &group_max_mark_qty, &students_qty, index_group);
    fclose(in);

    char what_do[STR_SIZE];
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }

    while (!feof(stdin)) {
        fscanf(stdin, "%s", what_do);
        if (feof(stdin)) {
            return 0;
        }
        if (!strcmp(what_do, "result")) {
            for (int i = 0; i <= group_max_mark_qty; ++i) {
                printf("Группа: %s. Балл: %.2lf\n", students[group_max_mark[i]].group, max_mark, &students_qty, index_group);
            }
        } else if (!strcmp(what_do, "add")) {
            FILE *add_file = fopen(argv[1], "a");
            if (!add_file) {
            printf("I/O Error: can't open file.\n");
                exit(1);
            }
            add_student(add_file, &students, group_max_mark, &max_mark, &group_max_mark_qty, &students_qty, index_group);
            if (feof(stdin)) {
                fclose(add_file);
                return 0;
            }
            fclose(add_file);
        } else if (!strcmp(what_do, "remove")) {
            char surname[STR_SIZE];
            char initials[3];
            fscanf(stdin, "%s", surname);
            if (feof(stdin)) {
                return 0;
            }
            fscanf(stdin, "%s", initials);
            if (feof(stdin)) {
                return 0;
            }
            remove_student(argv[1], surname, initials, &students, group_max_mark, &max_mark, &group_max_mark_qty, &students_qty, index_group);
        } else if (!strcmp(what_do, "close") || !strcmp(what_do, "exit")) {
            break;
        } else if (!strcmp(what_do, "info")) {
            FILE *in = fopen(argv[1], "r");
            if (!in) {
                printf("I/O Error: can't open file.\n");
                exit(1);
            }
            char surname[STR_SIZE];
            char initials[3];
            fscanf(stdin, "%s", &surname);
            if (feof(stdin)) {
                return 0;
            }
            fscanf(stdin, "%s", &initials);
            if (feof(stdin)) {
                fclose(in);
                return 0;
            }
            info_student(in, surname, initials);
            fclose(in);
        } else if (!strcmp(what_do, "help")) {
            printf("\tresult - вывод результата\n");
            printf("\tadd    [фамилия] [инициалы] [пол] [группа] [количество предметов] [пары [предмет][оценка]] - добавить студента\n");
            printf("\tremove    [фамилия] [инициалы] - удалить студента\n");
            printf("\tinfo    [фамилия] [инициалы] - информация о студенте\n");
            printf("\texit - завершение программы\n");
        } else {
            // return 0;
        }
    }

    return 0;
}