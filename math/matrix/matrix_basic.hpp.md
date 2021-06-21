---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inverse_matrix.0.test.cpp
    title: remote_test/yosupo/math/inverse_matrix.0.test.cpp
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
    \ basic / \u77E9\u9635\u57FA\u7840\n *\n */\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <iostream>\n#include <vector>\n\nnamespace lib {\n\ntemplate\
    \ <typename Type, typename Container = std::vector<Type>> class Matrix {\npublic:\n\
    \  using value_type = Type;\n\n  /**\n   * @brief Matrix \u7C7B\n   *\n   * @param\
    \ r \u884C\n   * @param c \u5217\n   * @param v \u521D\u503C\n   */\n  Matrix(int\
    \ r, int c, const Type &v = Type()) : row_(r), col_(c), mat_(row_ * col_, v) {}\n\
    \  ~Matrix() = default;\n  Matrix(const Matrix &) = default;\n\n  Matrix &operator=(const\
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
    \ r, int c) const { return mat_[r * col_ + c]; }\n#endif\n\n  friend Matrix make_identity_matrix(int\
    \ r) {\n    Matrix res(r, r);\n    for (int i = 0; i < r; ++i) res.at(i, i) =\
    \ Type(1);\n    return res;\n  }\n\n  Matrix &operator+=(const Matrix &rhs) {\n\
    \    assert(row() == rhs.row());\n    assert(col() == rhs.col());\n    for (int\
    \ i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\n    return *this;\n\
    \  }\n\n  Matrix &operator-=(const Matrix &rhs) {\n    assert(row() == rhs.row());\n\
    \    assert(col() == rhs.col());\n    for (int i = 0, n = size(); i < n; ++i)\
    \ mat_[i] -= rhs.mat_[i];\n    return *this;\n  }\n\n  Matrix &operator*=(const\
    \ Matrix &rhs) {\n    int n = row(), m = rhs.col(), l = col();\n    assert(l ==\
    \ rhs.row());\n    Matrix res(n, m, Type(0));\n    for (int i = 0; i != n; ++i)\n\
    \      for (int k = 0; k != l; ++k)\n        for (int j = 0; j != m; ++j) res.at(i,\
    \ j) += at(i, k) * rhs.at(k, j);\n    return this->operator=(res);\n  }\n\n  friend\
    \ std::istream &operator>>(std::istream &is, Matrix &rhs) {\n    for (auto &i\
    \ : rhs.mat_) is >> i;\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const Matrix &rhs) {\n    int n = rhs.col();\n    for (int i = 0, e = rhs.size(),\
    \ k = 0; i < e; ++i) {\n      os << rhs.mat_[i];\n      if (++k == n) {\n    \
    \    k = 0;\n        std::cout << '\\n';\n      } else {\n        std::cout <<\
    \ ' ';\n      }\n    }\n    return os;\n  }\n\n  friend Matrix operator+(const\
    \ Matrix &lhs, const Matrix &rhs) { return Matrix(lhs) += rhs; }\n  friend Matrix\
    \ operator-(const Matrix &lhs, const Matrix &rhs) { return Matrix(lhs) -= rhs;\
    \ }\n  friend Matrix operator*(const Matrix &lhs, const Matrix &rhs) { return\
    \ Matrix(lhs) *= rhs; }\n\n  /**\n   * @brief \u57DF\u4E0A\u7684\u65B9\u9635\u9006\
    \u5143\n   * @note \u4F7F\u7528 Gauss-Jordan \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\
    \uFF0C\u6240\u4EE5\u5143\u7D20\u9700\u8981\u5C5E\u4E8E\u57DF\n   * @return Matrix\n\
    \   */\n  Matrix inv() const {\n    int n = row();\n    assert(col() == n);\n\
    \    Matrix extmat(n, n << 1, Type(0)), res(n, n);\n    for (int i = 0; i < n;\
    \ ++i) std::copy(row_begin(i), row_end(i), extmat.row_begin(i));\n    for (int\
    \ i = 0; i < n; ++i) extmat.at(i, i + n) = Type(1);\n    /*\n      [ x x x x |\
    \ 1 0 0 0 ] => [ 1 0 0 0 | x x x x ]\n      [ x x x x | 0 1 0 0 ] => [ 0 1 0 0\
    \ | x x x x ]\n      [ x x x x | 0 0 1 0 ] => [ 0 0 1 0 | x x x x ]\n      [ x\
    \ x x x | 0 0 0 1 ] => [ 0 0 0 1 | x x x x ]\n    */\n    // \u5148\u5C06\u5DE6\
    \u8FB9\u77E9\u9635\u6D88\u5143\u4E3A\u4E0A\u4E09\u89D2\u77E9\u9635\u4E14\u4E3B\
    \u5BF9\u89D2\u7EBF\u4E3A 1 \u518D\u4E0B\u9762\u5F80\u4E0A\u5C06\u8BE5\u77E9\u9635\
    \u6D88\u4E3A diag(1,1,1 ...)\n    {\n      for (int i = 0; i < n; ++i) {     \
    \  // \u7B2C\u4E00\u9636\u6BB5\n        if (extmat.at(i, i) == Type(0)) { // \u9009\
    \u4E3B\u5143\n          int pivot = i + 1;\n          for (; pivot < n; ++pivot)\n\
    \            if (extmat.at(pivot, i) != Type(0)) break;\n          if (pivot ==\
    \ n) return Matrix(0, 0); // \u4E0D\u5B58\u5728\u9006\u77E9\u9635\n          std::swap_ranges(extmat.row_begin(i)\
    \ + i, extmat.row_end(i),\n                           extmat.row_begin(pivot)\
    \ + i); // \u4EA4\u6362\u884C\n        }\n        if (extmat.at(i, i) != Type(1))\
    \ {\n          Type iv = Type(1) / extmat.at(i, i);\n          std::for_each(extmat.row_begin(i)\
    \ + i, extmat.row_end(i), [iv](Type &a) { a *= iv; });\n        }\n        for\
    \ (int j = i + 1; j < n; ++j) {\n          Type p = extmat.at(j, i);\n       \
    \   if (p == Type(0)) continue;\n          extmat.at(j, i) = Type(0);\n      \
    \    for (int k = i + 1; k < (n << 1); ++k) extmat.at(j, k) -= p * extmat.at(i,\
    \ k);\n        }\n      }\n      for (int i = n - 2; i >= 0; --i) { // \u7B2C\u4E8C\
    \u9636\u6BB5\n        for (int j = i; j >= 0; --j) {\n          Type p = extmat.at(j,\
    \ i + 1);\n          if (p == Type(0)) continue;\n          extmat.at(j, i + 1)\
    \ = Type(0);\n          for (int k = i + 2; k < (n << 1); ++k) extmat.at(j, k)\
    \ -= p * extmat.at(i + 1, k);\n        }\n      }\n    }\n    for (int i = 0;\
    \ i < n; ++i)\n      std::copy(extmat.row_begin(i) + n, extmat.row_end(i), res.row_begin(i));\n\
    \    return res;\n  }\n\n  Type det() const;\n  int rank() const;\n\nprivate:\n\
    \  int row_, col_;\n  Container mat_;\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef MATRIX_BASIC_HEADER_HPP\n#define MATRIX_BASIC_HEADER_HPP\n\n/**\n\
    \ * @brief matrix basic / \u77E9\u9635\u57FA\u7840\n *\n */\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <vector>\n\nnamespace lib {\n\
    \ntemplate <typename Type, typename Container = std::vector<Type>> class Matrix\
    \ {\npublic:\n  using value_type = Type;\n\n  /**\n   * @brief Matrix \u7C7B\n\
    \   *\n   * @param r \u884C\n   * @param c \u5217\n   * @param v \u521D\u503C\n\
    \   */\n  Matrix(int r, int c, const Type &v = Type()) : row_(r), col_(c), mat_(row_\
    \ * col_, v) {}\n  ~Matrix() = default;\n  Matrix(const Matrix &) = default;\n\
    \n  Matrix &operator=(const Matrix &) = default;\n\n  int row() const { return\
    \ row_; }\n  int col() const { return col_; }\n  int size() const { return row_\
    \ * col_; }\n  bool is_empty() const { return size() == 0; }\n\n  decltype(auto)\
    \ row_begin(int r) { return mat_.begin() + r * col_; }\n  decltype(auto) row_cbegin(int\
    \ r) const { return mat_.cbegin() + r * col_; }\n  decltype(auto) row_begin(int\
    \ r) const { return row_cbegin(r); }\n  decltype(auto) row_end(int r) { return\
    \ mat_.begin() + (r + 1) * col_; }\n  decltype(auto) row_cend(int r) const { return\
    \ mat_.cbegin() + (r + 1) * col_; }\n  decltype(auto) row_end(int r) const { return\
    \ row_cend(r); }\n\n#ifdef LOCAL\n  Type &at(int r, int c) { return mat_.at(r\
    \ * col_ + c); }\n  const Type &at(int r, int c) const { return mat_.at(r * col_\
    \ + c); }\n#else\n  Type &at(int r, int c) { return mat_[r * col_ + c]; }\n  const\
    \ Type &at(int r, int c) const { return mat_[r * col_ + c]; }\n#endif\n\n  friend\
    \ Matrix make_identity_matrix(int r) {\n    Matrix res(r, r);\n    for (int i\
    \ = 0; i < r; ++i) res.at(i, i) = Type(1);\n    return res;\n  }\n\n  Matrix &operator+=(const\
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
    \ &os, const Matrix &rhs) {\n    int n = rhs.col();\n    for (int i = 0, e = rhs.size(),\
    \ k = 0; i < e; ++i) {\n      os << rhs.mat_[i];\n      if (++k == n) {\n    \
    \    k = 0;\n        std::cout << '\\n';\n      } else {\n        std::cout <<\
    \ ' ';\n      }\n    }\n    return os;\n  }\n\n  friend Matrix operator+(const\
    \ Matrix &lhs, const Matrix &rhs) { return Matrix(lhs) += rhs; }\n  friend Matrix\
    \ operator-(const Matrix &lhs, const Matrix &rhs) { return Matrix(lhs) -= rhs;\
    \ }\n  friend Matrix operator*(const Matrix &lhs, const Matrix &rhs) { return\
    \ Matrix(lhs) *= rhs; }\n\n  /**\n   * @brief \u57DF\u4E0A\u7684\u65B9\u9635\u9006\
    \u5143\n   * @note \u4F7F\u7528 Gauss-Jordan \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\
    \uFF0C\u6240\u4EE5\u5143\u7D20\u9700\u8981\u5C5E\u4E8E\u57DF\n   * @return Matrix\n\
    \   */\n  Matrix inv() const {\n    int n = row();\n    assert(col() == n);\n\
    \    Matrix extmat(n, n << 1, Type(0)), res(n, n);\n    for (int i = 0; i < n;\
    \ ++i) std::copy(row_begin(i), row_end(i), extmat.row_begin(i));\n    for (int\
    \ i = 0; i < n; ++i) extmat.at(i, i + n) = Type(1);\n    /*\n      [ x x x x |\
    \ 1 0 0 0 ] => [ 1 0 0 0 | x x x x ]\n      [ x x x x | 0 1 0 0 ] => [ 0 1 0 0\
    \ | x x x x ]\n      [ x x x x | 0 0 1 0 ] => [ 0 0 1 0 | x x x x ]\n      [ x\
    \ x x x | 0 0 0 1 ] => [ 0 0 0 1 | x x x x ]\n    */\n    // \u5148\u5C06\u5DE6\
    \u8FB9\u77E9\u9635\u6D88\u5143\u4E3A\u4E0A\u4E09\u89D2\u77E9\u9635\u4E14\u4E3B\
    \u5BF9\u89D2\u7EBF\u4E3A 1 \u518D\u4E0B\u9762\u5F80\u4E0A\u5C06\u8BE5\u77E9\u9635\
    \u6D88\u4E3A diag(1,1,1 ...)\n    {\n      for (int i = 0; i < n; ++i) {     \
    \  // \u7B2C\u4E00\u9636\u6BB5\n        if (extmat.at(i, i) == Type(0)) { // \u9009\
    \u4E3B\u5143\n          int pivot = i + 1;\n          for (; pivot < n; ++pivot)\n\
    \            if (extmat.at(pivot, i) != Type(0)) break;\n          if (pivot ==\
    \ n) return Matrix(0, 0); // \u4E0D\u5B58\u5728\u9006\u77E9\u9635\n          std::swap_ranges(extmat.row_begin(i)\
    \ + i, extmat.row_end(i),\n                           extmat.row_begin(pivot)\
    \ + i); // \u4EA4\u6362\u884C\n        }\n        if (extmat.at(i, i) != Type(1))\
    \ {\n          Type iv = Type(1) / extmat.at(i, i);\n          std::for_each(extmat.row_begin(i)\
    \ + i, extmat.row_end(i), [iv](Type &a) { a *= iv; });\n        }\n        for\
    \ (int j = i + 1; j < n; ++j) {\n          Type p = extmat.at(j, i);\n       \
    \   if (p == Type(0)) continue;\n          extmat.at(j, i) = Type(0);\n      \
    \    for (int k = i + 1; k < (n << 1); ++k) extmat.at(j, k) -= p * extmat.at(i,\
    \ k);\n        }\n      }\n      for (int i = n - 2; i >= 0; --i) { // \u7B2C\u4E8C\
    \u9636\u6BB5\n        for (int j = i; j >= 0; --j) {\n          Type p = extmat.at(j,\
    \ i + 1);\n          if (p == Type(0)) continue;\n          extmat.at(j, i + 1)\
    \ = Type(0);\n          for (int k = i + 2; k < (n << 1); ++k) extmat.at(j, k)\
    \ -= p * extmat.at(i + 1, k);\n        }\n      }\n    }\n    for (int i = 0;\
    \ i < n; ++i)\n      std::copy(extmat.row_begin(i) + n, extmat.row_end(i), res.row_begin(i));\n\
    \    return res;\n  }\n\n  Type det() const;\n  int rank() const;\n\nprivate:\n\
    \  int row_, col_;\n  Container mat_;\n};\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/matrix_basic.hpp
  requiredBy: []
  timestamp: '2021-06-22 07:36:50+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/inverse_matrix.0.test.cpp
  - remote_test/yosupo/math/matrix_product.0.test.cpp
documentation_of: math/matrix/matrix_basic.hpp
layout: document
redirect_from:
- /library/math/matrix/matrix_basic.hpp
- /library/math/matrix/matrix_basic.hpp.html
title: "matrix basic / \u77E9\u9635\u57FA\u7840"
---
