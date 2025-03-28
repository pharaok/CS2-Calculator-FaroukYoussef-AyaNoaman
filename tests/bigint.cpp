#include "../src/bigint.h"
#include "cassert"

void test() {
  assert(BigInt(2) + BigInt(2) == BigInt(4));
  assert(BigInt(0) + BigInt(25) == BigInt(25));
  assert(BigInt(7) - BigInt(11) == BigInt(-4));
  assert(BigInt(3) * BigInt(4) == BigInt(12));
  assert(BigInt(8) / BigInt(4) == BigInt(2));

  assert(BigInt(2) < BigInt(4));
  assert(BigInt(9) > BigInt(-11));
  assert(BigInt(3) >= BigInt(3));
}
