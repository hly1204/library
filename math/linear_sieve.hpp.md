---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/stirling_numbers.hpp
    title: Stirling Numbers (in $\mathbb{F} _ p$ for FFT prime $p$)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/linear_sieve.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\
    \n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n\
    #define LIB ::lib::\n\n\n#line 5 \"math/linear_sieve.hpp\"\n\n#include <vector>\n\
    \nLIB_BEGIN\n\n// Output: primes in [0, `n`) (sorted).\nstd::vector<int> prime_table(int\
    \ n) {\n  std::vector<bool> is_comp(n, false);\n  std::vector<int> res;\n  for\
    \ (int i = 2; i < n; ++i) {\n    if (!is_comp[i]) res.push_back(i);\n    for (int\
    \ j = 0, je = res.size(); j < je && i * res[j] < n; ++j) {\n      is_comp[i *\
    \ res[j]] = true;\n      if (i % res[j] == 0) break;\n    }\n  }\n  return res;\n\
    }\n\ntemplate <typename ModIntT>\nstd::vector<ModIntT> pow_table(int e, int n)\
    \ {\n  std::vector<bool> is_comp(n, false);\n  std::vector<int> p;\n  std::vector<ModIntT>\
    \ res(n);\n  if (n >= 1) {\n    res.front() = (e == 0 ? ModIntT(1) : ModIntT());\
    \ // 0^0 = 1\n    if (n >= 2) res[1] = ModIntT(1);\n  }\n  for (int i = 2; i <\
    \ n; ++i) {\n    if (!is_comp[i]) {\n      p.push_back(i);\n      res[i] = ModIntT(i).pow(e);\n\
    \    }\n    for (int j = 0, je = static_cast<int>(p.size()); j < je && i * p[j]\
    \ < n; ++j) {\n      is_comp[i * p[j]] = true;\n      res[i * p[j]]     = res[i]\
    \ * res[p[j]];\n      if (i % p[j] == 0) break;\n    }\n  }\n  return res;\n}\n\
    \nLIB_END\n\n\n"
  code: "#ifndef LINEAR_SIEVE_HPP\n#define LINEAR_SIEVE_HPP\n\n#include \"../common.hpp\"\
    \n\n#include <vector>\n\nLIB_BEGIN\n\n// Output: primes in [0, `n`) (sorted).\n\
    std::vector<int> prime_table(int n) {\n  std::vector<bool> is_comp(n, false);\n\
    \  std::vector<int> res;\n  for (int i = 2; i < n; ++i) {\n    if (!is_comp[i])\
    \ res.push_back(i);\n    for (int j = 0, je = res.size(); j < je && i * res[j]\
    \ < n; ++j) {\n      is_comp[i * res[j]] = true;\n      if (i % res[j] == 0) break;\n\
    \    }\n  }\n  return res;\n}\n\ntemplate <typename ModIntT>\nstd::vector<ModIntT>\
    \ pow_table(int e, int n) {\n  std::vector<bool> is_comp(n, false);\n  std::vector<int>\
    \ p;\n  std::vector<ModIntT> res(n);\n  if (n >= 1) {\n    res.front() = (e ==\
    \ 0 ? ModIntT(1) : ModIntT()); // 0^0 = 1\n    if (n >= 2) res[1] = ModIntT(1);\n\
    \  }\n  for (int i = 2; i < n; ++i) {\n    if (!is_comp[i]) {\n      p.push_back(i);\n\
    \      res[i] = ModIntT(i).pow(e);\n    }\n    for (int j = 0, je = static_cast<int>(p.size());\
    \ j < je && i * p[j] < n; ++j) {\n      is_comp[i * p[j]] = true;\n      res[i\
    \ * p[j]]     = res[i] * res[p[j]];\n      if (i % p[j] == 0) break;\n    }\n\
    \  }\n  return res;\n}\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: math/linear_sieve.hpp
  requiredBy:
  - math/stirling_numbers.hpp
  timestamp: '2022-06-03 11:52:48+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
documentation_of: math/linear_sieve.hpp
layout: document
title: Linear Sieve
---
