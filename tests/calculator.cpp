#include "../src/calculator.h"
#include "../src/bigint.h"
#include <cassert>
#include <iostream>

int main() {
  std::cout << "Running calculator tests..." << std::endl;

  assert(calculator::add(2, 3) == 5);
  assert(calculator::sub(5, 3) == 2);
  assert(calculator::mult(7, 11) == 77);
  assert(calculator::div(9, 2) == 4);
  std::cout << "All integer tests passed." << std::endl;

  assert(calculator::gcd(48, 18) == 6);
  assert(calculator::gcd(56, 98) == 14);
  assert(calculator::lcm(4, 6) == 12);
  assert(calculator::lcm(15, 20) == 60);
  std::cout << "All GCD and LCM tests passed." << std::endl;

  assert(calculator::fact(BigInt(5)) == BigInt(120));
  assert(calculator::mult(BigInt(1000000), BigInt(1000000)) ==
         BigInt(1000000000000));
  assert(calculator::gcd(BigInt("1234567890123456789"),
                         BigInt("9876543210987654321")) ==
         BigInt("90000000009"));
  assert(calculator::lcm(BigInt("1234567890123456789"),
                         BigInt("9876543210987654321")) ==
         BigInt("135480701249809480123626141"));
  std::cout << "All BigInt tests passed." << std::endl;

  std::cout << "All calculator tests passed." << std::endl;
  return 0;
}
