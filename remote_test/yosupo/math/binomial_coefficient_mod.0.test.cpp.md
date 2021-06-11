---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':question:'
    path: math/basic/binary_pow.hpp
    title: "binary power / \u5FEB\u901F\u5E42"
  - icon: ':heavy_check_mark:'
    path: math/basic/crt.hpp
    title: "Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
  - icon: ':question:'
    path: math/basic/exgcd.hpp
    title: "extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\
      \u6CD5"
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: "binomial coefficient mod / \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21"
  - icon: ':question:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient
  bundledCode: "#line 1 \"remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\n\
    #line 1 \"math/modulo/binomial_coefficient_mod.hpp\"\n\n\n\n/**\n * @brief binomial\
    \ coefficient mod / \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21\n *\n */\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <tuple>\n#include <vector>\n\n#line\
    \ 1 \"math/basic/binary_pow.hpp\"\n\n\n\n/**\n * @brief binary power / \u5FEB\u901F\
    \u5E42\n *\n */\n\n#line 10 \"math/basic/binary_pow.hpp\"\n#include <type_traits>\n\
    \n#line 1 \"traits/base.hpp\"\n\n\n\n/**\n * @brief type traits / \u7C7B\u578B\
    \u8403\u53D6\n *\n */\n\n#line 11 \"traits/base.hpp\"\n\nnamespace lib {\n\ntemplate\
    \ <typename Type> struct promote_integral;\ntemplate <> struct promote_integral<std::int32_t>\
    \ { using type = std::int64_t; };\ntemplate <> struct promote_integral<std::uint32_t>\
    \ { using type = std::uint64_t; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename\
    \ Type> using promote_integral_t = typename promote_integral<Type>::type;\n\n\
    template <typename T, typename U,\n          bool = (sizeof(T) > sizeof(U) ||\
    \ (sizeof(T) == sizeof(U) && std::is_signed_v<T>))>\nstruct longer_integral;\n\
    template <typename T, typename U> struct longer_integral<T, U, true> { using type\
    \ = T; };\ntemplate <typename T, typename U> struct longer_integral<T, U, false>\
    \ { using type = U; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename T, typename\
    \ U> using longer_integral_t = typename longer_integral<T, U>::type;\n\n} // namespace\
    \ lib\n\n\n#line 1 \"math/basic/binary_mul.hpp\"\n\n\n\n/**\n * @brief binary\
    \ multiplication / \u5FEB\u901F\u4E58\n *\n */\n\n#line 10 \"math/basic/binary_mul.hpp\"\
    \n\n#line 12 \"math/basic/binary_mul.hpp\"\n\nnamespace lib {\n\nnamespace internal\
    \ {\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>, T> mul_mod(T\
    \ x, T y, T mod) {\n  if ((x %= mod) < 0) x += mod;\n  if ((y %= mod) < 0) y +=\
    \ mod;\n  if constexpr (sizeof(T) < 8) {\n    return static_cast<T>(static_cast<promote_integral_t<T>>(x)\
    \ * y % mod);\n  } else {\n    T res = 0;\n    for (; y != 0; y >>= 1) {\n   \
    \   if ((y & 1) && (res += x) >= mod) res -= mod;\n      if ((x <<= 1) >= mod)\
    \ x -= mod;\n    }\n    return res;\n  }\n}\n\n} // namespace internal\n\ntemplate\
    \ <typename T1, typename T2, typename T3,\n          typename T = longer_integral_t<longer_integral_t<T1,\
    \ T2>, T3>>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3>, T>\nmul_mod(T1 x, T2 y, T3 mod) {\n  if constexpr\
    \ (std::is_signed_v<T1> || std::is_signed_v<T2>) {\n    return internal::mul_mod<std::make_signed_t<T>>(x,\
    \ y, mod);\n  } else {\n    return internal::mul_mod<T>(x, y, mod);\n  }\n}\n\n\
    } // namespace lib\n\n\n#line 14 \"math/basic/binary_pow.hpp\"\n\nnamespace lib\
    \ {\n\ntemplate <typename T1, typename T2>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, T1> pow(T1 x, T2 y) {\n  assert(y >= 0);\n  T1 res\
    \ = 1;\n  for (; y != 0; y >>= 1, x *= x)\n    if (y & 1) res *= x;\n  return\
    \ res;\n}\n\ntemplate <typename T1, typename T2, typename T3>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2> && std::is_integral_v<T3>, T1>\npow_mod(T1 x, T2 y,\
    \ T3 mod) {\n  assert(y >= 0);\n  T1 res = (mod != 1);\n  if constexpr (sizeof(T1)\
    \ < 8) {\n    using S = promote_integral_t<T1>;\n    for (; y != 0; y >>= 1, x\
    \ = static_cast<S>(x) * x % mod)\n      if (y & 1) res = static_cast<S>(res) *\
    \ x % mod;\n  } else {\n    // \u4F7F\u5F97 T1 \u4E3A 64 \u4F4D\u6574\u578B\u65F6\
    \u4E5F\u80FD\u5DE5\u4F5C\n    for (; y != 0; y >>= 1, x = mul_mod(x, x, mod))\n\
    \      if (y & 1) res = mul_mod(res, x, mod);\n  }\n  return res;\n}\n\n} // namespace\
    \ lib\n\n\n#line 1 \"math/basic/crt.hpp\"\n\n\n\n/**\n * @brief Chinese remainder\
    \ theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406\n *\n */\n\n#line 12 \"math/basic/crt.hpp\"\
    \n\n#line 1 \"math/basic/exgcd.hpp\"\n\n\n\n/**\n * @brief extended Euclidean\
    \ algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\u6CD5\n *\n */\n\n#line\
    \ 12 \"math/basic/exgcd.hpp\"\n\n#line 14 \"math/basic/exgcd.hpp\"\n\nnamespace\
    \ lib {\n\nnamespace internal {\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>,\
    \ T> gcd(T a, T b) {\n  while (b != 0) std::tie(a, b) = std::make_tuple(b, a %\
    \ b);\n  return a;\n}\n\ntemplate <typename T, typename S = std::make_signed_t<T>>\n\
    std::enable_if_t<std::is_integral_v<T>, std::tuple<T, S, S>> exgcd(T a, T b) {\n\
    \  S a_p = a, b_p = b, x1 = 1, x2 = 0, x3 = 0, x4 = 1;\n  while (b_p != 0) {\n\
    \    S q = a_p / b_p;\n    std::tie(x1, x2, x3, x4, a_p, b_p) =\n        std::make_tuple(x3,\
    \ x4, x1 - x3 * q, x2 - x4 * q, b_p, a_p - b_p * q);\n  }\n  return std::make_tuple(static_cast<T>(a_p),\
    \ x1, x2);\n}\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>,\
    \ T> inv_mod(T x, T mod) {\n  using S = std::make_signed_t<T>;\n  S a = x, b =\
    \ mod, x1 = 1, x3 = 0;\n  assert(a < b);\n  while (b != 0) {\n    S q = a / b;\n\
    \    std::tie(x1, x3, a, b) = std::make_tuple(x3, x1 - x3 * q, b, a - b * q);\n\
    \  }\n  assert(a == 1 && \"inv_mod_error\");\n  return static_cast<T>(x1 < 0 ?\
    \ x1 + mod : x1);\n}\n\n} // namespace internal\n\ntemplate <typename T1, typename\
    \ T2, typename T = longer_integral_t<T1, T2>>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, T> gcd(T1 a, T2 b) {\n  return internal::gcd<T>(a,\
    \ b);\n}\n\ntemplate <typename T1, typename T2, typename T = longer_integral_t<T1,\
    \ T2>,\n          typename S = std::make_signed_t<T>>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, std::tuple<T, S, S>>\nexgcd(T1 a, T2 b) {\n  return\
    \ internal::exgcd<T, S>(a, b);\n}\n\ntemplate <typename T1, typename T2, typename\
    \ T = longer_integral_t<T1, T2>>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>,\
    \ T> inv_mod(T1 x, T2 mod) {\n  return internal::inv_mod<T>(x, mod);\n}\n\n} //\
    \ namespace lib\n\n\n#line 15 \"math/basic/crt.hpp\"\n\nnamespace lib {\n\ntemplate\
    \ <typename T> class CoprimeCRT {\npublic:\n  using u64 = std::uint64_t;\n\n \
    \ CoprimeCRT() = default;\n\n  CoprimeCRT(const std::vector<T> &m) : m_(m), C_(m.size())\
    \ {\n    // \u5047\u8BBE m \u6570\u7EC4\u4E2D\u6240\u6709\u5143\u7D20\u7684\u4E58\
    \u79EF\u5728 std::int64_t \u8868\u793A\u8303\u56F4\u5185\n    int n = m_.size();\n\
    \    u64 prod = 1;\n    for (int i = 0; i < n; ++i) {\n      C_[i] = inv_mod(prod\
    \ % m_[i], m_[i]);\n      prod *= m_[i];\n    }\n  }\n\n  ~CoprimeCRT() = default;\n\
    \n  void set_m(const std::vector<T> &m) {\n    m_ = m;\n    int n = m_.size();\n\
    \    C_.resize(n);\n    u64 prod = 1;\n    for (int i = 0; i < n; ++i) {\n   \
    \   C_[i] = inv_mod(prod % m_[i], m_[i]);\n      prod *= m_[i];\n    }\n  }\n\n\
    \  u64 operator()(const std::vector<T> &v) const {\n    int n = m_.size();\n \
    \   assert(v.size() == n);\n    u64 x = 0, prod = 1;\n    for (int i = 0; i <\
    \ n; ++i) {\n      x += mul_mod(v[i] + m_[i] - x % m_[i], C_[i], m_[i]) * prod;\n\
    \      prod *= m_[i];\n    }\n    return x;\n  }\n\nprivate:\n  std::vector<T>\
    \ m_, C_;\n};\n\n// TODO\ntemplate <typename T> class CRT;\n\n} // namespace lib\n\
    \n\n#line 17 \"math/modulo/binomial_coefficient_mod.hpp\"\n\nnamespace lib {\n\
    \nclass BinomialCoefficientModSmall {\npublic:\n  using u32 = std::uint32_t;\n\
    \  using u64 = std::uint64_t;\n\n  /**\n   * @brief \u521B\u5EFA\u4E00\u4E2A\u65B0\
    \u7684\u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21\u9884\u5904\u7406\u5BF9\u8C61\
    \n   *\n   * @param mod \u7684\u7D20\u56E0\u6570\u5206\u89E3\u540E\u6240\u6709\
    \u7D20\u6570\u5E42\u6B21\u7684\u56E0\u6570\u548C\u4E0D\u80FD\u592A\u5927\n   */\n\
    \  BinomialCoefficientModSmall(u32 mod) {\n    for (u32 i = 2; i * i <= mod; ++i)\
    \ {\n      if (mod % i == 0) {\n        u32 e = 0, old_mod = mod;\n        do\
    \ {\n          ++e;\n          mod /= i;\n        } while (mod % i == 0);\n  \
    \      u32 ie = old_mod / mod;\n        factor_.push_back({i, e, ie, {}, {}});\n\
    \        auto &fac = std::get<3>(factor_.back());\n        auto &ifac = std::get<4>(factor_.back());\n\
    \        fac.resize(ie);\n        ifac.resize(ie);\n        if (e == 1) {\n  \
    \        fac[0] = ifac[0] = 1;\n          for (int j = 1; j != ie; ++j) fac[j]\
    \ = u64(fac[j - 1]) * j % ie;\n          ifac[ie - 1] = ie - 1; // Wilson's theorem\n\
    \          for (int j = ie - 2; j > 0; --j) ifac[j] = u64(ifac[j + 1]) * (j +\
    \ 1) % ie;\n        } else {\n          ifac[0] = fac[0] = 1;\n          for (int\
    \ j = 1; j != ie; ++j) {\n            fac[j] = (j % i == 0) ? fac[j - 1] : u64(fac[j\
    \ - 1]) * j % ie;\n            ifac[j] = u64(fac[j]) * ifac[j - 1] % ie;\n   \
    \       }\n          u32 ivie = inv_mod(ifac[ie - 1], ie);\n          for (int\
    \ j = ie - 1; j > 0; --j)\n            ifac[j] = u64(ivie) * ifac[j - 1] % ie,\
    \ ivie = u64(ivie) * fac[j] % ie;\n        }\n      }\n    }\n    if (mod != 1)\
    \ {\n      u32 ie = mod;\n      factor_.push_back({mod, 1, mod, {}, {}});\n  \
    \    auto &fac = std::get<3>(factor_.back());\n      auto &ifac = std::get<4>(factor_.back());\n\
    \      fac.resize(ie);\n      ifac.resize(ie);\n      fac[0] = ifac[0] = 1;\n\
    \      for (int j = 1; j != ie; ++j) fac[j] = u64(fac[j - 1]) * j % ie;\n    \
    \  ifac[ie - 1] = ie - 1; // Wilson's theorem\n      for (int j = ie - 2; j >\
    \ 0; --j) ifac[j] = u64(ifac[j + 1]) * (j + 1) % ie;\n    }\n    std::vector<u32>\
    \ factor(factor_.size());\n    for (int i = 0, e = factor_.size(); i < e; ++i)\
    \ factor[i] = std::get<2>(factor_[i]);\n    crt_.set_m(factor);\n  }\n\n  ~BinomialCoefficientModSmall()\
    \ = default;\n\n  /**\n   * @brief \u8FD4\u56DE nCm \u5BF9 mod \u53D6\u6A21\n\
    \   *\n   * @param n\n   * @param m\n   * @return u32\n   */\n  u32 operator()(u64\
    \ n, u64 m) const {\n    if (n < m) return 0;\n    std::vector<u32> v;\n    for\
    \ (auto &i : factor_) {\n      u32 p = std::get<0>(i), q = std::get<1>(i), pq\
    \ = std::get<2>(i);\n      const std::vector<u32> &fac = std::get<3>(i), &ifac\
    \ = std::get<4>(i);\n      u64 n_t = n, m_t = m, res = 1;\n      if (q == 1) {\n\
    \        for (; n_t; n_t /= p, m_t /= p) {\n          if (n_t % p < m_t % p) {\n\
    \            res = 0;\n            break;\n          }\n          res = res *\
    \ u64(fac[n_t % p]) % p * ifac[m_t % p] % p * ifac[n_t % p - m_t % p] % p;\n \
    \       }\n      } else {\n        u64 r = n_t - m_t, k = 0;\n        for (u64\
    \ n1 = n_t / p; n1; n1 /= p) k += n1;\n        for (u64 m1 = m_t / p; m1; m1 /=\
    \ p) k -= m1;\n        for (u64 r1 = r / p; r1; r1 /= p) k -= r1;\n        if\
    \ (k >= q) {\n          res = 0;\n        } else {\n          u32 pk = lib::pow(p,\
    \ k);\n          u64 is_negative = 0;\n          for (; n_t; n_t /= p, m_t /=\
    \ p, r /= p) {\n            res = res * fac[n_t % pq] % pq * ifac[m_t % pq] %\
    \ pq * ifac[r % pq] % pq;\n            is_negative += n_t / pq + m_t / pq + r\
    \ / pq;\n          }\n          if ((p == 2 && q >= 3) || (is_negative & 1) ==\
    \ 0)\n            res = res * pk % pq;\n          else\n            res = (pq\
    \ - res) * pk % pq;\n        }\n      }\n      v.push_back(res);\n    }\n    return\
    \ crt_(v);\n  }\n\nprivate:\n  std::vector<std::tuple<u32, u32, u32, std::vector<u32>,\
    \ std::vector<u32>>> factor_;\n  CoprimeCRT<u32> crt_;\n};\n\n} // namespace lib\n\
    \n\n#line 4 \"remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp\"\n\n\
    #include <iostream>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\"\
    , stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n  int t, m;\n  std::cin >> t >> m;\n  lib::BinomialCoefficientModSmall\
    \ bc(m);\n  while (t--) {\n    long long n, m;\n    std::cin >> n >> m;\n    std::cout\
    \ << bc(n, m) << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\
    \n#include \"math/modulo/binomial_coefficient_mod.hpp\"\n\n#include <iostream>\n\
    \nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int t, m;\n  std::cin >> t >> m;\n  lib::BinomialCoefficientModSmall bc(m);\n\
    \  while (t--) {\n    long long n, m;\n    std::cin >> n >> m;\n    std::cout\
    \ << bc(n, m) << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - math/modulo/binomial_coefficient_mod.hpp
  - math/basic/binary_pow.hpp
  - traits/base.hpp
  - math/basic/binary_mul.hpp
  - math/basic/crt.hpp
  - math/basic/exgcd.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-11 23:09:55+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
- /verify/remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp.html
title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
---
