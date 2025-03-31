#include "bigint.h"
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

BigInt abs(BigInt bigint) { return BigInt(bigint.digits); }

BigInt::BigInt(long long d, bool neg) : negative(neg || d < 0) {
  d = abs(d);
  digits.push_back(d & numeric_limits<unsigned int>::max());
  if (d >> 32)
    digits.push_back(d >> 32);
}
BigInt::BigInt(vector<unsigned int> ds, bool neg) : negative(neg), digits(ds) {}
BigInt::BigInt(string s) : BigInt() {
  negative = s[0] == '-';
  if (negative || s[0] == '+')
    s = s.substr(1);

  int i;
  for (i = 0; i + 9 < s.length(); i += 9) {
    *this *= 1e9;
    *this += stoul(s.substr(i, 9));
  }
  *this *= pow(10, s.length() - i);
  *this += stoul(s.substr(i));
}
void BigInt::normalize() {
  while (digits.size() > 1 && digits.back() == 0)
    digits.pop_back();
}
BigInt BigInt::operator-() const { return BigInt(digits, !negative); }

void BigInt::addWithCarry(int i, unsigned long long c) {
  if (c == 0)
    return;
  if (i >= digits.size())
    digits.resize(i + 1);
  c += digits[i];
  digits[i] = c;
  addWithCarry(i + 1, c >> 32);
}
void BigInt::subWithBorrow(int i, unsigned long long b) {
  if (b == 0)
    return;
  if (i >= digits.size())
    digits.resize(i + 1);
  b = digits[i] - b;
  digits[i] = b;
  subWithBorrow(i + 1, b >> 32);
}

BigInt BigInt::operator+(const BigInt &other) const {
  if (negative != other.negative)
    return *this - -other;

  BigInt sum = *this;
  sum.digits.resize(max(digits.size(), other.digits.size()) + 1);
  for (int i = 0; i < other.digits.size(); i++)
    sum.addWithCarry(i, other.digits[i]);

  sum.normalize();
  return sum;
}
BigInt BigInt::operator-(const BigInt &other) const {
  if (negative != other.negative)
    return *this + -other;
  if (abs(*this) < abs(other))
    return -(other - *this);

  BigInt diff = *this;
  diff.digits.resize(max(digits.size(), other.digits.size()));
  for (int i = 0; i < other.digits.size(); i++)
    diff.subWithBorrow(i, other.digits[i]);

  diff.normalize();
  return diff;
}
BigInt BigInt::operator*(const BigInt &other) const {
  BigInt prod(vector<unsigned int>(digits.size() + other.digits.size(), 0));

  for (int i = 0; i < digits.size(); i++) {
    for (int j = 0; j < other.digits.size(); j++) {
      unsigned long long tmp =
          static_cast<unsigned long long>(digits[i]) * other.digits[j];
      prod.addWithCarry(i + j, tmp);
    }
  }

  prod.normalize();
  return prod;
}
BigInt BigInt::divmod(const BigInt &divisor, BigInt &remainder) const {
  // binary long division
  // https://en.wikipedia.org/wiki/Division_algorithm#Integer_division_(unsigned)_with_remainder

  remainder = 0;
  BigInt quotient;
  quotient.digits.resize(digits.size() + 4);
  for (int i = (digits.size() * 32) - 1; i >= 0; i--) {
    remainder <<= 1;
    remainder.digits[0] |= (digits[i / 32] >> (i % 32)) & 1;

    if (remainder >= divisor) {
      remainder -= divisor;
      quotient.digits[i / 32] |= 1 << (i % 32);
    }
  }

  quotient.negative = negative != divisor.negative;
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
  res.normalize();
  return res;
}
BigInt BigInt::operator<<(int shift) const {
  int wordShift = shift / 32;
  shift %= 32;
  BigInt res = *this;
  res.digits.insert(res.digits.begin(), wordShift, 0);
  res.digits.push_back(0);
  if (shift) {
    for (int i = res.digits.size() - 1; i >= 0; i--) {
      res.digits[i] <<= shift;
      if (i > 0)
        res.digits[i] |= res.digits[i - 1] >> (32 - shift);
    }
  }
  res.normalize();
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
    return abs(*this) == 0 && abs(other) == 0;

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

BigInt BigInt::factorial(BigInt n) {
  BigInt res = 1;
  for (BigInt i = 2; i <= n; i += 1)
    res *= i;
  return res;
}
