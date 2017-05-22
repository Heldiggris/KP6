#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "io.h"

int main(int argc, char *argv[])
{
    List *l[MAX_GROUP] = { NULL };
    char group_max_mark[STR_SIZE] = " ";
    double max_mark = 0;
    int index_group[MAX_GROUP] = { 0 } ;
    int index_qty = 0;
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }
    group_max_avg_mark(in, l, group_max_mark, &max_mark, &index_qty, index_group);
    fclose(in);

    char what_do[STR_SIZE];
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }
    printf("Введите запрос\n");
    while (!feof(stdin)) {
        fscanf(stdin, "%s", what_do);
        if (feof(stdin)) {
            break;
        }
        if (!strcmp(what_do, "result")) {
                printf("Группа: %s. Балл: %.2lf\n", group_max_mark, max_mark);
        } else if (!strcmp(what_do, "add")) {
            FILE *add_file = fopen(argv[1], "a");
            if (!add_file) {
            printf("I/O Error: can't open file.\n");
                exit(1);
            }
            if (feof(stdin)) {
                fclose(add_file);
                break;
            }
            fclose(add_file);
        } else if (!strcmp(what_do, "remove")) {
            char surname[STR_SIZE];
            char initials[3];
            fscanf(stdin, "%s", surname);
            if (feof(stdin)) {
                break;
            }
            fscanf(stdin, "%s", initials);
            if (feof(stdin)) {
                break;
            }
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
                break;
            }
            fscanf(stdin, "%s", &initials);
            if (feof(stdin)) {
                fclose(in);
                break;
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
        }
    }
    int pos = 0;


    for (int i = 0; i < index_qty; ++i) {
        list_destroy(l[index_group[i]]);
    }

    return 0;
}