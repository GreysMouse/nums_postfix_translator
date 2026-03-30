#include "../include/buffer.h"
#include "../include/scanner.h"
#include "../include/translator.h"
#include "../macro/exceptions.h"
#include <string.h>

static void expr(token **tokens, char **result, int lpar);
static void term(token **tokens, char **result, int lpar);
static void atom(token **tokens, char **result);
static void rpar(token **tokens);

char *translate(FILE *src, long src_len)
{
    token *tokens;
    char *result;

    tokens = scan(src, src_len);
    result = create_buf(sizeof(char) * (src_len + 1));

    /* work with 'tokens' and 'result'
     * in the same way as with a stream */
    atom(&tokens, &result);
    expr(&tokens, &result, 0);

    free_tokens(tokens);

    *result = '\0';

    return result;
}

static void expr(token **tokens, char **result, int lpar)
{
    for (token t = **tokens; t.id != BOUND; (*tokens)++, t = **tokens) {
        if (t.id == PLUS || t.id == MINUS) {
            (*tokens)++;

            atom(tokens, result);
            term(tokens, result, lpar);

            **result = (char)t.id;
            (*result)++;
        } else if (t.id == MUL || t.id == DIV) {
            (*tokens)--;

            term(tokens, result, lpar);
        } else if (t.id == R_PAREN) {
            if (!lpar) {
                SYNTAX_LPAREN_ERR(1L);
            }

            (*tokens)--;
            break;
        } else {
            SYNTAX_INVAL_OP_ERR(1L, (char)t.id);
        };
    }
}

static void term(token **tokens, char **result, int lpar)
{
    for (token t = **tokens; t.id != BOUND; (*tokens)++, t = **tokens) {
        if (t.id == MUL || t.id == DIV) {
            (*tokens)++;

            atom(tokens, result);

            **result = (char)t.id;
            (*result)++;
        } else if (t.id == PLUS || t.id == MINUS) {
            (*tokens)--;
            break;
        } else if (t.id == R_PAREN) {
            if (!lpar) {
                SYNTAX_LPAREN_ERR(1L);
            }

            (*tokens)--;
            break;
        } else {
            SYNTAX_INVAL_OP_ERR(1L, (char)t.id);
        };
    }
}

static void atom(token **tokens, char **result)
{
    token t = **tokens;

    (*tokens)++;

    if (t.id == NUM) {
        memcpy(*result, t.lex, sizeof(char) * t.len);
        *result += t.len;
    } else if (t.id == L_PAREN) {
        atom(tokens, result);
        expr(tokens, result, 1);
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