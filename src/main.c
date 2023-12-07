#include <stdio.h>
#include <string.h>
#include "include/color.h"
#include "include/vector.h"
#include "include/string.h"
#include "include/args.h"

int main(int argc, char const *argv[]) {

    int exit_code = 0;
    
    vector_t* args_vec = vector_init();

    for (int i = 0; i < argc; i++) {
        vector_add(args_vec, string_from((int) strlen(argv[i]), argv[i]));
    }

    args_t* args = args_build(args_vec);
    if (args->file_name == NULL) {
        string_t* error_str = string_from(5, "error");
        string_t* error_color_str = color_format_color(error_str, TEXT_COLOR_FOREGROUND_LIGHT_RED);
        string_t* error_color_bold_str = color_format_color(error_color_str, TEXT_COLOR_BOLD);

        string_print(error_color_bold_str);
        printf(": Cannot parse args\n");

        string_destory(error_str);
        string_destory(error_color_str);
        string_destory(error_color_bold_str);

        string_t* usage_str = string_from(5, "usage");
        string_t* usage_bold_str = color_format_color(usage_str, TEXT_COLOR_BOLD);

        string_print(usage_bold_str);
        printf(": <filename>\n");

        string_destory(usage_str);
        string_destory(usage_bold_str);

        exit_code = -1;
        goto exit_args;
    }

    exit_args:
        
        args_destroy(args);
        for (int i = 0; i < vector_size(args_vec); i++) {
            string_destory(vector_get(args_vec, i));
        }
        vector_destroy(args_vec);

        return exit_code;
}
