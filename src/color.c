#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "include/string.h"
#include "include/color.h"

void color_print_color(const string_t* string, text_color_t color) {
    string_t* str = color_format_color(string, color);

    string_print(str);

    string_destory(str);
}

void color_println_color(const string_t* string, text_color_t color) {
    string_t* str = color_format_color(string, color);

    string_println(str);

    string_destory(str);
}

string_t* color_format_color(const string_t* string, text_color_t color) {
    string_t* color_str = color_color_to_string(color);
    string_t* str = string_init();

    for (int i = 0; i < string_size(color_str); i++) {
        string_add(str, *string_get(color_str, i));
    }

    for (int i = 0; i < string_size(string); i++) {
        string_add(str, *string_get(string, i));
    }

    string_destory(color_str);

    string_t* reset_str = color_color_to_string(TEXT_COLOR_RESET);

    for (int i = 0; i < string_size(reset_str); i++) {
        string_add(str, *string_get(reset_str, i));
    }

    string_destory(reset_str);

    return str;
}

string_t* color_color_to_string(text_color_t color) {
    unsigned short code = color_code_for_color(color);
    bool is_foreground = color_is_foreground(color);

    string_t* string = string_init();
    char str[8];
    sprintf(str, "%d", code);
    string_t* color_code_str = string_from(strlen(str), str);

    string_add(string, '\033');
    string_add(string, '[');

    if (!is_foreground) {
        string_add(string, ';');
    }
    
    for (int i = 0; i < string_size(color_code_str); i++) {
        string_add(string, *string_get(color_code_str, i));
    }
    string_add(string, 'm');

    string_destory(color_code_str);
    return string;
}

bool color_is_foreground(text_color_t color) {
    unsigned short code = color_code_for_color(color);

    return (code >= 30 && code <= 97);
}

unsigned short color_code_for_color(text_color_t color) {

    switch (color) {
        case TEXT_COLOR_FOREGROUND_BLACK:
            return 30;
        case TEXT_COLOR_FOREGROUND_RED:
            return 31;
        case TEXT_COLOR_FOREGROUND_GREEN:
            return 32;
        case TEXT_COLOR_FOREGROUND_YELLOW:
            return 33;
        case TEXT_COLOR_FOREGROUND_BLUE:
            return 34;
        case TEXT_COLOR_FOREGROUND_MAGENTA:
            return 35;
        case TEXT_COLOR_FOREGROUND_CYAN:
            return 36;
        case TEXT_COLOR_FOREGROUND_WHITE:
            return 37;
        case TEXT_COLOR_FOREGROUND_LIGHT_BLACK:
            return 90;
        case TEXT_COLOR_FOREGROUND_LIGHT_RED:
            return 91;
        case TEXT_COLOR_FOREGROUND_LIGHT_GREEN:
            return 92;
        case TEXT_COLOR_FOREGROUND_LIGHT_YELLOW:
            return 93;
        case TEXT_COLOR_FOREGROUND_LIGHT_BLUE:
            return 94;
        case TEXT_COLOR_FOREGROUND_LIGHT_MAGENTA:
            return 95;
        case TEXT_COLOR_FOREGROUND_LIGHT_CYAN:
            return 96;
        case TEXT_COLOR_FOREGROUND_LIGHT_WHITE:
            return 97;

        case TEXT_COLOR_BACKGROUND_BLACK:
            return 40;
        case TEXT_COLOR_BACKGROUND_RED:
            return 41;
        case TEXT_COLOR_BACKGROUND_GREEN:
            return 42;
        case TEXT_COLOR_BACKGROUND_YELLOW:
            return 43;
        case TEXT_COLOR_BACKGROUND_BLUE:
            return 44;
        case TEXT_COLOR_BACKGROUND_MAGENTA:
            return 45;
        case TEXT_COLOR_BACKGROUND_CYAN:
            return 46;
        case TEXT_COLOR_BACKGROUND_WHITE:
            return 47;
        case TEXT_COLOR_BACKGROUND_LIGHT_BLACK:
            return 100;
        case TEXT_COLOR_BACKGROUND_LIGHT_RED:
            return 101;
        case TEXT_COLOR_BACKGROUND_LIGHT_GREEN:
            return 102;
        case TEXT_COLOR_BACKGROUND_LIGHT_YELLOW:
            return 103;
        case TEXT_COLOR_BACKGROUND_LIGHT_BLUE:
            return 104;
        case TEXT_COLOR_BACKGROUND_LIGHT_MAGENTA:
            return 105;
        case TEXT_COLOR_BACKGROUND_LIGHT_CYAN:
            return 106;
        case TEXT_COLOR_BACKGROUND_LIGHT_WHITE:
            return 107;

        
        case TEXT_COLOR_RESET:
            return 0;
        case TEXT_COLOR_BOLD:
            return 1;
        case TEXT_COLOR_ITALIC:
            return 3;
        case TEXT_COLOR_UNDERLINE:
            return 4;
    }

}
