---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_pow.hpp
    title: "binary power / \u5FEB\u901F\u5E42"
  - icon: ':heavy_check_mark:'
    path: math/basic/crt.hpp
    title: "Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
  - icon: ':heavy_check_mark:'
    path: math/basic/exgcd.hpp
    title: "extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\
      \u6CD5"
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: "binomial coefficient mod / \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21"
  - icon: ':heavy_check_mark:'
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
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\r\n\
    \r\n#line 1 \"math/modulo/binomial_coefficient_mod.hpp\"\n\n\n\r\n/**\r\n * @brief\
    \ binomial coefficient mod / \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21\r\n *\r\
    \n */\r\n\r\n#include <cassert>\r\n#include <cstdint>\r\n#include <tuple>\r\n\
    #include <vector>\r\n\r\n#line 1 \"math/basic/binary_pow.hpp\"\n\n\n\r\n/**\r\n\
    \ * @brief binary power / \u5FEB\u901F\u5E42\r\n *\r\n */\r\n\r\n#line 10 \"math/basic/binary_pow.hpp\"\
    \n#include <type_traits>\r\n\r\n#line 1 \"traits/base.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief type traits / \u7C7B\u578B\u8403\u53D6\r\n *\r\n */\r\n\r\n#line 11 \"\
    traits/base.hpp\"\n\r\nnamespace lib {\r\n\r\ntemplate <typename Type>\r\nstruct\
    \ promote_integral;\r\ntemplate <>\r\nstruct promote_integral<std::int32_t> {\r\
    \n  using type = std::int64_t;\r\n};\r\ntemplate <>\r\nstruct promote_integral<std::uint32_t>\
    \ {\r\n  using type = std::uint64_t;\r\n};\r\n\r\n// \u8F85\u52A9\u6A21\u677F\r\
    \ntemplate <typename Type>\r\nusing promote_integral_t = typename promote_integral<Type>::type;\r\
    \n\r\ntemplate <typename T, typename U>\r\nusing longer_integral_t =\r\n    std::conditional_t<(sizeof(T)\
    \ > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>)),\r\n       \
    \                T, U>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"math/basic/binary_mul.hpp\"\
    \n\n\n\r\n/**\r\n * @brief binary multiplication / \u5FEB\u901F\u4E58\r\n *\r\n\
    \ */\r\n\r\n#line 10 \"math/basic/binary_mul.hpp\"\n\r\n#line 12 \"math/basic/binary_mul.hpp\"\
    \n\r\nnamespace lib::internal {\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>\
    \ && sizeof(T) <= 4 && std::is_signed_v<T>, T>\r\nmul_mod(T x, T y, T mod) {\r\
    \n  T res = static_cast<T>(static_cast<promote_integral_t<T>>(x) * y % mod);\r\
    \n  return res < 0 ? res + mod : res;\r\n}\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>\
    \ && sizeof(T) <= 4 && std::is_unsigned_v<T>, T>\r\nmul_mod(T x, T y, T mod) {\r\
    \n  return static_cast<T>(static_cast<promote_integral_t<T>>(x) * y % mod);\r\n\
    }\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T> && (sizeof(T)\
    \ > 4) && std::is_unsigned_v<T>, T>\r\nmul_mod(T x, T y, T mod) {\r\n  x %= mod,\
    \ y %= mod;\r\n  T res = 0;\r\n  for (; y != 0; y >>= 1) {\r\n    if ((y & 1)\
    \ && (res += x) >= mod) res -= mod;\r\n    if ((x <<= 1) >= mod) x -= mod;\r\n\
    \  }\r\n  return res;\r\n}\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>\
    \ && (sizeof(T) > 4) && std::is_signed_v<T>, T>\r\nmul_mod(T x, T y, T mod) {\r\
    \n  if ((x %= mod) < 0) x += mod;\r\n  if ((y %= mod) < 0) y += mod;\r\n  T res\
    \ = 0;\r\n  for (; y != 0; y >>= 1) {\r\n    if ((y & 1) && (res += x) >= mod)\
    \ res -= mod;\r\n    if ((x <<= 1) >= mod) x -= mod;\r\n  }\r\n  return res;\r\
    \n}\r\n\r\n} // namespace lib::internal\r\n\r\nnamespace lib {\r\n\r\ntemplate\
    \ <typename T1, typename T2, typename T3,\r\n          typename T = longer_integral_t<longer_integral_t<T1,\
    \ T2>, T3>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3> &&\r\n                     (std::is_signed_v<T1> ||\
    \ std::is_signed_v<T2>),\r\n                 T>\r\nmul_mod(T1 x, T2 y, T3 mod)\
    \ {\r\n  return internal::mul_mod<std::make_signed_t<T>>(x, y, mod);\r\n}\r\n\r\
    \ntemplate <typename T1, typename T2, typename T3,\r\n          typename T = longer_integral_t<longer_integral_t<T1,\
    \ T2>, T3>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3> &&\r\n                     std::is_unsigned_v<T1>\
    \ && std::is_unsigned_v<T2>,\r\n                 T>\r\nmul_mod(T1 x, T2 y, T3\
    \ mod) {\r\n  return internal::mul_mod<T>(x, y, mod);\r\n}\r\n\r\n} // namespace\
    \ lib\r\n\r\n\n#line 14 \"math/basic/binary_pow.hpp\"\n\r\nnamespace lib {\r\n\
    \r\ntemplate <typename T1, typename T2>\r\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, T1> pow(T1 x, T2 y) {\r\n  assert(y >= 0);\r\n  T1\
    \ res = 1;\r\n  for (; y != 0; y >>= 1, x *= x)\r\n    if (y & 1) res *= x;\r\n\
    \  return res;\r\n}\r\n\r\ntemplate <typename T1, typename T2, typename T3, typename\
    \ T = longer_integral_t<T1, T3>>\r\nstd::enable_if_t<std::is_integral_v<T1> &&\
    \ std::is_integral_v<T2> && std::is_integral_v<T3>, T>\r\npow_mod(T1 x, T2 y,\
    \ T3 mod) {\r\n  assert(y >= 0);\r\n  T res = (mod != 1), tx = x;\r\n  for (;\
    \ y != 0; y >>= 1, tx = mul_mod(tx, tx, mod))\r\n    if (y & 1) res = mul_mod(res,\
    \ tx, mod);\r\n  return res;\r\n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"\
    math/basic/crt.hpp\"\n\n\n\r\n/**\r\n * @brief Chinese remainder theorem / \u4E2D\
    \u56FD\u5269\u4F59\u5B9A\u7406\r\n * @docs docs/math/basic/crt.md\r\n */\r\n\r\
    \n#line 11 \"math/basic/crt.hpp\"\n#include <optional>\r\n#line 13 \"math/basic/crt.hpp\"\
    \n\r\n#line 1 \"math/basic/exgcd.hpp\"\n\n\n\r\n/**\r\n * @brief extended Euclidean\
    \ algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\u6CD5\r\n *\r\n */\r\n\
    \r\n#line 12 \"math/basic/exgcd.hpp\"\n\r\n#line 14 \"math/basic/exgcd.hpp\"\n\
    \r\nnamespace lib::internal {\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>,\
    \ T> gcd(T a, T b) {\r\n  while (b != 0) std::tie(a, b) = std::make_tuple(b, a\
    \ % b);\r\n  return a;\r\n}\r\n\r\ntemplate <typename T, typename S = std::make_signed_t<T>>\r\
    \nstd::enable_if_t<std::is_integral_v<T>, std::tuple<T, S, S>> exgcd(T a, T b)\
    \ {\r\n  S a_p = a, b_p = b, x1 = 1, x2 = 0, x3 = 0, x4 = 1;\r\n  while (b_p !=\
    \ 0) {\r\n    S q = a_p / b_p;\r\n    std::tie(x1, x2, x3, x4, a_p, b_p) =\r\n\
    \        std::make_tuple(x3, x4, x1 - x3 * q, x2 - x4 * q, b_p, a_p - b_p * q);\r\
    \n  }\r\n  return std::make_tuple(static_cast<T>(a_p), x1, x2);\r\n}\r\n\r\ntemplate\
    \ <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>, T> inv_mod(T x, T mod)\
    \ {\r\n  using S = std::make_signed_t<T>;\r\n  S a = x, b = mod, x1 = 1, x3 =\
    \ 0;\r\n  assert(a < b);\r\n  while (b != 0) {\r\n    S q                    =\
    \ a / b;\r\n    std::tie(x1, x3, a, b) = std::make_tuple(x3, x1 - x3 * q, b, a\
    \ - b * q);\r\n  }\r\n  assert(a == 1 && \"inv_mod_error\");\r\n  return static_cast<T>(x1\
    \ < 0 ? x1 + mod : x1);\r\n}\r\n\r\n} // namespace lib::internal\r\n\r\nnamespace\
    \ lib {\r\n\r\ntemplate <typename T1, typename T2, typename T = longer_integral_t<T1,\
    \ T2>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T>\
    \ gcd(T1 a, T2 b) {\r\n  return internal::gcd<T>(a, b);\r\n}\r\n\r\ntemplate <typename\
    \ T1, typename T2, typename T = longer_integral_t<T1, T2>,\r\n          typename\
    \ S = std::make_signed_t<T>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>,\
    \ std::tuple<T, S, S>>\r\nexgcd(T1 a, T2 b) {\r\n  return internal::exgcd<T, S>(a,\
    \ b);\r\n}\r\n\r\ntemplate <typename T1, typename T2, typename T = longer_integral_t<T1,\
    \ T2>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T>\
    \ inv_mod(T1 x, T2 mod) {\r\n  return internal::inv_mod<T>(x, mod);\r\n}\r\n\r\
    \n} // namespace lib\r\n\r\n\n#line 16 \"math/basic/crt.hpp\"\n\r\nnamespace lib\
    \ {\r\n\r\n/**\r\n * @brief \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406\u5408\u5E76\u6A21\
    \u6570\u4E92\u7D20\u7684\u540C\u4F59\u5F0F\uFF08 Garner \u7B97\u6CD5\uFF09\r\n\
    \ * @note \u5982\u679C\u591A\u6B21\u5408\u5E76\u540C\u6837\u6A21\u6570\u7684\u53EF\
    \u4EE5\u9884\u5904\u7406\r\n */\r\ntemplate <typename T>\r\nclass CoprimeCRT {\r\
    \npublic:\r\n  using u64 = std::uint64_t;\r\n\r\n  CoprimeCRT() = default;\r\n\
    \r\n  /**\r\n   * @note \u5047\u8BBE m \u6570\u7EC4\u4E2D\u6240\u6709\u5143\u7D20\
    \u7684\u4E58\u79EF\u5728 std::int64_t \u8868\u793A\u8303\u56F4\u5185\r\n   */\r\
    \n  CoprimeCRT(const std::vector<T> &m) : m_(m), C_(m.size()) {\r\n    int n \
    \   = m_.size();\r\n    u64 prod = 1;\r\n    for (int i = 0; i < n; ++i) {\r\n\
    \      C_[i] = inv_mod(prod % m_[i], m_[i]);\r\n      prod *= m_[i];\r\n    }\r\
    \n  }\r\n\r\n  ~CoprimeCRT() = default;\r\n\r\n  void set_m(const std::vector<T>\
    \ &m) {\r\n    m_    = m;\r\n    int n = m_.size();\r\n    C_.resize(n);\r\n \
    \   u64 prod = 1;\r\n    for (int i = 0; i < n; ++i) {\r\n      C_[i] = inv_mod(prod\
    \ % m_[i], m_[i]);\r\n      prod *= m_[i];\r\n    }\r\n  }\r\n\r\n  u64 operator()(const\
    \ std::vector<T> &v) const {\r\n    int n = m_.size();\r\n    assert(v.size()\
    \ == n);\r\n    u64 x = 0, prod = 1;\r\n    for (int i = 0; i < n; ++i) {\r\n\
    \      x += mul_mod(v[i] + m_[i] - x % m_[i], C_[i], m_[i]) * prod;\r\n      prod\
    \ *= m_[i];\r\n    }\r\n    return x;\r\n  }\r\n\r\nprivate:\r\n  std::vector<T>\
    \ m_, C_;\r\n};\r\n\r\ntemplate <typename T>\r\nstd::optional<std::pair<std::uint64_t,\
    \ std::uint64_t>> crt2(T a1, T m1, T a2, T m2) {\r\n  using u64 = std::uint64_t;\r\
    \n  using i64 = std::int64_t;\r\n  using S   = std::make_signed_t<T>;\r\n\r\n\
    \  if (m1 < m2) return crt2(a2, m2, a1, m1);\r\n\r\n  S d, x, y;\r\n  std::tie(d,\
    \ x, y) = exgcd(m1, m2);\r\n  S a2_a1           = S(a2) - S(a1);\r\n  S a2_a1_d\
    \         = a2_a1 / d;\r\n  if (a2_a1 != a2_a1_d * d) return {};\r\n  S m2_d =\
    \ m2 / d;\r\n  S k1   = i64(x % m2_d) * (a2_a1_d % m2_d) % m2_d;\r\n  if (k1 <\
    \ 0) k1 += m2_d;\r\n  return std::make_pair(u64(k1) * m1 + a1, u64(m1) * m2_d);\r\
    \n}\r\n\r\n/**\r\n * @brief \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406\u5408\u5E76\u540C\
    \u4F59\u5F0F\r\n *\r\n * @tparam T \u5143\u7D20\u7C7B\u578B\r\n * @param v \u4F59\
    \u6570\r\n * @param m \u6A21\u6570\r\n * @return std::optional<std::pair<T, T>>\
    \ \u82E5\u65E0\u89E3\u5219\u8FD4\u56DE std::nullopt \u5426\u5219\u8FD4\u56DE (remainder,\
    \ modular)\r\n */\r\ntemplate <typename T>\r\nstd::optional<std::pair<std::uint64_t,\
    \ std::uint64_t>> crt(const std::vector<T> &v,\r\n                           \
    \                                const std::vector<T> &m) {\r\n  int n = v.size();\r\
    \n  assert(n == m.size());\r\n  std::uint64_t V = 0, M = 1;\r\n  for (int i =\
    \ 0; i < n; ++i) {\r\n    auto res = crt2<std::int64_t>(v[i], m[i], V, M);\r\n\
    \    if (!res) return {};\r\n    std::tie(V, M) = res.value();\r\n  }\r\n  return\
    \ std::make_pair(V, M);\r\n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 17 \"math/modulo/binomial_coefficient_mod.hpp\"\
    \n\r\nnamespace lib {\r\n\r\nclass BinomialCoefficientModSmall {\r\npublic:\r\n\
    \  using u32 = std::uint32_t;\r\n  using u64 = std::uint64_t;\r\n\r\n  /**\r\n\
    \   * @brief \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21\r\n   * @param mod \u7D20\
    \u56E0\u6570\u5206\u89E3\u540E\u6240\u6709\u7D20\u6570\u5E42\u6B21\u7684\u56E0\
    \u6570\u548C\u4E0D\u80FD\u592A\u5927\r\n   */\r\n  BinomialCoefficientModSmall(u32\
    \ mod) {\r\n    for (u32 i = 2; i * i <= mod; ++i) {\r\n      if (mod % i == 0)\
    \ {\r\n        u32 e = 0, old_mod = mod;\r\n        do {\r\n          ++e;\r\n\
    \          mod /= i;\r\n        } while (mod % i == 0);\r\n        u32 ie = old_mod\
    \ / mod;\r\n        factor_.push_back({i, e, ie, {}, {}});\r\n        auto &fac\
    \  = std::get<3>(factor_.back());\r\n        auto &ifac = std::get<4>(factor_.back());\r\
    \n        fac.resize(ie);\r\n        ifac.resize(ie);\r\n        if (e == 1) {\r\
    \n          fac[0] = ifac[0] = 1;\r\n          for (int j = 1; j != ie; ++j) fac[j]\
    \ = u64(fac[j - 1]) * j % ie;\r\n          ifac[ie - 1] = ie - 1; // Wilson's\
    \ theorem\r\n          for (int j = ie - 2; j > 0; --j) ifac[j] = u64(ifac[j +\
    \ 1]) * (j + 1) % ie;\r\n        } else {\r\n          ifac[0] = fac[0] = 1;\r\
    \n          for (int j = 1; j != ie; ++j) {\r\n            fac[j]  = (j % i ==\
    \ 0) ? fac[j - 1] : u64(fac[j - 1]) * j % ie;\r\n            ifac[j] = u64(fac[j])\
    \ * ifac[j - 1] % ie;\r\n          }\r\n          u32 ivie = inv_mod(ifac[ie -\
    \ 1], ie);\r\n          for (int j = ie - 1; j > 0; --j)\r\n            ifac[j]\
    \ = u64(ivie) * ifac[j - 1] % ie, ivie = u64(ivie) * fac[j] % ie;\r\n        }\r\
    \n      }\r\n    }\r\n    if (mod != 1) {\r\n      u32 ie = mod;\r\n      factor_.push_back({mod,\
    \ 1, mod, {}, {}});\r\n      auto &fac  = std::get<3>(factor_.back());\r\n   \
    \   auto &ifac = std::get<4>(factor_.back());\r\n      fac.resize(ie);\r\n   \
    \   ifac.resize(ie);\r\n      fac[0] = ifac[0] = 1;\r\n      for (int j = 1; j\
    \ != ie; ++j) fac[j] = u64(fac[j - 1]) * j % ie;\r\n      ifac[ie - 1] = ie -\
    \ 1; // Wilson's theorem\r\n      for (int j = ie - 2; j > 0; --j) ifac[j] = u64(ifac[j\
    \ + 1]) * (j + 1) % ie;\r\n    }\r\n    std::vector<u32> factor(factor_.size());\r\
    \n    for (int i = 0, e = factor_.size(); i < e; ++i) factor[i] = std::get<2>(factor_[i]);\r\
    \n    crt_.set_m(factor);\r\n  }\r\n\r\n  ~BinomialCoefficientModSmall() = default;\r\
    \n\r\n  /**\r\n   * @brief \u8FD4\u56DE nCm \u5BF9 mod \u53D6\u6A21\r\n   * @todo\
    \ \u6CE8\u610F\u8FD9\u91CC n \u8FD9\u4E2A\u4E0A\u6307\u6807\u53EF\u4EE5\u4E3A\u8D1F\
    \u6570\uFF0C\u4F46\u6211\u5E76\u672A\u5B9E\u73B0\r\n   * @param n\r\n   * @param\
    \ m\r\n   * @return u32\r\n   */\r\n  u32 operator()(u64 n, u64 m) const {\r\n\
    \    if (n < m) return 0;\r\n    std::vector<u32> v;\r\n    for (auto &i : factor_)\
    \ {\r\n      u32 p = std::get<0>(i), q = std::get<1>(i), pq = std::get<2>(i);\r\
    \n      const std::vector<u32> &fac = std::get<3>(i), &ifac = std::get<4>(i);\r\
    \n      u64 n_t = n, m_t = m, res = 1;\r\n      if (q == 1) {\r\n        for (;\
    \ n_t; n_t /= p, m_t /= p) {\r\n          if (n_t % p < m_t % p) {\r\n       \
    \     res = 0;\r\n            break;\r\n          }\r\n          res = res * u64(fac[n_t\
    \ % p]) % p * ifac[m_t % p] % p * ifac[n_t % p - m_t % p] % p;\r\n        }\r\n\
    \      } else {\r\n        u64 r = n_t - m_t, k = 0;\r\n        for (u64 n1 =\
    \ n_t / p; n1; n1 /= p) k += n1;\r\n        for (u64 m1 = m_t / p; m1; m1 /= p)\
    \ k -= m1;\r\n        for (u64 r1 = r / p; r1; r1 /= p) k -= r1;\r\n        if\
    \ (k >= q) {\r\n          res = 0;\r\n        } else {\r\n          u32 pk   \
    \       = lib::pow(p, k);\r\n          u64 is_negative = 0;\r\n          for (;\
    \ n_t; n_t /= p, m_t /= p, r /= p) {\r\n            res = res * fac[n_t % pq]\
    \ % pq * ifac[m_t % pq] % pq * ifac[r % pq] % pq;\r\n            is_negative +=\
    \ n_t / pq + m_t / pq + r / pq;\r\n          }\r\n          if ((p == 2 && q >=\
    \ 3) || (is_negative & 1) == 0) res = res * pk % pq;\r\n          else\r\n   \
    \         res = (pq - res) * pk % pq;\r\n        }\r\n      }\r\n      v.push_back(res);\r\
    \n    }\r\n    return crt_(v);\r\n  }\r\n\r\nprivate:\r\n  std::vector<std::tuple<u32,\
    \ u32, u32, std::vector<u32>, std::vector<u32>>> factor_;\r\n  CoprimeCRT<u32>\
    \ crt_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 4 \"remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp\"\
    \n\r\n#include <iostream>\r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"\
    in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  int t, m;\r\n  std::cin >> t >> m;\r\n  lib::BinomialCoefficientModSmall\
    \ bc(m);\r\n  while (t--) {\r\n    long long n, m;\r\n    std::cin >> n >> m;\r\
    \n    std::cout << bc(n, m) << '\\n';\r\n  }\r\n  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\r\
    \n\r\n#include \"math/modulo/binomial_coefficient_mod.hpp\"\r\n\r\n#include <iostream>\r\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int t, m;\r\n  std::cin >> t >> m;\r\n  lib::BinomialCoefficientModSmall bc(m);\r\
    \n  while (t--) {\r\n    long long n, m;\r\n    std::cin >> n >> m;\r\n    std::cout\
    \ << bc(n, m) << '\\n';\r\n  }\r\n  return 0;\r\n}"
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
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
- /verify/remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp.html
title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
---
