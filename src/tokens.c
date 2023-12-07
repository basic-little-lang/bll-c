#include "include/string.h"
#include "include/tokens.h"
#include <stdlib.h>

token_t* token_base_init(token_type_t type) {
    token_t* token = malloc(sizeof(token_t));

    token->token_type = type;
    token->data = NULL;

    return token;
}
