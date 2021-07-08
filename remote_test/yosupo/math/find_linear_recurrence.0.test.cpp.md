---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
    title: "find shortest LFSR Berlekamp-Massey / \u5BFB\u627E\u6700\u77ED\u7EBF\u6027\
      \u9012\u63A8 Berlekamp-Massey \u7B97\u6CD5"
  - icon: ':heavy_check_mark:'
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
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\n\
    \n#include <iostream>\n#include <vector>\n\n#line 1 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
    \n\n\n\n/**\n * @brief find shortest LFSR Berlekamp-Massey / \u5BFB\u627E\u6700\
    \u77ED\u7EBF\u6027\u9012\u63A8 Berlekamp-Massey \u7B97\u6CD5\n * @docs docs/math/modulo/find_shortest_LFSR_Berlekamp_Massey.md\n\
    \ */\n\n#include <numeric>\n#include <utility>\n#line 12 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @brief \u5BFB\u627E\u6700\u77ED LFSR \uFF08\u4F46\
    \u4EC5\u5F53 L*2 <= N \u65F6\u552F\u4E00\uFF09\n * @ref J.L. Massey, Shift register\
    \ synthesis and BCH decoding,\n *      IEEE Trans. Inform. Theory, vol. IT-15,\
    \ 122\u2013127 (1969).\n * @tparam mod_t \u6709\u9664\u6CD5\uFF0C\u5FC5\u987B\u4E3A\
    \u57DF\n * @param s s_0, s_1, \u2026, s_{n-1}\n * @return std::vector<mod_t> C(x)=1+c_{1}*x+c_{2}*x^{2}+\
    \ \u2026 +c_{L}*x^{L}\n *         \u5BF9\u4E8E\u6240\u6709 i>=L \u548C s = s_0,\
    \ s_1, \u2026, s_{L-1}\n *         \u6EE1\u8DB3 s_{i} + c_{1}*s_{i-1} + c_{2}*s_{i-2}\
    \ + \u2026 + c_{L}*s_{i-L} = 0\n */\ntemplate <typename mod_t> std::vector<mod_t>\
    \ find_LFSR(const std::vector<mod_t> &s) {\n  const mod_t ZERO(0);\n  std::vector<mod_t>\
    \ C{mod_t(1)}, B(C);\n  mod_t b(1);\n  for (int N = 0, n = s.size(), L = 0, x\
    \ = 1; N < n; ++N) {\n    mod_t d(s[N]);\n    for (int i = 1; i <= L; ++i) d +=\
    \ C[i] * s[N - i];\n    if (d == ZERO) {\n      ++x;\n    } else if ((L << 1)\
    \ > N) {\n      // C(D)=C(D)-d/bD^xB(D)\n      if (C.size() < B.size() + x) C.resize(B.size()\
    \ + x, ZERO);\n      mod_t coef = d / b;\n      for (int i = x, ie = B.size()\
    \ + x; i < ie; ++i) C[i] -= coef * B[i - x];\n      ++x;\n    } else {\n     \
    \ std::vector<mod_t> T(C); // \u8BB0\u5F55 next discrepancy\n      // C(D)=C(D)-d/bD^xB(D)\n\
    \      if (C.size() < B.size() + x) C.resize(B.size() + x, ZERO);\n      mod_t\
    \ coef = d / b;\n      for (int i = x, ie = B.size() + x; i < ie; ++i) C[i] -=\
    \ coef * B[i - x];\n      L = N + 1 - L, B = std::move(T), b = d, x = 1;\n   \
    \ }\n  }\n  return C;\n}\n\n} // namespace lib\n\n\n#line 1 \"modint/Montgomery_modint.hpp\"\
    \n\n\n\n/**\n * @brief Montgomery modint / Montgomery \u53D6\u6A21\u7C7B\n * @docs\
    \ docs/modint/Montgomery_modint.md\n */\n\n#include <cstdint>\n#line 11 \"modint/Montgomery_modint.hpp\"\
    \n#include <type_traits>\n\nnamespace lib {\n\n/**\n * @brief Montgomery \u53D6\
    \u6A21\u7C7B\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n\
    \ * @author Nyaan\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\n */\n\
    template <std::uint32_t mod> class MontgomeryModInt {\npublic:\n  using i32 =\
    \ std::int32_t;\n  using u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n\
    \  using m32 = MontgomeryModInt;\n\n  using value_type = u32;\n\n  static constexpr\
    \ u32 get_mod() { return mod; }\n\n  static constexpr u32 get_primitive_root_prime()\
    \ {\n    u32 tmp[32] = {};\n    int cnt = 0;\n    const u32 phi = mod - 1;\n \
    \   u32 m = phi;\n    for (u32 i = 2; i * i <= m; ++i) {\n      if (m % i == 0)\
    \ {\n        tmp[cnt++] = i;\n        do {\n          m /= i;\n        } while\
    \ (m % i == 0);\n      }\n    }\n    if (m != 1) tmp[cnt++] = m;\n    for (m32\
    \ res = 2;; res += 1) {\n      bool f = true;\n      for (int i = 0; i < cnt &&\
    \ f; ++i) f &= res.pow(phi / tmp[i]) != 1;\n      if (f) return u32(res);\n  \
    \  }\n  }\n\n  constexpr MontgomeryModInt() = default;\n  ~MontgomeryModInt()\
    \ = default;\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  constexpr MontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) +\
    \ i32(mod)) * r2)) {}\n\n  constexpr MontgomeryModInt(const m32 &) = default;\n\
    \n  constexpr u32 get() const { return norm(reduce(v_)); }\n\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  explicit constexpr operator\
    \ T() const {\n    return T(get());\n  }\n\n  constexpr m32 operator-() const\
    \ {\n    m32 res;\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\n    return res;\n \
    \ }\n\n  constexpr m32 inv() const {\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\n\
    \    while (b != 0) {\n      i32 q = a / b, x1_old = x1, a_old = a;\n      x1\
    \ = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n    }\n    return m32(x1);\n\
    \  }\n\n  constexpr m32 &operator=(const m32 &) = default;\n\n  constexpr m32\
    \ &operator+=(const m32 &rhs) {\n    v_ += rhs.v_ - mod2;\n    v_ += mod2 & -(v_\
    \ >> 31);\n    return *this;\n  }\n  constexpr m32 &operator-=(const m32 &rhs)\
    \ {\n    v_ -= rhs.v_;\n    v_ += mod2 & -(v_ >> 31);\n    return *this;\n  }\n\
    \  constexpr m32 &operator*=(const m32 &rhs) {\n    v_ = reduce(u64(v_) * rhs.v_);\n\
    \    return *this;\n  }\n  constexpr m32 &operator/=(const m32 &rhs) { return\
    \ operator*=(rhs.inv()); }\n  friend constexpr m32 operator+(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) += rhs; }\n  friend constexpr m32 operator-(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }\n  friend constexpr m32\
    \ operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\n  friend\
    \ constexpr m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /=\
    \ rhs; }\n  friend constexpr bool operator==(const m32 &lhs, const m32 &rhs) {\n\
    \    return norm(lhs.v_) == norm(rhs.v_);\n  }\n  friend constexpr bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) {\n    return norm(lhs.v_) != norm(rhs.v_);\n  }\n\
    \n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\n    i32 x;\n\
    \    is >> x;\n    rhs = m32(x);\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m32 &rhs) { return os << rhs.get(); }\n\n  constexpr m32 pow(u64\
    \ y) const {\n    m32 res(1), x(*this);\n    for (; y != 0; y >>= 1, x *= x)\n\
    \      if (y & 1) res *= x;\n    return res;\n  }\n\nprivate:\n  static constexpr\
    \ u32 get_r() {\n    u32 two = 2, iv = mod * (two - mod * mod);\n    iv *= two\
    \ - mod * iv;\n    iv *= two - mod * iv;\n    return iv * (mod * iv - two);\n\
    \  }\n\n  static constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod)\
    \ >> 32; }\n  static constexpr u32 norm(u32 x) { return x - (mod & -((mod - 1\
    \ - x) >> 31)); }\n\n  u32 v_;\n\n  static constexpr u32 r = get_r();\n  static\
    \ constexpr u32 r2 = -u64(mod) % mod;\n  static constexpr u32 mod2 = mod << 1;\n\
    \n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\n  static_assert(-r *\
    \ mod == 1, \"???\\n\");\n  static_assert((mod & (3U << 30)) == 0, \"mod >= (1\
    \ << 30)\\n\");\n  static_assert(mod != 1, \"mod == 1\\n\");\n};\n\n// \u522B\u540D\
    \ntemplate <std::uint32_t mod> using MontModInt = MontgomeryModInt<mod>;\n\n}\
    \ // namespace lib\n\n\n#line 8 \"remote_test/yosupo/math/find_linear_recurrence.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n;\n  std::cin >> n;\n  std::vector<lib::MontModInt<998244353>> s(n);\n\
    \  for (auto &i : s) std::cin >> i;\n  auto rec = lib::find_LFSR(s);\n  std::cout\
    \ << rec.size() - 1 << '\\n';\n  for (int i = 1, ie = rec.size(); i < ie; ++i)\
    \ std::cout << -rec[i] << ' ';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\
    \n\n#include <iostream>\n#include <vector>\n\n#include \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
    \n#include \"modint/Montgomery_modint.hpp\"\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"\
    in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n  int n;\n  std::cin >> n;\n  std::vector<lib::MontModInt<998244353>>\
    \ s(n);\n  for (auto &i : s) std::cin >> i;\n  auto rec = lib::find_LFSR(s);\n\
    \  std::cout << rec.size() - 1 << '\\n';\n  for (int i = 1, ie = rec.size(); i\
    \ < ie; ++i) std::cout << -rec[i] << ' ';\n  return 0;\n}"
  dependsOn:
  - math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-08 03:55:34+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
- /verify/remote_test/yosupo/math/find_linear_recurrence.0.test.cpp.html
title: remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
---
