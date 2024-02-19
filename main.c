#include "assertlib.h"
#include "com_github_coderodde_thread_safe_strtok.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void test_hello_world_1() {
    const char* text = "ab cd,";
    const char* delimiters = " ,\n";
    char** arr = compute_string_tokens(text, delimiters);
    const size_t number_of_string_tokens = compute_number_of_string_tokens(arr);

    ASSERT(number_of_string_tokens == 3);

    ASSERT(strcmp(arr[0], "ab") == 0);
    ASSERT(strcmp(arr[1], "cd") == 0);
    ASSERT(strcmp(arr[2], "") == 0);
}

static void test_hello_world_2() {
    const char* const text = ",";
    const char* const delimiters = " , ";
    char** arr = compute_string_tokens(text, delimiters);
    const size_t number_of_string_tokens = compute_number_of_string_tokens(arr);

    ASSERT(number_of_string_tokens == 2);

    ASSERT(strcmp(arr[0], "") == 0);
    ASSERT(strcmp(arr[1], "") == 0);
}

static void test_hello_world_3() {
    const char* const text = ", ";
    const char* const delimiters = " , ";
    char** arr = compute_string_tokens(text, delimiters);
    const size_t number_of_string_tokens = compute_number_of_string_tokens(arr);

    ASSERT(number_of_string_tokens == 3);

    ASSERT(strcmp(arr[0], "") == 0);
    ASSERT(strcmp(arr[1], "") == 0);
    ASSERT(strcmp(arr[2], "") == 0);
}

int main() {
    test_hello_world_1();
    test_hello_world_2();
    test_hello_world_3();
    
    print_test_statistics();

    return 0;
}