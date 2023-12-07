
#ifndef _ARGS_H_
#define _ARGS_H_

#include "vector.h"
#include "string.h"

typedef struct {
    string_t* file_name;
} args_t;

args_t* args_build(const vector_t* args);
void args_destroy(args_t* args);

#endif
