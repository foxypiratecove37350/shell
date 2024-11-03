#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_args(const char *input, char ***parsed_args) {
    char *input_cpy = malloc(strlen(input) + 1);
    strcpy(input_cpy, input);

    char *newline = strchr(input_cpy, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    strcat(input_cpy, " ");

    int i = 0;
    char quoted = '\0';
    int arg_count = 2;
    *parsed_args = malloc(sizeof(char *) * arg_count);
    (*parsed_args)[i] = malloc(sizeof(char) * 10);
    (*parsed_args)[i][0] = '\0';

    int arg_idx = 0;

    for (int j = 0; input_cpy[j] != '\0'; j++) {
        if (input_cpy[j] == ' ' && input_cpy[j - 1] != ' ' && quoted == '\0') {
            (*parsed_args)[i][arg_idx] = '\0';
            i++;
            if (i >= arg_count) {
                arg_count *= 2;
                *parsed_args = realloc(*parsed_args, sizeof(char *) * arg_count);
            }
            (*parsed_args)[i] = malloc(sizeof(char) * 10);
            (*parsed_args)[i][0] = '\0';
            arg_idx = 0;
        } else if (input_cpy[j] == '"' || input_cpy[j] == '\'') {
            if (quoted == input_cpy[j] && input_cpy[j - 1] != '\\') {
                quoted = '\0';
            } else if (quoted == '\0') {
                quoted = input_cpy[j];
            } else {
                if (arg_idx >= 10) {
                    (*parsed_args)[i] = realloc((*parsed_args)[i], strlen((*parsed_args)[i]) * 2 + 1);
                }
                (*parsed_args)[i][arg_idx] = input_cpy[j];
                arg_idx++;
            }
        } else if (
            (input_cpy[j + 1] == '\\' ||
             input_cpy[j + 1] == 'a' ||
             input_cpy[j + 1] == 'b' ||
             input_cpy[j + 1] == 'f' ||
             input_cpy[j + 1] == 'n' ||
             input_cpy[j + 1] == 'r' ||
             input_cpy[j + 1] == 't' ||
             input_cpy[j + 1] == 'v' ||
             input_cpy[j + 1] == 'e' ||
             input_cpy[j + 1] == '?' ||
             input_cpy[j + 1] == '0') &&
            input_cpy[j] == '\\'
        ) {
            if (arg_idx >= 10) {
                (*parsed_args)[i] = realloc((*parsed_args)[i], strlen((*parsed_args)[i]) * 2 + 1);
            }

            char chr;
            switch (input_cpy[j + 1]) {
                case '\\':
                    chr = '\\';
                    break;
                case 'a':
                    chr = '\a';
                    break;
                case 'b':
                    chr = '\b';
                    break;
                case 'f':
                    chr = '\f';
                    break;
                case 'n':
                    chr = '\n';
                    break;
                case 'r':
                    chr = '\r';
                    break;
                case 't':
                    chr = '\t';
                    break;
                case 'v':
                    chr = '\v';
                case 'e':
                    chr = '\e';
                    break;
                case '?':
                    chr = '\?';
                    break;
                case '0':
                    chr = '\0';
                    break;
            }

            (*parsed_args)[i][arg_idx] = chr;
            arg_idx++;
            j++;
        } else {
            if (arg_idx >= 10) {
                (*parsed_args)[i] = realloc((*parsed_args)[i], strlen((*parsed_args)[i]) * 2 + 1);
            }
            (*parsed_args)[i][arg_idx] = input_cpy[j];
            arg_idx++;
        }
    }

    (*parsed_args)[i][arg_idx] = '\0';
    (*parsed_args)[i + 1] = NULL;

    free(input_cpy);

    if (quoted != '\0') {
        fprintf(stderr, "Error: Never closed quotes in the command\n");
        *parsed_args = ((void*)-1);
    }

    return i;
}
