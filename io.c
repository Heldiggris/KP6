#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "io.h"

int student_read_txt(Student *s, FILE *in)
{
    fscanf(in, "%s", &(s->surname));
    fscanf(in, "%s", &(s->initials));
    fscanf(in, "%s", &(s->gender));
    fscanf(in, "%s", &(s->group));
    fscanf(in, "%d", &(s->dm));
    fscanf(in, "%d", &(s->ma));
    fscanf(in, "%d", &(s->la));
    fscanf(in, "%d", &(s->cs));
    fscanf(in, "%d", &(s->hi));

    return !feof(in);
}

void student_write_txt(Student *s, FILE *file)
{
    fprintf(file, "%s      ", s->surname);
    fprintf(file, "%s   ", s->initials);
    fprintf(file, "%s        ", s->gender);
    fprintf(file, "%s      ", s->group);
    fprintf(file, "%d ", s->dm);
    fprintf(file, "%d ", s->ma);
    fprintf(file, "%d ", s->la);
    fprintf(file, "%d ", s->cs);
    fprintf(file, "%d \n", s->hi);
}

int student_read_bin(Student *s, FILE *in)
{
    fread(s->surname,  sizeof(char), STR_SIZE, in);
    fread(s->initials, sizeof(char), STR_SIZE, in);
    fread(&(s->gender), sizeof(char), STR_SIZE, in);
    fread(&(s->group), sizeof(char), STR_SIZE, in);
    fread(&(s->dm), sizeof(int), 1, in);
    fread(&(s->ma), sizeof(int), 1, in);
    fread(&(s->la), sizeof(int), 1, in);
    fread(&(s->cs), sizeof(int), 1, in);
    fread(&(s->hi), sizeof(int), 1, in);

    return !feof(in);
}

void student_write_bin(Student *s, FILE *out)
{
    fwrite(s->surname,  sizeof(char), STR_SIZE, out);
    fwrite(s->initials, sizeof(char), STR_SIZE, out);
    fwrite(&(s->gender), sizeof(char), STR_SIZE, out);
    fwrite(&(s->group), sizeof(char), STR_SIZE, out);
    fwrite(&(s->dm), sizeof(int), 1, out);
    fwrite(&(s->ma), sizeof(int), 1, out);
    fwrite(&(s->la), sizeof(int), 1, out);
    fwrite(&(s->cs), sizeof(int), 1, out);
    fwrite(&(s->hi), sizeof(int), 1, out);
}

void student_print(Student *s)
{
    printf("Name: %s %s\n", s->surname, s->initials);
    printf("Gender: %s\n", s->gender);
    printf("Group: %s\n", s->group);
    printf("Discrete math: %d\n", s->dm);
    printf("Calculus: %d\n", s->ma);
    printf("Linear algebra: %d\n", s->la);
    printf("Computer science: %d\n", s->cs);
    printf("History: %d\n", s->hi);

    printf("\n");
}

