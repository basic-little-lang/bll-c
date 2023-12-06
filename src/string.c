#include "include/vector.h"
#include "include/string.h"

string_t* string_init() {
    return vector_init();
}

void string_destory(string_t* str) {
    vector_destroy(str);
}
