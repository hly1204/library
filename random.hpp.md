---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: rng.hpp
    title: rng.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: basis.hpp
    title: basis.hpp
  - icon: ':heavy_check_mark:'
    path: frobenius.hpp
    title: frobenius.hpp
  - icon: ':heavy_check_mark:'
    path: mat_basic.hpp
    title: mat_basic.hpp
  - icon: ':warning:'
    path: mat_extra.hpp
    title: mat_extra.hpp
  - icon: ':heavy_check_mark:'
    path: mat_sparse.hpp
    title: mat_sparse.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/2d_convolution.0.test.cpp
    title: test/convolution/2d_convolution.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/multivariate_power_series.0.test.cpp
    title: test/formal_power_series/multivariate_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/adjugate_matrix.0.test.cpp
    title: test/matrix/adjugate_matrix.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/characteristic_polynomial.0.test.cpp
    title: test/matrix/characteristic_polynomial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/characteristic_polynomial.1.test.cpp
    title: test/matrix/characteristic_polynomial.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/inverse_matrix.0.test.cpp
    title: test/matrix/inverse_matrix.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/matrix_det.0.test.cpp
    title: test/matrix/matrix_det.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/matrix_product.0.test.cpp
    title: test/matrix/matrix_product.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/pow_of_matrix.0.test.cpp
    title: test/matrix/pow_of_matrix.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/sparse_matrix_det.0.test.cpp
    title: test/matrix/sparse_matrix_det.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"random.hpp\"\n\n#line 2 \"rng.hpp\"\n\n#include <cstdint>\n\
    #include <limits>\n\n// see: https://prng.di.unimi.it/xoshiro256starstar.c\n//\
    \ original license CC0 1.0\nclass xoshiro256starstar {\n    using u64 = std::uint64_t;\n\
    \n    static inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64\
    \ - k)); }\n\n    u64 s_[4];\n\n    u64 next() {\n        const u64 res = rotl(s_[1]\
    \ * 5, 7) * 9;\n        const u64 t   = s_[1] << 17;\n        s_[2] ^= s_[0];\n\
    \        s_[3] ^= s_[1];\n        s_[1] ^= s_[2];\n        s_[0] ^= s_[3];\n \
    \       s_[2] ^= t;\n        s_[3] = rotl(s_[3], 45);\n        return res;\n \
    \   }\n\npublic:\n    // see: https://prng.di.unimi.it/splitmix64.c\n    // original\
    \ license CC0 1.0\n    explicit xoshiro256starstar(u64 seed) {\n        for (int\
    \ i = 0; i < 4; ++i) {\n            u64 z = (seed += 0x9e3779b97f4a7c15);\n  \
    \          z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n            z     =\
    \ (z ^ (z >> 27)) * 0x94d049bb133111eb;\n            s_[i] = z ^ (z >> 31);\n\
    \        }\n    }\n    // see: https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator\n\
    \    using result_type = u64;\n    static constexpr u64 min() { return std::numeric_limits<u64>::min();\
    \ }\n    static constexpr u64 max() { return std::numeric_limits<u64>::max();\
    \ }\n    u64 operator()() { return next(); }\n};\n#line 4 \"random.hpp\"\n#include\
    \ <random>\n#include <vector>\n\ntemplate<typename Tp> inline std::vector<Tp>\
    \ random_vector(int n) {\n    std::vector<Tp> res(n);\n    xoshiro256starstar\
    \ rng(std::random_device{}());\n    std::uniform_int_distribution<decltype(Tp::mod())>\
    \ dis(0, Tp::mod() - 1);\n    for (int i = 0; i < n; ++i) res[i] = dis(rng);\n\
    \    return res;\n}\n\ntemplate<typename Tp> inline std::vector<Tp> random_vector_without_zero(int\
    \ n) {\n    std::vector<Tp> res(n);\n    xoshiro256starstar rng(std::random_device{}());\n\
    \    std::uniform_int_distribution<decltype(Tp::mod())> dis(1, Tp::mod() - 1);\n\
    \    for (int i = 0; i < n; ++i) res[i] = dis(rng);\n    return res;\n}\n"
  code: "#pragma once\n\n#include \"rng.hpp\"\n#include <random>\n#include <vector>\n\
    \ntemplate<typename Tp> inline std::vector<Tp> random_vector(int n) {\n    std::vector<Tp>\
    \ res(n);\n    xoshiro256starstar rng(std::random_device{}());\n    std::uniform_int_distribution<decltype(Tp::mod())>\
    \ dis(0, Tp::mod() - 1);\n    for (int i = 0; i < n; ++i) res[i] = dis(rng);\n\
    \    return res;\n}\n\ntemplate<typename Tp> inline std::vector<Tp> random_vector_without_zero(int\
    \ n) {\n    std::vector<Tp> res(n);\n    xoshiro256starstar rng(std::random_device{}());\n\
    \    std::uniform_int_distribution<decltype(Tp::mod())> dis(1, Tp::mod() - 1);\n\
    \    for (int i = 0; i < n; ++i) res[i] = dis(rng);\n    return res;\n}\n"
  dependsOn:
  - rng.hpp
  isVerificationFile: false
  path: random.hpp
  requiredBy:
  - mat_sparse.hpp
  - mat_basic.hpp
  - frobenius.hpp
  - mat_extra.hpp
  - basis.hpp
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/2d_convolution.0.test.cpp
  - test/formal_power_series/multivariate_power_series.0.test.cpp
  - test/matrix/characteristic_polynomial.1.test.cpp
  - test/matrix/matrix_det.0.test.cpp
  - test/matrix/inverse_matrix.0.test.cpp
  - test/matrix/characteristic_polynomial.0.test.cpp
  - test/matrix/sparse_matrix_det.0.test.cpp
  - test/matrix/adjugate_matrix.0.test.cpp
  - test/matrix/pow_of_matrix.0.test.cpp
  - test/matrix/matrix_product.0.test.cpp
documentation_of: random.hpp
layout: document
redirect_from:
- /library/random.hpp
- /library/random.hpp.html
title: random.hpp
---
