
#ifndef _STRING_H_
#define _STRING_H_

#include "vector.h"

typedef vector_t string_t;

string_t* string_from(int len, char str[]);
string_t* string_init();
int string_size(const string_t* str);
int string_capacity(const string_t* str);
char** string_data(const string_t* str);
char* string_get(const string_t* str, int index);
void string_add(string_t *restrict str, char chr);
char* string_remove(string_t* str, int index);
void string_destory(string_t* str);

#endif
