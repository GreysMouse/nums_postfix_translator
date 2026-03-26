#include <stddef.h>
#include <stdio.h>

#ifndef STREAM_H
#define STREAM_H

FILE *open_file(const char *name, const char *mode);

void read_file(FILE *input, void *buf, size_t memb_size, size_t memb_count);

long file_size(const char *name, FILE *input);

#endif