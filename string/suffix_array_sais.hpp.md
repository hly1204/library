---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: string/bwt.hpp
    title: "Burrows-Wheeler trasformation / Burrows-Wheeler \u53D8\u6362"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/string/suffix_array.0.test.cpp
    title: remote_test/yosupo/string/suffix_array.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/string/suffix_array_sais.md
    document_title: "suffix array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\
      \u6392\u5E8F\uFF09"
    links:
    - https://cp-algorithms.com/string/suffix-array.html
  bundledCode: "#line 1 \"string/suffix_array_sais.hpp\"\n\n\n\n/**\n * @brief suffix\
    \ array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\u6392\u5E8F\uFF09\n\
    \ * @docs docs/string/suffix_array_sais.md\n */\n\n#include <algorithm>\n#include\
    \ <string>\n#include <vector>\n\nnamespace lib {\n\nnamespace internal {\n\n/**\n\
    \ * @brief \u8BF1\u5BFC\u6392\u5E8F\n * @ref Ge Nong, Sen Zhang and Wai Hong Chan.\n\
    \ *      Linear Suffix Array Construction by Almost Pure Induced-Sorting.\n *\n\
    \ * @param s \u5B57\u7B26\u4E32\u6570\u7EC4\uFF0C\u5FC5\u987B\u4FDD\u8BC1\u672B\
    \u5C3E\u4E3A 0 \u4E14 0 \u662F\u6574\u4E2A\u5B57\u7B26\u4E32\u6570\u7EC4\u4E2D\
    \u53EA\u51FA\u73B0\u5728\u672B\u5C3E\u7684\u6700\u5C0F\u5B57\u7B26\uFF01\n * @param\
    \ K \u5B57\u7B26\u4E32\u6570\u7EC4\u7684\u503C\u57DF\uFF0C\u7531 [0, K)\n * @return\
    \ std::vector<int>\n */\nstd::vector<int> SA_IS(const std::vector<int> &s, int\
    \ K) {\n  const int n = s.size();\n  std::vector<bool> t(n);\n  std::vector<int>\
    \ bkt(K, 0), bkt_l(K), bkt_r(K), SA(n), p1;\n#define IS_S_TYPE(x) (t[x])\n#define\
    \ IS_L_TYPE(x) (!t[x])\n#define IS_LMS_TYPE(x) (IS_S_TYPE(x) && x != 0 && IS_L_TYPE(x\
    \ - 1))\n  t.back() = true;\n  for (int i = n - 2; i >= 0; --i) {\n    t[i] =\
    \ (s[i] < s[i + 1] || (IS_S_TYPE(i + 1) && s[i] == s[i + 1]));\n    if (IS_LMS_TYPE(i\
    \ + 1)) p1.push_back(i + 1);\n  }\n  std::reverse(p1.begin(), p1.end());\n  const\
    \ int n1 = p1.size();\n  for (int i = 0; i != n; ++i) ++bkt[s[i]];\n  for (int\
    \ i = 0, sum = 0; i != K; ++i) sum += bkt[i], bkt_r[i] = sum, bkt_l[i] = sum -\
    \ bkt[i];\n  std::vector<int> s1(n1), SA1(n1);\n  std::fill_n(SA.begin(), n, -1);\n\
    \  std::copy_n(bkt_r.begin(), K, bkt.begin());\n  for (int i = n1 - 1; i >= 0;\
    \ --i) SA[--bkt[s[p1[i]]]] = p1[i];\n  std::copy_n(bkt_l.begin(), K, bkt.begin());\n\
    \  for (int i = 0, j; i != n; ++i)\n    if ((j = SA[i] - 1) >= 0 && IS_L_TYPE(j))\
    \ SA[bkt[s[j]]++] = j;\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\n  for (int\
    \ i = n - 1, j; i >= 0; --i)\n    if ((j = SA[i] - 1) >= 0 && IS_S_TYPE(j)) SA[--bkt[s[j]]]\
    \ = j;\n  for (int i = 0, j = 0; i != n; ++i)\n    if (IS_LMS_TYPE(SA[i])) SA1[j++]\
    \ = SA[i];\n  int name = 0;\n  for (int i = 0, prev = -1; i != n1; ++i) {\n  \
    \  int pos = SA1[i];\n    for (int j = 0;; ++j)\n      if (prev == -1 || s[pos\
    \ + j] != s[prev + j] || IS_S_TYPE(pos + j) != IS_S_TYPE(prev + j)) {\n      \
    \  prev = pos, ++name;\n        break;\n      } else if (j != 0 && (IS_LMS_TYPE(pos\
    \ + j) || IS_LMS_TYPE(prev + j)))\n        break;\n    SA[pos] = name - 1;\n \
    \ }\n  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];\n  if (name != n1) {\n\
    \    SA1 = SA_IS(s1, name);\n  } else {\n    for (int i = 0; i != n1; ++i) SA1[s1[i]]\
    \ = i;\n  }\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\n  std::fill_n(SA.begin(),\
    \ n, -1);\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];\n\
    \  for (int i = 0, j; i != n; ++i)\n    if ((j = SA[i] - 1) >= 0 && IS_L_TYPE(j))\
    \ SA[bkt_l[s[j]]++] = j;\n  for (int i = n - 1, j; i >= 0; --i)\n    if ((j =\
    \ SA[i] - 1) >= 0 && IS_S_TYPE(j)) SA[--bkt_r[s[j]]] = j;\n#undef IS_S_TYPE\n\
    #undef IS_L_TYPE\n#undef IS_LMS_TYPE\n  return SA;\n}\n\n} // namespace internal\n\
    \n/**\n * @brief \u83B7\u53D6\u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\n\
    \ * @param s \u5B57\u7B26\u4E32\uFF0C\u4E00\u822C\u4E3A string \u6216 std::vector<int>\n\
    \ * @return std::vector<int> \u540E\u7F00\u6570\u7EC4\n */\ntemplate <typename\
    \ Container> std::vector<int> get_sa(const Container &s) {\n  std::vector<int>\
    \ s_cpy(s.size() + 1);\n  std::copy(s.begin(), s.end(), s_cpy.begin());\n  s_cpy.back()\
    \ = 0;\n  std::vector<int> SA(internal::SA_IS(s_cpy, *std::max_element(s.begin(),\
    \ s.end()) + 1));\n  SA.erase(SA.begin());\n  return SA;\n}\n\n/**\n * @brief\
    \ \u83B7\u53D6\u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\u7684\u7279\u5316\
    \n * @note \u5BB9\u5668\u4E3A std::string \u65F6\u7279\u5316\uFF01\n * @param\
    \ s \u5B57\u7B26\u4E32\n * @return std::vector<int>\n */\ntemplate <> std::vector<int>\
    \ get_sa<std::string>(const std::string &s) {\n  std::vector<int> s_cpy(s.size()\
    \ + 1);\n  std::copy(s.begin(), s.end(), s_cpy.begin());\n  s_cpy.back() = 0;\n\
    \  std::vector<int> SA(internal::SA_IS(s_cpy, 128));\n  SA.erase(SA.begin());\n\
    \  return SA;\n}\n\n/**\n * @brief \u83B7\u53D6 LCP \u6570\u7EC4\n * @see https://cp-algorithms.com/string/suffix-array.html\n\
    \ * @param s \u5B57\u7B26\u4E32\n * @param SA \u8BA1\u7B97\u5B8C\u6BD5\u7684 s\
    \ \u7684\u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\n * @return std::vector<int>\
    \ LCP \u6570\u7EC4\n */\ntemplate <typename Container>\nstd::vector<int> get_lcp(const\
    \ Container &s, const std::vector<int> &SA) {\n  int n = s.size();\n  std::vector<int>\
    \ rk(n), height(n - 1, 0);\n  // height[i] = s[SA[i]..n-1] \u4E0E s[SA[i+1]..n-1]\
    \ \u7684\u6700\u957F\u516C\u5171\u524D\u7F00\uFF08 longest common prefix \uFF09\
    \n  // Kasai \u7684\u8BBA\u6587\u4E2D\u79F0\u5176\u4E3A lcp \u6570\u7EC4\u6216\
    \ height \u6570\u7EC4\n  for (int i = 0; i != n; ++i) rk[SA[i]] = i;\n  for (int\
    \ i = 0, h = 0; i != n; ++i) {\n    if (rk[i] == n - 1) {\n      h = 0;\n    \
    \  continue;\n    }\n    int j = SA[rk[i] + 1];\n    while (i + h < n && j + h\
    \ < n && s[i + h] == s[j + h]) ++h;\n    height[rk[i]] = h;\n    if (h != 0) --h;\n\
    \  }\n  return height;\n}\n\n} // namespace lib\n\n\n"
  code: "#ifndef SUFFIX_ARRAY_SAIS_HEADER_HPP\n#define SUFFIX_ARRAY_SAIS_HEADER_HPP\n\
    \n/**\n * @brief suffix array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\
    \u6392\u5E8F\uFF09\n * @docs docs/string/suffix_array_sais.md\n */\n\n#include\
    \ <algorithm>\n#include <string>\n#include <vector>\n\nnamespace lib {\n\nnamespace\
    \ internal {\n\n/**\n * @brief \u8BF1\u5BFC\u6392\u5E8F\n * @ref Ge Nong, Sen\
    \ Zhang and Wai Hong Chan.\n *      Linear Suffix Array Construction by Almost\
    \ Pure Induced-Sorting.\n *\n * @param s \u5B57\u7B26\u4E32\u6570\u7EC4\uFF0C\u5FC5\
    \u987B\u4FDD\u8BC1\u672B\u5C3E\u4E3A 0 \u4E14 0 \u662F\u6574\u4E2A\u5B57\u7B26\
    \u4E32\u6570\u7EC4\u4E2D\u53EA\u51FA\u73B0\u5728\u672B\u5C3E\u7684\u6700\u5C0F\
    \u5B57\u7B26\uFF01\n * @param K \u5B57\u7B26\u4E32\u6570\u7EC4\u7684\u503C\u57DF\
    \uFF0C\u7531 [0, K)\n * @return std::vector<int>\n */\nstd::vector<int> SA_IS(const\
    \ std::vector<int> &s, int K) {\n  const int n = s.size();\n  std::vector<bool>\
    \ t(n);\n  std::vector<int> bkt(K, 0), bkt_l(K), bkt_r(K), SA(n), p1;\n#define\
    \ IS_S_TYPE(x) (t[x])\n#define IS_L_TYPE(x) (!t[x])\n#define IS_LMS_TYPE(x) (IS_S_TYPE(x)\
    \ && x != 0 && IS_L_TYPE(x - 1))\n  t.back() = true;\n  for (int i = n - 2; i\
    \ >= 0; --i) {\n    t[i] = (s[i] < s[i + 1] || (IS_S_TYPE(i + 1) && s[i] == s[i\
    \ + 1]));\n    if (IS_LMS_TYPE(i + 1)) p1.push_back(i + 1);\n  }\n  std::reverse(p1.begin(),\
    \ p1.end());\n  const int n1 = p1.size();\n  for (int i = 0; i != n; ++i) ++bkt[s[i]];\n\
    \  for (int i = 0, sum = 0; i != K; ++i) sum += bkt[i], bkt_r[i] = sum, bkt_l[i]\
    \ = sum - bkt[i];\n  std::vector<int> s1(n1), SA1(n1);\n  std::fill_n(SA.begin(),\
    \ n, -1);\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\n  for (int i = n1 -\
    \ 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] = p1[i];\n  std::copy_n(bkt_l.begin(), K,\
    \ bkt.begin());\n  for (int i = 0, j; i != n; ++i)\n    if ((j = SA[i] - 1) >=\
    \ 0 && IS_L_TYPE(j)) SA[bkt[s[j]]++] = j;\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\n\
    \  for (int i = n - 1, j; i >= 0; --i)\n    if ((j = SA[i] - 1) >= 0 && IS_S_TYPE(j))\
    \ SA[--bkt[s[j]]] = j;\n  for (int i = 0, j = 0; i != n; ++i)\n    if (IS_LMS_TYPE(SA[i]))\
    \ SA1[j++] = SA[i];\n  int name = 0;\n  for (int i = 0, prev = -1; i != n1; ++i)\
    \ {\n    int pos = SA1[i];\n    for (int j = 0;; ++j)\n      if (prev == -1 ||\
    \ s[pos + j] != s[prev + j] || IS_S_TYPE(pos + j) != IS_S_TYPE(prev + j)) {\n\
    \        prev = pos, ++name;\n        break;\n      } else if (j != 0 && (IS_LMS_TYPE(pos\
    \ + j) || IS_LMS_TYPE(prev + j)))\n        break;\n    SA[pos] = name - 1;\n \
    \ }\n  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];\n  if (name != n1) {\n\
    \    SA1 = SA_IS(s1, name);\n  } else {\n    for (int i = 0; i != n1; ++i) SA1[s1[i]]\
    \ = i;\n  }\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\n  std::fill_n(SA.begin(),\
    \ n, -1);\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];\n\
    \  for (int i = 0, j; i != n; ++i)\n    if ((j = SA[i] - 1) >= 0 && IS_L_TYPE(j))\
    \ SA[bkt_l[s[j]]++] = j;\n  for (int i = n - 1, j; i >= 0; --i)\n    if ((j =\
    \ SA[i] - 1) >= 0 && IS_S_TYPE(j)) SA[--bkt_r[s[j]]] = j;\n#undef IS_S_TYPE\n\
    #undef IS_L_TYPE\n#undef IS_LMS_TYPE\n  return SA;\n}\n\n} // namespace internal\n\
    \n/**\n * @brief \u83B7\u53D6\u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\n\
    \ * @param s \u5B57\u7B26\u4E32\uFF0C\u4E00\u822C\u4E3A string \u6216 std::vector<int>\n\
    \ * @return std::vector<int> \u540E\u7F00\u6570\u7EC4\n */\ntemplate <typename\
    \ Container> std::vector<int> get_sa(const Container &s) {\n  std::vector<int>\
    \ s_cpy(s.size() + 1);\n  std::copy(s.begin(), s.end(), s_cpy.begin());\n  s_cpy.back()\
    \ = 0;\n  std::vector<int> SA(internal::SA_IS(s_cpy, *std::max_element(s.begin(),\
    \ s.end()) + 1));\n  SA.erase(SA.begin());\n  return SA;\n}\n\n/**\n * @brief\
    \ \u83B7\u53D6\u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\u7684\u7279\u5316\
    \n * @note \u5BB9\u5668\u4E3A std::string \u65F6\u7279\u5316\uFF01\n * @param\
    \ s \u5B57\u7B26\u4E32\n * @return std::vector<int>\n */\ntemplate <> std::vector<int>\
    \ get_sa<std::string>(const std::string &s) {\n  std::vector<int> s_cpy(s.size()\
    \ + 1);\n  std::copy(s.begin(), s.end(), s_cpy.begin());\n  s_cpy.back() = 0;\n\
    \  std::vector<int> SA(internal::SA_IS(s_cpy, 128));\n  SA.erase(SA.begin());\n\
    \  return SA;\n}\n\n/**\n * @brief \u83B7\u53D6 LCP \u6570\u7EC4\n * @see https://cp-algorithms.com/string/suffix-array.html\n\
    \ * @param s \u5B57\u7B26\u4E32\n * @param SA \u8BA1\u7B97\u5B8C\u6BD5\u7684 s\
    \ \u7684\u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\n * @return std::vector<int>\
    \ LCP \u6570\u7EC4\n */\ntemplate <typename Container>\nstd::vector<int> get_lcp(const\
    \ Container &s, const std::vector<int> &SA) {\n  int n = s.size();\n  std::vector<int>\
    \ rk(n), height(n - 1, 0);\n  // height[i] = s[SA[i]..n-1] \u4E0E s[SA[i+1]..n-1]\
    \ \u7684\u6700\u957F\u516C\u5171\u524D\u7F00\uFF08 longest common prefix \uFF09\
    \n  // Kasai \u7684\u8BBA\u6587\u4E2D\u79F0\u5176\u4E3A lcp \u6570\u7EC4\u6216\
    \ height \u6570\u7EC4\n  for (int i = 0; i != n; ++i) rk[SA[i]] = i;\n  for (int\
    \ i = 0, h = 0; i != n; ++i) {\n    if (rk[i] == n - 1) {\n      h = 0;\n    \
    \  continue;\n    }\n    int j = SA[rk[i] + 1];\n    while (i + h < n && j + h\
    \ < n && s[i + h] == s[j + h]) ++h;\n    height[rk[i]] = h;\n    if (h != 0) --h;\n\
    \  }\n  return height;\n}\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_array_sais.hpp
  requiredBy:
  - string/bwt.hpp
  timestamp: '2021-07-03 02:24:28+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/string/suffix_array.0.test.cpp
documentation_of: string/suffix_array_sais.hpp
layout: document
redirect_from:
- /library/string/suffix_array_sais.hpp
- /library/string/suffix_array_sais.hpp.html
title: "suffix array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\u6392\u5E8F\
  \uFF09"
---
## 后缀数组

后缀数组即对于串 $S$ 每个字符开头的后缀都进行排序后按顺序在数组中存储后缀开始的索引。

## 诱导排序

在 SA-IS 即诱导排序中我们假设 $S$ 末尾有一个为零的最小字典序的字符。

诱导排序的主旨为我们只需要选择 $S$ 所有后缀这个集合中的一组“恰当”的子集（这个子集为所有 LMS-型后缀），只要子集已经有序，那么就可以在线性时间内“诱导”出所有后缀的相对顺序。

- L-型后缀意为 larger 即其字典序比它右边一个字符开头的后缀大；
- S-型后缀意为 smaller 即其字典序比它右边一个字符开头的后缀小；
- LMS-型后缀本身是 S-型后缀但该后缀的左侧为 L-型后缀，所以 LMS 为 left most S-type 的缩写。

我们注意 LMS-型后缀的定义，其左侧必须为 L-型后缀，这也意味着字符串本身这个后缀如果为 S-型后缀那么其也不属于 LMS-型后缀。

我们将整个后缀数组按照每个后缀的首字母划分为多个“桶”，每个桶中首字母必定相同，更进一步的，在每个桶中 L-型后缀必然排名在 S-型后缀前。

在代码中我们计算每个桶的开头和结尾，放入有序的 LMS-型后缀，从桶的末尾依次放入。后对 L-型后缀进行诱导，从桶的开头依次放入，注意此时 LMS-型后缀也未必在其恰当的位置，我们需要利用 L-型后缀之间的相对顺序对 S-型后缀进行诱导。

证明略。注意我们对 LMS-子串也使用该方法进行排序后重新命名，那么 LMS-后缀间的相对顺序只需要求解这个新的字符串的后缀数组即可，此时问题至少被减少为原先的一半，那么 $T(n)=T(n/2)+O(n)$ 有 $T(n)=O(n)$ 。

诱导排序的思想由 P. Ko 和 S. Aluru 提出，但是他们对于 LMS-子串的排序使用了更为复杂的另一种方法且需要使用到他们定义的数据结构，而 G. Nong 、 S. Zhang 和 W. H. Chan 则是提出 LMS-子串也可以使用诱导排序。

## 部分注释的代码

```cpp
void SA_IS(const int *s, int *SA, int n, int K) {
  // s 为字符串数组[0..n-1] 必须保证 s[n-1]=0 且为最小值
  // SA 为存储后缀数组[0..n-1]
  // n 为字符串长度
  // K 为值域

  bool *t = new bool[n]; // 类型数组
  int *bkt = new int[K]; // 桶
  int *bkt_l = new int[K];
  int *bkt_r = new int[K];
  int n1 = 0; // LMS-后缀的数量
  int *p1;    //按出现顺序存储所有 LMS-后缀的索引

#define is_S_type(x) (t[x])
#define is_L_type(x) (!t[x])
#define is_LMS_type(x) (is_S_type(x) && x != 0 && is_L_type(x - 1))

  // 预处理每一个后缀的类型
  t[n - 1] = true; // 0 为 S-型后缀且为 LMS-型后缀
  for (int i = n - 2; i >= 0; --i) {
    t[i] = (s[i] < s[i + 1] || (is_S_type(i + 1) && s[i] == s[i + 1]));
    n1 += is_LMS_type(i + 1); // s[0] 必然不是 LMS-型后缀，不会影响
  }

  // 预处理桶的边界
  for (int i = 0; i != K; ++i) bkt[i] = 0;
  for (int i = 0; i != n; ++i) ++bkt[s[i]];
  for (int i = 0, sum = 0; i != K; ++i) sum += bkt[i], bkt_r[i] = sum, bkt_l[i] = sum - bkt[i];

#define induced_sort()                                                                             \
  do {                                                                                             \
    for (int i = 0; i != K; ++i) bkt[i] = bkt_l[i];                                                \
    for (int i = 0, j; i != n; ++i)                                                                \
      if ((j = SA[i] - 1) >= 0 && is_L_type(j)) SA[bkt[s[j]]++] = j;                               \
    for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];                                                \
    for (int i = n - 1, j; i >= 0; --i)                                                            \
      if ((j = SA[i] - 1) >= 0 && is_S_type(j)) SA[--bkt[s[j]]] = j;                               \
  } while (0)

  // 将所有 LMS-后缀放入 SA 对应桶的末尾并诱导排序
  p1 = new int[n1];
  for (int i = 0, j = 0; i != n; ++i) {
    SA[i] = -1;
    if (is_LMS_type(i)) p1[j++] = i;
  }
  for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];
  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] = p1[i];
  induced_sort();

  int *s1 = new int[n1];  // 新的字符串
  int *SA1 = new int[n1]; // 存储新的字符串排的后缀数组
  for (int i = 0, j = 0; i != n; ++i)
    if (is_LMS_type(SA[i])) SA1[j++] = SA[i]; // 存储 LMS-子串的相对顺序
  int name = 0;
  // 对所有 LMS-子串命名
  for (int i = 0, prev = -1; i != n1; ++i) {
    int pos = SA1[i];
    for (int j = 0;; ++j) // 无需设置范围，因为 s[n-1]=0 为最小值且不会出现在其余位置
      if (prev == -1 || s[pos + j] != s[prev + j] || is_S_type(pos + j) != is_S_type(prev + j)) {
        prev = pos, ++name;
        break;
      } else if (j != 0 && (is_LMS_type(pos + j) || is_LMS_type(prev + j))) // 到末尾了停止比较
        break;
    SA[pos] = name - 1; // 利用 SA 暂时存储新字符串的 name
  }
  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];

  if (name != n1)
    SA_IS(s1, SA1, n1, name);
  else
    for (int i = 0; i != n1; ++i) SA1[s1[i]] = i;

  for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];
  for (int i = 0; i != n; ++i) SA[i] = -1;
  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];
  induced_sort();

  delete[] SA1;
  delete[] s1;
  delete[] p1;
  delete[] bkt_r;
  delete[] bkt_l;
  delete[] bkt;
  delete[] t;

#undef is_S_type
#undef is_L_type
#undef is_LMS_type
#undef induced_sort
}
```

## 参考文献

- G. Nong, S. Zhang, and W. H. Chan, “Linear suffix array construction by almost pure induced-sorting,” in Proceedings of DCC, U.S.A., Mar. 2009.