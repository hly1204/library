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
  bundledCode: "#line 1 \"math/matrix/characteristic_polynomial.hpp\"\n\n\n\r\n/**\r\
    \n * @brief characteristic polynomial / \u7279\u5F81\u591A\u9879\u5F0F\r\n *\r\
    \n */\r\n\r\n#include <vector>\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief\
    \ \u83B7\u53D6\u65B9\u9635\u7684\u7279\u5F81\u591A\u9879\u5F0F\r\n * @note \u7279\
    \u5F81\u591A\u9879\u5F0F det(xI-m) \u800C\u975E det(m-xI)\r\n * @tparam Type \u65B9\
    \u9635\u4E2D\u7684\u5143\u7D20\r\n * @param m \u65B9\u9635 m\r\n * @return std::vector<Type>\r\
    \n */\r\ntemplate <typename MatType, typename Type = typename MatType::value_type>\r\
    \nstd::vector<Type> get_charpoly(const MatType &m) {\r\n  auto h = m.to_upper_Hessenberg();\r\
    \n  int n  = m.row();\r\n  std::vector<std::vector<Type>> p(n + 1);\r\n  p[0]\
    \ = {Type(1)};\r\n  for (int i = 1; i <= n; ++i) {\r\n    const std::vector<Type>\
    \ &pi_1 = p[i - 1];\r\n    std::vector<Type> &pi         = p[i];\r\n    pi.resize(i\
    \ + 1, Type(0));\r\n    Type v = -h.at(i - 1, i - 1);\r\n    for (int j = 0; j\
    \ < i; ++j) {\r\n      pi[j] += pi_1[j] * v;\r\n      pi[j + 1] += pi_1[j];\r\n\
    \    }\r\n    Type t(1);\r\n    for (int j = 1; j < i; ++j) {\r\n      t *= h.at(i\
    \ - j, i - j - 1);\r\n      Type prod = t * h.at(i - j - 1, i - 1);\r\n      if\
    \ (prod == Type(0)) continue;\r\n      for (int k = 0; k <= i - j - 1; ++k) pi[k]\
    \ -= prod * p[i - j - 1][k];\r\n    }\r\n  }\r\n  return p[n];\r\n}\r\n\r\n} //\
    \ namespace lib\r\n\r\n\n"
  code: "#ifndef CHARACTERISTIC_POLYNOMIAL_HEADER_HPP\r\n#define CHARACTERISTIC_POLYNOMIAL_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief characteristic polynomial / \u7279\u5F81\u591A\u9879\u5F0F\
    \r\n *\r\n */\r\n\r\n#include <vector>\r\n\r\nnamespace lib {\r\n\r\n/**\r\n *\
    \ @brief \u83B7\u53D6\u65B9\u9635\u7684\u7279\u5F81\u591A\u9879\u5F0F\r\n * @note\
    \ \u7279\u5F81\u591A\u9879\u5F0F det(xI-m) \u800C\u975E det(m-xI)\r\n * @tparam\
    \ Type \u65B9\u9635\u4E2D\u7684\u5143\u7D20\r\n * @param m \u65B9\u9635 m\r\n\
    \ * @return std::vector<Type>\r\n */\r\ntemplate <typename MatType, typename Type\
    \ = typename MatType::value_type>\r\nstd::vector<Type> get_charpoly(const MatType\
    \ &m) {\r\n  auto h = m.to_upper_Hessenberg();\r\n  int n  = m.row();\r\n  std::vector<std::vector<Type>>\
    \ p(n + 1);\r\n  p[0] = {Type(1)};\r\n  for (int i = 1; i <= n; ++i) {\r\n   \
    \ const std::vector<Type> &pi_1 = p[i - 1];\r\n    std::vector<Type> &pi     \
    \    = p[i];\r\n    pi.resize(i + 1, Type(0));\r\n    Type v = -h.at(i - 1, i\
    \ - 1);\r\n    for (int j = 0; j < i; ++j) {\r\n      pi[j] += pi_1[j] * v;\r\n\
    \      pi[j + 1] += pi_1[j];\r\n    }\r\n    Type t(1);\r\n    for (int j = 1;\
    \ j < i; ++j) {\r\n      t *= h.at(i - j, i - j - 1);\r\n      Type prod = t *\
    \ h.at(i - j - 1, i - 1);\r\n      if (prod == Type(0)) continue;\r\n      for\
    \ (int k = 0; k <= i - j - 1; ++k) pi[k] -= prod * p[i - j - 1][k];\r\n    }\r\
    \n  }\r\n  return p[n];\r\n}\r\n\r\n} // namespace lib\r\n\r\n#endif\r\n"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/characteristic_polynomial.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
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
