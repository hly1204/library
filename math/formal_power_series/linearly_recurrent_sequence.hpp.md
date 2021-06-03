---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "\u57FA-2 NTT"
  - icon: ':heavy_check_mark:'
    path: traits/modint.hpp
    title: traits/modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/linearly_recurrent_sequence.hpp\"\
    \n\n\n\n#include <numeric>\n\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <vector>\n\n#line 1 \"traits/modint.hpp\"\n\n\n\nnamespace lib {\n\ntemplate\
    \ <typename mod_t> struct modint_traits {\n  using type = typename mod_t::value_type;\n\
    \  static constexpr type get_mod() { return mod_t::get_mod(); }\n  static constexpr\
    \ type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\n};\n\n} // namespace lib\n\n\n#line 10 \"math/formal_power_series/radix_2_NTT.hpp\"\
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
    }\n\n} // namespace lib\n\n\n#line 7 \"math/formal_power_series/linearly_recurrent_sequence.hpp\"\
    \n\nnamespace lib {\n\ntemplate <typename mod_t> class LinearlyRecurrentSequence\
    \ {\npublic:\n  LinearlyRecurrentSequence(const std::vector<mod_t> &rec_seq, const\
    \ std::vector<mod_t> &init_val)\n      : p_(init_val) {\n    // rec_seq = {c_0,\
    \ c_1, c_2, ..., c_{d-1}}\n    // init_val = {u_0, u_1, u_2, ..., u_{d-1}}\n \
    \   // u_d = c_0u_0 + c_1u_1 + ... + c_{d-1}u_{d-1}\n    // d \u9636\u7684\u9012\
    \u63A8\n    int d = rec_seq.size();\n    q_.resize(d + 1);\n    q_[0] = 1;\n \
    \   for (int i = 1; i <= d; ++i) q_[i] = -rec_seq[d - i];\n    // q_ = 1 - c_{d-1}x\
    \ - c_{d-2}x^2 - ... - c_0x^d\n    std::vector<mod_t> q_cpy(q_);\n    int len\
    \ = get_ntt_len((d << 1) + 1);\n    q_cpy.resize(len, mod_t(0));\n    p_.resize(len,\
    \ mod_t(0));\n    dft(q_cpy);\n    dft(p_);\n    for (int i = 0; i != len; ++i)\
    \ p_[i] *= q_cpy[i];\n    idft(p_);\n    p_.resize(d);\n  }\n  ~LinearlyRecurrentSequence()\
    \ = default;\n\n  mod_t operator[](unsigned long long n) const { // \u8FD4\u56DE\
    \ [x^n]p(x)/q(x)\n    if (n == 0) return p_[0];\n    std::vector<mod_t> p_cpy(p_),\
    \ q_cpy(q_);\n    int len = get_ntt_len((q_cpy.size() << 1) - 1);\n    p_cpy.resize(len,\
    \ mod_t(0));\n    q_cpy.resize(len, mod_t(0));\n    dft(p_cpy);\n    dft(q_cpy);\n\
    \    for (;; n >>= 1) {                                         // p(x)/q(x) =\
    \ p(x)q(-x)/(q(x)q(-x))\n      for (int i = 0; i != len; ++i) p_cpy[i] *= q_cpy[i\
    \ ^ 1]; // p(x)q(-x) \u5206\u5B50\n      if (n & 1) {                        \
    \                     // \u957F\u5EA6\u4F1A\u53D8\u4E3A\u539F\u5148\u7684\u4E00\
    \u534A\n        NTT<mod_t>::odd_dft(len, p_cpy.data());\n      } else {\n    \
    \    NTT<mod_t>::even_dft(len, p_cpy.data());\n      }\n      for (int i = 0;\
    \ i != len; i += 2) q_cpy[i] = q_cpy[i + 1] = q_cpy[i] * q_cpy[i + 1];\n     \
    \ NTT<mod_t>::even_dft(len, q_cpy.data());\n      if (n == 1) // [x^0](q(x)q(-x))=1\
    \ \uFF0C\u4F7F\u7528\u7B2C\u4E00\u79CD\u7C7B\u578B\u7684 accumulate \u5373\u4ECE\
    \u5DE6\u5F00\u59CB fold \u5E76\u7D2F\u52A0\u7B54\u6848\n        return std::accumulate(p_cpy.begin(),\
    \ p_cpy.begin() + (len >> 1), mod_t(0)) /\n               mod_t(len >> 1);\n \
    \     NTT<mod_t>::dft_doubling(len >> 1, q_cpy.data());\n      NTT<mod_t>::dft_doubling(len\
    \ >> 1, p_cpy.data());\n    }\n  }\n\nprivate:\n  std::vector<mod_t> p_, q_; //\
    \ p(x)/q(x)\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef LINEARLY_RECURRENT_SEQUENCE_HEADER_HPP\n#define LINEARLY_RECURRENT_SEQUENCE_HEADER_HPP\n\
    \n#include <numeric>\n\n#include \"radix_2_NTT.hpp\"\n\nnamespace lib {\n\ntemplate\
    \ <typename mod_t> class LinearlyRecurrentSequence {\npublic:\n  LinearlyRecurrentSequence(const\
    \ std::vector<mod_t> &rec_seq, const std::vector<mod_t> &init_val)\n      : p_(init_val)\
    \ {\n    // rec_seq = {c_0, c_1, c_2, ..., c_{d-1}}\n    // init_val = {u_0, u_1,\
    \ u_2, ..., u_{d-1}}\n    // u_d = c_0u_0 + c_1u_1 + ... + c_{d-1}u_{d-1}\n  \
    \  // d \u9636\u7684\u9012\u63A8\n    int d = rec_seq.size();\n    q_.resize(d\
    \ + 1);\n    q_[0] = 1;\n    for (int i = 1; i <= d; ++i) q_[i] = -rec_seq[d -\
    \ i];\n    // q_ = 1 - c_{d-1}x - c_{d-2}x^2 - ... - c_0x^d\n    std::vector<mod_t>\
    \ q_cpy(q_);\n    int len = get_ntt_len((d << 1) + 1);\n    q_cpy.resize(len,\
    \ mod_t(0));\n    p_.resize(len, mod_t(0));\n    dft(q_cpy);\n    dft(p_);\n \
    \   for (int i = 0; i != len; ++i) p_[i] *= q_cpy[i];\n    idft(p_);\n    p_.resize(d);\n\
    \  }\n  ~LinearlyRecurrentSequence() = default;\n\n  mod_t operator[](unsigned\
    \ long long n) const { // \u8FD4\u56DE [x^n]p(x)/q(x)\n    if (n == 0) return\
    \ p_[0];\n    std::vector<mod_t> p_cpy(p_), q_cpy(q_);\n    int len = get_ntt_len((q_cpy.size()\
    \ << 1) - 1);\n    p_cpy.resize(len, mod_t(0));\n    q_cpy.resize(len, mod_t(0));\n\
    \    dft(p_cpy);\n    dft(q_cpy);\n    for (;; n >>= 1) {                    \
    \                     // p(x)/q(x) = p(x)q(-x)/(q(x)q(-x))\n      for (int i =\
    \ 0; i != len; ++i) p_cpy[i] *= q_cpy[i ^ 1]; // p(x)q(-x) \u5206\u5B50\n    \
    \  if (n & 1) {                                             // \u957F\u5EA6\u4F1A\
    \u53D8\u4E3A\u539F\u5148\u7684\u4E00\u534A\n        NTT<mod_t>::odd_dft(len, p_cpy.data());\n\
    \      } else {\n        NTT<mod_t>::even_dft(len, p_cpy.data());\n      }\n \
    \     for (int i = 0; i != len; i += 2) q_cpy[i] = q_cpy[i + 1] = q_cpy[i] * q_cpy[i\
    \ + 1];\n      NTT<mod_t>::even_dft(len, q_cpy.data());\n      if (n == 1) //\
    \ [x^0](q(x)q(-x))=1 \uFF0C\u4F7F\u7528\u7B2C\u4E00\u79CD\u7C7B\u578B\u7684 accumulate\
    \ \u5373\u4ECE\u5DE6\u5F00\u59CB fold \u5E76\u7D2F\u52A0\u7B54\u6848\n       \
    \ return std::accumulate(p_cpy.begin(), p_cpy.begin() + (len >> 1), mod_t(0))\
    \ /\n               mod_t(len >> 1);\n      NTT<mod_t>::dft_doubling(len >> 1,\
    \ q_cpy.data());\n      NTT<mod_t>::dft_doubling(len >> 1, p_cpy.data());\n  \
    \  }\n  }\n\nprivate:\n  std::vector<mod_t> p_, q_; // p(x)/q(x)\n};\n\n} // namespace\
    \ lib\n\n#endif"
  dependsOn:
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  isVerificationFile: false
  path: math/formal_power_series/linearly_recurrent_sequence.hpp
  requiredBy: []
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
documentation_of: math/formal_power_series/linearly_recurrent_sequence.hpp
layout: document
title: "\u5E38\u7CFB\u6570\u9F50\u6B21\u7EBF\u6027\u9012\u63A8"
---

## 常系数齐次线性递推

在类 `LinearlyRecurrentSequence` 有函数

- `LinearlyRecurrentSequence(rec, init_val)` 为构造函数，接收递推式和初值。
- `operator[](k)` 返回递推序列第 $k$ 项的值。

使用 Bostan-Mori 的 LSB 算法，常数较小。这个类仅支持 NTT 友好的模数且递推式阶数不能超过模数能做的 DFT 的长度。若我们想支持任意模数，使用三个较大的 NTT 模数是必要的，注意到在最后的 `dft_doubling` 过程中 `idft` 之后使用 CRT 复原系数并重新全部 `dft` 即可，常数为 NTT 友好模数询问的三倍多一些。