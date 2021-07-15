---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/datastructure/staticrmq.0.test.cpp
    title: remote_test/yosupo/datastructure/staticrmq.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "sparse table / \u7A00\u758F\u8868"
    links: []
  bundledCode: "#line 1 \"datastructure/basic/sparse_table.hpp\"\n\n\n\r\n/**\r\n\
    \ * @brief sparse table / \u7A00\u758F\u8868\r\n *\r\n */\r\n\r\n#include <algorithm>\r\
    \n#include <cassert>\r\n#include <cstdint>\r\n#include <functional>\r\n#include\
    \ <vector>\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename Type, typename FoldFunc>\r\
    \nclass SparseTable {\r\npublic:\r\n  static std::uint32_t log2_floor(std::uint32_t\
    \ n) {\r\n    n >>= 1, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8, n |=\
    \ n >> 16, ++n;\r\n    static constexpr std::uint32_t deBruijn    = 0x4653adf;\r\
    \n    static constexpr std::uint32_t convert[32] = {0,  1,  2,  6,  3,  11, 7,\
    \  16, 4,  14, 12,\r\n                                                  21, 8,\
    \  23, 17, 26, 31, 5,  10, 15, 13, 20,\r\n                                   \
    \               22, 25, 30, 9,  19, 24, 29, 18, 28, 27};\r\n    return convert[n\
    \ * deBruijn >> 27];\r\n  }\r\n  template <typename Container>\r\n  SparseTable(const\
    \ Container &init_v, const FoldFunc &f = FoldFunc()) : N_(init_v.size()), f_(f)\
    \ {\r\n    int level = log2_floor(N_);\r\n    table_.resize(level + 1);\r\n  \
    \  table_[0].resize(N_);\r\n    std::copy_n(init_v.begin(), N_, table_[0].begin());\r\
    \n    for (int i = 0; i < level; ++i) {\r\n      int s                       =\
    \ N_ + 1 - (1 << (i + 1));\r\n      const std::vector<Type> &ti = table_[i];\r\
    \n      std::vector<Type> &ti1      = table_[i + 1];\r\n      ti1.resize(s);\r\
    \n      for (int j = 0, offset = 1 << i; j < s; ++j) ti1[j] = f_(ti[j], ti[j +\
    \ offset]);\r\n    }\r\n  }\r\n  ~SparseTable() = default;\r\n\r\n  Type fold(int\
    \ l, int r) const { // [l,r]\r\n    assert(l <= r);\r\n    int level = log2_floor(r\
    \ + 1 - l);\r\n    return f_(table_[level][l], table_[level][r + 1 - (1 << level)]);\r\
    \n  }\r\n\r\nprivate:\r\n  const int N_;\r\n  FoldFunc f_;\r\n  std::vector<std::vector<Type>>\
    \ table_;\r\n};\r\n\r\ntemplate <typename Type, typename Comp = std::less<>>\r\
    \nSparseTable<Type, std::function<Type(const Type &, const Type &)>>\r\nmake_rmq_sparse_table(const\
    \ std::vector<Type> &init_v, Comp cmp = Comp()) {\r\n  return SparseTable<Type,\
    \ std::function<Type(const Type &, const Type &)>>(\r\n      init_v, [&cmp](const\
    \ Type &x, const Type &y) { return cmp(x, y) ? x : y; });\r\n}\r\n\r\n} // namespace\
    \ lib\r\n\r\n\n"
  code: "#ifndef SPARSE_TABLE_HEADER_HPP\r\n#define SPARSE_TABLE_HEADER_HPP\r\n\r\n\
    /**\r\n * @brief sparse table / \u7A00\u758F\u8868\r\n *\r\n */\r\n\r\n#include\
    \ <algorithm>\r\n#include <cassert>\r\n#include <cstdint>\r\n#include <functional>\r\
    \n#include <vector>\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename Type, typename\
    \ FoldFunc>\r\nclass SparseTable {\r\npublic:\r\n  static std::uint32_t log2_floor(std::uint32_t\
    \ n) {\r\n    n >>= 1, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8, n |=\
    \ n >> 16, ++n;\r\n    static constexpr std::uint32_t deBruijn    = 0x4653adf;\r\
    \n    static constexpr std::uint32_t convert[32] = {0,  1,  2,  6,  3,  11, 7,\
    \  16, 4,  14, 12,\r\n                                                  21, 8,\
    \  23, 17, 26, 31, 5,  10, 15, 13, 20,\r\n                                   \
    \               22, 25, 30, 9,  19, 24, 29, 18, 28, 27};\r\n    return convert[n\
    \ * deBruijn >> 27];\r\n  }\r\n  template <typename Container>\r\n  SparseTable(const\
    \ Container &init_v, const FoldFunc &f = FoldFunc()) : N_(init_v.size()), f_(f)\
    \ {\r\n    int level = log2_floor(N_);\r\n    table_.resize(level + 1);\r\n  \
    \  table_[0].resize(N_);\r\n    std::copy_n(init_v.begin(), N_, table_[0].begin());\r\
    \n    for (int i = 0; i < level; ++i) {\r\n      int s                       =\
    \ N_ + 1 - (1 << (i + 1));\r\n      const std::vector<Type> &ti = table_[i];\r\
    \n      std::vector<Type> &ti1      = table_[i + 1];\r\n      ti1.resize(s);\r\
    \n      for (int j = 0, offset = 1 << i; j < s; ++j) ti1[j] = f_(ti[j], ti[j +\
    \ offset]);\r\n    }\r\n  }\r\n  ~SparseTable() = default;\r\n\r\n  Type fold(int\
    \ l, int r) const { // [l,r]\r\n    assert(l <= r);\r\n    int level = log2_floor(r\
    \ + 1 - l);\r\n    return f_(table_[level][l], table_[level][r + 1 - (1 << level)]);\r\
    \n  }\r\n\r\nprivate:\r\n  const int N_;\r\n  FoldFunc f_;\r\n  std::vector<std::vector<Type>>\
    \ table_;\r\n};\r\n\r\ntemplate <typename Type, typename Comp = std::less<>>\r\
    \nSparseTable<Type, std::function<Type(const Type &, const Type &)>>\r\nmake_rmq_sparse_table(const\
    \ std::vector<Type> &init_v, Comp cmp = Comp()) {\r\n  return SparseTable<Type,\
    \ std::function<Type(const Type &, const Type &)>>(\r\n      init_v, [&cmp](const\
    \ Type &x, const Type &y) { return cmp(x, y) ? x : y; });\r\n}\r\n\r\n} // namespace\
    \ lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/basic/sparse_table.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/datastructure/staticrmq.0.test.cpp
documentation_of: datastructure/basic/sparse_table.hpp
layout: document
redirect_from:
- /library/datastructure/basic/sparse_table.hpp
- /library/datastructure/basic/sparse_table.hpp.html
title: "sparse table / \u7A00\u758F\u8868"
---
