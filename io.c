#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "io.h"

int student_read_txt(Student *s, FILE *in)
{
    fscanf(in, "%s", &s->surname);
    fscanf(in, "%s", &s->initials);
    fscanf(in, "%s", &s->gender);
    fscanf(in, "%s", &s->group);
    fscanf(in, "%d", &s->marks_qty);
    for (int i = 0; i < s->marks_qty; ++i) {
        fscanf(in, "%s", &s->marks->ob[i]);
        fscanf(in, "%d", &s->marks->mark[i]);
    }
    return !feof(in);
}

void student_write_txt(Student *s, FILE *file)
{
    printf(file, "%s", &s->surname);
    printf(file, "%s", &s->initials);
    printf(file, "%s", &s->gender);
    printf(file, "%s", &s->group);
    printf(file, "%d", &s->marks_qty);
    for (int i = 0; i < s->marks_qty; ++i) {
        printf(file, "%s", &s->marks->ob[i]);
        printf(file, "%d", &s->marks->mark[i]);
    }
}

int student_read_bin(Student *s, FILE *in)
{
    fread(s->surname,  sizeof(char), STR_SIZE, in);
    fread(s->initials, sizeof(char), STR_SIZE, in);
    fread(&(s->gender), sizeof(char), STR_SIZE, in);
    fread(&(s->group), sizeof(char), STR_SIZE, in);
    fread(&(s->marks_qty), sizeof(int), 1, in);
    printf("%d\n", s->marks_qty);
    for (int i = 0; i < s->marks_qty; ++i) {
        printf("bbb\n");
        fread(&(s->marks->ob[i]), sizeof(char), STR_SIZE, in);
        printf("ccc\n");
        fread(&(s->marks->mark[i]), sizeof(int), 1, in);
        printf("ddd\n");
    }
    return !feof(in);
}

void student_write_bin(Student *s, FILE *out)
{
    fwrite(s->surname,  sizeof(char), STR_SIZE, out);
    fwrite(s->initials, sizeof(char), STR_SIZE, out);
    fwrite(&(s->gender), sizeof(char), STR_SIZE, out);
    fwrite(&(s->group), sizeof(char), STR_SIZE, out);
    fwrite((s->marks_qty), sizeof(int), 1, out);
    for (int i = 0; i < s->marks_qty; ++i) {
        fwrite((s->marks->ob[i]), sizeof(char), 20, out);
        fwrite(&(s->marks->mark[i]), sizeof(int), 1, out);
    }
}

// void student_print(Student *s)
// {
//     printf("Name: %s %s\n", s->surname, s->initials);
//     printf("Gender: %s\n", s->gender);
//     printf("Group: %s\n", s->group);
//     printf("Discrete math: %d\n", s->dm);
//     printf("Calculus: %d\n", s->ma);
//     printf("Linear algebra: %d\n", s->la);
//     printf("Computer science: %d\n", s->cs);
//     printf("History: %d\n", s->hi);

//     printf("\n");
// }

