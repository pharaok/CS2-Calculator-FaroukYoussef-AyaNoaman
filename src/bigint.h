#include <ostream>
#include <vector>
typedef long long ll;
class BigInt {
private:
  std::vector<ll> digits;

public:
  BigInt(ll n);

  BigInt operator+(const BigInt &other);
  BigInt operator-(const BigInt &other);
  BigInt operator*(const BigInt &other);
  BigInt operator/(const BigInt &other);

  BigInt operator+=(const BigInt &other);
  BigInt operator-=(const BigInt &other);
  BigInt operator*=(const BigInt &other);
  BigInt operator/=(const BigInt &other);
};
