---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/poly_extended_gcd.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 5 \"math/poly_extended_gcd.hpp\"\n\n#include\
    \ <algorithm>\n#include <array>\n#include <cassert>\n#include <optional>\n#include\
    \ <tuple>\n#include <utility>\n\nLIB_BEGIN\n\n// helper class for Euclidean algorithm\n\
    template <typename PolyT>\nclass polynomial_gcd_matrix : public std::array<std::array<PolyT,\
    \ 2>, 2> {\n  using MyBase = std::array<std::array<PolyT, 2>, 2>;\n\npublic:\n\
    \  polynomial_gcd_matrix(const PolyT &m00, const PolyT &m01, const PolyT &m10,\
    \ const PolyT &m11)\n      : MyBase{std::array<PolyT, 2>{m00, m01}, std::array<PolyT,\
    \ 2>{m10, m11}} {}\n  polynomial_gcd_matrix operator*(const polynomial_gcd_matrix\
    \ &rhs) const {\n    return polynomial_gcd_matrix((*this)[0][0] * rhs[0][0] +\
    \ (*this)[0][1] * rhs[1][0],\n                                 (*this)[0][0] *\
    \ rhs[0][1] + (*this)[0][1] * rhs[1][1],\n                                 (*this)[1][0]\
    \ * rhs[0][0] + (*this)[1][1] * rhs[1][0],\n                                 (*this)[1][0]\
    \ * rhs[0][1] + (*this)[1][1] * rhs[1][1]);\n  }\n  std::array<PolyT, 2> operator*(const\
    \ std::array<PolyT, 2> &rhs) const {\n    return {(*this)[0][0] * rhs[0] + (*this)[0][1]\
    \ * rhs[1],\n            (*this)[1][0] * rhs[0] + (*this)[1][1] * rhs[1]};\n \
    \ }\n};\n\nnamespace detail {\n\ntemplate <typename PolyT>\npolynomial_gcd_matrix<PolyT>\
    \ hgcd(const PolyT &A, const PolyT &B) {\n  assert(A.deg() > B.deg());\n  assert(!B.is_zero());\n\
    \  int m = (A.deg() + 1) >> 1;\n  if (B.deg() < m) return polynomial_gcd_matrix<PolyT>({1},\
    \ {}, {}, {1});\n  auto R      = hgcd(PolyT(A.cbegin() + m, A.cend()), PolyT(B.cbegin()\
    \ + m, B.cend()));\n  auto [C, D] = R * std::array<PolyT, 2>{A, B};\n  if (D.deg()\
    \ < m) return R;\n  auto [Q, E] = C.div_with_rem(D);\n  if (E.deg() < m) return\
    \ polynomial_gcd_matrix<PolyT>({}, {1}, {1}, -Q) * R;\n  int k = (m << 1) - D.deg();\n\
    \  return hgcd(PolyT(D.cbegin() + k, D.cend()), PolyT(E.cbegin() + k, E.cend()))\
    \ *\n         polynomial_gcd_matrix<PolyT>({}, {1}, {1}, -Q) * R;\n}\n\ntemplate\
    \ <typename PolyT>\nstd::pair<polynomial_gcd_matrix<PolyT>, PolyT> cogcd(const\
    \ PolyT &A, const PolyT &B) {\n  assert(A.deg() > B.deg());\n  assert(!B.is_zero());\n\
    \  polynomial_gcd_matrix<PolyT> M({1}, {}, {}, {1});\n  PolyT A_cpy(A), B_cpy(B);\n\
    \  for (;;) {\n    auto M0     = hgcd(A_cpy, B_cpy);\n    auto [C, D] = M0 * std::array<PolyT,\
    \ 2>{A_cpy, B_cpy};\n    if (D.is_zero()) return std::make_pair(M0 * M, C);\n\
    \    auto [Q, E] = C.div_with_rem(D);\n    M0          = polynomial_gcd_matrix<PolyT>({},\
    \ {1}, {1}, -Q) * M0;\n    if (E.is_zero()) return std::make_pair(M0 * M, D);\n\
    \    A_cpy.swap(D), B_cpy.swap(E);\n    M = M0 * M;\n  }\n}\n\n} // namespace\
    \ detail\n\ntemplate <typename PolyT>\nstd::tuple<PolyT, PolyT, PolyT> poly_ext_gcd(const\
    \ PolyT &A, const PolyT &B) {\n  if (B.is_zero()) return std::make_tuple(PolyT{1},\
    \ PolyT{}, A);\n  if (A.is_zero()) return std::make_tuple(PolyT{}, PolyT{1}, B);\n\
    \  if (A.deg() > B.deg()) {\n    auto [M, d] = detail::cogcd(A, B);\n    return\
    \ std::make_tuple(M[0][0], M[0][1], d);\n  } else if (A.deg() < B.deg()) {\n \
    \   auto [M, d] = detail::cogcd(B, A);\n    return std::make_tuple(M[0][1], M[0][0],\
    \ d);\n  } else {\n    auto [Q, R] = A.div_with_rem(B);\n    if (R.is_zero())\
    \ return std::make_tuple(PolyT{}, PolyT{1}, B);\n    auto [M, d] = detail::cogcd(B,\
    \ R);\n    M           = M * polynomial_gcd_matrix<PolyT>({}, {1}, {1}, -Q);\n\
    \    return std::make_tuple(M[0][0], M[0][1], d);\n  }\n}\n\ntemplate <typename\
    \ PolyT>\nstd::optional<PolyT> poly_inv(const PolyT &A, const PolyT &modular)\
    \ {\n  auto [x, y, d] = poly_ext_gcd(A, modular);\n  if (d.deg() != 0) return\
    \ {};\n  std::for_each(x.begin(), x.end(), [iv = d.front().inv()](auto &&v) {\
    \ v *= iv; });\n  return x;\n}\n\nLIB_END\n\n\n"
  code: "#ifndef POLY_EXTENDED_GCD_HPP\n#define POLY_EXTENDED_GCD_HPP\n\n#include\
    \ \"../common.hpp\"\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n\
    #include <optional>\n#include <tuple>\n#include <utility>\n\nLIB_BEGIN\n\n// helper\
    \ class for Euclidean algorithm\ntemplate <typename PolyT>\nclass polynomial_gcd_matrix\
    \ : public std::array<std::array<PolyT, 2>, 2> {\n  using MyBase = std::array<std::array<PolyT,\
    \ 2>, 2>;\n\npublic:\n  polynomial_gcd_matrix(const PolyT &m00, const PolyT &m01,\
    \ const PolyT &m10, const PolyT &m11)\n      : MyBase{std::array<PolyT, 2>{m00,\
    \ m01}, std::array<PolyT, 2>{m10, m11}} {}\n  polynomial_gcd_matrix operator*(const\
    \ polynomial_gcd_matrix &rhs) const {\n    return polynomial_gcd_matrix((*this)[0][0]\
    \ * rhs[0][0] + (*this)[0][1] * rhs[1][0],\n                                 (*this)[0][0]\
    \ * rhs[0][1] + (*this)[0][1] * rhs[1][1],\n                                 (*this)[1][0]\
    \ * rhs[0][0] + (*this)[1][1] * rhs[1][0],\n                                 (*this)[1][0]\
    \ * rhs[0][1] + (*this)[1][1] * rhs[1][1]);\n  }\n  std::array<PolyT, 2> operator*(const\
    \ std::array<PolyT, 2> &rhs) const {\n    return {(*this)[0][0] * rhs[0] + (*this)[0][1]\
    \ * rhs[1],\n            (*this)[1][0] * rhs[0] + (*this)[1][1] * rhs[1]};\n \
    \ }\n};\n\nnamespace detail {\n\ntemplate <typename PolyT>\npolynomial_gcd_matrix<PolyT>\
    \ hgcd(const PolyT &A, const PolyT &B) {\n  assert(A.deg() > B.deg());\n  assert(!B.is_zero());\n\
    \  int m = (A.deg() + 1) >> 1;\n  if (B.deg() < m) return polynomial_gcd_matrix<PolyT>({1},\
    \ {}, {}, {1});\n  auto R      = hgcd(PolyT(A.cbegin() + m, A.cend()), PolyT(B.cbegin()\
    \ + m, B.cend()));\n  auto [C, D] = R * std::array<PolyT, 2>{A, B};\n  if (D.deg()\
    \ < m) return R;\n  auto [Q, E] = C.div_with_rem(D);\n  if (E.deg() < m) return\
    \ polynomial_gcd_matrix<PolyT>({}, {1}, {1}, -Q) * R;\n  int k = (m << 1) - D.deg();\n\
    \  return hgcd(PolyT(D.cbegin() + k, D.cend()), PolyT(E.cbegin() + k, E.cend()))\
    \ *\n         polynomial_gcd_matrix<PolyT>({}, {1}, {1}, -Q) * R;\n}\n\ntemplate\
    \ <typename PolyT>\nstd::pair<polynomial_gcd_matrix<PolyT>, PolyT> cogcd(const\
    \ PolyT &A, const PolyT &B) {\n  assert(A.deg() > B.deg());\n  assert(!B.is_zero());\n\
    \  polynomial_gcd_matrix<PolyT> M({1}, {}, {}, {1});\n  PolyT A_cpy(A), B_cpy(B);\n\
    \  for (;;) {\n    auto M0     = hgcd(A_cpy, B_cpy);\n    auto [C, D] = M0 * std::array<PolyT,\
    \ 2>{A_cpy, B_cpy};\n    if (D.is_zero()) return std::make_pair(M0 * M, C);\n\
    \    auto [Q, E] = C.div_with_rem(D);\n    M0          = polynomial_gcd_matrix<PolyT>({},\
    \ {1}, {1}, -Q) * M0;\n    if (E.is_zero()) return std::make_pair(M0 * M, D);\n\
    \    A_cpy.swap(D), B_cpy.swap(E);\n    M = M0 * M;\n  }\n}\n\n} // namespace\
    \ detail\n\ntemplate <typename PolyT>\nstd::tuple<PolyT, PolyT, PolyT> poly_ext_gcd(const\
    \ PolyT &A, const PolyT &B) {\n  if (B.is_zero()) return std::make_tuple(PolyT{1},\
    \ PolyT{}, A);\n  if (A.is_zero()) return std::make_tuple(PolyT{}, PolyT{1}, B);\n\
    \  if (A.deg() > B.deg()) {\n    auto [M, d] = detail::cogcd(A, B);\n    return\
    \ std::make_tuple(M[0][0], M[0][1], d);\n  } else if (A.deg() < B.deg()) {\n \
    \   auto [M, d] = detail::cogcd(B, A);\n    return std::make_tuple(M[0][1], M[0][0],\
    \ d);\n  } else {\n    auto [Q, R] = A.div_with_rem(B);\n    if (R.is_zero())\
    \ return std::make_tuple(PolyT{}, PolyT{1}, B);\n    auto [M, d] = detail::cogcd(B,\
    \ R);\n    M           = M * polynomial_gcd_matrix<PolyT>({}, {1}, {1}, -Q);\n\
    \    return std::make_tuple(M[0][0], M[0][1], d);\n  }\n}\n\ntemplate <typename\
    \ PolyT>\nstd::optional<PolyT> poly_inv(const PolyT &A, const PolyT &modular)\
    \ {\n  auto [x, y, d] = poly_ext_gcd(A, modular);\n  if (d.deg() != 0) return\
    \ {};\n  std::for_each(x.begin(), x.end(), [iv = d.front().inv()](auto &&v) {\
    \ v *= iv; });\n  return x;\n}\n\nLIB_END\n\n#endif\n"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: math/poly_extended_gcd.hpp
  requiredBy: []
  timestamp: '2023-01-14 11:55:02+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
documentation_of: math/poly_extended_gcd.hpp
layout: document
title: Extended Euclidean Algorithm (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT
  prime $p$)
---
