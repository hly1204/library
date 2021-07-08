---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix_base.hpp
    title: "matrix base / \u77E9\u9635\u57FA\u7C7B"
  - icon: ':heavy_check_mark:'
    path: math/matrix/square_matrix.hpp
    title: "square matrix / \u65B9\u9635"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/matrix_det.2.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/math/matrix/arbitrary_modulo_square_matrix.md
    document_title: "arbitrary modulo square matrix / \u4EFB\u610F\u6A21\u6570\u65B9\
      \u9635"
    links: []
  bundledCode: "#line 1 \"math/matrix/arbitrary_modulo_square_matrix.hpp\"\n\n\n\n\
    /**\n * @brief arbitrary modulo square matrix / \u4EFB\u610F\u6A21\u6570\u65B9\
    \u9635\n * @docs docs/math/matrix/arbitrary_modulo_square_matrix.md\n */\n\n#line\
    \ 1 \"math/matrix/square_matrix.hpp\"\n\n\n\n/**\n * @brief square matrix / \u65B9\
    \u9635\n *\n */\n\n#include <optional>\n\n#line 1 \"math/matrix/matrix_base.hpp\"\
    \n\n\n\n/**\n * @brief matrix base / \u77E9\u9635\u57FA\u7C7B\n *\n */\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <numeric>\n#include\
    \ <vector>\n\nnamespace lib {\n\ntemplate <typename Type> class Matrix {\npublic:\n\
    \  using value_type = Type;\n\n  /**\n   * @brief Matrix \u7C7B\n   *\n   * @param\
    \ r \u884C\n   * @param c \u5217\n   * @param v \u521D\u503C\n   */\n  Matrix(int\
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
    \  int row_, col_;\n  std::vector<Type> mat_;\n};\n\n} // namespace lib\n\n\n\
    #line 12 \"math/matrix/square_matrix.hpp\"\n\nnamespace lib {\n\ntemplate <typename\
    \ Type> class SquareMatrix : public Matrix<Type> {\npublic:\n  SquareMatrix(int\
    \ r, const Type &v = Type()) : Matrix<Type>(r, r, v) {}\n  virtual ~SquareMatrix()\
    \ = default;\n\n  /**\n   * @brief \u57DF\u4E0A\u7684\u65B9\u9635\u9006\u5143\n\
    \   * @note \u4F7F\u7528 Gauss-Jordan \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\uFF0C\
    \u6240\u4EE5\u5143\u7D20\u9700\u8981\u5C5E\u4E8E\u57DF\n   * @return std::optional<SquareMatrix>\n\
    \   */\n  virtual std::optional<SquareMatrix> inv() const {\n    int n = this->row();\n\
    \    assert(this->col() == n);\n    Matrix aug(n, n << 1, Type(0));\n    SquareMatrix\
    \ res(n, n); // aug \u5373 augmented matrix \u589E\u5E7F\u77E9\u9635\n    for\
    \ (int i = 0; i < n; ++i) std::copy(this->row_begin(i), this->row_end(i), aug.row_begin(i));\n\
    \    for (int i = 0; i < n; ++i) aug.at(i, i + n) = Type(1);\n    /*\n      [\
    \ x x x x | 1 0 0 0 ] => [ 1 0 0 0 | x x x x ]\n      [ x x x x | 0 1 0 0 ] =>\
    \ [ 0 1 0 0 | x x x x ]\n      [ x x x x | 0 0 1 0 ] => [ 0 0 1 0 | x x x x ]\n\
    \      [ x x x x | 0 0 0 1 ] => [ 0 0 0 1 | x x x x ]\n    */\n    // \u5148\u5C06\
    \u5DE6\u8FB9\u77E9\u9635\u6D88\u5143\u4E3A\u4E0A\u4E09\u89D2\u77E9\u9635\u4E14\
    \u4E3B\u5BF9\u89D2\u7EBF\u4E3A 1 \u518D\u4E0B\u9762\u5F80\u4E0A\u5C06\u8BE5\u77E9\
    \u9635\u6D88\u4E3A diag(1,1,1 ...)\n    {\n      for (int i = 0; i < n; ++i) {\
    \    // \u7B2C\u4E00\u9636\u6BB5\n        if (aug.at(i, i) == Type(0)) { // \u9009\
    \u4E3B\u5143\n          int pivot = i + 1;\n          for (; pivot < n; ++pivot)\n\
    \            if (aug.at(pivot, i) != Type(0)) break;\n          if (pivot == n)\
    \ return {}; // \u4E0D\u5B58\u5728\u9006\u77E9\u9635\n          std::swap_ranges(aug.row_begin(i)\
    \ + i, aug.row_end(i),\n                           aug.row_begin(pivot) + i);\
    \ // \u4EA4\u6362\u884C\n        }\n        if (aug.at(i, i) != Type(1)) {\n \
    \         Type iv = Type(1) / aug.at(i, i);\n          std::for_each(aug.row_begin(i)\
    \ + i, aug.row_end(i), [iv](Type &a) { a *= iv; });\n        }\n        for (int\
    \ j = i + 1; j < n; ++j) {\n          Type p = aug.at(j, i);\n          if (p\
    \ == Type(0)) continue;\n          aug.at(j, i) = Type(0);\n          for (int\
    \ k = i + 1; k < (n << 1); ++k) aug.at(j, k) -= p * aug.at(i, k);\n        }\n\
    \      }\n      for (int i = n - 2; i >= 0; --i) { // \u7B2C\u4E8C\u9636\u6BB5\
    \n        for (int j = i; j >= 0; --j) {\n          Type p = aug.at(j, i + 1);\n\
    \          if (p == Type(0)) continue;\n          // \u8FD9\u91CC\u76F4\u63A5\u4ECE\
    \ n \u5F00\u59CB\u679A\u4E3E\u5373\u53EF\uFF0C\u800C\u975E i + 2 \uFF0C\u56E0\u4E3A\
    \ i + 2 \u5230 n - 1 \u90FD\u4E3A\u96F6\u4E86\n          for (int k = n; k < (n\
    \ << 1); ++k) aug.at(j, k) -= p * aug.at(i + 1, k);\n        }\n      }\n    }\n\
    \    for (int i = 0; i < n; ++i) std::copy(aug.row_begin(i) + n, aug.row_end(i),\
    \ res.row_begin(i));\n    return res;\n  }\n\n  /**\n   * @brief \u65B9\u9635\u7684\
    \u884C\u5217\u5F0F\n   * @note \u4F7F\u7528 Gauss \u6D88\u5143\uFF0C\u6709\u9664\
    \u6CD5\uFF0C\u6240\u4EE5\u5143\u7D20\u9700\u8981\u5C5E\u4E8E\u57DF\n   * @return\
    \ Type\n   */\n  virtual Type det() const {\n    int n = this->row();\n    assert(this->col()\
    \ == n);\n    SquareMatrix m(*this);\n    bool odd = false;\n    // \u5BF9\u77E9\
    \u9635 m \u7528 Gauss \u6D88\u5143\u6210\u4E0A\u4E09\u89D2\u77E9\u9635\uFF0C\u5176\
    \u5BF9\u89D2\u7EBF\u5143\u7D20\u7684\u79EF\u5373\u89E3\n    Type res(1); // 0x0\
    \ \u77E9\u9635\u7684\u884C\u5217\u5F0F\u4E5F\u4E3A 1\n    {\n      for (int i\
    \ = 0; i < n; ++i) {\n        if (m.at(i, i) == Type(0)) { // \u9009\u4E3B\u5143\
    \n          int pivot = i + 1;\n          for (; pivot < n; ++pivot)\n       \
    \     if (m.at(pivot, i) != Type(0)) break;\n          if (pivot == n) return\
    \ Type(0); // \u884C\u5217\u5F0F\u4E3A 0\n          std::swap_ranges(m.row_begin(i)\
    \ + i, m.row_end(i), m.row_begin(pivot) + i);\n          odd = !odd;\n       \
    \ }\n        res *= m.at(i, i);\n        Type iv = Type(1) / m.at(i, i);\n   \
    \     for (int j = i + 1; j < n; ++j) {\n          Type p = m.at(j, i) * iv;\n\
    \          m.at(j, i) = Type(0);\n          for (int k = i + 1; k < n; ++k) m.at(j,\
    \ k) -= p * m.at(i, k);\n        }\n      }\n    }\n    return odd ? -res : res;\n\
    \  }\n\n  /**\n   * @brief \u77E9\u9635\u7684\u79E9\n   * @note \u4F7F\u7528 Gauss\
    \ \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\uFF0C\u6240\u4EE5\u5143\u7D20\u9700\u8981\
    \u5C5E\u4E8E\u57DF\n   * @return int\n   */\n  virtual int rank() const {\n  \
    \  int n = this->row(), res = 0;\n    assert(this->col() == n);\n    SquareMatrix\
    \ m(*this);\n    {\n      for (int i = 0; i < n; ++i) {\n        if (m.at(i, i)\
    \ == Type(0)) { // \u9009\u4E3B\u5143\n          int pivot = i + 1;\n        \
    \  for (; pivot < n; ++pivot)\n            if (m.at(pivot, i) != Type(0)) break;\n\
    \          if (pivot == n) continue;\n          std::swap_ranges(m.row_begin(i)\
    \ + i, m.row_end(i), m.row_begin(pivot) + i);\n        }\n        ++res;\n   \
    \     Type iv = Type(1) / m.at(i, i);\n        for (int j = i + 1; j < n; ++j)\
    \ {\n          Type p = m.at(j, i) * iv;\n          m.at(j, i) = Type(0);\n  \
    \        for (int k = i + 1; k < n; ++k) m.at(j, k) -= p * m.at(i, k);\n     \
    \   }\n      }\n    }\n    return res;\n  }\n\n  /**\n   * @brief \u76F8\u4F3C\
    \u53D8\u6362\u4E3A\u4E0A Hessenberg \u65B9\u9635\n   * @note \u4F7F\u7528 Gauss\
    \ \u6D88\u5143\uFF0C\u6709\u9664\u6CD5\uFF0C\u6240\u4EE5\u5143\u7D20\u9700\u8981\
    \u5C5E\u4E8E\u57DF\n   * @return SquareMatrix\n   */\n  SquareMatrix to_upper_Hessenberg()\
    \ const {\n    int n = this->row();\n    assert(this->col() == n);\n    SquareMatrix\
    \ m(*this);\n    for (int i = 0; i < n - 2; ++i) {\n      if (m.at(i + 1, i) ==\
    \ Type(0)) {\n        int pivot = i + 2;\n        for (; pivot < n; ++pivot)\n\
    \          if (m.at(pivot, i) != Type(0)) break;\n        if (pivot == n) continue;\n\
    \        std::swap_ranges(m.row_begin(i + 1) + i, m.row_end(i + 1), m.row_begin(pivot)\
    \ + i);\n        for (int j = 0; j < n; ++j) std::swap(m.at(j, i + 1), m.at(j,\
    \ pivot));\n      }\n      Type iv = Type(1) / m.at(i + 1, i);\n      for (int\
    \ j = i + 2; j < n; ++j) {\n        if (m.at(j, i) == Type(0)) continue;\n   \
    \     Type v = m.at(j, i) * iv;\n        for (int k = i; k < n; ++k) m.at(j, k)\
    \ -= v * m.at(i + 1, k);\n        for (int k = 0; k != n; ++k) m.at(k, i + 1)\
    \ += v * m.at(k, j);\n      }\n    }\n    return m;\n  }\n\n  friend std::istream\
    \ &operator>>(std::istream &is, SquareMatrix &rhs) {\n    for (auto &i : rhs.mat_)\
    \ is >> i;\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const SquareMatrix &rhs) {\n    int n = rhs.col();\n    for (int i = 0,\
    \ e = rhs.size(), k = 0; i < e; ++i) {\n      os << rhs.mat_[i];\n      if (++k\
    \ == n) {\n        k = 0;\n        std::cout << '\\n';\n      } else {\n     \
    \   std::cout << ' ';\n      }\n    }\n    return os;\n  }\n};\n\n} // namespace\
    \ lib\n\n\n#line 10 \"math/matrix/arbitrary_modulo_square_matrix.hpp\"\n\nnamespace\
    \ lib {\n\ntemplate <typename Type> class ArbitraryModuloSquareMatrix : public\
    \ SquareMatrix<Type> {\npublic:\n  using base = SquareMatrix<Type>;\n  using base::base;\n\
    \n  virtual ~ArbitraryModuloSquareMatrix() = default;\n  virtual int rank() const\
    \ override {\n\n    using raw_type = typename Type::value_type;\n\n    int n =\
    \ this->row(), res = 0;\n    assert(this->col() == n);\n    ArbitraryModuloSquareMatrix\
    \ m(*this);\n    std::vector<int> real_row(n);\n    for (int i = 0; i < n; ++i)\
    \ real_row[i] = i;\n    // \u5BF9\u77E9\u9635 m \u7528 Gauss \u6D88\u5143\u6210\
    \u4E0A\u4E09\u89D2\u77E9\u9635\n    {\n      for (int i = 0; i < n; ++i) {\n \
    \       int pivot = -1;\n        raw_type min_value;\n        for (int j = i;\
    \ j < n; ++j) { // \u9009\u4E3B\u5143\uFF0C\u4E3B\u5143\u9009\u62E9\u6570\u503C\
    \u6700\u5C0F\u7684\u975E\u96F6\n          int real_j = real_row[j];\n        \
    \  if (m.at(real_j, i) != Type(0) &&\n              (pivot == -1 || raw_type(m.at(real_j,\
    \ i)) < min_value)) {\n            min_value = raw_type(m.at(real_j, i));\n  \
    \          pivot = j;\n          }\n        }\n        if (pivot == -1) continue;\n\
    \        ++res;\n        if (real_row[pivot] != real_row[i]) std::swap(real_row[i],\
    \ real_row[pivot]);\n        for (int j = i + 1; j < n; ++j) {\n          while\
    \ (m.at(real_row[j], i) != Type(0)) {\n            if (raw_type(m.at(real_row[j],\
    \ i)) < raw_type(m.at(real_row[i], i)))\n              std::swap(real_row[i],\
    \ real_row[j]);\n            int real_i = real_row[i], real_j = real_row[j];\n\
    \            Type p(raw_type(m.at(real_j, i)) / raw_type(m.at(real_i, i)));\n\
    \            for (int k = i; k < n; ++k) m.at(real_j, k) -= p * m.at(real_i, k);\n\
    \          }\n        }\n      }\n    }\n    return res;\n  }\n  virtual Type\
    \ det() const override {\n\n    using raw_type = typename Type::value_type;\n\n\
    \    int n = this->row();\n    assert(this->col() == n);\n    ArbitraryModuloSquareMatrix\
    \ m(*this);\n    bool odd = false;\n    std::vector<int> real_row(n);\n    for\
    \ (int i = 0; i < n; ++i) real_row[i] = i;\n    // \u5BF9\u77E9\u9635 m \u7528\
    \ Gauss \u6D88\u5143\u6210\u4E0A\u4E09\u89D2\u77E9\u9635\uFF0C\u5176\u5BF9\u89D2\
    \u7EBF\u5143\u7D20\u7684\u79EF\u5373\u89E3\n    Type res(1); // 0x0 \u77E9\u9635\
    \u7684\u884C\u5217\u5F0F\u4E5F\u4E3A 1\n    {\n      for (int i = 0; i < n; ++i)\
    \ {\n        int pivot = -1;\n        raw_type min_value;\n        for (int j\
    \ = i; j < n; ++j) { // \u9009\u4E3B\u5143\uFF0C\u4E3B\u5143\u9009\u62E9\u6570\
    \u503C\u6700\u5C0F\u7684\u975E\u96F6\n          int real_j = real_row[j];\n  \
    \        if (m.at(real_j, i) != Type(0) &&\n              (pivot == -1 || raw_type(m.at(real_j,\
    \ i)) < min_value)) {\n            min_value = raw_type(m.at(real_j, i));\n  \
    \          pivot = j;\n          }\n        }\n        if (pivot == -1) return\
    \ Type(0);\n        if (real_row[pivot] != real_row[i]) {\n          std::swap(real_row[i],\
    \ real_row[pivot]);\n          odd = !odd;\n        }\n        for (int j = i\
    \ + 1; j < n; ++j) {\n          while (m.at(real_row[j], i) != Type(0)) {\n  \
    \          if (raw_type(m.at(real_row[j], i)) < raw_type(m.at(real_row[i], i)))\
    \ {\n              std::swap(real_row[i], real_row[j]);\n              odd = !odd;\n\
    \            }\n            int real_i = real_row[i], real_j = real_row[j];\n\
    \            Type p(raw_type(m.at(real_j, i)) / raw_type(m.at(real_i, i)));\n\
    \            for (int k = i; k < n; ++k) m.at(real_j, k) -= p * m.at(real_i, k);\n\
    \          }\n        }\n        res *= m.at(real_row[i], i);\n      }\n    }\n\
    \    return odd ? -res : res;\n  }\n\n  virtual ArbitraryModuloSquareMatrix to_upper_Hessenberg()\
    \ const {\n\n    using raw_type = typename Type::value_type;\n\n    int n = this->row();\n\
    \    assert(this->col() == n);\n    ArbitraryModuloSquareMatrix m(*this);\n  \
    \  for (int i = 0; i < n - 2; ++i) {\n      int pivot = -1;\n      raw_type min_value;\n\
    \      for (int j = i + 1; j < n; ++j) { // \u9009\u4E3B\u5143\uFF0C\u4E3B\u5143\
    \u9009\u62E9\u6570\u503C\u6700\u5C0F\u7684\u975E\u96F6\n        if (m.at(j, i)\
    \ != Type(0) && (pivot == -1 || raw_type(m.at(j, i)) < min_value)) {\n       \
    \   min_value = raw_type(m.at(j, i));\n          pivot = j;\n        }\n     \
    \ }\n      if (pivot == -1) continue;\n      if (pivot != i + 1) {\n        std::swap_ranges(m.row_begin(i\
    \ + 1) + i, m.row_end(i + 1), m.row_begin(pivot) + i);\n        for (int j = 0;\
    \ j < n; ++j) std::swap(m.at(j, i + 1), m.at(j, pivot));\n      }\n      for (int\
    \ j = i + 2; j < n; ++j) {\n        while (m.at(j, i) != Type(0)) {\n        \
    \  if (raw_type(m.at(j, i)) < raw_type(m.at(i + 1, i))) {\n            std::swap_ranges(m.row_begin(i\
    \ + 1) + i, m.row_end(i + 1), m.row_begin(j) + i);\n            for (int k = 0;\
    \ k < n; ++k) std::swap(m.at(k, i + 1), m.at(k, j));\n          }\n          Type\
    \ v(raw_type(m.at(j, i)) / raw_type(m.at(i + 1, i)));\n          for (int k =\
    \ i; k < n; ++k) m.at(j, k) -= v * m.at(i + 1, k);\n          for (int k = 0;\
    \ k != n; ++k) m.at(k, i + 1) += v * m.at(k, j);\n        }\n      }\n    }\n\
    \    return m;\n  }\n\n  friend std::istream &operator>>(std::istream &is, ArbitraryModuloSquareMatrix\
    \ &rhs) {\n    for (auto &i : rhs.mat_) is >> i;\n    return is;\n  }\n  friend\
    \ std::ostream &operator<<(std::ostream &os, const ArbitraryModuloSquareMatrix\
    \ &rhs) {\n    int n = rhs.col();\n    for (int i = 0, e = rhs.size(), k = 0;\
    \ i < e; ++i) {\n      os << rhs.mat_[i];\n      if (++k == n) {\n        k =\
    \ 0;\n        std::cout << '\\n';\n      } else {\n        std::cout << ' ';\n\
    \      }\n    }\n    return os;\n  }\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef ARBITRARY_MODULO_SQUARE_MATRIX_HEADER_HPP\n#define ARBITRARY_MODULO_SQUARE_MATRIX_HEADER_HPP\n\
    \n/**\n * @brief arbitrary modulo square matrix / \u4EFB\u610F\u6A21\u6570\u65B9\
    \u9635\n * @docs docs/math/matrix/arbitrary_modulo_square_matrix.md\n */\n\n#include\
    \ \"square_matrix.hpp\"\n\nnamespace lib {\n\ntemplate <typename Type> class ArbitraryModuloSquareMatrix\
    \ : public SquareMatrix<Type> {\npublic:\n  using base = SquareMatrix<Type>;\n\
    \  using base::base;\n\n  virtual ~ArbitraryModuloSquareMatrix() = default;\n\
    \  virtual int rank() const override {\n\n    using raw_type = typename Type::value_type;\n\
    \n    int n = this->row(), res = 0;\n    assert(this->col() == n);\n    ArbitraryModuloSquareMatrix\
    \ m(*this);\n    std::vector<int> real_row(n);\n    for (int i = 0; i < n; ++i)\
    \ real_row[i] = i;\n    // \u5BF9\u77E9\u9635 m \u7528 Gauss \u6D88\u5143\u6210\
    \u4E0A\u4E09\u89D2\u77E9\u9635\n    {\n      for (int i = 0; i < n; ++i) {\n \
    \       int pivot = -1;\n        raw_type min_value;\n        for (int j = i;\
    \ j < n; ++j) { // \u9009\u4E3B\u5143\uFF0C\u4E3B\u5143\u9009\u62E9\u6570\u503C\
    \u6700\u5C0F\u7684\u975E\u96F6\n          int real_j = real_row[j];\n        \
    \  if (m.at(real_j, i) != Type(0) &&\n              (pivot == -1 || raw_type(m.at(real_j,\
    \ i)) < min_value)) {\n            min_value = raw_type(m.at(real_j, i));\n  \
    \          pivot = j;\n          }\n        }\n        if (pivot == -1) continue;\n\
    \        ++res;\n        if (real_row[pivot] != real_row[i]) std::swap(real_row[i],\
    \ real_row[pivot]);\n        for (int j = i + 1; j < n; ++j) {\n          while\
    \ (m.at(real_row[j], i) != Type(0)) {\n            if (raw_type(m.at(real_row[j],\
    \ i)) < raw_type(m.at(real_row[i], i)))\n              std::swap(real_row[i],\
    \ real_row[j]);\n            int real_i = real_row[i], real_j = real_row[j];\n\
    \            Type p(raw_type(m.at(real_j, i)) / raw_type(m.at(real_i, i)));\n\
    \            for (int k = i; k < n; ++k) m.at(real_j, k) -= p * m.at(real_i, k);\n\
    \          }\n        }\n      }\n    }\n    return res;\n  }\n  virtual Type\
    \ det() const override {\n\n    using raw_type = typename Type::value_type;\n\n\
    \    int n = this->row();\n    assert(this->col() == n);\n    ArbitraryModuloSquareMatrix\
    \ m(*this);\n    bool odd = false;\n    std::vector<int> real_row(n);\n    for\
    \ (int i = 0; i < n; ++i) real_row[i] = i;\n    // \u5BF9\u77E9\u9635 m \u7528\
    \ Gauss \u6D88\u5143\u6210\u4E0A\u4E09\u89D2\u77E9\u9635\uFF0C\u5176\u5BF9\u89D2\
    \u7EBF\u5143\u7D20\u7684\u79EF\u5373\u89E3\n    Type res(1); // 0x0 \u77E9\u9635\
    \u7684\u884C\u5217\u5F0F\u4E5F\u4E3A 1\n    {\n      for (int i = 0; i < n; ++i)\
    \ {\n        int pivot = -1;\n        raw_type min_value;\n        for (int j\
    \ = i; j < n; ++j) { // \u9009\u4E3B\u5143\uFF0C\u4E3B\u5143\u9009\u62E9\u6570\
    \u503C\u6700\u5C0F\u7684\u975E\u96F6\n          int real_j = real_row[j];\n  \
    \        if (m.at(real_j, i) != Type(0) &&\n              (pivot == -1 || raw_type(m.at(real_j,\
    \ i)) < min_value)) {\n            min_value = raw_type(m.at(real_j, i));\n  \
    \          pivot = j;\n          }\n        }\n        if (pivot == -1) return\
    \ Type(0);\n        if (real_row[pivot] != real_row[i]) {\n          std::swap(real_row[i],\
    \ real_row[pivot]);\n          odd = !odd;\n        }\n        for (int j = i\
    \ + 1; j < n; ++j) {\n          while (m.at(real_row[j], i) != Type(0)) {\n  \
    \          if (raw_type(m.at(real_row[j], i)) < raw_type(m.at(real_row[i], i)))\
    \ {\n              std::swap(real_row[i], real_row[j]);\n              odd = !odd;\n\
    \            }\n            int real_i = real_row[i], real_j = real_row[j];\n\
    \            Type p(raw_type(m.at(real_j, i)) / raw_type(m.at(real_i, i)));\n\
    \            for (int k = i; k < n; ++k) m.at(real_j, k) -= p * m.at(real_i, k);\n\
    \          }\n        }\n        res *= m.at(real_row[i], i);\n      }\n    }\n\
    \    return odd ? -res : res;\n  }\n\n  virtual ArbitraryModuloSquareMatrix to_upper_Hessenberg()\
    \ const {\n\n    using raw_type = typename Type::value_type;\n\n    int n = this->row();\n\
    \    assert(this->col() == n);\n    ArbitraryModuloSquareMatrix m(*this);\n  \
    \  for (int i = 0; i < n - 2; ++i) {\n      int pivot = -1;\n      raw_type min_value;\n\
    \      for (int j = i + 1; j < n; ++j) { // \u9009\u4E3B\u5143\uFF0C\u4E3B\u5143\
    \u9009\u62E9\u6570\u503C\u6700\u5C0F\u7684\u975E\u96F6\n        if (m.at(j, i)\
    \ != Type(0) && (pivot == -1 || raw_type(m.at(j, i)) < min_value)) {\n       \
    \   min_value = raw_type(m.at(j, i));\n          pivot = j;\n        }\n     \
    \ }\n      if (pivot == -1) continue;\n      if (pivot != i + 1) {\n        std::swap_ranges(m.row_begin(i\
    \ + 1) + i, m.row_end(i + 1), m.row_begin(pivot) + i);\n        for (int j = 0;\
    \ j < n; ++j) std::swap(m.at(j, i + 1), m.at(j, pivot));\n      }\n      for (int\
    \ j = i + 2; j < n; ++j) {\n        while (m.at(j, i) != Type(0)) {\n        \
    \  if (raw_type(m.at(j, i)) < raw_type(m.at(i + 1, i))) {\n            std::swap_ranges(m.row_begin(i\
    \ + 1) + i, m.row_end(i + 1), m.row_begin(j) + i);\n            for (int k = 0;\
    \ k < n; ++k) std::swap(m.at(k, i + 1), m.at(k, j));\n          }\n          Type\
    \ v(raw_type(m.at(j, i)) / raw_type(m.at(i + 1, i)));\n          for (int k =\
    \ i; k < n; ++k) m.at(j, k) -= v * m.at(i + 1, k);\n          for (int k = 0;\
    \ k != n; ++k) m.at(k, i + 1) += v * m.at(k, j);\n        }\n      }\n    }\n\
    \    return m;\n  }\n\n  friend std::istream &operator>>(std::istream &is, ArbitraryModuloSquareMatrix\
    \ &rhs) {\n    for (auto &i : rhs.mat_) is >> i;\n    return is;\n  }\n  friend\
    \ std::ostream &operator<<(std::ostream &os, const ArbitraryModuloSquareMatrix\
    \ &rhs) {\n    int n = rhs.col();\n    for (int i = 0, e = rhs.size(), k = 0;\
    \ i < e; ++i) {\n      os << rhs.mat_[i];\n      if (++k == n) {\n        k =\
    \ 0;\n        std::cout << '\\n';\n      } else {\n        std::cout << ' ';\n\
    \      }\n    }\n    return os;\n  }\n};\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - math/matrix/square_matrix.hpp
  - math/matrix/matrix_base.hpp
  isVerificationFile: false
  path: math/matrix/arbitrary_modulo_square_matrix.hpp
  requiredBy: []
  timestamp: '2021-07-09 03:49:04+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
  - remote_test/yosupo/matrix/matrix_det.2.test.cpp
documentation_of: math/matrix/arbitrary_modulo_square_matrix.hpp
layout: document
redirect_from:
- /library/math/matrix/arbitrary_modulo_square_matrix.hpp
- /library/math/matrix/arbitrary_modulo_square_matrix.hpp.html
title: "arbitrary modulo square matrix / \u4EFB\u610F\u6A21\u6570\u65B9\u9635"
---
## 任意模数方阵的高斯消元

在矩阵高斯消元的过程中，我们想利用第 $i$ 行去消去第 $j$ 行使得第 $j$ 行第 $i$ 个元素为零，此时因为没有办法使用乘法逆元（模数非素数），需要进行类似于辗转相除的过程，为了使得这个过程尽可能短，最好选择一列中“数值”非零且最小的当做主元。

同样的我们也可以使用这种方法使得任意模数的方阵变为上 Hessenberg 矩阵，而通过上 Hessenberg 矩阵求出特征多项式是没有除法的，沿用之前的方法即可。