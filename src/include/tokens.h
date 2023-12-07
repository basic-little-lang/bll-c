
#ifndef _TOKENS_H_
#define _TOKENS_H_

#include "string.h"

typedef enum {
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLIE,
    MODULO,
    POWER,
    NEGITIVE,
    EQUAL,
    CHAR,
    POINT,
    WHITESPACE,
} token_type_t;

extern const char TOKEN_COMMENT_CHAR;

typedef struct {
    token_type_t token_type;
    void* data;
} token_t;

token_t* token_base_init(token_type_t type);
token_type_t token_type(const token_t* token);
string_t* token_string(const token_t* token);
void* token_data(const token_t* token);
void token_destory(const token_t* token);

#endif
