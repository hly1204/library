---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/arbitrary_modulo_convolution.hpp
    title: "arbitrary modulo convolution / \u4EFB\u610F\u6A21\u6570\u5377\u79EF"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/chirp_z.hpp
    title: "chirp z transform / chirp z \u53D8\u6362"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/convolution.hpp
    title: "convolution / \u5377\u79EF"
  - icon: ':question:'
    path: math/formal_power_series/formal_power_series.hpp
    title: "basic operations of formal power series / \u5F62\u5F0F\u5E42\u7EA7\u6570\
      \u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp
    title: "linearly recurrent sequence Bostan-Mori / \u5E38\u7CFB\u6570\u7EBF\u6027\
      \u9012\u63A8\u5E8F\u5217 Bostan-Mori \u7B97\u6CD5"
  - icon: ':question:'
    path: math/formal_power_series/polynomial.hpp
    title: "polynomial / \u591A\u9879\u5F0F"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.1.test.cpp
    title: remote_test/yosupo/math/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/math/formal_power_series/radix_2_NTT.md
    document_title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\n\n\n\n/**\n\
    \ * @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\n * @docs docs/math/formal_power_series/radix_2_NTT.md\n\
    \ */\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <vector>\n\n#line 1 \"traits/modint.hpp\"\n\n\n\n/**\n * @brief modint traits\
    \ / \u53D6\u6A21\u7C7B\u8403\u53D6\n *\n */\n\nnamespace lib {\n\ntemplate <typename\
    \ mod_t> struct modint_traits {\n  using type = typename mod_t::value_type;\n\
    \  static constexpr type get_mod() { return mod_t::get_mod(); }\n  static constexpr\
    \ type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\n};\n\n} // namespace lib\n\n\n#line 15 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @note \u5FC5\u987B\u7528 NTT \u53CB\u597D\u7684\
    \u6A21\u6570\uFF01\uFF01\uFF01\n */\ntemplate <typename mod_t> class NTT {\npublic:\n\
    \  NTT() = delete;\n\n  static void set_root(int len) {\n    static int lim =\
    \ 0;\n    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\n\
    \    if (lim == 0) {\n      rt.resize(1 << 20);\n      irt.resize(1 << 20);\n\
    \      rt[0] = irt[0] = 1;\n      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod()\
    \ >> 21), ig_t = g_t.inv();\n      rt[1 << 19] = g_t, irt[1 << 19] = ig_t;\n \
    \     for (int i = 18; i >= 0; --i) {\n        g_t *= g_t, ig_t *= ig_t;\n   \
    \     rt[1 << i] = g_t, irt[1 << i] = ig_t;\n      }\n      lim = 1;\n    }\n\
    \    for (; (lim << 1) < len; lim <<= 1) {\n      mod_t g = rt[lim], ig = irt[lim];\n\
    \      for (int i = lim + 1, e = lim << 1; i < e; ++i) {\n        rt[i] = rt[i\
    \ - lim] * g;\n        irt[i] = irt[i - lim] * ig;\n      }\n    }\n  }\n\n  static\
    \ void dft(int n, mod_t *x) {\n    for (int j = 0, l = n >> 1; j != l; ++j) {\n\
    \      mod_t u = x[j], v = x[j + l];\n      x[j] = u + v, x[j + l] = u - v;\n\
    \    }\n    for (int i = n >> 1; i >= 2; i >>= 1) {\n      for (int j = 0, l =\
    \ i >> 1; j != l; ++j) {\n        mod_t u = x[j], v = x[j + l];\n        x[j]\
    \ = u + v, x[j + l] = u - v;\n      }\n      for (int j = i, l = i >> 1, m = 1;\
    \ j != n; j += i, ++m) {\n        mod_t root = rt[m];\n        for (int k = 0;\
    \ k != l; ++k) {\n          mod_t u = x[j + k], v = x[j + k + l] * root;\n   \
    \       x[j + k] = u + v, x[j + k + l] = u - v;\n        }\n      }\n    }\n \
    \ }\n\n  static void idft(int n, mod_t *x) {\n    for (int i = 2; i < n; i <<=\
    \ 1) {\n      for (int j = 0, l = i >> 1; j != l; ++j) {\n        mod_t u = x[j],\
    \ v = x[j + l];\n        x[j] = u + v, x[j + l] = u - v;\n      }\n      for (int\
    \ j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {\n        mod_t root = irt[m];\n\
    \        for (int k = 0; k != l; ++k) {\n          mod_t u = x[j + k], v = x[j\
    \ + k + l];\n          x[j + k] = u + v, x[j + k + l] = (u - v) * root;\n    \
    \    }\n      }\n    }\n    mod_t iv(mod_t(n).inv());\n    for (int j = 0, l =\
    \ n >> 1; j != l; ++j) {\n      mod_t u = x[j] * iv, v = x[j + l] * iv;\n    \
    \  x[j] = u + v, x[j + l] = u - v;\n    }\n  }\n\n  static void even_dft(int n,\
    \ mod_t *x) {\n    static constexpr mod_t IT(mod_t(2).inv());\n    for (int i\
    \ = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * (x[i] + x[i + 1]);\n  }\n\n  static\
    \ void odd_dft(int n, mod_t *x) {\n    static constexpr mod_t IT(mod_t(2).inv());\n\
    \    for (int i = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * irt[j] * (x[i] -\
    \ x[i + 1]);\n  }\n\n  static void dft_doubling(int n, mod_t *x) {\n    static\
    \ constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\n    std::copy_n(x,\
    \ n, x + n);\n    idft(n, x + n);\n    mod_t k(1), t(g.pow((modint_traits<mod_t>::get_mod()\
    \ - 1) / (n << 1)));\n    for (int i = 0; i != n; ++i) x[n + i] *= k, k *= t;\n\
    \    dft(n, x + n);\n  }\n\nprivate:\n  static inline std::vector<mod_t> rt, irt;\n\
    };\n\nstd::uint32_t get_ntt_len(std::uint32_t n) {\n  --n;\n  n |= n >> 1;\n \
    \ n |= n >> 2;\n  n |= n >> 4;\n  n |= n >> 8;\n  return (n | n >> 16) + 1;\n\
    }\n\n/**\n * @brief \u63A5\u6536\u4E00\u4E2A\u591A\u9879\u5F0F\uFF0C\u8FD4\u56DE\
    \u4E8C\u8FDB\u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\u5217\uFF0C\u5373 x(1),\
    \ x(-1) \u7B49\uFF0C\n *        \u5BF9\u4E8E\u4E0B\u6807 i \u548C i^1 \u5FC5\u7136\
    \u662F\u4E24\u4E2A\u4E92\u4E3A\u76F8\u53CD\u6570\u7684\u70B9\u503C\n *\n * @tparam\
    \ mod_t\n * @param n\n * @param x\n */\ntemplate <typename mod_t> void dft(int\
    \ n, mod_t *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::dft(n, x);\n}\n\n\
    /**\n * @brief \u63A5\u6536\u4E8C\u8FDB\u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\
    \u5217\uFF0C\u8FD4\u56DE\u591A\u9879\u5F0F\u5E8F\u5217 mod (x^n - 1)\n *\n * @tparam\
    \ mod_t\n * @param n\n * @param x\n */\ntemplate <typename mod_t> void idft(int\
    \ n, mod_t *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::idft(n, x);\n}\n\n\
    template <typename mod_t> void dft(std::vector<mod_t> &x) {\n  NTT<mod_t>::set_root(x.size());\n\
    \  NTT<mod_t>::dft(x.size(), x.data());\n}\n\ntemplate <typename mod_t> void idft(std::vector<mod_t>\
    \ &x) {\n  NTT<mod_t>::set_root(x.size());\n  NTT<mod_t>::idft(x.size(), x.data());\n\
    }\n\n} // namespace lib\n\n\n"
  code: "#ifndef RADIX_2_NTT_HEADER_HPP\n#define RADIX_2_NTT_HEADER_HPP\n\n/**\n *\
    \ @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\n * @docs docs/math/formal_power_series/radix_2_NTT.md\n\
    \ */\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <vector>\n\n#include \"../../traits/modint.hpp\"\n\nnamespace lib {\n\n/**\n\
    \ * @note \u5FC5\u987B\u7528 NTT \u53CB\u597D\u7684\u6A21\u6570\uFF01\uFF01\uFF01\
    \n */\ntemplate <typename mod_t> class NTT {\npublic:\n  NTT() = delete;\n\n \
    \ static void set_root(int len) {\n    static int lim = 0;\n    static constexpr\
    \ mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\n    if (lim == 0)\
    \ {\n      rt.resize(1 << 20);\n      irt.resize(1 << 20);\n      rt[0] = irt[0]\
    \ = 1;\n      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod() >> 21), ig_t =\
    \ g_t.inv();\n      rt[1 << 19] = g_t, irt[1 << 19] = ig_t;\n      for (int i\
    \ = 18; i >= 0; --i) {\n        g_t *= g_t, ig_t *= ig_t;\n        rt[1 << i]\
    \ = g_t, irt[1 << i] = ig_t;\n      }\n      lim = 1;\n    }\n    for (; (lim\
    \ << 1) < len; lim <<= 1) {\n      mod_t g = rt[lim], ig = irt[lim];\n      for\
    \ (int i = lim + 1, e = lim << 1; i < e; ++i) {\n        rt[i] = rt[i - lim] *\
    \ g;\n        irt[i] = irt[i - lim] * ig;\n      }\n    }\n  }\n\n  static void\
    \ dft(int n, mod_t *x) {\n    for (int j = 0, l = n >> 1; j != l; ++j) {\n   \
    \   mod_t u = x[j], v = x[j + l];\n      x[j] = u + v, x[j + l] = u - v;\n   \
    \ }\n    for (int i = n >> 1; i >= 2; i >>= 1) {\n      for (int j = 0, l = i\
    \ >> 1; j != l; ++j) {\n        mod_t u = x[j], v = x[j + l];\n        x[j] =\
    \ u + v, x[j + l] = u - v;\n      }\n      for (int j = i, l = i >> 1, m = 1;\
    \ j != n; j += i, ++m) {\n        mod_t root = rt[m];\n        for (int k = 0;\
    \ k != l; ++k) {\n          mod_t u = x[j + k], v = x[j + k + l] * root;\n   \
    \       x[j + k] = u + v, x[j + k + l] = u - v;\n        }\n      }\n    }\n \
    \ }\n\n  static void idft(int n, mod_t *x) {\n    for (int i = 2; i < n; i <<=\
    \ 1) {\n      for (int j = 0, l = i >> 1; j != l; ++j) {\n        mod_t u = x[j],\
    \ v = x[j + l];\n        x[j] = u + v, x[j + l] = u - v;\n      }\n      for (int\
    \ j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {\n        mod_t root = irt[m];\n\
    \        for (int k = 0; k != l; ++k) {\n          mod_t u = x[j + k], v = x[j\
    \ + k + l];\n          x[j + k] = u + v, x[j + k + l] = (u - v) * root;\n    \
    \    }\n      }\n    }\n    mod_t iv(mod_t(n).inv());\n    for (int j = 0, l =\
    \ n >> 1; j != l; ++j) {\n      mod_t u = x[j] * iv, v = x[j + l] * iv;\n    \
    \  x[j] = u + v, x[j + l] = u - v;\n    }\n  }\n\n  static void even_dft(int n,\
    \ mod_t *x) {\n    static constexpr mod_t IT(mod_t(2).inv());\n    for (int i\
    \ = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * (x[i] + x[i + 1]);\n  }\n\n  static\
    \ void odd_dft(int n, mod_t *x) {\n    static constexpr mod_t IT(mod_t(2).inv());\n\
    \    for (int i = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * irt[j] * (x[i] -\
    \ x[i + 1]);\n  }\n\n  static void dft_doubling(int n, mod_t *x) {\n    static\
    \ constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\n    std::copy_n(x,\
    \ n, x + n);\n    idft(n, x + n);\n    mod_t k(1), t(g.pow((modint_traits<mod_t>::get_mod()\
    \ - 1) / (n << 1)));\n    for (int i = 0; i != n; ++i) x[n + i] *= k, k *= t;\n\
    \    dft(n, x + n);\n  }\n\nprivate:\n  static inline std::vector<mod_t> rt, irt;\n\
    };\n\nstd::uint32_t get_ntt_len(std::uint32_t n) {\n  --n;\n  n |= n >> 1;\n \
    \ n |= n >> 2;\n  n |= n >> 4;\n  n |= n >> 8;\n  return (n | n >> 16) + 1;\n\
    }\n\n/**\n * @brief \u63A5\u6536\u4E00\u4E2A\u591A\u9879\u5F0F\uFF0C\u8FD4\u56DE\
    \u4E8C\u8FDB\u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\u5217\uFF0C\u5373 x(1),\
    \ x(-1) \u7B49\uFF0C\n *        \u5BF9\u4E8E\u4E0B\u6807 i \u548C i^1 \u5FC5\u7136\
    \u662F\u4E24\u4E2A\u4E92\u4E3A\u76F8\u53CD\u6570\u7684\u70B9\u503C\n *\n * @tparam\
    \ mod_t\n * @param n\n * @param x\n */\ntemplate <typename mod_t> void dft(int\
    \ n, mod_t *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::dft(n, x);\n}\n\n\
    /**\n * @brief \u63A5\u6536\u4E8C\u8FDB\u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\
    \u5217\uFF0C\u8FD4\u56DE\u591A\u9879\u5F0F\u5E8F\u5217 mod (x^n - 1)\n *\n * @tparam\
    \ mod_t\n * @param n\n * @param x\n */\ntemplate <typename mod_t> void idft(int\
    \ n, mod_t *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::idft(n, x);\n}\n\n\
    template <typename mod_t> void dft(std::vector<mod_t> &x) {\n  NTT<mod_t>::set_root(x.size());\n\
    \  NTT<mod_t>::dft(x.size(), x.data());\n}\n\ntemplate <typename mod_t> void idft(std::vector<mod_t>\
    \ &x) {\n  NTT<mod_t>::set_root(x.size());\n  NTT<mod_t>::idft(x.size(), x.data());\n\
    }\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - traits/modint.hpp
  isVerificationFile: false
  path: math/formal_power_series/radix_2_NTT.hpp
  requiredBy:
  - math/formal_power_series/convolution.hpp
  - math/formal_power_series/chirp_z.hpp
  - math/formal_power_series/arbitrary_modulo_convolution.hpp
  - math/formal_power_series/polynomial.hpp
  - math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp
  - math/formal_power_series/formal_power_series.hpp
  timestamp: '2021-07-13 17:52:29+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  - remote_test/yosupo/math/convolution_mod.0.test.cpp
  - remote_test/yosupo/math/convolution_mod.1.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
documentation_of: math/formal_power_series/radix_2_NTT.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/radix_2_NTT.hpp
- /library/math/formal_power_series/radix_2_NTT.hpp.html
title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
---
## 常用 NTT 友好的模数

我们知道 NTT 友好的模数 $p$ 是素数且 $-1\bmod{p}$ 一定是二次剩余。在 $\mathbb{C}$ 中的 FFT 依靠的就是幂次为 $1$ 的元素即单位根，而在 NTT 中我们可以知道也存在阶为 $2$ 的幂次的元素，于是可以做 radix-2 NTT ，但 FFT 显然更灵活。

根据 Legendre 符号我们知道当 $p$ 为奇素数时， $\left(\frac{-1}{p}\right)\equiv (-1)^{(p-1)/2}\pmod{p}$ 若 $\left(\frac{-1}{p}\right)\equiv 1\pmod{p}$ 则为二次剩余，那么意味着 $p\bmod 4=1$ 。

NTT 模数是容易得到的，假设我们需要处理 $2^{23}$ 长的 NTT ，意味着需要其有阶为 $2^{23}$ 的元素，而 $\varphi(p)=p-1=2^{23}\cdot t$ 其中 $t\bmod 2=1$ 此时其中一定有元素的阶整除 $2^{23}$ ，我们枚举 $t$ 并依次进行素性测试即可。

| 素数 $p$ | 周期 |
| :----: | :----: |
| $998244353$ | $2^{23}$ |
| $897581057$  | $2^{23}$ |
| $880803841$ | $2^{23}$ |
| $645922817$ | $2^{23}$ |
| $595591169$ | $2^{23}$ |
| $377487361$ | $2^{23}$ |