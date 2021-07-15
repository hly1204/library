---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: misc/deBruijn_sequence.hpp
    title: "de Bruijn sequence / de Bruijn \u5E8F\u5217"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "bit operations / \u4F4D\u8FD0\u7B97"
    links: []
  bundledCode: "#line 1 \"misc/bit_operation.hpp\"\n\n\n\r\n/**\r\n * @brief bit operations\
    \ / \u4F4D\u8FD0\u7B97\r\n *\r\n */\r\n\r\n#include <cassert>\r\n#include <cstdint>\r\
    \n\r\n#line 1 \"misc/deBruijn_sequence.hpp\"\n\n\n\r\n/**\r\n * @brief de Bruijn\
    \ sequence / de Bruijn \u5E8F\u5217\r\n *\r\n */\r\n\r\n#line 10 \"misc/deBruijn_sequence.hpp\"\
    \n\r\nnamespace lib {\r\n\r\nint deBruijn_log2(std::uint64_t n) {\r\n  static\
    \ constexpr std::uint64_t deBruijn = 0x022fdd63cc95386d;\r\n  static constexpr\
    \ int convert[64]        = {\r\n      0,  1,  2,  53, 3,  7,  54, 27, 4,  38,\
    \ 41, 8,  34, 55, 48, 28, 62, 5,  39, 46, 44, 42,\r\n      22, 9,  24, 35, 59,\
    \ 56, 49, 18, 29, 11, 63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21,\r\n    \
    \  23, 58, 17, 10, 51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13,\
    \ 12};\r\n  return convert[n * deBruijn >> 58];\r\n}\r\n\r\nint deBruijn_log2(std::uint32_t\
    \ n) {\r\n  static constexpr std::uint32_t deBruijn = 0x4653adf;\r\n  static constexpr\
    \ int convert[32]        = {0,  1,  2,  6,  3,  11, 7,  16, 4,  14, 12,\r\n  \
    \                                    21, 8,  23, 17, 26, 31, 5,  10, 15, 13, 20,\r\
    \n                                      22, 25, 30, 9,  19, 24, 29, 18, 28, 27};\r\
    \n  return convert[n * deBruijn >> 27];\r\n}\r\n\r\n} // namespace lib\r\n\r\n\
    \n#line 13 \"misc/bit_operation.hpp\"\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief\
    \ \u5728\u4E8C\u8FDB\u5236\u6700\u9AD8\u7684 1 \u540E\u9762\u586B\u5145\u6EE1\
    \ 1\r\n * @param x\r\n * @return std::uint32_t\r\n */\r\nstd::uint32_t fill_one_after_msb(std::uint32_t\
    \ x) {\r\n  x |= x >> 1;\r\n  x |= x >> 2;\r\n  x |= x >> 4;\r\n  x |= x >> 8;\r\
    \n  return x | x >> 16;\r\n}\r\n\r\nstd::uint64_t fill_one_after_msb(std::uint64_t\
    \ x) {\r\n  x |= x >> 1;\r\n  x |= x >> 2;\r\n  x |= x >> 4;\r\n  x |= x >> 8;\r\
    \n  x |= x >> 16;\r\n  return x | x >> 32;\r\n}\r\n\r\n/**\r\n * @brief \u8BA1\
    \u7B97 x \u7684\u4E8C\u8FDB\u5236\u8868\u793A\u4E2D least significant 1-bit \u7684\
    \u7D22\u5F15\u52A0\u4E00\r\n * @param x\r\n * @return int \u82E5 x=0 \u5219\u8FD4\
    \u56DE 0 \u3002\r\n */\r\nint ffs(std::uint32_t x) { return x == 0 ? 0 : deBruijn_log2(x\
    \ & ~(x - 1)) + 1; }\r\n\r\nint ffs(std::uint64_t x) { return x == 0 ? 0 : deBruijn_log2(x\
    \ & ~(x - 1)) + 1; }\r\n\r\n/**\r\n * @brief \u8BA1\u7B97 x \u7684\u4E8C\u8FDB\
    \u5236\u8868\u793A\u4E2D\u4ECE most significant bit \u4F4D\u7F6E\u5F00\u59CB\u6709\
    \u591A\u5C11\u4E2A 0\r\n * @param x\r\n * @return int \u82E5 x=0 \u5219\u672A\u5B9A\
    \u4E49\u3002\r\n *\r\n */\r\nint clz(std::uint32_t x) {\r\n  assert(x != 0);\r\
    \n  return 31 - deBruijn_log2(fill_one_after_msb(x >> 1) + 1);\r\n}\r\n\r\nint\
    \ clz(std::uint64_t x) {\r\n  assert(x != 0);\r\n  return 63 - deBruijn_log2(fill_one_after_msb(x\
    \ >> 1) + 1);\r\n}\r\n\r\n/**\r\n * @brief \u8BA1\u7B97 x \u7684\u4E8C\u8FDB\u5236\
    \u8868\u793A\u4E2D\u4ECE least significant bit \u4F4D\u7F6E\u5F00\u59CB\u6709\u591A\
    \u5C11\u4E2A 0\r\n * @param x\r\n * @return int \u82E5 x=0 \u5219\u8FD4\u56DE\u672A\
    \u5B9A\u4E49\r\n */\r\nint ctz(std::uint32_t x) {\r\n  assert(x != 0);\r\n  return\
    \ deBruijn_log2(x & ~(x - 1));\r\n}\r\n\r\nint ctz(std::uint64_t x) {\r\n  assert(x\
    \ != 0);\r\n  return deBruijn_log2(x & ~(x - 1));\r\n}\r\n\r\n/**\r\n * @brief\
    \ \u8BA1\u7B97 x \u7684\u4E8C\u8FDB\u5236\u8868\u793A\u4E2D 1 \u7684\u4E2A\u6570\
    \r\n * @param x\r\n * @return int\r\n */\r\nint popcount(std::uint32_t x) {\r\n\
    \  int cnt = 0;\r\n  while (x) ++cnt, x &= x - 1;\r\n  return cnt;\r\n}\r\n\r\n\
    int popcount(std::uint64_t x) {\r\n  int cnt = 0;\r\n  while (x) ++cnt, x &= x\
    \ - 1;\r\n  return cnt;\r\n}\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef BIT_OPERATION_HEADER_HPP\r\n#define BIT_OPERATION_HEADER_HPP\r\n\r\
    \n/**\r\n * @brief bit operations / \u4F4D\u8FD0\u7B97\r\n *\r\n */\r\n\r\n#include\
    \ <cassert>\r\n#include <cstdint>\r\n\r\n#include \"deBruijn_sequence.hpp\"\r\n\
    \r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u5728\u4E8C\u8FDB\u5236\u6700\u9AD8\
    \u7684 1 \u540E\u9762\u586B\u5145\u6EE1 1\r\n * @param x\r\n * @return std::uint32_t\r\
    \n */\r\nstd::uint32_t fill_one_after_msb(std::uint32_t x) {\r\n  x |= x >> 1;\r\
    \n  x |= x >> 2;\r\n  x |= x >> 4;\r\n  x |= x >> 8;\r\n  return x | x >> 16;\r\
    \n}\r\n\r\nstd::uint64_t fill_one_after_msb(std::uint64_t x) {\r\n  x |= x >>\
    \ 1;\r\n  x |= x >> 2;\r\n  x |= x >> 4;\r\n  x |= x >> 8;\r\n  x |= x >> 16;\r\
    \n  return x | x >> 32;\r\n}\r\n\r\n/**\r\n * @brief \u8BA1\u7B97 x \u7684\u4E8C\
    \u8FDB\u5236\u8868\u793A\u4E2D least significant 1-bit \u7684\u7D22\u5F15\u52A0\
    \u4E00\r\n * @param x\r\n * @return int \u82E5 x=0 \u5219\u8FD4\u56DE 0 \u3002\
    \r\n */\r\nint ffs(std::uint32_t x) { return x == 0 ? 0 : deBruijn_log2(x & ~(x\
    \ - 1)) + 1; }\r\n\r\nint ffs(std::uint64_t x) { return x == 0 ? 0 : deBruijn_log2(x\
    \ & ~(x - 1)) + 1; }\r\n\r\n/**\r\n * @brief \u8BA1\u7B97 x \u7684\u4E8C\u8FDB\
    \u5236\u8868\u793A\u4E2D\u4ECE most significant bit \u4F4D\u7F6E\u5F00\u59CB\u6709\
    \u591A\u5C11\u4E2A 0\r\n * @param x\r\n * @return int \u82E5 x=0 \u5219\u672A\u5B9A\
    \u4E49\u3002\r\n *\r\n */\r\nint clz(std::uint32_t x) {\r\n  assert(x != 0);\r\
    \n  return 31 - deBruijn_log2(fill_one_after_msb(x >> 1) + 1);\r\n}\r\n\r\nint\
    \ clz(std::uint64_t x) {\r\n  assert(x != 0);\r\n  return 63 - deBruijn_log2(fill_one_after_msb(x\
    \ >> 1) + 1);\r\n}\r\n\r\n/**\r\n * @brief \u8BA1\u7B97 x \u7684\u4E8C\u8FDB\u5236\
    \u8868\u793A\u4E2D\u4ECE least significant bit \u4F4D\u7F6E\u5F00\u59CB\u6709\u591A\
    \u5C11\u4E2A 0\r\n * @param x\r\n * @return int \u82E5 x=0 \u5219\u8FD4\u56DE\u672A\
    \u5B9A\u4E49\r\n */\r\nint ctz(std::uint32_t x) {\r\n  assert(x != 0);\r\n  return\
    \ deBruijn_log2(x & ~(x - 1));\r\n}\r\n\r\nint ctz(std::uint64_t x) {\r\n  assert(x\
    \ != 0);\r\n  return deBruijn_log2(x & ~(x - 1));\r\n}\r\n\r\n/**\r\n * @brief\
    \ \u8BA1\u7B97 x \u7684\u4E8C\u8FDB\u5236\u8868\u793A\u4E2D 1 \u7684\u4E2A\u6570\
    \r\n * @param x\r\n * @return int\r\n */\r\nint popcount(std::uint32_t x) {\r\n\
    \  int cnt = 0;\r\n  while (x) ++cnt, x &= x - 1;\r\n  return cnt;\r\n}\r\n\r\n\
    int popcount(std::uint64_t x) {\r\n  int cnt = 0;\r\n  while (x) ++cnt, x &= x\
    \ - 1;\r\n  return cnt;\r\n}\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn:
  - misc/deBruijn_sequence.hpp
  isVerificationFile: false
  path: misc/bit_operation.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: misc/bit_operation.hpp
layout: document
redirect_from:
- /library/misc/bit_operation.hpp
- /library/misc/bit_operation.hpp.html
title: "bit operations / \u4F4D\u8FD0\u7B97"
---
