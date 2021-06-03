---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: remote_test/yosupo/string/suffix_array.0.test.cpp
    title: remote_test/yosupo/string/suffix_array.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://cp-algorithms.com/string/suffix-array.html
  bundledCode: "#line 1 \"string/suffix_array_sais.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <string>\n#include <vector>\n\nnamespace lib {\n\nnamespace internal\
    \ {\n\nstd::vector<int> SA_IS(const std::vector<int> &s, int K) {\n  const int\
    \ n = s.size();\n  std::vector<bool> t(n);\n  std::vector<int> bkt(K, 0), bkt_l(K),\
    \ bkt_r(K), SA(n), p1;\n#define is_S_type(x) (t[x])\n#define is_L_type(x) (!t[x])\n\
    #define is_LMS_type(x) (is_S_type(x) && x != 0 && is_L_type(x - 1))\n#define induced_sort()\
    \                                                                            \
    \ \\\n  do {                                                                 \
    \                            \\\n    std::copy_n(bkt_l.begin(), K, bkt.begin());\
    \                                                    \\\n    for (int i = 0, j;\
    \ i != n; ++i)                                                               \
    \ \\\n      if ((j = SA[i] - 1) >= 0 && is_L_type(j)) SA[bkt[s[j]]++] = j;   \
    \                            \\\n    std::copy_n(bkt_r.begin(), K, bkt.begin());\
    \                                                    \\\n    for (int i = n -\
    \ 1, j; i >= 0; --i)                                                         \
    \   \\\n      if ((j = SA[i] - 1) >= 0 && is_S_type(j)) SA[--bkt[s[j]]] = j; \
    \                              \\\n  } while (0)\n  t.back() = true;\n  for (int\
    \ i = n - 2; i >= 0; --i) {\n    t[i] = (s[i] < s[i + 1] || (is_S_type(i + 1)\
    \ && s[i] == s[i + 1]));\n    if (is_LMS_type(i + 1)) p1.push_back(i + 1);\n \
    \ }\n  std::reverse(p1.begin(), p1.end());\n  const int n1 = p1.size();\n  for\
    \ (int i = 0; i != n; ++i) ++bkt[s[i]];\n  for (int i = 0, sum = 0; i != K; ++i)\
    \ sum += bkt[i], bkt_r[i] = sum, bkt_l[i] = sum - bkt[i];\n  std::vector<int>\
    \ s1(n1), SA1(n1);\n  std::fill_n(SA.begin(), n, -1);\n  std::copy_n(bkt_r.begin(),\
    \ K, bkt.begin());\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] =\
    \ p1[i];\n  induced_sort();\n  for (int i = 0, j = 0; i != n; ++i)\n    if (is_LMS_type(SA[i]))\
    \ SA1[j++] = SA[i];\n  int name = 0;\n  for (int i = 0, prev = -1; i != n1; ++i)\
    \ {\n    int pos = SA1[i];\n    for (int j = 0;; ++j)\n      if (prev == -1 ||\
    \ s[pos + j] != s[prev + j] || is_S_type(pos + j) != is_S_type(prev + j)) {\n\
    \        prev = pos, ++name;\n        break;\n      } else if (j != 0 && (is_LMS_type(pos\
    \ + j) || is_LMS_type(prev + j)))\n        break;\n    SA[pos] = name - 1;\n \
    \ }\n  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];\n  if (name != n1)\n \
    \   SA1 = SA_IS(s1, name);\n  else\n    for (int i = 0; i != n1; ++i) SA1[s1[i]]\
    \ = i;\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\n  std::fill_n(SA.begin(),\
    \ n, -1);\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];\n\
    \  induced_sort();\n#undef is_S_type\n#undef is_L_type\n#undef is_LMS_type\n#undef\
    \ induced_sort\n  return SA;\n}\n\n} // namespace internal\n\nstd::vector<int>\
    \ get_sa(const std::string &s) {\n  std::vector<int> s_cpy(s.size() + 1);\n  std::copy(s.begin(),\
    \ s.end(), s_cpy.begin());\n  s_cpy.back() = 0;\n  std::vector<int> SA(internal::SA_IS(s_cpy,\
    \ 128));\n  SA.erase(SA.begin());\n  return SA;\n}\n\n// reference: https://cp-algorithms.com/string/suffix-array.html\n\
    std::vector<int> get_height(const std::string &s, const std::vector<int> &SA)\
    \ {\n  int n = s.size();\n  std::vector<int> rk(n), height(n - 1, 0);\n  // height[i]\
    \ = s[SA[i]..n-1] \u4E0E s[SA[i+1]..n-1] \u7684\u6700\u957F\u516C\u5171\u524D\u7F00\
    \uFF08 longest common prefix \uFF09\n  // Kasai \u7684\u8BBA\u6587\u4E2D\u79F0\
    \u5176\u4E3A lcp \u6570\u7EC4\u6216 height \u6570\u7EC4\n  for (int i = 0; i !=\
    \ n; ++i) rk[SA[i]] = i;\n  for (int i = 0, h = 0; i != n; ++i) {\n    if (rk[i]\
    \ == n - 1) {\n      h = 0;\n      continue;\n    }\n    int j = SA[rk[i] + 1];\n\
    \    while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;\n    height[rk[i]]\
    \ = h;\n    if (h != 0) --h;\n  }\n  return height;\n}\n\n} // namespace lib\n\
    \n\n"
  code: "#ifndef SUFFIX_ARRAY_SAIS_HEADER_HPP\n#define SUFFIX_ARRAY_SAIS_HEADER_HPP\n\
    \n#include <algorithm>\n#include <string>\n#include <vector>\n\nnamespace lib\
    \ {\n\nnamespace internal {\n\nstd::vector<int> SA_IS(const std::vector<int> &s,\
    \ int K) {\n  const int n = s.size();\n  std::vector<bool> t(n);\n  std::vector<int>\
    \ bkt(K, 0), bkt_l(K), bkt_r(K), SA(n), p1;\n#define is_S_type(x) (t[x])\n#define\
    \ is_L_type(x) (!t[x])\n#define is_LMS_type(x) (is_S_type(x) && x != 0 && is_L_type(x\
    \ - 1))\n#define induced_sort()                                              \
    \                               \\\n  do {                                   \
    \                                                          \\\n    std::copy_n(bkt_l.begin(),\
    \ K, bkt.begin());                                                    \\\n   \
    \ for (int i = 0, j; i != n; ++i)                                            \
    \                    \\\n      if ((j = SA[i] - 1) >= 0 && is_L_type(j)) SA[bkt[s[j]]++]\
    \ = j;                               \\\n    std::copy_n(bkt_r.begin(), K, bkt.begin());\
    \                                                    \\\n    for (int i = n -\
    \ 1, j; i >= 0; --i)                                                         \
    \   \\\n      if ((j = SA[i] - 1) >= 0 && is_S_type(j)) SA[--bkt[s[j]]] = j; \
    \                              \\\n  } while (0)\n  t.back() = true;\n  for (int\
    \ i = n - 2; i >= 0; --i) {\n    t[i] = (s[i] < s[i + 1] || (is_S_type(i + 1)\
    \ && s[i] == s[i + 1]));\n    if (is_LMS_type(i + 1)) p1.push_back(i + 1);\n \
    \ }\n  std::reverse(p1.begin(), p1.end());\n  const int n1 = p1.size();\n  for\
    \ (int i = 0; i != n; ++i) ++bkt[s[i]];\n  for (int i = 0, sum = 0; i != K; ++i)\
    \ sum += bkt[i], bkt_r[i] = sum, bkt_l[i] = sum - bkt[i];\n  std::vector<int>\
    \ s1(n1), SA1(n1);\n  std::fill_n(SA.begin(), n, -1);\n  std::copy_n(bkt_r.begin(),\
    \ K, bkt.begin());\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] =\
    \ p1[i];\n  induced_sort();\n  for (int i = 0, j = 0; i != n; ++i)\n    if (is_LMS_type(SA[i]))\
    \ SA1[j++] = SA[i];\n  int name = 0;\n  for (int i = 0, prev = -1; i != n1; ++i)\
    \ {\n    int pos = SA1[i];\n    for (int j = 0;; ++j)\n      if (prev == -1 ||\
    \ s[pos + j] != s[prev + j] || is_S_type(pos + j) != is_S_type(prev + j)) {\n\
    \        prev = pos, ++name;\n        break;\n      } else if (j != 0 && (is_LMS_type(pos\
    \ + j) || is_LMS_type(prev + j)))\n        break;\n    SA[pos] = name - 1;\n \
    \ }\n  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];\n  if (name != n1)\n \
    \   SA1 = SA_IS(s1, name);\n  else\n    for (int i = 0; i != n1; ++i) SA1[s1[i]]\
    \ = i;\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\n  std::fill_n(SA.begin(),\
    \ n, -1);\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];\n\
    \  induced_sort();\n#undef is_S_type\n#undef is_L_type\n#undef is_LMS_type\n#undef\
    \ induced_sort\n  return SA;\n}\n\n} // namespace internal\n\nstd::vector<int>\
    \ get_sa(const std::string &s) {\n  std::vector<int> s_cpy(s.size() + 1);\n  std::copy(s.begin(),\
    \ s.end(), s_cpy.begin());\n  s_cpy.back() = 0;\n  std::vector<int> SA(internal::SA_IS(s_cpy,\
    \ 128));\n  SA.erase(SA.begin());\n  return SA;\n}\n\n// reference: https://cp-algorithms.com/string/suffix-array.html\n\
    std::vector<int> get_height(const std::string &s, const std::vector<int> &SA)\
    \ {\n  int n = s.size();\n  std::vector<int> rk(n), height(n - 1, 0);\n  // height[i]\
    \ = s[SA[i]..n-1] \u4E0E s[SA[i+1]..n-1] \u7684\u6700\u957F\u516C\u5171\u524D\u7F00\
    \uFF08 longest common prefix \uFF09\n  // Kasai \u7684\u8BBA\u6587\u4E2D\u79F0\
    \u5176\u4E3A lcp \u6570\u7EC4\u6216 height \u6570\u7EC4\n  for (int i = 0; i !=\
    \ n; ++i) rk[SA[i]] = i;\n  for (int i = 0, h = 0; i != n; ++i) {\n    if (rk[i]\
    \ == n - 1) {\n      h = 0;\n      continue;\n    }\n    int j = SA[rk[i] + 1];\n\
    \    while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;\n    height[rk[i]]\
    \ = h;\n    if (h != 0) --h;\n  }\n  return height;\n}\n\n} // namespace lib\n\
    \n#endif"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_array_sais.hpp
  requiredBy: []
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - remote_test/yosupo/string/suffix_array.0.test.cpp
documentation_of: string/suffix_array_sais.hpp
layout: document
title: "\u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\u6392\u5E8F\uFF09"
---

## 后缀数组

使用 0-indexed ，有函数

- `get_sa(s)` 接收 `std::string` 类型，返回 `std::vector<int>` 类型。
- `get_height(s, SA)` 接收原字符串和后缀数组，返回 LCP （ longest common prefix ）数组， LCP 数组长度为后缀数组长度减少一，在下标 `i` 的位置存储了 `SA[i]` 和 `SA[i+1]` 的 LCP 长度。

