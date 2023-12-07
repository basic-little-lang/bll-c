#include <stdio.h>
#include "include/string.h"
#include "include/files.h"

string_t* files_read_file_to_string(const string_t* file_name) {

    char c_filename_str[string_size(file_name) + 1];
    for (int i = 0; i < string_size(file_name); i++) {
        c_filename_str[i] = *string_get(file_name, i);
    }
    c_filename_str[string_size(file_name)] = '\0';

    FILE* file = fopen(c_filename_str, "r");
    if (file == NULL) return NULL;

    string_t* contents = string_init();

    char c;
    while ((c = fgetc(file)) != EOF) {
        string_add(contents, c);
    }

    fclose(file);

    string_add(contents, '\n');

    return contents;
}
