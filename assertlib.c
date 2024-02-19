#include "assertlib.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define COMPLETION_BAR_LENGTH 80

static size_t passes = 0;
static size_t failed = 0;

void assert_impl(bool passed,
    const char* condition_text,
    const char* file_name,
    size_t line_number) {
    if (passed) {
        passes++;
    }
    else {
        failed++;

        fprintf(stderr,
            "Failed condition \"%s\" in file \"%s\" at line %zu.\n",
            condition_text,
            file_name,
            line_number);
    }
}

int get_exit_status() {
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

static void print_bar(size_t bar_length) {
    size_t total_assertions = passes + failed;

    char* bar = calloc(bar_length + 16, sizeof(char));

    if (bar == NULL) {
        return;
    }

    bar[0] = '[';
    bar[bar_length + 1] = ']';

    float ratio = (float)(passes) / (float)(total_assertions);

    size_t hash_symbols = (size_t)(bar_length * ratio);

    for (size_t i = 0; i < hash_symbols; i++) {
        bar[i + 1] = '#';
    }

    for (size_t i = 0; i < bar_length - hash_symbols; i++) {
        bar[i + 1 + hash_symbols] = '.';
    }

    printf("%s: %.2f%%.\n", bar, 100.0f * ratio);
    free(bar);
}

void print_test_statistics() {
    printf("Passes: %zu, failures: %zu, total assertions: %zu.\n",
        passes,
        failed,
        passes + failed);

    print_bar(COMPLETION_BAR_LENGTH);
}