#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "include/vector.h"
#include "include/string.h"
#include "include/parser.h"
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
    char* key = malloc(sizeof(char) * (string_size(key_str) + 1));
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
    for (int i = 0; i < vector_size(vars->keys); i++) {
        free(vector_get(vars->keys, i));
    }
    for (int i = 0; i < vector_size(vars->vals); i++) {
        free(vector_get(vars->vals, i));
    }
    vector_destroy(vars->keys);
    vector_destroy(vars->vals);
    free(vars);
}

bool execute_execute(const vector_t* tokens) {
    vars_t* vars = vars_init();
    double last_val = 0;

    for (int i = 0; i < vector_size(tokens); i++) {
        parser_token_t* token = vector_get(tokens, i);

        parser_token_t* last_token;
        parser_token_t* next_token;

        int last_index = i - 1;
        int next_index = i + 1;

        if (last_index < 0) {
            last_token = NULL;
        } else {
            last_token = vector_get(tokens, last_index);
        }

        if (!(next_index < vector_size(tokens))) {
            next_token = NULL;
        } else {
            next_token = vector_get(tokens, next_index);
        }

        switch (parser_token_type(token)) {
            case PARSER_TOKEN_TYPE_ADD:
                {
                    if (last_token == NULL || next_token == NULL) {
                        vars_destory(vars);
                        return false;
                    }

                    double last_v;
                    double next_v;

                    switch (parser_token_type(last_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            last_v = *((double*) parser_token_data(last_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(last_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                last_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    switch (parser_token_type(next_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            next_v = *((double*) parser_token_data(next_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(next_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                next_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    last_val = last_v + next_v;

                }
                break;
            case PARSER_TOKEN_TYPE_SUBTRACT:
                {
                    if (last_token == NULL || next_token == NULL) {
                        vars_destory(vars);
                        return false;
                    }

                    double last_v;
                    double next_v;

                    switch (parser_token_type(last_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            last_v = *((double*) parser_token_data(last_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(last_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                last_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    switch (parser_token_type(next_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            next_v = *((double*) parser_token_data(next_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(next_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                next_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    last_val = last_v - next_v;

                }
                break;
            case PARSER_TOKEN_TYPE_MULTIPLIE:
                {
                    if (last_token == NULL || next_token == NULL) {
                        vars_destory(vars);
                        return false;
                    }

                    double last_v;
                    double next_v;

                    switch (parser_token_type(last_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            last_v = *((double*) parser_token_data(last_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(last_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                last_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    switch (parser_token_type(next_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            next_v = *((double*) parser_token_data(next_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(next_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                next_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    last_val = last_v * next_v;

                }
                break;
            case PARSER_TOKEN_TYPE_DIVIDE:
                {
                    if (last_token == NULL || next_token == NULL) {
                        vars_destory(vars);
                        return false;
                    }

                    double last_v;
                    double next_v;

                    switch (parser_token_type(last_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            last_v = *((double*) parser_token_data(last_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(last_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                last_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    switch (parser_token_type(next_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            next_v = *((double*) parser_token_data(next_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(next_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                next_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    last_val = last_v / next_v;

                }
                break;
            case PARSER_TOKEN_TYPE_MODULO:
                {
                    if (last_token == NULL || next_token == NULL) {
                        vars_destory(vars);
                        return false;
                    }

                    double last_v;
                    double next_v;

                    switch (parser_token_type(last_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            last_v = *((double*) parser_token_data(last_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(last_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                last_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    switch (parser_token_type(next_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            next_v = *((double*) parser_token_data(next_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(next_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                next_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    last_val = (int) last_v % (int) next_v;

                }
                break;
            case PARSER_TOKEN_TYPE_POWER:
                {
                    if (last_token == NULL || next_token == NULL) {
                        vars_destory(vars);
                        return false;
                    }

                    double last_v;
                    double next_v;

                    switch (parser_token_type(last_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            last_v = *((double*) parser_token_data(last_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(last_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                last_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    switch (parser_token_type(next_token)) {
                        case PARSER_TOKEN_TYPE_NUMBER:
                            next_v = *((double*) parser_token_data(next_token));
                            break;
                        case PARSER_TOKEN_TYPE_VAR:
                            {
                                double val;
                                double* p = vars_get(vars, ((string_t*) parser_token_data(next_token)));
                                if (p != NULL) {
                                    val = *p;
                                } else {
                                    val = 0;
                                }
                                next_v = val;
                            }
                            break;
                        default:  
                            vars_destory(vars);
                            return false;
                    }

                    last_val = pow(last_v, next_v);

                }
                break;
            case PARSER_TOKEN_TYPE_EQUAL:
                {

                    if (last_token == NULL || next_token == NULL) {
                        vars_destory(vars);
                        return false;
                    }

                    switch (parser_token_type(next_token)) {
                        case PARSER_TOKEN_TYPE_VAR:
                            vars_update_or_insert(vars, parser_token_data(next_token), last_val);
                            break;
                        case PARSER_TOKEN_TYPE_NUMBER:
                            switch (parser_token_type(last_token)) {
                                case PARSER_TOKEN_TYPE_VAR:
                                    vars_update_or_insert(vars, parser_token_data(last_token), *((double*) parser_token_data(next_token)));
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            vars_destory(vars);
                            return false;
                    }

                }
                break;
            case PARSER_TOKEN_TYPE_PRINT:
                {
                    if (next_token == NULL) {
                        vars_destory(vars);
                        return false;
                    }


                    if (parser_token_type(next_token) == PARSER_TOKEN_TYPE_VAR) {
                        string_t* key = parser_token_data(next_token);
                        string_print(key);
                        double* p = vars_get(vars, key);
                        if (p == NULL) {
                            printf(" = %.16lf\n", 0.0);
                        } else {
                            printf(" = %.16lf\n", *p);
                        }
                    } else {
                        vars_destory(vars);
                        return false;
                    }

                }
                break;
            case PARSER_TOKEN_TYPE_COPY:
                {
                    if (next_token == NULL) {
                        vars_destory(vars);
                        return false;
                    }

                    int next_two_index = i + 2;

                    parser_token_t* next_two_token;

                    if (!(next_two_index < vector_size(tokens))) {
                        vars_destory(vars);
                        return false;
                    } else {
                        next_two_token = vector_get(tokens, next_two_index);
                    }

                    double val = 0;
                    double* p = vars_get(vars, parser_token_data(next_token));
                    if (p != NULL) val = *p;

                    vars_update_or_insert(vars, parser_token_data(next_two_token), val);

                }
                break;
            default:
                break;
        }

    }

    vars_destory(vars);
    return true;
}
