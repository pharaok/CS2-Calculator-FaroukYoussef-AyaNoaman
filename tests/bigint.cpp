#include "../src/bigint.h"
#include "cassert"
#include <climits>
#include <iostream>
#include <limits>
#include <ostream>

int main() {
  assert(BigInt(2) + BigInt(2) == BigInt(4));
  assert(BigInt(7) - BigInt(11) == -BigInt(4));
  assert(-BigInt(7) + BigInt(11) == BigInt(4));
  assert(BigInt(3) * BigInt(4) == BigInt(12));
  assert(BigInt(8) / BigInt(4) == BigInt(2));
  assert(BigInt(8) % BigInt(4) == BigInt(0));
  assert(BigInt(8) % BigInt(3) == BigInt(2));

  assert(BigInt(0) == BigInt(0));
  assert(BigInt(0) == BigInt("+0"));
  assert(BigInt("+0") == BigInt("-0"));
  assert(BigInt(13) < BigInt(14));
  assert(BigInt(2) < BigInt(4));
  assert(BigInt(9) > BigInt(-11));
  assert(BigInt(3) >= BigInt(3));

  assert(BigInt::factorial(100) ==
         BigInt("93326215443944152681699238856266700490715968264381621468592963"
                "89521759999322991560894146397615651828625369792082722375825118"
                "5210916864000000000000000000000000"));
  assert(BigInt::gcd(BigInt(12), BigInt(15)) == BigInt(3));
  assert(BigInt::lcm(BigInt(12), BigInt(15)) == BigInt(60));
  return 0;
}
