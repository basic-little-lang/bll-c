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
