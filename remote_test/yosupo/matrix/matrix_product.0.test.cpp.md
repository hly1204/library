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
    #define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product\"\r\n\r\n#include\
    \ <iostream>\r\n\r\n#line 1 \"math/matrix/matrix_base.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief matrix base / \u77E9\u9635\u57FA\u7C7B\r\n *\r\n */\r\n\r\n#include <algorithm>\r\
    \n#include <cassert>\r\n#line 12 \"math/matrix/matrix_base.hpp\"\n#include <numeric>\r\
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
    \n\r\n\n#line 1 \"modint/Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n * @brief Montgomery\
    \ modint / Montgomery \u53D6\u6A21\u7C7B\r\n * @docs docs/modint/Montgomery_modint.md\r\
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
    \ = MontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 7 \"remote_test/yosupo/matrix/matrix_product.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n, m, k;\r\n  std::cin >> n >> m >> k;\r\n  lib::Matrix<lib::MontModInt<998244353>>\
    \ a(n, m), b(m, k);\r\n  std::cin >> a >> b;\r\n  std::cout << a * b;\r\n  return\
    \ 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product\"\r\n\r\n\
    #include <iostream>\r\n\r\n#include \"math/matrix/matrix_base.hpp\"\r\n#include\
    \ \"modint/Montgomery_modint.hpp\"\r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"\
    in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  int n, m, k;\r\n  std::cin >> n >> m >> k;\r\n  lib::Matrix<lib::MontModInt<998244353>>\
    \ a(n, m), b(m, k);\r\n  std::cin >> a >> b;\r\n  std::cout << a * b;\r\n  return\
    \ 0;\r\n}"
  dependsOn:
  - math/matrix/matrix_base.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/matrix/matrix_product.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: remote_test/yosupo/matrix/matrix_product.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/matrix/matrix_product.0.test.cpp
- /verify/remote_test/yosupo/matrix/matrix_product.0.test.cpp.html
title: remote_test/yosupo/matrix/matrix_product.0.test.cpp
---
