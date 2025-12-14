#include "input.h"

int get_int_input(const char* prompt) {
    char buffer[100];
    int value;

    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Input error.\n");
            continue;
        }

        if (sscanf(buffer, "%d", &value) == 1) {
            return value;
        }

        printf("Invalid input! Please enter a number.\n");
    }
}

void get_string_input(const char* prompt, char* buffer, size_t buffer_size) {
    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, buffer_size, stdin) == NULL) {
            printf("Input error occurred.\n");
            continue;
        }

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (strlen(buffer) > 0) {
            break;
        }

        printf("Input cannot be empty.\n");
    }
}