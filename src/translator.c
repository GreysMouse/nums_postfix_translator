#include "../include/buffer.h"
#include "../include/scanner.h"
#include "../include/translator.h"
#include "../macro/exceptions.h"
#include <string.h>

// static void expr(FILE *input, stack *result, int lpar, long *ppos);
// static void term(FILE *input, stack *result, int lpar, long *ppos);
// static void fact(token **tokens, char **result);
// static void rpar(FILE *input, stack *result, long *ppos);

char *translate(FILE *src, long src_len)
{
    token *tokens;
    char *result;

    tokens = scan(src, src_len);
    result = create_buf(sizeof(char) * (src_len + 1));

    fact(&tokens, &result);

    return result;
}

static void fact(token **tokens, char **result)
{
    token_id id = (**tokens).id;

    if (id == NUM) {
        // memcpy();
        *tokens++;
        *result += 2;
    } else if (peek == '(') {
        fact(input, result, ppos);
        expr(input, result, 1, ppos);
        rpar(input, result, ppos);
    } else if (peek == EOF) {
        SYNTAX_NO_OPND_ERR(*ppos + 1);
    } else {
        SYNTAX_INVAL_OPND_ERR(*ppos, peek);
    }
}