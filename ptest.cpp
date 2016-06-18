#include <string.h>
#include "ptest.hpp"
#include <algorithm>

namespace ptest {
		stats_t ptest_suite::general_stats;

		ptest_suite::ptest_suite (const std::string &suite_name,
						const config_t &local_config) : stats{}, config(local_config), suite_name(suite_name) { }

		// =========================================================================

		bool ptest_suite::p__start_assertion_ (bool expr, const std::string &name, const std::string &msg) {
			if (expr) {
				update_stats(function_status::passed);
				if (config.print_passed_tests) {
					print_assertion_preamble(output_type::passed, name);
					print_thread_safe(output_type::passed, "\n\tPASSED\n\n");
				}

			} else {
				update_stats(function_status::failed);
				print_assertion_preamble(output_type::failed, name);
				print_thread_safe(output_type::failed, "\n\tFAILED");
				if (!msg.empty())
					print_thread_safe(output_type::failed, ": ", msg);

				print_thread_safe(output_type::failed, "\n\n");
				if (config.terminate_after_first_failure)
					terminate_process();
			}

			return expr;
		}

		// =========================================================================

		void ptest_suite::terminate_process () {
			std::cout << "\nterminating... ";
			std::cout.flush();
			std::cerr.flush();
			exit(0);
		}

		void ptest_suite::update_stats (const ptest_suite::function_status &status,
						const std::chrono::microseconds &execution_time) const {

			switch (status) {
				case function_status::passed:
					++general_stats.passed;
					++stats.passed;
					general_stats.total_time.store(general_stats.total_time.load() + execution_time);
					stats.total_time.store(stats.total_time.load() + execution_time);
					break;
				case function_status::failed:
					++general_stats.failed;
					++stats.failed;
					general_stats.total_time.store(general_stats.total_time.load() + execution_time);
					stats.total_time.store(stats.total_time.load() + execution_time);
					break;
				case function_status::timeout:
					++general_stats.timeout;
					++stats.timeout;
					break;
				case function_status::exception:
					++general_stats.exceptions;
					++stats.exceptions;
			}
		}

		// =========================================================================

		void ptest_suite::print_suite_result () const { // TODO redundant code
			print_thread_safe(output_type::info, "----- TEST RESULT IN SUITE ", suite_name, ":\n");
			print_thread_safe(output_type::info, "tests passed:         ", stats.passed, '\n');
			print_thread_safe(output_type::info, "tests failed:         ", stats.failed, '\n');
			print_thread_safe(output_type::info, "timeout:              ", stats.timeout, '\n');
			print_thread_safe(output_type::info, "exceptions:           ", stats.exceptions, '\n');
			print_thread_safe(output_type::info, "total execution time: ", stats.total_time.load().count(), " microseconds\n\n");
		}

		void ptest_suite::print_general_result () const { // TODO redundant code
			print_thread_safe(output_type::info, "----- FINAL TEST RESULT:\n");
			print_thread_safe(output_type::info, "tests passed:         ", general_stats.passed, '\n');
			print_thread_safe(output_type::info, "tests failed:         ", general_stats.failed, '\n');
			print_thread_safe(output_type::info, "timeout:              ", general_stats.timeout, '\n');
			print_thread_safe(output_type::info, "exceptions:           ", general_stats.exceptions, '\n');
			print_thread_safe(output_type::info, "total execution time: ", general_stats.total_time.load().count(), " microseconds\n\n");
		}

		void ptest_suite::print_value (const output_type &ot, const std::string &value) const {
			print_thread_safe(ot, "\"", value, "\"");
		}

		void ptest_suite::print_value (const output_type &ot, const char *value) const {
			print_thread_safe(ot, "\"", value, "\"");
		}

		void ptest_suite::print_value (const output_type &ot, const char value) const {
			print_thread_safe(ot, "\'", value, "\'");
		}

		void ptest_suite::print_args (const output_type &, const std::vector<std::string> &, size_t) const { }

		void ptest_suite::print_name_and_value (const output_type &ot,
						const std::string &name,
						const char *value) const {

			std::string s_name(name.substr(1)), s_value(value);
			s_value += "\"";
			s_name.erase(std::remove(s_name.begin(), s_name.end(), '\\'), s_name.end());
			s_value.erase(std::remove(s_value.begin(), s_value.end(), '\\'), s_value.end());
			if ((s_name == s_value) || !config.print_names_of_arguments)
				print_value(ot, value);
			else {
				print_thread_safe(ot, name, "=");
				print_value(ot, value);
			}
		}

		void ptest_suite::print_name_and_value (const output_type &ot, const std::string &name, const char value) const {
			std::string s_name(name.substr(1, 1)), s_value(1, value);
			if ((s_name == s_value) || !config.print_names_of_arguments)
				print_value(ot, value);
			else {
				print_thread_safe(ot, name, "=");
				print_value(ot, value);
			}
		}

		void ptest_suite::print_assertion_preamble (const output_type &ot,
						const std::string &assertion_name) const {

			if (suite_name != "") {
				print_thread_safe(ot, suite_name, ": ");
			}

			print_thread_safe(ot, "running assertion  ", assertion_name);

			if (config.print_thread_id) {
				print_thread_safe(ot, "  at thread ", std::this_thread::get_id());
			}
		}

		std::string ptest_suite::collapse_if_lambda (const std::string &func_name) const {
			// []{} && no regular function name can start with [
			if (func_name.size() < 4 || func_name.at(0) != '[' ||
			    !config.collapse_lambda_functions)

				return func_name;


			char closing_bracket = '}';
			char opening_bracket = '{';
			size_t counter = 0;

			for (size_t i = func_name.find_last_of(closing_bracket); i < func_name.size(); --i) {
				if (func_name[i] == closing_bracket)
					++counter;

				else if (func_name[i] == opening_bracket)
					--counter;

				if (counter == 0)
					return func_name.substr(0, i);
			}

			return func_name;
		}

		ptest_suite general_suite("");
}

bool p__start_assertion_ (bool expr, const std::string &name, const std::string &msg) {
	return ptest::general_suite.p__start_assertion_(expr, name, msg);
}

void print_final_result () { ptest::general_suite.print_general_result(); }
