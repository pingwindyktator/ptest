#include <iostream>
#include "plog/plog.hpp"
#include "ptest/ptest.hpp"
#include "libmath/libmath.hpp"
#include "prandom/prandom.hpp"
#include "mod_number/mod_number.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <list>
#include <vector>
#include <x86intrin.h>

using namespace std;
using namespace boost::multiprecision;

typedef number<cpp_int_backend<5120, 5120, signed_magnitude, checked, void>> long_type;

new_test_suite(power_modulo_suite);
new_test_suite(prandom_in_range_suite);
new_test_suite(is_coprime_suite);
new_test_suite(get_mult_inverse_suite);

void power_modulo_test (size_t size) {
  static constexpr size_t bytes = 15;
  power_modulo_suite.config.set_max_time(std::chrono::seconds(1));
  power_modulo_suite.config.use_cerr_to_error = false;
  power_modulo_suite.config.print_passed_tests = false;

  long_type a, b, mod;

  for (size_t i = 0; i < size; ++i) {
    a = prandom::get_posivite_random<decltype(a)>(bytes);
    b = prandom::get_posivite_random<decltype(b)>(bytes);
    mod = prandom::get_posivite_random<decltype(mod)>(bytes) + 1;
    run_suite_assert(power_modulo_suite, a >= 0);
    run_suite_assert(power_modulo_suite, b >= 0);
    run_suite_assert(power_modulo_suite, mod >= 0);
    run_suite_test(power_modulo_suite, pmath::power_modulo<decltype(a)>, a, b, mod, powm(a, b, mod), pequal);
  }
}

void prandom_in_range_test (size_t size, size_t mod = 10) {
  long_type a, b, result;
  for (size_t i = 1; i <= size; ++i) {
    a = prandom::get_random<decltype(a)>(size % mod);
    b = prandom::get_posivite_random<decltype(b)>(size % mod) + 1;

    result = prandom::get_random_in_range<decltype(result)>(a, a + b);
    if (run_suite_assert(prandom_in_range_suite, result >= a) == pfailed) {
      pdebug(result);
      pdebug(a);
      pdebug(b + a);
    }
    if (run_suite_assert(prandom_in_range_suite, result < b + a) == pfailed) {
      pdebug(result);
      pdebug(a);
      pdebug(b + a);
    }
  }
}

void prandom_uniformly_dist_test (size_t size, size_t max = 1000) {
  size_t result;
  size_t *occ = new size_t[max] {};

  for (size_t i = 1; i <= size; ++i) {
    result = prandom::get_random_in_range<decltype(result)>(0, max);
    if (run_assert(result >= 0) == pfailed) {
      pdebug(result);
      pdebug(max);
    }
    if (run_assert(result < max) == pfailed) {
      pdebug(result);
      pdebug(max);
    }
    ++occ[result];
  }

  size_t max_element = 0, min_element = numeric_limits<size_t>::max();

  cout << "RESULT:\n";
  for (size_t i = 0; i < max; ++i) {
    cout << i << ":\t" << occ[i] << '\n';
    if (max_element < occ[i])
      max_element = occ[i];

    if (min_element > occ[i])
      min_element = occ[i];
  }
  cout << '\n';
  pdebug(max_element - min_element);
  delete[] occ;
}

void is_coprime_test (int size, const long_type &max) {
  long_type random;
  vector<long_type> cop;
  for (int i = 0; i < size; ++i) {
    random = prandom::get_random_in_range<long_type>(0, max);
    try {
      cop = pmath::coprimes<long_type>(0, max, random);
    } catch (const std::bad_alloc &exc) {
    }
    for (auto &c : cop) {
      run_suite_test(is_coprime_suite, pmath::gcd<long_type>, c, random, 1, pequal);
    }
  }
}

template <int max>
bool get_mult_inverse_test (int size) {
  mod_number<int, max> checked;
  auto checker = [] (const mod_number<int, max> &a) {
      pdebug(max);
      return (a.get_mult_inverse() * a == 1);
  };

  for (int i = 0; i < size; ++i) {
    checked = prandom::get_random_in_range<int>(0, max);
    run_suite_test(get_mult_inverse_suite, checker, checked, 1, pequal);
  }
  return false;
}


int main () {
  cerr.rdbuf(cout.rdbuf()); // redirect std::cerr into std::cout
  ptest::config_t my_conf;
  my_conf.terminate_after_first_failure = false;
  my_conf.terminate_after_first_exception = false;
  my_conf.print_passed_tests = false;
  my_conf.use_cerr_to_error = false;

  is_coprime_suite.config = my_conf;
  prandom_in_range_suite.config = my_conf;
  power_modulo_suite.config = my_conf;
  get_mult_inverse_suite.config = my_conf;
  ptest::general_suite.config = my_conf;

  get_mult_inverse_suite.config.print_exceptions = false;

  try {
    ptest::call_test(4, is_coprime_test, 10000, 1000);
    ptest::call_test(4, prandom_in_range_test, 100000, 10000);
    ptest::call_test(4, power_modulo_test, 1000000);
    ptest::call_test(1, get_mult_inverse_test<987>, 100000);

    print_final_suite_result(power_modulo_suite);
    print_final_suite_result(prandom_in_range_suite);
    print_final_suite_result(is_coprime_suite);
    print_final_suite_result(get_mult_inverse_suite);
    print_final_test_result();
  } catch (const exception &ex) {
    cout << ex.what();
  }
  return 0;
}