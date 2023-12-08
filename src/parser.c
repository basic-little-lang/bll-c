#include <stdlib.h>
#include "include/string.h"
#include "include/parser.h"

parser_token_t* parser_token_base_init(parser_token_type_t token_type) {
    parser_token_t* token = malloc(sizeof(parser_token_t));

    token->token_type = token_type;
    token->data = NULL;

    return token;
}

parser_token_t* parser_token_number_init(double data) {
    parser_token_t* token = malloc(sizeof(parser_token_t));

    token->token_type = PARSER_TOKEN_TYPE_NUMBER;
    token->data = malloc(sizeof(double));
    *((double*) token->data) = data;

    return token;
}

parser_token_t* parser_token_var_init(const string_t* data) {
    parser_token_t* token = malloc(sizeof(parser_token_t));

    token->token_type = PARSER_TOKEN_TYPE_VAR;

    string_t* str = string_init();
    for (int i = 0; i < string_size(data); i++) {
        string_add(str, *string_get(data, i));
    }

    token->data = str;

    return token;
}
