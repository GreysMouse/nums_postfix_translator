#include <stddef.h>
#include <stdio.h>

#ifndef STREAM_H
#define STREAM_H

FILE *open_file(const char *name, const char *mode);

long file_size(const char *name, FILE *input);

int file_pull_c(FILE *input, long *ppos);
void file_push_c(FILE *input, int c, long *ppos);

#endif