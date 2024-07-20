---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps_sqrt.hpp
    title: fps_sqrt.hpp
  - icon: ':heavy_check_mark:'
    path: frobenius.hpp
    title: frobenius.hpp
  - icon: ':heavy_check_mark:'
    path: random.hpp
    title: random.hpp
  - icon: ':heavy_check_mark:'
    path: sqrt_mod.hpp
    title: sqrt_mod.hpp
  - icon: ':heavy_check_mark:'
    path: treap_node_base.hpp
    title: treap_node_base.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
    title: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/point_set_range_composite.0.test.cpp
    title: test/data_structure/point_set_range_composite.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/range_affine_point_get.0.test.cpp
    title: test/data_structure/range_affine_point_get.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/range_affine_range_sum.0.test.cpp
    title: test/data_structure/range_affine_range_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/range_reverse_range_sum.0.test.cpp
    title: test/data_structure/range_reverse_range_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
    title: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/characteristic_polynomial.1.test.cpp
    title: test/matrix/characteristic_polynomial.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/pow_of_matrix.0.test.cpp
    title: test/matrix/pow_of_matrix.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator
    - https://prng.di.unimi.it/splitmix64.c
    - https://prng.di.unimi.it/xoshiro256starstar.c
  bundledCode: "#line 2 \"rng.hpp\"\n\n#include <cstdint>\n#include <limits>\n\n//\
    \ see: https://prng.di.unimi.it/xoshiro256starstar.c\n// original license CC0\
    \ 1.0\nclass xoshiro256starstar {\n    using u64 = std::uint64_t;\n\n    static\
    \ inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64 - k)); }\n\
    \n    u64 s_[4];\n\n    u64 next() {\n        const u64 res = rotl(s_[1] * 5,\
    \ 7) * 9;\n        const u64 t   = s_[1] << 17;\n        s_[2] ^= s_[0];\n   \
    \     s_[3] ^= s_[1];\n        s_[1] ^= s_[2];\n        s_[0] ^= s_[3];\n    \
    \    s_[2] ^= t;\n        s_[3] = rotl(s_[3], 45);\n        return res;\n    }\n\
    \npublic:\n    // see: https://prng.di.unimi.it/splitmix64.c\n    // original\
    \ license CC0 1.0\n    explicit xoshiro256starstar(u64 seed) {\n        for (int\
    \ i = 0; i < 4; ++i) {\n            u64 z = (seed += 0x9e3779b97f4a7c15);\n  \
    \          z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n            z     =\
    \ (z ^ (z >> 27)) * 0x94d049bb133111eb;\n            s_[i] = z ^ (z >> 31);\n\
    \        }\n    }\n    // see: https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator\n\
    \    using result_type = u64;\n    static constexpr u64 min() { return std::numeric_limits<u64>::min();\
    \ }\n    static constexpr u64 max() { return std::numeric_limits<u64>::max();\
    \ }\n    u64 operator()() { return next(); }\n};\n"
  code: "#pragma once\n\n#include <cstdint>\n#include <limits>\n\n// see: https://prng.di.unimi.it/xoshiro256starstar.c\n\
    // original license CC0 1.0\nclass xoshiro256starstar {\n    using u64 = std::uint64_t;\n\
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
    \ }\n    u64 operator()() { return next(); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: rng.hpp
  requiredBy:
  - random.hpp
  - fps_sqrt.hpp
  - frobenius.hpp
  - sqrt_mod.hpp
  - treap_node_base.hpp
  timestamp: '2024-05-15 00:00:04+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
  - test/data_structure/range_reverse_range_sum.0.test.cpp
  - test/data_structure/range_affine_point_get.0.test.cpp
  - test/data_structure/range_affine_range_sum.0.test.cpp
  - test/data_structure/point_set_range_composite.0.test.cpp
  - test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
  - test/matrix/pow_of_matrix.0.test.cpp
  - test/matrix/characteristic_polynomial.1.test.cpp
documentation_of: rng.hpp
layout: document
redirect_from:
- /library/rng.hpp
- /library/rng.hpp.html
title: rng.hpp
---
