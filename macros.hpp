#ifndef PLIB_PTEST_MACROS_HPP
#define PLIB_PTEST_MACROS_HPP

#include "suite_test_macro.hpp"
#include "test_macro.hpp"
#include "assert_macro.hpp"
#include "new_test_suite_macro.hpp"

#define run_equal_test(...) run_test(__VA_ARGS__, pequal)
#define run_unequal_test(...) (run_test(__VA_ARGS__, punequal))
#define run_suite_equal_test(...) (run_suite_test(__VA_ARGS__, pequal))
#define run_suite_unequal_test(...) (run_suite_test(__VA_ARGS__, punequal))

#endif //PLIB_PTEST_MACROS_HPP
