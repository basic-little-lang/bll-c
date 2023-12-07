#include <stdlib.h>
#include "include/vector.h"
#include "include/string.h"
#include "include/args.h"

args_t* args_build(const vector_t* args) {

    args_t* new_args = malloc(sizeof(args_t));

    if (vector_size(args) < 2) {
        new_args->file_name = NULL;
        return new_args;
    }

    string_t* file_name = string_init();

    for (int i = 0; i < string_size(vector_get(args, 1)); i++) {
        string_add(file_name, *string_get(vector_get(args, 1), i));
    }

    new_args->file_name = file_name;
    return new_args;
}

void args_destroy(args_t* args) {
    if (args->file_name != NULL) {
        free(args->file_name);
    }
    free(args);
}
