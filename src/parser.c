#include <stdlib.h>
#include "include/parser.h"

parser_token_t* parser_token_base_init(parser_token_type_t token_type) {
    parser_token_t* token = malloc(sizeof(parser_token_t));

    token->token_type = token_type;
    token->data = NULL;

    return token;
}

parser_token_t* parser_token_number_init(double data) {
    parser_token_t* token = malloc(sizeof(parser_token_t));

    token->token_type = PARSER_TOKEN_NUMBER;
    token->data = malloc(sizeof(double));
    *((double*) token->data) = data;

    return token;
}
