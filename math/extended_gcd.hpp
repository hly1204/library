#ifndef EXTENDED_GCD_HPP
#define EXTENDED_GCD_HPP

#include "../common.hpp"

#include <tuple>
#include <utility>
#include <vector>

LIB_BEGIN

// Input:  integer `a` and `b`.
// Output: (x, y, z) such that `a`x + `b`y = z = gcd(`a`, `b`).
[[deprecated]] std::tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
  long long x11 = 1, x12 = 0, x21 = 0, x22 = 1;
  while (b != 0) {
    long long q = a / b, x11_cpy = x11, x12_cpy = x12, a_cpy = a;
    x11 = x21, x21 = x11_cpy - q * x21;
    x12 = x22, x22 = x12_cpy - q * x22;
    a = b, b = a_cpy - q * b;
  }
  return std::make_tuple(x11, x12, a);
}

// Input:  integer `a` and `b`.
// Output: (x, gcd(`a`, `b`)) such that `a`x ≡ gcd(`a`, `b`) (mod `b`).
std::pair<long long, long long> inv_gcd(long long a, long long b) {
  long long x11 = 1, x21 = 0;
  while (b != 0) {
    long long q = a / b, x11_cpy = x11, a_cpy = a;
    x11 = x21, x21 = x11_cpy - q * x21;
    a = b, b = a_cpy - q * b;
  }
  return std::make_pair(x11, a);
}

namespace detail {

template <typename ModIntT>
class modular_inverse {
  std::vector<ModIntT> ivs{ModIntT()};

  enum : int { LIM = 1 << 20 };

public:
  modular_inverse() {}
  ModIntT operator()(int k) {
    // assume `ModIntT::mod()` is prime.
    if (k > LIM) return ModIntT(k).inv();
    // preprocess modular inverse from 1 to `k`
    if (int n = static_cast<int>(ivs.size()); n <= k) {
      int nn = n;
      while (nn <= k) nn <<= 1;
      ivs.resize(nn);
      ModIntT v(1);
      for (int i = n; i != nn; ++i) ivs[i] = v, v *= ModIntT(i);
      v = v.inv();
      for (int i = nn - 1; i >= n; --i) ivs[i] *= v, v *= ModIntT(i);
    }
    return ivs[k];
  }
};

} // namespace detail

LIB_END

#endif