#include "com_github_coderodde_thread_safe_strtok.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

static bool character_belongs_to_delimiter_set(
                char ch,
                const char* const delimiters) {
    char* current_char_ptr = delimiters;

    while (current_char_ptr != NULL) {
        if (*current_char_ptr == '\0') {
            return false;
        }

        if (*current_char_ptr == ch) {
            return true;
        }

        current_char_ptr++;
    }

    return false;
}

static void string_token_init(string_token* st,
                              const char* const token,
                              const string_token* const next_string_token) {
    st->token = token;
    st->next_string_token = next_string_token;
}

static string_token* string_token_alloc(
            const char* const token,
            const string_token* const next_string_token) {

    string_token* st = malloc(sizeof(st));

    if (st == NULL) {
        return NULL;
    }

    string_token_init(st, token, next_string_token);

    return st;
}

static const char* string_token_copy(const char* const text, 
                                     size_t token_offset,
                                     size_t token_length) {

    /* + 1 in order to malloc the space for zero-terminator: */
    char* token_text = malloc(sizeof(char) * (token_length + 1));

    /* Terminate the token: */
    token_text[token_length] = '\0';

    /* Copy text[token_offset], ..., text[token_offset + token_length - 1]: */
    strncpy_s(token_text, 
              token_length + 1, 
              &text[token_offset], 
              token_length);

    return token_text;
}

string_token* string_tokenize(const char* const text,
                              const char* const delimiters) {
    if (text == NULL || delimiters == NULL) {
        return NULL;
    }

    string_token* head_string_token = NULL;
    string_token* tail_string_token = NULL;

    size_t text_length = strlen(text);
    size_t previous_token_start_index = 0;

    for (size_t i = 0; i < text_length + 1; i++) {
        char ch = text[i];

        if (character_belongs_to_delimiter_set(ch, delimiters) || ch == '\0') {
            size_t token_length = i - previous_token_start_index;

            const char* token_text = 
                string_token_copy(text,
                                  previous_token_start_index, 
                                  token_length);

            printf("%s\n", token_text);

            string_token* st = string_token_alloc(token_text, NULL);

            if (head_string_token == NULL) {
                head_string_token = st;
                tail_string_token = st;
            } else {
                tail_string_token->next_string_token = st;
                tail_string_token = st;
            }

            if (token_length == 0) {
                previous_token_start_index = i + 1;
            } else {
                previous_token_start_index = i + 1;
            }
        }
    }

    return head_string_token;
}