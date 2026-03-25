#include <stddef.h>
#include <stdio.h>

#ifndef STREAM_H
#define STREAM_H

FILE *open_file(const char *name, const char *mode);

size_t read_file(FILE *input, void *buf, size_t len);

long file_size(const char *name, FILE *input);

#endif