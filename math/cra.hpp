#ifndef CRA_HPP
#define CRA_HPP

#include "../common.hpp"
#include "extended_gcd.hpp"

#include <cassert>
#include <numeric>
#include <optional>
#include <utility>
#include <vector>

LIB_BEGIN

namespace detail {

std::optional<std::pair<long long, long long>> cra2(long long a0, long long m0, long long a1,
                                                    long long m1) {
  if (m0 < m1) return cra2(a1, m1, a0, m0);
  auto [x, d]  = inv_gcd(m0, m1);
  auto a1_a0   = a1 - a0; // assume `a0` < `m0` and `a1` < `m1`
  auto a1_a0_d = a1_a0 / d;
  if (a1_a0 != a1_a0_d * d) return {};
  auto m1_d = m1 / d;
  auto k0   = x % m1_d * (a1_a0_d % m1_d) % m1_d;
  if (k0 < 0) k0 += m1_d;
  return std::make_pair(a0 + k0 * m0, m0 * m1_d);
}

} // namespace detail

// Returns (remainder, modular)
std::optional<std::pair<long long, long long>> cra(const std::vector<long long> &a,
                                                   const std::vector<long long> &m) {
  const int n = static_cast<int>(a.size());
  assert(a.size() == m.size());
  auto safe_mod = [](long long a, long long m) { return a %= m, (a < 0 ? a + m : a); };
  long long A = 0, M = 1;
  for (int i = 0; i != n; ++i) {
    auto res = detail::cra2(safe_mod(a[i], m[i]), m[i], A, M);
    if (!res) return {};
    std::tie(A, M) = res.value();
  }
  return std::make_pair(A, M);
}

std::optional<std::pair<int, int>> cra_mod(const std::vector<int> &a, const std::vector<int> &m,
                                           const int modular) {
  const int n = static_cast<int>(a.size());
  assert(a.size() == m.size());
  auto safe_mod = [](int a, int m) { return a %= m, (a < 0 ? a + m : a); };
  std::vector<int> m_cpy(m);
  // check conflicts and make coprime
  for (int i = 0; i != n; ++i) {
    auto &&mi = m_cpy[i];
    for (int j = 0; j != i; ++j) {
      auto &&mj = m_cpy[j];
      auto d    = std::gcd(mi, mj);
      if (d == 1) continue;
      if (safe_mod(a[i], d) != safe_mod(a[j], d)) return {};
      mi /= d, mj /= d;
      if (auto k = std::gcd(mi, d); k != 1)
        while (d % k == 0) mi *= k, d /= k;
      mj *= d;
    }
  }
  m_cpy.push_back(modular);
  std::vector<int> pp(n + 1, 1), res(n + 1);
  for (int i = 0; i != n; ++i) {
    auto u = (safe_mod(a[i], m_cpy[i]) - res[i]) * inv_gcd(pp[i], m_cpy[i]).first % m_cpy[i];
    if (u < 0) u += m_cpy[i];
    for (int j = i + 1; j <= n; ++j)
      res[j] = (res[j] + u * pp[j]) % m_cpy[j],
      pp[j]  = static_cast<long long>(pp[j]) * m_cpy[i] % m_cpy[j];
  }
  return std::make_pair(res.back(), pp.back());
}

LIB_END

#endif