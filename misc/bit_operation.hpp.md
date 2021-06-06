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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ misc/bit_operation.hpp: line 12: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "/**\n * @brief bit operations / \u4F4D\u8FD0\u7B97\n *\n */\n\n#ifndef BIT_OPERATION_HEADER_HPP\n\
    #define BIT_OPERATION_HEADER_HPP\n\n#include <cassert>\n#include <cstdint>\n\n\
    #include \"deBruijn_sequence.hpp\"\n\nnamespace lib {\n\n/**\n * @brief \u5728\
    \u4E8C\u8FDB\u5236\u6700\u9AD8\u7684 1 \u540E\u9762\u586B\u5145\u6EE1 1\n *\n\
    \ * @param x\n * @return std::uint32_t\n */\nstd::uint32_t fill_one_after_msb(std::uint32_t\
    \ x) {\n  x |= x >> 1;\n  x |= x >> 2;\n  x |= x >> 4;\n  x |= x >> 8;\n  return\
    \ x | x >> 16;\n}\n\nstd::uint64_t fill_one_after_msb(std::uint64_t x) {\n  x\
    \ |= x >> 1;\n  x |= x >> 2;\n  x |= x >> 4;\n  x |= x >> 8;\n  x |= x >> 16;\n\
    \  return x | x >> 32;\n}\n\n/**\n * @brief \u8BA1\u7B97 `x` \u7684\u4E8C\u8FDB\
    \u5236\u8868\u793A\u4E2D least significant 1-bit \u7684\u7D22\u5F15\u52A0\u4E00\
    \uFF0C\u82E5 `x == 0` \u5219\u8FD4\u56DE `0`\n *\n * @param x\n * @return int\n\
    \ */\nint ffs(std::uint32_t x) { return x == 0 ? 0 : deBruijn_log2(x & ~(x - 1))\
    \ + 1; }\n\nint ffs(std::uint64_t x) { return x == 0 ? 0 : deBruijn_log2(x & ~(x\
    \ - 1)) + 1; }\n\n/**\n * @brief \u8BA1\u7B97 `x` \u7684\u4E8C\u8FDB\u5236\u8868\
    \u793A\u4E2D\u4ECE most significant bit \u4F4D\u7F6E\u5F00\u59CB\u6709\u591A\u5C11\
    \u4E2A `0` \uFF0C\u82E5 `x == 0`\n * \u5219\u672A\u5B9A\u4E49\u3002\n *\n * @param\
    \ x\n * @return int\n */\nint clz(std::uint32_t x) {\n  assert(x != 0);\n  return\
    \ 31 - deBruijn_log2(fill_one_after_msb(x >> 1) + 1);\n}\n\nint clz(std::uint64_t\
    \ x) {\n  assert(x != 0);\n  return 63 - deBruijn_log2(fill_one_after_msb(x >>\
    \ 1) + 1);\n}\n\n/**\n * @brief \u8BA1\u7B97 `x` \u7684\u4E8C\u8FDB\u5236\u8868\
    \u793A\u4E2D\u4ECE least significant bit \u4F4D\u7F6E\u5F00\u59CB\u6709\u591A\u5C11\
    \u4E2A `0` \uFF0C\u82E5 `x == 0`\n * \u5219\u672A\u5B9A\u4E49\u3002\n *\n * @param\
    \ x\n * @return int\n */\nint ctz(std::uint32_t x) {\n  assert(x != 0);\n  return\
    \ deBruijn_log2(x & ~(x - 1));\n}\n\nint ctz(std::uint64_t x) {\n  assert(x !=\
    \ 0);\n  return deBruijn_log2(x & ~(x - 1));\n}\n\n/**\n * @brief \u8BA1\u7B97\
    \ `x` \u7684\u4E8C\u8FDB\u5236\u8868\u793A\u4E2D `1` \u7684\u4E2A\u6570\u3002\n\
    \ *\n * @param x\n * @return int\n */\nint popcount(std::uint32_t x) {\n  int\
    \ cnt = 0;\n  while (x) ++cnt, x &= x - 1;\n  return cnt;\n}\n\nint popcount(std::uint64_t\
    \ x) {\n  int cnt = 0;\n  while (x) ++cnt, x &= x - 1;\n  return cnt;\n}\n\n}\
    \ // namespace lib\n\n#endif"
  dependsOn:
  - misc/deBruijn_sequence.hpp
  isVerificationFile: false
  path: misc/bit_operation.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: misc/bit_operation.hpp
layout: document
redirect_from:
- /library/misc/bit_operation.hpp
- /library/misc/bit_operation.hpp.html
title: "bit operations / \u4F4D\u8FD0\u7B97"
---
