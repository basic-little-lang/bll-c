
#ifndef _PARSER_H_
#define _PARSER_H_

typedef enum {
    PARSER_TOKEN_ADD,
    PARSER_TOKEN_SUBTRACT,
    PARSER_TOKEN_DIVIDE,
    PARSER_TOKEN_MULTIPLIE,
    PARSER_TOKEN_MODULO,
    PARSER_TOKEN_POWER,
    PARSER_TOKEN_NUMBER,
    PARSER_TOKEN_EQUAL,
    PARSER_TOKEN_PRINT,
    PARSER_TOKEN_COPY,
    PARSER_TOKEN_VAR,
} parser_token_type_t;

typedef struct {
    parser_token_type_t token_type;
    void* data;
} parser_token_t;

#endif
