#include <string.h>
#include "ptest.hpp"
#include <algorithm>

namespace ptest {
    void _print_value (std::ostream &out, const char *value) {
      _print_thread_safe(out, "\"", value, "\"");
    }

    void _print_value (std::ostream &out, const char value) {
      _print_thread_safe(out, "\'", value, "\'");
    }

    void _print_name_and_value (std::ostream &out, const char *name, const char *value) {
      std::string s_name(name + 1), s_value(value);
      s_value += "\"";
      s_name.erase(std::remove(s_name.begin(), s_name.end(), '\\'), s_name.end());
      s_value.erase(std::remove(s_value.begin(), s_value.end(), '\\'), s_value.end());
      if ((s_name == s_value) || !ptest::configuration.print_names_of_arguments)
        _print_value(out, value);
      else {
        _print_thread_safe(out, name, "=");
        _print_value(out, value);
      }
    }

    void _print_name_and_value (std::ostream &out, const char *name, const char value) {
      std::string s_name(name + 1), s_value (1, value);
      s_value += "\'";
      s_name.erase(std::remove(s_name.begin(), s_name.end(), '\\'), s_name.end());
      if ((s_name == s_value) || !ptest::configuration.print_names_of_arguments)
        _print_value(out, value);
      else {
        _print_thread_safe(out, name, "=");
        _print_value(out, value);
      }
    }

    void _terminate_main_thread() {
      std::cout.flush();
      std::cerr.flush();
      exit(0);
    }
}