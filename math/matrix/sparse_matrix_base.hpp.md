---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/matrix/square_sparse_matrix.hpp
    title: "square sparse matrix / \u7A00\u758F\u65B9\u9635"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
    title: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "sparse matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B"
    links: []
  bundledCode: "#line 1 \"math/matrix/sparse_matrix_base.hpp\"\n\n\n\n/**\n * @brief\
    \ sparse matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B\n *\n */\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace lib {\n\ntemplate <typename Type>\
    \ class SparseMatrix {\npublic:\n  using value_type = Type;\n\n  SparseMatrix(int\
    \ r, int c, const Type &v = Type()) : row_(r), col_(c), default_val_(v), mat_(r)\
    \ {}\n  virtual ~SparseMatrix() = default;\n  SparseMatrix(const SparseMatrix\
    \ &) = default;\n\n  virtual SparseMatrix &operator=(const SparseMatrix &) = default;\n\
    \n  int row() const { return row_; }\n  int col() const { return col_; }\n  int\
    \ size() const { return row_ * col_; }\n  bool is_empty() const { return size()\
    \ == 0; }\n\n  Type &at(int r, int c) {\n    for (auto &[pos, v] : mat_[r])\n\
    \      if (pos == c) return v;\n    mat_[r].emplace_back(c, default_val_);\n \
    \   return mat_[r].back().second;\n  }\n  Type at(int r, int c) const {\n    for\
    \ (auto &[pos, v] : mat_[r])\n      if (pos == c) return v;\n    return default_val_;\n\
    \  }\n\n  virtual std::vector<Type> apply(const std::vector<Type> &x) const {\n\
    \    int r = row(), c = col();\n    assert(c == x.size());\n    std::vector<Type>\
    \ res(r, Type(0));\n    for (int i = 0; i < r; ++i)\n      for (auto &[pos, v]\
    \ : mat_[i]) res[i] += v * x[pos];\n    return res;\n  }\n\nprotected:\n  int\
    \ row_, col_;\n  const Type default_val_;\n  std::vector<std::vector<std::pair<int,\
    \ Type>>> mat_;\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef SPARSE_MATRIX_BASE_HEADER_HPP\n#define SPARSE_MATRIX_BASE_HEADER_HPP\n\
    \n/**\n * @brief sparse matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B\n *\n\
    \ */\n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include\
    \ <numeric>\n#include <utility>\n#include <vector>\n\nnamespace lib {\n\ntemplate\
    \ <typename Type> class SparseMatrix {\npublic:\n  using value_type = Type;\n\n\
    \  SparseMatrix(int r, int c, const Type &v = Type()) : row_(r), col_(c), default_val_(v),\
    \ mat_(r) {}\n  virtual ~SparseMatrix() = default;\n  SparseMatrix(const SparseMatrix\
    \ &) = default;\n\n  virtual SparseMatrix &operator=(const SparseMatrix &) = default;\n\
    \n  int row() const { return row_; }\n  int col() const { return col_; }\n  int\
    \ size() const { return row_ * col_; }\n  bool is_empty() const { return size()\
    \ == 0; }\n\n  Type &at(int r, int c) {\n    for (auto &[pos, v] : mat_[r])\n\
    \      if (pos == c) return v;\n    mat_[r].emplace_back(c, default_val_);\n \
    \   return mat_[r].back().second;\n  }\n  Type at(int r, int c) const {\n    for\
    \ (auto &[pos, v] : mat_[r])\n      if (pos == c) return v;\n    return default_val_;\n\
    \  }\n\n  virtual std::vector<Type> apply(const std::vector<Type> &x) const {\n\
    \    int r = row(), c = col();\n    assert(c == x.size());\n    std::vector<Type>\
    \ res(r, Type(0));\n    for (int i = 0; i < r; ++i)\n      for (auto &[pos, v]\
    \ : mat_[i]) res[i] += v * x[pos];\n    return res;\n  }\n\nprotected:\n  int\
    \ row_, col_;\n  const Type default_val_;\n  std::vector<std::vector<std::pair<int,\
    \ Type>>> mat_;\n};\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/sparse_matrix_base.hpp
  requiredBy:
  - math/matrix/square_sparse_matrix.hpp
  timestamp: '2021-06-30 10:17:50+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
documentation_of: math/matrix/sparse_matrix_base.hpp
layout: document
redirect_from:
- /library/math/matrix/sparse_matrix_base.hpp
- /library/math/matrix/sparse_matrix_base.hpp.html
title: "sparse matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B"
---
