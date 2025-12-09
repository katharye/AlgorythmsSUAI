#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "lab1.h"

int comment_flag = 0;
const char *datatypes[] = {"void",  "char",           "unsigned char", "signed char",
                           "short", "unsigned short", "int",           "unsigned int",
                           "long",  "unsigned long",  "long long",     "unsigned long long",
                           "float", "double",         "long double",   "const"};
const int datalen = 16;

static int is_function_header(const char *line) {
    if (strstr(line, "/*")) comment_flag = 1;
    if (strstr(line, "*/")) comment_flag = 0;
    if (strstr(line, "//") || comment_flag) return 0;

    if (strchr(line, ';')) return 0;
    if (strchr(line, '\"') || strchr(line, '\'')) return 0;

    const char *bracket = strchr(line, '(');
    if (!bracket) return 0;

    const char *banlist[] = {"if (", "switch (", "while (", "#define", "for ("};
    for (int i = 0; i < 5; i++)
        if (strstr(line, banlist[i])) return 0;

    int datatype_flag = 0;
    for (int i = 0; i < datalen; i++) {
        if (strstr(line, datatypes[i])) datatype_flag = 1;
    }
    if (!datatype_flag) return 0;

    const char *before_bracket = bracket - 1;
    while (before_bracket > line && isspace(*before_bracket)) {
        before_bracket--;
    }
    if (before_bracket <= line || !(isalnum(*before_bracket) || *before_bracket == '_')) return 0;

    return 1;
}

static void print_header(char *line) {
    for (char *p = line; *p != '\0'; p++) {
        if (*p != '{') {
            printf("%s%c%s", green, *p, reset);
        } else {
            printf("%s%c", reset, *p);
        }
    }
    printf("%s", reset);
}


int lab1(char* filename) { 
    char buffer[max_code_length];
    FILE *file = fopen(filename, "rt");

    if (!file) {
        printf("n/a\n");
        return 1;
    }
    while (fgets(buffer, max_code_length, file)) {
        if (is_function_header(buffer)) {
            print_header(buffer);
        } else {
            printf("%s", buffer);
        }
    }

    fclose(file);
    return 0;
}

