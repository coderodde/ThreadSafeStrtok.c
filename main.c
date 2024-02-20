#include "assertlib.h"
#include "strtok_arr.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void test_hello_world_1() {
    const char* text = "ab cd,";
    const char* delimiters = " ,\n";
    char** arr = strtok_arr(text, delimiters);
    const size_t number_of_string_tokens = strtok_arr_len(arr);

    ASSERT(number_of_string_tokens == 3);

    ASSERT(strcmp(arr[0], "ab") == 0);
    ASSERT(strcmp(arr[1], "cd") == 0);
    ASSERT(strcmp(arr[2], "") == 0);

    strtok_arr_free(arr);
}

static void test_hello_world_2() {
    const char* const text = ",";
    const char* const delimiters = " , ";
    char** arr = strtok_arr(text, delimiters);
    const size_t number_of_string_tokens = strtok_arr_len(arr);

    ASSERT(number_of_string_tokens == 2);

    ASSERT(strcmp(arr[0], "") == 0);
    ASSERT(strcmp(arr[1], "") == 0);

    strtok_arr_free(arr);
}

static void test_hello_world_3() {
    const char* const text = ", ";
    const char* const delimiters = " , ";
    char** arr = strtok_arr(text, delimiters);
    const size_t number_of_string_tokens = strtok_arr_len(arr);

    ASSERT(number_of_string_tokens == 3);

    ASSERT(strcmp(arr[0], "") == 0);
    ASSERT(strcmp(arr[1], "") == 0);
    ASSERT(strcmp(arr[2], "") == 0);

    strtok_arr_free(arr);
}

int main() {
    test_hello_world_1();
    test_hello_world_2();
    test_hello_world_3();
    
    print_test_statistics();

    return 0;
}