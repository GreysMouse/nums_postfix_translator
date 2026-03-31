#include "include/buffer.h"
#include "include/stream.h"
#include "include/translator.h"
#include "macro/exceptions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *src, *dest = stdout;
    char *result;
    long src_len;

    if (argc < 2) {
        NO_SRC_FILE_ERR(argv[0]);
    }

    src = open_file(argv[1], "r");
    src_len = file_size(argv[1], src);

    if (!src_len) {
        NO_INPUT_DATA();
    }

    result = translate(src, src_len);

    if (argv[2]) {
        dest = open_file(argv[2], "w");
    }

    fprintf(dest, "%s\n", result);
    free(result);
    fclose(src);

    return EXIT_SUCCESS;
}