---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/modulo/sqrt_mod.hpp
    title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
  - icon: ':x:'
    path: modint/runtime_Montgomery_modint.hpp
    title: "runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\
      \u7C7B"
  - icon: ':question:'
    path: modint/runtime_long_Montgomery_modint.hpp
    title: "runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\u578B\
      \ Montgomery \u53D6\u6A21\u7C7B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"remote_test/yosupo/math/mod_sqrt.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include <iostream>\n#include\
    \ <vector>\n\n#line 1 \"math/modulo/sqrt_mod.hpp\"\n\n\n\n/**\n * @brief square\
    \ root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839\n * @docs docs/math/modulo/sqrt_mod.md\n\
    \ */\n\n#include <cassert>\n#include <random>\n#include <tuple>\n#include <type_traits>\n\
    #line 14 \"math/modulo/sqrt_mod.hpp\"\n\n#line 1 \"modint/runtime_Montgomery_modint.hpp\"\
    \n\n\n\n/**\n * @brief runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery\
    \ \u53D6\u6A21\u7C7B\n *\n */\n\n#include <cstdint>\n#line 12 \"modint/runtime_Montgomery_modint.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @brief \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\
    \u7C7B\n * @ref https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n\
    \ * @author Nyaan\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\n */\n\
    class RuntimeMontgomeryModInt {\npublic:\n  using i32 = std::int32_t;\n  using\
    \ u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n  using m32 = RuntimeMontgomeryModInt;\n\
    \n  using value_type = u32;\n\n  static u32 get_mod() { return mod; }\n\n  static\
    \ bool set_mod(u32 m) {\n    if ((m & 1) == 0 || m == 1 || (m & (3U << 30)) !=\
    \ 0) return false;\n    mod = m, mod2 = mod << 1;\n    u32 two = 2, iv = mod *\
    \ (two - mod * mod);\n    iv *= two - mod * iv;\n    iv *= two - mod * iv;\n \
    \   r = iv * (mod * iv - two);\n    r2 = -u64(mod) % mod;\n    return true;\n\
    \  }\n\n  RuntimeMontgomeryModInt() = default;\n  ~RuntimeMontgomeryModInt() =\
    \ default;\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  RuntimeMontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod))\
    \ * r2)) {}\n\n  RuntimeMontgomeryModInt(const m32 &) = default;\n\n  u32 get()\
    \ const { return norm(reduce(v_)); }\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  explicit constexpr operator T() const {\n    return T(get());\n\
    \  }\n\n  m32 operator-() const {\n    m32 res;\n    res.v_ = (mod2 & -(v_ !=\
    \ 0)) - v_;\n    return res;\n  }\n\n  m32 inv() const {\n    i32 x1 = 1, x3 =\
    \ 0, a = get(), b = mod;\n    while (b != 0) {\n      i32 q = a / b, x1_old =\
    \ x1, a_old = a;\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b *\
    \ q;\n    }\n    return m32(x1);\n  }\n\n  m32 &operator+=(const m32 &rhs) {\n\
    \    v_ += rhs.v_ - mod2;\n    v_ += mod2 & -(v_ >> 31);\n    return *this;\n\
    \  }\n  m32 &operator-=(const m32 &rhs) {\n    v_ -= rhs.v_;\n    v_ += mod2 &\
    \ -(v_ >> 31);\n    return *this;\n  }\n  m32 &operator*=(const m32 &rhs) {\n\
    \    v_ = reduce(u64(v_) * rhs.v_);\n    return *this;\n  }\n  m32 &operator/=(const\
    \ m32 &rhs) { return operator*=(rhs.inv()); }\n  friend m32 operator+(const m32\
    \ &lhs, const m32 &rhs) { return m32(lhs) += rhs; }\n  friend m32 operator-(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }\n  friend m32 operator*(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\n  friend m32 operator/(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }\n  friend bool operator==(const\
    \ m32 &lhs, const m32 &rhs) { return norm(lhs.v_) == norm(rhs.v_); }\n  friend\
    \ bool operator!=(const m32 &lhs, const m32 &rhs) { return norm(lhs.v_) != norm(rhs.v_);\
    \ }\n\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\n    i32\
    \ x;\n    is >> x;\n    rhs = m32(x);\n    return is;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &os, const m32 &rhs) { return os << rhs.get(); }\n\n\
    \  m32 pow(u64 y) const {\n    m32 res(1), x(*this);\n    for (; y != 0; y >>=\
    \ 1, x *= x)\n      if (y & 1) res *= x;\n    return res;\n  }\n\nprivate:\n \
    \ static u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod) >> 32; }\n  static\
    \ u32 norm(u32 x) { return x - (mod & -((mod - 1 - x) >> 31)); }\n\n  u32 v_;\n\
    \n  static u32 r, r2, mod, mod2;\n};\n\nRuntimeMontgomeryModInt::u32 RuntimeMontgomeryModInt::r;\n\
    RuntimeMontgomeryModInt::u32 RuntimeMontgomeryModInt::r2;\nRuntimeMontgomeryModInt::u32\
    \ RuntimeMontgomeryModInt::mod;\nRuntimeMontgomeryModInt::u32 RuntimeMontgomeryModInt::mod2;\n\
    \n// \u522B\u540D\nusing RuntimeMontModInt = RuntimeMontgomeryModInt;\n\n} //\
    \ namespace lib\n\n\n#line 1 \"modint/runtime_long_Montgomery_modint.hpp\"\n\n\
    \n\n/**\n * @brief runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\
    \u578B Montgomery \u53D6\u6A21\u7C7B\n *\n */\n\n#line 14 \"modint/runtime_long_Montgomery_modint.hpp\"\
    \n\n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace lib {\n\n/**\n *\
    \ @brief \u8FD0\u884C\u65F6\u957F\u6574\u578B Montgomery \u53D6\u6A21\u7C7B\n\
    \ * @ref https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n *\
    \ @author Nyaan\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\n */\n\
    class RuntimeLongMontgomeryModInt {\npublic:\n  using u32 = std::uint32_t;\n \
    \ using i64 = std::int64_t;\n  using u64 = std::uint64_t;\n  using m64 = RuntimeLongMontgomeryModInt;\n\
    \n  using value_type = u64;\n\n  static u64 get_mod() { return mod; }\n\n  static\
    \ bool set_mod(u64 m) {\n    if ((m & 1) == 0 || m == 1 || (m & (1ULL << 63))\
    \ != 0) return false;\n    mod = m;\n    r = get_r();\n    r2 = get_r2();\n  \
    \  return true;\n  }\n\n  RuntimeLongMontgomeryModInt() = default;\n  ~RuntimeLongMontgomeryModInt()\
    \ = default;\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  RuntimeLongMontgomeryModInt(T v) : v_(reduce(mul(norm(v % i64(mod)),\
    \ r2))) {}\n\n  RuntimeLongMontgomeryModInt(const m64 &) = default;\n\n  u64 get()\
    \ const { return reduce({0, v_}); }\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  explicit operator T() const {\n    return T(get());\n  }\n\n  m64\
    \ operator-() const {\n    m64 res;\n    res.v_ = (mod & -(v_ != 0)) - v_;\n \
    \   return res;\n  }\n\n  m64 inv() const {\n    i64 x1 = 1, x3 = 0, a = get(),\
    \ b = mod;\n    while (b != 0) {\n      i64 q = a / b, x1_old = x1, a_old = a;\n\
    \      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n    }\n    return\
    \ m64(x1);\n  }\n\n  m64 &operator+=(const m64 &rhs) {\n    v_ += rhs.v_ - mod;\n\
    \    v_ += mod & -(v_ >> 63);\n    return *this;\n  }\n  m64 &operator-=(const\
    \ m64 &rhs) {\n    v_ -= rhs.v_;\n    v_ += mod & -(v_ >> 63);\n    return *this;\n\
    \  }\n  m64 &operator*=(const m64 &rhs) {\n    v_ = reduce(mul(v_, rhs.v_));\n\
    \    return *this;\n  }\n  m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv());\
    \ }\n  friend m64 operator+(const m64 &lhs, const m64 &rhs) { return m64(lhs)\
    \ += rhs; }\n  friend m64 operator-(const m64 &lhs, const m64 &rhs) { return m64(lhs)\
    \ -= rhs; }\n  friend m64 operator*(const m64 &lhs, const m64 &rhs) { return m64(lhs)\
    \ *= rhs; }\n  friend m64 operator/(const m64 &lhs, const m64 &rhs) { return m64(lhs)\
    \ /= rhs; }\n  friend bool operator==(const m64 &lhs, const m64 &rhs) { return\
    \ lhs.v_ == rhs.v_; }\n  friend bool operator!=(const m64 &lhs, const m64 &rhs)\
    \ { return lhs.v_ != rhs.v_; }\n\n  friend std::istream &operator>>(std::istream\
    \ &is, m64 &rhs) {\n    i64 x;\n    is >> x;\n    rhs = m64(x);\n    return is;\n\
    \  }\n  friend std::ostream &operator<<(std::ostream &os, const m64 &rhs) { return\
    \ os << rhs.get(); }\n\n  m64 pow(u64 y) const {\n    m64 res(1), x(*this);\n\
    \    for (; y != 0; y >>= 1, x *= x)\n      if (y & 1) res *= x;\n    return res;\n\
    \  }\n\nprivate:\n  static std::pair<u64, u64> mul(u64 x, u64 y) {\n#ifdef __GNUC__\n\
    \    unsigned __int128 res = (unsigned __int128)x * y;\n    return {u64(res >>\
    \ 64), u64(res)};\n#elif defined(_MSC_VER)\n    u64 h, l = _umul128(x, y, &h);\n\
    \    return {h, l};\n#else\n    u64 a = x >> 32, b = u32(x), c = y >> 32, d =\
    \ u32(y), ad = a * d, bc = b * c;\n    return {a * c + (ad >> 32) + (bc >> 32)\
    \ +\n                (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32))\
    \ >> 32),\n            x * y};\n#endif\n  }\n\n  static u64 mulh(u64 x, u64 y)\
    \ {\n#ifdef __GNUC__\n    return u64((unsigned __int128)x * y >> 64);\n#elif defined(_MSC_VER)\n\
    \    return __umulh(x, y);\n#else\n    u64 a = x >> 32, b = u32(x), c = y >> 32,\
    \ d = u32(y), ad = a * d, bc = b * c;\n    return a * c + (ad >> 32) + (bc >>\
    \ 32) +\n           (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32))\
    \ >> 32);\n#endif\n  }\n\n  static u64 get_r() {\n    u64 two = 2, iv = mod *\
    \ (two - mod * mod);\n    iv *= two - mod * iv;\n    iv *= two - mod * iv;\n \
    \   iv *= two - mod * iv;\n    return iv * (two - mod * iv);\n  }\n\n  static\
    \ u64 get_r2() {\n    u64 iv = -u64(mod) % mod;\n    for (int i = 0; i != 64;\
    \ ++i)\n      if ((iv <<= 1) >= mod) iv -= mod;\n    return iv;\n  }\n\n  static\
    \ u64 reduce(const std::pair<u64, u64> &x) {\n    u64 res = x.first - mulh(x.second\
    \ * r, mod);\n    return res + (mod & -(res >> 63));\n  }\n\n  static u64 norm(i64\
    \ x) { return x + (mod & -(x < 0)); }\n\n  u64 v_;\n\n  static u64 mod, r, r2;\n\
    };\n\nRuntimeLongMontgomeryModInt::u64 RuntimeLongMontgomeryModInt::mod;\nRuntimeLongMontgomeryModInt::u64\
    \ RuntimeLongMontgomeryModInt::r;\nRuntimeLongMontgomeryModInt::u64 RuntimeLongMontgomeryModInt::r2;\n\
    \nusing RuntimeLongMontModInt = RuntimeLongMontgomeryModInt;\n\n} // namespace\
    \ lib\n\n\n#line 17 \"math/modulo/sqrt_mod.hpp\"\n\nnamespace lib {\n\nnamespace\
    \ internal {\n\ntemplate <typename mod_t> std::vector<mod_t> sqrt_mod_prime(const\
    \ mod_t x) {\n  const auto p = mod_t::get_mod();\n  const mod_t ONE(1), MINUS_ONE(-ONE),\
    \ ZERO(0);\n  if (x == ZERO) return {ZERO};\n  if (x.pow(p >> 1) == MINUS_ONE)\
    \ return {};\n  if ((p & 3) == 3) {\n    mod_t res = x.pow((p + 1) >> 2);\n  \
    \  return {res, -res};\n  }\n\n  static std::random_device rd;\n  static std::mt19937\
    \ gen(rd());\n  std::uniform_int_distribution<std::uint32_t> dis(2, p - 1);\n\n\
    \  const mod_t four(mod_t(4) * x);\n  mod_t t, w2;\n  do {\n    t = mod_t(dis(gen)),\
    \ w2 = t * t - four;\n    if (w2 == ZERO) { // \u8DB3\u591F\u5E78\u8FD0\u65F6\n\
    \      t /= 2;\n      return {t, -t};\n    }\n  } while (w2.pow(p >> 1) != MINUS_ONE);\n\
    \n  mod_t a(ONE), b(ZERO), c(ZERO), d(ONE);\n\n  for (auto e = (p + 1) >> 1; e\
    \ != 0; e >>= 1) {\n    if (e & 1) {\n      mod_t bd = b * d;\n      std::tie(a,\
    \ b) = std::make_pair(a * c - bd * x, a * d + b * c + bd * t);\n    }\n    mod_t\
    \ dd = d * d, cd = c * d;\n    std::tie(c, d) = std::make_pair(c * c - dd * x,\
    \ cd + cd + dd * t);\n  }\n\n  return {a, -a};\n}\n\n} // namespace internal\n\
    \n/**\n * @brief \u6A21\u5E73\u65B9\u6839\n * @param x [0, p-1] \u4E2D\u7684\u4E00\
    \u4E2A\u503C\n * @param p \u7D20\u6570\n * @return std::vector<T>\n */\ntemplate\
    \ <typename T>\nstd::enable_if_t<std::is_integral_v<T>, std::vector<T>> sqrt_mod_prime(T\
    \ x, T p) {\n  if (p == 2 || x == 0) return {x};\n  if (p < (3U << 30)) {\n  \
    \  bool okay = RuntimeMontgomeryModInt::set_mod(p);\n    assert(okay);\n    auto\
    \ res = internal::sqrt_mod_prime(RuntimeMontgomeryModInt(x));\n    return std::vector<T>(res.begin(),\
    \ res.end());\n  }\n  bool okay = RuntimeLongMontgomeryModInt::set_mod(p);\n \
    \ assert(okay);\n  auto res = internal::sqrt_mod_prime(RuntimeLongMontgomeryModInt(x));\n\
    \  return std::vector<T>(res.begin(), res.end());\n}\n\n} // namespace lib\n\n\
    \n#line 7 \"remote_test/yosupo/math/mod_sqrt.0.test.cpp\"\n\nint main() {\n#ifdef\
    \ LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n\
    #endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n  int t;\n  std::cin\
    \ >> t;\n  while (t--) {\n    int k, p;\n    std::cin >> k >> p;\n    auto res\
    \ = lib::sqrt_mod_prime(k, p);\n    if (res.empty())\n      std::cout << \"-1\\\
    n\";\n    else\n      std::cout << res[0] << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include\
    \ <iostream>\n#include <vector>\n\n#include \"math/modulo/sqrt_mod.hpp\"\n\nint\
    \ main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int t;\n  std::cin >> t;\n  while (t--) {\n    int k, p;\n    std::cin >> k\
    \ >> p;\n    auto res = lib::sqrt_mod_prime(k, p);\n    if (res.empty())\n   \
    \   std::cout << \"-1\\n\";\n    else\n      std::cout << res[0] << '\\n';\n \
    \ }\n  return 0;\n}"
  dependsOn:
  - math/modulo/sqrt_mod.hpp
  - modint/runtime_Montgomery_modint.hpp
  - modint/runtime_long_Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-27 15:17:15+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: remote_test/yosupo/math/mod_sqrt.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/mod_sqrt.0.test.cpp
- /verify/remote_test/yosupo/math/mod_sqrt.0.test.cpp.html
title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
---
