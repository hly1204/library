---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/integer_factorization_Pollard_rho.hpp
    title: "integer factorization Pollard's rho / \u6574\u6570\u5206\u89E3 Pollard\
      \ \u7684 rho \u7B97\u6CD5"
  - icon: ':question:'
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
    \ PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\r\n\r\n#include <iostream>\r\
    \n\r\n#line 1 \"math/basic/integer_factorization_Pollard_rho.hpp\"\n\n\n\r\n/**\r\
    \n * @brief integer factorization Pollard's rho / \u6574\u6570\u5206\u89E3 Pollard\
    \ \u7684 rho \u7B97\u6CD5\r\n *\r\n */\r\n\r\n#include <cstdint>\r\n#include <map>\r\
    \n#include <numeric>\r\n#include <random>\r\n\r\n#line 1 \"modint/runtime_long_Montgomery_modint.hpp\"\
    \n\n\n\r\n/**\r\n * @brief runtime long Montgomery modint / \u8FD0\u884C\u65F6\
    \u957F\u6574\u578B Montgomery \u53D6\u6A21\u7C7B\r\n *\r\n */\r\n\r\n#include\
    \ <cassert>\r\n#line 12 \"modint/runtime_long_Montgomery_modint.hpp\"\n#include\
    \ <tuple>\r\n#include <type_traits>\r\n\r\n#ifdef _MSC_VER\r\n  #include <intrin.h>\r\
    \n#endif\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u8FD0\u884C\u65F6\u957F\
    \u6574\u578B Montgomery \u53D6\u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
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
    \ 15 \"math/basic/integer_factorization_Pollard_rho.hpp\"\n\r\nnamespace lib::internal\
    \ {\r\n\r\n/**\r\n * @brief Pollard-rho \u7B97\u6CD5\r\n * @param n\r\n * @return\
    \ std::uint64_t \u4E00\u4E2A\uFF08\u7D20\uFF09\u56E0\u6570\uFF1F\r\n */\r\nstd::uint64_t\
    \ rho(std::uint64_t n) {\r\n  using u64 = std::uint64_t;\r\n  using m64 = RuntimeLongMontModInt<-1>;\r\
    \n  static std::random_device rd;\r\n  static std::mt19937 gen(rd());\r\n  std::uniform_int_distribution<u64>\
    \ dis(2, n - 1);\r\n  if (m64::get_mod() != n) m64::set_mod(n);\r\n  const m64\
    \ R(dis(gen));\r\n  auto f = [=](m64 x) -> m64 { return x * x + R; };\r\n  m64\
    \ x, y(dis(gen)), ys, q(1);\r\n  u64 g       = 1;\r\n  const int m = 128;\r\n\
    \  for (int r = 1; g == 1; r <<= 1) {\r\n    x = y;\r\n    for (int i = 0; i <\
    \ r; ++i) y = f(y);\r\n    for (int k = 0; g == 1 && k < r; k += m) {\r\n    \
    \  ys = y;\r\n      for (int i = 0; i < m && i < r - k; ++i) q *= x - (y = f(y));\r\
    \n      g = std::gcd(u64(q), n);\r\n    }\r\n  }\r\n  if (g == n) do\r\n     \
    \ g = std::gcd(u64(x - (ys = f(ys))), n);\r\n    while (g == 1);\r\n  return g\
    \ == n ? rho(n) : g;\r\n}\r\n\r\n} // namespace lib::internal\r\n\r\nnamespace\
    \ lib {\r\n\r\n/**\r\n * @brief Miller-Rabin \u7D20\u6027\u6D4B\u8BD5\r\n * @note\
    \ \u5047\u8BBE\u5E7F\u4E49\u9ECE\u66FC\u5047\u8BBE\u6210\u7ACB\r\n */\r\nbool\
    \ is_prime(std::uint64_t n) {\r\n  if (n <= 2) return n == 2;\r\n  if ((n & 1)\
    \ == 0) return false;\r\n  if (n < 8) return true;\r\n  using m64 = RuntimeLongMontModInt<-1>;\r\
    \n  bool okay = m64::set_mod(n);\r\n  assert(okay);\r\n  int t           = 0;\r\
    \n  std::uint64_t u = n - 1;\r\n  do u >>= 1, ++t;\r\n  while ((u & 1) == 0);\r\
    \n  const m64 ONE(1), MINUS_ONE(n - 1);\r\n  for (int i : {2, 3, 5, 7, 11, 13,\
    \ 17, 19, 23, 29, 31, 37}) {\r\n    if (n == i) return true;\r\n    m64 x = m64(i).pow(u);\r\
    \n    for (int j = 0; j != t && x != ONE; ++j) {\r\n      m64 y = x * x;\r\n \
    \     if (x != MINUS_ONE && y == ONE) return false;\r\n      x = y;\r\n    }\r\
    \n    if (x != ONE) return false;\r\n  }\r\n  return true;\r\n}\r\n\r\n} // namespace\
    \ lib\r\n\r\nnamespace lib::internal {\r\n\r\nvoid factorize_odd(std::uint64_t\
    \ n, std::map<std::uint64_t, int> &mp) {\r\n  if (n < 2) return;\r\n  if (is_prime(n))\
    \ {\r\n    ++mp[n];\r\n    return;\r\n  }\r\n  std::uint64_t g = rho(n);\r\n \
    \ factorize_odd(n / g, mp);\r\n  factorize_odd(g, mp);\r\n}\r\n\r\n} // namespace\
    \ lib::internal\r\n\r\nnamespace lib {\r\n\r\nstd::map<std::uint64_t, int> factorize(std::uint64_t\
    \ n) {\r\n  std::map<std::uint64_t, int> res;\r\n  if (n < 2) return res;\r\n\
    \  int t = 0;\r\n  while ((n & 1) == 0) n >>= 1, ++t;\r\n  if (t) res[2] = t;\r\
    \n  internal::factorize_odd(n, res);\r\n  return res;\r\n}\r\n\r\n} // namespace\
    \ lib\r\n\r\n\n#line 6 \"remote_test/yosupo/math/factorize.0.test.cpp\"\n\r\n\
    int main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int Q;\r\n  std::cin >> Q;\r\n  while (Q--) {\r\n    long long a;\r\n    std::cin\
    \ >> a;\r\n    std::vector<long long> factor;\r\n    auto mp = lib::factorize(a);\r\
    \n    for (auto i : mp) {\r\n      for (int j = i.second; j > 0; --j) factor.push_back(i.first);\r\
    \n    }\r\n    std::cout << factor.size() << ' ';\r\n    for (auto i : factor)\
    \ std::cout << i << ' ';\r\n    std::cout << '\\n';\r\n  }\r\n  return 0;\r\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\r\n\r\n#include\
    \ <iostream>\r\n\r\n#include \"math/basic/integer_factorization_Pollard_rho.hpp\"\
    \r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  int Q;\r\n  std::cin >> Q;\r\n  while (Q--) {\r\n  \
    \  long long a;\r\n    std::cin >> a;\r\n    std::vector<long long> factor;\r\n\
    \    auto mp = lib::factorize(a);\r\n    for (auto i : mp) {\r\n      for (int\
    \ j = i.second; j > 0; --j) factor.push_back(i.first);\r\n    }\r\n    std::cout\
    \ << factor.size() << ' ';\r\n    for (auto i : factor) std::cout << i << ' ';\r\
    \n    std::cout << '\\n';\r\n  }\r\n  return 0;\r\n}"
  dependsOn:
  - math/basic/integer_factorization_Pollard_rho.hpp
  - modint/runtime_long_Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/factorize.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/factorize.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/factorize.0.test.cpp
- /verify/remote_test/yosupo/math/factorize.0.test.cpp.html
title: remote_test/yosupo/math/factorize.0.test.cpp
---
