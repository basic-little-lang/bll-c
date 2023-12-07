#include "include/string.h"
#include "include/tokens.h"
#include <stdlib.h>

token_t* token_base_init(token_type_t type) {
    token_t* token = malloc(sizeof(token_t));

    token->token_type = type;
    token->data = NULL;

    return token;
}

token_t* token_char_init(char data) {
    token_t* token = malloc(sizeof(token_t));

    token->token_type = TOKEN_TYPE_CHAR;
    token->data = malloc(sizeof(char));
    *((char*) token->data) = data;

    return token;
}

token_type_t token_type(const token_t* token) {
    return token->token_type;
}
