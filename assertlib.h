#ifndef COM_GITHUB_CODERODDE_ASSERTLIB_H
#define COM_GITHUB_CODERODDE_ASSERTLIB_H

void print_test_statistics();
int get_exit_status();

#define ASSERT_IMPL(COND, FILE, LINE) assert_impl(COND, #COND, FILE, LINE);
#define ASSERT(COND) ASSERT_IMPL(COND, __FILE__, __LINE__)

#endif