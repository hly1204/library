---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: misc/deBruijn_sequence.hpp
    title: misc/deBruijn_sequence.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"misc/bit_operation.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n\n#line 1 \"misc/deBruijn_sequence.hpp\"\n\n\n\n#line 5 \"misc/deBruijn_sequence.hpp\"\
    \n\nnamespace lib {\n\nint deBruijn_log2(std::uint64_t n) {\n  static constexpr\
    \ std::uint64_t deBruijn = 0x022fdd63cc95386d;\n  static constexpr int convert[64]\
    \ = {\n      0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28, 62,\
    \ 5,  39, 46, 44, 42,\n      22, 9,  24, 35, 59, 56, 49, 18, 29, 11, 63, 52, 6,\
    \  26, 37, 40, 33, 47, 61, 45, 43, 21,\n      23, 58, 17, 10, 51, 25, 36, 32,\
    \ 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12};\n  return convert[n * deBruijn\
    \ >> 58];\n}\n\nint deBruijn_log2(std::uint32_t n) {\n  static constexpr std::uint32_t\
    \ deBruijn = 0x4653adf;\n  static constexpr int convert[32] = {0,  1,  2,  6,\
    \  3,  11, 7,  16, 4,  14, 12,\n                                      21, 8, \
    \ 23, 17, 26, 31, 5,  10, 15, 13, 20,\n                                      22,\
    \ 25, 30, 9,  19, 24, 29, 18, 28, 27};\n  return convert[n * deBruijn >> 27];\n\
    }\n\n} // namespace lib\n\n\n#line 8 \"misc/bit_operation.hpp\"\n\nnamespace lib\
    \ {\n\nstd::uint32_t fill_one_after_msb(std::uint32_t x) {\n  x |= x >> 1;\n \
    \ x |= x >> 2;\n  x |= x >> 4;\n  x |= x >> 8;\n  return x | x >> 16;\n}\n\nstd::uint64_t\
    \ fill_one_after_msb(std::uint64_t x) {\n  x |= x >> 1;\n  x |= x >> 2;\n  x |=\
    \ x >> 4;\n  x |= x >> 8;\n  x |= x >> 16;\n  return x | x >> 32;\n}\n\nint ffs(std::uint32_t\
    \ x) { return x == 0 ? 0 : deBruijn_log2(x & ~(x - 1)) + 1; }\n\nint ffs(std::uint64_t\
    \ x) { return x == 0 ? 0 : deBruijn_log2(x & ~(x - 1)) + 1; }\n\nint clz(std::uint32_t\
    \ x) {\n  assert(x != 0);\n  return 31 - deBruijn_log2(fill_one_after_msb(x >>\
    \ 1) + 1);\n}\n\nint clz(std::uint64_t x) {\n  assert(x != 0);\n  return 63 -\
    \ deBruijn_log2(fill_one_after_msb(x >> 1) + 1);\n}\n\nint ctz(std::uint32_t x)\
    \ {\n  assert(x != 0);\n  return deBruijn_log2(x & ~(x - 1));\n}\n\nint ctz(std::uint64_t\
    \ x) {\n  assert(x != 0);\n  return deBruijn_log2(x & ~(x - 1));\n}\n\nint popcount(std::uint32_t\
    \ x) {\n  int cnt = 0;\n  while (x) ++cnt, x &= x - 1;\n  return cnt;\n}\n\nint\
    \ popcount(std::uint64_t x) {\n  int cnt = 0;\n  while (x) ++cnt, x &= x - 1;\n\
    \  return cnt;\n}\n\n} // namespace lib\n\n\n"
  code: "#ifndef BIT_OPERATION_HEADER_HPP\n#define BIT_OPERATION_HEADER_HPP\n\n#include\
    \ <cassert>\n#include <cstdint>\n\n#include \"deBruijn_sequence.hpp\"\n\nnamespace\
    \ lib {\n\nstd::uint32_t fill_one_after_msb(std::uint32_t x) {\n  x |= x >> 1;\n\
    \  x |= x >> 2;\n  x |= x >> 4;\n  x |= x >> 8;\n  return x | x >> 16;\n}\n\n\
    std::uint64_t fill_one_after_msb(std::uint64_t x) {\n  x |= x >> 1;\n  x |= x\
    \ >> 2;\n  x |= x >> 4;\n  x |= x >> 8;\n  x |= x >> 16;\n  return x | x >> 32;\n\
    }\n\nint ffs(std::uint32_t x) { return x == 0 ? 0 : deBruijn_log2(x & ~(x - 1))\
    \ + 1; }\n\nint ffs(std::uint64_t x) { return x == 0 ? 0 : deBruijn_log2(x & ~(x\
    \ - 1)) + 1; }\n\nint clz(std::uint32_t x) {\n  assert(x != 0);\n  return 31 -\
    \ deBruijn_log2(fill_one_after_msb(x >> 1) + 1);\n}\n\nint clz(std::uint64_t x)\
    \ {\n  assert(x != 0);\n  return 63 - deBruijn_log2(fill_one_after_msb(x >> 1)\
    \ + 1);\n}\n\nint ctz(std::uint32_t x) {\n  assert(x != 0);\n  return deBruijn_log2(x\
    \ & ~(x - 1));\n}\n\nint ctz(std::uint64_t x) {\n  assert(x != 0);\n  return deBruijn_log2(x\
    \ & ~(x - 1));\n}\n\nint popcount(std::uint32_t x) {\n  int cnt = 0;\n  while\
    \ (x) ++cnt, x &= x - 1;\n  return cnt;\n}\n\nint popcount(std::uint64_t x) {\n\
    \  int cnt = 0;\n  while (x) ++cnt, x &= x - 1;\n  return cnt;\n}\n\n} // namespace\
    \ lib\n\n#endif\n"
  dependsOn:
  - misc/deBruijn_sequence.hpp
  isVerificationFile: false
  path: misc/bit_operation.hpp
  requiredBy: []
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: misc/bit_operation.hpp
layout: document
title: "\u4F4D\u8FD0\u7B97"
---

## 位运算

使用 de Bruijn 序列实现了一些基本的位运算操作如下：

- `ffs(x)` 计算 `x` 的二进制表示中 least significant 1-bit 的索引加一，若 `x == 0` 则返回 `0` 。
- `clz(x)` 计算 `x` 的二进制表示中从 most significant bit 位置开始有多少个 `0` ，若 `x == 0` 则未定义。
- `ctz(x)` 计算 `x` 的二进制表示中从 least significant bit 位置开始有多少个 `0` ，若 `x == 0` 则未定义。
- `popcount(x)` 计算 `x` 的二进制表示中 `1` 的个数。

注意：这里的 most significant bit 为二进制表示中最高位，而 least significant bit 为二进制表示中最低位。且函数的参数只有 `std::uint32_t` 和 `std::uint64_t` 两种类型，返回值统一为 `int` 类型。这里的算法不应该被其他文件依赖，因为只是相当粗糙的实现。

