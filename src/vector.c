#include <stdlib.h>
#include "include/vector.h"

vector_t* vector_init() {
    vector_t* vec = malloc(sizeof(vector_t));
    vec->capacity = VECTOR_STARTING_CAPACITY;
    vec->size = 0;
    
    vec->data = malloc(sizeof(void*) * vec->capacity);

    return vec;
}

int vector_size(const vector_t* vec) {
    return vec->size;
}

int vector_capacity(const vector_t* vec) {
    return vec->capacity;
}

void** vector_data(const vector_t* vec) {
    return vec->data;
}

void* vector_get(const vector_t* vec, int index) {
    if (index < 0 || index >= vector_size(vec)) return NULL;

    return vec->data[index];
}

void vector_add(vector_t *restrict vec, void *restrict item) {
    if ((vector_size(vec) + 1) > vector_capacity(vec)) {

        vec->capacity = vec->capacity * 2;
        vec->data = realloc(vec->data, sizeof(void*) * vec->capacity);
    }

    vec->size += 1;

    vec->data[vec->size - 1] = item;

}

void* vector_remove(vector_t* vec, int index) {

    if (index < 0 || index >= vector_size(vec)) return NULL;

    void* return_val = vector_get(vec, index);

    for (int i = index; i < vector_size(vec) - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }

    vec->data[vector_size(vec) - 1] = NULL;
    vec->size = vec->size - 1;

    return return_val;
}

void vector_destroy(vector_t* vec) {

    free(vec->data);
    free(vec);

}
