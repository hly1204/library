---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/matrix/black_box_linear_algebra.hpp
    title: "black box linear algebra / \u9ED1\u76D2\u7EBF\u6027\u4EE3\u6570"
  - icon: ':x:'
    path: math/matrix/matrix_base.hpp
    title: "matrix base / \u77E9\u9635\u57FA\u7C7B"
  - icon: ':x:'
    path: math/matrix/square_matrix.hpp
    title: "square matrix / \u65B9\u9635"
  - icon: ':question:'
    path: math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
    title: "find shortest LFSR Berlekamp-Massey / \u5BFB\u627E\u6700\u77ED\u7EBF\u6027\
      \u9012\u63A8 Berlekamp-Massey \u7B97\u6CD5"
  - icon: ':question:'
    path: modint/Montgomery_modint.hpp
    title: "Montgomery modint / Montgomery \u53D6\u6A21\u7C7B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/matrix_det
    links:
    - https://judge.yosupo.jp/problem/matrix_det
  bundledCode: "#line 1 \"remote_test/yosupo/matrix/matrix_det.1.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/matrix_det\"\r\n\r\n#include <iostream>\r\
    \n\r\n#line 1 \"math/matrix/black_box_linear_algebra.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief black box linear algebra / \u9ED1\u76D2\u7EBF\u6027\u4EE3\u6570\r\n *\
    \ @docs docs/math/matrix/black_box_linear_algebra.md\r\n */\r\n\r\n#include <algorithm>\r\
    \n#include <cassert>\r\n#include <functional>\r\n#include <numeric>\r\n#include\
    \ <random>\r\n#include <vector>\r\n\r\n#line 1 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
    \n\n\n\r\n/**\r\n * @brief find shortest LFSR Berlekamp-Massey / \u5BFB\u627E\u6700\
    \u77ED\u7EBF\u6027\u9012\u63A8 Berlekamp-Massey \u7B97\u6CD5\r\n * @docs docs/math/modulo/find_shortest_LFSR_Berlekamp_Massey.md\r\
    \n */\r\n\r\n#line 10 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\n\
    #include <utility>\r\n#line 12 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u5BFB\u627E\u6700\u77ED LFSR \uFF08\
    \u4F46\u4EC5\u5F53 L*2 <= N \u65F6\u552F\u4E00\uFF09\r\n * @ref J.L. Massey, Shift\
    \ register synthesis and BCH decoding,\r\n *      IEEE Trans. Inform. Theory,\
    \ vol. IT-15, 122\u2013127 (1969).\r\n * @tparam mod_t \u6709\u9664\u6CD5\uFF0C\
    \u5FC5\u987B\u4E3A\u57DF\r\n * @param s s_0, s_1, \u2026, s_{n-1}\r\n * @return\
    \ std::vector<mod_t> C(x)=1+c_{1}*x+c_{2}*x^{2}+ \u2026 +c_{L}*x^{L}\r\n *   \
    \      \u5BF9\u4E8E\u6240\u6709 i>=L \u548C s = s_0, s_1, \u2026, s_{L-1}\r\n\
    \ *         \u6EE1\u8DB3 s_{i} + c_{1}*s_{i-1} + c_{2}*s_{i-2} + \u2026 + c_{L}*s_{i-L}\
    \ = 0\r\n */\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t> find_LFSR(const\
    \ std::vector<mod_t> &s) {\r\n  const mod_t ZERO(0);\r\n  std::vector<mod_t> C{mod_t(1)},\
    \ B(C);\r\n  mod_t b(1);\r\n  for (int N = 0, n = s.size(), L = 0, x = 1; N <\
    \ n; ++N) {\r\n    mod_t d(s[N]);\r\n    for (int i = 1; i <= L; ++i) d += C[i]\
    \ * s[N - i];\r\n    if (d == ZERO) {\r\n      ++x;\r\n    } else if ((L << 1)\
    \ > N) {\r\n      // C(D)=C(D)-d/bD^xB(D)\r\n      if (C.size() < B.size() + x)\
    \ C.resize(B.size() + x, ZERO);\r\n      mod_t coef = d / b;\r\n      for (int\
    \ i = x, ie = B.size() + x; i < ie; ++i) C[i] -= coef * B[i - x];\r\n      ++x;\r\
    \n    } else {\r\n      std::vector<mod_t> T(C); // \u8BB0\u5F55 next discrepancy\r\
    \n      // C(D)=C(D)-d/bD^xB(D)\r\n      if (C.size() < B.size() + x) C.resize(B.size()\
    \ + x, ZERO);\r\n      mod_t coef = d / b;\r\n      for (int i = x, ie = B.size()\
    \ + x; i < ie; ++i) C[i] -= coef * B[i - x];\r\n      L = N + 1 - L, B = std::move(T),\
    \ b = d, x = 1;\r\n    }\r\n  }\r\n  return C;\r\n}\r\n\r\n} // namespace lib\r\
    \n\r\n\n#line 17 \"math/matrix/black_box_linear_algebra.hpp\"\n\r\nnamespace lib\
    \ {\r\n\r\ntemplate <typename T, typename GenFunc>\r\nstd::vector<T> get_rand_vec(int\
    \ s, GenFunc &gen) {\r\n  std::vector<T> res(s);\r\n  std::generate(res.begin(),\
    \ res.end(), gen);\r\n  return res;\r\n}\r\n\r\n/**\r\n * @brief \u83B7\u53D6\u77E9\
    \u9635\u7684\u6700\u5C0F\u591A\u9879\u5F0F\uFF08\u968F\u673A\u5316\u7B97\u6CD5\
    \uFF09\r\n * @note \u5FC5\u987B\u4E3A\u6709\u9650\u57DF\r\n * @ref Douglas H.\
    \ Wiedemann (1986). Solving Sparse Linear Equations Over Finite Fields.\r\n *\
    \ @return std::vector<Type> \u9996\u4E00\u591A\u9879\u5F0F\r\n */\r\ntemplate\
    \ <typename MatType, typename Type = typename MatType::value_type>\r\nstd::vector<Type>\
    \ black_box_minpoly(const MatType &m) {\r\n\r\n  static std::random_device rd;\r\
    \n  static std::mt19937 gen(rd());\r\n  std::uniform_int_distribution<typename\
    \ Type::value_type> dis(1, Type::get_mod() - 1);\r\n\r\n  auto gen1 = [&dis]()\
    \ { return dis(gen); };\r\n  auto gen2 = std::bind(get_rand_vec<Type, decltype(gen1)>,\
    \ std::placeholders::_1, gen1);\r\n\r\n  const Type ZERO(0);\r\n  int n = m.row();\r\
    \n  assert(n == m.col());\r\n  std::vector<Type> u(gen2(n)), v(gen2(n)), bilinear_projection(n\
    \ << 1);\r\n  for (int i = 0; i < (n << 1); ++i) {\r\n    bilinear_projection[i]\
    \ = std::inner_product(u.begin(), u.end(), v.begin(), ZERO);\r\n    v = m.apply(v);\
    \ // \u4E0D\u9700\u8981\u5199\u6210 std::move \u56E0\u4E3A\u7F16\u8BD1\u5668\u4F1A\
    \u81EA\u52A8\u4F18\u5316\uFF01\r\n  }\r\n  std::vector<Type> res = find_LFSR(bilinear_projection);\r\
    \n  // \u7CFB\u6570\u7FFB\u8F6C\uFF01\u56E0\u4E3A\u5728\u8FD9\u91CC LFSR \u8FD4\
    \u56DE\u5173\u7CFB\u591A\u9879\u5F0F\r\n  // \u4E3A\u4E86\u4E0D\u5728\u6570\u7EC4\
    \u7684\u5F00\u5934\u63D2\u5165\u5143\u7D20\u6545\u4F7F\u7528 LFSR \u4E2D\u5B9A\
    \u4E49\u7684\u5173\u7CFB\u591A\u9879\u5F0F\u66F4\u65B9\u4FBF\r\n  // \u800C\u6700\
    \u5C0F\u591A\u9879\u5F0F\u5219\u53EA\u9700\u7FFB\u8F6C\u5176\u7CFB\u6570\u5373\
    \u9996\u4E00\u7684\u6700\u5C0F\u591A\u9879\u5F0F\r\n  std::reverse(res.begin(),\
    \ res.end());\r\n  return res;\r\n}\r\n\r\n/**\r\n * @brief \u83B7\u53D6\u77E9\
    \u9635\u7684\u884C\u5217\u5F0F\uFF08\u968F\u673A\u5316\u7B97\u6CD5\uFF09\r\n *\
    \ @note \u5FC5\u987B\u4E3A\u6709\u9650\u57DF\r\n * @ref Douglas H. Wiedemann (1986).\
    \ Solving Sparse Linear Equations Over Finite Fields.\r\n */\r\ntemplate <typename\
    \ MatType, typename Type = typename MatType::value_type>\r\nType black_box_det(const\
    \ MatType &m) {\r\n\r\n  static std::random_device rd;\r\n  static std::mt19937\
    \ gen(rd());\r\n  std::uniform_int_distribution<typename Type::value_type> dis(1,\
    \ Type::get_mod() - 1);\r\n\r\n  auto gen1 = [&dis]() { return dis(gen); };\r\n\
    \  auto gen2 = std::bind(get_rand_vec<Type, decltype(gen1)>, std::placeholders::_1,\
    \ gen1);\r\n\r\n  const Type ZERO(0);\r\n  int n = m.row();\r\n  assert(n == m.col());\r\
    \n  std::vector<Type> u(gen2(n)), v(gen2(n)), diag(gen2(n)), bilinear_projection(n\
    \ << 1);\r\n  for (int i = 0; i < (n << 1); ++i) {\r\n    bilinear_projection[i]\
    \ = std::inner_product(u.begin(), u.end(), v.begin(), ZERO);\r\n    for (int i\
    \ = 0; i < n; ++i) v[i] *= diag[i];\r\n    v = m.apply(v);\r\n  }\r\n  std::vector<Type>\
    \ mp = find_LFSR(bilinear_projection);\r\n  Type res = mp.back() / std::accumulate(diag.begin(),\
    \ diag.end(), Type(1), std::multiplies<>());\r\n  return (n & 1) == 1 ? -res :\
    \ res;\r\n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"math/matrix/square_matrix.hpp\"\
    \n\n\n\r\n/**\r\n * @brief square matrix / \u65B9\u9635\r\n *\r\n */\r\n\r\n#include\
    \ <optional>\r\n\r\n#line 1 \"math/matrix/matrix_base.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief matrix base / \u77E9\u9635\u57FA\u7C7B\r\n *\r\n */\r\n\r\n#line 14 \"\
    math/matrix/matrix_base.hpp\"\n\r\nnamespace lib {\r\n\r\ntemplate <typename Type>\r\
    \nclass Matrix {\r\npublic:\r\n  using value_type = Type;\r\n\r\n  /**\r\n   *\
    \ @brief Matrix \u7C7B\r\n   *\r\n   * @param r \u884C\r\n   * @param c \u5217\
    \r\n   * @param v \u521D\u503C\r\n   */\r\n  Matrix(int r, int c, const Type &v\
    \ = Type()) : row_(r), col_(c), mat_(row_ * col_, v) {}\r\n  virtual ~Matrix()\
    \      = default;\r\n  Matrix(const Matrix &) = default;\r\n\r\n  virtual Matrix\
    \ &operator=(const Matrix &) = default;\r\n\r\n  int row() const { return row_;\
    \ }\r\n  int col() const { return col_; }\r\n  int size() const { return row_\
    \ * col_; }\r\n  bool is_empty() const { return size() == 0; }\r\n\r\n  decltype(auto)\
    \ row_begin(int r) { return mat_.begin() + r * col_; }\r\n  decltype(auto) row_cbegin(int\
    \ r) const { return mat_.cbegin() + r * col_; }\r\n  decltype(auto) row_begin(int\
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
    \n\r\n\n#line 12 \"math/matrix/square_matrix.hpp\"\n\r\nnamespace lib {\r\n\r\n\
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
    \ lib\r\n\r\n\n#line 1 \"modint/Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n * @brief\
    \ Montgomery modint / Montgomery \u53D6\u6A21\u7C7B\r\n * @docs docs/modint/Montgomery_modint.md\r\
    \n */\r\n\r\n#include <cstdint>\r\n#line 11 \"modint/Montgomery_modint.hpp\"\n\
    #include <type_traits>\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief Montgomery\
    \ \u53D6\u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\r\n\
    \ */\r\ntemplate <std::uint32_t mod>\r\nclass MontgomeryModInt {\r\npublic:\r\n\
    \  using i32 = std::int32_t;\r\n  using u32 = std::uint32_t;\r\n  using u64 =\
    \ std::uint64_t;\r\n  using m32 = MontgomeryModInt;\r\n\r\n  using value_type\
    \ = u32;\r\n\r\n  static constexpr u32 get_mod() { return mod; }\r\n\r\n  static\
    \ constexpr u32 get_primitive_root_prime() {\r\n    u32 tmp[32]   = {};\r\n  \
    \  int cnt       = 0;\r\n    const u32 phi = mod - 1;\r\n    u32 m         = phi;\r\
    \n    for (u32 i = 2; i * i <= m; ++i) {\r\n      if (m % i == 0) {\r\n      \
    \  tmp[cnt++] = i;\r\n        do { m /= i; } while (m % i == 0);\r\n      }\r\n\
    \    }\r\n    if (m != 1) tmp[cnt++] = m;\r\n    for (m32 res = 2;; res += 1)\
    \ {\r\n      bool f = true;\r\n      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi\
    \ / tmp[i]) != 1;\r\n      if (f) return u32(res);\r\n    }\r\n  }\r\n\r\n  constexpr\
    \ MontgomeryModInt() = default;\r\n  ~MontgomeryModInt()          = default;\r\
    \n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\
    \n  constexpr MontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod)) *\
    \ r2)) {}\r\n\r\n  constexpr MontgomeryModInt(const m32 &) = default;\r\n\r\n\
    \  constexpr u32 get() const { return norm(reduce(v_)); }\r\n\r\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit constexpr\
    \ operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  constexpr m32 operator-()\
    \ const {\r\n    m32 res;\r\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  constexpr m32 inv() const {\r\n    i32 x1 = 1, x3 = 0,\
    \ a = get(), b = mod;\r\n    while (b != 0) {\r\n      i32 q = a / b, x1_old =\
    \ x1, a_old = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b\
    \ * q;\r\n    }\r\n    return m32(x1);\r\n  }\r\n\r\n  constexpr m32 &operator=(const\
    \ m32 &) = default;\r\n\r\n  constexpr m32 &operator+=(const m32 &rhs) {\r\n \
    \   v_ += rhs.v_ - mod2;\r\n    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\
    \n  }\r\n  constexpr m32 &operator-=(const m32 &rhs) {\r\n    v_ -= rhs.v_;\r\n\
    \    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\n  }\r\n  constexpr m32\
    \ &operator*=(const m32 &rhs) {\r\n    v_ = reduce(u64(v_) * rhs.v_);\r\n    return\
    \ *this;\r\n  }\r\n  constexpr m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend constexpr m32 operator+(const m32 &lhs, const m32 &rhs) { return\
    \ m32(lhs) += rhs; }\r\n  friend constexpr m32 operator-(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) -= rhs; }\r\n  friend constexpr m32 operator*(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\r\n  friend constexpr\
    \ m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }\r\n\
    \  friend constexpr bool operator==(const m32 &lhs, const m32 &rhs) {\r\n    return\
    \ norm(lhs.v_) == norm(rhs.v_);\r\n  }\r\n  friend constexpr bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) {\r\n    return norm(lhs.v_) != norm(rhs.v_);\r\n\
    \  }\r\n\r\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\r\n\
    \    i32 x;\r\n    is >> x;\r\n    rhs = m32(x);\r\n    return is;\r\n  }\r\n\
    \  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return\
    \ os << rhs.get(); }\r\n\r\n  constexpr m32 pow(u64 y) const {\r\n    m32 res(1),\
    \ x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n      if (y & 1) res *=\
    \ x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static constexpr u32 get_r()\
    \ {\r\n    u32 two = 2, iv = mod * (two - mod * mod);\r\n    iv *= two - mod *\
    \ iv;\r\n    iv *= two - mod * iv;\r\n    return iv * (mod * iv - two);\r\n  }\r\
    \n\r\n  static constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod)\
    \ >> 32; }\r\n  static constexpr u32 norm(u32 x) { return x - (mod & -((mod -\
    \ 1 - x) >> 31)); }\r\n\r\n  u32 v_;\r\n\r\n  static constexpr u32 r    = get_r();\r\
    \n  static constexpr u32 r2   = -u64(mod) % mod;\r\n  static constexpr u32 mod2\
    \ = mod << 1;\r\n\r\n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\r\n\
    \  static_assert(-r * mod == 1, \"???\\n\");\r\n  static_assert((mod & (3U <<\
    \ 30)) == 0, \"mod >= (1 << 30)\\n\");\r\n  static_assert(mod != 1, \"mod == 1\\\
    n\");\r\n};\r\n\r\n// \u522B\u540D\r\ntemplate <std::uint32_t mod>\r\nusing MontModInt\
    \ = MontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 8 \"remote_test/yosupo/matrix/matrix_det.1.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n;\r\n  std::cin >> n;\r\n  lib::SquareMatrix<lib::MontModInt<998244353>>\
    \ m(n);\r\n  std::cin >> m;\r\n  std::cout << lib::black_box_det(m);\r\n  return\
    \ 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_det\"\r\n\r\n#include\
    \ <iostream>\r\n\r\n#include \"math/matrix/black_box_linear_algebra.hpp\"\r\n\
    #include \"math/matrix/square_matrix.hpp\"\r\n#include \"modint/Montgomery_modint.hpp\"\
    \r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  int n;\r\n  std::cin >> n;\r\n  lib::SquareMatrix<lib::MontModInt<998244353>>\
    \ m(n);\r\n  std::cin >> m;\r\n  std::cout << lib::black_box_det(m);\r\n  return\
    \ 0;\r\n}"
  dependsOn:
  - math/matrix/black_box_linear_algebra.hpp
  - math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
  - math/matrix/square_matrix.hpp
  - math/matrix/matrix_base.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/matrix/matrix_det.1.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: remote_test/yosupo/matrix/matrix_det.1.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/matrix/matrix_det.1.test.cpp
- /verify/remote_test/yosupo/matrix/matrix_det.1.test.cpp.html
title: remote_test/yosupo/matrix/matrix_det.1.test.cpp
---
