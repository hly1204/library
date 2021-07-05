---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
    title: "find shortest LFSR Berlekamp-Massey / \u5BFB\u627E\u6700\u77ED\u7EBF\u6027\
      \u9012\u63A8 Berlekamp-Massey \u7B97\u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/matrix_det.1.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
    title: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/math/matrix/black_box_linear_algebra.md
    document_title: "black box linear algebra / \u9ED1\u76D2\u7EBF\u6027\u4EE3\u6570"
    links: []
  bundledCode: "#line 1 \"math/matrix/black_box_linear_algebra.hpp\"\n\n\n\n/**\n\
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
    \u57DF\n * @param s s_0, s_1, ..., s_{n-1}\n * @return std::vector<mod_t> C(x)=1+c_{1}*x+c_{2}*x^{2}+...+c_{L}*x^{L}\n\
    \ *         \u5BF9\u4E8E\u6240\u6709 i>=L \u548C s = s_0, s_1, ..., s_{L-1}\n\
    \ *         \u6EE1\u8DB3 s_{i} + c_{1}*s_{i-1} + c_{2}*s_{i-2} + ... + c_{L}*s_{i-L}\
    \ = 0\n */\ntemplate <typename mod_t> std::vector<mod_t> find_LFSR(const std::vector<mod_t>\
    \ &s) {\n  const mod_t ZERO(0);\n  std::vector<mod_t> C{mod_t(1)}, B(C);\n  mod_t\
    \ b(1);\n  for (int N = 0, n = s.size(), L = 0, x = 1; N < n; ++N) {\n    mod_t\
    \ d(s[N]);\n    for (int i = 1; i <= L; ++i) d += C[i] * s[N - i];\n    if (d\
    \ == ZERO) {\n      ++x;\n    } else if ((L << 1) > N) {\n      // C(D)=C(D)-d/bD^xB(D)\n\
    \      if (C.size() < B.size() + x) C.resize(B.size() + x, ZERO);\n      mod_t\
    \ coef = d / b;\n      for (int i = x, ie = B.size() + x; i < ie; ++i) C[i] -=\
    \ coef * B[i - x];\n      ++x;\n    } else {\n      std::vector<mod_t> T(C); //\
    \ \u8BB0\u5F55 next discrepancy\n      // C(D)=C(D)-d/bD^xB(D)\n      if (C.size()\
    \ < B.size() + x) C.resize(B.size() + x, ZERO);\n      mod_t coef = d / b;\n \
    \     for (int i = x, ie = B.size() + x; i < ie; ++i) C[i] -= coef * B[i - x];\n\
    \      L = N + 1 - L, B = std::move(T), b = d, x = 1;\n    }\n  }\n  return C;\n\
    }\n\n} // namespace lib\n\n\n#line 17 \"math/matrix/black_box_linear_algebra.hpp\"\
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
    }\n\n} // namespace lib\n\n\n"
  code: "#ifndef BLACK_BOX_LINEAR_ALGEBRA_HEADER_HPP\n#define BLACK_BOX_LINEAR_ALGEBRA_HEADER_HPP\n\
    \n/**\n * @brief black box linear algebra / \u9ED1\u76D2\u7EBF\u6027\u4EE3\u6570\
    \n * @docs docs/math/matrix/black_box_linear_algebra.md\n */\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <numeric>\n#include <random>\n\
    #include <vector>\n\n#include \"../modulo/find_shortest_LFSR_Berlekamp_Massey.hpp\"\
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
    }\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp
  isVerificationFile: false
  path: math/matrix/black_box_linear_algebra.hpp
  requiredBy: []
  timestamp: '2021-07-05 14:46:07+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/matrix/matrix_det.1.test.cpp
  - remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
documentation_of: math/matrix/black_box_linear_algebra.hpp
layout: document
redirect_from:
- /library/math/matrix/black_box_linear_algebra.hpp
- /library/math/matrix/black_box_linear_algebra.hpp.html
title: "black box linear algebra / \u9ED1\u76D2\u7EBF\u6027\u4EE3\u6570"
---
## 黑盒线性代数

黑盒线性代数的意思是我们没办法直接接触到该矩阵，但我们可以获取矩阵与向量的乘积，借此来进行计算。

### 最小多项式

Wiedemann 提出，对于黑盒矩阵 $\mathbf{A}\in\mathbb{F}^{n\times n}$ 和一个随机的向量 $\mathbf{v}\in\mathbb{F}^n$ 其 Krylov 序列 $\lbrace \mathbf{A}^i\mathbf{v} \rbrace _ {i=0}^\infty$ 的最小多项式 $f^{\mathbf{A},\mathbf{v}}$ 很大可能等于 $\mathbf{A}$ 的最小多项式 $f^{\mathbf{A}}$ ，而对于第二个随机向量 $\mathbf{u}$ 其 bilinear projection 序列 $\lbrace \mathbf{u}^{\mathrm{T}}\mathbf{A}^i\mathbf{v} \rbrace _ {i=0}^\infty$ 的最小多项式 $f^{\mathbf{A},\mathbf{v}} _ \mathbf{u}$ 很大可能等于 $f^{\mathbf{A},\mathbf{v}}$ 。而 $f^{\mathbf{A},\mathbf{v}} _ \mathbf{u}$ 我们可以借助 Berlekamp-Massey 算法来计算（只需翻转即能得到首一多项式，这是因为 LFSR （序列的最小多项式）与矩阵最小多项式定义不同）。

### 行列式

根据上面提到的，假设 $\mathbf{A}$ 的特征多项式 $\chi (\mathbf{A})=\det(\lambda \mathbf{I}-\mathbf{A})$ 等于 $f^{\mathbf{A}}$ 那么有很大可能有这样的等式

$$
\det(\lambda \mathbf{I}-\mathbf{A})=f^{\mathbf{A}}=f^{\mathbf{A},\mathbf{v}}=f^{\mathbf{A},\mathbf{v}} _ \mathbf{u}
$$

Kaltofen 和 Pan 指出这个可能性至少为 $1-2\deg(f^{\mathbf{A}})/\lvert S\rvert$ 。因此

$$
\det(\mathbf{A})=(-1)^nf^{\mathbf{A},\mathbf{v}} _ \mathbf{u}(0)
$$

也就是其常数项，但是前提是 $f^{\mathbf{A}}=\chi(\mathbf{A})$ 。

在 2002 年 Chen 等提出了用一个对角矩阵

$$
\tilde{\mathbf{A}}=\mathbf{A}\cdot \operatorname{diag}(d_1,\cdots ,d_n)
$$

可以使得矩阵 $\tilde{\mathbf{A}}$ 满足这个条件，而 $\det(\operatorname{diag}(d_1,\cdots ,d_n))=\prod _ {i=1}^nd_i$ 。

我们求出 $\det(\tilde{\mathbf{A}})/\det(\operatorname{diag}(d_1,\cdots ,d_n))$ 即可。

## 参考文献

- Douglas H. Wiedemann (1986). Solving Sparse Linear Equations Over Finite Fields.