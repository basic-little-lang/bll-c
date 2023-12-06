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
