---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: rng.hpp
    title: rng.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps_sqrt.hpp
    title: fps_sqrt.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
    title: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sqrt_mod.hpp\"\n\n#line 2 \"rng.hpp\"\n\n#include <cstdint>\n\
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
    \ }\n    u64 operator()() { return next(); }\n};\n#line 4 \"sqrt_mod.hpp\"\n#include\
    \ <random>\n#include <type_traits>\n#include <vector>\n\ntemplate<typename Tp>\
    \ inline std::vector<Tp> sqrt_mod_prime(Tp a) {\n    // Bostan--Mori's algorithm\n\
    \    const auto p = Tp::mod();\n    if (p == 2 || a == 0) return {a};\n    if\
    \ (a.pow(p / 2) == -1) return {};\n    if ((p & 3) == 3) {\n        const auto\
    \ b = a.pow((p + 1) / 4);\n        return {b, -b};\n    }\n    xoshiro256starstar\
    \ rng(std::random_device{}());\n    std::uniform_int_distribution<std::decay_t<decltype(p)>>\
    \ dis(2, p - 1);\n    Tp t;\n    do { t = dis(rng); } while ((t * t - a * 4).pow(p\
    \ / 2) != -1);\n    Tp k0 = 1, k1, k2 = -t, k3 = a;\n    for (auto e = (p + 1)\
    \ >> 1;;) {\n        if (e & 1) {\n            k0 = k1 - k0 * k2, k1 *= k3;\n\
    \        } else {\n            k1 = k0 * k3 - k1 * k2;\n        }\n        if\
    \ ((e >>= 1) == 0) return {k0, -k0};\n        k2 = k3 + k3 - k2 * k2, k3 *= k3;\n\
    \    }\n}\n"
  code: "#pragma once\n\n#include \"rng.hpp\"\n#include <random>\n#include <type_traits>\n\
    #include <vector>\n\ntemplate<typename Tp> inline std::vector<Tp> sqrt_mod_prime(Tp\
    \ a) {\n    // Bostan--Mori's algorithm\n    const auto p = Tp::mod();\n    if\
    \ (p == 2 || a == 0) return {a};\n    if (a.pow(p / 2) == -1) return {};\n   \
    \ if ((p & 3) == 3) {\n        const auto b = a.pow((p + 1) / 4);\n        return\
    \ {b, -b};\n    }\n    xoshiro256starstar rng(std::random_device{}());\n    std::uniform_int_distribution<std::decay_t<decltype(p)>>\
    \ dis(2, p - 1);\n    Tp t;\n    do { t = dis(rng); } while ((t * t - a * 4).pow(p\
    \ / 2) != -1);\n    Tp k0 = 1, k1, k2 = -t, k3 = a;\n    for (auto e = (p + 1)\
    \ >> 1;;) {\n        if (e & 1) {\n            k0 = k1 - k0 * k2, k1 *= k3;\n\
    \        } else {\n            k1 = k0 * k3 - k1 * k2;\n        }\n        if\
    \ ((e >>= 1) == 0) return {k0, -k0};\n        k2 = k3 + k3 - k2 * k2, k3 *= k3;\n\
    \    }\n}\n"
  dependsOn:
  - rng.hpp
  isVerificationFile: false
  path: sqrt_mod.hpp
  requiredBy:
  - fps_sqrt.hpp
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
documentation_of: sqrt_mod.hpp
layout: document
redirect_from:
- /library/sqrt_mod.hpp
- /library/sqrt_mod.hpp.html
title: sqrt_mod.hpp
---
