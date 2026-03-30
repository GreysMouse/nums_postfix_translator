#include <stdio.h>

#ifndef PARSER_H
#define PARSER_H

enum token_id { NUM, PLUS, MINUS, MUL, DIV, L_PAREN, R_PAREN, BOUND };

typedef struct token {
    int id;
    char *lex;
} token;

token *scan(FILE *src, long src_len);

#endif