---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/matrix_product.0.test.cpp
    title: remote_test/yosupo/math/matrix_product.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "matrix basic / \u77E9\u9635\u57FA\u7840"
    links: []
  bundledCode: "#line 1 \"math/matrix/matrix_basic.hpp\"\n\n\n\n/**\n * @brief matrix\
    \ basic / \u77E9\u9635\u57FA\u7840\n *\n */\n\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\n\nnamespace lib {\n\ntemplate <typename Type, typename Container\
    \ = std::vector<Type>> class Matrix {\npublic:\n  /**\n   * @brief Matrix \u7C7B\
    \n   *\n   * @param r \u884C\n   * @param c \u5217\n   * @param v \u521D\u503C\
    \n   */\n  Matrix(int r, int c, const Type &v = Type()) : row_(r), col_(c), mat_(row_\
    \ * col_, v) {}\n  ~Matrix() = default;\n  Matrix(const Matrix &) = default;\n\
    \n  Matrix &operator=(const Matrix &) = default;\n\n  int row() const { return\
    \ row_; }\n  int col() const { return col_; }\n  int size() const { return row_\
    \ * col_; }\n  bool is_empty() const { return size() == 0; }\n\n  Type &at(int\
    \ r, int c) { return mat_[r * col_ + c]; }\n  const Type &at(int r, int c) const\
    \ { return mat_[r * col_ + c]; }\n\n  friend Matrix make_identity_matrix(int r)\
    \ {\n    Matrix res(r, r);\n    for (int i = 0; i < r; ++i) res.at(i, i) = Type(1);\n\
    \    return res;\n  }\n\n  Matrix &operator+=(const Matrix &rhs) {\n    assert(row()\
    \ == rhs.row());\n    assert(col() == rhs.col());\n    for (int i = 0, n = size();\
    \ i < n; ++i) mat_[i] -= rhs.mat_[i];\n    return *this;\n  }\n\n  Matrix &operator-=(const\
    \ Matrix &rhs) {\n    assert(row() == rhs.row());\n    assert(col() == rhs.col());\n\
    \    for (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\n    return\
    \ *this;\n  }\n\n  Matrix &operator*=(const Matrix &rhs) {\n    int n = row(),\
    \ m = rhs.col(), l = col();\n    assert(l == rhs.row());\n    Matrix res(n, m,\
    \ Type(0));\n    for (int i = 0; i != n; ++i)\n      for (int k = 0; k != l; ++k)\n\
    \        for (int j = 0; j != m; ++j) res.at(i, j) += at(i, k) * rhs.at(k, j);\n\
    \    return this->operator=(res);\n  }\n\n  friend std::istream &operator>>(std::istream\
    \ &is, Matrix &rhs) {\n    for (auto &i : rhs.mat_) is >> i;\n    return is;\n\
    \  }\n  friend std::ostream &operator<<(std::ostream &os, const Matrix &rhs) {\n\
    \    int n = rhs.col();\n    for (int i = 0, e = rhs.size(); i < e; ++i) os <<\
    \ rhs.mat_[i] << \" \\n\"[i == n - 1];\n    return os;\n  }\n\n  friend Matrix\
    \ operator+(const Matrix &lhs, const Matrix &rhs) { return Matrix(lhs) += rhs;\
    \ }\n  friend Matrix operator-(const Matrix &lhs, const Matrix &rhs) { return\
    \ Matrix(lhs) -= rhs; }\n  friend Matrix operator*(const Matrix &lhs, const Matrix\
    \ &rhs) { return Matrix(lhs) *= rhs; }\n\nprivate:\n  int row_, col_;\n  Container\
    \ mat_;\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef MATRIX_BASIC_HEADER_HPP\n#define MATRIX_BASIC_HEADER_HPP\n\n/**\n\
    \ * @brief matrix basic / \u77E9\u9635\u57FA\u7840\n *\n */\n\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\n\nnamespace lib {\n\ntemplate <typename\
    \ Type, typename Container = std::vector<Type>> class Matrix {\npublic:\n  /**\n\
    \   * @brief Matrix \u7C7B\n   *\n   * @param r \u884C\n   * @param c \u5217\n\
    \   * @param v \u521D\u503C\n   */\n  Matrix(int r, int c, const Type &v = Type())\
    \ : row_(r), col_(c), mat_(row_ * col_, v) {}\n  ~Matrix() = default;\n  Matrix(const\
    \ Matrix &) = default;\n\n  Matrix &operator=(const Matrix &) = default;\n\n \
    \ int row() const { return row_; }\n  int col() const { return col_; }\n  int\
    \ size() const { return row_ * col_; }\n  bool is_empty() const { return size()\
    \ == 0; }\n\n  Type &at(int r, int c) { return mat_[r * col_ + c]; }\n  const\
    \ Type &at(int r, int c) const { return mat_[r * col_ + c]; }\n\n  friend Matrix\
    \ make_identity_matrix(int r) {\n    Matrix res(r, r);\n    for (int i = 0; i\
    \ < r; ++i) res.at(i, i) = Type(1);\n    return res;\n  }\n\n  Matrix &operator+=(const\
    \ Matrix &rhs) {\n    assert(row() == rhs.row());\n    assert(col() == rhs.col());\n\
    \    for (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\n    return\
    \ *this;\n  }\n\n  Matrix &operator-=(const Matrix &rhs) {\n    assert(row() ==\
    \ rhs.row());\n    assert(col() == rhs.col());\n    for (int i = 0, n = size();\
    \ i < n; ++i) mat_[i] -= rhs.mat_[i];\n    return *this;\n  }\n\n  Matrix &operator*=(const\
    \ Matrix &rhs) {\n    int n = row(), m = rhs.col(), l = col();\n    assert(l ==\
    \ rhs.row());\n    Matrix res(n, m, Type(0));\n    for (int i = 0; i != n; ++i)\n\
    \      for (int k = 0; k != l; ++k)\n        for (int j = 0; j != m; ++j) res.at(i,\
    \ j) += at(i, k) * rhs.at(k, j);\n    return this->operator=(res);\n  }\n\n  friend\
    \ std::istream &operator>>(std::istream &is, Matrix &rhs) {\n    for (auto &i\
    \ : rhs.mat_) is >> i;\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const Matrix &rhs) {\n    int n = rhs.col();\n    for (int i = 0, e = rhs.size();\
    \ i < e; ++i) os << rhs.mat_[i] << \" \\n\"[i == n - 1];\n    return os;\n  }\n\
    \n  friend Matrix operator+(const Matrix &lhs, const Matrix &rhs) { return Matrix(lhs)\
    \ += rhs; }\n  friend Matrix operator-(const Matrix &lhs, const Matrix &rhs) {\
    \ return Matrix(lhs) -= rhs; }\n  friend Matrix operator*(const Matrix &lhs, const\
    \ Matrix &rhs) { return Matrix(lhs) *= rhs; }\n\nprivate:\n  int row_, col_;\n\
    \  Container mat_;\n};\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/matrix_basic.hpp
  requiredBy: []
  timestamp: '2021-06-21 04:44:53+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/matrix_product.0.test.cpp
documentation_of: math/matrix/matrix_basic.hpp
layout: document
redirect_from:
- /library/math/matrix/matrix_basic.hpp
- /library/math/matrix/matrix_basic.hpp.html
title: "matrix basic / \u77E9\u9635\u57FA\u7840"
---
