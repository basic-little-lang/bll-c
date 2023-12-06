#include <stdio.h>
#include <stdlib.h>
#include "include/vector.h"

int main() {
    
    vector_t* vec = vector_init();

    for (int i = 0; i < 12; i++) {
        int *num = malloc(sizeof(int));
        *num = i + 1;
        vector_add(vec, num);
    }

    free(vector_remove(vec, 6));
    printf("%d and %d\n", vector_size(vec), vector_capacity(vec));

    for (int i = 0; i < vector_size(vec); i++) {
        printf("%d\n", *((int*) vector_get(vec, i)));
        free(vector_get(vec, i));
    }


    vector_destroy(vec);

}
