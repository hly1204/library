---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: math/random.hpp
    title: Pseudo Random Number Generator
  - icon: ':question:'
    path: math/sqrt_mod.hpp
    title: Square Roots (in $\mathbb{F} _ p$)
  - icon: ':heavy_check_mark:'
    path: modint/runtime_modint.hpp
    title: Runtime ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"remote_test/yosupo/math/sqrt_mod.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#line 1 \"math/sqrt_mod.hpp\"\
    \n\n\n\n#line 1 \"common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace\
    \ lib {\n#define LIB_END }\n#define LIB ::lib::\n\n\n#line 1 \"math/random.hpp\"\
    \n\n\n\n#line 5 \"math/random.hpp\"\n\n#include <cstdint>\n#include <limits>\n\
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
    \  u64 operator()() { return next(); }\n};\n\nLIB_END\n\n\n#line 6 \"math/sqrt_mod.hpp\"\
    \n\n#include <random>\n#include <type_traits>\n#include <vector>\n\nLIB_BEGIN\n\
    \ntemplate <typename ModIntT>\nstd::vector<ModIntT> sqrt_mod_prime(ModIntT a)\
    \ {\n  // Bostan--Mori's algorithm\n  const auto p = ModIntT::mod();\n  if (p\
    \ == 2 || a.is_zero()) return {a};\n  if (a.pow(p >> 1) == -1) return {};\n  if\
    \ ((p & 3) == 3) {\n    ModIntT b(a.pow((p + 1) >> 2));\n    return {b, -b};\n\
    \  }\n  xoshiro256starstar gen(std::random_device{}());\n  std::uniform_int_distribution<std::decay_t<decltype(p)>>\
    \ dis(2, p - 1);\n  ModIntT t;\n  do { t = dis(gen); } while ((t * t - 4 * a).pow(p\
    \ >> 1) != -1);\n  ModIntT k0(1), k1, k2(-t), k3(a);\n  for (auto e = (p + 1)\
    \ >> 1;;) {\n    // clang-format off\n    if (e & 1) k0 = k1 - k0 * k2, k1 *=\
    \ k3;\n    else k1 = k0 * k3 - k1 * k2;\n    // clang-format on\n    if ((e >>=\
    \ 1) == 0) return {k0, -k0};\n    k2 = k3 + k3 - k2 * k2, k3 *= k3;\n  }\n}\n\n\
    LIB_END\n\n\n#line 1 \"modint/runtime_modint.hpp\"\n\n\n\n#line 5 \"modint/runtime_modint.hpp\"\
    \n\n#ifdef LIB_DEBUG\n  #include <stdexcept>\n#endif\n#line 10 \"modint/runtime_modint.hpp\"\
    \n#include <iostream>\n#line 12 \"modint/runtime_modint.hpp\"\n\nLIB_BEGIN\n\n\
    template <int /* IdT */>\nclass runtime_modint31 {\n  using i32 = std::int32_t;\n\
    \  using u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n\n  u32 v_{};\n\n\
    \  static inline u32 norm(i32 x) { return x + (-(x < 0) & MOD); }\n  static inline\
    \ u32 redc(u64 x) {\n    u32 t = (x + static_cast<u64>(static_cast<u32>(x) * R)\
    \ * MOD_ODD) >> 32;\n    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));\n\
    \  }\n  static inline u32 tsf(u32 x) {\n    return redc(static_cast<u64>(x % MOD_ODD)\
    \ * R2) << OFFSET | (x & MASK);\n  }\n\n  static u32 R, R2, MOD, MOD_ODD, OFFSET,\
    \ MASK;\n  static i32 SMOD;\n\npublic:\n  static inline bool set_mod(u32 m) {\n\
    \    if (m == 1 || m >> 31 != 0) return false;\n    for (MOD = MOD_ODD = m, OFFSET\
    \ = 0; (MOD_ODD & 1) == 0; ++OFFSET, MOD_ODD >>= 1) {}\n    MASK = (1 << OFFSET)\
    \ - 1, SMOD = static_cast<i32>(MOD);\n    {\n      // compute R\n      u32 t =\
    \ 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);\n      iv *= t - MOD_ODD * iv, iv\
    \ *= t - MOD_ODD * iv;\n      R = iv * (MOD_ODD * iv - t);\n    }\n    // compute\
    \ R2\n    R2 = -static_cast<u64>(MOD_ODD) % MOD_ODD;\n    return true;\n  }\n\
    \  static inline u32 mod() { return MOD; }\n  static inline i32 smod() { return\
    \ SMOD; }\n  runtime_modint31() {}\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  runtime_modint31(IntT v) : v_(tsf(norm(v % SMOD))) {}\n  u32 val()\
    \ const {\n    u32 h = redc(v_ >> OFFSET);\n    return ((h - v_) * R & MASK) *\
    \ MOD_ODD + h;\n  }\n  i32 sval() const { return val(); }\n  bool is_zero() const\
    \ { return v_ == 0; }\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  explicit operator IntT() const {\n    return static_cast<IntT>(val());\n\
    \  }\n  runtime_modint31 operator-() const {\n    runtime_modint31 res;\n    u32\
    \ h  = v_ >> OFFSET;\n    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-v_\
    \ & MASK);\n    return res;\n  }\n  runtime_modint31 inv() const {\n    i32 x1\
    \ = 1, x3 = 0, a = sval(), b = SMOD;\n    while (b != 0) {\n      i32 q = a /\
    \ b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b =\
    \ a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n    if (a != 1) throw std::runtime_error(\"\
    modular inverse error\");\n#endif\n    return runtime_modint31(x1);\n  }\n  runtime_modint31\
    \ &operator+=(const runtime_modint31 &rhs) {\n    u32 h = (v_ >> OFFSET) + (rhs.v_\
    \ >> OFFSET) - MOD_ODD;\n    v_    = ((h + (MOD_ODD & -(h >> 31))) << OFFSET)\
    \ | ((v_ + rhs.v_) & MASK);\n    return *this;\n  }\n  runtime_modint31 &operator-=(const\
    \ runtime_modint31 &rhs) {\n    u32 h = (v_ >> OFFSET) - (rhs.v_ >> OFFSET);\n\
    \    v_    = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ - rhs.v_) & MASK);\n\
    \    return *this;\n  }\n  runtime_modint31 &operator*=(const runtime_modint31\
    \ &rhs) {\n    v_ = (redc(static_cast<u64>(v_ >> OFFSET) * (rhs.v_ >> OFFSET))\
    \ << OFFSET) |\n         ((v_ * rhs.v_) & MASK);\n    return *this;\n  }\n  runtime_modint31\
    \ &operator/=(const runtime_modint31 &rhs) { return operator*=(rhs.inv()); }\n\
    \  runtime_modint31 pow(u64 e) const {\n    for (runtime_modint31 res(1), x(*this);;\
    \ x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1) == 0) return res;\n\
    \    }\n  }\n  void swap(runtime_modint31 &rhs) {\n    auto v = v_;\n    v_ =\
    \ rhs.v_, rhs.v_ = v;\n  }\n  friend runtime_modint31 operator+(const runtime_modint31\
    \ &lhs, const runtime_modint31 &rhs) {\n    return runtime_modint31(lhs) += rhs;\n\
    \  }\n  friend runtime_modint31 operator-(const runtime_modint31 &lhs, const runtime_modint31\
    \ &rhs) {\n    return runtime_modint31(lhs) -= rhs;\n  }\n  friend runtime_modint31\
    \ operator*(const runtime_modint31 &lhs, const runtime_modint31 &rhs) {\n    return\
    \ runtime_modint31(lhs) *= rhs;\n  }\n  friend runtime_modint31 operator/(const\
    \ runtime_modint31 &lhs, const runtime_modint31 &rhs) {\n    return runtime_modint31(lhs)\
    \ /= rhs;\n  }\n  friend bool operator==(const runtime_modint31 &lhs, const runtime_modint31\
    \ &rhs) {\n    return lhs.v_ == rhs.v_;\n  }\n  friend bool operator!=(const runtime_modint31\
    \ &lhs, const runtime_modint31 &rhs) {\n    return lhs.v_ != rhs.v_;\n  }\n  friend\
    \ std::istream &operator>>(std::istream &is, runtime_modint31 &rhs) {\n    i32\
    \ x;\n    is >> x;\n    rhs = runtime_modint31(x);\n    return is;\n  }\n  friend\
    \ std::ostream &operator<<(std::ostream &os, const runtime_modint31 &rhs) {\n\
    \    return os << rhs.val();\n  }\n};\n\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::R;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::R2;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::MOD;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::MOD_ODD;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::OFFSET;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::MASK;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::i32\
    \ runtime_modint31<IdT>::SMOD;\n\ntemplate <int IdT>\nusing rm31 = runtime_modint31<IdT>;\n\
    \nLIB_END\n\n\n#line 5 \"remote_test/yosupo/math/sqrt_mod.0.test.cpp\"\n\n#include\
    \ <cassert>\n#line 8 \"remote_test/yosupo/math/sqrt_mod.0.test.cpp\"\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int t;\n  std::cin >> t;\n  while (t--) {\n    int k, p;\n    std::cin >> k\
    \ >> p;\n    bool ok = lib::rm31<-1>::set_mod(p);\n    assert(ok);\n    auto res\
    \ = lib::sqrt_mod_prime<lib::rm31<-1>>(k);\n    if (res.empty()) {\n      std::cout\
    \ << \"-1\\n\";\n    } else {\n      std::cout << res.front() << '\\n';\n    }\n\
    \  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include\
    \ \"math/sqrt_mod.hpp\"\n#include \"modint/runtime_modint.hpp\"\n\n#include <cassert>\n\
    #include <iostream>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\"\
    , stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n  int t;\n  std::cin >> t;\n  while (t--) {\n    int\
    \ k, p;\n    std::cin >> k >> p;\n    bool ok = lib::rm31<-1>::set_mod(p);\n \
    \   assert(ok);\n    auto res = lib::sqrt_mod_prime<lib::rm31<-1>>(k);\n    if\
    \ (res.empty()) {\n      std::cout << \"-1\\n\";\n    } else {\n      std::cout\
    \ << res.front() << '\\n';\n    }\n  }\n  return 0;\n}"
  dependsOn:
  - math/sqrt_mod.hpp
  - common.hpp
  - math/random.hpp
  - modint/runtime_modint.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/sqrt_mod.0.test.cpp
  requiredBy: []
  timestamp: '2022-06-22 23:05:33+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/sqrt_mod.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/sqrt_mod.0.test.cpp
- /verify/remote_test/yosupo/math/sqrt_mod.0.test.cpp.html
title: remote_test/yosupo/math/sqrt_mod.0.test.cpp
---
