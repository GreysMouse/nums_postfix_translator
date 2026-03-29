#include "../include/stream.h"
#include "../macro/exceptions.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

FILE *open_file(const char *name, const char *mode)
{
    FILE *file = fopen(name, mode);

    if (!file) {
        perror(name);
        exit(errno);
    }
    return file;
}

long file_size(const char *name, FILE *input)
{
    int end = fseek(input, 0L, SEEK_END);

    if (end == -1) {
        perror(name);
        exit(errno);
    }

    long fpos = ftell(input);

    if (fpos == -1) {
        perror(name);
        exit(errno);
    }
    rewind(input);

    return fpos;
}

int file_pull_c(FILE *input, long *ppos)
{
    int c = fgetc(input);

    if (c == EOF) {
        if (!feof(input)) {
            INPUT_STREAM_ERR();
        }
    } else {
        (*ppos)++;
    }
    return c;
}

void file_push_c(FILE *input, int c, long *ppos)
{
    if (ungetc(c, input) == EOF) {
        INPUT_STREAM_ERR();
    }
    (*ppos)--;
}