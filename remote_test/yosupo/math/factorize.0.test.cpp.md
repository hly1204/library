---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/integer_factorization.hpp
    title: "integer factorization / \u6574\u6570\u5206\u89E3"
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
    PROBLEM: https://judge.yosupo.jp/problem/factorize
    links:
    - https://judge.yosupo.jp/problem/factorize
  bundledCode: "#line 1 \"remote_test/yosupo/math/factorize.0.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n\n#include <iostream>\n\
    \n#line 1 \"math/basic/integer_factorization.hpp\"\n\n\n\n/**\n * @brief integer\
    \ factorization / \u6574\u6570\u5206\u89E3\n *\n */\n\n#include <cstdint>\n#include\
    \ <map>\n#include <numeric>\n#include <random>\n\n#line 1 \"modint/runtime_long_Montgomery_modint.hpp\"\
    \n\n\n\n/**\n * @brief runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\
    \u6574\u578B Montgomery \u53D6\u6A21\u7C7B\n *\n */\n\n#include <cassert>\n#line\
    \ 12 \"modint/runtime_long_Montgomery_modint.hpp\"\n#include <tuple>\n#include\
    \ <type_traits>\n\n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace lib\
    \ {\n\n/**\n * @brief \u8FD0\u884C\u65F6\u957F Montgomery \u53D6\u6A21\u7C7B\n\
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
    \  }\n\nprivate:\n  //---\n  static std::pair<u64, u64> mul(u64 x, u64 y) {\n\
    #ifdef _MSC_VER\n    u64 h, l = _umul128(x, y, &h);\n    return {h, l};\n#elif\
    \ defined(__GNUC__)\n    unsigned __int128 res = (unsigned __int128)x * y;\n \
    \   return {u64(res >> 64), u64(res)};\n#else\n    u64 a = x >> 32, b = u32(x),\
    \ c = y >> 32, d = u32(y), ac = a * c, bd = b * d, ad = a * d,\n        bc = b\
    \ * c;\n    // low = bd + (ad + bc << 32); \u4F46\u662F\u6CA1\u5FC5\u8981\n  \
    \  return {ac + (ad >> 32) + (bc >> 32) +\n                (((ad & -UINT32_C(1))\
    \ + (bc & -UINT32_C(1)) + (bd >> 32)) >> 32),\n            x * y};\n#endif\n \
    \ }\n\n  static u64 mulh(u64 x, u64 y) {\n#ifdef _MSC_VER\n    return __umulh(x,\
    \ y);\n#elif defined(__GNUC__)\n    return (unsigned __int128)x * y >> 64;\n#else\n\
    \    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ac = a * c, bd = b\
    \ * d, ad = a * d,\n        bc = b * c;\n    return ac + (ad >> 32) + (bc >> 32)\
    \ +\n           (((ad & -UINT32_C(1)) + (bc & -UINT32_C(1)) + (bd >> 32)) >> 32);\n\
    #endif\n  }\n  //---\n\n  static u64 get_r() {\n    u64 two = 2, iv = mod * (two\
    \ - mod * mod);\n    iv *= two - mod * iv;\n    iv *= two - mod * iv;\n    iv\
    \ *= two - mod * iv;\n    return iv * (two - mod * iv);\n  }\n\n  static u64 get_r2()\
    \ {\n    u64 iv = -u64(mod) % mod;\n    for (int i = 0; i != 64; ++i)\n      if\
    \ ((iv <<= 1) >= mod) iv -= mod;\n    return iv;\n  }\n\n  static u64 reduce(const\
    \ std::pair<u64, u64> &x) {\n    u64 res = x.first - mulh(x.second * r, mod);\n\
    \    return res + (mod & -(res >> 63));\n  }\n\n  static u64 norm(i64 x) { return\
    \ x + (mod & -(x < 0)); }\n\n  u64 v_;\n\n  static u64 mod, r, r2;\n};\n\nRuntimeLongMontgomeryModInt::u64\
    \ RuntimeLongMontgomeryModInt::mod;\nRuntimeLongMontgomeryModInt::u64 RuntimeLongMontgomeryModInt::r;\n\
    RuntimeLongMontgomeryModInt::u64 RuntimeLongMontgomeryModInt::r2;\n\nusing RuntimeLongMontModInt\
    \ = RuntimeLongMontgomeryModInt;\n\n} // namespace lib\n\n\n#line 15 \"math/basic/integer_factorization.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @brief Miller-Rabin \u7D20\u6027\u6D4B\u8BD5\n\
    \ *\n * @param n\n * @return true\n * @return false\n */\nbool is_prime(std::uint64_t\
    \ n) {\n  if (n <= 2) return n == 2;\n  if ((n & 1) == 0) return false;\n  if\
    \ (n < 8) return true;\n  using m64 = RuntimeLongMontModInt;\n  bool okay = m64::set_mod(n);\n\
    \  assert(okay);\n  int t = 0;\n  std::uint64_t u = n - 1;\n  do\n    u >>= 1,\
    \ ++t;\n  while ((u & 1) == 0);\n  const m64 ONE(1), MINUS_ONE(n - 1);\n  for\
    \ (int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {\n    if (n == i) return\
    \ true;\n    m64 x = m64(i).pow(u);\n    for (int i = 0; i != t && x != ONE; ++i)\
    \ {\n      m64 y = x * x;\n      if (x != MINUS_ONE && y == ONE) return false;\n\
    \      x = y;\n    }\n    if (x != ONE) return false;\n  }\n  return true;\n}\n\
    \nstd::uint64_t rho(std::uint64_t n) {\n  using u64 = std::uint64_t;\n  using\
    \ m64 = RuntimeLongMontModInt;\n  static std::random_device rd;\n  static std::mt19937\
    \ gen(rd());\n  std::uniform_int_distribution<u64> dis(2, n - 1);\n  if (m64::get_mod()\
    \ != n) m64::set_mod(n);\n  const m64 R(dis(gen));\n  auto f = [=](m64 x) -> m64\
    \ { return x * x + R; };\n  m64 x, y(dis(gen)), ys, q(1);\n  u64 g = 1;\n  const\
    \ int m = 128;\n  for (int r = 1; g == 1; r <<= 1) {\n    x = y;\n    for (int\
    \ i = 0; i < r; ++i) y = f(y);\n    for (int k = 0; g == 1 && k < r; k += m) {\n\
    \      ys = y;\n      for (int i = 0; i < m && i < r - k; ++i) q *= x - (y = f(y));\n\
    \      g = std::gcd(u64(q), n);\n    }\n  }\n  if (g == n) do\n      g = std::gcd(u64(x\
    \ - (ys = f(ys))), n);\n    while (g == 1);\n  return g == n ? rho(n) : g;\n}\n\
    \nvoid factorize_odd(std::uint64_t n, std::map<std::uint64_t, int> &mp) {\n  if\
    \ (n < 2) return;\n  if (is_prime(n)) {\n    ++mp[n];\n    return;\n  }\n  std::uint64_t\
    \ g = rho(n);\n  factorize_odd(n / g, mp);\n  factorize_odd(g, mp);\n}\n\nstd::map<std::uint64_t,\
    \ int> factorize(std::uint64_t n) {\n  std::map<std::uint64_t, int> res;\n  if\
    \ (n < 2) return res;\n  int t = 0;\n  while ((n & 1) == 0) n >>= 1, ++t;\n  if\
    \ (t) res[2] = t;\n  factorize_odd(n, res);\n  return res;\n}\n\n} // namespace\
    \ lib\n\n\n#line 6 \"remote_test/yosupo/math/factorize.0.test.cpp\"\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int Q;\n  std::cin >> Q;\n  while (Q--) {\n    long long a;\n    std::cin >>\
    \ a;\n    std::vector<long long> factor;\n    auto mp = lib::factorize(a);\n \
    \   for (auto i : mp) {\n      for (int j = i.second; j > 0; --j) factor.push_back(i.first);\n\
    \    }\n    std::cout << factor.size() << ' ';\n    for (auto i : factor) std::cout\
    \ << i << ' ';\n    std::cout << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n\n#include\
    \ <iostream>\n\n#include \"math/basic/integer_factorization.hpp\"\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int Q;\n  std::cin >> Q;\n  while (Q--) {\n    long long a;\n    std::cin >>\
    \ a;\n    std::vector<long long> factor;\n    auto mp = lib::factorize(a);\n \
    \   for (auto i : mp) {\n      for (int j = i.second; j > 0; --j) factor.push_back(i.first);\n\
    \    }\n    std::cout << factor.size() << ' ';\n    for (auto i : factor) std::cout\
    \ << i << ' ';\n    std::cout << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - math/basic/integer_factorization.hpp
  - modint/runtime_long_Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/factorize.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-06 21:24:21+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/factorize.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/factorize.0.test.cpp
- /verify/remote_test/yosupo/math/factorize.0.test.cpp.html
title: remote_test/yosupo/math/factorize.0.test.cpp
---
