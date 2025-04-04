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

### Parser Program

You can input any common mathematical expression (numbers only, no variables) and it will be interpreted by the program.
You may use common arithmetic, brackets, and all functions from the Calculator library below.

Example:
`5 * 4 - 2lcm(2, 3)*4!` will output `-268`.

### Calculator Library

Features:

- [x] Basic arithmetic (addition, subtraction, multiplication, division)
- [x] Factorial (integer types only)
- [x] Greatest common divisor (integer types only)
- [x] Least common multiple (integer types only)
- [x] Random number generator
- [x] Incorporated BigInt class (infinite integers) described below

### BigInt Library

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
