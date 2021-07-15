---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/arbitrary_modulo_convolution.hpp
    title: "arbitrary modulo convolution / \u4EFB\u610F\u6A21\u6570\u5377\u79EF"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "NTT prime crt / NTT \u7D20\u6570\u7528\u4E2D\u56FD\u5269\u4F59\
      \u5B9A\u7406"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/NTT_crt.hpp\"\n\n\n\n/**\n * @brief\
    \ NTT prime crt / NTT \u7D20\u6570\u7528\u4E2D\u56FD\u5269\u4F59\u5B9A\u7406\n\
    \ *\n */\n\n#include <cstdint>\n#include <type_traits>\n\nnamespace lib {\n\n\
    template <std::uint32_t M0, std::uint32_t M1, std::uint32_t M2,\n          std::enable_if_t<(M0\
    \ < M1) && ((M0 | M1 | M2) < (1U << 31)) &&\n                               ((M0\
    \ & M1 & M2 & 1) == 1) && (M0 != M1) && (M0 != M2) && (M1 != M2),\n          \
    \                 int> = 0>\nclass NTTCRT3 {\npublic:\n  using u32 = std::uint32_t;\n\
    \  using u64 = std::uint64_t;\n\n  NTTCRT3(u32 mod) : m_(mod), M0M1_mod_m_(u64(M0)\
    \ * M1 % mod) {}\n  ~NTTCRT3() = default;\n\n  u32 operator()(u32 a, u32 b, u32\
    \ c) const {\n    // x mod M0 = a, x mod M1 = b, x mod M2 = c\n    // a + k0M0\
    \ = b + k1M1 => k0 = (b - a) / M0 (mod M1)\n    // x = a + k0M0 (mod M0M1) =>\
    \ a + k0M0 + k01M0M1 = c + k2M2\n    // => k01 = (c - (a + k0M0)) / (M0M1) (mod\
    \ M2)\n    // => x mod M0M1M2 = a + k0M0 + k01M0M1\n    u32 k0 = b - a;\n    if\
    \ (int(k0) < 0) k0 += M1;\n    k0      = u64(k0) * M0_inv_M1_ % M1;\n    u64 d\
    \   = a + u64(k0) * M0;\n    u32 k01 = c - d % M2;\n    if (int(k01) < 0) k01\
    \ += M2;\n    // NTT \u6A21\u6570\u90FD\u5C0F\u4E8E (1U << 31) \u6240\u4EE5\u5728\
    \u8FD9\u91CC\u53EF\u4EE5\u4F7F\u7528\u52A0\u6CD5\u540E\u518D\u53D6\u6A21\n   \
    \ return (d + u64(k01) * M0M1_inv_M2_ % M2 * M0M1_mod_m_) % m_;\n  }\n\n  static\
    \ constexpr u32 get_inv(u32 x, u32 mod) {\n    u32 res = 1;\n    for (u32 e =\
    \ mod - 2; e != 0; e >>= 1) {\n      if (e & 1) res = u64(res) * x % mod;\n  \
    \    x = u64(x) * x % mod;\n    }\n    return res;\n  }\n\nprivate:\n  u32 m_,\
    \ M0M1_mod_m_;\n  static constexpr u32 M0_inv_M1_   = get_inv(M0, M1);\n  static\
    \ constexpr u32 M0M1_inv_M2_ = get_inv(u64(M0) * M1 % M2, M2);\n};\n\n} // namespace\
    \ lib\n\n\n"
  code: "#ifndef NTT_CRT_HEADER_HPP\n#define NTT_CRT_HEADER_HPP\n\n/**\n * @brief\
    \ NTT prime crt / NTT \u7D20\u6570\u7528\u4E2D\u56FD\u5269\u4F59\u5B9A\u7406\n\
    \ *\n */\n\n#include <cstdint>\n#include <type_traits>\n\nnamespace lib {\n\n\
    template <std::uint32_t M0, std::uint32_t M1, std::uint32_t M2,\n          std::enable_if_t<(M0\
    \ < M1) && ((M0 | M1 | M2) < (1U << 31)) &&\n                               ((M0\
    \ & M1 & M2 & 1) == 1) && (M0 != M1) && (M0 != M2) && (M1 != M2),\n          \
    \                 int> = 0>\nclass NTTCRT3 {\npublic:\n  using u32 = std::uint32_t;\n\
    \  using u64 = std::uint64_t;\n\n  NTTCRT3(u32 mod) : m_(mod), M0M1_mod_m_(u64(M0)\
    \ * M1 % mod) {}\n  ~NTTCRT3() = default;\n\n  u32 operator()(u32 a, u32 b, u32\
    \ c) const {\n    // x mod M0 = a, x mod M1 = b, x mod M2 = c\n    // a + k0M0\
    \ = b + k1M1 => k0 = (b - a) / M0 (mod M1)\n    // x = a + k0M0 (mod M0M1) =>\
    \ a + k0M0 + k01M0M1 = c + k2M2\n    // => k01 = (c - (a + k0M0)) / (M0M1) (mod\
    \ M2)\n    // => x mod M0M1M2 = a + k0M0 + k01M0M1\n    u32 k0 = b - a;\n    if\
    \ (int(k0) < 0) k0 += M1;\n    k0      = u64(k0) * M0_inv_M1_ % M1;\n    u64 d\
    \   = a + u64(k0) * M0;\n    u32 k01 = c - d % M2;\n    if (int(k01) < 0) k01\
    \ += M2;\n    // NTT \u6A21\u6570\u90FD\u5C0F\u4E8E (1U << 31) \u6240\u4EE5\u5728\
    \u8FD9\u91CC\u53EF\u4EE5\u4F7F\u7528\u52A0\u6CD5\u540E\u518D\u53D6\u6A21\n   \
    \ return (d + u64(k01) * M0M1_inv_M2_ % M2 * M0M1_mod_m_) % m_;\n  }\n\n  static\
    \ constexpr u32 get_inv(u32 x, u32 mod) {\n    u32 res = 1;\n    for (u32 e =\
    \ mod - 2; e != 0; e >>= 1) {\n      if (e & 1) res = u64(res) * x % mod;\n  \
    \    x = u64(x) * x % mod;\n    }\n    return res;\n  }\n\nprivate:\n  u32 m_,\
    \ M0M1_mod_m_;\n  static constexpr u32 M0_inv_M1_   = get_inv(M0, M1);\n  static\
    \ constexpr u32 M0M1_inv_M2_ = get_inv(u64(M0) * M1 % M2, M2);\n};\n\n} // namespace\
    \ lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/formal_power_series/NTT_crt.hpp
  requiredBy:
  - math/formal_power_series/arbitrary_modulo_convolution.hpp
  timestamp: '2021-07-15 14:25:20+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
documentation_of: math/formal_power_series/NTT_crt.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/NTT_crt.hpp
- /library/math/formal_power_series/NTT_crt.hpp.html
title: "NTT prime crt / NTT \u7D20\u6570\u7528\u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
---
