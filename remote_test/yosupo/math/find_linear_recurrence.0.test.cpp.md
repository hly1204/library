---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
    title: "find shortest LFSR Berlekamp-Massey / \u5BFB\u627E\u6700\u77ED\u7EBF\u6027\
      \u9012\u63A8 Berlekamp-Massey \u7B97\u6CD5"
  - icon: ':question:'
    path: modint/Montgomery_modint.hpp
    title: "Montgomery modint / Montgomery \u53D6\u6A21\u7C7B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/find_linear_recurrence
    links:
    - https://judge.yosupo.jp/problem/find_linear_recurrence
  bundledCode: "#line 1 \"remote_test/yosupo/math/find_linear_recurrence.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\r\
    \n\r\n#include <iostream>\r\n#include <vector>\r\n\r\n#line 1 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
    \n\n\n\r\n/**\r\n * @brief find shortest LFSR Berlekamp-Massey / \u5BFB\u627E\u6700\
    \u77ED\u7EBF\u6027\u9012\u63A8 Berlekamp-Massey \u7B97\u6CD5\r\n * @docs docs/math/modulo/find_shortest_LFSR_Berlekamp_Massey.md\r\
    \n */\r\n\r\n#include <numeric>\r\n#include <utility>\r\n#line 12 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u5BFB\u627E\u6700\u77ED LFSR \uFF08\
    \u4F46\u4EC5\u5F53 L*2 <= N \u65F6\u552F\u4E00\uFF09\r\n * @ref J.L. Massey, Shift\
    \ register synthesis and BCH decoding,\r\n *      IEEE Trans. Inform. Theory,\
    \ vol. IT-15, 122\u2013127 (1969).\r\n * @tparam mod_t \u6709\u9664\u6CD5\uFF0C\
    \u5FC5\u987B\u4E3A\u57DF\r\n * @param s s_0, s_1, \u2026, s_{n-1}\r\n * @return\
    \ std::vector<mod_t> C(x)=1+c_{1}*x+c_{2}*x^{2}+ \u2026 +c_{L}*x^{L}\r\n *   \
    \      \u5BF9\u4E8E\u6240\u6709 i>=L \u548C s = s_0, s_1, \u2026, s_{L-1}\r\n\
    \ *         \u6EE1\u8DB3 s_{i} + c_{1}*s_{i-1} + c_{2}*s_{i-2} + \u2026 + c_{L}*s_{i-L}\
    \ = 0\r\n */\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t> find_LFSR(const\
    \ std::vector<mod_t> &s) {\r\n  const mod_t ZERO(0);\r\n  std::vector<mod_t> C{mod_t(1)},\
    \ B(C);\r\n  mod_t b(1);\r\n  for (int N = 0, n = s.size(), L = 0, x = 1; N <\
    \ n; ++N) {\r\n    mod_t d(s[N]);\r\n    for (int i = 1; i <= L; ++i) d += C[i]\
    \ * s[N - i];\r\n    if (d == ZERO) {\r\n      ++x;\r\n    } else if ((L << 1)\
    \ > N) {\r\n      // C(D)=C(D)-d/bD^xB(D)\r\n      if (C.size() < B.size() + x)\
    \ C.resize(B.size() + x, ZERO);\r\n      mod_t coef = d / b;\r\n      for (int\
    \ i = x, ie = B.size() + x; i < ie; ++i) C[i] -= coef * B[i - x];\r\n      ++x;\r\
    \n    } else {\r\n      std::vector<mod_t> T(C); // \u8BB0\u5F55 next discrepancy\r\
    \n      // C(D)=C(D)-d/bD^xB(D)\r\n      if (C.size() < B.size() + x) C.resize(B.size()\
    \ + x, ZERO);\r\n      mod_t coef = d / b;\r\n      for (int i = x, ie = B.size()\
    \ + x; i < ie; ++i) C[i] -= coef * B[i - x];\r\n      L = N + 1 - L, B = std::move(T),\
    \ b = d, x = 1;\r\n    }\r\n  }\r\n  return C;\r\n}\r\n\r\n} // namespace lib\r\
    \n\r\n\n#line 1 \"modint/Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n * @brief Montgomery\
    \ modint / Montgomery \u53D6\u6A21\u7C7B\r\n * @docs docs/modint/Montgomery_modint.md\r\
    \n */\r\n\r\n#include <cstdint>\r\n#line 11 \"modint/Montgomery_modint.hpp\"\n\
    #include <type_traits>\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief Montgomery\
    \ \u53D6\u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\r\n\
    \ */\r\ntemplate <std::uint32_t mod>\r\nclass MontgomeryModInt {\r\npublic:\r\n\
    \  using i32 = std::int32_t;\r\n  using u32 = std::uint32_t;\r\n  using u64 =\
    \ std::uint64_t;\r\n  using m32 = MontgomeryModInt;\r\n\r\n  using value_type\
    \ = u32;\r\n\r\n  static constexpr u32 get_mod() { return mod; }\r\n\r\n  static\
    \ constexpr u32 get_primitive_root_prime() {\r\n    u32 tmp[32]   = {};\r\n  \
    \  int cnt       = 0;\r\n    const u32 phi = mod - 1;\r\n    u32 m         = phi;\r\
    \n    for (u32 i = 2; i * i <= m; ++i) {\r\n      if (m % i == 0) {\r\n      \
    \  tmp[cnt++] = i;\r\n        do { m /= i; } while (m % i == 0);\r\n      }\r\n\
    \    }\r\n    if (m != 1) tmp[cnt++] = m;\r\n    for (m32 res = 2;; res += 1)\
    \ {\r\n      bool f = true;\r\n      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi\
    \ / tmp[i]) != 1;\r\n      if (f) return u32(res);\r\n    }\r\n  }\r\n\r\n  constexpr\
    \ MontgomeryModInt() = default;\r\n  ~MontgomeryModInt()          = default;\r\
    \n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\
    \n  constexpr MontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod)) *\
    \ r2)) {}\r\n\r\n  constexpr MontgomeryModInt(const m32 &) = default;\r\n\r\n\
    \  constexpr u32 get() const { return norm(reduce(v_)); }\r\n\r\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit constexpr\
    \ operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  constexpr m32 operator-()\
    \ const {\r\n    m32 res;\r\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  constexpr m32 inv() const {\r\n    i32 x1 = 1, x3 = 0,\
    \ a = get(), b = mod;\r\n    while (b != 0) {\r\n      i32 q = a / b, x1_old =\
    \ x1, a_old = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b\
    \ * q;\r\n    }\r\n    return m32(x1);\r\n  }\r\n\r\n  constexpr m32 &operator=(const\
    \ m32 &) = default;\r\n\r\n  constexpr m32 &operator+=(const m32 &rhs) {\r\n \
    \   v_ += rhs.v_ - mod2;\r\n    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\
    \n  }\r\n  constexpr m32 &operator-=(const m32 &rhs) {\r\n    v_ -= rhs.v_;\r\n\
    \    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\n  }\r\n  constexpr m32\
    \ &operator*=(const m32 &rhs) {\r\n    v_ = reduce(u64(v_) * rhs.v_);\r\n    return\
    \ *this;\r\n  }\r\n  constexpr m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend constexpr m32 operator+(const m32 &lhs, const m32 &rhs) { return\
    \ m32(lhs) += rhs; }\r\n  friend constexpr m32 operator-(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) -= rhs; }\r\n  friend constexpr m32 operator*(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\r\n  friend constexpr\
    \ m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }\r\n\
    \  friend constexpr bool operator==(const m32 &lhs, const m32 &rhs) {\r\n    return\
    \ norm(lhs.v_) == norm(rhs.v_);\r\n  }\r\n  friend constexpr bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) {\r\n    return norm(lhs.v_) != norm(rhs.v_);\r\n\
    \  }\r\n\r\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\r\n\
    \    i32 x;\r\n    is >> x;\r\n    rhs = m32(x);\r\n    return is;\r\n  }\r\n\
    \  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return\
    \ os << rhs.get(); }\r\n\r\n  constexpr m32 pow(u64 y) const {\r\n    m32 res(1),\
    \ x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n      if (y & 1) res *=\
    \ x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static constexpr u32 get_r()\
    \ {\r\n    u32 two = 2, iv = mod * (two - mod * mod);\r\n    iv *= two - mod *\
    \ iv;\r\n    iv *= two - mod * iv;\r\n    return iv * (mod * iv - two);\r\n  }\r\
    \n\r\n  static constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod)\
    \ >> 32; }\r\n  static constexpr u32 norm(u32 x) { return x - (mod & -((mod -\
    \ 1 - x) >> 31)); }\r\n\r\n  u32 v_;\r\n\r\n  static constexpr u32 r    = get_r();\r\
    \n  static constexpr u32 r2   = -u64(mod) % mod;\r\n  static constexpr u32 mod2\
    \ = mod << 1;\r\n\r\n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\r\n\
    \  static_assert(-r * mod == 1, \"???\\n\");\r\n  static_assert((mod & (3U <<\
    \ 30)) == 0, \"mod >= (1 << 30)\\n\");\r\n  static_assert(mod != 1, \"mod == 1\\\
    n\");\r\n};\r\n\r\n// \u522B\u540D\r\ntemplate <std::uint32_t mod>\r\nusing MontModInt\
    \ = MontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 8 \"remote_test/yosupo/math/find_linear_recurrence.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n;\r\n  std::cin >> n;\r\n  std::vector<lib::MontModInt<998244353>> s(n);\r\
    \n  for (auto &i : s) std::cin >> i;\r\n  auto rec = lib::find_LFSR(s);\r\n  std::cout\
    \ << rec.size() - 1 << '\\n';\r\n  for (int i = 1, ie = rec.size(); i < ie; ++i)\
    \ std::cout << -rec[i] << ' ';\r\n  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\
    \r\n\r\n#include <iostream>\r\n#include <vector>\r\n\r\n#include \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
    \r\n#include \"modint/Montgomery_modint.hpp\"\r\n\r\nint main() {\r\n#ifdef LOCAL\r\
    \n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\r\
    \n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\n  int\
    \ n;\r\n  std::cin >> n;\r\n  std::vector<lib::MontModInt<998244353>> s(n);\r\n\
    \  for (auto &i : s) std::cin >> i;\r\n  auto rec = lib::find_LFSR(s);\r\n  std::cout\
    \ << rec.size() - 1 << '\\n';\r\n  for (int i = 1, ie = rec.size(); i < ie; ++i)\
    \ std::cout << -rec[i] << ' ';\r\n  return 0;\r\n}"
  dependsOn:
  - math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
- /verify/remote_test/yosupo/math/find_linear_recurrence.0.test.cpp.html
title: remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
---
