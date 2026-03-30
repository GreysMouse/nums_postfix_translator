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

    return result;
}
