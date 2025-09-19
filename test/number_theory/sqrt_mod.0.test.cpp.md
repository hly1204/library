---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: rng.hpp
    title: rng.hpp
  - icon: ':heavy_check_mark:'
    path: xgcd.hpp
    title: xgcd.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"test/number_theory/sqrt_mod.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#line 2 \"rng.hpp\"\n\n#include\
    \ <cstdint>\n#include <limits>\n\n// see: https://prng.di.unimi.it/xoshiro256starstar.c\n\
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
    \ }\n    u64 operator()() { return next(); }\n};\n#line 2 \"xgcd.hpp\"\n\n#include\
    \ <array>\n#include <type_traits>\n#include <utility>\n\n// returns [x, y, gcd(a,\
    \ b)] s.t. ax+by = gcd(a, b)\ntemplate<typename Int>\ninline std::enable_if_t<std::is_signed_v<Int>,\
    \ std::array<Int, 3>> xgcd(Int a, Int b) {\n    Int x11 = 1, x12 = 0, x21 = 0,\
    \ x22 = 1;\n    while (b) {\n        std::add_const_t<Int> q = a / b;\n      \
    \  x11                     = std::exchange(x21, x11 - x21 * q);\n        x12 \
    \                    = std::exchange(x22, x12 - x22 * q);\n        a         \
    \              = std::exchange(b, a - b * q);\n    }\n    return {x11, x12, a};\n\
    }\n\n// returns [a^(-1) mod b, gcd(a, b)]\ntemplate<typename Int>\ninline std::enable_if_t<std::is_signed_v<Int>,\
    \ std::array<Int, 2>> inv_gcd(Int a, Int b) {\n    Int x11 = 1, x21 = 0;\n   \
    \ while (b) {\n        std::add_const_t<Int> q = a / b;\n        x11         \
    \            = std::exchange(x21, x11 - x21 * q);\n        a                 \
    \      = std::exchange(b, a - b * q);\n    }\n    return {x11, a}; // check x11\
    \ < 0, check a = 1\n}\n#line 5 \"test/number_theory/sqrt_mod.0.test.cpp\"\n#include\
    \ <iostream>\n#include <random>\n\nint inv_mod(int a, int mod) {\n    const int\
    \ res = std::get<0>(inv_gcd(a, mod));\n    return res < 0 ? res + mod : res;\n\
    }\n\nint pow_mod(int a, int e, int mod) {\n    if (e < 0) return pow_mod(inv_mod(a,\
    \ mod), -e, mod);\n    for (int res = 1;; a = (long long)a * a % mod) {\n    \
    \    if (e & 1) res = (long long)res * a % mod;\n        if ((e /= 2) == 0) return\
    \ res;\n    }\n}\n\n// Tonelli--Shanks's algorithm\n// see:\n// [1]: Daniel. J.\
    \ Bernstein. Faster Square Roots in Annoying Finite Fields.\nint sqrt_mod(int\
    \ a, int mod) {\n    // mod must be prime\n    if (a == 0 || mod == 2) return\
    \ a;\n\n    auto is_square = [](int a, int mod) { return pow_mod(a, (mod - 1)\
    \ / 2, mod) == 1; };\n\n    if (!is_square(a, mod)) return -1;\n\n    static xoshiro256starstar\
    \ rng{std::random_device{}()};\n    std::uniform_int_distribution<> dis(2, mod\
    \ - 1);\n\n    int r;\n    do { r = dis(rng); } while (is_square(r, mod));\n\n\
    \    int n = 1, m = (mod - 1) / 2;\n    while (m % 2 == 0) ++n, m /= 2;\n    //\
    \ mod = 2^n m\n\n    const int am = pow_mod(a, m, mod);\n    // ord(c) = 2^n\n\
    \    const int c = pow_mod(r, m, mod);\n\n    // find e such that a^m=c^e\n  \
    \  int e = 0;\n    for (int i = 1, j = 2; i < n; ++i, j *= 2) {\n        // One\
    \ can reduce the constant factor by\n        // calculating something during the\
    \ iteration,\n        // but it is not necessary.\n        if (pow_mod((long long)am\
    \ * pow_mod(c, -e, mod) % mod, (mod - 1) / (m * j * 2), mod) == 1)\n         \
    \   continue;\n        e += j;\n    }\n\n    // now set m=2j+1 => a^(2j)a=c^e\
    \ => a=c^ea^(-2j)\n    return (long long)pow_mod(c, e / 2, mod) * pow_mod(a, -(m\
    \ / 2), mod) % mod;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int T;\n    std::cin >> T;\n    while (T--) {\n\
    \        int a, mod;\n        std::cin >> a >> mod;\n        std::cout << sqrt_mod(a,\
    \ mod) << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include\
    \ \"rng.hpp\"\n#include \"xgcd.hpp\"\n#include <iostream>\n#include <random>\n\
    \nint inv_mod(int a, int mod) {\n    const int res = std::get<0>(inv_gcd(a, mod));\n\
    \    return res < 0 ? res + mod : res;\n}\n\nint pow_mod(int a, int e, int mod)\
    \ {\n    if (e < 0) return pow_mod(inv_mod(a, mod), -e, mod);\n    for (int res\
    \ = 1;; a = (long long)a * a % mod) {\n        if (e & 1) res = (long long)res\
    \ * a % mod;\n        if ((e /= 2) == 0) return res;\n    }\n}\n\n// Tonelli--Shanks's\
    \ algorithm\n// see:\n// [1]: Daniel. J. Bernstein. Faster Square Roots in Annoying\
    \ Finite Fields.\nint sqrt_mod(int a, int mod) {\n    // mod must be prime\n \
    \   if (a == 0 || mod == 2) return a;\n\n    auto is_square = [](int a, int mod)\
    \ { return pow_mod(a, (mod - 1) / 2, mod) == 1; };\n\n    if (!is_square(a, mod))\
    \ return -1;\n\n    static xoshiro256starstar rng{std::random_device{}()};\n \
    \   std::uniform_int_distribution<> dis(2, mod - 1);\n\n    int r;\n    do { r\
    \ = dis(rng); } while (is_square(r, mod));\n\n    int n = 1, m = (mod - 1) / 2;\n\
    \    while (m % 2 == 0) ++n, m /= 2;\n    // mod = 2^n m\n\n    const int am =\
    \ pow_mod(a, m, mod);\n    // ord(c) = 2^n\n    const int c = pow_mod(r, m, mod);\n\
    \n    // find e such that a^m=c^e\n    int e = 0;\n    for (int i = 1, j = 2;\
    \ i < n; ++i, j *= 2) {\n        // One can reduce the constant factor by\n  \
    \      // calculating something during the iteration,\n        // but it is not\
    \ necessary.\n        if (pow_mod((long long)am * pow_mod(c, -e, mod) % mod, (mod\
    \ - 1) / (m * j * 2), mod) == 1)\n            continue;\n        e += j;\n   \
    \ }\n\n    // now set m=2j+1 => a^(2j)a=c^e => a=c^ea^(-2j)\n    return (long\
    \ long)pow_mod(c, e / 2, mod) * pow_mod(a, -(m / 2), mod) % mod;\n}\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ T;\n    std::cin >> T;\n    while (T--) {\n        int a, mod;\n        std::cin\
    \ >> a >> mod;\n        std::cout << sqrt_mod(a, mod) << '\\n';\n    }\n    return\
    \ 0;\n}\n"
  dependsOn:
  - rng.hpp
  - xgcd.hpp
  isVerificationFile: true
  path: test/number_theory/sqrt_mod.0.test.cpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/number_theory/sqrt_mod.0.test.cpp
layout: document
redirect_from:
- /verify/test/number_theory/sqrt_mod.0.test.cpp
- /verify/test/number_theory/sqrt_mod.0.test.cpp.html
title: test/number_theory/sqrt_mod.0.test.cpp
---
