---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/matrix/sparse_square_matrix.hpp
    title: "sparse square matrix / \u7A00\u758F\u65B9\u9635"
  _extendedVerifiedWith:
  - icon: ':x:'
    path: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
    title: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "sparse matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B"
    links: []
  bundledCode: "#line 1 \"math/matrix/sparse_matrix_base.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief sparse matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B\r\n *\r\n */\r\
    \n\r\n#include <cassert>\r\n#include <utility>\r\n#include <vector>\r\n\r\nnamespace\
    \ lib {\r\n\r\ntemplate <typename Type>\r\nclass SparseMatrix {\r\npublic:\r\n\
    \  using value_type = Type;\r\n\r\n  SparseMatrix(int r, int c, const Type &v\
    \ = Type()) : row_(r), col_(c), default_val_(v), mat_(r) {}\r\n  virtual ~SparseMatrix()\
    \            = default;\r\n  SparseMatrix(const SparseMatrix &) = default;\r\n\
    \r\n  virtual SparseMatrix &operator=(const SparseMatrix &) = default;\r\n\r\n\
    \  int row() const { return row_; }\r\n  int col() const { return col_; }\r\n\
    \  int size() const { return row_ * col_; }\r\n  bool is_empty() const { return\
    \ size() == 0; }\r\n\r\n  Type &at(int r, int c) {\r\n    for (auto &[pos, v]\
    \ : mat_[r])\r\n      if (pos == c) return v;\r\n    return mat_[r].emplace_back(c,\
    \ default_val_).second;\r\n  }\r\n  Type at(int r, int c) const {\r\n    for (auto\
    \ &[pos, v] : mat_[r])\r\n      if (pos == c) return v;\r\n    return default_val_;\r\
    \n  }\r\n\r\n  virtual std::vector<Type> apply(const std::vector<Type> &x) const\
    \ {\r\n    int r = row(), c = col();\r\n    assert(c == x.size());\r\n    assert(default_val_\
    \ == Type(0)); // \u82E5\u9ED8\u8BA4\u503C\u4E0D\u4E3A\u96F6\u5219\u9700\u8981\
    \u4FEE\u6539\u6B64\u51FD\u6570\r\n    std::vector<Type> res(r, Type(0));\r\n \
    \   for (int i = 0; i < r; ++i) {\r\n      for (auto &[pos, v] : mat_[i]) res[i]\
    \ += v * x[pos];\r\n    }\r\n    return res;\r\n  }\r\n\r\nprotected:\r\n  int\
    \ row_, col_;\r\n  const Type default_val_;\r\n  std::vector<std::vector<std::pair<int,\
    \ Type>>> mat_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef SPARSE_MATRIX_BASE_HEADER_HPP\r\n#define SPARSE_MATRIX_BASE_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief sparse matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B\
    \r\n *\r\n */\r\n\r\n#include <cassert>\r\n#include <utility>\r\n#include <vector>\r\
    \n\r\nnamespace lib {\r\n\r\ntemplate <typename Type>\r\nclass SparseMatrix {\r\
    \npublic:\r\n  using value_type = Type;\r\n\r\n  SparseMatrix(int r, int c, const\
    \ Type &v = Type()) : row_(r), col_(c), default_val_(v), mat_(r) {}\r\n  virtual\
    \ ~SparseMatrix()            = default;\r\n  SparseMatrix(const SparseMatrix &)\
    \ = default;\r\n\r\n  virtual SparseMatrix &operator=(const SparseMatrix &) =\
    \ default;\r\n\r\n  int row() const { return row_; }\r\n  int col() const { return\
    \ col_; }\r\n  int size() const { return row_ * col_; }\r\n  bool is_empty() const\
    \ { return size() == 0; }\r\n\r\n  Type &at(int r, int c) {\r\n    for (auto &[pos,\
    \ v] : mat_[r])\r\n      if (pos == c) return v;\r\n    return mat_[r].emplace_back(c,\
    \ default_val_).second;\r\n  }\r\n  Type at(int r, int c) const {\r\n    for (auto\
    \ &[pos, v] : mat_[r])\r\n      if (pos == c) return v;\r\n    return default_val_;\r\
    \n  }\r\n\r\n  virtual std::vector<Type> apply(const std::vector<Type> &x) const\
    \ {\r\n    int r = row(), c = col();\r\n    assert(c == x.size());\r\n    assert(default_val_\
    \ == Type(0)); // \u82E5\u9ED8\u8BA4\u503C\u4E0D\u4E3A\u96F6\u5219\u9700\u8981\
    \u4FEE\u6539\u6B64\u51FD\u6570\r\n    std::vector<Type> res(r, Type(0));\r\n \
    \   for (int i = 0; i < r; ++i) {\r\n      for (auto &[pos, v] : mat_[i]) res[i]\
    \ += v * x[pos];\r\n    }\r\n    return res;\r\n  }\r\n\r\nprotected:\r\n  int\
    \ row_, col_;\r\n  const Type default_val_;\r\n  std::vector<std::vector<std::pair<int,\
    \ Type>>> mat_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/sparse_matrix_base.hpp
  requiredBy:
  - math/matrix/sparse_square_matrix.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
documentation_of: math/matrix/sparse_matrix_base.hpp
layout: document
redirect_from:
- /library/math/matrix/sparse_matrix_base.hpp
- /library/math/matrix/sparse_matrix_base.hpp.html
title: "sparse matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B"
---
