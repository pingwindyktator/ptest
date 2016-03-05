#ifndef PLIB_PTEST_ASSERT_MACRO_HPP
#define PLIB_PTEST_ASSERT_MACRO_HPP
#include "general_macro_overloading.hpp"

#define ppassed true
#define pfailed false

#define run_assert(...) VFUNC(run_assert, __VA_ARGS__)

#define run_assert1(expr) p__start_assertion_(expr,#expr)

#define run_assert2(expr,msg) p__start_assertion_(expr,#expr,msg)


#endif //PLIB_PTEST_ASSERT_MACRO_HPP
