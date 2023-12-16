---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: math/extended_gcd.hpp
    title: Extended Euclidean Algorithm (in $\mathbb{Z}$)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E
  bundledCode: "#line 1 \"remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp\"\
    \n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E\"\
    \n\n#line 1 \"math/extended_gcd.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\n#define\
    \ LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n#define LIB\
    \ ::lib::\n\n\n#line 5 \"math/extended_gcd.hpp\"\n\n#include <tuple>\n#include\
    \ <utility>\n#include <vector>\n\nLIB_BEGIN\n\n// Input:  integer `a` and `b`.\n\
    // Output: (x, y, z) such that `a`x + `b`y = z = gcd(`a`, `b`).\n[[deprecated]]\
    \ std::tuple<long long, long long, long long> ext_gcd(long long a, long long b)\
    \ {\n  long long x11 = 1, x12 = 0, x21 = 0, x22 = 1;\n  while (b != 0) {\n   \
    \ long long q = a / b, x11_cpy = x11, x12_cpy = x12, a_cpy = a;\n    x11 = x21,\
    \ x21 = x11_cpy - q * x21;\n    x12 = x22, x22 = x12_cpy - q * x22;\n    a = b,\
    \ b = a_cpy - q * b;\n  }\n  return std::make_tuple(x11, x12, a);\n}\n\n// Input:\
    \  integer `a` and `b`.\n// Output: (x, gcd(`a`, `b`)) such that `a`x \u2261 gcd(`a`,\
    \ `b`) (mod `b`).\nstd::pair<long long, long long> inv_gcd(long long a, long long\
    \ b) {\n  long long x11 = 1, x21 = 0;\n  while (b != 0) {\n    long long q = a\
    \ / b, x11_cpy = x11, a_cpy = a;\n    x11 = x21, x21 = x11_cpy - q * x21;\n  \
    \  a = b, b = a_cpy - q * b;\n  }\n  return std::make_pair(x11, a);\n}\n\nnamespace\
    \ detail {\n\ntemplate <typename ModIntT>\nclass modular_inverse {\n  std::vector<ModIntT>\
    \ ivs{ModIntT()};\n\n  enum : int { LIM = 1 << 20 };\n\npublic:\n  modular_inverse()\
    \ {}\n  ModIntT operator()(int k) {\n    // assume `ModIntT::mod()` is prime.\n\
    \    if (k > LIM) return ModIntT(k).inv();\n    // preprocess modular inverse\
    \ from 1 to `k`\n    if (int n = static_cast<int>(ivs.size()); n <= k) {\n   \
    \   int nn = n;\n      while (nn <= k) nn <<= 1;\n      ivs.resize(nn);\n    \
    \  ModIntT v(1);\n      for (int i = n; i != nn; ++i) ivs[i] = v, v *= ModIntT(i);\n\
    \      v = v.inv();\n      for (int i = nn - 1; i >= n; --i) ivs[i] *= v, v *=\
    \ ModIntT(i);\n    }\n    return ivs[k];\n  }\n};\n\n} // namespace detail\n\n\
    LIB_END\n\n\n#line 4 \"remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\",\
    \ \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n  int a, b;\n  std::cin >> a >> b;\n  auto [c, d, g]\
    \ = lib::ext_gcd(a, b);\n  std::cout << c << ' ' << d << '\\n';\n  return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E\"\
    \n\n#include \"math/extended_gcd.hpp\"\n\n#include <iostream>\n\nint main() {\n\
    #ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\", \"w\"\
    , stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int a, b;\n  std::cin >> a >> b;\n  auto [c, d, g] = lib::ext_gcd(a, b);\n\
    \  std::cout << c << ' ' << d << '\\n';\n  return 0;\n}"
  dependsOn:
  - math/extended_gcd.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp
  requiredBy: []
  timestamp: '2022-04-26 01:17:42+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp
- /verify/remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp.html
title: remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp
---
