#include <stdio.h>

#ifndef PARSER_H
#define PARSER_H

typedef enum {
    NUM = '0',
    PLUS = '+',
    MINUS = '-',
    MUL = '*',
    DIV = '/',
    L_PAREN = '(',
    R_PAREN = ')',
    BOUND = EOF
} token_id;

typedef struct token {
    token_id id;
    char *lex; /* ignored for non NUM */
    long len;  /* ignored for non NUM */
} token;

token *scan(FILE *src, long src_len);

void free_tokens(token *tokens);

#endif