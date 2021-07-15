---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix_base.hpp
    title: "matrix base / \u77E9\u9635\u57FA\u7C7B"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/matrix/arbitrary_modulo_square_matrix.hpp
    title: "arbitrary modulo square matrix / \u4EFB\u610F\u6A21\u6570\u65B9\u9635"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
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
    path: remote_test/yosupo/matrix/matrix_det.2.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "square matrix / \u65B9\u9635"
    links: []
  bundledCode: "#line 1 \"math/matrix/square_matrix.hpp\"\n\n\n\r\n/**\r\n * @brief\
    \ square matrix / \u65B9\u9635\r\n *\r\n */\r\n\r\n#include <optional>\r\n\r\n\
    #line 1 \"math/matrix/matrix_base.hpp\"\n\n\n\r\n/**\r\n * @brief matrix base\
    \ / \u77E9\u9635\u57FA\u7C7B\r\n *\r\n */\r\n\r\n#include <algorithm>\r\n#include\
    \ <cassert>\r\n#include <iostream>\r\n#include <numeric>\r\n#include <vector>\r\
    \n\r\nnamespace lib {\r\n\r\ntemplate <typename Type>\r\nclass Matrix {\r\npublic:\r\
    \n  using value_type = Type;\r\n\r\n  /**\r\n   * @brief Matrix \u7C7B\r\n   *\r\
    \n   * @param r \u884C\r\n   * @param c \u5217\r\n   * @param v \u521D\u503C\r\
    \n   */\r\n  Matrix(int r, int c, const Type &v = Type()) : row_(r), col_(c),\
    \ mat_(row_ * col_, v) {}\r\n  virtual ~Matrix()      = default;\r\n  Matrix(const\
    \ Matrix &) = default;\r\n\r\n  virtual Matrix &operator=(const Matrix &) = default;\r\
    \n\r\n  int row() const { return row_; }\r\n  int col() const { return col_; }\r\
    \n  int size() const { return row_ * col_; }\r\n  bool is_empty() const { return\
    \ size() == 0; }\r\n\r\n  decltype(auto) row_begin(int r) { return mat_.begin()\
    \ + r * col_; }\r\n  decltype(auto) row_cbegin(int r) const { return mat_.cbegin()\
    \ + r * col_; }\r\n  decltype(auto) row_begin(int r) const { return row_cbegin(r);\
    \ }\r\n  decltype(auto) row_end(int r) { return mat_.begin() + (r + 1) * col_;\
    \ }\r\n  decltype(auto) row_cend(int r) const { return mat_.cbegin() + (r + 1)\
    \ * col_; }\r\n  decltype(auto) row_end(int r) const { return row_cend(r); }\r\
    \n\r\n#ifdef LOCAL\r\n  Type &at(int r, int c) { return mat_.at(r * col_ + c);\
    \ }\r\n  const Type &at(int r, int c) const { return mat_.at(r * col_ + c); }\r\
    \n#else\r\n  Type &at(int r, int c) { return mat_[r * col_ + c]; }\r\n  const\
    \ Type &at(int r, int c) const { return mat_[r * col_ + c]; }\r\n#endif\r\n\r\n\
    \  virtual Matrix &operator+=(const Matrix &rhs) {\r\n    assert(row() == rhs.row());\r\
    \n    assert(col() == rhs.col());\r\n    for (int i = 0, n = size(); i < n; ++i)\
    \ mat_[i] -= rhs.mat_[i];\r\n    return *this;\r\n  }\r\n\r\n  virtual Matrix\
    \ &operator-=(const Matrix &rhs) {\r\n    assert(row() == rhs.row());\r\n    assert(col()\
    \ == rhs.col());\r\n    for (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];\r\
    \n    return *this;\r\n  }\r\n\r\n  virtual Matrix transpose() const {\r\n   \
    \ int n = row(), m = col();\r\n    Matrix res(m, n, Type(0));\r\n    for (int\
    \ i = 0; i < n; ++i)\r\n      for (int j = 0; j < m; ++j) res.at(j, i) = at(i,\
    \ j);\r\n    return res;\r\n  }\r\n\r\n  /**\r\n   * @brief \u8FD4\u56DE\u77E9\
    \u9635\u548C\u5217\u5411\u91CF x \u7684\u79EF\r\n   * @param x \u5217\u5411\u91CF\
    \ x \u6EE1\u8DB3 x \u7684\u884C\u6570\u7B49\u4E8E\u77E9\u9635\u7684\u5217\u6570\
    \r\n   * @return std::vector<Type>\r\n   */\r\n  virtual std::vector<Type> apply(const\
    \ std::vector<Type> &x) const {\r\n    assert(col() == x.size());\r\n    int n\
    \ = row();\r\n    std::vector<Type> res(n);\r\n    for (int i = 0; i < n; ++i)\r\
    \n      res[i] = std::inner_product(row_begin(i), row_end(i), x.begin(), Type(0));\r\
    \n    return res;\r\n  }\r\n\r\n  /**\r\n   * @brief \u77E9\u9635\u4E58\u6CD5\r\
    \n   * @param rhs \u53F3\u4E58\u7684\u77E9\u9635\r\n   * @return Matrix&\r\n \
    \  */\r\n  virtual Matrix &operator*=(const Matrix &rhs) {\r\n    int n = row(),\
    \ m = rhs.col(), l = col();\r\n    assert(l == rhs.row());\r\n    // n*l \u7684\
    \u77E9\u9635\u53F3\u4E58\u4E00\u4E2A l*m \u7684\u77E9\u9635\r\n    Matrix res(n,\
    \ m), trhs(rhs.transpose());\r\n    for (int i = 0; i < n; ++i)\r\n      for (int\
    \ j = 0; j < m; ++j)\r\n        res.at(i, j) = std::inner_product(row_begin(i),\
    \ row_end(i), trhs.row_begin(j), Type(0));\r\n    return this->operator=(res);\r\
    \n  }\r\n\r\n  virtual Matrix operator+(const Matrix &rhs) { return Matrix(*this)\
    \ += rhs; }\r\n  virtual Matrix operator-(const Matrix &rhs) { return Matrix(*this)\
    \ -= rhs; }\r\n  virtual Matrix operator*(const Matrix &rhs) { return Matrix(*this)\
    \ *= rhs; }\r\n\r\n  friend std::istream &operator>>(std::istream &is, Matrix\
    \ &rhs) {\r\n    for (auto &i : rhs.mat_) is >> i;\r\n    return is;\r\n  }\r\n\
    \  friend std::ostream &operator<<(std::ostream &os, const Matrix &rhs) {\r\n\
    \    int n = rhs.col();\r\n    for (int i = 0, e = rhs.size(), k = 0; i < e; ++i)\
    \ {\r\n      os << rhs.mat_[i];\r\n      if (++k == n) {\r\n        k = 0;\r\n\
    \        std::cout << '\\n';\r\n      } else {\r\n        std::cout << ' ';\r\n\
    \      }\r\n    }\r\n    return os;\r\n  }\r\n\r\nprotected:\r\n  int row_, col_;\r\
    \n  std::vector<Type> mat_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 12\
    \ \"math/matrix/square_matrix.hpp\"\n\r\nnamespace lib {\r\n\r\ntemplate <typename\
    \ Type>\r\nclass SquareMatrix : public Matrix<Type> {\r\npublic:\r\n  SquareMatrix(int\
    \ r, const Type &v = Type()) : Matrix<Type>(r, r, v) {}\r\n  virtual ~SquareMatrix()\
    \ = default;\r\n\r\n  /**\r\n   * @brief \u57DF\u4E0A\u7684\u65B9\u9635\u9006\u5143\
    \r\n   * @note \u4F7F\u7528 Gauss-Jordan \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\uFF0C\
    \u6240\u4EE5\u5143\u7D20\u9700\u8981\u5C5E\u4E8E\u57DF\r\n   * @return std::optional<SquareMatrix>\r\
    \n   */\r\n  virtual std::optional<SquareMatrix> inv() const {\r\n    int n =\
    \ this->row();\r\n    assert(this->col() == n);\r\n    Matrix aug(n, n << 1, Type(0));\r\
    \n    SquareMatrix res(n, n); // aug \u5373 augmented matrix \u589E\u5E7F\u77E9\
    \u9635\r\n    for (int i = 0; i < n; ++i) std::copy(this->row_begin(i), this->row_end(i),\
    \ aug.row_begin(i));\r\n    for (int i = 0; i < n; ++i) aug.at(i, i + n) = Type(1);\r\
    \n    /*\r\n      [ x x x x | 1 0 0 0 ] => [ 1 0 0 0 | x x x x ]\r\n      [ x\
    \ x x x | 0 1 0 0 ] => [ 0 1 0 0 | x x x x ]\r\n      [ x x x x | 0 0 1 0 ] =>\
    \ [ 0 0 1 0 | x x x x ]\r\n      [ x x x x | 0 0 0 1 ] => [ 0 0 0 1 | x x x x\
    \ ]\r\n    */\r\n    // \u5148\u5C06\u5DE6\u8FB9\u77E9\u9635\u6D88\u5143\u4E3A\
    \u4E0A\u4E09\u89D2\u77E9\u9635\u4E14\u4E3B\u5BF9\u89D2\u7EBF\u4E3A 1 \u518D\u4E0B\
    \u9762\u5F80\u4E0A\u5C06\u8BE5\u77E9\u9635\u6D88\u4E3A diag(1,1,1 ...)\r\n   \
    \ {\r\n      for (int i = 0; i < n; ++i) {    // \u7B2C\u4E00\u9636\u6BB5\r\n\
    \        if (aug.at(i, i) == Type(0)) { // \u9009\u4E3B\u5143\r\n          int\
    \ pivot = i + 1;\r\n          for (; pivot < n; ++pivot)\r\n            if (aug.at(pivot,\
    \ i) != Type(0)) break;\r\n          if (pivot == n) return {}; // \u4E0D\u5B58\
    \u5728\u9006\u77E9\u9635\r\n          std::swap_ranges(aug.row_begin(i) + i, aug.row_end(i),\r\
    \n                           aug.row_begin(pivot) + i); // \u4EA4\u6362\u884C\r\
    \n        }\r\n        if (aug.at(i, i) != Type(1)) {\r\n          Type iv = Type(1)\
    \ / aug.at(i, i);\r\n          std::for_each(aug.row_begin(i) + i, aug.row_end(i),\
    \ [iv](Type &a) { a *= iv; });\r\n        }\r\n        for (int j = i + 1; j <\
    \ n; ++j) {\r\n          Type p = aug.at(j, i);\r\n          if (p == Type(0))\
    \ continue;\r\n          aug.at(j, i) = Type(0);\r\n          for (int k = i +\
    \ 1; k < (n << 1); ++k) aug.at(j, k) -= p * aug.at(i, k);\r\n        }\r\n   \
    \   }\r\n      for (int i = n - 2; i >= 0; --i) { // \u7B2C\u4E8C\u9636\u6BB5\r\
    \n        for (int j = i; j >= 0; --j) {\r\n          Type p = aug.at(j, i + 1);\r\
    \n          if (p == Type(0)) continue;\r\n          // \u8FD9\u91CC\u76F4\u63A5\
    \u4ECE n \u5F00\u59CB\u679A\u4E3E\u5373\u53EF\uFF0C\u800C\u975E i + 2 \uFF0C\u56E0\
    \u4E3A i + 2 \u5230 n - 1 \u90FD\u4E3A\u96F6\u4E86\r\n          for (int k = n;\
    \ k < (n << 1); ++k) aug.at(j, k) -= p * aug.at(i + 1, k);\r\n        }\r\n  \
    \    }\r\n    }\r\n    for (int i = 0; i < n; ++i) std::copy(aug.row_begin(i)\
    \ + n, aug.row_end(i), res.row_begin(i));\r\n    return res;\r\n  }\r\n\r\n  /**\r\
    \n   * @brief \u65B9\u9635\u7684\u884C\u5217\u5F0F\r\n   * @note \u4F7F\u7528\
    \ Gauss \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\uFF0C\u6240\u4EE5\u5143\u7D20\u9700\
    \u8981\u5C5E\u4E8E\u57DF\r\n   * @return Type\r\n   */\r\n  virtual Type det()\
    \ const {\r\n    int n = this->row();\r\n    assert(this->col() == n);\r\n   \
    \ SquareMatrix m(*this);\r\n    bool odd = false;\r\n    // \u5BF9\u77E9\u9635\
    \ m \u7528 Gauss \u6D88\u5143\u6210\u4E0A\u4E09\u89D2\u77E9\u9635\uFF0C\u5176\u5BF9\
    \u89D2\u7EBF\u5143\u7D20\u7684\u79EF\u5373\u89E3\r\n    Type res(1); // 0x0 \u77E9\
    \u9635\u7684\u884C\u5217\u5F0F\u4E5F\u4E3A 1\r\n    {\r\n      for (int i = 0;\
    \ i < n; ++i) {\r\n        if (m.at(i, i) == Type(0)) { // \u9009\u4E3B\u5143\r\
    \n          int pivot = i + 1;\r\n          for (; pivot < n; ++pivot)\r\n   \
    \         if (m.at(pivot, i) != Type(0)) break;\r\n          if (pivot == n) return\
    \ Type(0); // \u884C\u5217\u5F0F\u4E3A 0\r\n          std::swap_ranges(m.row_begin(i)\
    \ + i, m.row_end(i), m.row_begin(pivot) + i);\r\n          odd = !odd;\r\n   \
    \     }\r\n        res *= m.at(i, i);\r\n        Type iv = Type(1) / m.at(i, i);\r\
    \n        for (int j = i + 1; j < n; ++j) {\r\n          Type p     = m.at(j,\
    \ i) * iv;\r\n          m.at(j, i) = Type(0);\r\n          for (int k = i + 1;\
    \ k < n; ++k) m.at(j, k) -= p * m.at(i, k);\r\n        }\r\n      }\r\n    }\r\
    \n    return odd ? -res : res;\r\n  }\r\n\r\n  /**\r\n   * @brief \u77E9\u9635\
    \u7684\u79E9\r\n   * @note \u4F7F\u7528 Gauss \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\
    \uFF0C\u6240\u4EE5\u5143\u7D20\u9700\u8981\u5C5E\u4E8E\u57DF\r\n   * @return int\r\
    \n   */\r\n  virtual int rank() const {\r\n    int n = this->row(), res = 0;\r\
    \n    assert(this->col() == n);\r\n    SquareMatrix m(*this);\r\n    {\r\n   \
    \   for (int i = 0; i < n; ++i) {\r\n        if (m.at(i, i) == Type(0)) { // \u9009\
    \u4E3B\u5143\r\n          int pivot = i + 1;\r\n          for (; pivot < n; ++pivot)\r\
    \n            if (m.at(pivot, i) != Type(0)) break;\r\n          if (pivot ==\
    \ n) continue;\r\n          std::swap_ranges(m.row_begin(i) + i, m.row_end(i),\
    \ m.row_begin(pivot) + i);\r\n        }\r\n        ++res;\r\n        Type iv =\
    \ Type(1) / m.at(i, i);\r\n        for (int j = i + 1; j < n; ++j) {\r\n     \
    \     Type p     = m.at(j, i) * iv;\r\n          m.at(j, i) = Type(0);\r\n   \
    \       for (int k = i + 1; k < n; ++k) m.at(j, k) -= p * m.at(i, k);\r\n    \
    \    }\r\n      }\r\n    }\r\n    return res;\r\n  }\r\n\r\n  /**\r\n   * @brief\
    \ \u76F8\u4F3C\u53D8\u6362\u4E3A\u4E0A Hessenberg \u65B9\u9635\r\n   * @note \u4F7F\
    \u7528 Gauss \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\uFF0C\u6240\u4EE5\u5143\u7D20\
    \u9700\u8981\u5C5E\u4E8E\u57DF\r\n   * @return SquareMatrix\r\n   */\r\n  SquareMatrix\
    \ to_upper_Hessenberg() const {\r\n    int n = this->row();\r\n    assert(this->col()\
    \ == n);\r\n    SquareMatrix m(*this);\r\n    for (int i = 0; i < n - 2; ++i)\
    \ {\r\n      if (m.at(i + 1, i) == Type(0)) {\r\n        int pivot = i + 2;\r\n\
    \        for (; pivot < n; ++pivot)\r\n          if (m.at(pivot, i) != Type(0))\
    \ break;\r\n        if (pivot == n) continue;\r\n        std::swap_ranges(m.row_begin(i\
    \ + 1) + i, m.row_end(i + 1), m.row_begin(pivot) + i);\r\n        for (int j =\
    \ 0; j < n; ++j) std::swap(m.at(j, i + 1), m.at(j, pivot));\r\n      }\r\n   \
    \   Type iv = Type(1) / m.at(i + 1, i);\r\n      for (int j = i + 2; j < n; ++j)\
    \ {\r\n        if (m.at(j, i) == Type(0)) continue;\r\n        Type v = m.at(j,\
    \ i) * iv;\r\n        for (int k = i; k < n; ++k) m.at(j, k) -= v * m.at(i + 1,\
    \ k);\r\n        for (int k = 0; k != n; ++k) m.at(k, i + 1) += v * m.at(k, j);\r\
    \n      }\r\n    }\r\n    return m;\r\n  }\r\n\r\n  friend std::istream &operator>>(std::istream\
    \ &is, SquareMatrix &rhs) {\r\n    for (auto &i : rhs.mat_) is >> i;\r\n    return\
    \ is;\r\n  }\r\n  friend std::ostream &operator<<(std::ostream &os, const SquareMatrix\
    \ &rhs) {\r\n    int n = rhs.col();\r\n    for (int i = 0, e = rhs.size(), k =\
    \ 0; i < e; ++i) {\r\n      os << rhs.mat_[i];\r\n      if (++k == n) {\r\n  \
    \      k = 0;\r\n        std::cout << '\\n';\r\n      } else {\r\n        std::cout\
    \ << ' ';\r\n      }\r\n    }\r\n    return os;\r\n  }\r\n};\r\n\r\n} // namespace\
    \ lib\r\n\r\n\n"
  code: "#ifndef SQUARE_MATRIX_HEADER_HPP\r\n#define SQUARE_MATRIX_HEADER_HPP\r\n\r\
    \n/**\r\n * @brief square matrix / \u65B9\u9635\r\n *\r\n */\r\n\r\n#include <optional>\r\
    \n\r\n#include \"math/matrix/matrix_base.hpp\"\r\n\r\nnamespace lib {\r\n\r\n\
    template <typename Type>\r\nclass SquareMatrix : public Matrix<Type> {\r\npublic:\r\
    \n  SquareMatrix(int r, const Type &v = Type()) : Matrix<Type>(r, r, v) {}\r\n\
    \  virtual ~SquareMatrix() = default;\r\n\r\n  /**\r\n   * @brief \u57DF\u4E0A\
    \u7684\u65B9\u9635\u9006\u5143\r\n   * @note \u4F7F\u7528 Gauss-Jordan \u6D88\u5143\
    \uFF0C\u6709\u9664\u6CD5\uFF0C\u6240\u4EE5\u5143\u7D20\u9700\u8981\u5C5E\u4E8E\
    \u57DF\r\n   * @return std::optional<SquareMatrix>\r\n   */\r\n  virtual std::optional<SquareMatrix>\
    \ inv() const {\r\n    int n = this->row();\r\n    assert(this->col() == n);\r\
    \n    Matrix aug(n, n << 1, Type(0));\r\n    SquareMatrix res(n, n); // aug \u5373\
    \ augmented matrix \u589E\u5E7F\u77E9\u9635\r\n    for (int i = 0; i < n; ++i)\
    \ std::copy(this->row_begin(i), this->row_end(i), aug.row_begin(i));\r\n    for\
    \ (int i = 0; i < n; ++i) aug.at(i, i + n) = Type(1);\r\n    /*\r\n      [ x x\
    \ x x | 1 0 0 0 ] => [ 1 0 0 0 | x x x x ]\r\n      [ x x x x | 0 1 0 0 ] => [\
    \ 0 1 0 0 | x x x x ]\r\n      [ x x x x | 0 0 1 0 ] => [ 0 0 1 0 | x x x x ]\r\
    \n      [ x x x x | 0 0 0 1 ] => [ 0 0 0 1 | x x x x ]\r\n    */\r\n    // \u5148\
    \u5C06\u5DE6\u8FB9\u77E9\u9635\u6D88\u5143\u4E3A\u4E0A\u4E09\u89D2\u77E9\u9635\
    \u4E14\u4E3B\u5BF9\u89D2\u7EBF\u4E3A 1 \u518D\u4E0B\u9762\u5F80\u4E0A\u5C06\u8BE5\
    \u77E9\u9635\u6D88\u4E3A diag(1,1,1 ...)\r\n    {\r\n      for (int i = 0; i <\
    \ n; ++i) {    // \u7B2C\u4E00\u9636\u6BB5\r\n        if (aug.at(i, i) == Type(0))\
    \ { // \u9009\u4E3B\u5143\r\n          int pivot = i + 1;\r\n          for (;\
    \ pivot < n; ++pivot)\r\n            if (aug.at(pivot, i) != Type(0)) break;\r\
    \n          if (pivot == n) return {}; // \u4E0D\u5B58\u5728\u9006\u77E9\u9635\
    \r\n          std::swap_ranges(aug.row_begin(i) + i, aug.row_end(i),\r\n     \
    \                      aug.row_begin(pivot) + i); // \u4EA4\u6362\u884C\r\n  \
    \      }\r\n        if (aug.at(i, i) != Type(1)) {\r\n          Type iv = Type(1)\
    \ / aug.at(i, i);\r\n          std::for_each(aug.row_begin(i) + i, aug.row_end(i),\
    \ [iv](Type &a) { a *= iv; });\r\n        }\r\n        for (int j = i + 1; j <\
    \ n; ++j) {\r\n          Type p = aug.at(j, i);\r\n          if (p == Type(0))\
    \ continue;\r\n          aug.at(j, i) = Type(0);\r\n          for (int k = i +\
    \ 1; k < (n << 1); ++k) aug.at(j, k) -= p * aug.at(i, k);\r\n        }\r\n   \
    \   }\r\n      for (int i = n - 2; i >= 0; --i) { // \u7B2C\u4E8C\u9636\u6BB5\r\
    \n        for (int j = i; j >= 0; --j) {\r\n          Type p = aug.at(j, i + 1);\r\
    \n          if (p == Type(0)) continue;\r\n          // \u8FD9\u91CC\u76F4\u63A5\
    \u4ECE n \u5F00\u59CB\u679A\u4E3E\u5373\u53EF\uFF0C\u800C\u975E i + 2 \uFF0C\u56E0\
    \u4E3A i + 2 \u5230 n - 1 \u90FD\u4E3A\u96F6\u4E86\r\n          for (int k = n;\
    \ k < (n << 1); ++k) aug.at(j, k) -= p * aug.at(i + 1, k);\r\n        }\r\n  \
    \    }\r\n    }\r\n    for (int i = 0; i < n; ++i) std::copy(aug.row_begin(i)\
    \ + n, aug.row_end(i), res.row_begin(i));\r\n    return res;\r\n  }\r\n\r\n  /**\r\
    \n   * @brief \u65B9\u9635\u7684\u884C\u5217\u5F0F\r\n   * @note \u4F7F\u7528\
    \ Gauss \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\uFF0C\u6240\u4EE5\u5143\u7D20\u9700\
    \u8981\u5C5E\u4E8E\u57DF\r\n   * @return Type\r\n   */\r\n  virtual Type det()\
    \ const {\r\n    int n = this->row();\r\n    assert(this->col() == n);\r\n   \
    \ SquareMatrix m(*this);\r\n    bool odd = false;\r\n    // \u5BF9\u77E9\u9635\
    \ m \u7528 Gauss \u6D88\u5143\u6210\u4E0A\u4E09\u89D2\u77E9\u9635\uFF0C\u5176\u5BF9\
    \u89D2\u7EBF\u5143\u7D20\u7684\u79EF\u5373\u89E3\r\n    Type res(1); // 0x0 \u77E9\
    \u9635\u7684\u884C\u5217\u5F0F\u4E5F\u4E3A 1\r\n    {\r\n      for (int i = 0;\
    \ i < n; ++i) {\r\n        if (m.at(i, i) == Type(0)) { // \u9009\u4E3B\u5143\r\
    \n          int pivot = i + 1;\r\n          for (; pivot < n; ++pivot)\r\n   \
    \         if (m.at(pivot, i) != Type(0)) break;\r\n          if (pivot == n) return\
    \ Type(0); // \u884C\u5217\u5F0F\u4E3A 0\r\n          std::swap_ranges(m.row_begin(i)\
    \ + i, m.row_end(i), m.row_begin(pivot) + i);\r\n          odd = !odd;\r\n   \
    \     }\r\n        res *= m.at(i, i);\r\n        Type iv = Type(1) / m.at(i, i);\r\
    \n        for (int j = i + 1; j < n; ++j) {\r\n          Type p     = m.at(j,\
    \ i) * iv;\r\n          m.at(j, i) = Type(0);\r\n          for (int k = i + 1;\
    \ k < n; ++k) m.at(j, k) -= p * m.at(i, k);\r\n        }\r\n      }\r\n    }\r\
    \n    return odd ? -res : res;\r\n  }\r\n\r\n  /**\r\n   * @brief \u77E9\u9635\
    \u7684\u79E9\r\n   * @note \u4F7F\u7528 Gauss \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\
    \uFF0C\u6240\u4EE5\u5143\u7D20\u9700\u8981\u5C5E\u4E8E\u57DF\r\n   * @return int\r\
    \n   */\r\n  virtual int rank() const {\r\n    int n = this->row(), res = 0;\r\
    \n    assert(this->col() == n);\r\n    SquareMatrix m(*this);\r\n    {\r\n   \
    \   for (int i = 0; i < n; ++i) {\r\n        if (m.at(i, i) == Type(0)) { // \u9009\
    \u4E3B\u5143\r\n          int pivot = i + 1;\r\n          for (; pivot < n; ++pivot)\r\
    \n            if (m.at(pivot, i) != Type(0)) break;\r\n          if (pivot ==\
    \ n) continue;\r\n          std::swap_ranges(m.row_begin(i) + i, m.row_end(i),\
    \ m.row_begin(pivot) + i);\r\n        }\r\n        ++res;\r\n        Type iv =\
    \ Type(1) / m.at(i, i);\r\n        for (int j = i + 1; j < n; ++j) {\r\n     \
    \     Type p     = m.at(j, i) * iv;\r\n          m.at(j, i) = Type(0);\r\n   \
    \       for (int k = i + 1; k < n; ++k) m.at(j, k) -= p * m.at(i, k);\r\n    \
    \    }\r\n      }\r\n    }\r\n    return res;\r\n  }\r\n\r\n  /**\r\n   * @brief\
    \ \u76F8\u4F3C\u53D8\u6362\u4E3A\u4E0A Hessenberg \u65B9\u9635\r\n   * @note \u4F7F\
    \u7528 Gauss \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\uFF0C\u6240\u4EE5\u5143\u7D20\
    \u9700\u8981\u5C5E\u4E8E\u57DF\r\n   * @return SquareMatrix\r\n   */\r\n  SquareMatrix\
    \ to_upper_Hessenberg() const {\r\n    int n = this->row();\r\n    assert(this->col()\
    \ == n);\r\n    SquareMatrix m(*this);\r\n    for (int i = 0; i < n - 2; ++i)\
    \ {\r\n      if (m.at(i + 1, i) == Type(0)) {\r\n        int pivot = i + 2;\r\n\
    \        for (; pivot < n; ++pivot)\r\n          if (m.at(pivot, i) != Type(0))\
    \ break;\r\n        if (pivot == n) continue;\r\n        std::swap_ranges(m.row_begin(i\
    \ + 1) + i, m.row_end(i + 1), m.row_begin(pivot) + i);\r\n        for (int j =\
    \ 0; j < n; ++j) std::swap(m.at(j, i + 1), m.at(j, pivot));\r\n      }\r\n   \
    \   Type iv = Type(1) / m.at(i + 1, i);\r\n      for (int j = i + 2; j < n; ++j)\
    \ {\r\n        if (m.at(j, i) == Type(0)) continue;\r\n        Type v = m.at(j,\
    \ i) * iv;\r\n        for (int k = i; k < n; ++k) m.at(j, k) -= v * m.at(i + 1,\
    \ k);\r\n        for (int k = 0; k != n; ++k) m.at(k, i + 1) += v * m.at(k, j);\r\
    \n      }\r\n    }\r\n    return m;\r\n  }\r\n\r\n  friend std::istream &operator>>(std::istream\
    \ &is, SquareMatrix &rhs) {\r\n    for (auto &i : rhs.mat_) is >> i;\r\n    return\
    \ is;\r\n  }\r\n  friend std::ostream &operator<<(std::ostream &os, const SquareMatrix\
    \ &rhs) {\r\n    int n = rhs.col();\r\n    for (int i = 0, e = rhs.size(), k =\
    \ 0; i < e; ++i) {\r\n      os << rhs.mat_[i];\r\n      if (++k == n) {\r\n  \
    \      k = 0;\r\n        std::cout << '\\n';\r\n      } else {\r\n        std::cout\
    \ << ' ';\r\n      }\r\n    }\r\n    return os;\r\n  }\r\n};\r\n\r\n} // namespace\
    \ lib\r\n\r\n#endif\r\n"
  dependsOn:
  - math/matrix/matrix_base.hpp
  isVerificationFile: false
  path: math/matrix/square_matrix.hpp
  requiredBy:
  - math/matrix/arbitrary_modulo_square_matrix.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/matrix/matrix_det.0.test.cpp
  - remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
  - remote_test/yosupo/matrix/matrix_det.1.test.cpp
  - remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
  - remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
  - remote_test/yosupo/matrix/matrix_det.2.test.cpp
documentation_of: math/matrix/square_matrix.hpp
layout: document
redirect_from:
- /library/math/matrix/square_matrix.hpp
- /library/math/matrix/square_matrix.hpp.html
title: "square matrix / \u65B9\u9635"
---
