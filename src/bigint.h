#pragma once

#include <ostream>
#include <string>
#include <vector>
class BigInt {
private:
  bool negative;
  std::vector<unsigned int> digits; // little-endian
  void addWithCarry(int i, unsigned long long carry);
  void subWithBorrow(int i, long long borrow);

public:
  BigInt(long long n = 0, bool negative = false);
  BigInt(std::vector<unsigned int> digits, bool negative = false);
  BigInt(std::string s);

  int bitLength();
  void normalize();
  BigInt operator-() const;

  BigInt divmod(const BigInt &other, BigInt &remainder) const;

  BigInt operator+(const BigInt &other) const;
  BigInt operator-(const BigInt &other) const;
  BigInt operator*(const BigInt &other) const;
  BigInt operator/(const BigInt &other) const;
  BigInt operator%(const BigInt &other) const;
  BigInt operator>>(int shift) const;
  BigInt operator<<(int shift) const;

  BigInt &operator+=(const BigInt &other);
  BigInt &operator-=(const BigInt &other);
  BigInt &operator*=(const BigInt &other);
  BigInt &operator/=(const BigInt &other);
  BigInt &operator%=(const BigInt &other);
  BigInt &operator>>=(int shift);
  BigInt &operator<<=(int shift);

  bool operator==(const BigInt &other) const;
  bool operator!=(const BigInt &other) const;
  bool operator<(const BigInt &other) const;
  bool operator>(const BigInt &other) const;
  bool operator<=(const BigInt &other) const;
  bool operator>=(const BigInt &other) const;

  friend std::ostream &operator<<(std::ostream &os, const BigInt &bi);
  friend BigInt abs(BigInt bigint);
  static BigInt factorial(BigInt n);
  static BigInt gcd(BigInt a, BigInt b);
  static BigInt lcm(BigInt a, BigInt b);
  static BigInt pow(BigInt base, BigInt exp);
  static BigInt randomBits(int bits);
  static BigInt randomRange(BigInt min, BigInt max);
};
