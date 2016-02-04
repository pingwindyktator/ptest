#ifndef PLIB_PTEST_HPP
#define PLIB_PTEST_HPP

#include <tuple>
#include <vector>
#include <chrono>
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include <list>
#include "prettyprint/pretty_print.hpp"


namespace ptest {
    struct stats_t {
        std::atomic<size_t> passed;
        std::atomic<size_t> failed;
        std::atomic<size_t> timeout;
        std::atomic<size_t> exceptions;
        std::atomic<std::chrono::microseconds> total_time;
    };

    struct config_t {
        std::chrono::microseconds max_time;
        bool is_timeout_active = false;
        bool use_cerr_to_error = false;
        bool print_passed_tests = false;
        bool print_exceptions = true;
        bool print_names_of_arguments = true;
        bool terminate_after_first_failure = false;
        bool terminate_after_first_exception = false;
        bool terminate_after_first_timeout = false;

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

    template <typename func_t, typename ... Args>
    std::chrono::microseconds measure_execution_time (func_t &&func, Args &&... args) {
      auto start = std::chrono::high_resolution_clock::now();
      func(std::forward<Args>(args)...);
      auto end = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }

    template <typename func_t, typename ... Args>
    void call_test (size_t threads_number, func_t &&func, Args &&... args) {
      std::list <std::thread> threads;
      for (size_t i = 0; i < threads_number; ++i)
        threads.emplace_back(std::thread(func, std::forward<Args>(args)...));

      for (auto &t : threads)
        t.join();
    }

    class ptest_suite {
    public:
        mutable stats_t stats;
        static stats_t general_stats;
        config_t config;

        ptest_suite (const std::string &suite_name, const config_t &local_config = config_t());

        // =========================================================================

        template <typename func_t, typename T, typename ... Args>
        void start_test (func_t &&function,
                const std::string &func_name,
                const T &expected_result,
                bool equality,
                std::vector<std::string> &&args_names,
                Args &&... args) const {

          using return_type = typename std::result_of<func_t(Args...)>::type;
          // VOODOO MAGIC, DO NOT TOUCH
          static const std::string voodoo[2][5] = {{"  ", "\n", "!(", ")\n", "  "},
                                                   {"",   "\n", "",   "\n",  ""}};

          std::ostream &error_output = (config.use_cerr_to_error ? std::cerr : std::cout);

          function_result<return_type> result;

          try {
            result = run_function(config.is_timeout_active, function, std::forward<Args>(args)...);
          } catch (const timeout_exception &ex) {
            print_test_preamble(error_output, func_name, args_names, args ...);
            print_thread_safe(error_output, "\n\tTIMEOUT\n\n");
            update_stats(function_status::timeout);
            if (config.terminate_after_first_timeout)
              terminate_process();

            return;
          } catch (const std::exception &exc) {
            if (config.print_exceptions) {
              print_test_preamble(error_output, func_name, args_names, args ...);
              print_thread_safe(error_output, "\n\tEXCEPTION CAUGTH: ", exc.what(), "\n\n");
            }
            update_stats(function_status::exception);
            if (config.terminate_after_first_exception)
              terminate_process();

            return;
          } catch (...) {
            if (config.print_exceptions) {
              print_test_preamble(error_output, func_name, args_names, args ...);
              print_thread_safe(error_output, "\n\tEXCEPTION CAUGTH", "\n\n");
            }
            update_stats(function_status::exception);
            if (config.terminate_after_first_exception)
              terminate_process();

            return;
          }

          bool is_ok = (result.result == expected_result);
          if (!equality)
            is_ok = !is_ok;

          if (is_ok) {
            update_stats(function_status::passed, result.execution_time);
            if (config.print_passed_tests) {
              print_test_preamble(std::cout, func_name, args_names, args...);
              print_thread_safe(std::cout, "\n\tPASSED in ", result.execution_time.count(), " microseconds\n\n");
            }
          } else {
            update_stats(function_status::failed, result.execution_time);
            print_test_preamble(error_output, func_name, args_names, args ...);
            print_thread_safe(std::cout, "\n\tFAILED in        ", voodoo[equality][4], result.execution_time.count(), " microseconds\n");
            print_thread_safe(error_output, "\tresult was       ", voodoo[equality][0], result.result, voodoo[equality][1]);
            print_thread_safe(error_output, "\texpecting result ", voodoo[equality][2], expected_result, voodoo[equality][3], '\n');
            if (config.terminate_after_first_failure)
              terminate_process();
          }
        }

        void run_assertion (bool expr, const std::string &name, const std::string &msg = "");

        // =========================================================================

        void clear_stats();

        // =========================================================================

        void print_suite_result () const;

        static void print_general_result ();

        template <typename ... Args>
        static void print_thread_safe (std::ostream &out, Args &&... args) {
          static std::mutex mtx;
          std::lock_guard<std::mutex> lock(mtx);
          _print_thread_safe(out, std::forward<Args>(args)...);
        }

    private:
        template <typename T>
        struct function_result {
            T result;
            std::chrono::microseconds execution_time;
        };

        enum class function_status {
            failed = 0,
            passed = 1,
            timeout = 2,
            exception = 3
        };

        std::string suite_name;

        // =========================================================================

        template <typename func_t, typename ... Args>
        auto run_function_with_timeout (func_t &&func,
                Args &&... args) const -> function_result<typename std::result_of<func_t(Args...)>::type> {

          using return_type = typename std::result_of<func_t(Args...)>::type;

          auto start = std::chrono::high_resolution_clock::now();
          auto exec = [&func, &args...] () -> return_type {
            return func(std::forward<Args>(args)...);
          };

          auto task = std::packaged_task<return_type()>(exec);

          auto handle = task.get_future();
          std::thread th(std::move(task));

          if (handle.wait_for(config.max_time + std::chrono::milliseconds(10)) == std::future_status::timeout) {
            th.detach();
            throw timeout_exception();
          } else {
            auto end = std::chrono::high_resolution_clock::now();
            th.detach();
            return {handle.get(), std::chrono::duration_cast<std::chrono::microseconds>(end - start)};
          }
        }

        template <typename func_t, typename ... Args>
        auto run_function_without_timeout (func_t &&func,
                Args &&... args) const -> function_result<typename std::result_of<func_t(Args...)>::type> {

          auto start = std::chrono::high_resolution_clock::now();
          auto result = func(std::forward<Args>(args)...);
          auto end = std::chrono::high_resolution_clock::now();
          return {result, std::chrono::duration_cast<std::chrono::microseconds>(end - start)};
        }

        template <typename func_t, typename ... Args>
        auto run_function (bool timeout,
                func_t &&func,
                Args &&... args) const -> function_result<typename std::result_of<func_t(Args...)>::type> {

          return (timeout ? run_function_with_timeout(func, std::forward<Args>(args)...)
                          : run_function_without_timeout(func, std::forward<Args>(args)...));
        }

        // =========================================================================

        static void terminate_process ();

        void update_stats (const function_status &,
                const std::chrono::microseconds & = std::chrono::microseconds::zero()) const;

        // =========================================================================

        template <typename First>
        static void _print_thread_safe (std::ostream &out, const First &value) {
          out << value;
          out.flush();
        }

        template <typename First, typename ... Rest>
        static void _print_thread_safe (std::ostream &out, const First &value, Rest &&... rest) {
          out << value;
          _print_thread_safe(out, std::forward<Rest>(rest)...);
        }

        template <typename T>
        void print_value (std::ostream &out, const T &value) const {
          print_thread_safe(out, value);
        }

        void print_value (std::ostream &out, const std::string &value) const;

        void print_value (std::ostream &out, const char value) const;

        template <typename T>
        void print_name_and_value (std::ostream &out, const std::string &name, const T &value) const {
          try {
            auto res = std::stold(name);
            print_thread_safe(out, res);
          } catch (...) {
            if (config.print_names_of_arguments)
              print_thread_safe(out, name, "=");

            print_value(out, value);
          }
        }

        void print_name_and_value (std::ostream &out, const std::string &name, const std::string &value) const;

        void print_name_and_value (std::ostream &out, const std::string &name, const char value) const;

        template <typename First>
        void print_args (std::ostream &out,
                const std::vector<std::string> args_names,
                size_t pos,
                const First &first) const {
          print_name_and_value(out, args_names.at(pos), first);
        }

        void print_args (std::ostream &out,
                const std::vector<std::string> args_names,
                size_t pos) const;

        template <typename First, typename ... Rest>
        void print_args (std::ostream &out,
                const std::vector<std::string> args_names,
                size_t pos,
                const First &first,
                Rest &&... rest) const {

          print_name_and_value(out, args_names.at(pos), first);
          print_thread_safe(out, ", ");
          print_args(out, args_names, pos + 1, std::forward<Rest>(rest)...);
        }

        template <typename ... Args>
        void print_test_preamble (std::ostream &out,
                const std::string &func_name,
                const std::vector<std::string> &args_names,
                Args &&... args) const {

          if (suite_name == "") {
            print_thread_safe(out, "running test ", func_name, "(");
          } else {
            print_thread_safe(out, suite_name, ": running test ", func_name, "(");
          }
          print_args(out, args_names, 0, std::forward<Args>(args)...);
          print_thread_safe(out, ")");
        }

        template <typename ... Args>
        void print_assertion_preamble (std::ostream &out,
                const std::string &assertion_name) const {

          if (suite_name == "") {
            print_thread_safe(out, "running assertion ", assertion_name);
          } else {
            print_thread_safe(out, suite_name, ": running assertion ", assertion_name);
          }
        }
    };

    extern ptest_suite general_suite;
}

#include "suite_test_macro.hpp"
#include "test_macro.hpp"
#include "assert_macro.hpp"
#include "new_test_suite_macro.hpp"

#define print_final_test_result() {\
ptest::ptest_suite::print_general_result();\
}

#define print_final_suite_result(suite) {\
suite.print_suite_result();\
}

#endif //PLIB_PTEST_HPP
