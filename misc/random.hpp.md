---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "pseudo random generator / \u4F2A\u968F\u673A\u6570\u751F\u6210\
      \u5668"
    links:
    - https://prng.di.unimi.it/splitmix64.c
    - https://prng.di.unimi.it/xoshiro256starstar.c
  bundledCode: "#line 1 \"misc/random.hpp\"\n\n\n\n#include <cassert>\n#include <cstdint>\n\
    #include <type_traits>\n\nnamespace lib {\n\n// xoshiro256starstar\n// reference:\
    \ https://prng.di.unimi.it/xoshiro256starstar.c\n// \u5468\u671F\u4E3A 2^{256}-1\n\
    // UINT64_C(x) \u7B49\u4EF7\u4E8E\u5728 x \u540E\u9762\u62FC\u63A5 ULL\nclass\
    \ Random {\nprivate:\n  using u64 = std::uint64_t;\n\npublic:\n  // splitmix64\n\
    \  // reference: https://prng.di.unimi.it/splitmix64.c\n  Random(u64 x = 0) {\
    \ // x \u4E3A\u79CD\u5B50\n    for (int i = 0; i < 4; ++i) {\n      u64 z = (x\
    \ += 0x9e3779b97f4a7c15);\n      z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n \
    \     z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n      s[i] = z ^ (z >> 31);\n\
    \    }\n  }\n  ~Random() = default;\n\n  template <typename T>\n  std::enable_if_t<std::is_integral_v<T>,\
    \ T> uniform_int(T upper) { // [0, upper]\n    assert(upper > 0);\n    u64 mask\
    \ = u64(upper);\n    mask |= mask >> 1;\n    mask |= mask >> 2;\n    mask |= mask\
    \ >> 4;\n    mask |= mask >> 8;\n    mask |= mask >> 16;\n    if constexpr (sizeof(T)\
    \ > 4) mask |= mask >> 32;\n    for (;;) {\n      u64 res = next() & mask;\n \
    \     if (res <= upper) return T(res);\n    }\n  }\n\n  template <typename T>\n\
    \  std::enable_if_t<std::is_integral_v<T>, T> uniform_int(T lower, T upper) {\
    \ // [lower, upper]\n    assert(upper > lower);\n    // \u5982\u679C\u662F std::numeric_limits<int>::min()\
    \ \u5230 0 \u8303\u56F4\u5185\n    // upper - lower \u7684\u884C\u4E3A\u662F\u672A\
    \u5B9A\u4E49\u7684\uFF0C\u7C7B\u4F3C\u7684\u4E5F\u662F\uFF0C\u4F46\u8FD9\u91CC\
    \u4E0D\u4F5C\u5224\u65AD\n    return uniform_int(upper - lower) + lower;\n  }\n\
    \n  void jump() { // \u7B49\u4EF7\u4E8E\u8C03\u7528 2^128 \u6B21 next()\n    static\
    \ const u64 JUMP[] = {0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa,\n\
    \                               0x39abdc4529b1661c};\n    u64 s0 = 0;\n    u64\
    \ s1 = 0;\n    u64 s2 = 0;\n    u64 s3 = 0;\n    for (int i = 0; i < sizeof JUMP\
    \ / sizeof *JUMP; i++)\n      for (int b = 0; b < 64; b++) {\n        if (JUMP[i]\
    \ & UINT64_C(1) << b) {\n          s0 ^= s[0];\n          s1 ^= s[1];\n      \
    \    s2 ^= s[2];\n          s3 ^= s[3];\n        }\n        next();\n      }\n\
    \    s[0] = s0;\n    s[1] = s1;\n    s[2] = s2;\n    s[3] = s3;\n  }\n  void long_jump()\
    \ { // \u7B49\u4EF7\u4E8E\u8C03\u7528 2^192 \u6B21 next() \u4E0E\u4E0A\u8FF0\u533A\
    \u522B\u5728\u4E8E 2^64 \u6B21\u8C03\u7528\n    static const u64 LONG_JUMP[] =\
    \ {0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241,\n             \
    \                       0x39109bb02acbe635};\n    u64 s0 = 0;\n    u64 s1 = 0;\n\
    \    u64 s2 = 0;\n    u64 s3 = 0;\n    for (int i = 0; i < sizeof LONG_JUMP /\
    \ sizeof *LONG_JUMP; i++)\n      for (int b = 0; b < 64; b++) {\n        if (LONG_JUMP[i]\
    \ & UINT64_C(1) << b) {\n          s0 ^= s[0];\n          s1 ^= s[1];\n      \
    \    s2 ^= s[2];\n          s3 ^= s[3];\n        }\n        next();\n      }\n\
    \    s[0] = s0;\n    s[1] = s1;\n    s[2] = s2;\n    s[3] = s3;\n  }\n\nprivate:\n\
    \  u64 s[4];\n  static inline u64 rotl(const u64 x, int k) { return (x << k) |\
    \ (x >> (64 - k)); }\n  u64 next() {\n    const u64 result = rotl(s[1] * 5, 7)\
    \ * 9;\n    const u64 t = s[1] << 17;\n    s[2] ^= s[0];\n    s[3] ^= s[1];\n\
    \    s[1] ^= s[2];\n    s[0] ^= s[3];\n    s[2] ^= t;\n    s[3] = rotl(s[3], 45);\n\
    \    return result;\n  }\n};\n\n} // namespace lib\n\n/**\n * @brief pseudo random\
    \ generator / \u4F2A\u968F\u673A\u6570\u751F\u6210\u5668\n *\n */\n\n\n"
  code: "#ifndef RANDOM_XOSHIRO256STARSTAR_HEADER_HPP\n#define RANDOM_XOSHIRO256STARSTAR_HEADER_HPP\n\
    \n#include <cassert>\n#include <cstdint>\n#include <type_traits>\n\nnamespace\
    \ lib {\n\n// xoshiro256starstar\n// reference: https://prng.di.unimi.it/xoshiro256starstar.c\n\
    // \u5468\u671F\u4E3A 2^{256}-1\n// UINT64_C(x) \u7B49\u4EF7\u4E8E\u5728 x \u540E\
    \u9762\u62FC\u63A5 ULL\nclass Random {\nprivate:\n  using u64 = std::uint64_t;\n\
    \npublic:\n  // splitmix64\n  // reference: https://prng.di.unimi.it/splitmix64.c\n\
    \  Random(u64 x = 0) { // x \u4E3A\u79CD\u5B50\n    for (int i = 0; i < 4; ++i)\
    \ {\n      u64 z = (x += 0x9e3779b97f4a7c15);\n      z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \      z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n      s[i] = z ^ (z >> 31);\n\
    \    }\n  }\n  ~Random() = default;\n\n  template <typename T>\n  std::enable_if_t<std::is_integral_v<T>,\
    \ T> uniform_int(T upper) { // [0, upper]\n    assert(upper > 0);\n    u64 mask\
    \ = u64(upper);\n    mask |= mask >> 1;\n    mask |= mask >> 2;\n    mask |= mask\
    \ >> 4;\n    mask |= mask >> 8;\n    mask |= mask >> 16;\n    if constexpr (sizeof(T)\
    \ > 4) mask |= mask >> 32;\n    for (;;) {\n      u64 res = next() & mask;\n \
    \     if (res <= upper) return T(res);\n    }\n  }\n\n  template <typename T>\n\
    \  std::enable_if_t<std::is_integral_v<T>, T> uniform_int(T lower, T upper) {\
    \ // [lower, upper]\n    assert(upper > lower);\n    // \u5982\u679C\u662F std::numeric_limits<int>::min()\
    \ \u5230 0 \u8303\u56F4\u5185\n    // upper - lower \u7684\u884C\u4E3A\u662F\u672A\
    \u5B9A\u4E49\u7684\uFF0C\u7C7B\u4F3C\u7684\u4E5F\u662F\uFF0C\u4F46\u8FD9\u91CC\
    \u4E0D\u4F5C\u5224\u65AD\n    return uniform_int(upper - lower) + lower;\n  }\n\
    \n  void jump() { // \u7B49\u4EF7\u4E8E\u8C03\u7528 2^128 \u6B21 next()\n    static\
    \ const u64 JUMP[] = {0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa,\n\
    \                               0x39abdc4529b1661c};\n    u64 s0 = 0;\n    u64\
    \ s1 = 0;\n    u64 s2 = 0;\n    u64 s3 = 0;\n    for (int i = 0; i < sizeof JUMP\
    \ / sizeof *JUMP; i++)\n      for (int b = 0; b < 64; b++) {\n        if (JUMP[i]\
    \ & UINT64_C(1) << b) {\n          s0 ^= s[0];\n          s1 ^= s[1];\n      \
    \    s2 ^= s[2];\n          s3 ^= s[3];\n        }\n        next();\n      }\n\
    \    s[0] = s0;\n    s[1] = s1;\n    s[2] = s2;\n    s[3] = s3;\n  }\n  void long_jump()\
    \ { // \u7B49\u4EF7\u4E8E\u8C03\u7528 2^192 \u6B21 next() \u4E0E\u4E0A\u8FF0\u533A\
    \u522B\u5728\u4E8E 2^64 \u6B21\u8C03\u7528\n    static const u64 LONG_JUMP[] =\
    \ {0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241,\n             \
    \                       0x39109bb02acbe635};\n    u64 s0 = 0;\n    u64 s1 = 0;\n\
    \    u64 s2 = 0;\n    u64 s3 = 0;\n    for (int i = 0; i < sizeof LONG_JUMP /\
    \ sizeof *LONG_JUMP; i++)\n      for (int b = 0; b < 64; b++) {\n        if (LONG_JUMP[i]\
    \ & UINT64_C(1) << b) {\n          s0 ^= s[0];\n          s1 ^= s[1];\n      \
    \    s2 ^= s[2];\n          s3 ^= s[3];\n        }\n        next();\n      }\n\
    \    s[0] = s0;\n    s[1] = s1;\n    s[2] = s2;\n    s[3] = s3;\n  }\n\nprivate:\n\
    \  u64 s[4];\n  static inline u64 rotl(const u64 x, int k) { return (x << k) |\
    \ (x >> (64 - k)); }\n  u64 next() {\n    const u64 result = rotl(s[1] * 5, 7)\
    \ * 9;\n    const u64 t = s[1] << 17;\n    s[2] ^= s[0];\n    s[3] ^= s[1];\n\
    \    s[1] ^= s[2];\n    s[0] ^= s[3];\n    s[2] ^= t;\n    s[3] = rotl(s[3], 45);\n\
    \    return result;\n  }\n};\n\n} // namespace lib\n\n/**\n * @brief pseudo random\
    \ generator / \u4F2A\u968F\u673A\u6570\u751F\u6210\u5668\n *\n */\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: misc/random.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:47:15+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: misc/random.hpp
layout: document
redirect_from:
- /library/misc/random.hpp
- /library/misc/random.hpp.html
title: "pseudo random generator / \u4F2A\u968F\u673A\u6570\u751F\u6210\u5668"
---
