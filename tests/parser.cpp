#include "../src/parser.h"
#include <cassert>
#include <cmath>
#include <iostream>

int main() {
  std::cout << "Running parser tests..." << std::endl;

  const double EPSILON = 0.0001;

  assert(std::fabs(compute("2 + 3") - 5) <= EPSILON);
  assert(std::fabs(compute("2 * 3") - 6) <= EPSILON);
  assert(std::fabs(compute("7 / 2") - 3.5) <= EPSILON);
  assert(std::fabs(compute("5 - 3") - 2) <= EPSILON);
  std::cout << "All simple expression tests passed." << std::endl;

  assert(std::fabs(compute("2 + 3 * 4") - 14) <= EPSILON);
  assert(std::fabs(compute("2 * 3 + 4") - 10) <= EPSILON);
  assert(std::fabs(compute("2 * (3 + 4)") - 14) <= EPSILON);
  assert(std::fabs(compute("(2 + 3) * (4 - 5)") - -5) <= EPSILON);
  std::cout << "All operator precedence tests passed." << std::endl;

  std::cout << "All parser tests passed." << std::endl;
  return 0;
}
