---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: string/suffix_array_sais.hpp
    title: "suffix array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\u6392\u5E8F\
      \uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    _deprecated_at_docs: docs/string/bwt.md
    document_title: "Burrows-Wheeler trasformation / Burrows-Wheeler \u53D8\u6362"
    links: []
  bundledCode: "#line 1 \"string/bwt.hpp\"\n\n\n\r\n/**\r\n * @brief Burrows-Wheeler\
    \ trasformation / Burrows-Wheeler \u53D8\u6362\r\n * @docs docs/string/bwt.md\r\
    \n */\r\n\r\n#include <algorithm>\r\n#include <cassert>\r\n#include <string>\r\
    \n#include <vector>\r\n\r\n#line 1 \"string/suffix_array_sais.hpp\"\n\n\n\r\n\
    /**\r\n * @brief suffix array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\
    \u6392\u5E8F\uFF09\r\n * @docs docs/string/suffix_array_sais.md\r\n */\r\n\r\n\
    #line 12 \"string/suffix_array_sais.hpp\"\n\r\nnamespace lib::internal {\r\n\r\
    \n/**\r\n * @brief \u8BF1\u5BFC\u6392\u5E8F\r\n * @ref Ge Nong, Sen Zhang and\
    \ Wai Hong Chan.\r\n *      Linear Suffix Array Construction by Almost Pure Induced-Sorting.\r\
    \n *\r\n * @param s \u5B57\u7B26\u4E32\u6570\u7EC4\uFF0C\u5FC5\u987B\u4FDD\u8BC1\
    \u672B\u5C3E\u4E3A 0 \u4E14 0 \u662F\u6574\u4E2A\u5B57\u7B26\u4E32\u6570\u7EC4\
    \u4E2D\u53EA\u51FA\u73B0\u5728\u672B\u5C3E\u7684\u6700\u5C0F\u5B57\u7B26\uFF01\
    \r\n * @param K \u5B57\u7B26\u4E32\u6570\u7EC4\u7684\u503C\u57DF\uFF0C\u7531 [0,\
    \ K)\r\n * @return std::vector<int>\r\n */\r\nstd::vector<int> SA_IS(const std::vector<int>\
    \ &s, int K) {\r\n  const int n = s.size();\r\n  std::vector<bool> t(n);\r\n \
    \ std::vector<int> bkt(K, 0), bkt_l(K), bkt_r(K), SA(n), p1;\r\n#define IS_S_TYPE(x)\
    \ (t[x])\r\n#define IS_L_TYPE(x) (!t[x])\r\n#define IS_LMS_TYPE(x) (IS_S_TYPE(x)\
    \ && x != 0 && IS_L_TYPE(x - 1))\r\n  t.back() = true;\r\n  for (int i = n - 2;\
    \ i >= 0; --i) {\r\n    t[i] = (s[i] < s[i + 1] || (IS_S_TYPE(i + 1) && s[i] ==\
    \ s[i + 1]));\r\n    if (IS_LMS_TYPE(i + 1)) p1.push_back(i + 1);\r\n  }\r\n \
    \ std::reverse(p1.begin(), p1.end());\r\n  const int n1 = p1.size();\r\n  for\
    \ (int i = 0; i != n; ++i) ++bkt[s[i]];\r\n  for (int i = 0, sum = 0; i != K;\
    \ ++i) sum += bkt[i], bkt_r[i] = sum, bkt_l[i] = sum - bkt[i];\r\n  std::vector<int>\
    \ s1(n1), SA1(n1);\r\n  std::fill_n(SA.begin(), n, -1);\r\n  std::copy_n(bkt_r.begin(),\
    \ K, bkt.begin());\r\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]]\
    \ = p1[i];\r\n  std::copy_n(bkt_l.begin(), K, bkt.begin());\r\n  for (int i =\
    \ 0, j; i != n; ++i)\r\n    if ((j = SA[i] - 1) >= 0 && IS_L_TYPE(j)) SA[bkt[s[j]]++]\
    \ = j;\r\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\r\n  for (int i = n -\
    \ 1, j; i >= 0; --i)\r\n    if ((j = SA[i] - 1) >= 0 && IS_S_TYPE(j)) SA[--bkt[s[j]]]\
    \ = j;\r\n  for (int i = 0, j = 0; i != n; ++i)\r\n    if (IS_LMS_TYPE(SA[i]))\
    \ SA1[j++] = SA[i];\r\n  int name = 0;\r\n  for (int i = 0, prev = -1; i != n1;\
    \ ++i) {\r\n    int pos = SA1[i];\r\n    for (int j = 0;; ++j)\r\n      if (prev\
    \ == -1 || s[pos + j] != s[prev + j] || IS_S_TYPE(pos + j) != IS_S_TYPE(prev +\
    \ j)) {\r\n        prev = pos, ++name;\r\n        break;\r\n      } else if (j\
    \ != 0 && (IS_LMS_TYPE(pos + j) || IS_LMS_TYPE(prev + j)))\r\n        break;\r\
    \n    SA[pos] = name - 1;\r\n  }\r\n  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];\r\
    \n  if (name != n1) {\r\n    SA1 = SA_IS(s1, name);\r\n  } else {\r\n    for (int\
    \ i = 0; i != n1; ++i) SA1[s1[i]] = i;\r\n  }\r\n  std::copy_n(bkt_r.begin(),\
    \ K, bkt.begin());\r\n  std::fill_n(SA.begin(), n, -1);\r\n  for (int i = n1 -\
    \ 1; i >= 0; --i) SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];\r\n  for (int i = 0,\
    \ j; i != n; ++i)\r\n    if ((j = SA[i] - 1) >= 0 && IS_L_TYPE(j)) SA[bkt_l[s[j]]++]\
    \ = j;\r\n  for (int i = n - 1, j; i >= 0; --i)\r\n    if ((j = SA[i] - 1) >=\
    \ 0 && IS_S_TYPE(j)) SA[--bkt_r[s[j]]] = j;\r\n#undef IS_S_TYPE\r\n#undef IS_L_TYPE\r\
    \n#undef IS_LMS_TYPE\r\n  return SA;\r\n}\r\n\r\n} // namespace lib::internal\r\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u83B7\u53D6\u540E\u7F00\u6570\u7EC4\
    \uFF08 0-indexed \uFF09\r\n * @param s \u5B57\u7B26\u4E32\uFF0C\u4E00\u822C\u4E3A\
    \ string \u6216 std::vector<int>\r\n * @return std::vector<int> \u540E\u7F00\u6570\
    \u7EC4\r\n */\r\ntemplate <typename Container>\r\nstd::vector<int> get_sa(const\
    \ Container &s) {\r\n  std::vector<int> s_cpy(s.size() + 1);\r\n  std::copy(s.begin(),\
    \ s.end(), s_cpy.begin());\r\n  s_cpy.back() = 0;\r\n  std::vector<int> SA(internal::SA_IS(s_cpy,\
    \ *std::max_element(s.begin(), s.end()) + 1));\r\n  SA.erase(SA.begin());\r\n\
    \  return SA;\r\n}\r\n\r\n/**\r\n * @brief \u83B7\u53D6\u540E\u7F00\u6570\u7EC4\
    \uFF08 0-indexed \uFF09\u7684\u7279\u5316\r\n * @note \u5BB9\u5668\u4E3A std::string\
    \ \u65F6\u7279\u5316\uFF01\r\n * @param s \u5B57\u7B26\u4E32\r\n * @return std::vector<int>\r\
    \n */\r\ntemplate <>\r\nstd::vector<int> get_sa<std::string>(const std::string\
    \ &s) {\r\n  std::vector<int> s_cpy(s.size() + 1);\r\n  std::copy(s.begin(), s.end(),\
    \ s_cpy.begin());\r\n  s_cpy.back() = 0;\r\n  std::vector<int> SA(internal::SA_IS(s_cpy,\
    \ 128));\r\n  SA.erase(SA.begin());\r\n  return SA;\r\n}\r\n\r\n/**\r\n * @brief\
    \ \u83B7\u53D6 LCP \u6570\u7EC4\r\n * @see https://cp-algorithms.com/string/suffix-array.html\r\
    \n * @param s \u5B57\u7B26\u4E32\r\n * @param SA \u8BA1\u7B97\u5B8C\u6BD5\u7684\
    \ s \u7684\u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\r\n * @return std::vector<int>\
    \ LCP \u6570\u7EC4\r\n */\r\ntemplate <typename Container>\r\nstd::vector<int>\
    \ get_lcp(const Container &s, const std::vector<int> &SA) {\r\n  int n = s.size();\r\
    \n  std::vector<int> rk(n), height(n - 1, 0);\r\n  // height[i] = s[SA[i]..n-1]\
    \ \u4E0E s[SA[i+1]..n-1] \u7684\u6700\u957F\u516C\u5171\u524D\u7F00\uFF08 longest\
    \ common prefix \uFF09\r\n  // Kasai \u7684\u8BBA\u6587\u4E2D\u79F0\u5176\u4E3A\
    \ lcp \u6570\u7EC4\u6216 height \u6570\u7EC4\r\n  for (int i = 0; i != n; ++i)\
    \ rk[SA[i]] = i;\r\n  for (int i = 0, h = 0; i != n; ++i) {\r\n    if (rk[i] ==\
    \ n - 1) {\r\n      h = 0;\r\n      continue;\r\n    }\r\n    int j = SA[rk[i]\
    \ + 1];\r\n    while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;\r\n\
    \    height[rk[i]] = h;\r\n    if (h != 0) --h;\r\n  }\r\n  return height;\r\n\
    }\r\n\r\n} // namespace lib\r\n\r\n\n#line 15 \"string/bwt.hpp\"\n\r\nnamespace\
    \ lib {\r\n\r\n/**\r\n * @brief \u83B7\u53D6 BWT \u6570\u7EC4\uFF08\u5B57\u7B26\
    \u4E32\uFF09\r\n * @param v \u5B57\u7B26\u4E32\u6570\u7EC4\uFF0C\u5FC5\u987B\u4FDD\
    \u8BC1 0 \u662F\u672A\u51FA\u73B0\u7684\u6700\u5C0F\u503C\r\n * @param SA v \u7684\
    \u540E\u7F00\u6570\u7EC4\r\n */\r\ntemplate <typename Container>\r\nContainer\
    \ bwt(const Container &v, const std::vector<int> &SA) {\r\n  int n = v.size();\r\
    \n  Container res;\r\n  res.resize(n + 1);\r\n  for (int i = 0; i < n; ++i) res[i\
    \ + 1] = SA[i] != 0 ? v[SA[i] - 1] : 0;\r\n  res[0] = v.back();\r\n  return res;\r\
    \n}\r\n\r\n/**\r\n * @brief \u83B7\u53D6 BWT \u6570\u7EC4\uFF08\u5B57\u7B26\u4E32\
    \uFF09\r\n * @param v \u5B57\u7B26\u4E32\u6570\u7EC4\uFF0C\u5FC5\u987B\u4FDD\u8BC1\
    \ 0 \u662F\u672A\u51FA\u73B0\u7684\u6700\u5C0F\u503C\r\n */\r\ntemplate <typename\
    \ Container>\r\nContainer bwt(const Container &v) {\r\n  return bwt(v, get_sa(v));\r\
    \n}\r\n\r\n/**\r\n * @brief \u4ECE BWT \u6570\u7EC4\u8BA1\u7B97\u539F\u6570\u7EC4\
    \uFF08\u5B57\u7B26\u4E32\uFF09\r\n * @ref M. Burrows and D. J. Wheeler. A block-sorting\
    \ lossless data compression algorithm.\r\n *      Technical Report 124, Digital\
    \ Equipment Corporation, Palo Alto, California, 1994.\r\n * @param v BWT \u6570\
    \u7EC4\uFF0C\u5176\u4E2D\u5FC5\u6709\u4E00\u4E2A 0\r\n */\r\ntemplate <typename\
    \ Container>\r\nContainer ibwt(const Container &v) {\r\n  int n = v.size();\r\n\
    \  int K = *std::max_element(v.begin(), v.end()) + 1;\r\n  Container res;\r\n\
    \  res.resize(n); // \u4E3A\u4E86 std::string \u7279\u6B8A\u5904\u7406\r\n  //\
    \ C[i] \u4E3A\u5B57\u7B26 i \u51FA\u73B0\u7684\u6B21\u6570\uFF0C P[i] \u4E3A v[i]\
    \ \u5728\u524D\u7F00\u4E2D\u51FA\u73B0\u7684\u6B21\u6570\uFF08\u4E0D\u5305\u542B\
    \uFF09\r\n  std::vector<int> C(K, 0), P(n, 0);\r\n  int I = -1; // \u8BB0\u5F55\
    \u7EC8\u6B62\u7B26\u53F7\u4F4D\u7F6E\r\n  for (int i = 0; i < n; ++i) {\r\n  \
    \  P[i] = C[v[i]]++;\r\n    if (v[i] == 0) I = i;\r\n  }\r\n  assert(I != -1);\r\
    \n  for (int i = 0, sum = 0; i < K; ++i) sum += C[i], C[i] = sum - C[i];\r\n \
    \ for (int i = I, j = n - 1; j >= 0; --j) res[j] = v[i], i = P[i] + C[v[i]];\r\
    \n  res.pop_back();\r\n  return res;\r\n}\r\n\r\n/**\r\n * @brief \u4ECE BWT \u6570\
    \u7EC4\u8BA1\u7B97\u539F\u6570\u7EC4\uFF08\u5B57\u7B26\u4E32\uFF09\u7684\u7279\
    \u5316\r\n */\r\ntemplate <>\r\nstd::string ibwt<std::string>(const std::string\
    \ &v) {\r\n  int n = v.size();\r\n  std::string res;\r\n  res.resize(n);\r\n \
    \ // C[i] \u4E3A\u5B57\u7B26 i \u51FA\u73B0\u7684\u6B21\u6570\uFF0C P[i] \u4E3A\
    \ v[i] \u5728\u524D\u7F00\u4E2D\u51FA\u73B0\u7684\u6B21\u6570\uFF08\u4E0D\u5305\
    \u542B\uFF09\r\n  std::vector<int> C(128, 0), P(n, 0);\r\n  int I = -1; // \u8BB0\
    \u5F55\u7EC8\u6B62\u7B26\u53F7\u4F4D\u7F6E\r\n  for (int i = 0; i < n; ++i) {\r\
    \n    P[i] = C[v[i]]++;\r\n    if (v[i] == 0) I = i;\r\n  }\r\n  assert(I != -1);\r\
    \n  for (int i = 0, sum = 0; i < 128; ++i) sum += C[i], C[i] = sum - C[i];\r\n\
    \  for (int i = I, j = n - 1; j >= 0; --j) res[j] = v[i], i = P[i] + C[v[i]];\r\
    \n  res.pop_back();\r\n  return res;\r\n}\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef BURROWS_WHEELER_TRANSFORMATION_HEADER_HPP\r\n#define BURROWS_WHEELER_TRANSFORMATION_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief Burrows-Wheeler trasformation / Burrows-Wheeler \u53D8\u6362\
    \r\n * @docs docs/string/bwt.md\r\n */\r\n\r\n#include <algorithm>\r\n#include\
    \ <cassert>\r\n#include <string>\r\n#include <vector>\r\n\r\n#include \"suffix_array_sais.hpp\"\
    \r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u83B7\u53D6 BWT \u6570\u7EC4\uFF08\
    \u5B57\u7B26\u4E32\uFF09\r\n * @param v \u5B57\u7B26\u4E32\u6570\u7EC4\uFF0C\u5FC5\
    \u987B\u4FDD\u8BC1 0 \u662F\u672A\u51FA\u73B0\u7684\u6700\u5C0F\u503C\r\n * @param\
    \ SA v \u7684\u540E\u7F00\u6570\u7EC4\r\n */\r\ntemplate <typename Container>\r\
    \nContainer bwt(const Container &v, const std::vector<int> &SA) {\r\n  int n =\
    \ v.size();\r\n  Container res;\r\n  res.resize(n + 1);\r\n  for (int i = 0; i\
    \ < n; ++i) res[i + 1] = SA[i] != 0 ? v[SA[i] - 1] : 0;\r\n  res[0] = v.back();\r\
    \n  return res;\r\n}\r\n\r\n/**\r\n * @brief \u83B7\u53D6 BWT \u6570\u7EC4\uFF08\
    \u5B57\u7B26\u4E32\uFF09\r\n * @param v \u5B57\u7B26\u4E32\u6570\u7EC4\uFF0C\u5FC5\
    \u987B\u4FDD\u8BC1 0 \u662F\u672A\u51FA\u73B0\u7684\u6700\u5C0F\u503C\r\n */\r\
    \ntemplate <typename Container>\r\nContainer bwt(const Container &v) {\r\n  return\
    \ bwt(v, get_sa(v));\r\n}\r\n\r\n/**\r\n * @brief \u4ECE BWT \u6570\u7EC4\u8BA1\
    \u7B97\u539F\u6570\u7EC4\uFF08\u5B57\u7B26\u4E32\uFF09\r\n * @ref M. Burrows and\
    \ D. J. Wheeler. A block-sorting lossless data compression algorithm.\r\n *  \
    \    Technical Report 124, Digital Equipment Corporation, Palo Alto, California,\
    \ 1994.\r\n * @param v BWT \u6570\u7EC4\uFF0C\u5176\u4E2D\u5FC5\u6709\u4E00\u4E2A\
    \ 0\r\n */\r\ntemplate <typename Container>\r\nContainer ibwt(const Container\
    \ &v) {\r\n  int n = v.size();\r\n  int K = *std::max_element(v.begin(), v.end())\
    \ + 1;\r\n  Container res;\r\n  res.resize(n); // \u4E3A\u4E86 std::string \u7279\
    \u6B8A\u5904\u7406\r\n  // C[i] \u4E3A\u5B57\u7B26 i \u51FA\u73B0\u7684\u6B21\u6570\
    \uFF0C P[i] \u4E3A v[i] \u5728\u524D\u7F00\u4E2D\u51FA\u73B0\u7684\u6B21\u6570\
    \uFF08\u4E0D\u5305\u542B\uFF09\r\n  std::vector<int> C(K, 0), P(n, 0);\r\n  int\
    \ I = -1; // \u8BB0\u5F55\u7EC8\u6B62\u7B26\u53F7\u4F4D\u7F6E\r\n  for (int i\
    \ = 0; i < n; ++i) {\r\n    P[i] = C[v[i]]++;\r\n    if (v[i] == 0) I = i;\r\n\
    \  }\r\n  assert(I != -1);\r\n  for (int i = 0, sum = 0; i < K; ++i) sum += C[i],\
    \ C[i] = sum - C[i];\r\n  for (int i = I, j = n - 1; j >= 0; --j) res[j] = v[i],\
    \ i = P[i] + C[v[i]];\r\n  res.pop_back();\r\n  return res;\r\n}\r\n\r\n/**\r\n\
    \ * @brief \u4ECE BWT \u6570\u7EC4\u8BA1\u7B97\u539F\u6570\u7EC4\uFF08\u5B57\u7B26\
    \u4E32\uFF09\u7684\u7279\u5316\r\n */\r\ntemplate <>\r\nstd::string ibwt<std::string>(const\
    \ std::string &v) {\r\n  int n = v.size();\r\n  std::string res;\r\n  res.resize(n);\r\
    \n  // C[i] \u4E3A\u5B57\u7B26 i \u51FA\u73B0\u7684\u6B21\u6570\uFF0C P[i] \u4E3A\
    \ v[i] \u5728\u524D\u7F00\u4E2D\u51FA\u73B0\u7684\u6B21\u6570\uFF08\u4E0D\u5305\
    \u542B\uFF09\r\n  std::vector<int> C(128, 0), P(n, 0);\r\n  int I = -1; // \u8BB0\
    \u5F55\u7EC8\u6B62\u7B26\u53F7\u4F4D\u7F6E\r\n  for (int i = 0; i < n; ++i) {\r\
    \n    P[i] = C[v[i]]++;\r\n    if (v[i] == 0) I = i;\r\n  }\r\n  assert(I != -1);\r\
    \n  for (int i = 0, sum = 0; i < 128; ++i) sum += C[i], C[i] = sum - C[i];\r\n\
    \  for (int i = I, j = n - 1; j >= 0; --j) res[j] = v[i], i = P[i] + C[v[i]];\r\
    \n  res.pop_back();\r\n  return res;\r\n}\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn:
  - string/suffix_array_sais.hpp
  isVerificationFile: false
  path: string/bwt.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/bwt.hpp
layout: document
redirect_from:
- /library/string/bwt.hpp
- /library/string/bwt.hpp.html
title: "Burrows-Wheeler trasformation / Burrows-Wheeler \u53D8\u6362"
---
## Burrows-Wheeler 变换

对于字符串 $s=\texttt{banana0}$ 定义其后缀数组 SA 为

$$
\operatorname{SA}(s)=(6,5,3,1,0,4,2)
$$

也就是

$$
\texttt{0}\\
\texttt{a0}\\
\texttt{ana0}\\
\texttt{anana0}\\
\texttt{banana0}\\
\texttt{na0}\\
\texttt{nana0}\\
$$

而 BWT 则是对循环串进行排序，有

$$
\texttt{0banana}\\
\texttt{a0banan}\\
\texttt{ana0ban}\\
\texttt{anana0b}\\
\texttt{banana0}\\
\texttt{na0bana}\\
\texttt{nana0ba}\\
$$

我们取其末尾的字符为 $\operatorname{BWT}(s)=\texttt{annb0aa}$ 。

注意这里需要这个末尾的字符 $\texttt{0}$ 作为“哨兵”表示文本串的结尾，其必须在文本串中没有出现过且为字典序最小的字符，如此一来我们可以通过后缀数组来进行构建，有

$$
\operatorname{BWT} _ i(s)=
\begin{cases}
s _ {\operatorname{SA}_i(s)-1}&\text{if }\operatorname{SA}_i(s)\gt 0\\
\texttt{0}&\text{otherwise}
\end{cases}
$$

不难发现这是正确的。如果没有“哨兵”字符，我们需要将串拷贝一份拼接在后面再求其后缀数组，例如 [P4051 [JSOI2007]字符加密](https://www.luogu.com.cn/problem/P4051) 如果我们使用倍增法求 SA ，不难在过程中改为其循环串的 SA 。但这也不符合 BWT 的定义了。

BWT 在计算过程中没有丢失信息，这也意味着 BWT 是可逆的。

## Last-First 映射

我们还是注意该串

$$
\texttt{\textcolor{red}{0}banan\textcolor{red}{a}}\\
\texttt{\textcolor{red}{a}0bana\textcolor{red}{n}}\\
\texttt{\textcolor{red}{a}na0ba\textcolor{red}{n}}\\
\texttt{\textcolor{red}{a}nana0\textcolor{red}{b}}\\
\texttt{\textcolor{red}{b}anana\textcolor{red}{0}}\\
\texttt{\textcolor{red}{n}a0ban\textcolor{red}{a}}\\
\texttt{\textcolor{red}{n}ana0b\textcolor{red}{a}}\\
$$

我们注意 First 即第一列是其 SA 中按照排名的后缀的首个字符且 Last 即 BWT 中的第 $i$ 个 $\texttt{a}$ 也对应 SA 中的第 $i$ 个 $\texttt{a}$ ，以此类推。

## FM-index

TODO

## 参考文献

- M. Burrows and D. J. Wheeler. [A block-sorting lossless data compression algorithm](https://www.cl.cam.ac.uk/teaching/2003/DSAlgs/SRC-124.pdf). Technical Report 124, Digital Equipment Corporation, Palo Alto, California, 1994.