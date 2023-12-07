
#ifndef _TOKENS_H_
#define _TOKENS_H_

#include "string.h"

typedef enum {
    TOKEN_TYPE_ADD,
    TOKEN_TYPE_SUBTRACT,
    TOKEN_TYPE_DIVIDE,
    TOKEN_TYPE_MULTIPLIE,
    TOKEN_TYPE_MODULO,
    TOKEN_TYPE_POWER,
    TOKEN_TYPE_NEGITIVE,
    TOKEN_TYPE_EQUAL,
    TOKEN_TYPE_CHAR,
    TOKEN_TYPE_POINT,
    TOKEN_TYPE_WHITESPACE,
} token_type_t;

extern const char TOKEN_COMMENT_CHAR;

typedef struct {
    token_type_t token_type;
    void* data;
} token_t;

token_t* token_base_init(token_type_t type);
token_t* token_char_init(char data);
token_type_t token_type(const token_t* token);
string_t* token_string(const token_t* token);
void* token_data(const token_t* token);
void token_destory(token_t* token);

#endif
