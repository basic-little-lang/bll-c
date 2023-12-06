
#ifndef _VECTOR_H_
#define _VECTOR_H_

#define VECTOR_STARTING_CAPACITY 4;

typedef struct {
    int size;
    int capacity;
    void **data;
} vector_t;

vector_t* vector_init();
int vector_size(const vector_t* vec);
int vector_capacity(const vector_t* vec);
void** vector_data(const vector_t* vec);
void* vector_get(const vector_t* vec, int index);
void vector_add(const vector_t *restrict vec, void *restrict item);
void* vector_remove(const vector_t* vec, int index);
void vector_destroy(const vector_t* vec);

#endif
