---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: string/suffix_array_sais.hpp
    title: "suffix array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\u6392\u5E8F\
      \uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"remote_test/yosupo/string/suffix_array.0.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include <iostream>\n\
    #include <string>\n#include <vector>\n\n#line 1 \"string/suffix_array_sais.hpp\"\
    \n/**\n * @brief suffix array SA-IS / \u540E\u7F00\u6570\u7EC4\uFF08\u8BF1\u5BFC\
    \u6392\u5E8F\uFF09\n *\n */\n\n#ifndef SUFFIX_ARRAY_SAIS_HEADER_HPP\n#define SUFFIX_ARRAY_SAIS_HEADER_HPP\n\
    \n#include <algorithm>\n#line 12 \"string/suffix_array_sais.hpp\"\n\nnamespace\
    \ lib {\n\nnamespace internal {\n\nstd::vector<int> SA_IS(const std::vector<int>\
    \ &s, int K) {\n  const int n = s.size();\n  std::vector<bool> t(n);\n  std::vector<int>\
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
    \ induced_sort\n  return SA;\n}\n\n} // namespace internal\n\n/**\n * @brief \u83B7\
    \u53D6\u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\n *\n * @param s \u5B57\u7B26\
    \u4E32\n * @return std::vector<int> \u540E\u7F00\u6570\u7EC4\n */\nstd::vector<int>\
    \ get_sa(const std::string &s) {\n  std::vector<int> s_cpy(s.size() + 1);\n  std::copy(s.begin(),\
    \ s.end(), s_cpy.begin());\n  s_cpy.back() = 0;\n  std::vector<int> SA(internal::SA_IS(s_cpy,\
    \ 128));\n  SA.erase(SA.begin());\n  return SA;\n}\n\n/**\n * @brief \u8FD4\u56DE\
    \ LCP \u6570\u7EC4\n *\n * @param s \u5B57\u7B26\u4E32\n * @param SA \u8BA1\u7B97\
    \u5B8C\u6BD5\u7684 s \u7684\u540E\u7F00\u6570\u7EC4\uFF08 0-indexed \uFF09\n *\
    \ @return std::vector<int> LCP \u6570\u7EC4\n */\nstd::vector<int> get_height(const\
    \ std::string &s, const std::vector<int> &SA) {\n  // reference: https://cp-algorithms.com/string/suffix-array.html\n\
    \  int n = s.size();\n  std::vector<int> rk(n), height(n - 1, 0);\n  // height[i]\
    \ = s[SA[i]..n-1] \u4E0E s[SA[i+1]..n-1] \u7684\u6700\u957F\u516C\u5171\u524D\u7F00\
    \uFF08 longest common prefix \uFF09\n  // Kasai \u7684\u8BBA\u6587\u4E2D\u79F0\
    \u5176\u4E3A lcp \u6570\u7EC4\u6216 height \u6570\u7EC4\n  for (int i = 0; i !=\
    \ n; ++i) rk[SA[i]] = i;\n  for (int i = 0, h = 0; i != n; ++i) {\n    if (rk[i]\
    \ == n - 1) {\n      h = 0;\n      continue;\n    }\n    int j = SA[rk[i] + 1];\n\
    \    while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;\n    height[rk[i]]\
    \ = h;\n    if (h != 0) --h;\n  }\n  return height;\n}\n\n} // namespace lib\n\
    \n#endif\n#line 8 \"remote_test/yosupo/string/suffix_array.0.test.cpp\"\n\nint\
    \ main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  std::string s;\n  std::cin >> s;\n  for (auto i : lib::get_sa(s)) std::cout\
    \ << i << ' ';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include\
    \ <iostream>\n#include <string>\n#include <vector>\n\n#include \"string/suffix_array_sais.hpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  std::string s;\n  std::cin >> s;\n  for (auto i : lib::get_sa(s)) std::cout\
    \ << i << ' ';\n  return 0;\n}"
  dependsOn:
  - string/suffix_array_sais.hpp
  isVerificationFile: true
  path: remote_test/yosupo/string/suffix_array.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: remote_test/yosupo/string/suffix_array.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/string/suffix_array.0.test.cpp
- /verify/remote_test/yosupo/string/suffix_array.0.test.cpp.html
title: remote_test/yosupo/string/suffix_array.0.test.cpp
---
