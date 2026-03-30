#include <stdio.h>

#ifndef PARSER_H
#define PARSER_H

typedef enum { NUM, PLUS, MINUS, MUL, DIV, L_PAREN, R_PAREN, BOUND } token_id;

typedef struct token {
    token_id id;
    char *lex;
} token;

token *scan(FILE *src, long src_len);

#endif