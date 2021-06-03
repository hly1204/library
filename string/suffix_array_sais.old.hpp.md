---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/suffix_array_sais.old.hpp\"\n\n\n\nnamespace discarded\
    \ {\n\nvoid SA_IS(const int *s, int *SA, int n, int K) {\n  // s \u4E3A\u5B57\u7B26\
    \u4E32\u6570\u7EC4[0..n-1] \u5FC5\u987B\u4FDD\u8BC1 s[n-1]=0 \u4E14\u4E3A\u6700\
    \u5C0F\u503C\n  // SA \u4E3A\u5B58\u50A8\u540E\u7F00\u6570\u7EC4[0..n-1]\n  //\
    \ n \u4E3A\u5B57\u7B26\u4E32\u957F\u5EA6\n  // K \u4E3A\u503C\u57DF\n\n  bool\
    \ *t = new bool[n]; // \u7C7B\u578B\u6570\u7EC4\n  int *bkt = new int[K]; // \u6876\
    \n  int *bkt_l = new int[K];\n  int *bkt_r = new int[K];\n  int n1 = 0; // LMS-\u540E\
    \u7F00\u7684\u6570\u91CF\n  int *p1;    //\u6309\u51FA\u73B0\u987A\u5E8F\u5B58\
    \u50A8\u6240\u6709 LMS-\u540E\u7F00\u7684\u7D22\u5F15\n\n#define is_S_type(x)\
    \ (t[x])\n#define is_L_type(x) (!t[x])\n#define is_LMS_type(x) (is_S_type(x) &&\
    \ x != 0 && is_L_type(x - 1))\n\n  // \u9884\u5904\u7406\u6BCF\u4E00\u4E2A\u540E\
    \u7F00\u7684\u7C7B\u578B\n  t[n - 1] = true; // 0 \u4E3A S-\u578B\u540E\u7F00\u4E14\
    \u4E3A LMS-\u578B\u540E\u7F00\n  for (int i = n - 2; i >= 0; --i) {\n    t[i]\
    \ = (s[i] < s[i + 1] || (is_S_type(i + 1) && s[i] == s[i + 1]));\n    n1 += is_LMS_type(i\
    \ + 1); // s[0] \u5FC5\u7136\u4E0D\u662F LMS-\u578B\u540E\u7F00\uFF0C\u4E0D\u4F1A\
    \u5F71\u54CD\n  }\n\n  // \u9884\u5904\u7406\u6876\u7684\u8FB9\u754C\n  for (int\
    \ i = 0; i != K; ++i) bkt[i] = 0;\n  for (int i = 0; i != n; ++i) ++bkt[s[i]];\n\
    \  for (int i = 0, sum = 0; i != K; ++i) sum += bkt[i], bkt_r[i] = sum, bkt_l[i]\
    \ = sum - bkt[i];\n\n#define induced_sort()                                  \
    \                                           \\\n  do {                       \
    \                                                                      \\\n  \
    \  for (int i = 0; i != K; ++i) bkt[i] = bkt_l[i];                           \
    \                     \\\n    for (int i = 0, j; i != n; ++i)                \
    \                                                \\\n      if ((j = SA[i] - 1)\
    \ >= 0 && is_L_type(j)) SA[bkt[s[j]]++] = j;                               \\\n\
    \    for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];                         \
    \                       \\\n    for (int i = n - 1, j; i >= 0; --i)          \
    \                                                  \\\n      if ((j = SA[i] -\
    \ 1) >= 0 && is_S_type(j)) SA[--bkt[s[j]]] = j;                              \
    \ \\\n  } while (0)\n\n  // \u5C06\u6240\u6709 LMS-\u540E\u7F00\u653E\u5165 SA\
    \ \u5BF9\u5E94\u6876\u7684\u672B\u5C3E\u5E76\u8BF1\u5BFC\u6392\u5E8F\n  p1 = new\
    \ int[n1];\n  for (int i = 0, j = 0; i != n; ++i) {\n    SA[i] = -1;\n    if (is_LMS_type(i))\
    \ p1[j++] = i;\n  }\n  for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];\n  for\
    \ (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]] = p1[i];\n  induced_sort();\n\
    \n  int *s1 = new int[n1];  // \u65B0\u7684\u5B57\u7B26\u4E32\n  int *SA1 = new\
    \ int[n1]; // \u5B58\u50A8\u65B0\u7684\u5B57\u7B26\u4E32\u6392\u7684\u540E\u7F00\
    \u6570\u7EC4\n  for (int i = 0, j = 0; i != n; ++i)\n    if (is_LMS_type(SA[i]))\
    \ SA1[j++] = SA[i]; // \u5B58\u50A8 LMS-\u5B50\u4E32\u7684\u76F8\u5BF9\u987A\u5E8F\
    \n  int name = 0;\n  // \u5BF9\u6240\u6709 LMS-\u5B50\u4E32\u547D\u540D\n  for\
    \ (int i = 0, prev = -1; i != n1; ++i) {\n    int pos = SA1[i];\n    for (int\
    \ j = 0;; ++j) // \u65E0\u9700\u8BBE\u7F6E\u8303\u56F4\uFF0C\u56E0\u4E3A s[n-1]=0\
    \ \u4E3A\u6700\u5C0F\u503C\u4E14\u4E0D\u4F1A\u51FA\u73B0\u5728\u5176\u4F59\u4F4D\
    \u7F6E\n      if (prev == -1 || s[pos + j] != s[prev + j] || is_S_type(pos + j)\
    \ != is_S_type(prev + j)) {\n        prev = pos, ++name;\n        break;\n   \
    \   } else if (j != 0 && (is_LMS_type(pos + j) || is_LMS_type(prev + j))) // \u5230\
    \u672B\u5C3E\u4E86\u505C\u6B62\u6BD4\u8F83\n        break;\n    SA[pos] = name\
    \ - 1; // \u5229\u7528 SA \u6682\u65F6\u5B58\u50A8\u65B0\u5B57\u7B26\u4E32\u7684\
    \ name\n  }\n  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];\n\n  if (name\
    \ != n1)\n    SA_IS(s1, SA1, n1, name);\n  else\n    for (int i = 0; i != n1;\
    \ ++i) SA1[s1[i]] = i;\n\n  for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];\n\
    \  for (int i = 0; i != n; ++i) SA[i] = -1;\n  for (int i = n1 - 1; i >= 0; --i)\
    \ SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];\n  induced_sort();\n\n  delete[] SA1;\n\
    \  delete[] s1;\n  delete[] p1;\n  delete[] bkt_r;\n  delete[] bkt_l;\n  delete[]\
    \ bkt;\n  delete[] t;\n\n#undef is_S_type\n#undef is_L_type\n#undef is_LMS_type\n\
    #undef induced_sort\n}\n\n} // namespace discarded\n\n\n"
  code: "#ifndef SUFFIX_ARRAY_SAIS_HEADER_HPP\n#define SUFFIX_ARRAY_SAIS_HEADER_HPP\n\
    \nnamespace discarded {\n\nvoid SA_IS(const int *s, int *SA, int n, int K) {\n\
    \  // s \u4E3A\u5B57\u7B26\u4E32\u6570\u7EC4[0..n-1] \u5FC5\u987B\u4FDD\u8BC1\
    \ s[n-1]=0 \u4E14\u4E3A\u6700\u5C0F\u503C\n  // SA \u4E3A\u5B58\u50A8\u540E\u7F00\
    \u6570\u7EC4[0..n-1]\n  // n \u4E3A\u5B57\u7B26\u4E32\u957F\u5EA6\n  // K \u4E3A\
    \u503C\u57DF\n\n  bool *t = new bool[n]; // \u7C7B\u578B\u6570\u7EC4\n  int *bkt\
    \ = new int[K]; // \u6876\n  int *bkt_l = new int[K];\n  int *bkt_r = new int[K];\n\
    \  int n1 = 0; // LMS-\u540E\u7F00\u7684\u6570\u91CF\n  int *p1;    //\u6309\u51FA\
    \u73B0\u987A\u5E8F\u5B58\u50A8\u6240\u6709 LMS-\u540E\u7F00\u7684\u7D22\u5F15\n\
    \n#define is_S_type(x) (t[x])\n#define is_L_type(x) (!t[x])\n#define is_LMS_type(x)\
    \ (is_S_type(x) && x != 0 && is_L_type(x - 1))\n\n  // \u9884\u5904\u7406\u6BCF\
    \u4E00\u4E2A\u540E\u7F00\u7684\u7C7B\u578B\n  t[n - 1] = true; // 0 \u4E3A S-\u578B\
    \u540E\u7F00\u4E14\u4E3A LMS-\u578B\u540E\u7F00\n  for (int i = n - 2; i >= 0;\
    \ --i) {\n    t[i] = (s[i] < s[i + 1] || (is_S_type(i + 1) && s[i] == s[i + 1]));\n\
    \    n1 += is_LMS_type(i + 1); // s[0] \u5FC5\u7136\u4E0D\u662F LMS-\u578B\u540E\
    \u7F00\uFF0C\u4E0D\u4F1A\u5F71\u54CD\n  }\n\n  // \u9884\u5904\u7406\u6876\u7684\
    \u8FB9\u754C\n  for (int i = 0; i != K; ++i) bkt[i] = 0;\n  for (int i = 0; i\
    \ != n; ++i) ++bkt[s[i]];\n  for (int i = 0, sum = 0; i != K; ++i) sum += bkt[i],\
    \ bkt_r[i] = sum, bkt_l[i] = sum - bkt[i];\n\n#define induced_sort()         \
    \                                                                    \\\n  do\
    \ {                                                                          \
    \                   \\\n    for (int i = 0; i != K; ++i) bkt[i] = bkt_l[i];  \
    \                                              \\\n    for (int i = 0, j; i !=\
    \ n; ++i)                                                                \\\n\
    \      if ((j = SA[i] - 1) >= 0 && is_L_type(j)) SA[bkt[s[j]]++] = j;        \
    \                       \\\n    for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];\
    \                                                \\\n    for (int i = n - 1, j;\
    \ i >= 0; --i)                                                            \\\n\
    \      if ((j = SA[i] - 1) >= 0 && is_S_type(j)) SA[--bkt[s[j]]] = j;        \
    \                       \\\n  } while (0)\n\n  // \u5C06\u6240\u6709 LMS-\u540E\
    \u7F00\u653E\u5165 SA \u5BF9\u5E94\u6876\u7684\u672B\u5C3E\u5E76\u8BF1\u5BFC\u6392\
    \u5E8F\n  p1 = new int[n1];\n  for (int i = 0, j = 0; i != n; ++i) {\n    SA[i]\
    \ = -1;\n    if (is_LMS_type(i)) p1[j++] = i;\n  }\n  for (int i = 0; i != K;\
    \ ++i) bkt[i] = bkt_r[i];\n  for (int i = n1 - 1; i >= 0; --i) SA[--bkt[s[p1[i]]]]\
    \ = p1[i];\n  induced_sort();\n\n  int *s1 = new int[n1];  // \u65B0\u7684\u5B57\
    \u7B26\u4E32\n  int *SA1 = new int[n1]; // \u5B58\u50A8\u65B0\u7684\u5B57\u7B26\
    \u4E32\u6392\u7684\u540E\u7F00\u6570\u7EC4\n  for (int i = 0, j = 0; i != n; ++i)\n\
    \    if (is_LMS_type(SA[i])) SA1[j++] = SA[i]; // \u5B58\u50A8 LMS-\u5B50\u4E32\
    \u7684\u76F8\u5BF9\u987A\u5E8F\n  int name = 0;\n  // \u5BF9\u6240\u6709 LMS-\u5B50\
    \u4E32\u547D\u540D\n  for (int i = 0, prev = -1; i != n1; ++i) {\n    int pos\
    \ = SA1[i];\n    for (int j = 0;; ++j) // \u65E0\u9700\u8BBE\u7F6E\u8303\u56F4\
    \uFF0C\u56E0\u4E3A s[n-1]=0 \u4E3A\u6700\u5C0F\u503C\u4E14\u4E0D\u4F1A\u51FA\u73B0\
    \u5728\u5176\u4F59\u4F4D\u7F6E\n      if (prev == -1 || s[pos + j] != s[prev +\
    \ j] || is_S_type(pos + j) != is_S_type(prev + j)) {\n        prev = pos, ++name;\n\
    \        break;\n      } else if (j != 0 && (is_LMS_type(pos + j) || is_LMS_type(prev\
    \ + j))) // \u5230\u672B\u5C3E\u4E86\u505C\u6B62\u6BD4\u8F83\n        break;\n\
    \    SA[pos] = name - 1; // \u5229\u7528 SA \u6682\u65F6\u5B58\u50A8\u65B0\u5B57\
    \u7B26\u4E32\u7684 name\n  }\n  for (int i = 0; i != n1; ++i) s1[i] = SA[p1[i]];\n\
    \n  if (name != n1)\n    SA_IS(s1, SA1, n1, name);\n  else\n    for (int i = 0;\
    \ i != n1; ++i) SA1[s1[i]] = i;\n\n  for (int i = 0; i != K; ++i) bkt[i] = bkt_r[i];\n\
    \  for (int i = 0; i != n; ++i) SA[i] = -1;\n  for (int i = n1 - 1; i >= 0; --i)\
    \ SA[--bkt[s[p1[SA1[i]]]]] = p1[SA1[i]];\n  induced_sort();\n\n  delete[] SA1;\n\
    \  delete[] s1;\n  delete[] p1;\n  delete[] bkt_r;\n  delete[] bkt_l;\n  delete[]\
    \ bkt;\n  delete[] t;\n\n#undef is_S_type\n#undef is_L_type\n#undef is_LMS_type\n\
    #undef induced_sort\n}\n\n} // namespace discarded\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_array_sais.old.hpp
  requiredBy: []
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/suffix_array_sais.old.hpp
layout: document
redirect_from:
- /library/string/suffix_array_sais.old.hpp
- /library/string/suffix_array_sais.old.hpp.html
title: string/suffix_array_sais.old.hpp
---
