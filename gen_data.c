#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char latin[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZFM";
#define LATIN_SIZE ((int)(sizeof(latin) - 1))
char digits[] = "123456789";
#define DIGITS_SIZE ((int)(sizeof(digits) - 1))
#define SUBJ_SIZE 20

#define FNAME_SIZE 32
#define NAME_MAX_SIZE 23
#define BUF_SIZE (4 * 1024 * 1024)

char buf[BUF_SIZE] = { '\0' };
static unsigned int g_seed = 0;


static inline void fast_srand(int seed)
{
    g_seed = seed;
}

static inline int fast_rand()
{
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}


int main(int argc, char *argv[])
{
    int qty = 10;// * 1000 * 1000;
    if (argc >= 2) {
        qty = atoi(argv[1]);
    }
    
    char fname[FNAME_SIZE] = "_input.txt";
    if (argc >= 3) {
        strncat(argv[2], fname, FNAME_SIZE - 1);
    }
    
    FILE *f = fopen(fname, "wb");
    if (!f) {
        fprintf(stderr, "Error: can't open file '%s'.\n", fname);
        return 1;
    }
    
    fast_srand(0);

    register int buf_pos = 0;
    for (int i = 0; i < qty; ++i) {
        register int name_size = fast_rand() % NAME_MAX_SIZE + 1;
        for (register int j = 0; j < name_size; ++j) {
            buf[buf_pos++] = latin[fast_rand() % LATIN_SIZE];
        }
        buf[buf_pos++] = ' ';
        buf[buf_pos++] = latin[fast_rand() % LATIN_SIZE];
        buf[buf_pos++] = latin[fast_rand() % LATIN_SIZE];
        buf[buf_pos++] = '\t';

        buf[buf_pos++] = latin[LATIN_SIZE + fast_rand() % 2 - 2];
        buf[buf_pos++] = '\t';
        for (register int j = 0; j < 4; ++j) {
            buf[buf_pos++] = latin[fast_rand() % LATIN_SIZE];
        }
        buf[buf_pos++] = '\t';
        int azz = digits[fast_rand() % DIGITS_SIZE];
        // printf("*%d*  \n", azz - '0');
        buf[buf_pos++] = azz;
        buf[buf_pos++] = '\t';
        for(int k = 0; k < azz - '0'; ++k) {
            for (register int j = 0; j < 4; ++j) {
                buf[buf_pos++] = latin[fast_rand() % LATIN_SIZE];
            }
            buf[buf_pos++] = '\t';
            buf[buf_pos++] = digits[fast_rand() % 5];
            buf[buf_pos++] = '\t';
        }

        // buf[buf_pos++] = digits[fast_rand() % DIGITS_SIZE];
        buf[buf_pos++] = '\n';
        buf[buf_pos + 1] = '\0';

        if (buf_pos >= BUF_SIZE - 64) {
            fwrite(buf, sizeof(buf[0]), buf_pos, f);
            buf_pos = 0;
        }
    }

    if (buf_pos > 0) {
        fwrite(buf, sizeof(buf[0]), buf_pos, f);
    }
    
    fclose(f);
    
    return 0;
}