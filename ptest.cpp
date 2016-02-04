#include <string.h>
#include "ptest.hpp"
#include <algorithm>

namespace ptest {
    stats_t ptest_suite::general_stats;

    ptest_suite::ptest_suite (const std::string &suite_name,
            const config_t &local_config) : config(local_config), suite_name(suite_name) {

      clear_stats();
    }

    void ptest_suite::print_value (std::ostream &out, const std::string &value) const {
      print_thread_safe(out, "\"", value, "\"");
    }

    void ptest_suite::print_value (std::ostream &out, const char value) const {
      print_thread_safe(out, "\'", value, "\'");
    }

    void ptest_suite::print_args (std::ostream &out, const std::vector<std::string> args_names, size_t pos) const { }

    void ptest_suite::print_name_and_value (std::ostream &out,
            const std::string &name,
            const std::string &value) const {
      std::string s_name(name.substr(1)), s_value(value);
      s_value += "\"";
      s_name.erase(std::remove(s_name.begin(), s_name.end(), '\\'), s_name.end());
      s_value.erase(std::remove(s_value.begin(), s_value.end(), '\\'), s_value.end());
      if ((s_name == s_value) || !config.print_names_of_arguments)
        print_value(out, value);
      else {
        print_thread_safe(out, name, "=");
        print_value(out, value);
      }
    }

    void ptest_suite::print_name_and_value (std::ostream &out, const std::string &name, const char value) const {
      std::string s_name(name.substr(1)), s_value(1, value);
      s_value += "\'";
      s_name.erase(std::remove(s_name.begin(), s_name.end(), '\\'), s_name.end());
      if ((s_name == s_value) || !config.print_names_of_arguments)
        print_value(out, value);
      else {
        print_thread_safe(out, name, "=");
        print_value(out, value);
      }
    }


    void ptest_suite::terminate_process () {
      std::cout << "\nterminating... ";
      std::cout.flush();
      std::cerr.flush();
      exit(0);
    }


    void ptest_suite::print_suite_result () const {
      print_thread_safe(std::cout, "----- TEST RESULT IN SUITE ", suite_name, ":\n");
      print_thread_safe(std::cout, "tests passed:         ", stats.passed, '\n');
      print_thread_safe(std::cout, "tests failed:         ", stats.failed, '\n');
      print_thread_safe(std::cout, "timeout:              ", stats.timeout, '\n');
      print_thread_safe(std::cout, "exceptions:           ", stats.exceptions, '\n');
      print_thread_safe(std::cout, "total execution time: ", stats.total_time.load().count(), " microseconds\n\n");
    }

    void ptest_suite::print_general_result () {
      print_thread_safe(std::cout, "----- FINAL TEST RESULT:\n");
      print_thread_safe(std::cout, "tests passed:         ", general_stats.passed, '\n');
      print_thread_safe(std::cout, "tests failed:         ", general_stats.failed, '\n');
      print_thread_safe(std::cout, "timeout:              ", general_stats.timeout, '\n');
      print_thread_safe(std::cout, "exceptions:           ", general_stats.exceptions, '\n');
      print_thread_safe(std::cout, "total execution time: ", general_stats.total_time.load().count(), " microseconds\n\n");
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

    ptest_suite general_suite("");

    void ptest_suite::run_assertion (bool expr, const std::string &name, const std::string &msg) {
      if (expr) {
        update_stats(function_status::passed);
        if (config.print_passed_tests) {
          print_assertion_preamble(std::cout, name);
          print_thread_safe(std::cout, "\n\tPASSED\n\n");
        }

      } else {
        update_stats(function_status::failed);
        std::ostream &out = config.use_cerr_to_error ? std::cerr : std::cout;
        print_assertion_preamble(out, name);
        print_thread_safe(out, "\n\tFAILED");
        if (!msg.empty())
          print_thread_safe(out, ": ", msg);

        print_thread_safe(out, "\n\n");
        if (config.terminate_after_first_failure)
          terminate_process();
      }
    }

    void ptest_suite::clear_stats () {
      stats.exceptions = 0;
      stats.failed = 0;
      stats.passed = 0;
      stats.timeout = 0;
      stats.total_time = std::chrono::microseconds::zero();
    }
}