#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "io.h"

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage:\n\t./generate FILE_FROM FILE_TO\n");
        exit(0);
    }

    FILE *in  = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (!in || !out) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    Student s;

    if (!strcmp(argv[3], "txt")) {
        while (student_read_bin(&s, in)) {
            student_write_txt(&s, out);
        }
    } else {
        while (student_read_txt(&s, in)) {
            student_write_bin(&s, out);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}

