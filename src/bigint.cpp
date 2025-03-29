#include "bigint.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

BigInt abs(BigInt bigint) { return BigInt(bigint.digits); }

BigInt::BigInt(long long d, bool neg) : negative(neg || d < 0) {
  d = abs(d);
  digits.push_back(d & numeric_limits<unsigned int>::max());
  if (d > numeric_limits<unsigned int>::max())
    digits.push_back(d >> 32);
}
BigInt::BigInt(vector<unsigned int> ds, bool neg) : negative(neg), digits(ds) {}
BigInt::BigInt(string s) : BigInt() {
  negative = s[0] == '-';
  if (negative || s[0] == '+')
    s = s.substr(1);

  for (int i = s.size() - 1; i > 0; i -= 9) {
    *this *= 1e9;
    *this += stoul(s.substr(max(0, i - 8), min(9, i + 1)));
  }
}
void BigInt::normalize() {
  while (digits.size() > 1 && digits.back() == 0)
    digits.pop_back();
}
BigInt BigInt::operator-() const { return BigInt(digits, !negative); }

BigInt BigInt::operator+(const BigInt &other) const {
  if (negative != other.negative)
    return *this - -other;

  vector<unsigned int> ds;
  for (int i = 0; i < max(digits.size(), other.digits.size()); i++) {
    if (i >= ds.size())
      ds.push_back(0);
    ds[i] += digits[i] + other.digits[i];
    if (other.digits[i] >
        numeric_limits<unsigned int>::max() - digits[i]) // carry
    {
      if (i + 1 >= ds.size())
        ds.push_back(0);
      ds[i + 1] += 1;
    }
  }

  return BigInt(ds, negative);
}
BigInt BigInt::operator-(const BigInt &other) const {
  if (negative && other.negative)
    return -(-*this - -other);
  if (negative || other.negative)
    return *this + -other;
  if (abs(*this) < abs(other))
    return -(other - *this);

  vector<unsigned int> ds;
  for (int i = 0; i < max(digits.size(), other.digits.size()); i++) {
    if (i >= ds.size())
      ds.push_back(0);
    ds[i] += digits[i] - other.digits[i];
    if (digits[i] < other.digits[i]) // borrow
    {
      if (i + 1 >= ds.size())
        ds.push_back(0);
      ds[i + 1] -= 1;
    }
  }

  return BigInt(ds);
}
BigInt BigInt::operator*(const BigInt &other) const {
  vector<unsigned int> ds;
  for (int i = 0; i < digits.size(); i++) {
    for (int j = 0; j < other.digits.size(); j++) {
      if (i + j >= ds.size())
        ds.push_back(0);
      ds[i + j] += digits[i] * other.digits[j];
      if (1ull * digits[i] * other.digits[i] >
          numeric_limits<unsigned int>::max()) // carry
      {
        if (i + j + 1 >= ds.size())
          ds.push_back(0);
        ds[i + j + 1] += (1ull * digits[i] * other.digits[j]) >> 32;
      }
    }
  }

  return BigInt(ds, negative != other.negative);
}
BigInt BigInt::divmod(const BigInt &other, BigInt &remainder) const {
  // WARN: lol
  BigInt quotient;
  remainder = *this;
  while (remainder >= other) {
    remainder -= other;
    quotient += 1;
  }

  return quotient;
}
BigInt BigInt::operator/(const BigInt &other) const {
  BigInt remainder;
  return divmod(other, remainder);
}
BigInt BigInt::operator%(const BigInt &other) const {
  BigInt remainder;
  divmod(other, remainder);
  return remainder;
}

BigInt &BigInt::operator+=(const BigInt &other) {
  return (*this = *this + other);
}
BigInt &BigInt::operator-=(const BigInt &other) {
  return (*this = *this - other);
}
BigInt &BigInt::operator*=(const BigInt &other) {
  return (*this = *this * other);
}
BigInt &BigInt::operator/=(const BigInt &other) {
  return (*this = *this / other);
}

bool BigInt::operator==(const BigInt &other) const {
  if (negative != other.negative)
    return false;
  for (int i = 0; i < max(digits.size(), other.digits.size()); i++) {
    unsigned int d1 = i < digits.size() ? digits[i] : 0,
                 d2 = i < other.digits.size() ? other.digits[i] : 0;
    if (d1 != d2)
      return false;
  }
  return true;
}
bool BigInt::operator!=(const BigInt &other) const { return !(*this == other); }
bool BigInt::operator<(const BigInt &other) const {
  if (negative && other.negative)
    return -other < -(*this);
  if (negative)
    return true;
  if (other.negative)
    return false;

  for (int i = max(digits.size(), other.digits.size()) - 1; i >= 0; i--) {
    unsigned int d1 = i < digits.size() ? digits[i] : 0,
                 d2 = i < other.digits.size() ? other.digits[i] : 0;
    if (d1 < d2)
      return true;
    if (d1 > d2)
      return false;
  }

  return false;
}
bool BigInt::operator>(const BigInt &other) const { return (other < *this); }
bool BigInt::operator<=(const BigInt &other) const { return !(*this > other); }
bool BigInt::operator>=(const BigInt &other) const { return !(*this < other); }

ostream &operator<<(ostream &os, const BigInt &bi) {
  string digits;
  BigInt tmp, rem;
  for (tmp = abs(bi).divmod(1e9, rem); tmp > 0; tmp = tmp.divmod(1e9, rem))
    digits = to_string(rem.digits[0]) + digits;
  if (rem.digits[0] > 0)
    digits = to_string(rem.digits[0]) + digits;

  if (bi.negative)
    os << '-';
  os << digits;
  return os;
}
