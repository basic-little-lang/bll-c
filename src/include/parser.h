
#ifndef _PARSER_H_
#define _PARSER_H_

#include "string.h"

typedef enum {
    PARSER_TOKEN_TYPE_ADD,
    PARSER_TOKEN_TYPE_SUBTRACT,
    PARSER_TOKEN_TYPE_DIVIDE,
    PARSER_TOKEN_TYPE_MULTIPLIE,
    PARSER_TOKEN_TYPE_MODULO,
    PARSER_TOKEN_TYPE_POWER,
    PARSER_TOKEN_TYPE_NUMBER,
    PARSER_TOKEN_TYPE_EQUAL,
    PARSER_TOKEN_TYPE_PRINT,
    PARSER_TOKEN_TYPE_COPY,
    PARSER_TOKEN_TYPE_VAR,
} parser_token_type_t;

typedef struct {
    parser_token_type_t token_type;
    void* data;
} parser_token_t;

parser_token_t* parser_token_base_init(parser_token_type_t token_type);
parser_token_t* parser_token_number_init(double data);
parser_token_t* parser_token_var_init(const string_t* data);
parser_token_type_t parser_token_type(const parser_token_t* parser_token);
void* parser_token_data(const parser_token_t* parser_token);
string_t* parser_token_string(const parser_token_t* parser_token);
void parser_token_destory(parser_token_t* parser_token);

#endif
