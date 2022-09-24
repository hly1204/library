---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/integer_factorization.hpp
    title: Integer Factorization (Pollard's rho algorithm) (in $\mathbb{Z}$)
  - icon: ':heavy_check_mark:'
    path: math/random.hpp
    title: Pseudo Random Number Generator
  - icon: ':heavy_check_mark:'
    path: modint/runtime_long_montgomery_modint.hpp
    title: Runtime Long Montgomery ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/factorize
    links:
    - https://judge.yosupo.jp/problem/factorize
  bundledCode: "#line 1 \"remote_test/yosupo/math/factorize.0.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n\n#line 1 \"math/integer_factorization.hpp\"\
    \n\n\n\n#line 1 \"common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace\
    \ lib {\n#define LIB_END }\n#define LIB ::lib::\n\n\n#line 1 \"modint/runtime_long_montgomery_modint.hpp\"\
    \n\n\n\n#line 5 \"modint/runtime_long_montgomery_modint.hpp\"\n\n#ifdef LIB_DEBUG\n\
    \  #include <stdexcept>\n#endif\n#include <cstdint>\n#include <iostream>\n#include\
    \ <type_traits>\n\nLIB_BEGIN\n\ntemplate <int /* IdT */>\nclass runtime_montgomery_modint63\
    \ {\n  using u32 = std::uint32_t;\n  using i64 = std::int64_t;\n  using u64 =\
    \ std::uint64_t;\n\n  u64 v_{};\n\n  static inline u64 mul_high(u64 x, u64 y)\
    \ {\n    u64 a = x >> 32, b = static_cast<u32>(x), c = y >> 32, d = static_cast<u32>(y),\
    \ ad = a * d,\n        bc = b * c;\n    return a * c + (ad >> 32) + (bc >> 32)\
    \ +\n           (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);\n\
    \  }\n  static inline u64 redc_mul(u64 x, u64 y) {\n    u64 res = mul_high(x,\
    \ y) - mul_high(x * y * R, MOD);\n    return res + (MOD & -(res >> 63));\n  }\n\
    \  static inline u64 norm(i64 x) { return x + (MOD & -(x < 0)); }\n\n  static\
    \ u64 MOD, R, R2;\n  static i64 SMOD;\n\npublic:\n  static inline bool set_mod(u64\
    \ m) {\n    if ((m & 1) == 0 || m == 1 || m >> 63 != 0) return false;\n    MOD\
    \ = m;\n    {\n      // compute R\n      u64 t = 2, iv = MOD * (t - MOD * MOD);\n\
    \      iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;\n      R =\
    \ iv * (t - MOD * iv);\n    }\n    {\n      // compute R2\n      R2 = -MOD % MOD;\n\
    \      for (int i = 0; i != 64; ++i)\n        if ((R2 <<= 1) >= MOD) R2 -= MOD;\n\
    \    }\n    SMOD = static_cast<i64>(MOD);\n    return true;\n  }\n  static inline\
    \ u64 mod() { return MOD; }\n  static inline i64 smod() { return SMOD; }\n  runtime_montgomery_modint63()\
    \ {}\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int>\
    \ = 0>\n  runtime_montgomery_modint63(IntT v) : v_(redc_mul(norm(v % SMOD), R2))\
    \ {}\n  u64 val() const {\n    u64 res = -mul_high(v_ * R, MOD);\n    return res\
    \ + (MOD & -(res >> 63));\n  }\n  i64 sval() const { return val(); }\n  bool is_zero()\
    \ const { return v_ == 0; }\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  explicit operator IntT() const {\n    return static_cast<IntT>(val());\n\
    \  }\n  runtime_montgomery_modint63 operator-() const {\n    runtime_montgomery_modint63\
    \ res;\n    res.v_ = (MOD & -(v_ != 0)) - v_;\n    return res;\n  }\n  runtime_montgomery_modint63\
    \ inv() const {\n    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;\n    while (b !=\
    \ 0) {\n      i64 q = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n    if (a != 1)\
    \ throw std::runtime_error(\"modular inverse error\");\n#endif\n    return runtime_montgomery_modint63(x1);\n\
    \  }\n  runtime_montgomery_modint63 &operator+=(const runtime_montgomery_modint63\
    \ &rhs) {\n    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);\n    return *this;\n\
    \  }\n  runtime_montgomery_modint63 &operator-=(const runtime_montgomery_modint63\
    \ &rhs) {\n    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);\n    return *this;\n  }\n\
    \  runtime_montgomery_modint63 &operator*=(const runtime_montgomery_modint63 &rhs)\
    \ {\n    v_ = redc_mul(v_, rhs.v_);\n    return *this;\n  }\n  runtime_montgomery_modint63\
    \ &operator/=(const runtime_montgomery_modint63 &rhs) {\n    return operator*=(rhs.inv());\n\
    \  }\n  runtime_montgomery_modint63 pow(u64 e) const {\n    for (runtime_montgomery_modint63\
    \ res(1), x(*this);; x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1)\
    \ == 0) return res;\n    }\n  }\n  void swap(runtime_montgomery_modint63 &rhs)\
    \ {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_ = v;\n  }\n  friend runtime_montgomery_modint63\
    \ operator+(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) += rhs;\n  }\n  friend runtime_montgomery_modint63\
    \ operator-(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) -= rhs;\n  }\n  friend runtime_montgomery_modint63\
    \ operator*(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) *= rhs;\n  }\n  friend runtime_montgomery_modint63\
    \ operator/(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) /= rhs;\n  }\n  friend bool operator==(const\
    \ runtime_montgomery_modint63 &lhs,\n                         const runtime_montgomery_modint63\
    \ &rhs) {\n    return lhs.v_ == rhs.v_;\n  }\n  friend bool operator!=(const runtime_montgomery_modint63\
    \ &lhs,\n                         const runtime_montgomery_modint63 &rhs) {\n\
    \    return lhs.v_ != rhs.v_;\n  }\n  friend std::istream &operator>>(std::istream\
    \ &is, runtime_montgomery_modint63 &rhs) {\n    i64 x;\n    is >> x;\n    rhs\
    \ = runtime_montgomery_modint63(x);\n    return is;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &os, const runtime_montgomery_modint63 &rhs) {\n  \
    \  return os << rhs.val();\n  }\n};\n\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::u64\
    \ runtime_montgomery_modint63<IdT>::MOD;\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::u64\
    \ runtime_montgomery_modint63<IdT>::R;\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::u64\
    \ runtime_montgomery_modint63<IdT>::R2;\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::i64\
    \ runtime_montgomery_modint63<IdT>::SMOD;\n\ntemplate <int IdT>\nusing rmm63 =\
    \ runtime_montgomery_modint63<IdT>;\n\nLIB_END\n\n\n#line 1 \"math/random.hpp\"\
    \n\n\n\n#line 5 \"math/random.hpp\"\n\n#line 7 \"math/random.hpp\"\n#include <limits>\n\
    \nLIB_BEGIN\n\n// see https://prng.di.unimi.it/xoshiro256starstar.c\n// original\
    \ license CC0 1.0\nclass xoshiro256starstar {\n  using u64 = std::uint64_t;\n\n\
    \  static inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64 -\
    \ k)); }\n\n  u64 s_[4];\n\n  u64 next() {\n    const u64 res = rotl(s_[1] * 5,\
    \ 7) * 9;\n    const u64 t   = s_[1] << 17;\n    s_[2] ^= s_[0], s_[3] ^= s_[1],\
    \ s_[1] ^= s_[2], s_[0] ^= s_[3], s_[2] ^= t,\n        s_[3] = rotl(s_[3], 45);\n\
    \    return res;\n  }\n\npublic:\n  // see https://prng.di.unimi.it/splitmix64.c\n\
    \  // original license CC0 1.0\n  explicit xoshiro256starstar(u64 seed) {\n  \
    \  for (int i = 0; i != 4; ++i) {\n      u64 z = (seed += 0x9e3779b97f4a7c15);\n\
    \      z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n      z     = (z ^ (z >>\
    \ 27)) * 0x94d049bb133111eb;\n      s_[i] = z ^ (z >> 31);\n    }\n  }\n  // see\
    \ https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator\n  using\
    \ result_type = u64;\n  static constexpr u64 min() { return std::numeric_limits<u64>::min();\
    \ }\n  static constexpr u64 max() { return std::numeric_limits<u64>::max(); }\n\
    \  u64 operator()() { return next(); }\n};\n\nLIB_END\n\n\n#line 7 \"math/integer_factorization.hpp\"\
    \n\n#include <cassert>\n#include <map>\n#include <numeric>\n#include <random>\n\
    \nLIB_BEGIN\n\nnamespace detail {\n\ntemplate <template <int /* IdT */> typename\
    \ ModIntT>\nunsigned long long rho(unsigned long long n) {\n  using mint = ModIntT<-1>;\n\
    \  using u64  = unsigned long long;\n  xoshiro256starstar gen(std::random_device{}());\n\
    \  std::uniform_int_distribution<u64> dis(2, n - 1);\n  if (static_cast<u64>(mint::mod())\
    \ != n) mint::set_mod(n);\n  auto f = [R = mint(dis(gen))](mint x) { return x\
    \ * x + R; };\n  mint x, y(dis(gen)), ys, q(1);\n  u64 g       = 1;\n  const int\
    \ m = 128;\n  for (int r = 1; g == 1; r <<= 1) {\n    x = y;\n    for (int i =\
    \ 0; i < r; ++i) y = f(y);\n    for (int k = 0; g == 1 && k < r; k += m) {\n \
    \     ys = y;\n      for (int i = 0; i < m && i < r - k; ++i) q *= x - (y = f(y));\n\
    \      g = std::gcd(static_cast<u64>(q), n);\n    }\n  }\n  // clang-format off\n\
    \  if (g == n)\n    do { g = std::gcd(static_cast<u64>(x - (ys = f(ys))), n);\
    \ } while (g == 1);\n  // clang-format on\n  return g == n ? rho<ModIntT>(n) :\
    \ g;\n}\n\n} // namespace detail\n\nbool is_prime(unsigned long long n) {\n  //\
    \ Miller--Rabin test\n  if (n <= 2) return n == 2;\n  if ((n & 1) == 0) return\
    \ false;\n  if (n < 8) return true;\n  using mint = rmm63<-1>;\n  {\n    bool\
    \ okay = mint::set_mod(n);\n    assert(okay);\n  }\n  int t                = 0;\n\
    \  unsigned long long u = n - 1;\n  do { u >>= 1, ++t; } while ((u & 1) == 0);\n\
    \  for (int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {\n    if (n ==\
    \ static_cast<unsigned long long>(i)) return true;\n    mint x = mint(i).pow(u);\n\
    \    for (int j = 0; j != t && x != 1; ++j) {\n      mint y = x * x;\n      if\
    \ (x != -1 && y == 1) return false;\n      x = y;\n    }\n    if (x != 1) return\
    \ false;\n  }\n  return true;\n}\n\nnamespace detail {\n\nvoid factorize_odd(unsigned\
    \ long long n, std::map<unsigned long long, int> &mp) {\n  if (n < 2) return;\n\
    \  if (is_prime(n)) {\n    ++mp[n];\n    return;\n  }\n  auto g = rho<rmm63>(n);\n\
    \  factorize_odd(n / g, mp), factorize_odd(g, mp);\n}\n\n} // namespace detail\n\
    \nstd::map<unsigned long long, int> factorization(unsigned long long n) {\n  std::map<unsigned\
    \ long long, int> res;\n  if (n < 2) return res;\n  int t = 0;\n  while ((n &\
    \ 1) == 0) n >>= 1, ++t;\n  if (t) res[2] = t;\n  detail::factorize_odd(n, res);\n\
    \  return res;\n}\n\nLIB_END\n\n\n#line 4 \"remote_test/yosupo/math/factorize.0.test.cpp\"\
    \n\n#line 6 \"remote_test/yosupo/math/factorize.0.test.cpp\"\n#include <vector>\n\
    \nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int Q;\n  std::cin >> Q;\n  while (Q--) {\n    long long a;\n    std::cin >>\
    \ a;\n    std::vector<long long> factor;\n    auto mp = lib::factorization(a);\n\
    \    for (auto i : mp) {\n      for (int j = i.second; j > 0; --j) factor.push_back(i.first);\n\
    \    }\n    std::cout << factor.size() << ' ';\n    for (auto &&i : factor) std::cout\
    \ << i << ' ';\n    std::cout << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n\n#include\
    \ \"math/integer_factorization.hpp\"\n\n#include <iostream>\n#include <vector>\n\
    \nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int Q;\n  std::cin >> Q;\n  while (Q--) {\n    long long a;\n    std::cin >>\
    \ a;\n    std::vector<long long> factor;\n    auto mp = lib::factorization(a);\n\
    \    for (auto i : mp) {\n      for (int j = i.second; j > 0; --j) factor.push_back(i.first);\n\
    \    }\n    std::cout << factor.size() << ' ';\n    for (auto &&i : factor) std::cout\
    \ << i << ' ';\n    std::cout << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - math/integer_factorization.hpp
  - common.hpp
  - modint/runtime_long_montgomery_modint.hpp
  - common.hpp
  - math/random.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/factorize.0.test.cpp
  requiredBy: []
  timestamp: '2022-05-27 06:01:13+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/factorize.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/factorize.0.test.cpp
- /verify/remote_test/yosupo/math/factorize.0.test.cpp.html
title: remote_test/yosupo/math/factorize.0.test.cpp
---
