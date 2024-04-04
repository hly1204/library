---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: string/z_function.hpp
    title: Z Function
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"remote_test/yosupo/string/z_algorithm.0.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#line 1 \"string/z_function.hpp\"\
    \n\n\n\n#line 1 \"common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace\
    \ lib {\n#define LIB_END }\n#define LIB ::lib::\n\n\n#line 5 \"string/z_function.hpp\"\
    \n\n#include <vector>\n\nLIB_BEGIN\n\ntemplate <typename ContainerT>\nstd::vector<int>\
    \ z_function(ContainerT &&s) {\n  const int n = static_cast<int>(s.size());\n\
    \  std::vector<int> z(n, 0);\n  if (n == 0) return z;\n  if ((z[0] = n) == 1)\
    \ return z;\n  int zi = 0, l = -1, r = -1, i = 2;\n  for (auto s0 = s[0]; zi +\
    \ 1 < n && s[zi + 1] == s0; ++zi) {}\n  if ((z[1] = r = zi) > 0)\n    for (l =\
    \ 1; i < n && zi >= 0;) z[i++] = --zi;\n  for (; i < n; ++i)\n    if (r < i) {\n\
    \      for (zi = 0; zi + i < n && s[zi] == s[zi + i]; ++zi) {}\n      if ((z[i]\
    \ = zi) > 0) l = i, r = zi + i - 1;\n    } else if ((z[i] = z[i - l]) >= r - i\
    \ + 1) {\n      for (zi = r - i + 1; zi + i < n && s[zi] == s[zi + i]; ++zi) {}\n\
    \      z[i] = zi, l = i, r = zi + i - 1;\n    }\n  return z;\n}\n\nLIB_END\n\n\
    \n#line 4 \"remote_test/yosupo/string/z_algorithm.0.test.cpp\"\n\n#include <iostream>\n\
    #include <string>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\"\
    , stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n  std::string s;\n  std::cin >> s;\n  for (auto i :\
    \ lib::z_function(s)) std::cout << i << ' ';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#include\
    \ \"string/z_function.hpp\"\n\n#include <iostream>\n#include <string>\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  std::string s;\n  std::cin >> s;\n  for (auto i : lib::z_function(s)) std::cout\
    \ << i << ' ';\n  return 0;\n}"
  dependsOn:
  - string/z_function.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/yosupo/string/z_algorithm.0.test.cpp
  requiredBy: []
  timestamp: '2022-05-01 23:45:11+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/string/z_algorithm.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/string/z_algorithm.0.test.cpp
- /verify/remote_test/yosupo/string/z_algorithm.0.test.cpp.html
title: remote_test/yosupo/string/z_algorithm.0.test.cpp
---
