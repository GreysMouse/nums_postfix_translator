#include "../include/buffer.h"
#include "../include/scanner.h"
#include "../include/stream.h"
#include "../macro/exceptions.h"

token *scan(FILE *src, long src_len)
{
    /* Initially, it is assumed that each input symbol can be a token */
    token *tokens;

    tokens = create_buf(sizeof(token) * src_len);

    int peek;
    int pile = 0;
    long idx = 0;
    long pos = 0;

    while ((peek = file_pull_c(src, &pos)) != EOF) {
        if (peek >= '0' && peek <= '9') {

            if (pile) {
                delta++;
                continue;
            }

            tokens[idx].id = NUM;
            pile = 1;
            delta = 0;
        } else if (c == '+' || c == '-') {
            tokens[idx].id = LP_OP;
        } else if (c == '*' || c == '/') {
            tokens[idx].id = HP_OP;
        } else {
            PARSE_INVAL_CHAR_ERR(pos + 1);
        }
        pile = 0;
    }
}

long get_num_len(FILE *src, long *ppos)
{
    int peek;
    long shift = 1; /* file position shift */

    while ((peek = file_pull_c(src, ppos)) != EOF) {
        if (peek >= '0' && peek <= '9') {
            shift++;
        } else {
            int end = fseek(input, 0L, SEEK_END);

            if (end == -1) {
                perror(name);
                exit(errno);
            }
        }
    }
}