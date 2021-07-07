---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/matrix/matrix_base.hpp
    title: "matrix base / \u77E9\u9635\u57FA\u7C7B"
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
    PROBLEM: https://judge.yosupo.jp/problem/matrix_product
    links:
    - https://judge.yosupo.jp/problem/matrix_product
  bundledCode: "#line 1 \"remote_test/yosupo/matrix/matrix_product.0.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product\"\n\n#include\
    \ <iostream>\n\n#line 1 \"math/matrix/matrix_base.hpp\"\n\n\n\n/**\n * @brief\
    \ matrix base / \u77E9\u9635\u57FA\u7C7B\n *\n */\n\n#include <algorithm>\n#include\
    \ <cassert>\n#line 12 \"math/matrix/matrix_base.hpp\"\n#include <numeric>\n#include\
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
    #line 1 \"modint/Montgomery_modint.hpp\"\n\n\n\n/**\n * @brief Montgomery modint\
    \ / Montgomery \u53D6\u6A21\u7C7B\n * @docs docs/modint/Montgomery_modint.md\n\
    \ */\n\n#include <cstdint>\n#line 11 \"modint/Montgomery_modint.hpp\"\n#include\
    \ <type_traits>\n\nnamespace lib {\n\n/**\n * @brief Montgomery \u53D6\u6A21\u7C7B\
    \n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n\
    \ * @author Nyaan\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\n */\n\
    template <std::uint32_t mod> class MontgomeryModInt {\npublic:\n  using i32 =\
    \ std::int32_t;\n  using u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n\
    \  using m32 = MontgomeryModInt;\n\n  using value_type = u32;\n\n  static constexpr\
    \ u32 get_mod() { return mod; }\n\n  static constexpr u32 get_primitive_root_prime()\
    \ {\n    u32 tmp[32] = {};\n    int cnt = 0;\n    const u32 phi = mod - 1;\n \
    \   u32 m = phi;\n    for (u32 i = 2; i * i <= m; ++i) {\n      if (m % i == 0)\
    \ {\n        tmp[cnt++] = i;\n        do {\n          m /= i;\n        } while\
    \ (m % i == 0);\n      }\n    }\n    if (m != 1) tmp[cnt++] = m;\n    for (m32\
    \ res = 2;; res += 1) {\n      bool f = true;\n      for (int i = 0; i < cnt &&\
    \ f; ++i) f &= res.pow(phi / tmp[i]) != 1;\n      if (f) return u32(res);\n  \
    \  }\n  }\n\n  constexpr MontgomeryModInt() = default;\n  ~MontgomeryModInt()\
    \ = default;\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  constexpr MontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) +\
    \ i32(mod)) * r2)) {}\n\n  constexpr MontgomeryModInt(const m32 &) = default;\n\
    \n  constexpr u32 get() const { return norm(reduce(v_)); }\n\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  explicit constexpr operator\
    \ T() const {\n    return T(get());\n  }\n\n  constexpr m32 operator-() const\
    \ {\n    m32 res;\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\n    return res;\n \
    \ }\n\n  constexpr m32 inv() const {\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\n\
    \    while (b != 0) {\n      i32 q = a / b, x1_old = x1, a_old = a;\n      x1\
    \ = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n    }\n    return m32(x1);\n\
    \  }\n\n  constexpr m32 &operator=(const m32 &) = default;\n\n  constexpr m32\
    \ &operator+=(const m32 &rhs) {\n    v_ += rhs.v_ - mod2;\n    v_ += mod2 & -(v_\
    \ >> 31);\n    return *this;\n  }\n  constexpr m32 &operator-=(const m32 &rhs)\
    \ {\n    v_ -= rhs.v_;\n    v_ += mod2 & -(v_ >> 31);\n    return *this;\n  }\n\
    \  constexpr m32 &operator*=(const m32 &rhs) {\n    v_ = reduce(u64(v_) * rhs.v_);\n\
    \    return *this;\n  }\n  constexpr m32 &operator/=(const m32 &rhs) { return\
    \ operator*=(rhs.inv()); }\n  friend constexpr m32 operator+(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) += rhs; }\n  friend constexpr m32 operator-(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }\n  friend constexpr m32\
    \ operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\n  friend\
    \ constexpr m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /=\
    \ rhs; }\n  friend constexpr bool operator==(const m32 &lhs, const m32 &rhs) {\n\
    \    return norm(lhs.v_) == norm(rhs.v_);\n  }\n  friend constexpr bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) {\n    return norm(lhs.v_) != norm(rhs.v_);\n  }\n\
    \n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\n    i32 x;\n\
    \    is >> x;\n    rhs = m32(x);\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m32 &rhs) { return os << rhs.get(); }\n\n  constexpr m32 pow(u64\
    \ y) const {\n    m32 res(1), x(*this);\n    for (; y != 0; y >>= 1, x *= x)\n\
    \      if (y & 1) res *= x;\n    return res;\n  }\n\nprivate:\n  static constexpr\
    \ u32 get_r() {\n    u32 two = 2, iv = mod * (two - mod * mod);\n    iv *= two\
    \ - mod * iv;\n    iv *= two - mod * iv;\n    return iv * (mod * iv - two);\n\
    \  }\n\n  static constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod)\
    \ >> 32; }\n  static constexpr u32 norm(u32 x) { return x - (mod & -((mod - 1\
    \ - x) >> 31)); }\n\n  u32 v_;\n\n  static constexpr u32 r = get_r();\n  static\
    \ constexpr u32 r2 = -u64(mod) % mod;\n  static constexpr u32 mod2 = mod << 1;\n\
    \n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\n  static_assert(-r *\
    \ mod == 1, \"???\\n\");\n  static_assert((mod & (3U << 30)) == 0, \"mod >= (1\
    \ << 30)\\n\");\n  static_assert(mod != 1, \"mod == 1\\n\");\n};\n\n// \u522B\u540D\
    \ntemplate <std::uint32_t mod> using MontModInt = MontgomeryModInt<mod>;\n\n}\
    \ // namespace lib\n\n\n#line 7 \"remote_test/yosupo/matrix/matrix_product.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, m, k;\n  std::cin >> n >> m >> k;\n  lib::Matrix<lib::MontModInt<998244353>>\
    \ a(n, m), b(m, k);\n  std::cin >> a >> b;\n  std::cout << a * b;\n  return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product\"\n\n#include\
    \ <iostream>\n\n#include \"math/matrix/matrix_base.hpp\"\n#include \"modint/Montgomery_modint.hpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, m, k;\n  std::cin >> n >> m >> k;\n  lib::Matrix<lib::MontModInt<998244353>>\
    \ a(n, m), b(m, k);\n  std::cin >> a >> b;\n  std::cout << a * b;\n  return 0;\n\
    }"
  dependsOn:
  - math/matrix/matrix_base.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/matrix/matrix_product.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-08 03:55:34+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: remote_test/yosupo/matrix/matrix_product.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/matrix/matrix_product.0.test.cpp
- /verify/remote_test/yosupo/matrix/matrix_product.0.test.cpp.html
title: remote_test/yosupo/matrix/matrix_product.0.test.cpp
---
