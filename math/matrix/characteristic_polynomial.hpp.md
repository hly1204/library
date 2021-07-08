---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "characteristic polynomial / \u7279\u5F81\u591A\u9879\u5F0F"
    links: []
  bundledCode: "#line 1 \"math/matrix/characteristic_polynomial.hpp\"\n\n\n\n/**\n\
    \ * @brief characteristic polynomial / \u7279\u5F81\u591A\u9879\u5F0F\n *\n */\n\
    \n#include <vector>\n\nnamespace lib {\n\n/**\n * @brief \u83B7\u53D6\u65B9\u9635\
    \u7684\u7279\u5F81\u591A\u9879\u5F0F\n * @note \u7279\u5F81\u591A\u9879\u5F0F\
    \ det(xI-m) \u800C\u975E det(m-xI)\n * @tparam Type \u65B9\u9635\u4E2D\u7684\u5143\
    \u7D20\n * @param m \u65B9\u9635 m\n * @return std::vector<Type>\n */\ntemplate\
    \ <typename MatType, typename Type = typename MatType::value_type>\nstd::vector<Type>\
    \ get_charpoly(const MatType &m) {\n  auto h = m.to_upper_Hessenberg();\n  int\
    \ n = m.row();\n  std::vector<std::vector<Type>> p(n + 1);\n  p[0] = {Type(1)};\n\
    \  for (int i = 1; i <= n; ++i) {\n    const std::vector<Type> &pi_1 = p[i - 1];\n\
    \    std::vector<Type> &pi = p[i];\n    pi.resize(i + 1, Type(0));\n    Type v\
    \ = -h.at(i - 1, i - 1);\n    for (int j = 0; j < i; ++j) {\n      pi[j] += pi_1[j]\
    \ * v;\n      pi[j + 1] += pi_1[j];\n    }\n    Type t(1);\n    for (int j = 1;\
    \ j < i; ++j) {\n      t *= h.at(i - j, i - j - 1);\n      Type prod = t * h.at(i\
    \ - j - 1, i - 1);\n      if (prod == Type(0)) continue;\n      for (int k = 0;\
    \ k <= i - j - 1; ++k) pi[k] -= prod * p[i - j - 1][k];\n    }\n  }\n  return\
    \ p[n];\n}\n\n} // namespace lib\n\n\n"
  code: "#ifndef CHARACTERISTIC_POLYNOMIAL_HEADER_HPP\n#define CHARACTERISTIC_POLYNOMIAL_HEADER_HPP\n\
    \n/**\n * @brief characteristic polynomial / \u7279\u5F81\u591A\u9879\u5F0F\n\
    \ *\n */\n\n#include <vector>\n\nnamespace lib {\n\n/**\n * @brief \u83B7\u53D6\
    \u65B9\u9635\u7684\u7279\u5F81\u591A\u9879\u5F0F\n * @note \u7279\u5F81\u591A\u9879\
    \u5F0F det(xI-m) \u800C\u975E det(m-xI)\n * @tparam Type \u65B9\u9635\u4E2D\u7684\
    \u5143\u7D20\n * @param m \u65B9\u9635 m\n * @return std::vector<Type>\n */\n\
    template <typename MatType, typename Type = typename MatType::value_type>\nstd::vector<Type>\
    \ get_charpoly(const MatType &m) {\n  auto h = m.to_upper_Hessenberg();\n  int\
    \ n = m.row();\n  std::vector<std::vector<Type>> p(n + 1);\n  p[0] = {Type(1)};\n\
    \  for (int i = 1; i <= n; ++i) {\n    const std::vector<Type> &pi_1 = p[i - 1];\n\
    \    std::vector<Type> &pi = p[i];\n    pi.resize(i + 1, Type(0));\n    Type v\
    \ = -h.at(i - 1, i - 1);\n    for (int j = 0; j < i; ++j) {\n      pi[j] += pi_1[j]\
    \ * v;\n      pi[j + 1] += pi_1[j];\n    }\n    Type t(1);\n    for (int j = 1;\
    \ j < i; ++j) {\n      t *= h.at(i - j, i - j - 1);\n      Type prod = t * h.at(i\
    \ - j - 1, i - 1);\n      if (prod == Type(0)) continue;\n      for (int k = 0;\
    \ k <= i - j - 1; ++k) pi[k] -= prod * p[i - j - 1][k];\n    }\n  }\n  return\
    \ p[n];\n}\n\n} // namespace lib\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/characteristic_polynomial.hpp
  requiredBy: []
  timestamp: '2021-06-28 18:43:38+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
  - remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
documentation_of: math/matrix/characteristic_polynomial.hpp
layout: document
redirect_from:
- /library/math/matrix/characteristic_polynomial.hpp
- /library/math/matrix/characteristic_polynomial.hpp.html
title: "characteristic polynomial / \u7279\u5F81\u591A\u9879\u5F0F"
---
