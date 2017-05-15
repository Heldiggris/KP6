#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "io.h"

int main(int argc, char *argv[])
{
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
            FILE *in = fopen(argv[1], "r");
            if (!in) {
                printf("I/O Error: can't open file.\n");
                exit(1);
            }
            group_max_avg_mark(in, "F");
            fclose(in);
        } else if (!strcmp(what_do, "resultMale")) {
            FILE *in = fopen(argv[1], "r");
            if (!in) {
                printf("I/O Error: can't open file.\n");
                exit(1);
            }
            group_max_avg_mark(in, "M");
            fclose(in);
            } else if (!strcmp(what_do, "add")) {
            FILE *add_file = fopen(argv[1], "a");
            if (!add_file) {
            printf("I/O Error: can't open file.\n");
                exit(1);
            }
            Student student;
            fscanf(stdin, "%s", student.surname);
            if (feof(stdin)) {
                return 0;
            }
            fscanf(stdin, "%s", student.initials);
            if (feof(stdin)) {
                return 0;
            }
            fscanf(stdin, "%s", student.gender);
            if (feof(stdin)) {
                return 0;
            }
            fscanf(stdin, "%s", student.group);
            if (feof(stdin)) {
                return 0;
            }
            fscanf(stdin, "%d", &student.marks_qty);
            if (feof(stdin)) {
                return 0;
            }
            for (int i = 0; i < student.marks_qty; ++i) {
                fscanf(stdin, "%s", student.marks.ob[i]);
                if (feof(stdin)) {
                    return 0;
                }
                fscanf(stdin, "%d", &student.marks.mark[i]);
                if (feof(stdin)) {
                    return 0;
                }
            }
            student_write_bin(&student, add_file);
            fclose(add_file);
        } else if (!strcmp(what_do, "remove")) {
            char surname[STR_SIZE];
            char initials[3];
            fscanf(stdin, "%s", surname);
            if (feof(stdin)) {
                return 0;;
            }
            fscanf(stdin, "%s", initials);
            if (feof(stdin)) {
                return 0;
            }
            remove_el(argv[1], surname, initials);
        } else if (!strcmp(what_do, "close") || !strcmp(what_do, "exit")) {
            break;
        } else if (!strcmp(what_do, "info")) {
            char surname[STR_SIZE];
            char initials[3];
            fscanf(stdin, "%s", &surname);
            if (feof(stdin)) {
                return 0;
            }
            fscanf(stdin, "%s", &initials);
            if (feof(stdin)) {
            }
            info_student(argv[1], surname, initials);
        } else if (!strcmp(what_do, "help")) {
            printf("\tresult - вывод результата\n");
            printf("\tresultMale - вывод результата для студентов парней\n");
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