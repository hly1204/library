---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/suffix_array_sais.hpp
    title: "suffix array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\u6392\u5E8F\
      \uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"remote_test/yosupo/string/suffix_array.0.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\r\n\r\n#include <iostream>\r\
    \n#include <string>\r\n#include <vector>\r\n\r\n#line 1 \"string/suffix_array_sais.hpp\"\
    \n\n\n\r\n/**\r\n * @brief suffix array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\
    \u8BF1\u5BFC\u6392\u5E8F\uFF09\r\n * @docs docs/string/suffix_array_sais.md\r\n\
    \ */\r\n\r\n#include <algorithm>\r\n#line 12 \"string/suffix_array_sais.hpp\"\n\
    \r\nnamespace lib::internal {\r\n\r\n/**\r\n * @brief \u8BF1\u5BFC\u6392\u5E8F\
    \r\n * @ref Ge Nong, Sen Zhang and Wai Hong Chan.\r\n *      Linear Suffix Array\
    \ Construction by Almost Pure Induced-Sorting.\r\n *\r\n * @param s \u5B57\u7B26\
    \u4E32\u6570\u7EC4\uFF0C\u5FC5\u987B\u4FDD\u8BC1\u672B\u5C3E\u4E3A 0 \u4E14 0\
    \ \u662F\u6574\u4E2A\u5B57\u7B26\u4E32\u6570\u7EC4\u4E2D\u53EA\u51FA\u73B0\u5728\
    \u672B\u5C3E\u7684\u6700\u5C0F\u5B57\u7B26\uFF01\r\n * @param K \u5B57\u7B26\u4E32\
    \u6570\u7EC4\u7684\u503C\u57DF\uFF0C\u7531 [0, K)\r\n * @return std::vector<int>\r\
    \n */\r\nstd::vector<int> SA_IS(const std::vector<int> &s, int K) {\r\n  const\
    \ int n = s.size();\r\n  std::vector<bool> t(n);\r\n  std::vector<int> bkt(K,\
    \ 0), bkt_l(K), bkt_r(K), SA(n), p1;\r\n#define IS_S_TYPE(x) (t[x])\r\n#define\
    \ IS_L_TYPE(x) (!t[x])\r\n#define IS_LMS_TYPE(x) (IS_S_TYPE(x) && x != 0 && IS_L_TYPE(x\
    \ - 1))\r\n  t.back() = true;\r\n  for (int i = n - 2; i >= 0; --i) {\r\n    t[i]\
    \ = (s[i] < s[i + 1] || (IS_S_TYPE(i + 1) && s[i] == s[i + 1]));\r\n    if (IS_LMS_TYPE(i\
    \ + 1)) p1.push_back(i + 1);\r\n  }\r\n  std::reverse(p1.begin(), p1.end());\r\
    \n  const int n1 = p1.size();\r\n  for (int i = 0; i != n; ++i) ++bkt[s[i]];\r\
    \n  for (int i = 0, sum = 0; i != K; ++i) sum += bkt[i], bkt_r[i] = sum, bkt_l[i]\
    \ = sum - bkt[i];\r\n  std::vector<int> s1(n1), SA1(n1);\r\n  std::fill_n(SA.begin(),\
    \ n, -1);\r\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\r\n  for (int i = n1\
    \ - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] = p1[i];\r\n  std::copy_n(bkt_l.begin(),\
    \ K, bkt.begin());\r\n  for (int i = 0, j; i != n; ++i)\r\n    if ((j = SA[i]\
    \ - 1) >= 0 && IS_L_TYPE(j)) SA[bkt[s[j]]++] = j;\r\n  std::copy_n(bkt_r.begin(),\
    \ K, bkt.begin());\r\n  for (int i = n - 1, j; i >= 0; --i)\r\n    if ((j = SA[i]\
    \ - 1) >= 0 && IS_S_TYPE(j)) SA[--bkt[s[j]]] = j;\r\n  for (int i = 0, j = 0;\
    \ i != n; ++i)\r\n    if (IS_LMS_TYPE(SA[i])) SA1[j++] = SA[i];\r\n  int name\
    \ = 0;\r\n  for (int i = 0, prev = -1; i != n1; ++i) {\r\n    int pos = SA1[i];\r\
    \n    for (int j = 0;; ++j)\r\n      if (prev == -1 || s[pos + j] != s[prev +\
    \ j] || IS_S_TYPE(pos + j) != IS_S_TYPE(prev + j)) {\r\n        prev = pos, ++name;\r\
    \n        break;\r\n      } else if (j != 0 && (IS_LMS_TYPE(pos + j) || IS_LMS_TYPE(prev\
    \ + j)))\r\n        break;\r\n    SA[pos] = name - 1;\r\n  }\r\n  for (int i =\
    \ 0; i != n1; ++i) s1[i] = SA[p1[i]];\r\n  if (name != n1) {\r\n    SA1 = SA_IS(s1,\
    \ name);\r\n  } else {\r\n    for (int i = 0; i != n1; ++i) SA1[s1[i]] = i;\r\n\
    \  }\r\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\r\n  std::fill_n(SA.begin(),\
    \ n, -1);\r\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];\r\
    \n  for (int i = 0, j; i != n; ++i)\r\n    if ((j = SA[i] - 1) >= 0 && IS_L_TYPE(j))\
    \ SA[bkt_l[s[j]]++] = j;\r\n  for (int i = n - 1, j; i >= 0; --i)\r\n    if ((j\
    \ = SA[i] - 1) >= 0 && IS_S_TYPE(j)) SA[--bkt_r[s[j]]] = j;\r\n#undef IS_S_TYPE\r\
    \n#undef IS_L_TYPE\r\n#undef IS_LMS_TYPE\r\n  return SA;\r\n}\r\n\r\n} // namespace\
    \ lib::internal\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u83B7\u53D6\u540E\
    \u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\r\n * @param s \u5B57\u7B26\u4E32\uFF0C\
    \u4E00\u822C\u4E3A string \u6216 std::vector<int>\r\n * @return std::vector<int>\
    \ \u540E\u7F00\u6570\u7EC4\r\n */\r\ntemplate <typename Container>\r\nstd::vector<int>\
    \ get_sa(const Container &s) {\r\n  std::vector<int> s_cpy(s.size() + 1);\r\n\
    \  std::copy(s.begin(), s.end(), s_cpy.begin());\r\n  s_cpy.back() = 0;\r\n  std::vector<int>\
    \ SA(internal::SA_IS(s_cpy, *std::max_element(s.begin(), s.end()) + 1));\r\n \
    \ SA.erase(SA.begin());\r\n  return SA;\r\n}\r\n\r\n/**\r\n * @brief \u83B7\u53D6\
    \u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\u7684\u7279\u5316\r\n * @note\
    \ \u5BB9\u5668\u4E3A std::string \u65F6\u7279\u5316\uFF01\r\n * @param s \u5B57\
    \u7B26\u4E32\r\n * @return std::vector<int>\r\n */\r\ntemplate <>\r\nstd::vector<int>\
    \ get_sa<std::string>(const std::string &s) {\r\n  std::vector<int> s_cpy(s.size()\
    \ + 1);\r\n  std::copy(s.begin(), s.end(), s_cpy.begin());\r\n  s_cpy.back() =\
    \ 0;\r\n  std::vector<int> SA(internal::SA_IS(s_cpy, 128));\r\n  SA.erase(SA.begin());\r\
    \n  return SA;\r\n}\r\n\r\n/**\r\n * @brief \u83B7\u53D6 LCP \u6570\u7EC4\r\n\
    \ * @see https://cp-algorithms.com/string/suffix-array.html\r\n * @param s \u5B57\
    \u7B26\u4E32\r\n * @param SA \u8BA1\u7B97\u5B8C\u6BD5\u7684 s \u7684\u540E\u7F00\
    \u6570\u7EC4\uFF08 0-indexed \uFF09\r\n * @return std::vector<int> LCP \u6570\u7EC4\
    \r\n */\r\ntemplate <typename Container>\r\nstd::vector<int> get_lcp(const Container\
    \ &s, const std::vector<int> &SA) {\r\n  int n = s.size();\r\n  std::vector<int>\
    \ rk(n), height(n - 1, 0);\r\n  // height[i] = s[SA[i]..n-1] \u4E0E s[SA[i+1]..n-1]\
    \ \u7684\u6700\u957F\u516C\u5171\u524D\u7F00\uFF08 longest common prefix \uFF09\
    \r\n  // Kasai \u7684\u8BBA\u6587\u4E2D\u79F0\u5176\u4E3A lcp \u6570\u7EC4\u6216\
    \ height \u6570\u7EC4\r\n  for (int i = 0; i != n; ++i) rk[SA[i]] = i;\r\n  for\
    \ (int i = 0, h = 0; i != n; ++i) {\r\n    if (rk[i] == n - 1) {\r\n      h =\
    \ 0;\r\n      continue;\r\n    }\r\n    int j = SA[rk[i] + 1];\r\n    while (i\
    \ + h < n && j + h < n && s[i + h] == s[j + h]) ++h;\r\n    height[rk[i]] = h;\r\
    \n    if (h != 0) --h;\r\n  }\r\n  return height;\r\n}\r\n\r\n} // namespace lib\r\
    \n\r\n\n#line 8 \"remote_test/yosupo/string/suffix_array.0.test.cpp\"\n\r\nint\
    \ main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  std::string s;\r\n  std::cin >> s;\r\n  for (auto i : lib::get_sa(s)) std::cout\
    \ << i << ' ';\r\n  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\r\n\r\n#include\
    \ <iostream>\r\n#include <string>\r\n#include <vector>\r\n\r\n#include \"string/suffix_array_sais.hpp\"\
    \r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  std::string s;\r\n  std::cin >> s;\r\n  for (auto i\
    \ : lib::get_sa(s)) std::cout << i << ' ';\r\n  return 0;\r\n}"
  dependsOn:
  - string/suffix_array_sais.hpp
  isVerificationFile: true
  path: remote_test/yosupo/string/suffix_array.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/string/suffix_array.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/string/suffix_array.0.test.cpp
- /verify/remote_test/yosupo/string/suffix_array.0.test.cpp.html
title: remote_test/yosupo/string/suffix_array.0.test.cpp
---
