#include <stdio.h>
#include "include/string.h"
#include "include/files.h"

string_t* files_read_file_to_string(string_t* file_name) {

    FILE* file = fopen(*string_data(file_name), "r");
    if (file == NULL) return NULL;

    string_t* contents = string_init();

    char c;
    while ((c = fgetc(file)) != EOF) {
        string_add(contents, c);
    }

    fclose(file);

    return contents;
}
