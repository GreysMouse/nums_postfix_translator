#include "../include/parser.h"
#include "../macro/exceptions.h"

token *parse(const char *input, long input_len, token *output, long *output_len)
{
    /* It is assumed that each input symbol can be a token */
    token *tokens = create_buf(sizeof(token) * input_len);

    int pile = 0;
    long idx = 0;

    for (long pos = 0; pos < input_len; pos++) {
        char c = input[pos];

        if (c >= '0' && c <= '9') {
            tokens[idx].id = NUM;

            if (pile) {
                tokens[idx].len++;
                continue;
            }
            pile = 1;
        } else {
            if (c == '+' || c == '-') {
                tokens[idx].id = LP_OP;
            } else if (c == '*' || c == '/') {
                tokens[idx].id = HP_OP;
            } else {
                PARSE_INVAL_CHAR_ERR(pos + 1);
            }
            pile = 0;
        }

        tokens[idx].lex = (char *)input + pos;
        tokens[idx].len = 1;

        idx++;
    }

    /* Adding BOUND(EOF) token */
    tokens[idx].id = BOUND;
    idx++;

    *output_len = idx;
}