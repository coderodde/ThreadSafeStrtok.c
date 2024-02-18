#include "com_github_coderodde_thread_safe_strtok.h"
#include "com_github_coderodde_my_assert.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const size_t count_string_token_list(string_token* head) {
    size_t number_of_tokens = 0;

    while (head != NULL) {
        number_of_tokens++;
        head = head->next_string_token;
    }

    return number_of_tokens;
}

static char** convert_to_token_array(string_token* head, 
                                           size_t number_of_tokens) {
    char** arr = malloc(number_of_tokens);
    string_token* st = head;

    for (size_t i = 0; i < number_of_tokens; i++) {

        size_t token_length = strlen(st->token) + 1;
        arr[i] = malloc(sizeof(char) * token_length);

        strncpy_s(arr[i], 
                  token_length,
                  st->token,
                  token_length);

        st = st->next_string_token;
    }

    return arr;
}

void test_hello_world_1() {
    const char* text = "ab cd";
    const char* delimiters = " \n";
    const string_token* string_token_list_head =
        string_tokenize(text, delimiters);

    const size_t number_of_string_tokens =
        count_string_token_list(string_token_list_head);

    ASSERT(number_of_string_tokens == 2);

    const char* const token1 = string_token_list_head->token;
    const char* const token2 =
        string_token_list_head->next_string_token->token;

    ASSERT(strcmp(token1, "ab") == 0);
    ASSERT(strcmp(token2, "cd") == 0);
}

void test_hello_world_2() {
    const char* const text = ",";
    const char* const delimiters = " , ";

    const string_token* string_token_list_head =
        string_tokenize(text, delimiters);

    const size_t number_of_string_tokens =
        count_string_token_list(string_token_list_head);

    ASSERT(number_of_string_tokens == 2);

    char** arr = convert_to_token_array(string_token_list_head,
        number_of_string_tokens);

    ASSERT(strcmp(arr[0], "") == 0);
    ASSERT(strcmp(arr[1], "") == 0);
}

void test_hello_world_3() {
    const char* const text = ", ";
    const char* const delimiters = " , ";

    const string_token* string_token_list_head =
        string_tokenize(text, delimiters);

    const size_t number_of_string_tokens =
        count_string_token_list(string_token_list_head);

    ASSERT(number_of_string_tokens == 3);

    char** arr = convert_to_token_array(string_token_list_head,
        number_of_string_tokens);

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