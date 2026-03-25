#include "include/buffer.h"
#include "include/stream.h"
#include "macro/exceptions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *input, *output = stdout;
    char *input_buf, *output_buf;
    long buf_size;

    if (argc < 2) {
        NO_INPUT_FILE_ERR(argv[0]);
    }

    input = open_file(argv[1], "r");
    buf_size = file_size(argv[1], input);

    input_buf = create_buf(sizeof(char) * (buf_size + 1));
    output_buf = create_buf(sizeof(char) * (buf_size + 1));

    read_file(input, input_buf, buf_size);
    fclose(input);

    input_buf[buf_size] = '\0';

    if (argv[2]) {
        output = open_file(argv[2], "w");
    }

    fprintf(output, "%s\n", output_buf);

    free(input_buf);
    free(output_buf);

    return EXIT_SUCCESS;
}