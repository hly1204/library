---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "solve linear equations Lanczos / \u6C42\u89E3\u7EBF\u6027\u65B9\
      \u7A0B\u7EC4 Lanczos \u7B97\u6CD5"
    links: []
  bundledCode: "#line 1 \"math/matrix/solve_linear_equations_Lanczos.hpp\"\n\n\n\n\
    /**\n * @brief solve linear equations Lanczos / \u6C42\u89E3\u7EBF\u6027\u65B9\
    \u7A0B\u7EC4 Lanczos \u7B97\u6CD5\n *\n */\n\n#include <algorithm>\n#include <cassert>\n\
    #include <functional>\n#include <numeric>\n#include <optional>\n#include <vector>\n\
    \nnamespace lib {\n\nnamespace internal {\n\n/**\n * @brief \u6807\u51C6 Lanczos\
    \ \u7B97\u6CD5\n * @note \u8981\u6C42 M \u4E3A\u5BF9\u79F0\u65B9\u9635\u5373\u8F6C\
    \u7F6E\u4E3A\u81EA\u8EAB\u7684\u65B9\u9635\n *       \u8BE5\u7B97\u6CD5\u672A\u6D4B\
    \u8BD5\uFF01\n */\ntemplate <typename MatType, typename Type = typename MatType::value_type>\n\
    std::optional<std::vector<Type>> standard_Lanczos(const MatType &A, const std::vector<Type>\
    \ &b) {\n  int n = b.size();\n\n  assert(A.col() == A.row());\n  assert(n == A.row());\n\
    \n  const Type ZERO(0);\n\n  auto is_zero_vec = [ZERO](const std::vector<Type>\
    \ &v) -> bool {\n    return std::count(v.begin(), v.end(), ZERO) == v.size();\n\
    \  };\n\n  auto dot_product = [ZERO](const std::vector<Type> &a, const std::vector<Type>\
    \ &b) -> Type {\n    // \u8FD4\u56DE a^T b \u6807\u51C6\u7684\u5185\u79EF\n  \
    \  return std::inner_product(a.begin(), a.end(), b.begin(), ZERO);\n  };\n\n \
    \ if (is_zero_vec(b)) return std::vector<Type>(n, ZERO);\n\n  Type t_m1(1);\n\
    \  std::vector<Type> w_m1(n, ZERO), w_0(b);\n  std::vector<Type> v_0(w_m1), v_1(A.apply(w_0));\n\
    \  Type t_0 = dot_product(v_1, w_0);\n\n  if (t_0 == ZERO) return {};\n\n  std::vector<Type>\
    \ x(b);\n  Type tmp_0 = dot_product(w_0, b) / t_0;\n  for (auto &i : x) i *= tmp_0;\n\
    \  for (;;) {\n    Type tmp_1 = dot_product(v_1, v_1) / t_0, tmp_2 = dot_product(v_1,\
    \ v_0) / t_m1;\n    for (int i = 0; i < n; ++i) w_m1[i] = v_1[i] - tmp_1 * w_0[i]\
    \ - tmp_2 * w_m1[i];\n    std::swap(w_m1, w_0);\n    if (is_zero_vec(w_0)) return\
    \ A.apply(x) == b ? std::make_optional(x) : std::nullopt;\n    std::swap(v_0 =\
    \ A.apply(w_0), v_1);\n    std::swap(t_m1 = dot_product(v_1, w_0), t_0);\n   \
    \ if (t_0 == ZERO) return {};\n    Type tmp_3 = dot_product(w_0, b) / t_0;\n \
    \   for (int i = 0; i < n; ++i) x[i] += tmp_3 * w_0[i];\n  }\n}\n\n} // namespace\
    \ internal\n\n// TODO\n\n/**\n * @brief \u6C42\u89E3\u7EBF\u6027\u65B9\u7A0B\u7EC4\
    \u7684\u968F\u673A\u5316 Lanczos \u7B97\u6CD5\n * @note \u5BF9\u77E9\u9635\u4E0D\
    \u8981\u6C42\u5176\u4E3A\u65B9\u9635\n * @ref Wayne Eberly and Erich Kaltofen.\
    \ On Randomized Lanczos Algorithms. 1997.\n * @param A\n * @param b\n * @return\
    \ std::optional<std::vector<Type>> \u5411\u91CF x \u6EE1\u8DB3 Ax=b\n */\ntemplate\
    \ <typename MatType, typename Type = typename MatType::value_type>\nstd::optional<std::vector<Type>>\
    \ solve_linear_equations_Lanczos(const MatType &A,\n                         \
    \                                       const std::vector<Type> &b) {\n  return\
    \ internal::standard_Lanczos(A, b);\n}\n\n} // namespace lib\n\n\n"
  code: "#ifndef SOLVE_LINEAR_EQUATIONS_LANCZOS_HEADER_HPP\n#define SOLVE_LINEAR_EQUATIONS_LANCZOS_HEADER_HPP\n\
    \n/**\n * @brief solve linear equations Lanczos / \u6C42\u89E3\u7EBF\u6027\u65B9\
    \u7A0B\u7EC4 Lanczos \u7B97\u6CD5\n *\n */\n\n#include <algorithm>\n#include <cassert>\n\
    #include <functional>\n#include <numeric>\n#include <optional>\n#include <vector>\n\
    \nnamespace lib {\n\nnamespace internal {\n\n/**\n * @brief \u6807\u51C6 Lanczos\
    \ \u7B97\u6CD5\n * @note \u8981\u6C42 M \u4E3A\u5BF9\u79F0\u65B9\u9635\u5373\u8F6C\
    \u7F6E\u4E3A\u81EA\u8EAB\u7684\u65B9\u9635\n *       \u8BE5\u7B97\u6CD5\u672A\u6D4B\
    \u8BD5\uFF01\n */\ntemplate <typename MatType, typename Type = typename MatType::value_type>\n\
    std::optional<std::vector<Type>> standard_Lanczos(const MatType &A, const std::vector<Type>\
    \ &b) {\n  int n = b.size();\n\n  assert(A.col() == A.row());\n  assert(n == A.row());\n\
    \n  const Type ZERO(0);\n\n  auto is_zero_vec = [ZERO](const std::vector<Type>\
    \ &v) -> bool {\n    return std::count(v.begin(), v.end(), ZERO) == v.size();\n\
    \  };\n\n  auto dot_product = [ZERO](const std::vector<Type> &a, const std::vector<Type>\
    \ &b) -> Type {\n    // \u8FD4\u56DE a^T b \u6807\u51C6\u7684\u5185\u79EF\n  \
    \  return std::inner_product(a.begin(), a.end(), b.begin(), ZERO);\n  };\n\n \
    \ if (is_zero_vec(b)) return std::vector<Type>(n, ZERO);\n\n  Type t_m1(1);\n\
    \  std::vector<Type> w_m1(n, ZERO), w_0(b);\n  std::vector<Type> v_0(w_m1), v_1(A.apply(w_0));\n\
    \  Type t_0 = dot_product(v_1, w_0);\n\n  if (t_0 == ZERO) return {};\n\n  std::vector<Type>\
    \ x(b);\n  Type tmp_0 = dot_product(w_0, b) / t_0;\n  for (auto &i : x) i *= tmp_0;\n\
    \  for (;;) {\n    Type tmp_1 = dot_product(v_1, v_1) / t_0, tmp_2 = dot_product(v_1,\
    \ v_0) / t_m1;\n    for (int i = 0; i < n; ++i) w_m1[i] = v_1[i] - tmp_1 * w_0[i]\
    \ - tmp_2 * w_m1[i];\n    std::swap(w_m1, w_0);\n    if (is_zero_vec(w_0)) return\
    \ A.apply(x) == b ? std::make_optional(x) : std::nullopt;\n    std::swap(v_0 =\
    \ A.apply(w_0), v_1);\n    std::swap(t_m1 = dot_product(v_1, w_0), t_0);\n   \
    \ if (t_0 == ZERO) return {};\n    Type tmp_3 = dot_product(w_0, b) / t_0;\n \
    \   for (int i = 0; i < n; ++i) x[i] += tmp_3 * w_0[i];\n  }\n}\n\n} // namespace\
    \ internal\n\n// TODO\n\n/**\n * @brief \u6C42\u89E3\u7EBF\u6027\u65B9\u7A0B\u7EC4\
    \u7684\u968F\u673A\u5316 Lanczos \u7B97\u6CD5\n * @note \u5BF9\u77E9\u9635\u4E0D\
    \u8981\u6C42\u5176\u4E3A\u65B9\u9635\n * @ref Wayne Eberly and Erich Kaltofen.\
    \ On Randomized Lanczos Algorithms. 1997.\n * @param A\n * @param b\n * @return\
    \ std::optional<std::vector<Type>> \u5411\u91CF x \u6EE1\u8DB3 Ax=b\n */\ntemplate\
    \ <typename MatType, typename Type = typename MatType::value_type>\nstd::optional<std::vector<Type>>\
    \ solve_linear_equations_Lanczos(const MatType &A,\n                         \
    \                                       const std::vector<Type> &b) {\n  return\
    \ internal::standard_Lanczos(A, b);\n}\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/solve_linear_equations_Lanczos.hpp
  requiredBy: []
  timestamp: '2021-07-05 14:46:07+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/matrix/solve_linear_equations_Lanczos.hpp
layout: document
redirect_from:
- /library/math/matrix/solve_linear_equations_Lanczos.hpp
- /library/math/matrix/solve_linear_equations_Lanczos.hpp.html
title: "solve linear equations Lanczos / \u6C42\u89E3\u7EBF\u6027\u65B9\u7A0B\u7EC4\
  \ Lanczos \u7B97\u6CD5"
---
