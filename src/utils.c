#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "meta_data.h"
#include "utils.h"

int NO_COLOR = 0;

char *read_input() {
    size_t buff_sz = 100;

    char *input = malloc(buff_sz);
    if (input == NULL) {
        perror("Unable to allocate buffer");
        exit(EXIT_FAILURE);
    }

    size_t position = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        input[position++] = c;

        if (position >= buff_sz) {
            buff_sz *= 2;
            char *orig_input = input;
            input = realloc(input, buff_sz);

            if (input == NULL) {
                perror("Unable to reallocate buffer");
                free(orig_input);
                exit(EXIT_FAILURE);
            }
        }
    }

    input[position] = '\0';

    return input;
}

int color_print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    if (NO_COLOR) {
        const char *src = buffer;
        char *dst = buffer;

        while (*src) {
            if (*src == '\033' && *(src + 1) == '[') {
                while (*src && *src != 'm') {
                    src++;
                }
                if (*src == 'm') {
                    src++;
                }
            } else {
                *dst++ = *src++;
            }
        }
        *dst = '\0';
    }

    const int return_value = printf("%s", buffer);

    va_end(args);
    return return_value;
}

void display_welcome_message(void) {
    const time_t seed = /* time(NULL) */ 1730619132;
    srand(seed);
    const int rand_num = rand() % welcome_messages_num;

    color_print(welcome_messages[rand_num], product_name);
}

const char *find_changelog(const char *version) {
    for (size_t i = 0; changelogs[i] != NULL; i++) {
        const char *changelog = changelogs[i];

        if (changelog[0] == 'v') {
            for (size_t j = 1; j <= strlen(version); j++) {
                if (changelog[j] != version[j - 1]) {
                    break;
                }

                if (j == strlen(version)) {
                    return changelog;
                }
            }
        }
    }

    return NULL;
}
