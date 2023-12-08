#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "include/vector.h"
#include "include/string.h"
#include "include/execute.h"

typedef struct {
    vector_t* keys;
    vector_t* vals;
} vars_t;

vars_t* vars_init() {
    vars_t* vars = malloc(sizeof(vars_t));

    vars->keys = vector_init();
    vars->vals = vector_init();

    return vars;
}

void vars_insert(vars_t* vars, const string_t* key_str, double val) {
    char key[string_size(key_str) + 1];
    for (int i = 0; i < string_size(key_str); i++) {
        key[i] = *string_get(key_str, i);
    }
    key[string_size(key_str)] = '\0';

    double* data = malloc(sizeof(double));
    *data = val;

    vector_add(vars->keys, key);
    vector_add(vars->vals, data);
}

double* vars_get(vars_t* vars, const string_t* key_str) {
    char key[string_size(key_str) + 1];
    for (int i = 0; i < string_size(key_str); i++) {
        key[i] = *string_get(key_str, i);
    }
    key[string_size(key_str)] = '\0';

    for (int i = 0; i < vector_size(vars->keys); i++) {
        if (strcmp(key, vector_get(vars->keys, i)) == 0) {
            return vector_get(vars->vals, i);
        }
    }

    return NULL;

}

void vars_update_or_insert(vars_t* vars, const string_t* key_str, double val) {
    double* pVal = vars_get(vars, key_str);
    if (pVal != NULL) {
        *pVal = val;
        return;
    }
    vars_insert(vars, key_str, val);
}

void vars_destory(vars_t* vars) {
    for (int i = 0; i < vector_size(vars->vals); i++) {
        free(vector_get(vars->vals, i));
    }
    vector_destroy(vars->keys);
    vector_destroy(vars->vals);
    free(vars);
}

bool execute_execute(const vector_t* tokens) {

}
