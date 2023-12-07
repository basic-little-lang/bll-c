#include <stdio.h>
#include <string.h>
#include "include/vector.h"
#include "include/string.h"

int main(int argc, char const *argv[]) {
    
    vector_t* args = vector_init();

    for (int i = 0; i < argc; i++) {
        vector_add(args, string_from((int) strlen(argv[i]), argv[i]));
    }


    for (int i = 0; i < vector_size(args); i++) {
        string_destory(vector_get(args, i));
    }
    vector_destroy(args);

    return 0;
}
