---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: traits/modint.hpp
    title: traits/modint.hpp
  _extendedRequiredBy:
  - icon: ':question:'
    path: math/formal_power_series/fps_basic.hpp
    title: "\u5F62\u5F0F\u5E42\u7EA7\u6570\u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/linearly_recurrent_sequence.hpp
    title: "\u5E38\u7CFB\u6570\u9F50\u6B21\u7EBF\u6027\u9012\u63A8"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod.0.test.cpp
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
  - icon: ':x:'
    path: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\n#line\
    \ 1 \"traits/modint.hpp\"\n\n\n\nnamespace lib {\n\ntemplate <typename mod_t>\
    \ struct modint_traits {\n  using type = typename mod_t::value_type;\n  static\
    \ constexpr type get_mod() { return mod_t::get_mod(); }\n  static constexpr type\
    \ get_primitive_root_prime() { return mod_t::get_primitive_root_prime(); }\n};\n\
    \n} // namespace lib\n\n\n#line 10 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\nnamespace lib {\n\n// \u5FC5\u987B\u7528 NTT \u53CB\u597D\u7684\u6A21\u6570\
    \uFF01\uFF01\uFF01\ntemplate <typename mod_t> class NTT {\npublic:\n  NTT() =\
    \ delete;\n\n  static void set_root(int len) {\n    static int lim = 0;\n    static\
    \ constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\n    if\
    \ (lim == 0) {\n      rt.resize(1 << 20);\n      irt.resize(1 << 20);\n      rt[0]\
    \ = irt[0] = 1;\n      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod() >> 21),\
    \ ig_t = g_t.inv();\n      rt[1 << 19] = g_t, irt[1 << 19] = ig_t;\n      for\
    \ (int i = 18; i >= 0; --i) {\n        g_t *= g_t, ig_t *= ig_t;\n        rt[1\
    \ << i] = g_t, irt[1 << i] = ig_t;\n      }\n      lim = 1;\n    }\n    for (;\
    \ (lim << 1) < len; lim <<= 1) {\n      mod_t g = rt[lim], ig = irt[lim];\n  \
    \    for (int i = lim + 1, e = lim << 1; i < e; ++i) {\n        rt[i] = rt[i -\
    \ lim] * g;\n        irt[i] = irt[i - lim] * ig;\n      }\n    }\n  }\n\n  static\
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
    }\n\ntemplate <typename mod_t> void dft(int n, mod_t *x) {\n  NTT<mod_t>::set_root(n);\n\
    \  NTT<mod_t>::dft(n, x);\n}\n\ntemplate <typename mod_t> void idft(int n, mod_t\
    \ *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::idft(n, x);\n}\n\ntemplate\
    \ <typename mod_t> void dft(std::vector<mod_t> &x) {\n  NTT<mod_t>::set_root(x.size());\n\
    \  NTT<mod_t>::dft(x.size(), x.data());\n}\n\ntemplate <typename mod_t> void idft(std::vector<mod_t>\
    \ &x) {\n  NTT<mod_t>::set_root(x.size());\n  NTT<mod_t>::idft(x.size(), x.data());\n\
    }\n\n} // namespace lib\n\n\n"
  code: "#ifndef RADIX_2_NTT_HEADER_HPP\n#define RADIX_2_NTT_HEADER_HPP\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\n#include\
    \ \"../../traits/modint.hpp\"\n\nnamespace lib {\n\n// \u5FC5\u987B\u7528 NTT\
    \ \u53CB\u597D\u7684\u6A21\u6570\uFF01\uFF01\uFF01\ntemplate <typename mod_t>\
    \ class NTT {\npublic:\n  NTT() = delete;\n\n  static void set_root(int len) {\n\
    \    static int lim = 0;\n    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\n\
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
    }\n\ntemplate <typename mod_t> void dft(int n, mod_t *x) {\n  NTT<mod_t>::set_root(n);\n\
    \  NTT<mod_t>::dft(n, x);\n}\n\ntemplate <typename mod_t> void idft(int n, mod_t\
    \ *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::idft(n, x);\n}\n\ntemplate\
    \ <typename mod_t> void dft(std::vector<mod_t> &x) {\n  NTT<mod_t>::set_root(x.size());\n\
    \  NTT<mod_t>::dft(x.size(), x.data());\n}\n\ntemplate <typename mod_t> void idft(std::vector<mod_t>\
    \ &x) {\n  NTT<mod_t>::set_root(x.size());\n  NTT<mod_t>::idft(x.size(), x.data());\n\
    }\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - traits/modint.hpp
  isVerificationFile: false
  path: math/formal_power_series/radix_2_NTT.hpp
  requiredBy:
  - math/formal_power_series/fps_basic.hpp
  - math/formal_power_series/linearly_recurrent_sequence.hpp
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/convolution_mod.0.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
documentation_of: math/formal_power_series/radix_2_NTT.hpp
layout: document
title: "\u57FA-2 NTT"
---

## 基-2 NTT

考虑 FFT 的过程就是由 $\mathbb{C}[x]/(x^{2n}-c^2)$ 映射到 $\mathbb{C}[x]/(x^n-c)\times \mathbb{C}[x]/(x^n+c)$ 的过程，而 NTT 也是类似的，只是换成 $\mathbb{F}_p[x]/(x^{2n}-c^2)$ 而已，当 $-1$ 在模 $p$ 意义下是二次剩余时，我们可以找到更多阶为 $2$ 的幂次的元素，只需要这些元素就可以生成用到的“单位根”，故不需要使用“原根”。若 $-1$ 在模 $p$ 意义下是二次非剩余，则可能需要对域进行扩张，类似于 $f:\mathbb{R}\to\mathbb{C}$ 也就是 $\mathbb{R}[x]/(x^2+1)$ 。

## 常用的素数（ $\lt 2^{30}$ ）

| 素数 $p$ | 周期 |
| - | - |
| $167772161$ | $2^{25}$ |
| $754974721$ | $2^{24}$ |
| $998244353$ | $2^{23}$ |
| $595591169$ | $2^{23}$ |

## 常用的素数（ $\lt 2^{63}$ ）

| 周期 | 素数 $p$ | $p-1$ 的分解 |
| - | - | - |
| $2^{44}$ | $4580495072570638337$ | $2^{44}\cdot 83\cdot 3137$ |
| $2^{44}$ | $4581058022524059649$ | $2^{44}\cdot 3\cdot 11\cdot 13\cdot 607$ |
| $2^{44}$ | $4582113553686724609$ | $2^{44}\cdot 3\cdot 7\cdot 79\cdot 157$ |
| $2^{44}$ | $4585702359639785473$ | $2^{44}\cdot 3^{2}\cdot 11\cdot 2633$ |
| $2^{44}$ | $4587039365779161089$ | $2^{44}\cdot 7\cdot 193^{2}$ |
| $2^{44}$ | $4587391209500049409$ | $2^{44}\cdot 3\cdot 17\cdot 5113$ |
| $2^{44}$ | $4588130081313914881$ | $2^{44}\cdot 3\cdot 5\cdot 17387$ |
| $2^{44}$ | $4589572640569556993$ | $2^{44}\cdot 11\cdot 37\cdot 641$ |
| $2^{44}$ | $4610999923171655681$ | $2^{44}\cdot 5\cdot 19\cdot 31\cdot 89$ |
| $2^{44}$ | $4611105476287922177$ | $2^{44}\cdot 262111$ |
| $2^{45}$ | $4580336742896238593$ | $2^{45}\cdot 29\cdot 67^{2}$ |
| $2^{45}$ | $4581533011547258881$ | $2^{45}\cdot 3\cdot 5\cdot 8681$ |
| $2^{45}$ | $4584347761314365441$ | $2^{45}\cdot 5\cdot 11\cdot 23\cdot 103$ |
| $2^{45}$ | $4587655092290715649$ | $2^{45}\cdot 3\cdot 7^{2}\cdot 887$ |
| $2^{48}$ | $4585508845593296897$ | $2^{48}\cdot 11\cdot 1481$ |
| $2^{49}$ | $4582975570802900993$ | $2^{49}\cdot 7\cdot 1163$ |
| $2^{49}$ | $4595360469778169857$ | $2^{49}\cdot 3^{2}\cdot 907$ |
| $2^{50}$ | $4601552919265804289$ | $2^{50}\cdot 61\cdot 67$ |

## 参考文献

- Min_25 的[博客](https://min-25.hatenablog.com/entry/2015/04/07/160154)
- Daniel J. Bernstein. [Multidigit Multiplication for Mathematicians](https://cr.yp.to/papers/m3.pdf).
- [Matters Computational](https://www.jjj.de/fxt/#fxtbook)

