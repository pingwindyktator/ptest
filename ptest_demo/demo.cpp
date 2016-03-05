#include <iostream>
#include "../ptest.hpp"

using namespace std;

int overload (int) { return 42; }

int overload (char) { return 42; }

int give (int val) { return val; }

int give_const (const int val) { return val; }

int give_const_ref (const int &val) { return val; }

int give_rref (int &&val) { return val; }

int give_ptr (int *ptr) { return *ptr; }

char give_char (char c) { return c; }

const char *give_string (const char *str) { return str; }

int give_mult_param (char, const std::string &, int, double, const char*) { return 42; }

int get_string_and_cstring (const char *, const std::string &) { return 42; }

int get_timeout () { std::this_thread::sleep_for(4s); return 42; }

int get_std_exception () { throw std::runtime_error("hello"); }

int get_dumb_exception () { throw "I'm dumb!"; }

// -------------------------------------------------------

struct some_struct { };

std::ostream &operator<< (std::ostream &os, some_struct) {
	return os << "some_struct";
}

ptest::config_t get_def_config () { // config customization demo
	// ptest::general_suite.config is config for non-suited tests
	// each suite have its own config
	ptest::config_t conf;

	conf.print_exceptions = true;
	conf.print_passed_tests = true;
	conf.print_thread_id = true;
	conf.print_names_of_arguments = true;

	conf.terminate_after_first_failure = false;
	conf.terminate_after_first_exception = false;
	conf.terminate_after_first_timeout = false;

	conf.set_def_outputs();
	conf.set_all_output_to(std::cout);
	conf.outputs.at(ptest::output_type::timeout) = std::cerr;
//conf.outputs.at(ptest::output_type::exception) = some_file;

	conf.set_max_time(10ms);

	return conf;
}

void exception_demo () {
	ptest::general_suite.config.print_exceptions = true;
	run_equal_test(get_std_exception, 42); // running get_std_exception() with expected result 42
	run_equal_test(get_dumb_exception, 44); // running get_dumb_exception() with expected result 44
}

void timeout_demo () {
	new_test_suite(timeout_demo_suite);
	timeout_demo_suite.config.set_max_time(10ms); // setting 10ms as timeout for suite timeout_demo_suite
	timeout_demo_suite.config.print_passed_tests = true;
	// TODO there is no config.print_timeout

	timeout_demo_suite.run_equal_test(get_timeout, 42); // running get_timeout() with expecting result 42 and timeout set to 10ms
}

void main_demo () {
	ptest::general_suite.config = get_def_config(); // the way you can set up general config
//ptest::general_suite.config.print_exceptions = true;

	run_equal_test(give, 4, 4); // running give(4) with expected result 4
	run_unequal_test(give, 4, 5); // running give(4) with expected result other than 5

	run_equal_test(give, 4, 6); // some fail

	int a = 4;
	run_equal_test(give_const, a, 4);
	run_equal_test(give_const_ref, int(4), 4);
	run_equal_test(give_ptr, &a, a);
	run_equal_test(give_rref, std::move(a), 4);

	run_equal_test((int (*)(int))overload, 4, 42); // running overloaded func overload(4)
	run_equal_test((int (*)(char))overload, 'a', 42); // second overload

	run_equal_test(give_char, 'c', 'c');
	char c = 'c';
	run_equal_test(give_char, c, 'c');

	const std::string str = "str";
	run_equal_test(give_string, "str", str);

	run_equal_test(get_string_and_cstring, "some cstring", str, 42);

	const char *str2 = "str2";
	run_equal_test(give_mult_param, '\\', "some string", 42, 42.42, str2, 44);

	run_equal_test([=](int, char = 'c') { return 42; }, 2, 44);

	run_equal_test([](auto) { return 'c'; }, some_struct{}, 'c');
}

void suite_demo () {
	new_test_suite(some_suite); // variable name will be "some_suite" and suite name will be the same
	new_test_suite(other_suite, "I'm other suite"); // // variable name will be "other_suite" and suite name will be "I'm other suite"
	some_suite.config.print_passed_tests = true;
	other_suite.config.print_passed_tests = true;

	int a = 4;
	some_suite.run_equal_test(give, a, 4); // running give(a) in suite some_suite with expected result 4
	// all operations are the same as in non-suited tests

	some_suite.print_suite_result(); // printing result of all tests in suite
}

void thread_demo () {
	new_static_test_suite(thread_suite); // in case of using multithread tests, I suggest to declare suite as static
																			 // to avoid creation suite for every thread

	auto func = [&] () {
		for (int i = -10; i < 10; ++i)
			thread_suite.run_equal_test(give, i, i);
	};

	std::thread th1(func);
	std::thread th2(func);
	th1.join();
	th2.join();

	thread_suite.print_suite_result();
}

void assert_demo () {
	run_assert(4 == 4);
	run_assert(5 == 2, "uhuhu, problem here");

	new_test_suite(assert_demo_suite);
	assert_demo_suite.config.print_passed_tests = true;
	assert_demo_suite.run_assert(5 == 2, "maybe this time?");
	assert_demo_suite.run_assert(give(4) == 4);
}

void call_test_demo () {
	auto some_func = [] () { return "something"; };
	auto some_other_func = [&] (int, int) {
		new_static_test_suite(some_suite);
			some_suite.run_unequal_test(some_func, "something other");
	};

	ptest::call_test(2, some_other_func, 3, 3); // calling some_other_func(3,3) at 2 threads
}

int main () {
	timeout_demo();
	exception_demo();
	main_demo();
	suite_demo();
	thread_demo();
	assert_demo();
	call_test_demo();

	print_final_result();
	return 0;
}
