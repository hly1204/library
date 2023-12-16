---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp
    title: remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/cartesian_tree.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 5 \"datastructure/cartesian_tree.hpp\"\n\n\
    #include <functional>\n#include <stack>\n#include <tuple>\n#include <vector>\n\
    \nLIB_BEGIN\n\ntemplate <typename ContainerT, typename CmpT = std::less<>>\nstd::tuple<std::vector<int>,\
    \ std::vector<int>, std::vector<int>>\nbuild_cartesian_tree(ContainerT &&a) {\n\
    \  int n = static_cast<int>(a.size());\n  CmpT cmp;\n  std::vector<int> l(n, -1),\
    \ r(n, -1), p(n, -1);\n  std::stack<int, std::vector<int>> s;\n  for (int i =\
    \ 0; i != n; ++i) {\n    int last_poped = -1;\n    while (!s.empty() && cmp(a[i],\
    \ a[s.top()])) last_poped = s.top(), s.pop();\n    if (last_poped != -1) p[l[i]\
    \ = last_poped] = i;\n    if (!s.empty()) r[p[i] = s.top()] = i;\n    s.push(i);\n\
    \  }\n  return {l, r, p};\n}\n\nLIB_END\n\n\n"
  code: "#ifndef CARTESIAN_TREE_HPP\n#define CARTESIAN_TREE_HPP\n\n#include \"../common.hpp\"\
    \n\n#include <functional>\n#include <stack>\n#include <tuple>\n#include <vector>\n\
    \nLIB_BEGIN\n\ntemplate <typename ContainerT, typename CmpT = std::less<>>\nstd::tuple<std::vector<int>,\
    \ std::vector<int>, std::vector<int>>\nbuild_cartesian_tree(ContainerT &&a) {\n\
    \  int n = static_cast<int>(a.size());\n  CmpT cmp;\n  std::vector<int> l(n, -1),\
    \ r(n, -1), p(n, -1);\n  std::stack<int, std::vector<int>> s;\n  for (int i =\
    \ 0; i != n; ++i) {\n    int last_poped = -1;\n    while (!s.empty() && cmp(a[i],\
    \ a[s.top()])) last_poped = s.top(), s.pop();\n    if (last_poped != -1) p[l[i]\
    \ = last_poped] = i;\n    if (!s.empty()) r[p[i] = s.top()] = i;\n    s.push(i);\n\
    \  }\n  return {l, r, p};\n}\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: datastructure/cartesian_tree.hpp
  requiredBy: []
  timestamp: '2022-05-02 00:19:44+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp
documentation_of: datastructure/cartesian_tree.hpp
layout: document
title: Cartesian Tree
---
