#ifndef COM_GITHUB_CODERODDE_THREAD_SAFE_STRTOK_H
#define COM_GITHUB_CODERODDE_THREAD_SAFE_STRTOK_H

#include <stddef.h>

char** compute_string_tokens(const char* const text,
                             const char* const delimiters);

size_t compute_number_of_string_tokens(char** tokens);

#endif