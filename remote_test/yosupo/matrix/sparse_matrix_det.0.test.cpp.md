---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/black_box_linear_algebra.hpp
    title: "black box linear algebra / \u9ED1\u76D2\u7EBF\u6027\u4EE3\u6570"
  - icon: ':heavy_check_mark:'
    path: math/matrix/sparse_matrix_base.hpp
    title: "sparse matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B"
  - icon: ':heavy_check_mark:'
    path: math/matrix/sparse_square_matrix.hpp
    title: "sparse square matrix / \u7A00\u758F\u65B9\u9635"
  - icon: ':heavy_check_mark:'
    path: math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
    title: "find shortest LFSR Berlekamp-Massey / \u5BFB\u627E\u6700\u77ED\u7EBF\u6027\
      \u9012\u63A8 Berlekamp-Massey \u7B97\u6CD5"
  - icon: ':heavy_check_mark:'
    path: modint/Montgomery_modint.hpp
    title: "Montgomery modint / Montgomery \u53D6\u6A21\u7C7B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sparse_matrix_det
    links:
    - https://judge.yosupo.jp/problem/sparse_matrix_det
  bundledCode: "#line 1 \"remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/sparse_matrix_det\"\n\n#include\
    \ <iostream>\n\n#line 1 \"math/matrix/black_box_linear_algebra.hpp\"\n\n\n\n/**\n\
    \ * @brief black box linear algebra / \u9ED1\u76D2\u7EBF\u6027\u4EE3\u6570\n *\
    \ @docs docs/math/matrix/black_box_linear_algebra.md\n */\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <numeric>\n#include <random>\n\
    #include <vector>\n\n#line 1 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
    \n\n\n\n/**\n * @brief find shortest LFSR Berlekamp-Massey / \u5BFB\u627E\u6700\
    \u77ED\u7EBF\u6027\u9012\u63A8 Berlekamp-Massey \u7B97\u6CD5\n * @docs docs/math/modulo/find_shortest_LFSR_Berlekamp_Massey.md\n\
    \ */\n\n#line 10 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\n#include\
    \ <utility>\n#line 12 \"math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\n\
    \nnamespace lib {\n\n/**\n * @brief \u5BFB\u627E\u6700\u77ED LFSR \uFF08\u4F46\
    \u4EC5\u5F53 L*2 <= N \u65F6\u552F\u4E00\uFF09\n * @ref J.L. Massey, Shift register\
    \ synthesis and BCH decoding,\n *      IEEE Trans. Inform. Theory, vol. IT-15,\
    \ 122\u2013127 (1969).\n * @tparam mod_t \u6709\u9664\u6CD5\uFF0C\u5FC5\u987B\u4E3A\
    \u57DF\n * @param s s_0, s_1, \u2026, s_{n-1}\n * @return std::vector<mod_t> C(x)=1+c_{1}*x+c_{2}*x^{2}+\
    \ \u2026 +c_{L}*x^{L}\n *         \u5BF9\u4E8E\u6240\u6709 i>=L \u548C s = s_0,\
    \ s_1, \u2026, s_{L-1}\n *         \u6EE1\u8DB3 s_{i} + c_{1}*s_{i-1} + c_{2}*s_{i-2}\
    \ + \u2026 + c_{L}*s_{i-L} = 0\n */\ntemplate <typename mod_t> std::vector<mod_t>\
    \ find_LFSR(const std::vector<mod_t> &s) {\n  const mod_t ZERO(0);\n  std::vector<mod_t>\
    \ C{mod_t(1)}, B(C);\n  mod_t b(1);\n  for (int N = 0, n = s.size(), L = 0, x\
    \ = 1; N < n; ++N) {\n    mod_t d(s[N]);\n    for (int i = 1; i <= L; ++i) d +=\
    \ C[i] * s[N - i];\n    if (d == ZERO) {\n      ++x;\n    } else if ((L << 1)\
    \ > N) {\n      // C(D)=C(D)-d/bD^xB(D)\n      if (C.size() < B.size() + x) C.resize(B.size()\
    \ + x, ZERO);\n      mod_t coef = d / b;\n      for (int i = x, ie = B.size()\
    \ + x; i < ie; ++i) C[i] -= coef * B[i - x];\n      ++x;\n    } else {\n     \
    \ std::vector<mod_t> T(C); // \u8BB0\u5F55 next discrepancy\n      // C(D)=C(D)-d/bD^xB(D)\n\
    \      if (C.size() < B.size() + x) C.resize(B.size() + x, ZERO);\n      mod_t\
    \ coef = d / b;\n      for (int i = x, ie = B.size() + x; i < ie; ++i) C[i] -=\
    \ coef * B[i - x];\n      L = N + 1 - L, B = std::move(T), b = d, x = 1;\n   \
    \ }\n  }\n  return C;\n}\n\n} // namespace lib\n\n\n#line 17 \"math/matrix/black_box_linear_algebra.hpp\"\
    \n\nnamespace lib {\n\ntemplate <typename T, typename GenFunc> std::vector<T>\
    \ get_rand_vec(int s, GenFunc &gen) {\n  std::vector<T> res(s);\n  std::generate(res.begin(),\
    \ res.end(), gen);\n  return res;\n}\n\n/**\n * @brief \u83B7\u53D6\u77E9\u9635\
    \u7684\u6700\u5C0F\u591A\u9879\u5F0F\uFF08\u968F\u673A\u5316\u7B97\u6CD5\uFF09\
    \n * @note \u5FC5\u987B\u4E3A\u6709\u9650\u57DF\n * @ref Douglas H. Wiedemann\
    \ (1986). Solving Sparse Linear Equations Over Finite Fields.\n * @return std::vector<Type>\
    \ \u9996\u4E00\u591A\u9879\u5F0F\n */\ntemplate <typename MatType, typename Type\
    \ = typename MatType::value_type>\nstd::vector<Type> black_box_minpoly(const MatType\
    \ &m) {\n\n  static std::random_device rd;\n  static std::mt19937 gen(rd());\n\
    \  std::uniform_int_distribution<typename Type::value_type> dis(1, Type::get_mod()\
    \ - 1);\n\n  auto gen1 = [&dis]() { return dis(gen); };\n  auto gen2 = std::bind(get_rand_vec<Type,\
    \ decltype(gen1)>, std::placeholders::_1, gen1);\n\n  const Type ZERO(0);\n  int\
    \ n = m.row();\n  assert(n == m.col());\n  std::vector<Type> u(gen2(n)), v(gen2(n)),\
    \ bilinear_projection(n << 1);\n  for (int i = 0; i < (n << 1); ++i) {\n    bilinear_projection[i]\
    \ = std::inner_product(u.begin(), u.end(), v.begin(), ZERO);\n    v = m.apply(v);\
    \ // \u4E0D\u9700\u8981\u5199\u6210 std::move \u56E0\u4E3A\u7F16\u8BD1\u5668\u4F1A\
    \u81EA\u52A8\u4F18\u5316\uFF01\n  }\n  std::vector<Type> res = find_LFSR(bilinear_projection);\n\
    \  std::reverse(res.begin(),\n               res.end()); // \u7CFB\u6570\u7FFB\
    \u8F6C\uFF01\u56E0\u4E3A\u5728\u8FD9\u91CC LFSR \u5BF9\u5E94\u7684\u6700\u5C0F\
    \u591A\u9879\u5F0F\u548C\u77E9\u9635\u7684\u6700\u5C0F\u591A\u9879\u5F0F\u5B9A\
    \u4E49\u4E0D\u540C\n  return res;\n}\n\n/**\n * @brief \u83B7\u53D6\u77E9\u9635\
    \u7684\u884C\u5217\u5F0F\uFF08\u968F\u673A\u5316\u7B97\u6CD5\uFF09\n * @note \u5FC5\
    \u987B\u4E3A\u6709\u9650\u57DF\n * @ref Douglas H. Wiedemann (1986). Solving Sparse\
    \ Linear Equations Over Finite Fields.\n */\ntemplate <typename MatType, typename\
    \ Type = typename MatType::value_type>\nType black_box_det(const MatType &m) {\n\
    \n  static std::random_device rd;\n  static std::mt19937 gen(rd());\n  std::uniform_int_distribution<typename\
    \ Type::value_type> dis(1, Type::get_mod() - 1);\n\n  auto gen1 = [&dis]() { return\
    \ dis(gen); };\n  auto gen2 = std::bind(get_rand_vec<Type, decltype(gen1)>, std::placeholders::_1,\
    \ gen1);\n\n  const Type ZERO(0);\n  int n = m.row();\n  assert(n == m.col());\n\
    \  std::vector<Type> u(gen2(n)), v(gen2(n)), diag(gen2(n)), bilinear_projection(n\
    \ << 1);\n  for (int i = 0; i < (n << 1); ++i) {\n    bilinear_projection[i] =\
    \ std::inner_product(u.begin(), u.end(), v.begin(), ZERO);\n    for (int i = 0;\
    \ i < n; ++i) v[i] *= diag[i];\n    v = m.apply(v);\n  }\n  std::vector<Type>\
    \ mp = find_LFSR(bilinear_projection);\n  Type res = mp.back() / std::accumulate(diag.begin(),\
    \ diag.end(), Type(1), std::multiplies<>());\n  return (n & 1) == 1 ? -res : res;\n\
    }\n\n} // namespace lib\n\n\n#line 1 \"math/matrix/sparse_square_matrix.hpp\"\n\
    \n\n\n/**\n * @brief sparse square matrix / \u7A00\u758F\u65B9\u9635\n *\n */\n\
    \n#line 1 \"math/matrix/sparse_matrix_base.hpp\"\n\n\n\n/**\n * @brief sparse\
    \ matrix base / \u7A00\u758F\u77E9\u9635\u57FA\u7C7B\n *\n */\n\n#line 12 \"math/matrix/sparse_matrix_base.hpp\"\
    \n\nnamespace lib {\n\ntemplate <typename Type> class SparseMatrix {\npublic:\n\
    \  using value_type = Type;\n\n  SparseMatrix(int r, int c, const Type &v = Type())\
    \ : row_(r), col_(c), default_val_(v), mat_(r) {}\n  virtual ~SparseMatrix() =\
    \ default;\n  SparseMatrix(const SparseMatrix &) = default;\n\n  virtual SparseMatrix\
    \ &operator=(const SparseMatrix &) = default;\n\n  int row() const { return row_;\
    \ }\n  int col() const { return col_; }\n  int size() const { return row_ * col_;\
    \ }\n  bool is_empty() const { return size() == 0; }\n\n  Type &at(int r, int\
    \ c) {\n    for (auto &[pos, v] : mat_[r])\n      if (pos == c) return v;\n  \
    \  return mat_[r].emplace_back(c, default_val_).second;\n  }\n  Type at(int r,\
    \ int c) const {\n    for (auto &[pos, v] : mat_[r])\n      if (pos == c) return\
    \ v;\n    return default_val_;\n  }\n\n  virtual std::vector<Type> apply(const\
    \ std::vector<Type> &x) const {\n    int r = row(), c = col();\n    assert(c ==\
    \ x.size());\n    assert(default_val_ == Type(0)); // \u82E5\u9ED8\u8BA4\u503C\
    \u4E0D\u4E3A\u96F6\u5219\u9700\u8981\u4FEE\u6539\u6B64\u51FD\u6570\n    std::vector<Type>\
    \ res(r, Type(0));\n    for (int i = 0; i < r; ++i) {\n      for (auto &[pos,\
    \ v] : mat_[i]) res[i] += v * x[pos];\n    }\n    return res;\n  }\n\nprotected:\n\
    \  int row_, col_;\n  const Type default_val_;\n  std::vector<std::vector<std::pair<int,\
    \ Type>>> mat_;\n};\n\n} // namespace lib\n\n\n#line 10 \"math/matrix/sparse_square_matrix.hpp\"\
    \n\nnamespace lib {\n\ntemplate <typename Type> class SparseSquareMatrix : public\
    \ SparseMatrix<Type> {\npublic:\n  SparseSquareMatrix(int r, const Type &v = Type())\
    \ : SparseMatrix<Type>(r, r, v) {}\n  virtual ~SparseSquareMatrix() = default;\n\
    };\n\n} // namespace lib\n\n\n#line 1 \"modint/Montgomery_modint.hpp\"\n\n\n\n\
    /**\n * @brief Montgomery modint / Montgomery \u53D6\u6A21\u7C7B\n * @docs docs/modint/Montgomery_modint.md\n\
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
    \ // namespace lib\n\n\n#line 8 \"remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, k;\n  std::cin >> n >> k;\n  lib::SparseSquareMatrix<lib::MontModInt<998244353>>\
    \ m(n, 0);\n  while (k--) {\n    int r, c, v;\n    std::cin >> r >> c >> v;\n\
    \    m.at(r, c) = v;\n  }\n  std::cout << lib::black_box_det(m);\n  return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sparse_matrix_det\"\n\n\
    #include <iostream>\n\n#include \"math/matrix/black_box_linear_algebra.hpp\"\n\
    #include \"math/matrix/sparse_square_matrix.hpp\"\n#include \"modint/Montgomery_modint.hpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, k;\n  std::cin >> n >> k;\n  lib::SparseSquareMatrix<lib::MontModInt<998244353>>\
    \ m(n, 0);\n  while (k--) {\n    int r, c, v;\n    std::cin >> r >> c >> v;\n\
    \    m.at(r, c) = v;\n  }\n  std::cout << lib::black_box_det(m);\n  return 0;\n\
    }"
  dependsOn:
  - math/matrix/black_box_linear_algebra.hpp
  - math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
  - math/matrix/sparse_square_matrix.hpp
  - math/matrix/sparse_matrix_base.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-08 03:55:34+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
- /verify/remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp.html
title: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
---
