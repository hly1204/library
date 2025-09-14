---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: bitwise_conv.hpp
    title: bitwise_conv.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_and_convolution.0.test.cpp
    title: test/convolution/bitwise_and_convolution.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_xor_convolution.0.test.cpp
    title: test/convolution/bitwise_xor_convolution.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sps_fft.hpp\"\n\n#include <cassert>\n#include <iterator>\n\
    #include <vector>\n\n// set power series = R[x_1,...,x_n]/(x_1^2,...,x_n^2)\n\
    // FFT is computing F({1,-1}^n)\n\ntemplate<typename Iterator> inline void sps_fft_n(Iterator\
    \ a, int n) {\n    assert((n & (n - 1)) == 0);\n    for (int i = 2; i <= n; i\
    \ *= 2)\n        for (int j = 0; j < n; j += i)\n            for (int k = j; k\
    \ < j + i / 2; ++k) {\n                const auto u = a[k], v = a[k + i / 2];\n\
    \                a[k] = u + v, a[k + i / 2] = u - v;\n            }\n}\n\ntemplate<typename\
    \ Tp> inline void sps_fft(std::vector<Tp> &a) { sps_fft_n(a.begin(), a.size());\
    \ }\n\ntemplate<typename Iterator> inline void sps_inv_fft_n(Iterator a, int n)\
    \ {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n   \
    \ sps_fft_n(a, n);\n    const Tp iv = Tp::mod() - (Tp::mod() - 1) / n;\n    for\
    \ (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate<typename Tp> inline void\
    \ sps_inv_fft(std::vector<Tp> &a) {\n    sps_inv_fft_n(a.begin(), a.size());\n\
    }\n"
  code: "#pragma once\n\n#include <cassert>\n#include <iterator>\n#include <vector>\n\
    \n// set power series = R[x_1,...,x_n]/(x_1^2,...,x_n^2)\n// FFT is computing\
    \ F({1,-1}^n)\n\ntemplate<typename Iterator> inline void sps_fft_n(Iterator a,\
    \ int n) {\n    assert((n & (n - 1)) == 0);\n    for (int i = 2; i <= n; i *=\
    \ 2)\n        for (int j = 0; j < n; j += i)\n            for (int k = j; k <\
    \ j + i / 2; ++k) {\n                const auto u = a[k], v = a[k + i / 2];\n\
    \                a[k] = u + v, a[k + i / 2] = u - v;\n            }\n}\n\ntemplate<typename\
    \ Tp> inline void sps_fft(std::vector<Tp> &a) { sps_fft_n(a.begin(), a.size());\
    \ }\n\ntemplate<typename Iterator> inline void sps_inv_fft_n(Iterator a, int n)\
    \ {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n   \
    \ sps_fft_n(a, n);\n    const Tp iv = Tp::mod() - (Tp::mod() - 1) / n;\n    for\
    \ (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate<typename Tp> inline void\
    \ sps_inv_fft(std::vector<Tp> &a) {\n    sps_inv_fft_n(a.begin(), a.size());\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: sps_fft.hpp
  requiredBy:
  - bitwise_conv.hpp
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/bitwise_xor_convolution.0.test.cpp
  - test/convolution/bitwise_and_convolution.0.test.cpp
documentation_of: sps_fft.hpp
layout: document
redirect_from:
- /library/sps_fft.hpp
- /library/sps_fft.hpp.html
title: sps_fft.hpp
---
