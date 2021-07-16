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
  bundledCode: "#line 1 \"math/formal_power_series/NTT_crt.hpp\"\n\n\n\r\n/**\r\n\
    \ * @brief NTT prime crt / NTT \u7D20\u6570\u7528\u4E2D\u56FD\u5269\u4F59\u5B9A\
    \u7406\r\n *\r\n */\r\n\r\n#include <cstdint>\r\n#include <type_traits>\r\n\r\n\
    namespace lib {\r\n\r\ntemplate <std::uint32_t M0, std::uint32_t M1, std::uint32_t\
    \ M2,\r\n          std::enable_if_t<(M0 < M1) && ((M0 | M1 | M2) < (1U << 31))\
    \ &&\r\n                               ((M0 & M1 & M2 & 1) == 1) && (M0 != M1)\
    \ && (M0 != M2) && (M1 != M2),\r\n                           int> = 0>\r\nclass\
    \ NTTCRT3 {\r\npublic:\r\n  using u32 = std::uint32_t;\r\n  using u64 = std::uint64_t;\r\
    \n\r\n  constexpr NTTCRT3(u32 mod) : m_(mod), M0M1_mod_m_(u64(M0) * M1 % mod)\
    \ {}\r\n  ~NTTCRT3() = default;\r\n\r\n  constexpr u32 operator()(u32 a, u32 b,\
    \ u32 c) const {\r\n    // x mod M0 = a, x mod M1 = b, x mod M2 = c\r\n    //\
    \ a + k0M0 = b + k1M1 => k0 = (b - a) / M0 (mod M1)\r\n    // x = a + k0M0 (mod\
    \ M0M1) => a + k0M0 + k01M0M1 = c + k2M2\r\n    // => k01 = (c - (a + k0M0)) /\
    \ (M0M1) (mod M2)\r\n    // => x mod M0M1M2 = a + k0M0 + k01M0M1\r\n    u32 k0\
    \ = b - a;\r\n    if (int(k0) < 0) k0 += M1;\r\n    k0      = u64(k0) * M0_inv_M1_\
    \ % M1;\r\n    u64 d   = a + u64(k0) * M0;\r\n    u32 k01 = c - d % M2;\r\n  \
    \  if (int(k01) < 0) k01 += M2;\r\n    // NTT \u6A21\u6570\u90FD\u5C0F\u4E8E (1U\
    \ << 31) \u6240\u4EE5\u5728\u8FD9\u91CC\u53EF\u4EE5\u4F7F\u7528\u52A0\u6CD5\u540E\
    \u518D\u53D6\u6A21\r\n    return (d + u64(k01) * M0M1_inv_M2_ % M2 * M0M1_mod_m_)\
    \ % m_;\r\n  }\r\n\r\n  static constexpr u32 get_inv(u32 x, u32 mod) {\r\n   \
    \ u32 res = 1;\r\n    for (u32 e = mod - 2; e != 0; e >>= 1) {\r\n      if (e\
    \ & 1) res = u64(res) * x % mod;\r\n      x = u64(x) * x % mod;\r\n    }\r\n \
    \   return res;\r\n  }\r\n\r\nprivate:\r\n  u32 m_, M0M1_mod_m_;\r\n  static constexpr\
    \ u32 M0_inv_M1_   = get_inv(M0, M1);\r\n  static constexpr u32 M0M1_inv_M2_ =\
    \ get_inv(u64(M0) * M1 % M2, M2);\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef NTT_CRT_HEADER_HPP\r\n#define NTT_CRT_HEADER_HPP\r\n\r\n/**\r\n *\
    \ @brief NTT prime crt / NTT \u7D20\u6570\u7528\u4E2D\u56FD\u5269\u4F59\u5B9A\u7406\
    \r\n *\r\n */\r\n\r\n#include <cstdint>\r\n#include <type_traits>\r\n\r\nnamespace\
    \ lib {\r\n\r\ntemplate <std::uint32_t M0, std::uint32_t M1, std::uint32_t M2,\r\
    \n          std::enable_if_t<(M0 < M1) && ((M0 | M1 | M2) < (1U << 31)) &&\r\n\
    \                               ((M0 & M1 & M2 & 1) == 1) && (M0 != M1) && (M0\
    \ != M2) && (M1 != M2),\r\n                           int> = 0>\r\nclass NTTCRT3\
    \ {\r\npublic:\r\n  using u32 = std::uint32_t;\r\n  using u64 = std::uint64_t;\r\
    \n\r\n  constexpr NTTCRT3(u32 mod) : m_(mod), M0M1_mod_m_(u64(M0) * M1 % mod)\
    \ {}\r\n  ~NTTCRT3() = default;\r\n\r\n  constexpr u32 operator()(u32 a, u32 b,\
    \ u32 c) const {\r\n    // x mod M0 = a, x mod M1 = b, x mod M2 = c\r\n    //\
    \ a + k0M0 = b + k1M1 => k0 = (b - a) / M0 (mod M1)\r\n    // x = a + k0M0 (mod\
    \ M0M1) => a + k0M0 + k01M0M1 = c + k2M2\r\n    // => k01 = (c - (a + k0M0)) /\
    \ (M0M1) (mod M2)\r\n    // => x mod M0M1M2 = a + k0M0 + k01M0M1\r\n    u32 k0\
    \ = b - a;\r\n    if (int(k0) < 0) k0 += M1;\r\n    k0      = u64(k0) * M0_inv_M1_\
    \ % M1;\r\n    u64 d   = a + u64(k0) * M0;\r\n    u32 k01 = c - d % M2;\r\n  \
    \  if (int(k01) < 0) k01 += M2;\r\n    // NTT \u6A21\u6570\u90FD\u5C0F\u4E8E (1U\
    \ << 31) \u6240\u4EE5\u5728\u8FD9\u91CC\u53EF\u4EE5\u4F7F\u7528\u52A0\u6CD5\u540E\
    \u518D\u53D6\u6A21\r\n    return (d + u64(k01) * M0M1_inv_M2_ % M2 * M0M1_mod_m_)\
    \ % m_;\r\n  }\r\n\r\n  static constexpr u32 get_inv(u32 x, u32 mod) {\r\n   \
    \ u32 res = 1;\r\n    for (u32 e = mod - 2; e != 0; e >>= 1) {\r\n      if (e\
    \ & 1) res = u64(res) * x % mod;\r\n      x = u64(x) * x % mod;\r\n    }\r\n \
    \   return res;\r\n  }\r\n\r\nprivate:\r\n  u32 m_, M0M1_mod_m_;\r\n  static constexpr\
    \ u32 M0_inv_M1_   = get_inv(M0, M1);\r\n  static constexpr u32 M0M1_inv_M2_ =\
    \ get_inv(u64(M0) * M1 % M2, M2);\r\n};\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/formal_power_series/NTT_crt.hpp
  requiredBy:
  - math/formal_power_series/arbitrary_modulo_convolution.hpp
  timestamp: '2021-07-16 15:42:02+08:00'
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
