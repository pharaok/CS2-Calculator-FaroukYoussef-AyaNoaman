# CS2 Calculator

Simple calculator library and mathematical expression parser.

## Installation

```bash
git clone https://github.com/pharaok/CS2-Calculator-FaroukYoussef-AyaNoaman.git
cd CS2-Calculator-FaroukYoussef-AyaNoaman
mkdir build && cd build
cmake ..
make
```

## Documentation

### BigInt library

Arbitrary size integer library.
Implemented as a vector of unsigned 32-bit integer representing base 2^32 digits in little-endian order
(least significant digit is placed at the smallest index).

Features:

- [x] Arbitrary size integers
- [x] Basic arithmetic operations (+, -, \*, /, %)
- [x] Comparison operators (==, !=, <, >, <=, >=)
- [x] String and integer constructors
- [x] Factorial, power, GCD, and LCM functions
- [x] Random number generation
- [ ] Fast division algorithm such as Knuth's Algorithm D

## Contributors

- Farouk Youssef (farouktamer@aucegypt.edu)
- Aya Noaman (ayanoaman3@aucegypt.edu)
