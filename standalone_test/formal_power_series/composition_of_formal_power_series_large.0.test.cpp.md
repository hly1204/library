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
    PROBLEM: https://judge.yosupo.jp/problem/composition_of_formal_power_series_large
    links:
    - https://judge.yosupo.jp/problem/composition_of_formal_power_series_large
  bundledCode: "#line 1 \"standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/composition_of_formal_power_series_large\"\
    \n\n#include <cassert>\n#include <cstring>\n#include <iostream>\n#include <tuple>\n\
    #include <utility>\n#include <vector>\n\nusing uint         = unsigned;\nusing\
    \ ull          = unsigned long long;\nconstexpr uint MOD = 998244353;\n\nconstexpr\
    \ uint PowMod(uint a, ull e) {\n    for (uint res = 1;; a = (ull)a * a % MOD)\
    \ {\n        if (e & 1) res = (ull)res * a % MOD;\n        if ((e /= 2) == 0)\
    \ return res;\n    }\n}\n\nconstexpr uint InvMod(uint a) { return PowMod(a, MOD\
    \ - 2); }\n\nconstexpr uint QUAD_NONRESIDUE = 3;\nconstexpr int LOG2_ORD     \
    \    = __builtin_ctz(MOD - 1);\nconstexpr uint ZETA            = PowMod(QUAD_NONRESIDUE,\
    \ (MOD - 1) >> LOG2_ORD);\nconstexpr uint INV_ZETA        = InvMod(ZETA);\n\n\
    std::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int n) {\n    assert((n\
    \ & (n - 1)) == 0);\n    if (n / 2 == 0) return {};\n    std::vector<uint> root(n\
    \ / 2), inv_root(n / 2);\n    root[0] = inv_root[0] = 1;\n    for (int i = 0;\
    \ (1 << i) < n / 2; ++i)\n        root[1 << i]               = PowMod(ZETA, 1LL\
    \ << (LOG2_ORD - i - 2)),\n                  inv_root[1 << i] = PowMod(INV_ZETA,\
    \ 1LL << (LOG2_ORD - i - 2));\n    for (int i = 1; i < n / 2; ++i)\n        root[i]\
    \     = (ull)root[i - (i & (i - 1))] * root[i & (i - 1)] % MOD,\n        inv_root[i]\
    \ = (ull)inv_root[i - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;\n    return\
    \ {root, inv_root};\n}\n\nvoid Butterfly(uint a[], int n, const uint root[]) {\n\
    \    for (int i = n; i >= 2; i /= 2) {\n        for (int k = 0; k < i / 2; ++k)\
    \ {\n            const uint u = a[k];\n            if ((a[k] += a[k + i / 2])\
    \ >= MOD) a[k] -= MOD;\n            if ((a[k + i / 2] = u + MOD - a[k + i / 2])\
    \ >= MOD) a[k + i / 2] -= MOD;\n        }\n        for (int j = i, m = 1; j <\
    \ n; j += i, ++m)\n            for (int k = j; k < j + i / 2; ++k) {\n       \
    \         const uint u = a[k];\n                a[k + i / 2] = (ull)a[k + i /\
    \ 2] * root[m] % MOD;\n                if ((a[k] += a[k + i / 2]) >= MOD) a[k]\
    \ -= MOD;\n                if ((a[k + i / 2] = u + MOD - a[k + i / 2]) >= MOD)\
    \ a[k + i / 2] -= MOD;\n            }\n    }\n}\n\nvoid InvButterfly(uint a[],\
    \ int n, const uint root[]) {\n    for (int i = 2; i <= n; i *= 2) {\n       \
    \ for (int k = 0; k < i / 2; ++k) {\n            const uint u = a[k];\n      \
    \      if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;\n            if ((a[k +\
    \ i / 2] = u + MOD - a[k + i / 2]) >= MOD) a[k + i / 2] -= MOD;\n        }\n \
    \       for (int j = i, m = 1; j < n; j += i, ++m)\n            for (int k = j;\
    \ k < j + i / 2; ++k) {\n                const uint u = a[k];\n              \
    \  if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;\n                a[k + i /\
    \ 2] = (ull)(u + MOD - a[k + i / 2]) * root[m] % MOD;\n            }\n    }\n\
    }\n\nint GetFFTSize(int n) {\n    int len = 1;\n    while (len < n) len *= 2;\n\
    \    return len;\n}\n\nvoid FFT(uint a[], int n, const uint root[]) { Butterfly(a,\
    \ n, root); }\n\nvoid InvFFT(uint a[], int n, const uint root[]) {\n    InvButterfly(a,\
    \ n, root);\n    const uint invn = InvMod(n);\n    for (int i = 0; i < n; ++i)\
    \ a[i] = (ull)a[i] * invn % MOD;\n}\n\nstd::vector<uint> FPSComp(std::vector<uint>\
    \ f, std::vector<uint> g, int n) {\n    assert(empty(g) || g[0] == 0);\n    const\
    \ int N = GetFFTSize(n);\n    std::vector<uint> root, inv_root;\n    tie(root,\
    \ inv_root) = GetFFTRoot(N * 4);\n    // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n\
    \ in R[x]((y^(-1)))\n    const auto KinoshitaLi = [&root = as_const(root), &inv_root\
    \ = as_const(inv_root)](\n                                 auto &&KinoshitaLi,\
    \ std::vector<uint> &P, std::vector<uint> Q,\n                               \
    \  int d, int n) {\n        assert((int)size(P) == d * n * 2);\n        assert((int)size(Q)\
    \ == d * n * 2);\n        if (n == 1) return;\n        Q.resize(d * n * 4);\n\
    \        Q[d * n * 2] = 1;\n        FFT(data(Q), d * n * 4, data(root));\n   \
    \     if (n > 2) {\n            std::vector<uint> V(d * n * 2);\n            for\
    \ (int i = 0; i < d * n * 4; i += 2) V[i / 2] = (ull)Q[i] * Q[i + 1] % MOD;\n\
    \            InvFFT(data(V), d * n * 2, data(inv_root));\n            assert(V[0]\
    \ == 1);\n            V[0] = 0;\n            for (int i = 0; i < d * 2; ++i)\n\
    \                std::memset(data(V) + i * n + n / 2, 0, sizeof(uint) * (n / 2));\n\
    \            KinoshitaLi(KinoshitaLi, P, std::move(V), d * 2, n / 2);\n      \
    \  }\n        FFT(data(P), d * n * 2, data(root));\n        for (int i = 0; i\
    \ < d * n * 4; i += 2) {\n            const uint u = Q[i];\n            Q[i] \
    \        = (ull)P[i / 2] * Q[i + 1] % MOD;\n            Q[i + 1]     = (ull)P[i\
    \ / 2] * u % MOD;\n        }\n        InvFFT(data(Q), d * n * 4, data(inv_root));\n\
    \        for (int i = 0; i < d; ++i) {\n            uint *const u = data(P) +\
    \ i * n * 2;\n            std::memcpy(u, data(Q) + (i + d) * (n * 2), sizeof(uint)\
    \ * n);\n            std::memset(u + n, 0, sizeof(uint) * n);\n        }\n   \
    \ };\n    f.resize(N * 2);\n    g.resize(N * 2);\n    for (int i = N - 1; i >=\
    \ 0; --i) f[i * 2] = f[i], f[i * 2 + 1] = 0;\n    for (int i = 0; i < N; ++i)\
    \ g[i] = (g[i] != 0 ? MOD - g[i] : 0);\n    std::memset(data(g) + N, 0, sizeof(uint)\
    \ * N);\n    KinoshitaLi(KinoshitaLi, f, std::move(g), 1, N);\n    f.resize(n);\n\
    \    return f;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<uint>\
    \ f(n), g(n);\n    for (int i = 0; i < n; ++i) std::cin >> f[i];\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> g[i];\n    const auto fg = FPSComp(f, g, n);\n\
    \    for (int i = 0; i < n; ++i) std::cout << fg[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/composition_of_formal_power_series_large\"\
    \n\n#include <cassert>\n#include <cstring>\n#include <iostream>\n#include <tuple>\n\
    #include <utility>\n#include <vector>\n\nusing uint         = unsigned;\nusing\
    \ ull          = unsigned long long;\nconstexpr uint MOD = 998244353;\n\nconstexpr\
    \ uint PowMod(uint a, ull e) {\n    for (uint res = 1;; a = (ull)a * a % MOD)\
    \ {\n        if (e & 1) res = (ull)res * a % MOD;\n        if ((e /= 2) == 0)\
    \ return res;\n    }\n}\n\nconstexpr uint InvMod(uint a) { return PowMod(a, MOD\
    \ - 2); }\n\nconstexpr uint QUAD_NONRESIDUE = 3;\nconstexpr int LOG2_ORD     \
    \    = __builtin_ctz(MOD - 1);\nconstexpr uint ZETA            = PowMod(QUAD_NONRESIDUE,\
    \ (MOD - 1) >> LOG2_ORD);\nconstexpr uint INV_ZETA        = InvMod(ZETA);\n\n\
    std::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int n) {\n    assert((n\
    \ & (n - 1)) == 0);\n    if (n / 2 == 0) return {};\n    std::vector<uint> root(n\
    \ / 2), inv_root(n / 2);\n    root[0] = inv_root[0] = 1;\n    for (int i = 0;\
    \ (1 << i) < n / 2; ++i)\n        root[1 << i]               = PowMod(ZETA, 1LL\
    \ << (LOG2_ORD - i - 2)),\n                  inv_root[1 << i] = PowMod(INV_ZETA,\
    \ 1LL << (LOG2_ORD - i - 2));\n    for (int i = 1; i < n / 2; ++i)\n        root[i]\
    \     = (ull)root[i - (i & (i - 1))] * root[i & (i - 1)] % MOD,\n        inv_root[i]\
    \ = (ull)inv_root[i - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;\n    return\
    \ {root, inv_root};\n}\n\nvoid Butterfly(uint a[], int n, const uint root[]) {\n\
    \    for (int i = n; i >= 2; i /= 2) {\n        for (int k = 0; k < i / 2; ++k)\
    \ {\n            const uint u = a[k];\n            if ((a[k] += a[k + i / 2])\
    \ >= MOD) a[k] -= MOD;\n            if ((a[k + i / 2] = u + MOD - a[k + i / 2])\
    \ >= MOD) a[k + i / 2] -= MOD;\n        }\n        for (int j = i, m = 1; j <\
    \ n; j += i, ++m)\n            for (int k = j; k < j + i / 2; ++k) {\n       \
    \         const uint u = a[k];\n                a[k + i / 2] = (ull)a[k + i /\
    \ 2] * root[m] % MOD;\n                if ((a[k] += a[k + i / 2]) >= MOD) a[k]\
    \ -= MOD;\n                if ((a[k + i / 2] = u + MOD - a[k + i / 2]) >= MOD)\
    \ a[k + i / 2] -= MOD;\n            }\n    }\n}\n\nvoid InvButterfly(uint a[],\
    \ int n, const uint root[]) {\n    for (int i = 2; i <= n; i *= 2) {\n       \
    \ for (int k = 0; k < i / 2; ++k) {\n            const uint u = a[k];\n      \
    \      if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;\n            if ((a[k +\
    \ i / 2] = u + MOD - a[k + i / 2]) >= MOD) a[k + i / 2] -= MOD;\n        }\n \
    \       for (int j = i, m = 1; j < n; j += i, ++m)\n            for (int k = j;\
    \ k < j + i / 2; ++k) {\n                const uint u = a[k];\n              \
    \  if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;\n                a[k + i /\
    \ 2] = (ull)(u + MOD - a[k + i / 2]) * root[m] % MOD;\n            }\n    }\n\
    }\n\nint GetFFTSize(int n) {\n    int len = 1;\n    while (len < n) len *= 2;\n\
    \    return len;\n}\n\nvoid FFT(uint a[], int n, const uint root[]) { Butterfly(a,\
    \ n, root); }\n\nvoid InvFFT(uint a[], int n, const uint root[]) {\n    InvButterfly(a,\
    \ n, root);\n    const uint invn = InvMod(n);\n    for (int i = 0; i < n; ++i)\
    \ a[i] = (ull)a[i] * invn % MOD;\n}\n\nstd::vector<uint> FPSComp(std::vector<uint>\
    \ f, std::vector<uint> g, int n) {\n    assert(empty(g) || g[0] == 0);\n    const\
    \ int N = GetFFTSize(n);\n    std::vector<uint> root, inv_root;\n    tie(root,\
    \ inv_root) = GetFFTRoot(N * 4);\n    // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n\
    \ in R[x]((y^(-1)))\n    const auto KinoshitaLi = [&root = as_const(root), &inv_root\
    \ = as_const(inv_root)](\n                                 auto &&KinoshitaLi,\
    \ std::vector<uint> &P, std::vector<uint> Q,\n                               \
    \  int d, int n) {\n        assert((int)size(P) == d * n * 2);\n        assert((int)size(Q)\
    \ == d * n * 2);\n        if (n == 1) return;\n        Q.resize(d * n * 4);\n\
    \        Q[d * n * 2] = 1;\n        FFT(data(Q), d * n * 4, data(root));\n   \
    \     if (n > 2) {\n            std::vector<uint> V(d * n * 2);\n            for\
    \ (int i = 0; i < d * n * 4; i += 2) V[i / 2] = (ull)Q[i] * Q[i + 1] % MOD;\n\
    \            InvFFT(data(V), d * n * 2, data(inv_root));\n            assert(V[0]\
    \ == 1);\n            V[0] = 0;\n            for (int i = 0; i < d * 2; ++i)\n\
    \                std::memset(data(V) + i * n + n / 2, 0, sizeof(uint) * (n / 2));\n\
    \            KinoshitaLi(KinoshitaLi, P, std::move(V), d * 2, n / 2);\n      \
    \  }\n        FFT(data(P), d * n * 2, data(root));\n        for (int i = 0; i\
    \ < d * n * 4; i += 2) {\n            const uint u = Q[i];\n            Q[i] \
    \        = (ull)P[i / 2] * Q[i + 1] % MOD;\n            Q[i + 1]     = (ull)P[i\
    \ / 2] * u % MOD;\n        }\n        InvFFT(data(Q), d * n * 4, data(inv_root));\n\
    \        for (int i = 0; i < d; ++i) {\n            uint *const u = data(P) +\
    \ i * n * 2;\n            std::memcpy(u, data(Q) + (i + d) * (n * 2), sizeof(uint)\
    \ * n);\n            std::memset(u + n, 0, sizeof(uint) * n);\n        }\n   \
    \ };\n    f.resize(N * 2);\n    g.resize(N * 2);\n    for (int i = N - 1; i >=\
    \ 0; --i) f[i * 2] = f[i], f[i * 2 + 1] = 0;\n    for (int i = 0; i < N; ++i)\
    \ g[i] = (g[i] != 0 ? MOD - g[i] : 0);\n    std::memset(data(g) + N, 0, sizeof(uint)\
    \ * N);\n    KinoshitaLi(KinoshitaLi, f, std::move(g), 1, N);\n    f.resize(n);\n\
    \    return f;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<uint>\
    \ f(n), g(n);\n    for (int i = 0; i < n; ++i) std::cin >> f[i];\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> g[i];\n    const auto fg = FPSComp(f, g, n);\n\
    \    for (int i = 0; i < n; ++i) std::cout << fg[i] << ' ';\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
  requiredBy: []
  timestamp: '2025-08-17 18:42:55+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
layout: document
redirect_from:
- /verify/standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
- /verify/standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp.html
title: standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
---
