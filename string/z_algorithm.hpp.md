---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/string/z_algorithm.0.test.cpp
    title: remote_test/yosupo/string/z_algorithm.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Z algorithm / Z \u7B97\u6CD5"
    links: []
  bundledCode: "#line 1 \"string/z_algorithm.hpp\"\n\n\n\n/**\n * @brief Z algorithm\
    \ / Z \u7B97\u6CD5\n *\n */\n\n#include <algorithm>\n#include <vector>\n\nnamespace\
    \ lib {\n\n/**\n * @brief \u83B7\u53D6 z \u6570\u7EC4\uFF0C z[i] \u4E3A s \u4ECE\
    \ i \u5F00\u59CB\u7684\u540E\u7F00\u4E0E s \u7684\u6700\u957F\u516C\u5171\u524D\
    \u7F00\u7684\u957F\u5EA6\n *\n * @tparam Container \u5BB9\u5668\n * @param s \u5B57\
    \u7B26\u4E32\n * @return std::vector<int>\n */\ntemplate <typename Container>\
    \ std::vector<int> get_z(const Container &s) {\n  int n = s.size();\n  std::vector<int>\
    \ z(n, 0);\n  if (n == 0) return z;\n  z[0] = n;\n  // Z-box \u5373 s[l..r]=s[0..r-l+1]\n\
    \  // \u6211\u4EEC\u7EF4\u62A4 r \u6700\u53F3\u7684 Z-box\n  // \u5F53\u5F53\u524D\
    \u7D22\u5F15 i \u5728 Z-box \u4E2D\u65F6\uFF0C\u53EF\u4EE5\u5229\u7528\u524D\u9762\
    \u8BA1\u7B97\u5B8C\u6BD5\u7684 z[i-l] \u503C\u6765\u6269\u5C55\n  // \u4F46\u662F\
    \u6CE8\u610F\uFF0C\u82E5 l+z[i-l] > r \u4E86\uFF0C\u4E5F\u5FC5\u987B\u4ECE Z-box\
    \ \u7684 r \u5F00\u59CB\u6269\u5C55\uFF0C\u56E0\u4E3A\u540E\u9762\u7684\u5B57\u7B26\
    \u538B\u6839\u6CA1\u6709\u626B\u63CF\u5230\uFF01\n  // \u82E5 z[i-l] \u7684 Z-box\
    \ \u7684 r \u6CA1\u6709\u5F53\u524D\u7684 r \u5927\uFF0C\u5176\u5B9E\u4E0D\u7528\
    \u518D\u6269\u5C55\u4E86\uFF0C\u8FD9\u91CC\u6CA1\u6709\u663E\u5F0F\u5199\u51FA\
    \n  for (int i = 1, l = 0, r = 0; i != n; ++i) {\n    if (i <= r) z[i] = std::min(r\
    \ - i + 1, z[i - l]);\n    while (z[i] + i < n && s[z[i]] == s[z[i] + i]) ++z[i];\n\
    \    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;\n  }\n  return z;\n}\n\n}\
    \ // namespace lib\n\n\n"
  code: "#ifndef Z_ALGORITHM_HEADER_HPP\n#define Z_ALGORITHM_HEADER_HPP\n\n/**\n *\
    \ @brief Z algorithm / Z \u7B97\u6CD5\n *\n */\n\n#include <algorithm>\n#include\
    \ <vector>\n\nnamespace lib {\n\n/**\n * @brief \u83B7\u53D6 z \u6570\u7EC4\uFF0C\
    \ z[i] \u4E3A s \u4ECE i \u5F00\u59CB\u7684\u540E\u7F00\u4E0E s \u7684\u6700\u957F\
    \u516C\u5171\u524D\u7F00\u7684\u957F\u5EA6\n *\n * @tparam Container \u5BB9\u5668\
    \n * @param s \u5B57\u7B26\u4E32\n * @return std::vector<int>\n */\ntemplate <typename\
    \ Container> std::vector<int> get_z(const Container &s) {\n  int n = s.size();\n\
    \  std::vector<int> z(n, 0);\n  if (n == 0) return z;\n  z[0] = n;\n  // Z-box\
    \ \u5373 s[l..r]=s[0..r-l+1]\n  // \u6211\u4EEC\u7EF4\u62A4 r \u6700\u53F3\u7684\
    \ Z-box\n  // \u5F53\u5F53\u524D\u7D22\u5F15 i \u5728 Z-box \u4E2D\u65F6\uFF0C\
    \u53EF\u4EE5\u5229\u7528\u524D\u9762\u8BA1\u7B97\u5B8C\u6BD5\u7684 z[i-l] \u503C\
    \u6765\u6269\u5C55\n  // \u4F46\u662F\u6CE8\u610F\uFF0C\u82E5 l+z[i-l] > r \u4E86\
    \uFF0C\u4E5F\u5FC5\u987B\u4ECE Z-box \u7684 r \u5F00\u59CB\u6269\u5C55\uFF0C\u56E0\
    \u4E3A\u540E\u9762\u7684\u5B57\u7B26\u538B\u6839\u6CA1\u6709\u626B\u63CF\u5230\
    \uFF01\n  // \u82E5 z[i-l] \u7684 Z-box \u7684 r \u6CA1\u6709\u5F53\u524D\u7684\
    \ r \u5927\uFF0C\u5176\u5B9E\u4E0D\u7528\u518D\u6269\u5C55\u4E86\uFF0C\u8FD9\u91CC\
    \u6CA1\u6709\u663E\u5F0F\u5199\u51FA\n  for (int i = 1, l = 0, r = 0; i != n;\
    \ ++i) {\n    if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);\n    while (z[i]\
    \ + i < n && s[z[i]] == s[z[i] + i]) ++z[i];\n    if (i + z[i] - 1 > r) l = i,\
    \ r = i + z[i] - 1;\n  }\n  return z;\n}\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2021-06-12 14:03:29+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/string/z_algorithm.0.test.cpp
documentation_of: string/z_algorithm.hpp
layout: document
redirect_from:
- /library/string/z_algorithm.hpp
- /library/string/z_algorithm.hpp.html
title: "Z algorithm / Z \u7B97\u6CD5"
---
