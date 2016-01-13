#ifndef TESTING_PCTEST_HPP
#define TESTING_PCTEST_HPP

#include <tuple>
#include <vector>
#include <chrono>
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include "prettyprint/pretty_print.hpp"


namespace ptest {
    struct stats {
        size_t passed = 0;
        size_t failed = 0;
        size_t timeout = 0;
        std::chrono::milliseconds total_time = std::chrono::milliseconds::zero();
    };

    struct config {
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
    };

    class timeout_exception : public std::exception {
        virtual const char *what () const throw() {
          return "Timeout reached";
        }
    };

    class ptest_suite {
    public:
        mutable stats local_suite_stats;
        static stats general_stats;
        config local_config;

        ptest_suite (const std::string &suite_name, const config &local_config = config());

        template <typename ... Args>
        static void print_thread_safe (std::ostream &out, const Args &... args) {
          static std::mutex mtx;
          std::lock_guard<std::mutex> lock(mtx);
          inner_print_thread_safe(out, args...);
        }

        template <typename func_t, typename T, typename ... Args>
        void run_test (func_t function,
                const char *func_name,
                const T &expected_result,
                bool equality,
                std::vector<const char *> &&args_names,
                Args &&... args) const {

          // VOODOO MAGIC, DO NOT TOUCH
          static const std::string in[2][4] = {{"  ", "\n", "!(", ")\n"},
                                               {"",   "\n", "",   "\n"}};

          std::ostream &error_output = (local_config.use_cerr_to_error ? std::cerr : std::cout);

          function_result<decltype(function(args...))> result;

          try {
            result = run_function(local_config.is_timeout_active, function, std::forward<Args>(args)...);
          } catch (const timeout_exception &ex) {
            print_preamble(error_output, func_name, args_names, args ...);
            print_thread_safe(error_output, "\n\tTIMEOUT\n\n");
            if (local_config.terminate_after_first_failure)
              terminate_main_thread();

            update_stats(function_status::timeout);
            return;
          }

          bool is_ok = (result.result == expected_result);
          if (!equality)
            is_ok = !is_ok;

          if (is_ok) {
            update_stats(function_status::passed, result.execution_time);
            if (local_config.print_passed_tests) {
              print_preamble(std::cout, func_name, args_names, args...);
              print_thread_safe(std::cout, "\n\tPASSED in ", result.execution_time.count(), "ms\n\n");
            }
          } else {
            update_stats(function_status::failed, result.execution_time);
            print_preamble(error_output, func_name, args_names, args ...);
            print_thread_safe(std::cout, "\n\tFAILED in ", result.execution_time.count(), "ms\n");
            print_thread_safe(error_output, "\tresult was       ", in[equality][0], result.result, in[equality][1]);
            print_thread_safe(error_output, "\texpecting result ", in[equality][2], result.result, in[equality][3], '\n');
            if (local_config.terminate_after_first_failure)
              terminate_main_thread();
          }
          std::cout.flush();
          error_output.flush();
        }

        template <typename func_t, typename ... Args>
        static std::chrono::milliseconds measure_execution_time (func_t func, Args &... args) {
          auto start = std::chrono::high_resolution_clock::now();
          func(args...);
          auto end = std::chrono::high_resolution_clock::now();
          return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        }

        void print_suite_result () const;

        static void print_general_result ();

    private:
        template <typename T>
        struct function_result {
            T result;
            std::chrono::milliseconds execution_time;
        };

        enum class function_status {
            failed = 0,
            passed = 1,
            timeout = 2
        };

        std::string suite_name;

        template <typename First>
        static void inner_print_thread_safe (std::ostream &out, const First &value) {
          out << value;
        }

        template <typename First, typename ... Rest>
        static void inner_print_thread_safe (std::ostream &out, const First &value, const Rest &... rest) {
          out << value;
          inner_print_thread_safe(out, rest...);
        }

        static void terminate_main_thread ();

        void update_stats (const function_status &,
                const std::chrono::milliseconds & = std::chrono::milliseconds::zero()) const;

        template <typename T>
        void print_value (std::ostream &out, const T &value) const {
          print_thread_safe(out, value);
        }

        void print_value (std::ostream &out, const char *value) const;

        void print_value (std::ostream &out, const char value) const;

        template <typename T>
        void print_name_and_value (std::ostream &out, const char *name, const T &value) const {
          try {
            auto res = std::stold(name);
            print_thread_safe(out, res);
          } catch (...) {
            if (local_config.print_names_of_arguments)
              print_thread_safe(out, name, "=");

            print_value(out, value);
          }
        }

        void print_name_and_value (std::ostream &out, const char *name, const char *value) const;

        void print_name_and_value (std::ostream &out, const char *name, const char value) const;

        template <typename First>
        void print_args (std::ostream &out,
                const std::vector<const char *> args_names,
                size_t pos,
                const First &first) const {
          print_name_and_value(out, args_names.at(pos), first);
        }

        template <typename First, typename ... Rest>
        void print_args (std::ostream &out,
                const std::vector<const char *> args_names,
                size_t pos,
                const First &first,
                const Rest &... rest) const {

          print_name_and_value(out, args_names.at(pos), first);
          print_thread_safe(out, ", ");
          print_args(out, args_names, pos + 1, rest...);
        }

        void print_args (std::ostream &out,
                const std::vector<const char *> args_names,
                size_t pos) const;

        template <typename ... Args>
        void print_preamble (std::ostream &out,
                const char *func_name,
                const std::vector<const char *> &args_names,
                const Args &... args) const {

          if (suite_name == "") {
            print_thread_safe(out, "running test ", func_name, "(");
          } else {
            print_thread_safe(out, suite_name, ": running test ", func_name, "(");
          }
          print_args(out, args_names, 0, args...);
          print_thread_safe(out, ")");
        }

        template <typename func_t, typename ... Args>
        auto run_function_with_timeout (func_t func, Args &&... args) const -> function_result<decltype(func(args...))> {
          auto start = std::chrono::high_resolution_clock::now();
          auto task = std::packaged_task<decltype(func(args...))()>(std::bind(func, args...));
          auto handle = task.get_future();
          std::thread th(std::move(task));
          if (handle.wait_for(local_config.max_time + std::chrono::milliseconds(10)) == std::future_status::timeout) {
            th.detach();
            throw timeout_exception();
          } else {
            auto end = std::chrono::high_resolution_clock::now();
            th.detach();
            return {handle.get(), std::chrono::duration_cast<std::chrono::milliseconds>(end - start)};
          }
        }

        template <typename func_t, typename ... Args>
        auto run_function_without_timeout (func_t func, Args &&... args) const -> function_result<decltype(func(args...))> {
          auto start = std::chrono::high_resolution_clock::now();
          auto result = func(args...);
          auto end = std::chrono::high_resolution_clock::now();
          return {result, std::chrono::duration_cast<std::chrono::milliseconds>(end - start)};
        }

        template <typename func_t, typename ... Args>
        auto run_function (bool timeout, func_t func, Args &&... args) const -> function_result<decltype(func(args...))> {
          return (timeout ? run_function_with_timeout(func, std::forward<Args>(args)...)
                          : run_function_without_timeout(func, std::forward<Args>(args)...));
        }
    };

    extern ptest_suite general;
}

#include "ptest_simple_test_macro.hpp"
#include "ptest_suite_test_macro.hpp"

#define print_final_result() {\
ptest::ptest_suite::print_general_result();\
}
#endif //TESTING_PCTEST_HPP
