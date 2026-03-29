#ifndef PARSER_H
#define PARSER_H

enum token_id { NUM, LP_OP, HP_OP, L_PAREN, R_PAREN, BOUND };

typedef struct token {
    char *lex;
    long len;
    int id;
} token;

void parse(const char *input, long input_len, token *output, long *output_len);

#endif