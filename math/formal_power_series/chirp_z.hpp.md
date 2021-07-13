---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  - icon: ':heavy_check_mark:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.1.test.cpp
    title: remote_test/yosupo/math/convolution_mod.1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/math/formal_power_series/chirp_z.md
    document_title: "chirp z transform / chirp z \u53D8\u6362"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/chirp_z.hpp\"\n\n\n\n/**\n * @brief\
    \ chirp z transform / chirp z \u53D8\u6362\n * @docs docs/math/formal_power_series/chirp_z.md\n\
    \ */\n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <vector>\n\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\n\n\n\n/**\n\
    \ * @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\n * @docs docs/math/formal_power_series/radix_2_NTT.md\n\
    \ */\n\n#line 11 \"math/formal_power_series/radix_2_NTT.hpp\"\n#include <cstdint>\n\
    #line 13 \"math/formal_power_series/radix_2_NTT.hpp\"\n\n#line 1 \"traits/modint.hpp\"\
    \n\n\n\n/**\n * @brief modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6\n *\n */\n\
    \nnamespace lib {\n\ntemplate <typename mod_t> struct modint_traits {\n  using\
    \ type = typename mod_t::value_type;\n  static constexpr type get_mod() { return\
    \ mod_t::get_mod(); }\n  static constexpr type get_primitive_root_prime() { return\
    \ mod_t::get_primitive_root_prime(); }\n};\n\n} // namespace lib\n\n\n#line 15\
    \ \"math/formal_power_series/radix_2_NTT.hpp\"\n\nnamespace lib {\n\n/**\n * @note\
    \ \u5FC5\u987B\u7528 NTT \u53CB\u597D\u7684\u6A21\u6570\uFF01\uFF01\uFF01\n */\n\
    template <typename mod_t> class NTT {\npublic:\n  NTT() = delete;\n\n  static\
    \ void set_root(int len) {\n    static int lim = 0;\n    static constexpr mod_t\
    \ g(modint_traits<mod_t>::get_primitive_root_prime());\n    if (lim == 0) {\n\
    \      rt.resize(1 << 20);\n      irt.resize(1 << 20);\n      rt[0] = irt[0] =\
    \ 1;\n      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod() >> 21), ig_t = g_t.inv();\n\
    \      rt[1 << 19] = g_t, irt[1 << 19] = ig_t;\n      for (int i = 18; i >= 0;\
    \ --i) {\n        g_t *= g_t, ig_t *= ig_t;\n        rt[1 << i] = g_t, irt[1 <<\
    \ i] = ig_t;\n      }\n      lim = 1;\n    }\n    for (; (lim << 1) < len; lim\
    \ <<= 1) {\n      mod_t g = rt[lim], ig = irt[lim];\n      for (int i = lim +\
    \ 1, e = lim << 1; i < e; ++i) {\n        rt[i] = rt[i - lim] * g;\n        irt[i]\
    \ = irt[i - lim] * ig;\n      }\n    }\n  }\n\n  static void dft(int n, mod_t\
    \ *x) {\n    for (int j = 0, l = n >> 1; j != l; ++j) {\n      mod_t u = x[j],\
    \ v = x[j + l];\n      x[j] = u + v, x[j + l] = u - v;\n    }\n    for (int i\
    \ = n >> 1; i >= 2; i >>= 1) {\n      for (int j = 0, l = i >> 1; j != l; ++j)\
    \ {\n        mod_t u = x[j], v = x[j + l];\n        x[j] = u + v, x[j + l] = u\
    \ - v;\n      }\n      for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m)\
    \ {\n        mod_t root = rt[m];\n        for (int k = 0; k != l; ++k) {\n   \
    \       mod_t u = x[j + k], v = x[j + k + l] * root;\n          x[j + k] = u +\
    \ v, x[j + k + l] = u - v;\n        }\n      }\n    }\n  }\n\n  static void idft(int\
    \ n, mod_t *x) {\n    for (int i = 2; i < n; i <<= 1) {\n      for (int j = 0,\
    \ l = i >> 1; j != l; ++j) {\n        mod_t u = x[j], v = x[j + l];\n        x[j]\
    \ = u + v, x[j + l] = u - v;\n      }\n      for (int j = i, l = i >> 1, m = 1;\
    \ j != n; j += i, ++m) {\n        mod_t root = irt[m];\n        for (int k = 0;\
    \ k != l; ++k) {\n          mod_t u = x[j + k], v = x[j + k + l];\n          x[j\
    \ + k] = u + v, x[j + k + l] = (u - v) * root;\n        }\n      }\n    }\n  \
    \  mod_t iv(mod_t(n).inv());\n    for (int j = 0, l = n >> 1; j != l; ++j) {\n\
    \      mod_t u = x[j] * iv, v = x[j + l] * iv;\n      x[j] = u + v, x[j + l] =\
    \ u - v;\n    }\n  }\n\n  static void even_dft(int n, mod_t *x) {\n    static\
    \ constexpr mod_t IT(mod_t(2).inv());\n    for (int i = 0, j = 0; i != n; i +=\
    \ 2, ++j) x[j] = IT * (x[i] + x[i + 1]);\n  }\n\n  static void odd_dft(int n,\
    \ mod_t *x) {\n    static constexpr mod_t IT(mod_t(2).inv());\n    for (int i\
    \ = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * irt[j] * (x[i] - x[i + 1]);\n \
    \ }\n\n  static void dft_doubling(int n, mod_t *x) {\n    static constexpr mod_t\
    \ g(modint_traits<mod_t>::get_primitive_root_prime());\n    std::copy_n(x, n,\
    \ x + n);\n    idft(n, x + n);\n    mod_t k(1), t(g.pow((modint_traits<mod_t>::get_mod()\
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
    }\n\n} // namespace lib\n\n\n#line 15 \"math/formal_power_series/chirp_z.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @brief chirp z \u53D8\u6362\n * @tparam mod_t \u4E3A\
    \ NTT \u53CB\u597D\u7684\u6A21\u6570\n * @param n czt \u7684\u957F\u5EA6\n * @param\
    \ A \u591A\u9879\u5F0F\n * @param c\n * @return std::vector<mod_t> A(1), A(c),\
    \ A(c^2), \u2026, A(c^{n-1})\n */\ntemplate <typename mod_t> std::vector<mod_t>\
    \ czt(int n, const std::vector<mod_t> &A, mod_t c) {\n  const mod_t ZERO(0);\n\
    \  assert(c != ZERO);\n  assert(!A.empty());\n  int m = A.size();\n  while (m\
    \ > 0 && A[m - 1] == ZERO) --m;\n  if (m <= 1) return std::vector<mod_t>(n, A.front());\n\
    \  int sz = n + m - 1, len = get_ntt_len(sz), nm_max = std::max(n, m);\n  std::vector<mod_t>\
    \ A_0(A);\n  A_0.resize(len, ZERO);\n  mod_t c_tmp(1), ic = mod_t(1) / c, ic_tmp(1);\n\
    \  std::vector<mod_t> c_choose(sz), ic_choose(nm_max);\n  for (int i = 0; i <\
    \ 2 && i < sz; ++i) c_choose[i] = c_tmp;\n  for (int i = 2; i < sz; ++i) c_choose[i]\
    \ = c_choose[i - 1] * (c_tmp *= c);\n  for (int i = 0; i < 2 && i < nm_max; ++i)\
    \ ic_choose[i] = ic_tmp;\n  for (int i = 2; i < nm_max; ++i) ic_choose[i] = ic_choose[i\
    \ - 1] * (ic_tmp *= ic);\n  c_choose.resize(len, ZERO);\n  for (int i = 0; i <\
    \ m; ++i) A_0[i] *= ic_choose[i];\n  std::reverse(A_0.begin(), A_0.begin() + m);\n\
    \  dft(A_0), dft(c_choose);\n  for (int i = 0; i < len; ++i) c_choose[i] *= A_0[i];\n\
    \  idft(c_choose);\n  c_choose.erase(c_choose.begin(), c_choose.begin() + m -\
    \ 1);\n  c_choose.resize(n);\n  for (int i = 0; i < n; ++i) c_choose[i] *= ic_choose[i];\n\
    \  return c_choose;\n}\n\n} // namespace lib\n\n\n"
  code: "#ifndef CHIRP_Z_HEADER_HPP\n#define CHIRP_Z_HEADER_HPP\n\n/**\n * @brief\
    \ chirp z transform / chirp z \u53D8\u6362\n * @docs docs/math/formal_power_series/chirp_z.md\n\
    \ */\n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <vector>\n\n#include \"radix_2_NTT.hpp\"\n\nnamespace lib {\n\n/**\n * @brief\
    \ chirp z \u53D8\u6362\n * @tparam mod_t \u4E3A NTT \u53CB\u597D\u7684\u6A21\u6570\
    \n * @param n czt \u7684\u957F\u5EA6\n * @param A \u591A\u9879\u5F0F\n * @param\
    \ c\n * @return std::vector<mod_t> A(1), A(c), A(c^2), \u2026, A(c^{n-1})\n */\n\
    template <typename mod_t> std::vector<mod_t> czt(int n, const std::vector<mod_t>\
    \ &A, mod_t c) {\n  const mod_t ZERO(0);\n  assert(c != ZERO);\n  assert(!A.empty());\n\
    \  int m = A.size();\n  while (m > 0 && A[m - 1] == ZERO) --m;\n  if (m <= 1)\
    \ return std::vector<mod_t>(n, A.front());\n  int sz = n + m - 1, len = get_ntt_len(sz),\
    \ nm_max = std::max(n, m);\n  std::vector<mod_t> A_0(A);\n  A_0.resize(len, ZERO);\n\
    \  mod_t c_tmp(1), ic = mod_t(1) / c, ic_tmp(1);\n  std::vector<mod_t> c_choose(sz),\
    \ ic_choose(nm_max);\n  for (int i = 0; i < 2 && i < sz; ++i) c_choose[i] = c_tmp;\n\
    \  for (int i = 2; i < sz; ++i) c_choose[i] = c_choose[i - 1] * (c_tmp *= c);\n\
    \  for (int i = 0; i < 2 && i < nm_max; ++i) ic_choose[i] = ic_tmp;\n  for (int\
    \ i = 2; i < nm_max; ++i) ic_choose[i] = ic_choose[i - 1] * (ic_tmp *= ic);\n\
    \  c_choose.resize(len, ZERO);\n  for (int i = 0; i < m; ++i) A_0[i] *= ic_choose[i];\n\
    \  std::reverse(A_0.begin(), A_0.begin() + m);\n  dft(A_0), dft(c_choose);\n \
    \ for (int i = 0; i < len; ++i) c_choose[i] *= A_0[i];\n  idft(c_choose);\n  c_choose.erase(c_choose.begin(),\
    \ c_choose.begin() + m - 1);\n  c_choose.resize(n);\n  for (int i = 0; i < n;\
    \ ++i) c_choose[i] *= ic_choose[i];\n  return c_choose;\n}\n\n} // namespace lib\n\
    \n#endif"
  dependsOn:
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  isVerificationFile: false
  path: math/formal_power_series/chirp_z.hpp
  requiredBy: []
  timestamp: '2021-07-13 17:52:29+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/convolution_mod.1.test.cpp
documentation_of: math/formal_power_series/chirp_z.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/chirp_z.hpp
- /library/math/formal_power_series/chirp_z.hpp.html
title: "chirp z transform / chirp z \u53D8\u6362"
---
## chirp z 变换

也被称为 Bluestein 算法，我们使用标题的称呼。

对于 $A(x)=\sum _ {i=0}^na_ix^i\in\mathbb{F} _ p\lbrack x\rbrack$ 。我们希望得到 $A(1),A(c^2),A(c^4),\dots$ 其中 $c\in\mathbb{F} _ p^\times$ 那么可以通过将 $A_0(x)=\sum _ {i\geq 0}a_ic^{i^2}x^i$ （对于 $\forall j\gt n$ 令 $a_j=0$ ）与 $B_0(x)=\sum _ {i\geq 0}c^{-(i-n)^2}x^i$ 相乘得到，有

$$
\begin{aligned}
\lbrack x^{k}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{k}\left(\lbrack x^i\rbrack A_0(x)\right)\left(\lbrack x^{k-i}\rbrack B_0(x)\right)\\
&=\sum _ {i=0}^ka_ic^{i^2-(k-n-i)^2}
\end{aligned}
$$

令 $k=n+t$ 其中 $t\geq 0$ 那么

$$
\begin{aligned}
\sum _ {i=0}^ka_ic^{i^2-(k-n-i)^2}&=\sum _ {i=0}^{n+t}a_ic^{i^2-(i-t)^2}\\
&=c^{-t^2}\sum _ {i=0}^{n+t}a_ic^{2it}\\
&=c^{-t^2}A(c^{2t})
\end{aligned}
$$

而对于 $A(c),A(c^3),\dots $ 可构造 $A(cx)$ 后同理，因为我们从 $x^n$ 开始提取系数，所以可以使用循环卷积。

### 使用组合数作为指数

仍考虑上述问题，若将上面算法中的指数除以二，我们就能得到一个一次卷积即可计算 $A(1),A(c),A(c^2),\dots $ 的算法，但是会导致指数可能为小数。在数论变换中有时候没办法计算，此时考虑

$$
ki=\binom{i+k}{2}-\binom{i}{2}-\binom{k}{2}
$$

那么

$$
A(c^k)=c^{-\binom{k}{2}}\sum _ {i=0}^n\left(a_ic^{-\binom{i}{2}}\right)\left(c^{\binom{i+k}{2}}\right)
$$

是一个“减法卷积”，那么构造 $A_0(x)=\sum _ {i}a_{n-i}c^{-\binom{n-i}{2}}x^i$ （对于 $\forall j\gt n\lor j\lt 0$ 令 $a_j=0$ ）和 $B_0(x)=\sum _ {i\geq 0}c^{\binom{i}{2}}x^i$ 那么对于 $t\geq 0$ 有

$$
\begin{aligned}
\lbrack x^{n+t}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{n+t}\left(\lbrack x^{n+t-i}\rbrack A_0(x)\right)\left(\lbrack x^{i}\rbrack B_0(x)\right)\\
&=\sum _ {i=0}^{n+t}a_{i-t}c^{\binom{i}{2}-\binom{i-t}{2}}\\
&=\sum _ {i=-t}^na_ic^{\binom{i+t}{2}-\binom{i}{2}}\\
&=c^{\binom{t}{2}}\cdot A(c^t)
\end{aligned}
$$

可以用一次多项式乘法完成。另外 $\forall i\geq 2$ 有 $c^{\binom{i+1}{2}}=c^{\binom{i}{2}}\cdot c^i$ 。