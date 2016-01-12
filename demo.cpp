#include <iostream>
#include <chrono>
#include "ptest.hpp"

using namespace std;

int func (int a, int b, const char *, double, char) { return a * b; }

int test1 (int a, int b) { return a * b; }

int func2 (int a, const std::vector<int> &) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  return a;
}

int func3(const char *, const char [], const char [], char, const char, const char *, const char [], const char [], char, const char) { return 44; }

int func4(int a) { return a; }

int func5() { return 44; }


int main () {
  int b = 4;
  vector<int> vec {1, 2, 3};
  int aa = 99;
  run_simple_test(func4, b, 4, 0);
  run_simple_test(func5, 44, 1);
  run_simple_test(func2, 5, vec, 5, 0);
  run_simple_test(func, 1, 1, "ehe xd\"", 3.14, '\'', 2, 0);
  run_simple_test(func3, "ala ee", "ala a", "ala b", 'a', 'b', "al\"}", "al\"}", "al\"}", '\"', '\"', 44, 1);
  run_simple_test([] (int) -> int { return 99; }, 98, aa, 1);
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j)
    run_simple_test(test1, i, j, (i*j), 1);
  }

  return 0;
}