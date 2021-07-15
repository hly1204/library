---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: remote_test/yosupo/string/z_algorithm.0.test.cpp
    title: remote_test/yosupo/string/z_algorithm.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "Z algorithm / Z \u7B97\u6CD5"
    links: []
  bundledCode: "#line 1 \"string/z_algorithm.hpp\"\n\n\n\r\n/**\r\n * @brief Z algorithm\
    \ / Z \u7B97\u6CD5\r\n *\r\n */\r\n\r\n#include <algorithm>\r\n#include <vector>\r\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u83B7\u53D6 z \u6570\u7EC4\r\n\
    \ * @note z[i] \u4E3A s \u4ECE i \u5F00\u59CB\u7684\u540E\u7F00\u4E0E s \u7684\
    \u6700\u957F\u516C\u5171\u524D\u7F00\u7684\u957F\u5EA6\r\n * @tparam Container\
    \ \u5BB9\u5668\r\n * @param s \u5B57\u7B26\u4E32\r\n * @return std::vector<int>\r\
    \n */\r\ntemplate <typename Container>\r\nstd::vector<int> get_z(const Container\
    \ &s) {\r\n  int n = s.size();\r\n  std::vector<int> z(n, 0);\r\n  if (n == 0)\
    \ return z;\r\n  z[0] = n;\r\n  // Z-box \u5373 s[l..r]=s[0..r-l+1]\r\n  // \u6211\
    \u4EEC\u7EF4\u62A4 r \u6700\u53F3\u7684 Z-box\r\n  // \u5F53\u5F53\u524D\u7D22\
    \u5F15 i \u5728 Z-box \u4E2D\u65F6\uFF0C\u53EF\u4EE5\u5229\u7528\u524D\u9762\u8BA1\
    \u7B97\u5B8C\u6BD5\u7684 z[i-l] \u503C\u6765\u6269\u5C55\r\n  // \u4F46\u662F\u6CE8\
    \u610F\uFF0C\u82E5 l+z[i-l] > r \u4E86\uFF0C\u4E5F\u5FC5\u987B\u4ECE Z-box \u7684\
    \ r \u5F00\u59CB\u6269\u5C55\uFF0C\u56E0\u4E3A\u540E\u9762\u7684\u5B57\u7B26\u538B\
    \u6839\u6CA1\u6709\u626B\u63CF\u5230\uFF01\r\n  // \u82E5 z[i-l] \u7684 Z-box\
    \ \u7684 r \u6CA1\u6709\u5F53\u524D\u7684 r \u5927\uFF0C\u5176\u5B9E\u4E0D\u7528\
    \u518D\u6269\u5C55\u4E86\uFF0C\u8FD9\u91CC\u6CA1\u6709\u663E\u5F0F\u5199\u51FA\
    \r\n  for (int i = 1, l = 0, r = 0; i != n; ++i) {\r\n    if (i <= r) z[i] = std::min(r\
    \ - i + 1, z[i - l]);\r\n    while (z[i] + i < n && s[z[i]] == s[z[i] + i]) ++z[i];\r\
    \n    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;\r\n  }\r\n  return z;\r\n\
    }\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef Z_ALGORITHM_HEADER_HPP\r\n#define Z_ALGORITHM_HEADER_HPP\r\n\r\n\
    /**\r\n * @brief Z algorithm / Z \u7B97\u6CD5\r\n *\r\n */\r\n\r\n#include <algorithm>\r\
    \n#include <vector>\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u83B7\u53D6\
    \ z \u6570\u7EC4\r\n * @note z[i] \u4E3A s \u4ECE i \u5F00\u59CB\u7684\u540E\u7F00\
    \u4E0E s \u7684\u6700\u957F\u516C\u5171\u524D\u7F00\u7684\u957F\u5EA6\r\n * @tparam\
    \ Container \u5BB9\u5668\r\n * @param s \u5B57\u7B26\u4E32\r\n * @return std::vector<int>\r\
    \n */\r\ntemplate <typename Container>\r\nstd::vector<int> get_z(const Container\
    \ &s) {\r\n  int n = s.size();\r\n  std::vector<int> z(n, 0);\r\n  if (n == 0)\
    \ return z;\r\n  z[0] = n;\r\n  // Z-box \u5373 s[l..r]=s[0..r-l+1]\r\n  // \u6211\
    \u4EEC\u7EF4\u62A4 r \u6700\u53F3\u7684 Z-box\r\n  // \u5F53\u5F53\u524D\u7D22\
    \u5F15 i \u5728 Z-box \u4E2D\u65F6\uFF0C\u53EF\u4EE5\u5229\u7528\u524D\u9762\u8BA1\
    \u7B97\u5B8C\u6BD5\u7684 z[i-l] \u503C\u6765\u6269\u5C55\r\n  // \u4F46\u662F\u6CE8\
    \u610F\uFF0C\u82E5 l+z[i-l] > r \u4E86\uFF0C\u4E5F\u5FC5\u987B\u4ECE Z-box \u7684\
    \ r \u5F00\u59CB\u6269\u5C55\uFF0C\u56E0\u4E3A\u540E\u9762\u7684\u5B57\u7B26\u538B\
    \u6839\u6CA1\u6709\u626B\u63CF\u5230\uFF01\r\n  // \u82E5 z[i-l] \u7684 Z-box\
    \ \u7684 r \u6CA1\u6709\u5F53\u524D\u7684 r \u5927\uFF0C\u5176\u5B9E\u4E0D\u7528\
    \u518D\u6269\u5C55\u4E86\uFF0C\u8FD9\u91CC\u6CA1\u6709\u663E\u5F0F\u5199\u51FA\
    \r\n  for (int i = 1, l = 0, r = 0; i != n; ++i) {\r\n    if (i <= r) z[i] = std::min(r\
    \ - i + 1, z[i - l]);\r\n    while (z[i] + i < n && s[z[i]] == s[z[i] + i]) ++z[i];\r\
    \n    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;\r\n  }\r\n  return z;\r\n\
    }\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - remote_test/yosupo/string/z_algorithm.0.test.cpp
documentation_of: string/z_algorithm.hpp
layout: document
redirect_from:
- /library/string/z_algorithm.hpp
- /library/string/z_algorithm.hpp.html
title: "Z algorithm / Z \u7B97\u6CD5"
---
