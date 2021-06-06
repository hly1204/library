---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "\u57FA-2 NTT"
  - icon: ':heavy_check_mark:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "linearly recurrent sequence / \u5E38\u7CFB\u6570\u7EBF\u6027\u9012\
      \u63A8\u5E8F\u5217"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/formal_power_series/linearly_recurrent_sequence.hpp: line 11: unable to\
    \ process #include in #if / #ifdef / #ifndef other than include guards\n"
  code: "/**\n * @brief linearly recurrent sequence / \u5E38\u7CFB\u6570\u7EBF\u6027\
    \u9012\u63A8\u5E8F\u5217\n *\n */\n\n#ifndef LINEARLY_RECURRENT_SEQUENCE_HEADER_HPP\n\
    #define LINEARLY_RECURRENT_SEQUENCE_HEADER_HPP\n\n#include <numeric>\n\n#include\
    \ \"radix_2_NTT.hpp\"\n\nnamespace lib {\n\ntemplate <typename mod_t> class LinearlyRecurrentSequence\
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
    \ p(x)/q(x)\n};\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  isVerificationFile: false
  path: math/formal_power_series/linearly_recurrent_sequence.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
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