---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/NTT_crt.hpp
    title: "NTT prime crt / NTT \u7D20\u6570\u7528\u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/arbitrary_modulo_convolution.hpp
    title: "arbitrary modulo convolution / \u4EFB\u610F\u6A21\u6570\u5377\u79EF"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/convolution.hpp
    title: "convolution / \u5377\u79EF"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  - icon: ':question:'
    path: modint/Montgomery_modint.hpp
    title: "Montgomery modint / Montgomery \u53D6\u6A21\u7C7B"
  - icon: ':heavy_check_mark:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_1000000007
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_1000000007
  bundledCode: "#line 1 \"remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\
    \r\n\r\n#include <iostream>\r\n#include <vector>\r\n\r\n#line 1 \"math/formal_power_series/arbitrary_modulo_convolution.hpp\"\
    \n\n\n\r\n/**\r\n * @brief arbitrary modulo convolution / \u4EFB\u610F\u6A21\u6570\
    \u5377\u79EF\r\n *\r\n */\r\n\r\n#include <cstdint>\r\n#line 11 \"math/formal_power_series/arbitrary_modulo_convolution.hpp\"\
    \n\r\n#line 1 \"math/formal_power_series/NTT_crt.hpp\"\n\n\n\r\n/**\r\n * @brief\
    \ NTT prime crt / NTT \u7D20\u6570\u7528\u4E2D\u56FD\u5269\u4F59\u5B9A\u7406\r\
    \n *\r\n */\r\n\r\n#line 10 \"math/formal_power_series/NTT_crt.hpp\"\n#include\
    \ <type_traits>\r\n\r\nnamespace lib {\r\n\r\ntemplate <std::uint32_t M0, std::uint32_t\
    \ M1, std::uint32_t M2,\r\n          std::enable_if_t<(M0 < M1) && ((M0 | M1 |\
    \ M2) < (1U << 31)) &&\r\n                               ((M0 & M1 & M2 & 1) ==\
    \ 1) && (M0 != M1) && (M0 != M2) && (M1 != M2),\r\n                          \
    \ int> = 0>\r\nclass NTTCRT3 {\r\npublic:\r\n  using u32 = std::uint32_t;\r\n\
    \  using u64 = std::uint64_t;\r\n\r\n  NTTCRT3(u32 mod) : m_(mod), M0M1_mod_m_(u64(M0)\
    \ * M1 % mod) {}\r\n  ~NTTCRT3() = default;\r\n\r\n  u32 operator()(u32 a, u32\
    \ b, u32 c) const {\r\n    // x mod M0 = a, x mod M1 = b, x mod M2 = c\r\n   \
    \ // a + k0M0 = b + k1M1 => k0 = (b - a) / M0 (mod M1)\r\n    // x = a + k0M0\
    \ (mod M0M1) => a + k0M0 + k01M0M1 = c + k2M2\r\n    // => k01 = (c - (a + k0M0))\
    \ / (M0M1) (mod M2)\r\n    // => x mod M0M1M2 = a + k0M0 + k01M0M1\r\n    u32\
    \ k0 = b - a;\r\n    if (int(k0) < 0) k0 += M1;\r\n    k0      = u64(k0) * M0_inv_M1_\
    \ % M1;\r\n    u64 d   = a + u64(k0) * M0;\r\n    u32 k01 = c - d % M2;\r\n  \
    \  if (int(k01) < 0) k01 += M2;\r\n    // NTT \u6A21\u6570\u90FD\u5C0F\u4E8E (1U\
    \ << 31) \u6240\u4EE5\u5728\u8FD9\u91CC\u53EF\u4EE5\u4F7F\u7528\u52A0\u6CD5\u540E\
    \u518D\u53D6\u6A21\r\n    return (d + u64(k01) * M0M1_inv_M2_ % M2 * M0M1_mod_m_)\
    \ % m_;\r\n  }\r\n\r\n  static constexpr u32 get_inv(u32 x, u32 mod) {\r\n   \
    \ u32 res = 1;\r\n    for (u32 e = mod - 2; e != 0; e >>= 1) {\r\n      if (e\
    \ & 1) res = u64(res) * x % mod;\r\n      x = u64(x) * x % mod;\r\n    }\r\n \
    \   return res;\r\n  }\r\n\r\nprivate:\r\n  u32 m_, M0M1_mod_m_;\r\n  static constexpr\
    \ u32 M0_inv_M1_   = get_inv(M0, M1);\r\n  static constexpr u32 M0M1_inv_M2_ =\
    \ get_inv(u64(M0) * M1 % M2, M2);\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line\
    \ 1 \"math/formal_power_series/convolution.hpp\"\n\n\n\r\n/**\r\n * @brief convolution\
    \ / \u5377\u79EF\r\n *\r\n */\r\n\r\n#line 10 \"math/formal_power_series/convolution.hpp\"\
    \n\r\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\r\n * @docs docs/math/formal_power_series/radix_2_NTT.md\r\
    \n */\r\n\r\n#include <algorithm>\r\n#include <cassert>\r\n#line 13 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\r\n#line 1 \"traits/modint.hpp\"\n\n\n\r\n/**\r\n * @brief modint traits /\
    \ \u53D6\u6A21\u7C7B\u8403\u53D6\r\n *\r\n */\r\n\r\nnamespace lib {\r\n\r\ntemplate\
    \ <typename mod_t>\r\nstruct modint_traits {\r\n  using type = typename mod_t::value_type;\r\
    \n  static constexpr type get_mod() { return mod_t::get_mod(); }\r\n  static constexpr\
    \ type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 15 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @note \u5FC5\u987B\u7528 NTT \u53CB\u597D\
    \u7684\u6A21\u6570\uFF01\uFF01\uFF01\r\n */\r\ntemplate <typename mod_t>\r\nclass\
    \ NTT {\r\npublic:\r\n  NTT() = delete;\r\n\r\n  static void set_root(int len)\
    \ {\r\n    static int lim = 0;\r\n    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\r\
    \n    if (lim == 0) {\r\n      rt.resize(1 << 20);\r\n      irt.resize(1 << 20);\r\
    \n      rt[0] = irt[0] = 1;\r\n      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod()\
    \ >> 21), ig_t = g_t.inv();\r\n      rt[1 << 19] = g_t, irt[1 << 19] = ig_t;\r\
    \n      for (int i = 18; i >= 0; --i) {\r\n        g_t *= g_t, ig_t *= ig_t;\r\
    \n        rt[1 << i] = g_t, irt[1 << i] = ig_t;\r\n      }\r\n      lim = 1;\r\
    \n    }\r\n    for (; (lim << 1) < len; lim <<= 1) {\r\n      mod_t g = rt[lim],\
    \ ig = irt[lim];\r\n      for (int i = lim + 1, e = lim << 1; i < e; ++i) {\r\n\
    \        rt[i]  = rt[i - lim] * g;\r\n        irt[i] = irt[i - lim] * ig;\r\n\
    \      }\r\n    }\r\n  }\r\n\r\n  static void dft(int n, mod_t *x) {\r\n    for\
    \ (int j = 0, l = n >> 1; j != l; ++j) {\r\n      mod_t u = x[j], v = x[j + l];\r\
    \n      x[j] = u + v, x[j + l] = u - v;\r\n    }\r\n    for (int i = n >> 1; i\
    \ >= 2; i >>= 1) {\r\n      for (int j = 0, l = i >> 1; j != l; ++j) {\r\n   \
    \     mod_t u = x[j], v = x[j + l];\r\n        x[j] = u + v, x[j + l] = u - v;\r\
    \n      }\r\n      for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {\r\
    \n        mod_t root = rt[m];\r\n        for (int k = 0; k != l; ++k) {\r\n  \
    \        mod_t u = x[j + k], v = x[j + k + l] * root;\r\n          x[j + k] =\
    \ u + v, x[j + k + l] = u - v;\r\n        }\r\n      }\r\n    }\r\n  }\r\n\r\n\
    \  static void idft(int n, mod_t *x) {\r\n    for (int i = 2; i < n; i <<= 1)\
    \ {\r\n      for (int j = 0, l = i >> 1; j != l; ++j) {\r\n        mod_t u = x[j],\
    \ v = x[j + l];\r\n        x[j] = u + v, x[j + l] = u - v;\r\n      }\r\n    \
    \  for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {\r\n        mod_t\
    \ root = irt[m];\r\n        for (int k = 0; k != l; ++k) {\r\n          mod_t\
    \ u = x[j + k], v = x[j + k + l];\r\n          x[j + k] = u + v, x[j + k + l]\
    \ = (u - v) * root;\r\n        }\r\n      }\r\n    }\r\n    mod_t iv(mod_t(n).inv());\r\
    \n    for (int j = 0, l = n >> 1; j != l; ++j) {\r\n      mod_t u = x[j] * iv,\
    \ v = x[j + l] * iv;\r\n      x[j] = u + v, x[j + l] = u - v;\r\n    }\r\n  }\r\
    \n\r\n  static void even_dft(int n, mod_t *x) {\r\n    static constexpr mod_t\
    \ IT(mod_t(2).inv());\r\n    for (int i = 0, j = 0; i != n; i += 2, ++j) x[j]\
    \ = IT * (x[i] + x[i + 1]);\r\n  }\r\n\r\n  static void odd_dft(int n, mod_t *x)\
    \ {\r\n    static constexpr mod_t IT(mod_t(2).inv());\r\n    for (int i = 0, j\
    \ = 0; i != n; i += 2, ++j) x[j] = IT * irt[j] * (x[i] - x[i + 1]);\r\n  }\r\n\
    \r\n  static void dft_doubling(int n, mod_t *x) {\r\n    static constexpr mod_t\
    \ g(modint_traits<mod_t>::get_primitive_root_prime());\r\n    std::copy_n(x, n,\
    \ x + n);\r\n    idft(n, x + n);\r\n    mod_t k(1), t(g.pow((modint_traits<mod_t>::get_mod()\
    \ - 1) / (n << 1)));\r\n    for (int i = 0; i != n; ++i) x[n + i] *= k, k *= t;\r\
    \n    dft(n, x + n);\r\n  }\r\n\r\nprivate:\r\n  static inline std::vector<mod_t>\
    \ rt, irt;\r\n};\r\n\r\nstd::uint32_t get_ntt_len(std::uint32_t n) {\r\n  --n;\r\
    \n  n |= n >> 1;\r\n  n |= n >> 2;\r\n  n |= n >> 4;\r\n  n |= n >> 8;\r\n  return\
    \ (n | n >> 16) + 1;\r\n}\r\n\r\n/**\r\n * @brief \u63A5\u6536\u4E00\u4E2A\u591A\
    \u9879\u5F0F\uFF0C\u8FD4\u56DE\u4E8C\u8FDB\u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\
    \u5217\uFF0C\u5373 x(1), x(-1) \u7B49\uFF0C\r\n *        \u5BF9\u4E8E\u4E0B\u6807\
    \ i \u548C i^1 \u5FC5\u7136\u662F\u4E24\u4E2A\u4E92\u4E3A\u76F8\u53CD\u6570\u7684\
    \u70B9\u503C\r\n *\r\n * @tparam mod_t\r\n * @param n\r\n * @param x\r\n */\r\n\
    template <typename mod_t>\r\nvoid dft(int n, mod_t *x) {\r\n  NTT<mod_t>::set_root(n);\r\
    \n  NTT<mod_t>::dft(n, x);\r\n}\r\n\r\n/**\r\n * @brief \u63A5\u6536\u4E8C\u8FDB\
    \u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\u5217\uFF0C\u8FD4\u56DE\u591A\u9879\u5F0F\
    \u5E8F\u5217 mod (x^n - 1)\r\n *\r\n * @tparam mod_t\r\n * @param n\r\n * @param\
    \ x\r\n */\r\ntemplate <typename mod_t>\r\nvoid idft(int n, mod_t *x) {\r\n  NTT<mod_t>::set_root(n);\r\
    \n  NTT<mod_t>::idft(n, x);\r\n}\r\n\r\ntemplate <typename mod_t>\r\nvoid dft(std::vector<mod_t>\
    \ &x) {\r\n  NTT<mod_t>::set_root(x.size());\r\n  NTT<mod_t>::dft(x.size(), x.data());\r\
    \n}\r\n\r\ntemplate <typename mod_t>\r\nvoid idft(std::vector<mod_t> &x) {\r\n\
    \  NTT<mod_t>::set_root(x.size());\r\n  NTT<mod_t>::idft(x.size(), x.data());\r\
    \n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 12 \"math/formal_power_series/convolution.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief NTT \u6A21\u6570\u5377\u79EF\r\n\
    \ * @tparam mod_t NTT \u53CB\u597D\u7684\u6A21\u6570\u7C7B\r\n */\r\ntemplate\
    \ <typename mod_t>\r\nstd::vector<mod_t> convolve(const std::vector<mod_t> &x,\
    \ const std::vector<mod_t> &y) {\r\n  int n = x.size(), m = y.size();\r\n  if\
    \ (std::min(n, m) <= 32) {\r\n    std::vector<mod_t> res(n + m - 1, mod_t(0));\r\
    \n    for (int i = 0; i < n; ++i)\r\n      for (int j = 0; j < m; ++j) res[i +\
    \ j] += x[i] * y[j];\r\n    return res;\r\n  }\r\n  int len = get_ntt_len(n +\
    \ m - 1);\r\n  std::vector<mod_t> res(len);\r\n  std::copy_n(x.begin(), n, res.begin());\r\
    \n  std::fill(res.begin() + n, res.end(), mod_t(0));\r\n  dft(res);\r\n  if (&x\
    \ == &y) {\r\n    for (int i = 0; i < len; ++i) res[i] *= res[i];\r\n  } else\
    \ {\r\n    std::vector<mod_t> y_tmp(len);\r\n    std::copy_n(y.begin(), m, y_tmp.begin());\r\
    \n    std::fill(y_tmp.begin() + m, y_tmp.end(), mod_t(0));\r\n    dft(y_tmp);\r\
    \n    for (int i = 0; i < len; ++i) res[i] *= y_tmp[i];\r\n  }\r\n  idft(res);\r\
    \n  res.resize(n + m - 1);\r\n  return res;\r\n}\r\n\r\n} // namespace lib\r\n\
    \r\n\n#line 1 \"modint/Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n * @brief Montgomery\
    \ modint / Montgomery \u53D6\u6A21\u7C7B\r\n * @docs docs/modint/Montgomery_modint.md\r\
    \n */\r\n\r\n#line 12 \"modint/Montgomery_modint.hpp\"\n\r\nnamespace lib {\r\n\
    \r\n/**\r\n * @brief Montgomery \u53D6\u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
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
    \ = MontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 15 \"math/formal_power_series/arbitrary_modulo_convolution.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u4EFB\u610F\u6A21\u6570\u5377\u79EF\
    \r\n * @note \u53EA\u9002\u7528\u4E8E\u6A21\u6570\u4E3A 32 \u4F4D\r\n */\r\ntemplate\
    \ <typename Int, typename ModType>\r\nstd::enable_if_t<std::is_integral_v<ModType>\
    \ && (sizeof(ModType) <= 4) && std::is_integral_v<Int>,\r\n                 std::vector<Int>>\r\
    \nconvolve_mod(const std::vector<Int> &x, const std::vector<Int> &y, ModType mod)\
    \ {\r\n  using u32               = std::uint32_t;\r\n  static constexpr u32 M0\
    \ = 880803841, M1 = 897581057, M2 = 998244353;\r\n  NTTCRT3<M0, M1, M2> crt(mod);\r\
    \n  using mod_t0 = MontModInt<M0>;\r\n  using mod_t1 = MontModInt<M1>;\r\n  using\
    \ mod_t2 = MontModInt<M2>;\r\n  auto res0 =\r\n      convolve(std::vector<mod_t0>(x.begin(),\
    \ x.end()), std::vector<mod_t0>(y.begin(), y.end()));\r\n  auto res1 =\r\n   \
    \   convolve(std::vector<mod_t1>(x.begin(), x.end()), std::vector<mod_t1>(y.begin(),\
    \ y.end()));\r\n  auto res2 =\r\n      convolve(std::vector<mod_t2>(x.begin(),\
    \ x.end()), std::vector<mod_t2>(y.begin(), y.end()));\r\n  int n = res0.size();\r\
    \n  std::vector<Int> res;\r\n  res.reserve(n);\r\n  for (int i = 0; i < n; ++i)\
    \ res.emplace_back(crt(u32(res0[i]), u32(res1[i]), u32(res2[i])));\r\n  return\
    \ res;\r\n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 7 \"remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n, m;\r\n  std::cin >> n >> m;\r\n  std::vector<int> A(n), B(m);\r\n \
    \ for (auto &i : A) std::cin >> i;\r\n  for (auto &i : B) std::cin >> i;\r\n \
    \ for (auto i : lib::convolve_mod(A, B, 1000000007)) std::cout << i << ' ';\r\n\
    \  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\
    \r\n\r\n#include <iostream>\r\n#include <vector>\r\n\r\n#include \"math/formal_power_series/arbitrary_modulo_convolution.hpp\"\
    \r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  int n, m;\r\n  std::cin >> n >> m;\r\n  std::vector<int>\
    \ A(n), B(m);\r\n  for (auto &i : A) std::cin >> i;\r\n  for (auto &i : B) std::cin\
    \ >> i;\r\n  for (auto i : lib::convolve_mod(A, B, 1000000007)) std::cout << i\
    \ << ' ';\r\n  return 0;\r\n}"
  dependsOn:
  - math/formal_power_series/arbitrary_modulo_convolution.hpp
  - math/formal_power_series/NTT_crt.hpp
  - math/formal_power_series/convolution.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
- /verify/remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp.html
title: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
---
