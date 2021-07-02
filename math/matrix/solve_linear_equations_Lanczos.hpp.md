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
    \u7A0B\u7EC4 Lanczos \u7B97\u6CD5\n *\n */\n\n#include <functional>\n#include\
    \ <optional>\n#include <vector>\n\n// TODO\nnamespace lib {\n\n/**\n * @brief\
    \ \u6C42\u89E3\u7EBF\u6027\u65B9\u7A0B\u7EC4\u7684\u968F\u673A\u5316 Lanczos \u7B97\
    \u6CD5\n * @note \u5BF9\u77E9\u9635\u4E0D\u8981\u6C42\u5176\u4E3A\u65B9\u9635\n\
    \ * @ref Wayne Eberly and Erich Kaltofen. On Randomized Lanczos Algorithms. 1997.\n\
    \ * @param A\n * @param b\n * @return std::optional<std::vector<Type>> \u5411\u91CF\
    \ x \u6EE1\u8DB3 Ax=b\n */\ntemplate <typename MatType, typename Type = typename\
    \ MatType::value_type>\nstd::optional<std::vector<Type>> solve_linear_equations_Lanczos(const\
    \ MatType &A,\n                                                              \
    \  const std::vector<Type> &b) {\n  std::function<std::optional<std::vector<Type>>(const\
    \ MatType &, const std::vector<Type> &)>\n      standard_Lanczos = [](const MatType\
    \ &A, const std::vector<Type> &b) { // \u6807\u51C6 Lanczos \u7B97\u6CD5\n   \
    \     // \u8981\u6C42 M \u4E3A\u5BF9\u79F0\u65B9\u9635\u5373\u8F6C\u7F6E\u4E3A\
    \u81EA\u8EAB\u7684\u65B9\u9635\n\n      };\n  return {};\n}\n\n} // namespace\
    \ lib\n\n\n"
  code: "#ifndef SOLVE_LINEAR_EQUATIONS_LANCZOS_HEADER_HPP\n#define SOLVE_LINEAR_EQUATIONS_LANCZOS_HEADER_HPP\n\
    \n/**\n * @brief solve linear equations Lanczos / \u6C42\u89E3\u7EBF\u6027\u65B9\
    \u7A0B\u7EC4 Lanczos \u7B97\u6CD5\n *\n */\n\n#include <functional>\n#include\
    \ <optional>\n#include <vector>\n\n// TODO\nnamespace lib {\n\n/**\n * @brief\
    \ \u6C42\u89E3\u7EBF\u6027\u65B9\u7A0B\u7EC4\u7684\u968F\u673A\u5316 Lanczos \u7B97\
    \u6CD5\n * @note \u5BF9\u77E9\u9635\u4E0D\u8981\u6C42\u5176\u4E3A\u65B9\u9635\n\
    \ * @ref Wayne Eberly and Erich Kaltofen. On Randomized Lanczos Algorithms. 1997.\n\
    \ * @param A\n * @param b\n * @return std::optional<std::vector<Type>> \u5411\u91CF\
    \ x \u6EE1\u8DB3 Ax=b\n */\ntemplate <typename MatType, typename Type = typename\
    \ MatType::value_type>\nstd::optional<std::vector<Type>> solve_linear_equations_Lanczos(const\
    \ MatType &A,\n                                                              \
    \  const std::vector<Type> &b) {\n  std::function<std::optional<std::vector<Type>>(const\
    \ MatType &, const std::vector<Type> &)>\n      standard_Lanczos = [](const MatType\
    \ &A, const std::vector<Type> &b) { // \u6807\u51C6 Lanczos \u7B97\u6CD5\n   \
    \     // \u8981\u6C42 M \u4E3A\u5BF9\u79F0\u65B9\u9635\u5373\u8F6C\u7F6E\u4E3A\
    \u81EA\u8EAB\u7684\u65B9\u9635\n\n      };\n  return {};\n}\n\n} // namespace\
    \ lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/solve_linear_equations_Lanczos.hpp
  requiredBy: []
  timestamp: '2021-07-03 02:24:28+08:00'
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
