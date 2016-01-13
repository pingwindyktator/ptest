#include <string.h>
#include "ptest.hpp"
#include <algorithm>

namespace ptest {
    stats ptest_suite::general_stats;

    ptest_suite::ptest_suite (const std::string &suite_name,
            const config &local_config) : suite_name(suite_name) { }

    void ptest_suite::print_value (std::ostream &out, const char *value) const {
      print_thread_safe(out, "\"", value, "\"");
    }

    void ptest_suite::print_value (std::ostream &out, const char value) const {
      print_thread_safe(out, "\'", value, "\'");
    }

    void ptest_suite::print_name_and_value (std::ostream &out, const char *name, const char *value) const {
      std::string s_name(name + 1), s_value(value);
      s_value += "\"";
      s_name.erase(std::remove(s_name.begin(), s_name.end(), '\\'), s_name.end());
      s_value.erase(std::remove(s_value.begin(), s_value.end(), '\\'), s_value.end());
      if ((s_name == s_value) || !local_config.print_names_of_arguments)
        print_value(out, value);
      else {
        print_thread_safe(out, name, "=");
        print_value(out, value);
      }
    }

    void ptest_suite::print_name_and_value (std::ostream &out, const char *name, const char value) const {
      std::string s_name(name + 1), s_value(1, value);
      s_value += "\'";
      s_name.erase(std::remove(s_name.begin(), s_name.end(), '\\'), s_name.end());
      if ((s_name == s_value) || !local_config.print_names_of_arguments)
        print_value(out, value);
      else {
        print_thread_safe(out, name, "=");
        print_value(out, value);
      }
    }

    void ptest_suite::terminate_main_thread () {
      std::cout.flush();
      std::cerr.flush();
      exit(0);
    }

    void ptest_suite::print_args (std::ostream &out,
            const std::vector<const char *> args_names,
            size_t pos) const { }

    void ptest_suite::print_suite_result () const {
      print_thread_safe(std::cout, "----- RESULT IN SUITE ", suite_name,  ":\n");
      print_thread_safe(std::cout, "tests passed: ", local_suite_stats.passed, '\n');
      print_thread_safe(std::cout, "tests failed: ", local_suite_stats.failed, '\n');
      print_thread_safe(std::cout, "timeout: ", local_suite_stats.timeout, '\n');
      print_thread_safe(std::cout, "total execution time: ", local_suite_stats.total_time.count(), "ms\n");
      print_thread_safe(std::cout, "---------------------\n");
    }

    void ptest_suite::print_general_result () {
      print_thread_safe(std::cout, "----- FINAL RESULT:\n");
      print_thread_safe(std::cout, "tests passed: ", general_stats.passed, '\n');
      print_thread_safe(std::cout, "tests failed: ", general_stats.failed, '\n');
      print_thread_safe(std::cout, "timeout: ", general_stats.timeout, '\n');
      print_thread_safe(std::cout, "total execution time: ", general_stats.total_time.count(), "ms\n");
    }

    void ptest_suite::update_stats (const ptest_suite::function_status &status,
            const std::chrono::milliseconds &execution_time) const {
      switch (status) {
        case function_status::passed:
          ++general_stats.passed;
          ++local_suite_stats.passed;
          general_stats.total_time += execution_time;
          local_suite_stats.total_time += execution_time;
          break;
        case function_status::failed:
          ++general_stats.failed;
          ++local_suite_stats.failed;
          general_stats.total_time += execution_time;
          local_suite_stats.total_time += execution_time;
          break;
        case function_status::timeout:
          ++general_stats.timeout;
          ++local_suite_stats.timeout;
          break;
      }
    }

    ptest_suite general("");
}