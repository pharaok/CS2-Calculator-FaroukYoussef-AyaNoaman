#include "bigint.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
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
      unsigned long long tmp =
          static_cast<unsigned long long>(digits[i]) * other.digits[j];
      ds[i + j] += tmp & numeric_limits<unsigned int>::max();
      if (tmp >> 32) {
        if (i + j + 1 >= ds.size())
          ds.push_back(0);
        ds[i + j + 1] += tmp >> 32;
      }
    }
  }

  return BigInt(ds, negative != other.negative);
}
BigInt BigInt::divmod(const BigInt &other, BigInt &remainder) const {
  // binary long division
  remainder = 0;
  BigInt quotient, dividend = abs(*this), divisor = abs(other);
  quotient.digits.resize(digits.size());
  for (int i = digits.size() * 32 - 1; i >= 0; i--) {
    remainder <<= 1;
    remainder.digits[0] |= (dividend.digits[i / 32] >> (i % 32)) & 1;
    if (remainder >= divisor) {
      remainder -= divisor;
      quotient.digits[i / 32] |= 1 << (i % 32);
    }
  }

  quotient.negative = negative != other.negative;
  remainder.negative = negative;
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
BigInt BigInt::operator>>(int shift) const {
  int wordShift = shift / 32;
  shift %= 32;
  BigInt res = *this;
  res.digits.erase(res.digits.begin(), res.digits.begin() + wordShift);
  if (shift) {
    for (int i = 0; i < res.digits.size(); i++) {
      res.digits[i] >>= shift;
      if (i + 1 < res.digits.size())
        res.digits[i] |= (res.digits[i + 1] & ((1 << shift) - 1))
                         << (32 - shift);
    }
  }
  return res;
}
BigInt BigInt::operator<<(int shift) const {
  int wordShift = shift / 32;
  shift %= 32;
  BigInt res = *this;
  res.digits.insert(res.digits.begin(), wordShift, 0);
  if (shift) {
    for (int i = res.digits.size() - 1; i >= 0; i--) {
      res.digits[i] <<= shift;
      if (i > 0)
        res.digits[i] |= res.digits[i - 1] >> (32 - shift);
    }
  }
  return res;
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
BigInt &BigInt::operator%=(const BigInt &other) {
  return (*this = *this % other);
}
BigInt &BigInt::operator>>=(int shift) { return (*this = *this >> shift); }
BigInt &BigInt::operator<<=(int shift) { return (*this = *this << shift); }

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
  BigInt tmp, rem;
  string digits;

  for (tmp = abs(bi).divmod(1e9, rem); tmp > 0; tmp = tmp.divmod(1e9, rem)) {
    stringstream ss;
    ss << setw(9) << setfill('0') << rem.digits[0];
    digits = ss.str() + digits;
  }
  if (rem.digits[0] != 0) {
    stringstream ss;
    ss << rem.digits[0];
    digits = ss.str() + digits;
  }

  if (bi.negative)
    os << '-';
  os << digits;
  return os;
}
