#pragma once

#include <ostream>
#include <string>
#include <vector>
class BigInt {
private:
  bool negative;
  std::vector<unsigned int> digits; // little-endian

public:
  BigInt(long long n = 0, bool negative = false);
  BigInt(std::vector<unsigned int> digits, bool negative = false);
  BigInt(std::string s);

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
};
