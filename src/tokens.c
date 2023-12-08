#include "include/vector.h"
#include "include/string.h"
#include "include/tokens.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

const char TOKEN_COMMENT_CHAR = '#';

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

string_t* token_string(const token_t* token) {
    switch (token_type(token)) {
        case TOKEN_TYPE_CHAR:
            {
                string_t* str = string_from(5, "CHAR(");
                string_add(str, *((char*) token_data(token)));
                string_add(str, ')');
                return str;
            }
            break;
        case TOKEN_TYPE_ADD:
            {
                string_t* str = string_from(3, "ADD");
                return str;
            }
            break;
        case TOKEN_TYPE_SUBTRACT:
            {
                string_t* str = string_from(8, "SUBTRACT");
                return str;
            }
            break;
        case TOKEN_TYPE_DIVIDE:
            {
                string_t* str = string_from(6, "DIVIDE");
                return str;
            }
            break;
        case TOKEN_TYPE_MULTIPLIE:
            {
                string_t* str = string_from(9, "MULTIPLIE");
                return str;
            }
            break;
        case TOKEN_TYPE_MODULO:
            {
                string_t* str = string_from(6, "MODULO");
                return str;
            }
            break;
        case TOKEN_TYPE_POWER:
            {
                string_t* str = string_from(5, "POWER");
                return str;
            }
            break;
        case TOKEN_TYPE_EQUAL:
            {
                string_t* str = string_from(5, "EQUAL");
                return str;
            }
            break;
        case TOKEN_TYPE_NEGITIVE:
            {
                string_t* str = string_from(8, "NEGITIVE");
                return str;
            }
            break;
        case TOKEN_TYPE_POINT:
            {
                string_t* str = string_from(5, "POINT");
                return str;
            }
            break;
        case TOKEN_TYPE_WHITESPACE:
            {
                string_t* str = string_from(10, "WHITESPACE");
                return str;
            }
            break;
        default:
            {
                string_t* str = string_init();
                return str;
            }
            break;
    }
}

void* token_data(const token_t* token) {
    return token->data;
}

void token_destory(token_t* token) {
    switch (token_type(token)) {
        case TOKEN_TYPE_CHAR:
            free(token->data);
            free(token);
            break;
        default:
            free(token);
            break;
    }
}

vector_t* token_tokenize_string(string_t* str) {
    vector_t* tokens = vector_init();

    bool skip_comment = false;
    bool free_if_fail = false;

    for (int i = 0; i < string_size(str); i++) {
        char chr = *string_get(str, i);

        if (chr == '\n') {
            if (skip_comment) {
                skip_comment = false;
                continue;
            }
            vector_add(tokens, token_base_init(TOKEN_TYPE_WHITESPACE));
            free_if_fail = true;
            continue;
        }

        if (skip_comment) continue;
        if (chr == TOKEN_COMMENT_CHAR) {
            skip_comment = true;
            continue;
        }
        if (isspace(chr)) {
            vector_add(tokens, token_base_init(TOKEN_TYPE_WHITESPACE));
            free_if_fail = true;
            continue;
        }

        switch (chr) {
            case '+':
                vector_add(tokens, token_base_init(TOKEN_TYPE_ADD));
                free_if_fail = true;
                break;
            case '-':
                {
                    int next_index = i + 1;
                    if (next_index > string_size(str) && next_index > 0) {
                        if (free_if_fail) {
                            for (int j = 0; j < vector_size(tokens); j++) {
                                token_destory(vector_get(tokens, j));
                            }
                        }
                        vector_destroy(tokens);
                        return NULL;
                    }

                    char ch = *string_get(str, next_index);

                    if (isspace(ch)) {
                        vector_add(tokens, token_base_init(TOKEN_TYPE_SUBTRACT));
                    } else {
                        vector_add(tokens, token_base_init(TOKEN_TYPE_NEGITIVE));
                    }
                    free_if_fail = true;

                }
                break;
            case '*':
                vector_add(tokens, token_base_init(TOKEN_TYPE_MULTIPLIE));
                free_if_fail = true;
                break;
            case '/':
                vector_add(tokens, token_base_init(TOKEN_TYPE_DIVIDE));
                free_if_fail = true;
                break;
            case '%':
                vector_add(tokens, token_base_init(TOKEN_TYPE_MODULO));
                free_if_fail = true;
                break;
            case '^':
                vector_add(tokens, token_base_init(TOKEN_TYPE_POWER));
                free_if_fail = true;
                break;
            case '.':
                vector_add(tokens, token_base_init(TOKEN_TYPE_POINT));
                free_if_fail = true;
                break;
            case '=':
                vector_add(tokens, token_base_init(TOKEN_TYPE_EQUAL));
                free_if_fail = true;
                break;
            default:
                if (!isdigit(chr) && !isalpha(chr)) {
                    continue;
                }
                vector_add(tokens, token_char_init(chr));
                free_if_fail = true;
                break;
        }

    }

    return tokens;
}
