#include "../include/buffer.h"
#include "../include/parser.h"
#include "../include/translator.h"
#include "../macro/exceptions.h"
#include <string.h>

// static void expr(FILE *input, stack *result, int lpar, long *ppos);
// static void term(FILE *input, stack *result, int lpar, long *ppos);
static void fact(token **tokens, char **result);
// static void rpar(FILE *input, stack *result, long *ppos);

void translate(const char *input, char *output, long input_len)
{
    token *tokens;

    long tokens_len;
    long pos = 0;

    if (!input_len) {
        NO_INPUT_DATA();
    }

    /* It is assumed that each input symbol can be a token */
    tokens = create_buf(sizeof(token) * input_len);

    parse(input, input_len, tokens, &tokens_len);

    fact(&tokens, &output, &pos);

    // expr(input, result, 0, &pos);

    // stack_push_c(result, '\0');
}

static void fact(token **pp_tokens, char **pp_result, long *ppos)
{
    token t = **pp_tokens;
    *ppos++;

    if (t.id == NUM) {
        memcpy(*pp_result, t.lex, sizeof(char) * t.len);
        *pp_tokens++;
        *pp_result += sizeof(char) * t.len;
    } else if (t.id == L_PAREN) {
        fact(pp_tokens, pp_result, ppos);
        expr(pp_tokens, pp_result, 1, ppos);
        rpar(pp_tokens, pp_result, ppos);
    } else if (t.id == EOF) {
        SYNTAX_NO_OPND_ERR(*ppos + 1);
    } else {
        SYNTAX_INVAL_OPND_ERR(*ppos, *t.lex);
    }
}

static void rpar(token **pp_tokens, char **pp_result, long *ppos)
{
    token t = **pp_tokens;
    *ppos++;

    if (t.id != R_PAREN) {
        SYNTAX_RPAREN_ERR(*ppos + 1);
    }
}