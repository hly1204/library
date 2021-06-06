---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: misc/bit_operation.hpp
    title: "bit operations / \u4F4D\u8FD0\u7B97"
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "de Bruijn sequence / de Bruijn \u5E8F\u5217"
    links: []
  bundledCode: "#line 1 \"misc/deBruijn_sequence.hpp\"\n/**\n * @brief de Bruijn sequence\
    \ / de Bruijn \u5E8F\u5217\n *\n */\n\n#ifndef DEBRUIJN_HEADER_HPP\n#define DEBRUIJN_HEADER_HPP\n\
    \n#include <cstdint>\n\nnamespace lib {\n\nint deBruijn_log2(std::uint64_t n)\
    \ {\n  static constexpr std::uint64_t deBruijn = 0x022fdd63cc95386d;\n  static\
    \ constexpr int convert[64] = {\n      0,  1,  2,  53, 3,  7,  54, 27, 4,  38,\
    \ 41, 8,  34, 55, 48, 28, 62, 5,  39, 46, 44, 42,\n      22, 9,  24, 35, 59, 56,\
    \ 49, 18, 29, 11, 63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21,\n      23, 58,\
    \ 17, 10, 51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12};\n \
    \ return convert[n * deBruijn >> 58];\n}\n\nint deBruijn_log2(std::uint32_t n)\
    \ {\n  static constexpr std::uint32_t deBruijn = 0x4653adf;\n  static constexpr\
    \ int convert[32] = {0,  1,  2,  6,  3,  11, 7,  16, 4,  14, 12,\n           \
    \                           21, 8,  23, 17, 26, 31, 5,  10, 15, 13, 20,\n    \
    \                                  22, 25, 30, 9,  19, 24, 29, 18, 28, 27};\n\
    \  return convert[n * deBruijn >> 27];\n}\n\n} // namespace lib\n\n#endif\n"
  code: "/**\n * @brief de Bruijn sequence / de Bruijn \u5E8F\u5217\n *\n */\n\n#ifndef\
    \ DEBRUIJN_HEADER_HPP\n#define DEBRUIJN_HEADER_HPP\n\n#include <cstdint>\n\nnamespace\
    \ lib {\n\nint deBruijn_log2(std::uint64_t n) {\n  static constexpr std::uint64_t\
    \ deBruijn = 0x022fdd63cc95386d;\n  static constexpr int convert[64] = {\n   \
    \   0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28, 62, 5,  39,\
    \ 46, 44, 42,\n      22, 9,  24, 35, 59, 56, 49, 18, 29, 11, 63, 52, 6,  26, 37,\
    \ 40, 33, 47, 61, 45, 43, 21,\n      23, 58, 17, 10, 51, 25, 36, 32, 60, 20, 57,\
    \ 16, 50, 31, 19, 15, 30, 14, 13, 12};\n  return convert[n * deBruijn >> 58];\n\
    }\n\nint deBruijn_log2(std::uint32_t n) {\n  static constexpr std::uint32_t deBruijn\
    \ = 0x4653adf;\n  static constexpr int convert[32] = {0,  1,  2,  6,  3,  11,\
    \ 7,  16, 4,  14, 12,\n                                      21, 8,  23, 17, 26,\
    \ 31, 5,  10, 15, 13, 20,\n                                      22, 25, 30, 9,\
    \  19, 24, 29, 18, 28, 27};\n  return convert[n * deBruijn >> 27];\n}\n\n} //\
    \ namespace lib\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: misc/deBruijn_sequence.hpp
  requiredBy:
  - misc/bit_operation.hpp
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: misc/deBruijn_sequence.hpp
layout: document
redirect_from:
- /library/misc/deBruijn_sequence.hpp
- /library/misc/deBruijn_sequence.hpp.html
title: "de Bruijn sequence / de Bruijn \u5E8F\u5217"
---
