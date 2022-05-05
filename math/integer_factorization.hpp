#ifndef INTEGER_FACTORIZATION_HPP
#define INTEGER_FACTORIZATION_HPP

#include "../common.hpp"
#include "../modint/runtime_long_montgomery_modint.hpp"

#include <cassert>
#include <cstdint>
#include <map>
#include <numeric>
#include <random>

LIB_BEGIN

namespace detail {

template <template <int /* IdT */> typename ModIntT>
std::uint64_t rho(std::uint64_t n) {
  using mint = ModIntT<-1>;
  using u64  = std::uint64_t;
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<u64> dis(2, n - 1);
  if (mint::mod() != n) mint::set_mod(n);
  auto f = [R = mint(dis(gen))](mint x) { return x * x + R; };
  mint x, y(dis(gen)), ys, q(1);
  u64 g       = 1;
  const int m = 128;
  for (int r = 1; g == 1; r <<= 1) {
    x = y;
    for (int i = 0; i < r; ++i) y = f(y);
    for (int k = 0; g == 1 && k < r; k += m) {
      ys = y;
      for (int i = 0; i < m && i < r - k; ++i) q *= x - (y = f(y));
      g = std::gcd(static_cast<u64>(q), n);
    }
  }
  if (g == n) {
    do { g = std::gcd(static_cast<u64>(x - (ys = f(ys))), n); } while (g == 1);
  }
  return g == n ? rho<ModIntT>(n) : g;
}

} // namespace detail

bool is_prime(std::uint64_t n) {
  // Miller-Rabin test
  if (n <= 2) return n == 2;
  if ((n & 1) == 0) return false;
  if (n < 8) return true;
  using mint = rmm63<-1>;
  {
    bool okay = mint::set_mod(n);
    assert(okay);
  }
  int t           = 0;
  std::uint64_t u = n - 1;
  do { u >>= 1, ++t; } while ((u & 1) == 0);
  for (int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == static_cast<std::uint64_t>(i)) return true;
    mint x = mint(i).pow(u);
    for (int j = 0; j != t && x != 1; ++j) {
      mint y = x * x;
      if (x != -1 && y == 1) return false;
      x = y;
    }
    if (x != 1) return false;
  }
  return true;
}

namespace detail {

void factorize_odd(std::uint64_t n, std::map<std::uint64_t, int> &mp) {
  if (n < 2) return;
  if (is_prime(n)) {
    ++mp[n];
    return;
  }
  auto g = rho<rmm63>(n);
  factorize_odd(n / g, mp), factorize_odd(g, mp);
}

} // namespace detail

std::map<std::uint64_t, int> factorization(std::uint64_t n) {
  std::map<std::uint64_t, int> res;
  if (n < 2) return res;
  int t = 0;
  while ((n & 1) == 0) n >>= 1, ++t;
  if (t) res[2] = t;
  detail::factorize_odd(n, res);
  return res;
}

LIB_END

#endif