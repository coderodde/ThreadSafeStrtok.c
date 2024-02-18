#ifndef COM_GITHUB_CODERODDE_MY_ASSERT_H
#define COM_GITHUB_CODERODDE_MY_ASSERT_H

#include <stdbool.h>
#include <stdio.h>

extern size_t passes;
extern size_t failed;

void print_test_statistics();

#define ASSERT_IMPL(COND, LINE) assert_impl(COND, #COND, __LINE__);
#define ASSERT(COND) ASSERT_IMPL(COND, __LINE__)

#endif