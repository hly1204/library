---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/extended_gcd.hpp
    title: Extended Euclidean Algorithm (in $\mathbb{Z}$)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yuki/math/187.0.test.cpp
    title: remote_test/yuki/math/187.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/cra.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\n#define\
    \ LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n#define LIB\
    \ ::lib::\n\n\n#line 1 \"math/extended_gcd.hpp\"\n\n\n\n#line 5 \"math/extended_gcd.hpp\"\
    \n\n#include <tuple>\n#include <utility>\n#include <vector>\n\nLIB_BEGIN\n\n//\
    \ Input:  integer `a` and `b`.\n// Output: (x, y, z) such that `a`x + `b`y = z\
    \ = gcd(`a`, `b`).\n[[deprecated]] std::tuple<long long, long long, long long>\
    \ ext_gcd(long long a, long long b) {\n  long long x11 = 1, x12 = 0, x21 = 0,\
    \ x22 = 1;\n  while (b != 0) {\n    long long q = a / b, x11_cpy = x11, x12_cpy\
    \ = x12, a_cpy = a;\n    x11 = x21, x21 = x11_cpy - q * x21;\n    x12 = x22, x22\
    \ = x12_cpy - q * x22;\n    a = b, b = a_cpy - q * b;\n  }\n  return std::make_tuple(x11,\
    \ x12, a);\n}\n\n// Input:  integer `a` and `b`.\n// Output: (x, gcd(`a`, `b`))\
    \ such that `a`x \u2261 gcd(`a`, `b`) (mod `b`).\nstd::pair<long long, long long>\
    \ inv_gcd(long long a, long long b) {\n  long long x11 = 1, x21 = 0;\n  while\
    \ (b != 0) {\n    long long q = a / b, x11_cpy = x11, a_cpy = a;\n    x11 = x21,\
    \ x21 = x11_cpy - q * x21;\n    a = b, b = a_cpy - q * b;\n  }\n  return std::make_pair(x11,\
    \ a);\n}\n\nnamespace detail {\n\ntemplate <typename ModIntT>\nclass modular_inverse\
    \ {\n  std::vector<ModIntT> ivs{ModIntT()};\n\n  enum : int { LIM = 1 << 20 };\n\
    \npublic:\n  modular_inverse() {}\n  ModIntT operator()(int k) {\n    // assume\
    \ `ModIntT::mod()` is prime.\n    if (k > LIM) return ModIntT(k).inv();\n    //\
    \ preprocess modular inverse from 1 to `k`\n    if (int n = static_cast<int>(ivs.size());\
    \ n <= k) {\n      int nn = n;\n      while (nn <= k) nn <<= 1;\n      ivs.resize(nn);\n\
    \      ModIntT v(1);\n      for (int i = n; i != nn; ++i) ivs[i] = v, v *= ModIntT(i);\n\
    \      v = v.inv();\n      for (int i = nn - 1; i >= n; --i) ivs[i] *= v, v *=\
    \ ModIntT(i);\n    }\n    return ivs[k];\n  }\n};\n\n} // namespace detail\n\n\
    LIB_END\n\n\n#line 6 \"math/cra.hpp\"\n\n#include <cassert>\n#include <numeric>\n\
    #include <optional>\n#line 12 \"math/cra.hpp\"\n\nLIB_BEGIN\n\nnamespace detail\
    \ {\n\nstd::optional<std::pair<long long, long long>> cra2(long long a0, long\
    \ long m0, long long a1,\n                                                   \
    \ long long m1) {\n  if (m0 < m1) return cra2(a1, m1, a0, m0);\n  auto [x, d]\
    \  = inv_gcd(m0, m1);\n  auto a1_a0   = a1 - a0; // assume `a0` < `m0` and `a1`\
    \ < `m1`\n  auto a1_a0_d = a1_a0 / d;\n  if (a1_a0 != a1_a0_d * d) return {};\n\
    \  auto m1_d = m1 / d;\n  auto k0   = x % m1_d * (a1_a0_d % m1_d) % m1_d;\n  if\
    \ (k0 < 0) k0 += m1_d;\n  return std::make_pair(a0 + k0 * m0, m0 * m1_d);\n}\n\
    \n} // namespace detail\n\n// Returns (remainder, modular)\nstd::optional<std::pair<long\
    \ long, long long>> cra(const std::vector<long long> &a,\n                   \
    \                                const std::vector<long long> &m) {\n  const int\
    \ n = static_cast<int>(a.size());\n  assert(a.size() == m.size());\n  auto safe_mod\
    \ = [](long long a, long long m) { return a %= m, (a < 0 ? a + m : a); };\n  long\
    \ long A = 0, M = 1;\n  for (int i = 0; i != n; ++i) {\n    auto res = detail::cra2(safe_mod(a[i],\
    \ m[i]), m[i], A, M);\n    if (!res) return {};\n    std::tie(A, M) = res.value();\n\
    \  }\n  return std::make_pair(A, M);\n}\n\nstd::optional<std::pair<int, int>>\
    \ cra_mod(const std::vector<int> &a, const std::vector<int> &m,\n            \
    \                               const int modular) {\n  const int n = static_cast<int>(a.size());\n\
    \  assert(a.size() == m.size());\n  auto safe_mod = [](int a, int m) { return\
    \ a %= m, (a < 0 ? a + m : a); };\n  std::vector<int> m_cpy(m);\n  // check conflicts\
    \ and make coprime\n  for (int i = 0; i != n; ++i) {\n    auto &&mi = m_cpy[i];\n\
    \    for (int j = 0; j != i; ++j) {\n      auto &&mj = m_cpy[j];\n      auto d\
    \    = std::gcd(mi, mj);\n      if (d == 1) continue;\n      if (safe_mod(a[i],\
    \ d) != safe_mod(a[j], d)) return {};\n      mi /= d, mj /= d;\n      if (auto\
    \ k = std::gcd(mi, d); k != 1)\n        while (d % k == 0) mi *= k, d /= k;\n\
    \      mj *= d;\n    }\n  }\n  m_cpy.push_back(modular);\n  std::vector<int> pp(n\
    \ + 1, 1), res(n + 1);\n  for (int i = 0; i != n; ++i) {\n    auto u = (safe_mod(a[i],\
    \ m_cpy[i]) - res[i]) * inv_gcd(pp[i], m_cpy[i]).first % m_cpy[i];\n    if (u\
    \ < 0) u += m_cpy[i];\n    for (int j = i + 1; j <= n; ++j)\n      res[j] = (res[j]\
    \ + u * pp[j]) % m_cpy[j],\n      pp[j]  = static_cast<long long>(pp[j]) * m_cpy[i]\
    \ % m_cpy[j];\n  }\n  return std::make_pair(res.back(), pp.back());\n}\n\nLIB_END\n\
    \n\n"
  code: "#ifndef CRA_HPP\n#define CRA_HPP\n\n#include \"../common.hpp\"\n#include\
    \ \"extended_gcd.hpp\"\n\n#include <cassert>\n#include <numeric>\n#include <optional>\n\
    #include <utility>\n#include <vector>\n\nLIB_BEGIN\n\nnamespace detail {\n\nstd::optional<std::pair<long\
    \ long, long long>> cra2(long long a0, long long m0, long long a1,\n         \
    \                                           long long m1) {\n  if (m0 < m1) return\
    \ cra2(a1, m1, a0, m0);\n  auto [x, d]  = inv_gcd(m0, m1);\n  auto a1_a0   = a1\
    \ - a0; // assume `a0` < `m0` and `a1` < `m1`\n  auto a1_a0_d = a1_a0 / d;\n \
    \ if (a1_a0 != a1_a0_d * d) return {};\n  auto m1_d = m1 / d;\n  auto k0   = x\
    \ % m1_d * (a1_a0_d % m1_d) % m1_d;\n  if (k0 < 0) k0 += m1_d;\n  return std::make_pair(a0\
    \ + k0 * m0, m0 * m1_d);\n}\n\n} // namespace detail\n\n// Returns (remainder,\
    \ modular)\nstd::optional<std::pair<long long, long long>> cra(const std::vector<long\
    \ long> &a,\n                                                   const std::vector<long\
    \ long> &m) {\n  const int n = static_cast<int>(a.size());\n  assert(a.size()\
    \ == m.size());\n  auto safe_mod = [](long long a, long long m) { return a %=\
    \ m, (a < 0 ? a + m : a); };\n  long long A = 0, M = 1;\n  for (int i = 0; i !=\
    \ n; ++i) {\n    auto res = detail::cra2(safe_mod(a[i], m[i]), m[i], A, M);\n\
    \    if (!res) return {};\n    std::tie(A, M) = res.value();\n  }\n  return std::make_pair(A,\
    \ M);\n}\n\nstd::optional<std::pair<int, int>> cra_mod(const std::vector<int>\
    \ &a, const std::vector<int> &m,\n                                           const\
    \ int modular) {\n  const int n = static_cast<int>(a.size());\n  assert(a.size()\
    \ == m.size());\n  auto safe_mod = [](int a, int m) { return a %= m, (a < 0 ?\
    \ a + m : a); };\n  std::vector<int> m_cpy(m);\n  // check conflicts and make\
    \ coprime\n  for (int i = 0; i != n; ++i) {\n    auto &&mi = m_cpy[i];\n    for\
    \ (int j = 0; j != i; ++j) {\n      auto &&mj = m_cpy[j];\n      auto d    = std::gcd(mi,\
    \ mj);\n      if (d == 1) continue;\n      if (safe_mod(a[i], d) != safe_mod(a[j],\
    \ d)) return {};\n      mi /= d, mj /= d;\n      if (auto k = std::gcd(mi, d);\
    \ k != 1)\n        while (d % k == 0) mi *= k, d /= k;\n      mj *= d;\n    }\n\
    \  }\n  m_cpy.push_back(modular);\n  std::vector<int> pp(n + 1, 1), res(n + 1);\n\
    \  for (int i = 0; i != n; ++i) {\n    auto u = (safe_mod(a[i], m_cpy[i]) - res[i])\
    \ * inv_gcd(pp[i], m_cpy[i]).first % m_cpy[i];\n    if (u < 0) u += m_cpy[i];\n\
    \    for (int j = i + 1; j <= n; ++j)\n      res[j] = (res[j] + u * pp[j]) % m_cpy[j],\n\
    \      pp[j]  = static_cast<long long>(pp[j]) * m_cpy[i] % m_cpy[j];\n  }\n  return\
    \ std::make_pair(res.back(), pp.back());\n}\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  - math/extended_gcd.hpp
  isVerificationFile: false
  path: math/cra.hpp
  requiredBy: []
  timestamp: '2022-05-15 01:09:52+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yuki/math/187.0.test.cpp
documentation_of: math/cra.hpp
layout: document
title: Chinese Remainder Algorithm (in $\mathbb{Z} / m \mathbb{Z}$)
---

## Garner's Algorithm

**Problem**: Solve the following system of linear congruence equation.

$$
\begin{cases}
x \equiv a_0 \pmod{m_0} \\
x \equiv a_1 \pmod{m_1} \\
\vdots \\
x \equiv a _ {n - 1} \pmod{m _ {n - 1}}
\end{cases}\tag{1}
$$

Consider the simplest problem which is

$$
\begin{cases}
x \equiv a_0 \pmod{m_0} \\
x \equiv a_1 \pmod{m_1}
\end{cases}\tag{2}
$$

We have $x = a_0 + k_0m_0 = a_1 + k_1m_1$, which implies $k_0m_0 - k_1m_1 = (a_1 - a_0)$. Let $d := \gcd(m_0, m_1)$. We know that $(2)$ has solution if and only if $d \mid (a_1 - a_0)$, and we could use extended Euclidean algorithm to compute $s,t$ such that

$$
sm_0 + tm_1 = d,
$$

so

$$
k_0 = s \cdot \frac{a_1 - a_0}{d}.
$$

and

$$
x \equiv a_0 + k_0m_0 \pmod{\operatorname{lcm}(m_0, m_1)}.
$$

## Bibliography

1. math314のブログ. [任意modでの畳み込み演算をO(n log(n))で](https://math314.hateblo.jp/entry/2015/05/07/014908).
