#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/vector.h"
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

parser_token_type_t parser_token_type(const parser_token_t* parser_token) {
    return parser_token->token_type;
}

void* parser_token_data(const parser_token_t* parser_token) {
    return parser_token->data;
}

string_t* parser_token_string(const parser_token_t* parser_token) {
    switch (parser_token_type(parser_token)) {
        case PARSER_TOKEN_TYPE_NUMBER:
            {
                string_t* str = string_from(7, "NUMBER(");
                char number_str[64];
                sprintf(number_str, "%f", *((double*) parser_token_data(parser_token)));
                for (int i = 0; i < strlen(number_str); i++) {
                    string_add(str, number_str[i]);
                }
                string_add(str, ')');
                return str;
            }
            break;
        case PARSER_TOKEN_TYPE_VAR:
            {
                string_t* str = string_from(4, "VAR(");
                string_t* data = parser_token_data(parser_token);
                for (int i = 0; i < string_size(data); i++) {
                    string_add(str, *string_get(data, i));
                }
                string_add(str, ')');
                return str;
            }
            break;
        case PARSER_TOKEN_TYPE_ADD:
            {
                string_t* str = string_from(3, "ADD");
                return str;
            }
            break;
        case PARSER_TOKEN_TYPE_SUBTRACT:
            {
                string_t* str = string_from(8, "SUBTRACT");
                return str;
            }
            break;
        case PARSER_TOKEN_TYPE_DIVIDE:
            {
                string_t* str = string_from(6, "DIVIDE");
                return str;
            }
            break;
        case PARSER_TOKEN_TYPE_MULTIPLIE:
            {
                string_t* str = string_from(9, "MULTIPLIE");
                return str;
            }
            break;
        case PARSER_TOKEN_TYPE_MODULO:
            {
                string_t* str = string_from(6, "MODULO");
                return str;
            }
            break;
        case PARSER_TOKEN_TYPE_POWER:
            {
                string_t* str = string_from(5, "POWER");
                return str;
            }
            break;
        case PARSER_TOKEN_TYPE_EQUAL:
            {
                string_t* str = string_from(5, "EQUAL");
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

void parser_token_destory(parser_token_t* parser_token) {
    switch (parser_token_type(parser_token)) {
        case PARSER_TOKEN_TYPE_NUMBER:
            free(parser_token->data);
            free(parser_token);
            break;
        case PARSER_TOKEN_TYPE_VAR:
            string_destory(parser_token->data);
            free(parser_token);
            break;
        default:
            free(parser_token);
            break;
    }
}

vector_t* parser_convert(const vector_t* direct_tokens) {
    vector_t* parsered_tokens = vector_init();
    vector_t* buffer = vector_init();

    

    vector_destroy(buffer);
    return parsered_tokens;
}
