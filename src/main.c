#include <stdio.h>
#include <string.h>
#include "include/color.h"
#include "include/tokens.h"
#include "include/vector.h"
#include "include/string.h"
#include "include/args.h"
#include "include/files.h"

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

    string_t* contents = files_read_file_to_string(args->file_name);
    if (contents == NULL) {
        string_t* error_str = string_from(5, "error");
        string_t* error_color_str = color_format_color(error_str, TEXT_COLOR_FOREGROUND_LIGHT_RED);
        string_t* error_color_bold_str = color_format_color(error_color_str, TEXT_COLOR_BOLD);

        string_print(error_color_bold_str);
        printf(": Cannot open file: ");

        string_println(args->file_name);

        string_destory(error_str);
        string_destory(error_color_str);
        string_destory(error_color_bold_str);
        exit_code = -1;
        goto exit_args;
    }

    vector_t* direct_tokens = token_tokenize_string(contents);
    if (direct_tokens == NULL) {
        string_t* error_str = string_from(5, "error");
        string_t* error_color_str = color_format_color(error_str, TEXT_COLOR_FOREGROUND_LIGHT_RED);
        string_t* error_color_bold_str = color_format_color(error_color_str, TEXT_COLOR_BOLD);

        string_print(error_color_bold_str);
        printf(": Cannot parse file into direct tokens\n");

        string_destory(error_str);
        string_destory(error_color_str);
        string_destory(error_color_bold_str);
        exit_code = -1;
        goto exit_contents;
    }



    for (int i = 0; i < vector_size(direct_tokens); i++) {
        string_t* str = token_string(vector_get(direct_tokens, i));
        string_println(str);
        string_destory(str);
    }



    for (int i = 0; i < vector_size(direct_tokens); i++) {
        token_destory(vector_get(direct_tokens, i));
    }
    vector_destroy(direct_tokens);

    exit_contents:

        string_destory(contents);

    exit_args:
        
        args_destroy(args);
        for (int i = 0; i < vector_size(args_vec); i++) {
            string_destory(vector_get(args_vec, i));
        }
        vector_destroy(args_vec);

        return exit_code;
}
