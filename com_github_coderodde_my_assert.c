#include "com_github_coderodde_my_assert.h"
#include <stdlib.h>

static size_t passes = 0;
static size_t failed = 0;

void assert_impl(bool passed,
                        const char* condition_text,
                        size_t line_number) {
    if (passed) {
        passes++;
    } else {
        failed++;

        printf("Failed condition \"%s\" at line %zu.\n",
            condition_text,
            line_number);
    }
}

void print_test_statistics() {
    printf("Passes: %zu, failures: %zu, total assertions: %zu.\n",
           passes,
           failed,
           passes + failed);
}