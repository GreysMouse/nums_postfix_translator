#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#define NO_INPUT_DATA()                                                        \
    fprintf(stdout, "Nothing to translate: input data is empty\n");            \
    exit(EXIT_SUCCESS);

#define NO_INPUT_FILE_ERR(PROGRAM_NAME)                                        \
    fprintf(stderr, "Usage: %s <input file> [<output file>]\n", PROGRAM_NAME); \
    exit(EXIT_FAILURE);

#define NO_BUFFER_MEMORY_ERR()                                                 \
    fprintf(stderr, "Not enough memory to allocate buffer\n");                 \
    exit(errno);

#define INPUT_STREAM_READ_ERR()                                                \
    fprintf(stderr, "Input data stream read error\n");                         \
    exit(errno);

#define PARSE_INVAL_CHAR_ERR(POSITION)                                         \
    fprintf(stderr, "Parse error: invalid character in position %ld\n",        \
            (POSITION));                                                       \
    exit(EXIT_FAILURE);

#define SYNTAX_LPAREN_ERR(POSITION)                                            \
    fprintf(stderr, "Syntax error: there is no '(' for ')' in position %ld\n", \
            (POSITION));                                                       \
    exit(EXIT_FAILURE);

#define SYNTAX_RPAREN_ERR(POSITION)                                            \
    fprintf(stderr, "Syntax error: there is no ')' in position %ld\n",         \
            (POSITION));                                                       \
    exit(EXIT_FAILURE);

#define SYNTAX_INVAL_OP_ERR(POSITION, PEEK)                                    \
    fprintf(stderr, "Syntax error: invalid operator '%c' in position %ld\n",   \
            (PEEK), (POSITION));                                               \
    exit(EXIT_FAILURE);

#define SYNTAX_INVAL_OPND_ERR(POSITION, PEEK)                                  \
    fprintf(                                                                   \
        stderr,                                                                \
        "Syntax error: operand '%c' in position %ld is not a digit or '('\n",  \
        (PEEK), (POSITION));                                                   \
    exit(EXIT_FAILURE);

#define SYNTAX_NO_OPND_ERR(POSITION)                                           \
    fprintf(stderr, "Syntax error: there is no operand in position %ld\n",     \
            (POSITION));                                                       \
    exit(EXIT_FAILURE);

#endif