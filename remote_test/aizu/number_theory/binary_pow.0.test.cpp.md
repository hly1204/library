---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: modint/montgomery_modint.hpp
    title: Montgomery ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B
  bundledCode: "#line 1 \"remote_test/aizu/number_theory/binary_pow.0.test.cpp\"\n\
    #define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B\"\
    \n\n#line 1 \"modint/montgomery_modint.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\
    \n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n\
    #define LIB ::lib::\n\n\n#line 5 \"modint/montgomery_modint.hpp\"\n\n#ifdef LIB_DEBUG\n\
    \  #include <stdexcept>\n#endif\n#include <cstdint>\n#include <iostream>\n#include\
    \ <type_traits>\n\nLIB_BEGIN\n\ntemplate <std::uint32_t ModT>\nclass montgomery_modint30\
    \ {\n  using i32 = std::int32_t;\n  using u32 = std::uint32_t;\n  using u64 =\
    \ std::uint64_t;\n\n  u32 v_{};\n\n  static constexpr u32 get_r() {\n    u32 t\
    \ = 2, iv = MOD * (t - MOD * MOD);\n    iv *= t - MOD * iv, iv *= t - MOD * iv;\n\
    \    return iv * (MOD * iv - t);\n  }\n  static constexpr u32 redc(u64 x) {\n\
    \    return (x + static_cast<u64>(static_cast<u32>(x) * R) * MOD) >> 32;\n  }\n\
    \  static constexpr u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31));\
    \ }\n\n  static constexpr u32 MOD  = ModT;\n  static constexpr u32 MOD2 = MOD\
    \ << 1;\n  static constexpr u32 R    = get_r();\n  static constexpr u32 R2   =\
    \ -static_cast<u64>(MOD) % MOD;\n  static constexpr i32 SMOD = static_cast<i32>(MOD);\n\
    \n  static_assert(MOD & 1);\n  static_assert(-R * MOD == 1);\n  static_assert((MOD\
    \ >> 30) == 0);\n  static_assert(MOD != 1);\n\npublic:\n  static constexpr u32\
    \ mod() { return MOD; }\n  static constexpr i32 smod() { return SMOD; }\n  constexpr\
    \ montgomery_modint30() {}\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  constexpr montgomery_modint30(IntT v) : v_(redc(static_cast<u64>(v\
    \ % SMOD + SMOD) * R2)) {}\n  constexpr u32 val() const { return norm(redc(v_));\
    \ }\n  constexpr i32 sval() const { return norm(redc(v_)); }\n  constexpr bool\
    \ is_zero() const { return v_ == 0 || v_ == MOD; }\n  template <typename IntT,\
    \ std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  explicit constexpr operator\
    \ IntT() const {\n    return static_cast<IntT>(val());\n  }\n  constexpr montgomery_modint30\
    \ operator-() const {\n    montgomery_modint30 res;\n    res.v_ = (MOD2 & -(v_\
    \ != 0)) - v_;\n    return res;\n  }\n  constexpr montgomery_modint30 inv() const\
    \ {\n    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;\n    while (b != 0) {\n   \
    \   i32 q = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old - x3 *\
    \ q, a = b, b = a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n    if (a != 1) throw\
    \ std::runtime_error(\"modular inverse error\");\n#endif\n    return montgomery_modint30(x1);\n\
    \  }\n  constexpr montgomery_modint30 &operator+=(const montgomery_modint30 &rhs)\
    \ {\n    v_ += rhs.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);\n    return *this;\n \
    \ }\n  constexpr montgomery_modint30 &operator-=(const montgomery_modint30 &rhs)\
    \ {\n    v_ -= rhs.v_, v_ += MOD2 & -(v_ >> 31);\n    return *this;\n  }\n  constexpr\
    \ montgomery_modint30 &operator*=(const montgomery_modint30 &rhs) {\n    v_ =\
    \ redc(static_cast<u64>(v_) * rhs.v_);\n    return *this;\n  }\n  constexpr montgomery_modint30\
    \ &operator/=(const montgomery_modint30 &rhs) {\n    return operator*=(rhs.inv());\n\
    \  }\n  constexpr montgomery_modint30 pow(u64 e) const {\n    for (montgomery_modint30\
    \ res(1), x(*this);; x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1)\
    \ == 0) return res;\n    }\n  }\n  constexpr void swap(montgomery_modint30 &rhs)\
    \ {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_ = v;\n  }\n  friend constexpr montgomery_modint30\
    \ operator+(const montgomery_modint30 &lhs,\n                                \
    \                 const montgomery_modint30 &rhs) {\n    return montgomery_modint30(lhs)\
    \ += rhs;\n  }\n  friend constexpr montgomery_modint30 operator-(const montgomery_modint30\
    \ &lhs,\n                                                 const montgomery_modint30\
    \ &rhs) {\n    return montgomery_modint30(lhs) -= rhs;\n  }\n  friend constexpr\
    \ montgomery_modint30 operator*(const montgomery_modint30 &lhs,\n            \
    \                                     const montgomery_modint30 &rhs) {\n    return\
    \ montgomery_modint30(lhs) *= rhs;\n  }\n  friend constexpr montgomery_modint30\
    \ operator/(const montgomery_modint30 &lhs,\n                                \
    \                 const montgomery_modint30 &rhs) {\n    return montgomery_modint30(lhs)\
    \ /= rhs;\n  }\n  friend constexpr bool operator==(const montgomery_modint30 &lhs,\
    \ const montgomery_modint30 &rhs) {\n    return norm(lhs.v_) == norm(rhs.v_);\n\
    \  }\n  friend constexpr bool operator!=(const montgomery_modint30 &lhs, const\
    \ montgomery_modint30 &rhs) {\n    return norm(lhs.v_) != norm(rhs.v_);\n  }\n\
    \  friend std::istream &operator>>(std::istream &is, montgomery_modint30 &rhs)\
    \ {\n    i32 x;\n    is >> x;\n    rhs = montgomery_modint30(x);\n    return is;\n\
    \  }\n  friend std::ostream &operator<<(std::ostream &os, const montgomery_modint30\
    \ &rhs) {\n    return os << rhs.val();\n  }\n};\n\ntemplate <std::uint32_t ModT>\n\
    using mm30 = montgomery_modint30<ModT>;\n\nLIB_END\n\n\n#line 4 \"remote_test/aizu/number_theory/binary_pow.0.test.cpp\"\
    \n\n#line 6 \"remote_test/aizu/number_theory/binary_pow.0.test.cpp\"\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int n, m;\n  std::cin >> n >> m;\n  std::cout << lib::mm30<1000000007>(n).pow(m)\
    \ << '\\n';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B\"\
    \n\n#include \"modint/montgomery_modint.hpp\"\n\n#include <iostream>\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int n, m;\n  std::cin >> n >> m;\n  std::cout << lib::mm30<1000000007>(n).pow(m)\
    \ << '\\n';\n  return 0;\n}"
  dependsOn:
  - modint/montgomery_modint.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/aizu/number_theory/binary_pow.0.test.cpp
  requiredBy: []
  timestamp: '2022-04-26 01:17:42+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizu/number_theory/binary_pow.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizu/number_theory/binary_pow.0.test.cpp
- /verify/remote_test/aizu/number_theory/binary_pow.0.test.cpp.html
title: remote_test/aizu/number_theory/binary_pow.0.test.cpp
---
