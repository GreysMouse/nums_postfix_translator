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

size_t read_file(FILE *input, void *buf, size_t len)
{
    size_t n = fread(buf, sizeof(buf), len, input);

    if (n != len) {
        INPUT_STREAM_READ_ERR();
    }
    return n;
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