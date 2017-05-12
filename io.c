#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "io.h"

int student_read_txt(Student *s, FILE *in)
{
    fscanf(in, "%s", s->surname);
    fscanf(in, "%s", s->initials);
    fscanf(in, "%s", s->gender);
    fscanf(in, "%s", s->group);
    fscanf(in, "%d", &s->marks_qty);
    for (int i = 0; i < s->marks_qty; ++i) {
        fscanf(in, "%s", (s->marks.ob[i]));
        fscanf(in, "%d", &(s->marks.mark[i]));
    }
    return !feof(in);
}

void student_write_txt(Student *s, FILE *file)
{
    fprintf(file, "%s\t", s->surname);
    fprintf(file, "%s\t", s->initials);
    fprintf(file, "%s\t ", s->gender);
    fprintf(file, "%s\t", s->group);
    fprintf(file, "%d\t", s->marks_qty);
    for (int i = 0; i < s->marks_qty; ++i) {
        fprintf(file, "%s\t", s->marks.ob[i]);
        fprintf(file, "%d\t", s->marks.mark[i]);
    }
    fprintf(file, "\n");
}

int student_read_bin(Student *s, FILE *in)
{
    fread(s->surname,      sizeof(char), STR_SIZE, in);
    fread(s->initials,     sizeof(char), STR_SIZE, in);
    fread(s->gender,       sizeof(char), STR_SIZE, in);
    fread(s->group,        sizeof(char), STR_SIZE, in);
    fread(&(s->marks_qty), sizeof(int), 1, in);
    for (int i = 0; i < s->marks_qty; ++i) {
        fread((s->marks.ob[i]),    sizeof(char), STR_SIZE, in);
        fread(&(s->marks.mark[i]), sizeof(int), 1, in);
    }
    return !feof(in);
}

void student_write_bin(Student *s, FILE *out)
{
    fwrite(s->surname,  sizeof(char), STR_SIZE, out);
    fwrite(s->initials, sizeof(char), STR_SIZE, out);
    fwrite((s->gender), sizeof(char), STR_SIZE, out);
    fwrite((s->group),  sizeof(char), STR_SIZE, out);
    fwrite(&(s->marks_qty), sizeof(int), 1, out);
    for (int i = 0; i < s->marks_qty; ++i) {
        fwrite((s->marks.ob[i]), sizeof(char), STR_SIZE, out);
        fwrite(&(s->marks.mark[i]), sizeof(int), 1, out);
    }
}
