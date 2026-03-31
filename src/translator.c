#include "../include/buffer.h"
#include "../include/scanner.h"
#include "../include/translator.h"
#include "../macro/exceptions.h"
#include <string.h>

static void expr(token **tokens, char **output, int lpar);
static void term(token **tokens, char **output, int lpar);
static void atom(token **tokens, char **output);
static void rpar(token **tokens);

char *translate(FILE *src, long src_len)
{
    token *tokens, *pt;
    char *output, *ps;

    tokens = scan(src, src_len);
    output = create_buf(sizeof(char) * (src_len + 1));

    /* work with 'pt' and 'ps'
     * in the same way as with a stream */
    pt = tokens;
    ps = output;

    atom(&pt, &ps);
    expr(&pt, &ps, 0);

    free_tokens(tokens);

    output[src_len] = '\0';

    return output;
}

static void expr(token **tokens, char **output, int lpar)
{
    token_id id;

    while ((**tokens).id != BOUND) {
        id = (**tokens).id;

        if (id == PLUS || id == MINUS) {
            (*tokens)++;

            atom(tokens, output);
            term(tokens, output, lpar);

            **output = (char)id;
            (*output)++;
        } else if (id == MUL || id == DIV) {
            term(tokens, output, lpar);
        } else if (id == R_PAREN) {
            if (!lpar) {
                SYNTAX_LPAREN_ERR(1L);
            }
            break;
        } else {
            SYNTAX_INVAL_OP_ERR(1L, (char)id);
        };
    }
}

static void term(token **tokens, char **output, int lpar)
{
    token_id id;

    while ((**tokens).id != BOUND) {
        id = (**tokens).id;

        if (id == MUL || id == DIV) {
            (*tokens)++;

            atom(tokens, output);

            **output = (char)id;
            (*output)++;
        } else if (id == PLUS || id == MINUS) {
            break;
        } else if (id == R_PAREN) {
            if (!lpar) {
                SYNTAX_LPAREN_ERR(1L);
            }
            break;
        } else {
            SYNTAX_INVAL_OP_ERR(1L, (char)id);
        };
    }
}

static void atom(token **tokens, char **output)
{
    token t = **tokens;

    (*tokens)++;

    if (t.id == NUM) {
        memcpy(*output, t.lex, sizeof(char) * t.len);
        *output += t.len;
    } else if (t.id == L_PAREN) {
        atom(tokens, output);
        expr(tokens, output, 1);
        rpar(tokens);
    } else if (t.id == BOUND) {
        SYNTAX_NO_OPND_ERR(1L);
    } else {
        SYNTAX_INVAL_OPND_ERR(1L, (char)t.id);
    }
}

static void rpar(token **tokens)
{
    token t = **tokens;

    (*tokens)++;

    if (t.id != R_PAREN) {
        SYNTAX_RPAREN_ERR(1L);
    }
}