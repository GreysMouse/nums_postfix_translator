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

void read_file(FILE *input, void *buf, size_t memb_size, size_t memb_count)
{
    size_t n = fread(buf, memb_size, memb_count, input);

    if (n != memb_count) {
        INPUT_STREAM_READ_ERR();
    }
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