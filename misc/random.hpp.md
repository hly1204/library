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
  bundledCode: "#line 1 \"misc/random.hpp\"\n\n\n\r\n/**\r\n * @brief pseudo random\
    \ generator / \u4F2A\u968F\u673A\u6570\u751F\u6210\u5668\r\n *\r\n */\r\n\r\n\
    #include <cassert>\r\n#include <cstdint>\r\n#include <type_traits>\r\n\r\nnamespace\
    \ lib {\r\n\r\n/**\r\n * @brief xoshiro256starstar\r\n * @see https://prng.di.unimi.it/xoshiro256starstar.c\r\
    \n */\r\nclass Random {\r\nprivate:\r\n  using u64 = std::uint64_t;\r\n\r\npublic:\r\
    \n  /**\r\n   * @brief \u521B\u5EFA\u4E00\u4E2A\u65B0\u7684\u968F\u673A\u6570\u5BF9\
    \u8C61\uFF0C\u5171\u7528\u540C\u4E00\u4E2A\u79CD\u5B50\r\n   * @param x \u79CD\
    \u5B50\r\n   * @see https://prng.di.unimi.it/splitmix64.c\r\n   */\r\n  Random(u64\
    \ x = 0) {\r\n    for (int i = 0; i < 4; ++i) {\r\n      u64 z = (x += 0x9e3779b97f4a7c15);\r\
    \n      z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\r\n      z     = (z ^ (z\
    \ >> 27)) * 0x94d049bb133111eb;\r\n      s[i]  = z ^ (z >> 31);\r\n    }\r\n \
    \ }\r\n  ~Random() = default;\r\n\r\n  /**\r\n   * @brief \u8FD4\u56DE [0, upper]\
    \ \u4E2D\u5747\u5300\u5206\u5E03\u7684\u4E00\u4E2A\u6574\u6570\r\n   * @tparam\
    \ T\r\n   * @param upper \u4E0A\u754C\uFF0C\u53EF\u4EE5\u53D6\u5230\r\n   * @return\
    \ std::enable_if_t<std::is_integral_v<T>, T>\r\n   */\r\n  template <typename\
    \ T>\r\n  std::enable_if_t<std::is_integral_v<T>, T> uniform_int(T upper) {\r\n\
    \    assert(upper > 0);\r\n    u64 mask = u64(upper);\r\n    mask |= mask >> 1;\r\
    \n    mask |= mask >> 2;\r\n    mask |= mask >> 4;\r\n    mask |= mask >> 8;\r\
    \n    mask |= mask >> 16;\r\n    if constexpr (sizeof(T) > 4) mask |= mask >>\
    \ 32;\r\n    for (;;) {\r\n      u64 res = next() & mask;\r\n      if (res <=\
    \ upper) return T(res);\r\n    }\r\n  }\r\n\r\n  /**\r\n   * @brief \u8FD4\u56DE\
    \ [lower, upper] \u4E2D\u5747\u5300\u5206\u5E03\u7684\u4E00\u4E2A\u6574\u6570\r\
    \n   * @note \u8F93\u5165\u53EF\u80FD\u4F1A\u8D8A\u754C\uFF0C\u4F46\u8FD9\u91CC\
    \u4E0D\u5904\u7406\r\n   * @tparam T\r\n   * @param lower \u4E0B\u754C\uFF0C\u53EF\
    \u4EE5\u53D6\u5230\r\n   * @param upper \u4E0A\u754C\uFF0C\u53EF\u4EE5\u53D6\u5230\
    \r\n   * @return std::enable_if_t<std::is_integral_v<T>, T>\r\n   */\r\n  template\
    \ <typename T>\r\n  std::enable_if_t<std::is_integral_v<T>, T> uniform_int(T lower,\
    \ T upper) { // [lower, upper]\r\n    assert(upper > lower);\r\n    return uniform_int(upper\
    \ - lower) + lower;\r\n  }\r\n\r\n  void jump() { // \u7B49\u4EF7\u4E8E\u8C03\u7528\
    \ 2^128 \u6B21 next()\r\n    static const u64 JUMP[] = {0x180ec6d33cfd0aba, 0xd5a61266f0c9392c,\
    \ 0xa9582618e03fc9aa,\r\n                               0x39abdc4529b1661c};\r\
    \n    u64 s0                  = 0;\r\n    u64 s1                  = 0;\r\n   \
    \ u64 s2                  = 0;\r\n    u64 s3                  = 0;\r\n    for\
    \ (int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)\r\n      for (int b = 0; b\
    \ < 64; b++) {\r\n        if (JUMP[i] & UINT64_C(1) << b) {\r\n          s0 ^=\
    \ s[0];\r\n          s1 ^= s[1];\r\n          s2 ^= s[2];\r\n          s3 ^= s[3];\r\
    \n        }\r\n        next();\r\n      }\r\n    s[0] = s0;\r\n    s[1] = s1;\r\
    \n    s[2] = s2;\r\n    s[3] = s3;\r\n  }\r\n  void long_jump() { // \u7B49\u4EF7\
    \u4E8E\u8C03\u7528 2^192 \u6B21 next() \u4E0E\u4E0A\u8FF0\u533A\u522B\u5728\u4E8E\
    \ 2^64 \u6B21\u8C03\u7528\r\n    static const u64 LONG_JUMP[] = {0x76e15d3efefdcbbf,\
    \ 0xc5004e441c522fb3, 0x77710069854ee241,\r\n                                \
    \    0x39109bb02acbe635};\r\n    u64 s0                       = 0;\r\n    u64\
    \ s1                       = 0;\r\n    u64 s2                       = 0;\r\n \
    \   u64 s3                       = 0;\r\n    for (int i = 0; i < sizeof LONG_JUMP\
    \ / sizeof *LONG_JUMP; i++)\r\n      for (int b = 0; b < 64; b++) {\r\n      \
    \  if (LONG_JUMP[i] & UINT64_C(1) << b) {\r\n          s0 ^= s[0];\r\n       \
    \   s1 ^= s[1];\r\n          s2 ^= s[2];\r\n          s3 ^= s[3];\r\n        }\r\
    \n        next();\r\n      }\r\n    s[0] = s0;\r\n    s[1] = s1;\r\n    s[2] =\
    \ s2;\r\n    s[3] = s3;\r\n  }\r\n\r\nprivate:\r\n  u64 s[4];\r\n  static inline\
    \ u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64 - k)); }\r\n  u64\
    \ next() {\r\n    const u64 result = rotl(s[1] * 5, 7) * 9;\r\n    const u64 t\
    \      = s[1] << 17;\r\n    s[2] ^= s[0];\r\n    s[3] ^= s[1];\r\n    s[1] ^=\
    \ s[2];\r\n    s[0] ^= s[3];\r\n    s[2] ^= t;\r\n    s[3] = rotl(s[3], 45);\r\
    \n    return result;\r\n  }\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef RANDOM_XOSHIRO256STARSTAR_HEADER_HPP\r\n#define RANDOM_XOSHIRO256STARSTAR_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief pseudo random generator / \u4F2A\u968F\u673A\u6570\u751F\
    \u6210\u5668\r\n *\r\n */\r\n\r\n#include <cassert>\r\n#include <cstdint>\r\n\
    #include <type_traits>\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief xoshiro256starstar\r\
    \n * @see https://prng.di.unimi.it/xoshiro256starstar.c\r\n */\r\nclass Random\
    \ {\r\nprivate:\r\n  using u64 = std::uint64_t;\r\n\r\npublic:\r\n  /**\r\n  \
    \ * @brief \u521B\u5EFA\u4E00\u4E2A\u65B0\u7684\u968F\u673A\u6570\u5BF9\u8C61\uFF0C\
    \u5171\u7528\u540C\u4E00\u4E2A\u79CD\u5B50\r\n   * @param x \u79CD\u5B50\r\n \
    \  * @see https://prng.di.unimi.it/splitmix64.c\r\n   */\r\n  Random(u64 x = 0)\
    \ {\r\n    for (int i = 0; i < 4; ++i) {\r\n      u64 z = (x += 0x9e3779b97f4a7c15);\r\
    \n      z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\r\n      z     = (z ^ (z\
    \ >> 27)) * 0x94d049bb133111eb;\r\n      s[i]  = z ^ (z >> 31);\r\n    }\r\n \
    \ }\r\n  ~Random() = default;\r\n\r\n  /**\r\n   * @brief \u8FD4\u56DE [0, upper]\
    \ \u4E2D\u5747\u5300\u5206\u5E03\u7684\u4E00\u4E2A\u6574\u6570\r\n   * @tparam\
    \ T\r\n   * @param upper \u4E0A\u754C\uFF0C\u53EF\u4EE5\u53D6\u5230\r\n   * @return\
    \ std::enable_if_t<std::is_integral_v<T>, T>\r\n   */\r\n  template <typename\
    \ T>\r\n  std::enable_if_t<std::is_integral_v<T>, T> uniform_int(T upper) {\r\n\
    \    assert(upper > 0);\r\n    u64 mask = u64(upper);\r\n    mask |= mask >> 1;\r\
    \n    mask |= mask >> 2;\r\n    mask |= mask >> 4;\r\n    mask |= mask >> 8;\r\
    \n    mask |= mask >> 16;\r\n    if constexpr (sizeof(T) > 4) mask |= mask >>\
    \ 32;\r\n    for (;;) {\r\n      u64 res = next() & mask;\r\n      if (res <=\
    \ upper) return T(res);\r\n    }\r\n  }\r\n\r\n  /**\r\n   * @brief \u8FD4\u56DE\
    \ [lower, upper] \u4E2D\u5747\u5300\u5206\u5E03\u7684\u4E00\u4E2A\u6574\u6570\r\
    \n   * @note \u8F93\u5165\u53EF\u80FD\u4F1A\u8D8A\u754C\uFF0C\u4F46\u8FD9\u91CC\
    \u4E0D\u5904\u7406\r\n   * @tparam T\r\n   * @param lower \u4E0B\u754C\uFF0C\u53EF\
    \u4EE5\u53D6\u5230\r\n   * @param upper \u4E0A\u754C\uFF0C\u53EF\u4EE5\u53D6\u5230\
    \r\n   * @return std::enable_if_t<std::is_integral_v<T>, T>\r\n   */\r\n  template\
    \ <typename T>\r\n  std::enable_if_t<std::is_integral_v<T>, T> uniform_int(T lower,\
    \ T upper) { // [lower, upper]\r\n    assert(upper > lower);\r\n    return uniform_int(upper\
    \ - lower) + lower;\r\n  }\r\n\r\n  void jump() { // \u7B49\u4EF7\u4E8E\u8C03\u7528\
    \ 2^128 \u6B21 next()\r\n    static const u64 JUMP[] = {0x180ec6d33cfd0aba, 0xd5a61266f0c9392c,\
    \ 0xa9582618e03fc9aa,\r\n                               0x39abdc4529b1661c};\r\
    \n    u64 s0                  = 0;\r\n    u64 s1                  = 0;\r\n   \
    \ u64 s2                  = 0;\r\n    u64 s3                  = 0;\r\n    for\
    \ (int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)\r\n      for (int b = 0; b\
    \ < 64; b++) {\r\n        if (JUMP[i] & UINT64_C(1) << b) {\r\n          s0 ^=\
    \ s[0];\r\n          s1 ^= s[1];\r\n          s2 ^= s[2];\r\n          s3 ^= s[3];\r\
    \n        }\r\n        next();\r\n      }\r\n    s[0] = s0;\r\n    s[1] = s1;\r\
    \n    s[2] = s2;\r\n    s[3] = s3;\r\n  }\r\n  void long_jump() { // \u7B49\u4EF7\
    \u4E8E\u8C03\u7528 2^192 \u6B21 next() \u4E0E\u4E0A\u8FF0\u533A\u522B\u5728\u4E8E\
    \ 2^64 \u6B21\u8C03\u7528\r\n    static const u64 LONG_JUMP[] = {0x76e15d3efefdcbbf,\
    \ 0xc5004e441c522fb3, 0x77710069854ee241,\r\n                                \
    \    0x39109bb02acbe635};\r\n    u64 s0                       = 0;\r\n    u64\
    \ s1                       = 0;\r\n    u64 s2                       = 0;\r\n \
    \   u64 s3                       = 0;\r\n    for (int i = 0; i < sizeof LONG_JUMP\
    \ / sizeof *LONG_JUMP; i++)\r\n      for (int b = 0; b < 64; b++) {\r\n      \
    \  if (LONG_JUMP[i] & UINT64_C(1) << b) {\r\n          s0 ^= s[0];\r\n       \
    \   s1 ^= s[1];\r\n          s2 ^= s[2];\r\n          s3 ^= s[3];\r\n        }\r\
    \n        next();\r\n      }\r\n    s[0] = s0;\r\n    s[1] = s1;\r\n    s[2] =\
    \ s2;\r\n    s[3] = s3;\r\n  }\r\n\r\nprivate:\r\n  u64 s[4];\r\n  static inline\
    \ u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64 - k)); }\r\n  u64\
    \ next() {\r\n    const u64 result = rotl(s[1] * 5, 7) * 9;\r\n    const u64 t\
    \      = s[1] << 17;\r\n    s[2] ^= s[0];\r\n    s[3] ^= s[1];\r\n    s[1] ^=\
    \ s[2];\r\n    s[0] ^= s[3];\r\n    s[2] ^= t;\r\n    s[3] = rotl(s[3], 45);\r\
    \n    return result;\r\n  }\r\n};\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: misc/random.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: misc/random.hpp
layout: document
redirect_from:
- /library/misc/random.hpp
- /library/misc/random.hpp.html
title: "pseudo random generator / \u4F2A\u968F\u673A\u6570\u751F\u6210\u5668"
---
