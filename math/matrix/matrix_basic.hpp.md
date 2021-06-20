---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "matrix basic / \u77E9\u9635\u57FA\u7840"
    links: []
  bundledCode: "#line 1 \"math/matrix/matrix_basic.hpp\"\n\n\n\n/**\n * @brief matrix\
    \ basic / \u77E9\u9635\u57FA\u7840\n *\n */\n\n#include <vector>\n\nnamespace\
    \ lib {\n\n// TODO\ntemplate <typename Type, typename Container = std::vector<Type>>\
    \ class Matrix {\npublic:\n  /**\n   * @brief Matrix \u7C7B\n   *\n   * @param\
    \ r \u884C\n   * @param c \u5217\n   * @param v \u521D\u503C\n   */\n  Matrix(int\
    \ r, int c, const Type &v = Type()) : row_(r), col_(c), mat_(row_ * col_, v) {}\n\
    \  ~Matrix() = default;\n\n  Type &at(int r, int c) { return mat_[r * row_ + c];\
    \ }\n  const Type &at(int r, int c) const { return mat_[r * row_ + c]; }\n\nprivate:\n\
    \  int row_, col_;\n  Container mat_;\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef MATRIX_BASIC_HEADER_HPP\n#define MATRIX_BASIC_HEADER_HPP\n\n/**\n\
    \ * @brief matrix basic / \u77E9\u9635\u57FA\u7840\n *\n */\n\n#include <vector>\n\
    \nnamespace lib {\n\n// TODO\ntemplate <typename Type, typename Container = std::vector<Type>>\
    \ class Matrix {\npublic:\n  /**\n   * @brief Matrix \u7C7B\n   *\n   * @param\
    \ r \u884C\n   * @param c \u5217\n   * @param v \u521D\u503C\n   */\n  Matrix(int\
    \ r, int c, const Type &v = Type()) : row_(r), col_(c), mat_(row_ * col_, v) {}\n\
    \  ~Matrix() = default;\n\n  Type &at(int r, int c) { return mat_[r * row_ + c];\
    \ }\n  const Type &at(int r, int c) const { return mat_[r * row_ + c]; }\n\nprivate:\n\
    \  int row_, col_;\n  Container mat_;\n};\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/matrix_basic.hpp
  requiredBy: []
  timestamp: '2021-06-21 01:45:03+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/matrix/matrix_basic.hpp
layout: document
redirect_from:
- /library/math/matrix/matrix_basic.hpp
- /library/math/matrix/matrix_basic.hpp.html
title: "matrix basic / \u77E9\u9635\u57FA\u7840"
---
