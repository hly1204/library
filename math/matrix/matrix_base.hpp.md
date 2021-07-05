---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/matrix/square_matrix.hpp
    title: "square matrix / \u65B9\u9635"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
    title: remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/matrix_det.0.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/matrix_det.1.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/matrix_product.0.test.cpp
    title: remote_test/yosupo/matrix/matrix_product.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "matrix base / \u77E9\u9635\u57FA\u7C7B"
    links: []
  bundledCode: "#line 1 \"math/matrix/matrix_base.hpp\"\n\n\n\n/**\n * @brief matrix\
    \ base / \u77E9\u9635\u57FA\u7C7B\n *\n */\n\n#include <algorithm>\n#include <cassert>\n\
    #include <iostream>\n#include <numeric>\n#include <vector>\n\nnamespace lib {\n\
    \ntemplate <typename Type> class Matrix {\npublic:\n  using value_type = Type;\n\
    \n  /**\n   * @brief Matrix \u7C7B\n   *\n   * @param r \u884C\n   * @param c\
    \ \u5217\n   * @param v \u521D\u503C\n   */\n  Matrix(int r, int c, const Type\
    \ &v = Type()) : row_(r), col_(c), mat_(row_ * col_, v) {}\n  virtual ~Matrix()\
    \ = default;\n  Matrix(const Matrix &) = default;\n\n  virtual Matrix &operator=(const\
    \ Matrix &) = default;\n\n  int row() const { return row_; }\n  int col() const\
    \ { return col_; }\n  int size() const { return row_ * col_; }\n  bool is_empty()\
    \ const { return size() == 0; }\n\n  decltype(auto) row_begin(int r) { return\
    \ mat_.begin() + r * col_; }\n  decltype(auto) row_cbegin(int r) const { return\
    \ mat_.cbegin() + r * col_; }\n  decltype(auto) row_begin(int r) const { return\
    \ row_cbegin(r); }\n  decltype(auto) row_end(int r) { return mat_.begin() + (r\
    \ + 1) * col_; }\n  decltype(auto) row_cend(int r) const { return mat_.cbegin()\
    \ + (r + 1) * col_; }\n  decltype(auto) row_end(int r) const { return row_cend(r);\
    \ }\n\n#ifdef LOCAL\n  Type &at(int r, int c) { return mat_.at(r * col_ + c);\
    \ }\n  const Type &at(int r, int c) const { return mat_.at(r * col_ + c); }\n\
    #else\n  Type &at(int r, int c) { return mat_[r * col_ + c]; }\n  const Type &at(int\
    \ r, int c) const { return mat_[r * col_ + c]; }\n#endif\n\n  virtual Matrix &operator+=(const\
    \ Matrix &rhs) {\n    assert(row() == rhs.row());\n    assert(col() == rhs.col());\n\
    \    for (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\n    return\
    \ *this;\n  }\n\n  virtual Matrix &operator-=(const Matrix &rhs) {\n    assert(row()\
    \ == rhs.row());\n    assert(col() == rhs.col());\n    for (int i = 0, n = size();\
    \ i < n; ++i) mat_[i] -= rhs.mat_[i];\n    return *this;\n  }\n\n  virtual Matrix\
    \ transpose() const {\n    int n = row(), m = col();\n    Matrix res(m, n, Type(0));\n\
    \    for (int i = 0; i < n; ++i)\n      for (int j = 0; j < m; ++j) res.at(j,\
    \ i) = at(i, j);\n    return res;\n  }\n\n  /**\n   * @brief \u8FD4\u56DE\u77E9\
    \u9635\u548C\u5217\u5411\u91CF x \u7684\u79EF\n   * @param x \u5217\u5411\u91CF\
    \ x \u6EE1\u8DB3 x \u7684\u884C\u6570\u7B49\u4E8E\u77E9\u9635\u7684\u5217\u6570\
    \n   * @return std::vector<Type>\n   */\n  virtual std::vector<Type> apply(const\
    \ std::vector<Type> &x) const {\n    assert(col() == x.size());\n    int n = row();\n\
    \    std::vector<Type> res(n);\n    for (int i = 0; i < n; ++i)\n      res[i]\
    \ = std::inner_product(row_begin(i), row_end(i), x.begin(), Type(0));\n    return\
    \ res;\n  }\n\n  /**\n   * @brief \u77E9\u9635\u4E58\u6CD5\n   * @param rhs \u53F3\
    \u4E58\u7684\u77E9\u9635\n   * @return Matrix&\n   */\n  virtual Matrix &operator*=(const\
    \ Matrix &rhs) {\n    int n = row(), m = rhs.col(), l = col();\n    assert(l ==\
    \ rhs.row());\n    // n*l \u7684\u77E9\u9635\u53F3\u4E58\u4E00\u4E2A l*m \u7684\
    \u77E9\u9635\n    Matrix res(n, m), trhs(rhs.transpose());\n    for (int i = 0;\
    \ i < n; ++i)\n      for (int j = 0; j < m; ++j)\n        res.at(i, j) = std::inner_product(row_begin(i),\
    \ row_end(i), trhs.row_begin(j), Type(0));\n    return this->operator=(res);\n\
    \  }\n\n  virtual Matrix operator+(const Matrix &rhs) { return Matrix(*this) +=\
    \ rhs; }\n  virtual Matrix operator-(const Matrix &rhs) { return Matrix(*this)\
    \ -= rhs; }\n  virtual Matrix operator*(const Matrix &rhs) { return Matrix(*this)\
    \ *= rhs; }\n\n  friend std::istream &operator>>(std::istream &is, Matrix &rhs)\
    \ {\n    for (auto &i : rhs.mat_) is >> i;\n    return is;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &os, const Matrix &rhs) {\n    int n = rhs.col();\n\
    \    for (int i = 0, e = rhs.size(), k = 0; i < e; ++i) {\n      os << rhs.mat_[i];\n\
    \      if (++k == n) {\n        k = 0;\n        std::cout << '\\n';\n      } else\
    \ {\n        std::cout << ' ';\n      }\n    }\n    return os;\n  }\n\nprotected:\n\
    \  int row_, col_;\n  std::vector<Type> mat_;\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef MATRIX_BASE_HEADER_HPP\n#define MATRIX_BASE_HEADER_HPP\n\n/**\n *\
    \ @brief matrix base / \u77E9\u9635\u57FA\u7C7B\n *\n */\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <numeric>\n#include <vector>\n\
    \nnamespace lib {\n\ntemplate <typename Type> class Matrix {\npublic:\n  using\
    \ value_type = Type;\n\n  /**\n   * @brief Matrix \u7C7B\n   *\n   * @param r\
    \ \u884C\n   * @param c \u5217\n   * @param v \u521D\u503C\n   */\n  Matrix(int\
    \ r, int c, const Type &v = Type()) : row_(r), col_(c), mat_(row_ * col_, v) {}\n\
    \  virtual ~Matrix() = default;\n  Matrix(const Matrix &) = default;\n\n  virtual\
    \ Matrix &operator=(const Matrix &) = default;\n\n  int row() const { return row_;\
    \ }\n  int col() const { return col_; }\n  int size() const { return row_ * col_;\
    \ }\n  bool is_empty() const { return size() == 0; }\n\n  decltype(auto) row_begin(int\
    \ r) { return mat_.begin() + r * col_; }\n  decltype(auto) row_cbegin(int r) const\
    \ { return mat_.cbegin() + r * col_; }\n  decltype(auto) row_begin(int r) const\
    \ { return row_cbegin(r); }\n  decltype(auto) row_end(int r) { return mat_.begin()\
    \ + (r + 1) * col_; }\n  decltype(auto) row_cend(int r) const { return mat_.cbegin()\
    \ + (r + 1) * col_; }\n  decltype(auto) row_end(int r) const { return row_cend(r);\
    \ }\n\n#ifdef LOCAL\n  Type &at(int r, int c) { return mat_.at(r * col_ + c);\
    \ }\n  const Type &at(int r, int c) const { return mat_.at(r * col_ + c); }\n\
    #else\n  Type &at(int r, int c) { return mat_[r * col_ + c]; }\n  const Type &at(int\
    \ r, int c) const { return mat_[r * col_ + c]; }\n#endif\n\n  virtual Matrix &operator+=(const\
    \ Matrix &rhs) {\n    assert(row() == rhs.row());\n    assert(col() == rhs.col());\n\
    \    for (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\n    return\
    \ *this;\n  }\n\n  virtual Matrix &operator-=(const Matrix &rhs) {\n    assert(row()\
    \ == rhs.row());\n    assert(col() == rhs.col());\n    for (int i = 0, n = size();\
    \ i < n; ++i) mat_[i] -= rhs.mat_[i];\n    return *this;\n  }\n\n  virtual Matrix\
    \ transpose() const {\n    int n = row(), m = col();\n    Matrix res(m, n, Type(0));\n\
    \    for (int i = 0; i < n; ++i)\n      for (int j = 0; j < m; ++j) res.at(j,\
    \ i) = at(i, j);\n    return res;\n  }\n\n  /**\n   * @brief \u8FD4\u56DE\u77E9\
    \u9635\u548C\u5217\u5411\u91CF x \u7684\u79EF\n   * @param x \u5217\u5411\u91CF\
    \ x \u6EE1\u8DB3 x \u7684\u884C\u6570\u7B49\u4E8E\u77E9\u9635\u7684\u5217\u6570\
    \n   * @return std::vector<Type>\n   */\n  virtual std::vector<Type> apply(const\
    \ std::vector<Type> &x) const {\n    assert(col() == x.size());\n    int n = row();\n\
    \    std::vector<Type> res(n);\n    for (int i = 0; i < n; ++i)\n      res[i]\
    \ = std::inner_product(row_begin(i), row_end(i), x.begin(), Type(0));\n    return\
    \ res;\n  }\n\n  /**\n   * @brief \u77E9\u9635\u4E58\u6CD5\n   * @param rhs \u53F3\
    \u4E58\u7684\u77E9\u9635\n   * @return Matrix&\n   */\n  virtual Matrix &operator*=(const\
    \ Matrix &rhs) {\n    int n = row(), m = rhs.col(), l = col();\n    assert(l ==\
    \ rhs.row());\n    // n*l \u7684\u77E9\u9635\u53F3\u4E58\u4E00\u4E2A l*m \u7684\
    \u77E9\u9635\n    Matrix res(n, m), trhs(rhs.transpose());\n    for (int i = 0;\
    \ i < n; ++i)\n      for (int j = 0; j < m; ++j)\n        res.at(i, j) = std::inner_product(row_begin(i),\
    \ row_end(i), trhs.row_begin(j), Type(0));\n    return this->operator=(res);\n\
    \  }\n\n  virtual Matrix operator+(const Matrix &rhs) { return Matrix(*this) +=\
    \ rhs; }\n  virtual Matrix operator-(const Matrix &rhs) { return Matrix(*this)\
    \ -= rhs; }\n  virtual Matrix operator*(const Matrix &rhs) { return Matrix(*this)\
    \ *= rhs; }\n\n  friend std::istream &operator>>(std::istream &is, Matrix &rhs)\
    \ {\n    for (auto &i : rhs.mat_) is >> i;\n    return is;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &os, const Matrix &rhs) {\n    int n = rhs.col();\n\
    \    for (int i = 0, e = rhs.size(), k = 0; i < e; ++i) {\n      os << rhs.mat_[i];\n\
    \      if (++k == n) {\n        k = 0;\n        std::cout << '\\n';\n      } else\
    \ {\n        std::cout << ' ';\n      }\n    }\n    return os;\n  }\n\nprotected:\n\
    \  int row_, col_;\n  std::vector<Type> mat_;\n};\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/matrix_base.hpp
  requiredBy:
  - math/matrix/square_matrix.hpp
  timestamp: '2021-06-28 18:28:55+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/matrix/matrix_det.0.test.cpp
  - remote_test/yosupo/matrix/matrix_det.1.test.cpp
  - remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
  - remote_test/yosupo/matrix/matrix_product.0.test.cpp
  - remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
documentation_of: math/matrix/matrix_base.hpp
layout: document
redirect_from:
- /library/math/matrix/matrix_base.hpp
- /library/math/matrix/matrix_base.hpp.html
title: "matrix base / \u77E9\u9635\u57FA\u7C7B"
---
