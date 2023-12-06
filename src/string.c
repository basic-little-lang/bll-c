#include <stdio.h>
#include <stdlib.h>
#include "include/vector.h"
#include "include/string.h"

string_t* string_from(int len, const char str[]) {
    string_t* string = string_init();

    for (int i = 0; i < len; i++) {
        string_add(string, str[i]);
    }

    return string;
}

string_t* string_init() {
    return vector_init();
}

int string_size(const string_t* str) {
    return vector_size(str);
}

int string_capacity(const string_t* str) {
    return vector_capacity(str);
}

char** string_data(const string_t* str) {
    return (char**) vector_data(str);
}

char* string_get(const string_t* str, int index) {
    return (char*) vector_get(str, index);
}

void string_add(string_t *restrict str, char chr) {
    char* heap_char = malloc(sizeof(char));
    *heap_char = chr;
    vector_add(str, heap_char);
}

void string_remove(string_t* str, int index) {
    free(vector_remove(str, index));
}

void string_print(const string_t* str) {
    for (int i = 0; i < string_size(str); i++) {
        printf("%c", *string_get(str, i));
    }
}

void string_println(const string_t *str) {
    string_print(str);
    printf("\n");
}

void string_destory(string_t* str) {
    for (int i = 0; i < string_size(str); i++) {
        free(string_get(str, i));
    }
    vector_destroy(str);
}
