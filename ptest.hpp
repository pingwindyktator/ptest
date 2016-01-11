#ifndef TESTING_PCTEST_HPP
#define TESTING_PCTEST_HPP

#include "pctest_macro.hpp"
#include <tuple>
#include <vector>
#include <chrono>
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include "prettyprint/pretty_print.hpp"

using namespace std::chrono;

namespace ptest {
    struct {
        size_t passed = 0;
        size_t failed = 0;
        size_t timeout = 0;
        std::chrono::milliseconds total_time = std::chrono::milliseconds::zero();
    } stats;

    struct {
        std::chrono::milliseconds max_time;
        bool is_timeout_active = false;
        bool use_cerr_to_error = false;
        bool print_passed_tests = true;
        bool print_names_of_arguments = true;
        bool terminate_after_first_failure = false;

        template <class Rep, class Period = std::ratio<1>>
        void set_max_time (const std::chrono::duration<Rep, Period> &max) {
          if (max > std::chrono::milliseconds::max() - std::chrono::milliseconds(15)) {
            throw std::logic_error("invalid max_time set");
          }
          max_time = max;
          is_timeout_active = true;
        }
    } configuration;

    template <typename T>
    struct function_status {
        T result;
        std::chrono::milliseconds execution_time;
    };

    class timeout_exception : public std::exception {
        virtual const char *what () const throw() {
          return "Timeout reached";
        }
    };

    template <typename First>
    void _inner_print_thread_safe (std::ostream &out, const First &value) {
      out << value;
    }

    template <typename First, typename ... Rest>
    void _inner_print_thread_safe (std::ostream &out, const First &value, const Rest &... rest) {
      out << value;
      _inner_print_thread_safe(out, rest...);
    }

    template <typename ... Args>
    void _print_thread_safe (std::ostream &out, const Args &... args) {
      static std::mutex mtx;
      std::lock_guard<std::mutex> lock(mtx);
      _inner_print_thread_safe(out, args...);
    }

    template <typename func_t, typename ... Args>
    std::chrono::milliseconds _measure_execution_time (func_t func, const Args &... args) {
      auto start = std::chrono::high_resolution_clock::now();
      func(args...);
      auto end = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<milliseconds>(end - start);
    }

    void _terminate_main_thread ();

    template <typename T>
    void _print_value (std::ostream &out, const T &value) {
      _print_thread_safe(out, value);
    }

    void _print_value (std::ostream &out, const char *value);

    void _print_value (std::ostream &out, const char value);

    template <typename T>
    void _print_name_and_value (std::ostream &out, const char *name, const T &value) {
      try {
        auto res = std::stold(name);
        _print_thread_safe(out, res);
      } catch (...) {
        if (configuration.print_names_of_arguments)
          _print_thread_safe(out, name, "=");

        _print_value(out, value);
      }
    }

    void _print_name_and_value (std::ostream &out, const char *name, const char *value);

    void _print_name_and_value (std::ostream &out, const char *name, const char value);

    template <typename First>
    void _print_args (std::ostream &out, const std::vector<const char *> args_names, size_t pos, const First &first) {
      _print_name_and_value(out, args_names.at(pos), first);
    }

    template <typename First, typename ... Rest>
    void _print_args (std::ostream &out,
            const std::vector<const char *> args_names,
            size_t pos,
            const First &first,
            const Rest &... rest) {

      _print_name_and_value(out, args_names.at(pos), first);
      _print_thread_safe(out, ", ");
      _print_args(out, args_names, pos + 1, rest...);
    }

    void _print_args (std::ostream &out,
            const std::vector<const char *> args_names,
            size_t pos);

    template <typename ... Args>
    void _print_preamble (std::ostream &out,
            const char *func_name,
            const std::vector<const char *> &args_names,
            const Args &... args) {

      _print_thread_safe(out, "running test ", func_name, "(");
      _print_args(out, args_names, 0, args...);
      _print_thread_safe(out, ")");
    }

    template <typename func_t, typename ... Args>
    auto _run_function_with_timeout (func_t func, Args &&... args) -> function_status<decltype(func(args...))> {
      auto start = std::chrono::high_resolution_clock::now();
      auto task = std::packaged_task<decltype(func(args...))()>(std::bind(func, args...));
      auto handle = task.get_future();
      std::thread th(std::move(task));
      if (handle.wait_for(configuration.max_time + std::chrono::milliseconds(10)) == std::future_status::timeout) {
        th.detach();
        throw timeout_exception();
      } else {
        auto end = std::chrono::high_resolution_clock::now();
        th.detach();
        return {handle.get(), std::chrono::duration_cast<milliseconds>(end - start)};
      }
    }

    template <typename func_t, typename ... Args>
    auto _run_function_without_timeout (func_t func, Args &&... args) -> function_status<decltype(func(args...))> {
      auto start = std::chrono::high_resolution_clock::now();
      auto result = func(args...);
      auto end = std::chrono::high_resolution_clock::now();
      return {result, std::chrono::duration_cast<milliseconds>(end - start)};
    }

    template <typename func_t, typename ... Args>
    auto _run_function (bool timeout, func_t func, Args &&... args) -> function_status<decltype(func(args...))> {
      return (timeout ? _run_function_with_timeout(func, std::forward<Args>(args)...)
                      : _run_function_without_timeout(func, std::forward<Args>(args)...));
    }

    template <typename func_t, typename T, typename ... Args>
    void _run_test (func_t function,
            const char *func_name,
            const T &expected_result,
            bool equality,
            std::vector<const char *> &&args_names,
            Args &&... args) {

      // VOODOO MAGIC, DO NOT TOUCH
      static const std::string in[2][4] = {{"  ", "\n", "!(", ")\n"},
                                           {"",   "\n", "",   "\n"}};

      std::ostream &error_output = (configuration.use_cerr_to_error ? std::cerr : std::cout);

      function_status<decltype(function(args...))> result;

      try {
        result = _run_function(configuration.is_timeout_active, function, std::forward<Args>(args)...);
      } catch (const timeout_exception &ex) {
        ++stats.timeout;
        _print_preamble(error_output, func_name, args_names, args ...);
        _print_thread_safe(error_output, "\n\tTIMEOUT\n\n");
        if (configuration.terminate_after_first_failure)
          _terminate_main_thread();

        return;
      }

      stats.total_time += result.execution_time;

      bool is_ok = (result.result == expected_result);
      if (!equality)
        is_ok = !is_ok;

      if (is_ok) {
        ++stats.passed;
        if (configuration.print_passed_tests) {
          _print_preamble(std::cout, func_name, args_names, args...);
          _print_thread_safe(std::cout, "\n\tPASSED in ", result.execution_time.count(), "ms\n\n");
        }
      } else {
        ++stats.failed;
        _print_preamble(error_output, func_name, args_names, args ...);
        _print_thread_safe(std::cout, "\n\tFAILED in ", result.execution_time.count(), "ms\n");
        _print_thread_safe(error_output, "\tresult was       ", in[equality][0], result.result, in[equality][1]);
        _print_thread_safe(error_output, "\texpecting result ", in[equality][2], result.result, in[equality][3], '\n');
        if (configuration.terminate_after_first_failure)
          _terminate_main_thread();
      }
      std::cout.flush();
      error_output.flush();
    }

#define print_final_result() {\
ptest::_print_thread_safe(std::cout, "tests passed: ", ptest::stats.passed, '\n');\
ptest::_print_thread_safe(std::cout, "tests failed: ", ptest::stats.failed, '\n');\
ptest::_print_thread_safe(std::cout, "timeout: ", ptest::stats.timeout, '\n');\
ptest::_print_thread_safe(std::cout, "total execution time: ", ptest::stats.total_time.count(), "ms");\
}
    //    void print_final_result();
}

#endif //TESTING_PCTEST_HPP
