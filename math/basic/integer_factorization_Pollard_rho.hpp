#ifndef INTEGER_FACTORIZATION_POLLARD_RHO_HEADER_HPP
#define INTEGER_FACTORIZATION_POLLARD_RHO_HEADER_HPP

#include <cstdint>
#include <map>
#include <numeric>
#include <random>

#include "../../modint/runtime_long_Montgomery_modint.hpp"

namespace lib::internal {

// Pollard-rho 算法
// 一个不平凡的因子
std::uint64_t rho(std::uint64_t n) {
  using u64 = std::uint64_t;
  using m64 = RuntimeLongMontModInt<-1>;
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<u64> dis(2, n - 1);
  if (m64::get_mod() != n) m64::set_mod(n);
  const m64 R(dis(gen));
  auto f = [R](m64 x) -> m64 { return x * x + R; };
  m64 x, y(dis(gen)), ys, q(1);
  u64 g       = 1;
  const int m = 128;
  for (int r = 1; g == 1; r <<= 1) {
    x = y;
    for (int i = 0; i < r; ++i) y = f(y);
    for (int k = 0; g == 1 && k < r; k += m) {
      ys = y;
      for (int i = 0; i < m && i < r - k; ++i) q *= x - (y = f(y));
      g = std::gcd(u64(q), n);
    }
  }
  if (g == n) do
      g = std::gcd(u64(x - (ys = f(ys))), n);
    while (g == 1);
  return g == n ? rho(n) : g;
}

} // namespace lib::internal

namespace lib {

// Miller-Rabin 素性测试
// 假设广义黎曼假设成立
bool is_prime(std::uint64_t n) {
  if (n <= 2) return n == 2;
  if ((n & 1) == 0) return false;
  if (n < 8) return true;
  using m64 = RuntimeLongMontModInt<-1>;
  bool okay = m64::set_mod(n);
  assert(okay);
  int t           = 0;
  std::uint64_t u = n - 1;
  do u >>= 1, ++t;
  while ((u & 1) == 0);
  const m64 ONE(1), MINUS_ONE(n - 1);
  for (int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == i) return true;
    m64 x = m64(i).pow(u);
    for (int j = 0; j != t && x != ONE; ++j) {
      m64 y = x * x;
      if (x != MINUS_ONE && y == ONE) return false;
      x = y;
    }
    if (x != ONE) return false;
  }
  return true;
}

} // namespace lib

namespace lib::internal {

void factorize_odd(std::uint64_t n, std::map<std::uint64_t, int> &mp) {
  if (n < 2) return;
  if (is_prime(n)) {
    ++mp[n];
    return;
  }
  std::uint64_t g = rho(n);
  factorize_odd(n / g, mp);
  factorize_odd(g, mp);
}

} // namespace lib::internal

namespace lib {

std::map<std::uint64_t, int> factorize(std::uint64_t n) {
  std::map<std::uint64_t, int> res;
  if (n < 2) return res;
  int t = 0;
  while ((n & 1) == 0) n >>= 1, ++t;
  if (t) res[2] = t;
  internal::factorize_odd(n, res);
  return res;
}

} // namespace lib

#endif