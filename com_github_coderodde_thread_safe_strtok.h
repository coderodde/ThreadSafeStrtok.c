#ifndef COM_GITHUB_CODERODDE_THREAD_SAFE_STRTOK_H
#define COM_GITHUB_CODERODDE_THREAD_SAFE_STRTOK_H

typedef struct string_token {
    const char* token;
    struct string_token* next_string_token;
} string_token;

string_token* string_tokenize(const char* const text, 
                              const char* const delimiters);

#endif