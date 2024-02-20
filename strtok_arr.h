#ifndef COM_GITHUB_CODERODDE_THREAD_SAFE_STRTOK_H
#define COM_GITHUB_CODERODDE_THREAD_SAFE_STRTOK_H

#include <stddef.h>

char** strtok_arr(const char* const text,
                  const char* const delimiters);

size_t strtok_arr_len(char** tokens);
void strtok_arr_free(char** tokens);

#endif