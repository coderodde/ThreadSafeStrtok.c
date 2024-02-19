#include "com_github_coderodde_thread_safe_strtok.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct string_token_t {
    const char* token;
    struct string_token_t* p_next_string_token;
} string_token_t;

/********************************************************************
* Returns 'true' iff 'ch' is mentioned in the delimiter characters. *
********************************************************************/
static bool character_belongs_to_delimiter_set(
                char ch,
                const char* const delimiters) {

    return strchr(delimiters, ch) != NULL;
}

/***************************************************************************
* Frees the chain of tokens starting from 'p_token'. This function assumes *
* that the input 'p_token' is the head token.                              *
***************************************************************************/
static void free_tokens(string_token_t* p_token) {
    while (p_token != NULL) {
        string_token_t* p_next_token = p_token->p_next_string_token;
        free(p_token->token);
        free(p_token);
        p_token = p_next_token;
    }
}

static string_token_t* string_token_alloc(const char* const token) {

    string_token_t* st = malloc(sizeof *st);

    if (st == NULL) {
        return NULL;
    }

    st->token = token;
    st->p_next_string_token = NULL;

    return st;
}

/************************************************
* Creates a copy of a token residing in 'text'. *
************************************************/
static const char* string_token_copy(const char* const text, 
                                     size_t token_offset,
                                     size_t token_length) {

    /* + 1 in order to malloc the space for zero-terminator: */
    char* token_text = malloc(token_length + 1);

    if (token_text == NULL) {
        return NULL;
    }

    /* Terminate the token: */
    token_text[token_length] = '\0';

    /* Copy text[token_offset], ..., text[token_offset + token_length - 1]: */
    strncpy(token_text, 
            &text[token_offset], 
            token_length);

    return token_text;
}

char** compute_string_tokens(const char* const text,
                             const char* const delimiters) {

    if (text == NULL || delimiters == NULL) {
        return NULL;
    }

    string_token_t* p_head_string_token = NULL;
    string_token_t* p_tail_string_token = NULL;

    size_t text_length = strlen(text);
    size_t previous_token_start_index = 0;
    size_t number_of_tokens = 0;

    for (size_t i = 0; i < text_length + 1; i++) {
        char ch = text[i];

        if (character_belongs_to_delimiter_set(ch, delimiters) || ch == '\0') {
            size_t token_length = i - previous_token_start_index;

            const char* token_text = 
                string_token_copy(text,
                                  previous_token_start_index, 
                                  token_length);

            if (token_text == NULL) {
                free_tokens(p_head_string_token);
                return NULL;
            }

            string_token_t* st = string_token_alloc(token_text);

            if (st == NULL) {
                free(token_text);
                free_tokens(p_head_string_token);
                return NULL;
            }

            if (p_head_string_token == NULL) {
                p_head_string_token = st;
                p_tail_string_token = st;
            } else {
                p_tail_string_token->p_next_string_token = st;
                p_tail_string_token = st;
            }

            previous_token_start_index = i + 1;
            number_of_tokens++;
        }
    }

    char** return_token_array = malloc((number_of_tokens + 1) * sizeof(char*));

    if (return_token_array == NULL) {
        free_tokens(p_head_string_token);
        return NULL;
    }

    return_token_array[number_of_tokens] = NULL;
    string_token_t* p_token = p_head_string_token;

    for (size_t i = 0; i < number_of_tokens; i++) {
        return_token_array[i] = p_token->token;
        p_token = p_token->p_next_string_token;
    }

    return return_token_array;
}

size_t compute_number_of_string_tokens(char** arr) {
    size_t number_of_tokens = 0;
    size_t i = 0;

    for (;; i++) {
        if (arr[i] == NULL) {
            return i;
        }
    }

    abort();
    return 0;
}
