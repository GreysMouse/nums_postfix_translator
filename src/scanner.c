#include "../include/buffer.h"
#include "../include/scanner.h"
#include "../include/stream.h"
#include "../macro/exceptions.h"
#include <stdio.h>

static long peek_num_len(FILE *src, long *ppos);
static char *read_num(FILE *src, long len, long *ppos);

token *scan(FILE *src, long src_len)
{
    token *tokens;

    int c;
    long idx = 0;
    long pos = 0;
    long num_len = 0;

    /* Initially, it is assumed that each input symbol can be a token
     * and one extra token for bound */
    tokens = create_buf(sizeof(token) * (src_len + 1));

    while ((c = file_pull_c(src, &pos)) != EOF) {
        if (c >= '0' && c <= '9') {
            num_len = peek_num_len(src, &pos);

            tokens[idx].id = NUM;
            tokens[idx].lex = read_num(src, num_len, &pos);
            tokens[idx].len = num_len;
        } else if (c == '+') {
            tokens[idx].id = PLUS;
        } else if (c == '-') {
            tokens[idx].id = MINUS;
        } else if (c == '*') {
            tokens[idx].id = MUL;
        } else if (c == '/') {
            tokens[idx].id = DIV;
        } else if (c == '(') {
            tokens[idx].id = L_PAREN;
        } else if (c == ')') {
            tokens[idx].id = R_PAREN;
        } else {
            PARSE_INVAL_CHAR_ERR(pos + 1);
        }
        idx++;
    }
    tokens[idx].id = BOUND;

    return tokens;
}

void free_tokens(token *tokens)
{
    token *t = tokens;

    for (; t->id != BOUND; t++) {
        free(t->lex);
    }
    free(tokens);
}

static long peek_num_len(FILE *src, long *ppos)
{
    int c;
    long len = 0;
    long offset = 0; /* file position shift from first number`s digit */

    do {
        c = file_pull_c(src, ppos);
        len++;
    } while (c >= '0' && c <= '9');

    offset = c == EOF ? -len : -len - 1;

    if (fseek(src, sizeof(char) * offset, SEEK_CUR) == -1) {
        INPUT_STREAM_READ_ERR();
    }
    return len;
}

static char *read_num(FILE *src, long len, long *ppos)
{
    char *res;

    res = create_buf(sizeof(char) * len);

    for (int i = 0; i < len; i++) {
        res[i] = (char)file_pull_c(src, ppos);
    }
    return res;
}