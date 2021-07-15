---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/matrix/arbitrary_modulo_square_matrix.hpp
    title: "arbitrary modulo square matrix / \u4EFB\u610F\u6A21\u6570\u65B9\u9635"
  - icon: ':x:'
    path: math/matrix/square_matrix.hpp
    title: "square matrix / \u65B9\u9635"
  _extendedVerifiedWith:
  - icon: ':x:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
    title: remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/matrix_det.0.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/matrix_det.1.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.1.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/matrix_det.2.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.2.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/matrix_product.0.test.cpp
    title: remote_test/yosupo/matrix/matrix_product.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "matrix base / \u77E9\u9635\u57FA\u7C7B"
    links: []
  bundledCode: "#line 1 \"math/matrix/matrix_base.hpp\"\n\n\n\r\n/**\r\n * @brief\
    \ matrix base / \u77E9\u9635\u57FA\u7C7B\r\n *\r\n */\r\n\r\n#include <algorithm>\r\
    \n#include <cassert>\r\n#include <iostream>\r\n#include <numeric>\r\n#include\
    \ <vector>\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename Type>\r\nclass Matrix\
    \ {\r\npublic:\r\n  using value_type = Type;\r\n\r\n  /**\r\n   * @brief Matrix\
    \ \u7C7B\r\n   *\r\n   * @param r \u884C\r\n   * @param c \u5217\r\n   * @param\
    \ v \u521D\u503C\r\n   */\r\n  Matrix(int r, int c, const Type &v = Type()) :\
    \ row_(r), col_(c), mat_(row_ * col_, v) {}\r\n  virtual ~Matrix()      = default;\r\
    \n  Matrix(const Matrix &) = default;\r\n\r\n  virtual Matrix &operator=(const\
    \ Matrix &) = default;\r\n\r\n  int row() const { return row_; }\r\n  int col()\
    \ const { return col_; }\r\n  int size() const { return row_ * col_; }\r\n  bool\
    \ is_empty() const { return size() == 0; }\r\n\r\n  decltype(auto) row_begin(int\
    \ r) { return mat_.begin() + r * col_; }\r\n  decltype(auto) row_cbegin(int r)\
    \ const { return mat_.cbegin() + r * col_; }\r\n  decltype(auto) row_begin(int\
    \ r) const { return row_cbegin(r); }\r\n  decltype(auto) row_end(int r) { return\
    \ mat_.begin() + (r + 1) * col_; }\r\n  decltype(auto) row_cend(int r) const {\
    \ return mat_.cbegin() + (r + 1) * col_; }\r\n  decltype(auto) row_end(int r)\
    \ const { return row_cend(r); }\r\n\r\n#ifdef LOCAL\r\n  Type &at(int r, int c)\
    \ { return mat_.at(r * col_ + c); }\r\n  const Type &at(int r, int c) const {\
    \ return mat_.at(r * col_ + c); }\r\n#else\r\n  Type &at(int r, int c) { return\
    \ mat_[r * col_ + c]; }\r\n  const Type &at(int r, int c) const { return mat_[r\
    \ * col_ + c]; }\r\n#endif\r\n\r\n  virtual Matrix &operator+=(const Matrix &rhs)\
    \ {\r\n    assert(row() == rhs.row());\r\n    assert(col() == rhs.col());\r\n\
    \    for (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\r\n    return\
    \ *this;\r\n  }\r\n\r\n  virtual Matrix &operator-=(const Matrix &rhs) {\r\n \
    \   assert(row() == rhs.row());\r\n    assert(col() == rhs.col());\r\n    for\
    \ (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\r\n    return *this;\r\
    \n  }\r\n\r\n  virtual Matrix transpose() const {\r\n    int n = row(), m = col();\r\
    \n    Matrix res(m, n, Type(0));\r\n    for (int i = 0; i < n; ++i)\r\n      for\
    \ (int j = 0; j < m; ++j) res.at(j, i) = at(i, j);\r\n    return res;\r\n  }\r\
    \n\r\n  /**\r\n   * @brief \u8FD4\u56DE\u77E9\u9635\u548C\u5217\u5411\u91CF x\
    \ \u7684\u79EF\r\n   * @param x \u5217\u5411\u91CF x \u6EE1\u8DB3 x \u7684\u884C\
    \u6570\u7B49\u4E8E\u77E9\u9635\u7684\u5217\u6570\r\n   * @return std::vector<Type>\r\
    \n   */\r\n  virtual std::vector<Type> apply(const std::vector<Type> &x) const\
    \ {\r\n    assert(col() == x.size());\r\n    int n = row();\r\n    std::vector<Type>\
    \ res(n);\r\n    for (int i = 0; i < n; ++i)\r\n      res[i] = std::inner_product(row_begin(i),\
    \ row_end(i), x.begin(), Type(0));\r\n    return res;\r\n  }\r\n\r\n  /**\r\n\
    \   * @brief \u77E9\u9635\u4E58\u6CD5\r\n   * @param rhs \u53F3\u4E58\u7684\u77E9\
    \u9635\r\n   * @return Matrix&\r\n   */\r\n  virtual Matrix &operator*=(const\
    \ Matrix &rhs) {\r\n    int n = row(), m = rhs.col(), l = col();\r\n    assert(l\
    \ == rhs.row());\r\n    // n*l \u7684\u77E9\u9635\u53F3\u4E58\u4E00\u4E2A l*m\
    \ \u7684\u77E9\u9635\r\n    Matrix res(n, m), trhs(rhs.transpose());\r\n    for\
    \ (int i = 0; i < n; ++i)\r\n      for (int j = 0; j < m; ++j)\r\n        res.at(i,\
    \ j) = std::inner_product(row_begin(i), row_end(i), trhs.row_begin(j), Type(0));\r\
    \n    return this->operator=(res);\r\n  }\r\n\r\n  virtual Matrix operator+(const\
    \ Matrix &rhs) { return Matrix(*this) += rhs; }\r\n  virtual Matrix operator-(const\
    \ Matrix &rhs) { return Matrix(*this) -= rhs; }\r\n  virtual Matrix operator*(const\
    \ Matrix &rhs) { return Matrix(*this) *= rhs; }\r\n\r\n  friend std::istream &operator>>(std::istream\
    \ &is, Matrix &rhs) {\r\n    for (auto &i : rhs.mat_) is >> i;\r\n    return is;\r\
    \n  }\r\n  friend std::ostream &operator<<(std::ostream &os, const Matrix &rhs)\
    \ {\r\n    int n = rhs.col();\r\n    for (int i = 0, e = rhs.size(), k = 0; i\
    \ < e; ++i) {\r\n      os << rhs.mat_[i];\r\n      if (++k == n) {\r\n       \
    \ k = 0;\r\n        std::cout << '\\n';\r\n      } else {\r\n        std::cout\
    \ << ' ';\r\n      }\r\n    }\r\n    return os;\r\n  }\r\n\r\nprotected:\r\n \
    \ int row_, col_;\r\n  std::vector<Type> mat_;\r\n};\r\n\r\n} // namespace lib\r\
    \n\r\n\n"
  code: "#ifndef MATRIX_BASE_HEADER_HPP\r\n#define MATRIX_BASE_HEADER_HPP\r\n\r\n\
    /**\r\n * @brief matrix base / \u77E9\u9635\u57FA\u7C7B\r\n *\r\n */\r\n\r\n#include\
    \ <algorithm>\r\n#include <cassert>\r\n#include <iostream>\r\n#include <numeric>\r\
    \n#include <vector>\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename Type>\r\n\
    class Matrix {\r\npublic:\r\n  using value_type = Type;\r\n\r\n  /**\r\n   * @brief\
    \ Matrix \u7C7B\r\n   *\r\n   * @param r \u884C\r\n   * @param c \u5217\r\n  \
    \ * @param v \u521D\u503C\r\n   */\r\n  Matrix(int r, int c, const Type &v = Type())\
    \ : row_(r), col_(c), mat_(row_ * col_, v) {}\r\n  virtual ~Matrix()      = default;\r\
    \n  Matrix(const Matrix &) = default;\r\n\r\n  virtual Matrix &operator=(const\
    \ Matrix &) = default;\r\n\r\n  int row() const { return row_; }\r\n  int col()\
    \ const { return col_; }\r\n  int size() const { return row_ * col_; }\r\n  bool\
    \ is_empty() const { return size() == 0; }\r\n\r\n  decltype(auto) row_begin(int\
    \ r) { return mat_.begin() + r * col_; }\r\n  decltype(auto) row_cbegin(int r)\
    \ const { return mat_.cbegin() + r * col_; }\r\n  decltype(auto) row_begin(int\
    \ r) const { return row_cbegin(r); }\r\n  decltype(auto) row_end(int r) { return\
    \ mat_.begin() + (r + 1) * col_; }\r\n  decltype(auto) row_cend(int r) const {\
    \ return mat_.cbegin() + (r + 1) * col_; }\r\n  decltype(auto) row_end(int r)\
    \ const { return row_cend(r); }\r\n\r\n#ifdef LOCAL\r\n  Type &at(int r, int c)\
    \ { return mat_.at(r * col_ + c); }\r\n  const Type &at(int r, int c) const {\
    \ return mat_.at(r * col_ + c); }\r\n#else\r\n  Type &at(int r, int c) { return\
    \ mat_[r * col_ + c]; }\r\n  const Type &at(int r, int c) const { return mat_[r\
    \ * col_ + c]; }\r\n#endif\r\n\r\n  virtual Matrix &operator+=(const Matrix &rhs)\
    \ {\r\n    assert(row() == rhs.row());\r\n    assert(col() == rhs.col());\r\n\
    \    for (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\r\n    return\
    \ *this;\r\n  }\r\n\r\n  virtual Matrix &operator-=(const Matrix &rhs) {\r\n \
    \   assert(row() == rhs.row());\r\n    assert(col() == rhs.col());\r\n    for\
    \ (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\r\n    return *this;\r\
    \n  }\r\n\r\n  virtual Matrix transpose() const {\r\n    int n = row(), m = col();\r\
    \n    Matrix res(m, n, Type(0));\r\n    for (int i = 0; i < n; ++i)\r\n      for\
    \ (int j = 0; j < m; ++j) res.at(j, i) = at(i, j);\r\n    return res;\r\n  }\r\
    \n\r\n  /**\r\n   * @brief \u8FD4\u56DE\u77E9\u9635\u548C\u5217\u5411\u91CF x\
    \ \u7684\u79EF\r\n   * @param x \u5217\u5411\u91CF x \u6EE1\u8DB3 x \u7684\u884C\
    \u6570\u7B49\u4E8E\u77E9\u9635\u7684\u5217\u6570\r\n   * @return std::vector<Type>\r\
    \n   */\r\n  virtual std::vector<Type> apply(const std::vector<Type> &x) const\
    \ {\r\n    assert(col() == x.size());\r\n    int n = row();\r\n    std::vector<Type>\
    \ res(n);\r\n    for (int i = 0; i < n; ++i)\r\n      res[i] = std::inner_product(row_begin(i),\
    \ row_end(i), x.begin(), Type(0));\r\n    return res;\r\n  }\r\n\r\n  /**\r\n\
    \   * @brief \u77E9\u9635\u4E58\u6CD5\r\n   * @param rhs \u53F3\u4E58\u7684\u77E9\
    \u9635\r\n   * @return Matrix&\r\n   */\r\n  virtual Matrix &operator*=(const\
    \ Matrix &rhs) {\r\n    int n = row(), m = rhs.col(), l = col();\r\n    assert(l\
    \ == rhs.row());\r\n    // n*l \u7684\u77E9\u9635\u53F3\u4E58\u4E00\u4E2A l*m\
    \ \u7684\u77E9\u9635\r\n    Matrix res(n, m), trhs(rhs.transpose());\r\n    for\
    \ (int i = 0; i < n; ++i)\r\n      for (int j = 0; j < m; ++j)\r\n        res.at(i,\
    \ j) = std::inner_product(row_begin(i), row_end(i), trhs.row_begin(j), Type(0));\r\
    \n    return this->operator=(res);\r\n  }\r\n\r\n  virtual Matrix operator+(const\
    \ Matrix &rhs) { return Matrix(*this) += rhs; }\r\n  virtual Matrix operator-(const\
    \ Matrix &rhs) { return Matrix(*this) -= rhs; }\r\n  virtual Matrix operator*(const\
    \ Matrix &rhs) { return Matrix(*this) *= rhs; }\r\n\r\n  friend std::istream &operator>>(std::istream\
    \ &is, Matrix &rhs) {\r\n    for (auto &i : rhs.mat_) is >> i;\r\n    return is;\r\
    \n  }\r\n  friend std::ostream &operator<<(std::ostream &os, const Matrix &rhs)\
    \ {\r\n    int n = rhs.col();\r\n    for (int i = 0, e = rhs.size(), k = 0; i\
    \ < e; ++i) {\r\n      os << rhs.mat_[i];\r\n      if (++k == n) {\r\n       \
    \ k = 0;\r\n        std::cout << '\\n';\r\n      } else {\r\n        std::cout\
    \ << ' ';\r\n      }\r\n    }\r\n    return os;\r\n  }\r\n\r\nprotected:\r\n \
    \ int row_, col_;\r\n  std::vector<Type> mat_;\r\n};\r\n\r\n} // namespace lib\r\
    \n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/matrix_base.hpp
  requiredBy:
  - math/matrix/arbitrary_modulo_square_matrix.hpp
  - math/matrix/square_matrix.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - remote_test/yosupo/matrix/matrix_det.0.test.cpp
  - remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
  - remote_test/yosupo/matrix/matrix_det.1.test.cpp
  - remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
  - remote_test/yosupo/matrix/matrix_product.0.test.cpp
  - remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
  - remote_test/yosupo/matrix/matrix_det.2.test.cpp
documentation_of: math/matrix/matrix_base.hpp
layout: document
redirect_from:
- /library/math/matrix/matrix_base.hpp
- /library/math/matrix/matrix_base.hpp.html
title: "matrix base / \u77E9\u9635\u57FA\u7C7B"
---
