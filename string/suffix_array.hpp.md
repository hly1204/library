---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/string/suffix_array.0.test.cpp
    title: remote_test/yosupo/string/suffix_array.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/suffix_array.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\
    \n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 5 \"string/suffix_array.hpp\"\n\n#include\
    \ <algorithm>\n#include <vector>\n\nLIB_BEGIN\n\nnamespace detail {\n\n// Input:\
    \  String `s` and integer `K`, where `s[i]` \u2208 [0, `K`).\n//         `s` must\
    \ ends with '\\0' and `s[i]` > 0 for all rest `i`.\n// Output: Suffix array of\
    \ `s`.\nstd::vector<int> SA_IS(const std::vector<int> &s, int K) {\n  const int\
    \ n = static_cast<int>(s.size());\n  std::vector<bool> t(n);\n  std::vector<int>\
    \ bkt(K, 0), bkt_l(K), bkt_r(K), SA(n), p1;\n#define IS_S_TYPE(x) (t[x])\n#define\
    \ IS_L_TYPE(x) (!t[x])\n#define IS_LMS_TYPE(x) (IS_S_TYPE(x) && x != 0 && IS_L_TYPE(x\
    \ - 1))\n  t.back() = true;\n  for (int i = n - 2; i >= 0; --i) {\n    t[i] =\
    \ (s[i] < s[i + 1] || (IS_S_TYPE(i + 1) && s[i] == s[i + 1]));\n    if (IS_LMS_TYPE(i\
    \ + 1)) p1.push_back(i + 1);\n  }\n  std::reverse(p1.begin(), p1.end());\n  const\
    \ int n1 = static_cast<int>(p1.size());\n  for (int i = 0; i != n; ++i) ++bkt[s[i]];\n\
    \  for (int i = 0, sum = 0; i != K; ++i) bkt_l[i] = sum, bkt_r[i] = (sum += bkt[i]);\n\
    \  std::vector<int> s1(n1), SA1(n1);\n  std::fill_n(SA.begin(), n, -1);\n  std::copy_n(bkt_r.begin(),\
    \ K, bkt.begin());\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] =\
    \ p1[i];\n  std::copy_n(bkt_l.begin(), K, bkt.begin());\n  for (int i = 0; i !=\
    \ n; ++i)\n    if (int j = SA[i] - 1; j >= 0 && IS_L_TYPE(j)) SA[bkt[s[j]]++]\
    \ = j;\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\n  for (int i = n - 1; i\
    \ >= 0; --i)\n    if (int j = SA[i] - 1; j >= 0 && IS_S_TYPE(j)) SA[--bkt[s[j]]]\
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
    \  for (int i = 0; i != n; ++i)\n    if (int j = SA[i] - 1; j >= 0 && IS_L_TYPE(j))\
    \ SA[bkt_l[s[j]]++] = j;\n  for (int i = n - 1; i >= 0; --i)\n    if (int j =\
    \ SA[i] - 1; j >= 0 && IS_S_TYPE(j)) SA[--bkt_r[s[j]]] = j;\n#undef IS_S_TYPE\n\
    #undef IS_L_TYPE\n#undef IS_LMS_TYPE\n  return SA;\n}\n\n} // namespace detail\n\
    \ntemplate <typename ContainerT>\nstd::vector<int> suffix_array(ContainerT &&s)\
    \ {\n  std::vector<int> s_cpy(s.size() + 1);\n  std::copy(s.cbegin(), s.cend(),\
    \ s_cpy.begin());\n  s_cpy.back() = 0;\n  auto SA      = detail::SA_IS(s_cpy,\
    \ *std::max_element(s_cpy.cbegin(), s_cpy.cend()) + 1);\n  SA.erase(SA.begin());\n\
    \  return SA;\n}\n\nLIB_END\n\n\n"
  code: "#ifndef SUFFIX_ARRAY_HPP\n#define SUFFIX_ARRAY_HPP\n\n#include \"../common.hpp\"\
    \n\n#include <algorithm>\n#include <vector>\n\nLIB_BEGIN\n\nnamespace detail {\n\
    \n// Input:  String `s` and integer `K`, where `s[i]` \u2208 [0, `K`).\n//   \
    \      `s` must ends with '\\0' and `s[i]` > 0 for all rest `i`.\n// Output: Suffix\
    \ array of `s`.\nstd::vector<int> SA_IS(const std::vector<int> &s, int K) {\n\
    \  const int n = static_cast<int>(s.size());\n  std::vector<bool> t(n);\n  std::vector<int>\
    \ bkt(K, 0), bkt_l(K), bkt_r(K), SA(n), p1;\n#define IS_S_TYPE(x) (t[x])\n#define\
    \ IS_L_TYPE(x) (!t[x])\n#define IS_LMS_TYPE(x) (IS_S_TYPE(x) && x != 0 && IS_L_TYPE(x\
    \ - 1))\n  t.back() = true;\n  for (int i = n - 2; i >= 0; --i) {\n    t[i] =\
    \ (s[i] < s[i + 1] || (IS_S_TYPE(i + 1) && s[i] == s[i + 1]));\n    if (IS_LMS_TYPE(i\
    \ + 1)) p1.push_back(i + 1);\n  }\n  std::reverse(p1.begin(), p1.end());\n  const\
    \ int n1 = static_cast<int>(p1.size());\n  for (int i = 0; i != n; ++i) ++bkt[s[i]];\n\
    \  for (int i = 0, sum = 0; i != K; ++i) bkt_l[i] = sum, bkt_r[i] = (sum += bkt[i]);\n\
    \  std::vector<int> s1(n1), SA1(n1);\n  std::fill_n(SA.begin(), n, -1);\n  std::copy_n(bkt_r.begin(),\
    \ K, bkt.begin());\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] =\
    \ p1[i];\n  std::copy_n(bkt_l.begin(), K, bkt.begin());\n  for (int i = 0; i !=\
    \ n; ++i)\n    if (int j = SA[i] - 1; j >= 0 && IS_L_TYPE(j)) SA[bkt[s[j]]++]\
    \ = j;\n  std::copy_n(bkt_r.begin(), K, bkt.begin());\n  for (int i = n - 1; i\
    \ >= 0; --i)\n    if (int j = SA[i] - 1; j >= 0 && IS_S_TYPE(j)) SA[--bkt[s[j]]]\
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
    \  for (int i = 0; i != n; ++i)\n    if (int j = SA[i] - 1; j >= 0 && IS_L_TYPE(j))\
    \ SA[bkt_l[s[j]]++] = j;\n  for (int i = n - 1; i >= 0; --i)\n    if (int j =\
    \ SA[i] - 1; j >= 0 && IS_S_TYPE(j)) SA[--bkt_r[s[j]]] = j;\n#undef IS_S_TYPE\n\
    #undef IS_L_TYPE\n#undef IS_LMS_TYPE\n  return SA;\n}\n\n} // namespace detail\n\
    \ntemplate <typename ContainerT>\nstd::vector<int> suffix_array(ContainerT &&s)\
    \ {\n  std::vector<int> s_cpy(s.size() + 1);\n  std::copy(s.cbegin(), s.cend(),\
    \ s_cpy.begin());\n  s_cpy.back() = 0;\n  auto SA      = detail::SA_IS(s_cpy,\
    \ *std::max_element(s_cpy.cbegin(), s_cpy.cend()) + 1);\n  SA.erase(SA.begin());\n\
    \  return SA;\n}\n\nLIB_END\n\n#endif\n"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: string/suffix_array.hpp
  requiredBy: []
  timestamp: '2023-06-08 20:27:48+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/string/suffix_array.0.test.cpp
documentation_of: string/suffix_array.hpp
layout: document
title: Suffix Array (SA-IS)
---

## Bibliography

1. Ge Nong, Sen Zhang and Wai Hong Chan. Linear Suffix Array Construction by Almost Pure Induced-Sorting.
