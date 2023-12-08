#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "include/vector.h"
#include "include/string.h"
#include "include/tokens.h"
#include "include/parser.h"

parser_token_t* parser_string_to_keyword(const string_t* str) {
    if (strcmp(*string_data(str), "print") == 0) {
        return parser_token_base_init(PARSER_TOKEN_TYPE_PRINT);
    }
    if (strcmp(*string_data(str), "copy") == 0) {
        return parser_token_base_init(PARSER_TOKEN_TYPE_COPY);
    }

    return NULL;
}

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

    for (int i = 0; i < vector_size(direct_tokens); i++) {
        token_t* token = vector_get(direct_tokens, i);

        switch (token_type(token)) {
            case TOKEN_TYPE_CHAR:
                vector_add(buffer, token);

                {
                    string_t* string = string_init();

                    for (int j = 0; j < vector_size(buffer); j++) {
                        switch (token_type(vector_get(buffer, j))) {
                            case TOKEN_TYPE_CHAR:
                                string_add(string, *((char*) token_data(vector_get(buffer, j))));
                                break;
                            case TOKEN_TYPE_POINT:
                                string_add(string, '.');
                                break;
                            case TOKEN_TYPE_NEGITIVE:
                                string_add(string, '-');
                                break;
                            default:
                                break;
                        }
                    }

                    bool next_is_whitespace = true;
                    int next_index = i + 1;
                    if (next_index < vector_size(direct_tokens)) next_is_whitespace = (token_type(vector_get(direct_tokens, next_index)) == TOKEN_TYPE_WHITESPACE);

                    if (isdigit(*((char*) token_data(vector_get(direct_tokens, i)))) && next_is_whitespace) {
                        bool is_negitive = false;
                        for (int j = 0; j < string_size(string); j++) {
                            if (*string_get(string, j) == '-') {
                                is_negitive = true;
                                break;
                            }
                        }
                        string_t* str = string_init();
                        for (int j = 0; j < string_size(string); j++) {
                            char chr = *string_get(string, j);
                            if (chr == '-') continue;
                            string_add(str, chr);
                        }
        
                        char num_str[string_size(str) + 1];
                        for (int j = 0; j < string_size(str); j++) {
                            num_str[j] = *string_get(str, j);
                        }
                        num_str[string_size(str)] = 0;
                        double number = atof(num_str);

                        if (is_negitive) number *= -1.0;

                        vector_add(parsered_tokens, parser_token_number_init(number));

                        string_destory(str);

                        vector_destroy(buffer);
                        buffer = vector_init();
                        string_destory(string);

                    } else if (next_is_whitespace) {
                        parser_token_t* keyword_token = parser_string_to_keyword(string);
                        if (keyword_token == NULL) {
                            vector_add(parsered_tokens, parser_token_var_init(string));
                        } else {
                            vector_add(parsered_tokens, keyword_token);
                        }

                        vector_destroy(buffer);
                        buffer = vector_init();
                    } else {
                        string_destory(string);
                    }
                

                }

                break;
            case TOKEN_TYPE_ADD:
                vector_add(parsered_tokens, parser_token_base_init(PARSER_TOKEN_TYPE_ADD));
                break;
            case TOKEN_TYPE_SUBTRACT:
                vector_add(parsered_tokens, parser_token_base_init(PARSER_TOKEN_TYPE_SUBTRACT));
                break;
            case TOKEN_TYPE_MULTIPLIE:
                vector_add(parsered_tokens, parser_token_base_init(PARSER_TOKEN_TYPE_MULTIPLIE));
                break;
            case TOKEN_TYPE_DIVIDE:
                vector_add(parsered_tokens, parser_token_base_init(PARSER_TOKEN_TYPE_DIVIDE));
                break;
            case TOKEN_TYPE_MODULO:
                vector_add(parsered_tokens, parser_token_base_init(PARSER_TOKEN_TYPE_MODULO));
                break;
            case TOKEN_TYPE_POWER:
                vector_add(parsered_tokens, parser_token_base_init(PARSER_TOKEN_TYPE_POWER));
                break;
            case TOKEN_TYPE_POINT:
                vector_add(buffer, token);
                break;
            case TOKEN_TYPE_EQUAL:
                vector_add(parsered_tokens, parser_token_base_init(PARSER_TOKEN_TYPE_EQUAL));
                break;
            case TOKEN_TYPE_NEGITIVE:
                vector_add(buffer, token);
                break;
            case TOKEN_TYPE_WHITESPACE:
                break;
        }

    }

    vector_destroy(buffer);
    return parsered_tokens;
}
