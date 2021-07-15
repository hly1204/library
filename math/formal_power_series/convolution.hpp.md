---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  - icon: ':question:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/arbitrary_modulo_convolution.hpp
    title: "arbitrary modulo convolution / \u4EFB\u610F\u6A21\u6570\u5377\u79EF"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "convolution / \u5377\u79EF"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/convolution.hpp\"\n\n\n\r\n/**\r\
    \n * @brief convolution / \u5377\u79EF\r\n *\r\n */\r\n\r\n#include <vector>\r\
    \n\r\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\r\n * @docs docs/math/formal_power_series/radix_2_NTT.md\r\
    \n */\r\n\r\n#include <algorithm>\r\n#include <cassert>\r\n#include <cstdint>\r\
    \n#line 13 \"math/formal_power_series/radix_2_NTT.hpp\"\n\r\n#line 1 \"traits/modint.hpp\"\
    \n\n\n\r\n/**\r\n * @brief modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6\r\n\
    \ *\r\n */\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t>\r\nstruct modint_traits\
    \ {\r\n  using type = typename mod_t::value_type;\r\n  static constexpr type get_mod()\
    \ { return mod_t::get_mod(); }\r\n  static constexpr type get_primitive_root_prime()\
    \ { return mod_t::get_primitive_root_prime(); }\r\n};\r\n\r\n} // namespace lib\r\
    \n\r\n\n#line 15 \"math/formal_power_series/radix_2_NTT.hpp\"\n\r\nnamespace lib\
    \ {\r\n\r\n/**\r\n * @note \u5FC5\u987B\u7528 NTT \u53CB\u597D\u7684\u6A21\u6570\
    \uFF01\uFF01\uFF01\r\n */\r\ntemplate <typename mod_t>\r\nclass NTT {\r\npublic:\r\
    \n  NTT() = delete;\r\n\r\n  static void set_root(int len) {\r\n    static int\
    \ lim = 0;\r\n    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\r\
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
    \r\n\n"
  code: "#ifndef CONVOLUTION_HEADER_HPP\r\n#define CONVOLUTION_HEADER_HPP\r\n\r\n\
    /**\r\n * @brief convolution / \u5377\u79EF\r\n *\r\n */\r\n\r\n#include <vector>\r\
    \n\r\n#include \"radix_2_NTT.hpp\"\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief\
    \ NTT \u6A21\u6570\u5377\u79EF\r\n * @tparam mod_t NTT \u53CB\u597D\u7684\u6A21\
    \u6570\u7C7B\r\n */\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t> convolve(const\
    \ std::vector<mod_t> &x, const std::vector<mod_t> &y) {\r\n  int n = x.size(),\
    \ m = y.size();\r\n  if (std::min(n, m) <= 32) {\r\n    std::vector<mod_t> res(n\
    \ + m - 1, mod_t(0));\r\n    for (int i = 0; i < n; ++i)\r\n      for (int j =\
    \ 0; j < m; ++j) res[i + j] += x[i] * y[j];\r\n    return res;\r\n  }\r\n  int\
    \ len = get_ntt_len(n + m - 1);\r\n  std::vector<mod_t> res(len);\r\n  std::copy_n(x.begin(),\
    \ n, res.begin());\r\n  std::fill(res.begin() + n, res.end(), mod_t(0));\r\n \
    \ dft(res);\r\n  if (&x == &y) {\r\n    for (int i = 0; i < len; ++i) res[i] *=\
    \ res[i];\r\n  } else {\r\n    std::vector<mod_t> y_tmp(len);\r\n    std::copy_n(y.begin(),\
    \ m, y_tmp.begin());\r\n    std::fill(y_tmp.begin() + m, y_tmp.end(), mod_t(0));\r\
    \n    dft(y_tmp);\r\n    for (int i = 0; i < len; ++i) res[i] *= y_tmp[i];\r\n\
    \  }\r\n  idft(res);\r\n  res.resize(n + m - 1);\r\n  return res;\r\n}\r\n\r\n\
    } // namespace lib\r\n\r\n#endif"
  dependsOn:
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  isVerificationFile: false
  path: math/formal_power_series/convolution.hpp
  requiredBy:
  - math/formal_power_series/arbitrary_modulo_convolution.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
documentation_of: math/formal_power_series/convolution.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/convolution.hpp
- /library/math/formal_power_series/convolution.hpp.html
title: "convolution / \u5377\u79EF"
---
