---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod
    links:
    - https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod
  bundledCode: "#line 1 \"test/matrix/matrix_det_arbitrary_mod.0.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod\"\n\n#include\
    \ <cassert>\n#include <iostream>\n#include <vector>\n\nint det(std::vector<std::vector<int>>\
    \ a, int mod) {\n    assert(mod > 1);\n    const int n = a.size();\n    int det\
    \     = 1;\n    for (int i = 0; i < n; ++i) {\n        int pivot = i;\n      \
    \  for (; pivot < n; ++pivot)\n            if (a[pivot][i] != 0) break;\n    \
    \    if (pivot == n) return 0;\n        if (pivot != i) {\n            a[pivot].swap(a[i]);\n\
    \            det = mod - det;\n        }\n        for (int j = i + 1; j < n; ++j)\
    \ {\n            int aii = a[i][i], aji = a[j][i];\n            if (aji == 0)\
    \ continue;\n            // `a0` * `a[i][i]` + `a1` * `a[j][i]`     (1)\n    \
    \        // `b0` * `a[i][i]` + `b1` * `a[j][i]`     (2)\n            // Use Euclidean\
    \ algorithm to compute `a0, a1, b0, b1` s.t. (1) = 0 or (2) = 0\n            int\
    \ a0 = 1, a1 = 0, b0 = 0, b1 = 1;\n            while (aii != 0 && aji != 0) {\n\
    \                if (aii < aji) {\n                    const int q = aji / aii;\n\
    \                    aji -= aii * q, b0 -= a0 * q, b1 -= a1 * q;\n           \
    \     } else {\n                    const int q = aii / aji;\n               \
    \     aii -= aji * q, a0 -= b0 * q, a1 -= b1 * q;\n                }\n       \
    \     }\n            if (a0 < mod) a0 += mod;\n            if (a1 < mod) a1 +=\
    \ mod;\n            if (b0 < mod) b0 += mod;\n            if (b1 < mod) b1 +=\
    \ mod;\n            for (int k = i; k < n; ++k) {\n                const long\
    \ long aik = a[i][k], ajk = a[j][k];\n                a[i][k] = (aik * a0 + ajk\
    \ * a1) % mod;\n                a[j][k] = (aik * b0 + ajk * b1) % mod;\n     \
    \       }\n            if (aii == 0) {\n                a[i].swap(a[j]);\n   \
    \             det = mod - det;\n            }\n        }\n        if ((det = (long\
    \ long)det * a[i][i] % mod) == 0) return 0;\n    }\n    return det;\n}\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, mod;\n    std::cin >> n >> mod;\n    std::vector a(n, std::vector<int>(n));\n\
    \    for (int i = 0; i < n; ++i)\n        for (int j = 0; j < n; ++j) std::cin\
    \ >> a[i][j];\n    std::cout << det(a, mod) << '\\n';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <vector>\n\nint det(std::vector<std::vector<int>>\
    \ a, int mod) {\n    assert(mod > 1);\n    const int n = a.size();\n    int det\
    \     = 1;\n    for (int i = 0; i < n; ++i) {\n        int pivot = i;\n      \
    \  for (; pivot < n; ++pivot)\n            if (a[pivot][i] != 0) break;\n    \
    \    if (pivot == n) return 0;\n        if (pivot != i) {\n            a[pivot].swap(a[i]);\n\
    \            det = mod - det;\n        }\n        for (int j = i + 1; j < n; ++j)\
    \ {\n            int aii = a[i][i], aji = a[j][i];\n            if (aji == 0)\
    \ continue;\n            // `a0` * `a[i][i]` + `a1` * `a[j][i]`     (1)\n    \
    \        // `b0` * `a[i][i]` + `b1` * `a[j][i]`     (2)\n            // Use Euclidean\
    \ algorithm to compute `a0, a1, b0, b1` s.t. (1) = 0 or (2) = 0\n            int\
    \ a0 = 1, a1 = 0, b0 = 0, b1 = 1;\n            while (aii != 0 && aji != 0) {\n\
    \                if (aii < aji) {\n                    const int q = aji / aii;\n\
    \                    aji -= aii * q, b0 -= a0 * q, b1 -= a1 * q;\n           \
    \     } else {\n                    const int q = aii / aji;\n               \
    \     aii -= aji * q, a0 -= b0 * q, a1 -= b1 * q;\n                }\n       \
    \     }\n            if (a0 < mod) a0 += mod;\n            if (a1 < mod) a1 +=\
    \ mod;\n            if (b0 < mod) b0 += mod;\n            if (b1 < mod) b1 +=\
    \ mod;\n            for (int k = i; k < n; ++k) {\n                const long\
    \ long aik = a[i][k], ajk = a[j][k];\n                a[i][k] = (aik * a0 + ajk\
    \ * a1) % mod;\n                a[j][k] = (aik * b0 + ajk * b1) % mod;\n     \
    \       }\n            if (aii == 0) {\n                a[i].swap(a[j]);\n   \
    \             det = mod - det;\n            }\n        }\n        if ((det = (long\
    \ long)det * a[i][i] % mod) == 0) return 0;\n    }\n    return det;\n}\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, mod;\n    std::cin >> n >> mod;\n    std::vector a(n, std::vector<int>(n));\n\
    \    for (int i = 0; i < n; ++i)\n        for (int j = 0; j < n; ++j) std::cin\
    \ >> a[i][j];\n    std::cout << det(a, mod) << '\\n';\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/matrix/matrix_det_arbitrary_mod.0.test.cpp
  requiredBy: []
  timestamp: '2025-03-06 22:08:12+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/matrix/matrix_det_arbitrary_mod.0.test.cpp
layout: document
redirect_from:
- /verify/test/matrix/matrix_det_arbitrary_mod.0.test.cpp
- /verify/test/matrix/matrix_det_arbitrary_mod.0.test.cpp.html
title: test/matrix/matrix_det_arbitrary_mod.0.test.cpp
---
