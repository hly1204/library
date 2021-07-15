---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modulo/sqrt_mod.hpp
    title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
  - icon: ':heavy_check_mark:'
    path: modint/runtime_Montgomery_modint.hpp
    title: "runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\
      \u7C7B"
  - icon: ':heavy_check_mark:'
    path: modint/runtime_long_Montgomery_modint.hpp
    title: "runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\u578B\
      \ Montgomery \u53D6\u6A21\u7C7B"
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
  bundledCode: "#line 1 \"remote_test/yosupo/math/mod_sqrt.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sqrt_mod\"\r\n\r\n#include <iostream>\r\n\
    #include <vector>\r\n\r\n#line 1 \"math/modulo/sqrt_mod.hpp\"\n\n\n\r\n/**\r\n\
    \ * @brief square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839\r\n *\
    \ @docs docs/math/modulo/sqrt_mod.md\r\n */\r\n\r\n#include <cassert>\r\n#include\
    \ <random>\r\n#include <tuple>\r\n#include <type_traits>\r\n#line 14 \"math/modulo/sqrt_mod.hpp\"\
    \n\r\n#line 1 \"modint/runtime_Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n * @brief\
    \ runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\u7C7B\
    \r\n *\r\n */\r\n\r\n#include <cstdint>\r\n#line 12 \"modint/runtime_Montgomery_modint.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u8FD0\u884C\u65F6 Montgomery \u53D6\
    \u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @note \u7EA6\u5B9A\u4E0D\u4F7F\u7528\u6A21\u677F\u4E2D\
    \ int \u4E3A\u8D1F\u6570\u7684\u5BF9\u8C61\r\n */\r\ntemplate <int>\r\nclass RuntimeMontgomeryModInt\
    \ {\r\npublic:\r\n  using i32 = std::int32_t;\r\n  using u32 = std::uint32_t;\r\
    \n  using u64 = std::uint64_t;\r\n  using m32 = RuntimeMontgomeryModInt;\r\n\r\
    \n  using value_type = u32;\r\n\r\n  static u32 get_mod() { return mod; }\r\n\r\
    \n  static bool set_mod(u32 m) {\r\n    if ((m & 1) == 0 || m == 1 || (m & (3U\
    \ << 30)) != 0) return false;\r\n    mod = m, mod2 = mod << 1;\r\n    u32 two\
    \ = 2, iv = mod * (two - mod * mod);\r\n    iv *= two - mod * iv;\r\n    iv *=\
    \ two - mod * iv;\r\n    r  = iv * (mod * iv - two);\r\n    r2 = -u64(mod) % mod;\r\
    \n    return true;\r\n  }\r\n\r\n  RuntimeMontgomeryModInt()  = default;\r\n \
    \ ~RuntimeMontgomeryModInt() = default;\r\n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\r\n  RuntimeMontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod))\
    \ * r2)) {}\r\n\r\n  RuntimeMontgomeryModInt(const m32 &) = default;\r\n\r\n \
    \ u32 get() const { return norm(reduce(v_)); }\r\n\r\n  template <typename T,\
    \ std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit operator T()\
    \ const {\r\n    return T(get());\r\n  }\r\n\r\n  m32 operator-() const {\r\n\
    \    m32 res;\r\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\r\n    return res;\r\n\
    \  }\r\n\r\n  m32 inv() const {\r\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\r\
    \n    while (b != 0) {\r\n      i32 q = a / b, x1_old = x1, a_old = a;\r\n   \
    \   x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\r\n    }\r\n    return\
    \ m32(x1);\r\n  }\r\n\r\n  m32 &operator=(const m32 &) = default;\r\n\r\n  m32\
    \ &operator+=(const m32 &rhs) {\r\n    v_ += rhs.v_ - mod2;\r\n    v_ += mod2\
    \ & -(v_ >> 31);\r\n    return *this;\r\n  }\r\n  m32 &operator-=(const m32 &rhs)\
    \ {\r\n    v_ -= rhs.v_;\r\n    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\
    \n  }\r\n  m32 &operator*=(const m32 &rhs) {\r\n    v_ = reduce(u64(v_) * rhs.v_);\r\
    \n    return *this;\r\n  }\r\n  m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend m32 operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs)\
    \ += rhs; }\r\n  friend m32 operator-(const m32 &lhs, const m32 &rhs) { return\
    \ m32(lhs) -= rhs; }\r\n  friend m32 operator*(const m32 &lhs, const m32 &rhs)\
    \ { return m32(lhs) *= rhs; }\r\n  friend m32 operator/(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) /= rhs; }\r\n  friend bool operator==(const m32\
    \ &lhs, const m32 &rhs) { return norm(lhs.v_) == norm(rhs.v_); }\r\n  friend bool\
    \ operator!=(const m32 &lhs, const m32 &rhs) { return norm(lhs.v_) != norm(rhs.v_);\
    \ }\r\n\r\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\r\n\
    \    i32 x;\r\n    is >> x;\r\n    rhs = m32(x);\r\n    return is;\r\n  }\r\n\
    \  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return\
    \ os << rhs.get(); }\r\n\r\n  m32 pow(u64 y) const {\r\n    m32 res(1), x(*this);\r\
    \n    for (; y != 0; y >>= 1, x *= x)\r\n      if (y & 1) res *= x;\r\n    return\
    \ res;\r\n  }\r\n\r\nprivate:\r\n  static u32 reduce(u64 x) { return (x + u64(u32(x)\
    \ * r) * mod) >> 32; }\r\n  static u32 norm(u32 x) { return x - (mod & -((mod\
    \ - 1 - x) >> 31)); }\r\n\r\n  u32 v_;\r\n\r\n  static inline u32 r, r2, mod,\
    \ mod2;\r\n};\r\n\r\n// \u522B\u540D\r\ntemplate <int id>\r\nusing RuntimeMontModInt\
    \ = RuntimeMontgomeryModInt<id>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"\
    modint/runtime_long_Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n * @brief runtime\
    \ long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\u578B Montgomery \u53D6\
    \u6A21\u7C7B\r\n *\r\n */\r\n\r\n#line 14 \"modint/runtime_long_Montgomery_modint.hpp\"\
    \n\r\n#ifdef _MSC_VER\r\n  #include <intrin.h>\r\n#endif\r\n\r\nnamespace lib\
    \ {\r\n\r\n/**\r\n * @brief \u8FD0\u884C\u65F6\u957F\u6574\u578B Montgomery \u53D6\
    \u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @note \u7EA6\u5B9A\u4E0D\u4F7F\u7528\u6A21\u677F\u4E2D\
    \ int \u4E3A\u8D1F\u6570\u7684\u5BF9\u8C61\r\n */\r\ntemplate <int>\r\nclass RuntimeLongMontgomeryModInt\
    \ {\r\npublic:\r\n  using u32 = std::uint32_t;\r\n  using i64 = std::int64_t;\r\
    \n  using u64 = std::uint64_t;\r\n  using m64 = RuntimeLongMontgomeryModInt;\r\
    \n\r\n  using value_type = u64;\r\n\r\n  static u64 get_mod() { return mod; }\r\
    \n\r\n  static bool set_mod(u64 m) {\r\n    if ((m & 1) == 0 || m == 1 || (m &\
    \ (1ULL << 63)) != 0) return false;\r\n    mod = m;\r\n    r   = get_r();\r\n\
    \    r2  = get_r2();\r\n    return true;\r\n  }\r\n\r\n  RuntimeLongMontgomeryModInt()\
    \  = default;\r\n  ~RuntimeLongMontgomeryModInt() = default;\r\n\r\n  template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  RuntimeLongMontgomeryModInt(T\
    \ v) : v_(reduce(mul(norm(v % i64(mod)), r2))) {}\r\n\r\n  RuntimeLongMontgomeryModInt(const\
    \ m64 &) = default;\r\n\r\n  u64 get() const { return reduce({0, v_}); }\r\n\r\
    \n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n\
    \  explicit operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  m64 operator-()\
    \ const {\r\n    m64 res;\r\n    res.v_ = (mod & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  m64 inv() const {\r\n    i64 x1 = 1, x3 = 0, a = get(),\
    \ b = mod;\r\n    while (b != 0) {\r\n      i64 q = a / b, x1_old = x1, a_old\
    \ = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\r\n \
    \   }\r\n    return m64(x1);\r\n  }\r\n\r\n  m64 &operator=(const m64 &) = default;\r\
    \n\r\n  m64 &operator+=(const m64 &rhs) {\r\n    v_ += rhs.v_ - mod;\r\n    v_\
    \ += mod & -(v_ >> 63);\r\n    return *this;\r\n  }\r\n  m64 &operator-=(const\
    \ m64 &rhs) {\r\n    v_ -= rhs.v_;\r\n    v_ += mod & -(v_ >> 63);\r\n    return\
    \ *this;\r\n  }\r\n  m64 &operator*=(const m64 &rhs) {\r\n    v_ = reduce(mul(v_,\
    \ rhs.v_));\r\n    return *this;\r\n  }\r\n  m64 &operator/=(const m64 &rhs) {\
    \ return operator*=(rhs.inv()); }\r\n  friend m64 operator+(const m64 &lhs, const\
    \ m64 &rhs) { return m64(lhs) += rhs; }\r\n  friend m64 operator-(const m64 &lhs,\
    \ const m64 &rhs) { return m64(lhs) -= rhs; }\r\n  friend m64 operator*(const\
    \ m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }\r\n  friend m64 operator/(const\
    \ m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }\r\n  friend bool operator==(const\
    \ m64 &lhs, const m64 &rhs) { return lhs.v_ == rhs.v_; }\r\n  friend bool operator!=(const\
    \ m64 &lhs, const m64 &rhs) { return lhs.v_ != rhs.v_; }\r\n\r\n  friend std::istream\
    \ &operator>>(std::istream &is, m64 &rhs) {\r\n    i64 x;\r\n    is >> x;\r\n\
    \    rhs = m64(x);\r\n    return is;\r\n  }\r\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m64 &rhs) { return os << rhs.get(); }\r\n\r\n  m64 pow(u64 y) const\
    \ {\r\n    m64 res(1), x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n  \
    \    if (y & 1) res *= x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static\
    \ std::pair<u64, u64> mul(u64 x, u64 y) {\r\n#ifdef __GNUC__\r\n    unsigned __int128\
    \ res = (unsigned __int128)x * y;\r\n    return {u64(res >> 64), u64(res)};\r\n\
    #elif defined(_MSC_VER)\r\n    u64 h, l = _umul128(x, y, &h);\r\n    return {h,\
    \ l};\r\n#else\r\n    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad\
    \ = a * d, bc = b * c;\r\n    return {a * c + (ad >> 32) + (bc >> 32) +\r\n  \
    \              (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >>\
    \ 32),\r\n            x * y};\r\n#endif\r\n  }\r\n\r\n  static u64 mulh(u64 x,\
    \ u64 y) {\r\n#ifdef __GNUC__\r\n    return u64((unsigned __int128)x * y >> 64);\r\
    \n#elif defined(_MSC_VER)\r\n    return __umulh(x, y);\r\n#else\r\n    u64 a =\
    \ x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;\r\n  \
    \  return a * c + (ad >> 32) + (bc >> 32) +\r\n           (((ad & ~UINT32_C(0))\
    \ + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32);\r\n#endif\r\n  }\r\n\r\n  static\
    \ u64 get_r() {\r\n    u64 two = 2, iv = mod * (two - mod * mod);\r\n    iv *=\
    \ two - mod * iv;\r\n    iv *= two - mod * iv;\r\n    iv *= two - mod * iv;\r\n\
    \    return iv * (two - mod * iv);\r\n  }\r\n\r\n  static u64 get_r2() {\r\n \
    \   u64 iv = -u64(mod) % mod;\r\n    for (int i = 0; i != 64; ++i)\r\n      if\
    \ ((iv <<= 1) >= mod) iv -= mod;\r\n    return iv;\r\n  }\r\n\r\n  static u64\
    \ reduce(const std::pair<u64, u64> &x) {\r\n    u64 res = x.first - mulh(x.second\
    \ * r, mod);\r\n    return res + (mod & -(res >> 63));\r\n  }\r\n\r\n  static\
    \ u64 norm(i64 x) { return x + (mod & -(x < 0)); }\r\n\r\n  u64 v_;\r\n\r\n  static\
    \ inline u64 mod, r, r2;\r\n};\r\n\r\ntemplate <int id>\r\nusing RuntimeLongMontModInt\
    \ = RuntimeLongMontgomeryModInt<id>;\r\n\r\n} // namespace lib\r\n\r\n\n#line\
    \ 17 \"math/modulo/sqrt_mod.hpp\"\n\r\nnamespace lib::internal {\r\n\r\ntemplate\
    \ <typename mod_t>\r\nstd::vector<mod_t> sqrt_mod_prime(const mod_t x) {\r\n \
    \ const auto p = mod_t::get_mod();\r\n  const mod_t ONE(1), MINUS_ONE(-ONE), ZERO(0);\r\
    \n  if (x == ZERO) return {ZERO};\r\n  if (x.pow(p >> 1) == MINUS_ONE) return\
    \ {};\r\n  if ((p & 3) == 3) {\r\n    mod_t res = x.pow((p + 1) >> 2);\r\n   \
    \ return {res, -res};\r\n  }\r\n\r\n  static std::random_device rd;\r\n  static\
    \ std::mt19937 gen(rd());\r\n  std::uniform_int_distribution<std::uint32_t> dis(2,\
    \ p - 1);\r\n\r\n  const mod_t four(mod_t(4) * x);\r\n  mod_t t, w2;\r\n  do {\r\
    \n    t = mod_t(dis(gen)), w2 = t * t - four;\r\n    if (w2 == ZERO) { // \u8DB3\
    \u591F\u5E78\u8FD0\u65F6\r\n      t /= 2;\r\n      return {t, -t};\r\n    }\r\n\
    \  } while (w2.pow(p >> 1) != MINUS_ONE);\r\n\r\n  mod_t a(ONE), b(ZERO), c(ZERO),\
    \ d(ONE);\r\n\r\n  for (auto e = (p + 1) >> 1; e != 0; e >>= 1) {\r\n    if (e\
    \ & 1) {\r\n      mod_t bd       = b * d;\r\n      std::tie(a, b) = std::make_pair(a\
    \ * c - bd * x, a * d + b * c + bd * t);\r\n    }\r\n    mod_t dd = d * d, cd\
    \ = c * d;\r\n    std::tie(c, d) = std::make_pair(c * c - dd * x, cd + cd + dd\
    \ * t);\r\n  }\r\n\r\n  return {a, -a};\r\n}\r\n\r\n} // namespace lib::internal\r\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u6A21\u5E73\u65B9\u6839\r\n * @param\
    \ x [0, p-1] \u4E2D\u7684\u4E00\u4E2A\u503C\r\n * @param p \u7D20\u6570\r\n *\
    \ @return std::vector<T>\r\n */\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>,\
    \ std::vector<T>> sqrt_mod_prime(T x, T p) {\r\n  using m32 = RuntimeMontModInt<-1>;\r\
    \n  using m64 = RuntimeLongMontModInt<-1>;\r\n  if (p == 2 || x == 0) return {x};\r\
    \n  if (p < (3U << 30)) {\r\n    bool okay = m32::set_mod(p);\r\n    assert(okay);\r\
    \n    auto res = internal::sqrt_mod_prime(m32(x));\r\n    return std::vector<T>(res.begin(),\
    \ res.end());\r\n  }\r\n  bool okay = m64::set_mod(p);\r\n  assert(okay);\r\n\
    \  auto res = internal::sqrt_mod_prime(m64(x));\r\n  return std::vector<T>(res.begin(),\
    \ res.end());\r\n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 7 \"remote_test/yosupo/math/mod_sqrt.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int t;\r\n  std::cin >> t;\r\n  while (t--) {\r\n    int k, p;\r\n    std::cin\
    \ >> k >> p;\r\n    auto res = lib::sqrt_mod_prime(k, p);\r\n    if (res.empty())\
    \ std::cout << \"-1\\n\";\r\n    else\r\n      std::cout << res[0] << '\\n';\r\
    \n  }\r\n  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\r\n\r\n#include\
    \ <iostream>\r\n#include <vector>\r\n\r\n#include \"math/modulo/sqrt_mod.hpp\"\
    \r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  int t;\r\n  std::cin >> t;\r\n  while (t--) {\r\n  \
    \  int k, p;\r\n    std::cin >> k >> p;\r\n    auto res = lib::sqrt_mod_prime(k,\
    \ p);\r\n    if (res.empty()) std::cout << \"-1\\n\";\r\n    else\r\n      std::cout\
    \ << res[0] << '\\n';\r\n  }\r\n  return 0;\r\n}"
  dependsOn:
  - math/modulo/sqrt_mod.hpp
  - modint/runtime_Montgomery_modint.hpp
  - modint/runtime_long_Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/mod_sqrt.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/mod_sqrt.0.test.cpp
- /verify/remote_test/yosupo/math/mod_sqrt.0.test.cpp.html
title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
---
