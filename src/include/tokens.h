
#ifndef _TOKENS_H_
#define _TOKENS_H_

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

#endif
