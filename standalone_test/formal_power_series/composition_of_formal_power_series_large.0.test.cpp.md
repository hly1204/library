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
    \ {root, inv_root};\n}\n\nnamespace detail {\ntemplate<int N> void ButterflyRecPrime(uint[],\
    \ const uint[], int);\ntemplate<> void ButterflyRecPrime<1>(uint[], const uint[],\
    \ int) {}\ntemplate<int N> void ButterflyRecPrime(uint a[], const uint root[],\
    \ int lv) {\n    for (int i = 0; i < N / 2; ++i) {\n        const uint u = a[i];\n\
    \        a[i + N / 2] = (ull)a[i + N / 2] * root[lv] % MOD;\n        if ((a[i]\
    \ += a[i + N / 2]) >= MOD) a[i] -= MOD;\n        if ((a[i + N / 2] = u + MOD -\
    \ a[i + N / 2]) >= MOD) a[i + N / 2] -= MOD;\n    }\n    ButterflyRecPrime<N /\
    \ 2>(a, root, lv * 2);\n    ButterflyRecPrime<N / 2>(a + N / 2, root, lv * 2 +\
    \ 1);\n}\ntemplate<int N> void ButterflyRec(uint[], const uint[]);\ntemplate<>\
    \ void ButterflyRec<1>(uint[], const uint[]) {}\ntemplate<int N> void ButterflyRec(uint\
    \ a[], const uint root[]) {\n    for (int i = 0; i < N / 2; ++i) {\n        const\
    \ uint u = a[i];\n        if ((a[i] += a[i + N / 2]) >= MOD) a[i] -= MOD;\n  \
    \      if ((a[i + N / 2] = u + MOD - a[i + N / 2]) >= MOD) a[i + N / 2] -= MOD;\n\
    \    }\n    ButterflyRec<N / 2>(a, root);\n    ButterflyRecPrime<N / 2>(a + N\
    \ / 2, root, 1);\n}\ntemplate<int N> void InvButterflyRecPrime(uint[], const uint[],\
    \ int);\ntemplate<> void InvButterflyRecPrime<1>(uint[], const uint[], int) {}\n\
    template<int N> void InvButterflyRecPrime(uint a[], const uint root[], int lv)\
    \ {\n    InvButterflyRecPrime<N / 2>(a, root, lv * 2);\n    InvButterflyRecPrime<N\
    \ / 2>(a + N / 2, root, lv * 2 + 1);\n    for (int i = 0; i < N / 2; ++i) {\n\
    \        const uint u = a[i];\n        if ((a[i] += a[i + N / 2]) >= MOD) a[i]\
    \ -= MOD;\n        a[i + N / 2] = (ull)(u + MOD - a[i + N / 2]) * root[lv] % MOD;\n\
    \    }\n}\ntemplate<int N> void InvButterflyRec(uint[], const uint[]);\ntemplate<>\
    \ void InvButterflyRec<1>(uint[], const uint[]) {}\ntemplate<int N> void InvButterflyRec(uint\
    \ a[], const uint root[]) {\n    InvButterflyRec<N / 2>(a, root);\n    InvButterflyRecPrime<N\
    \ / 2>(a + N / 2, root, 1);\n    for (int i = 0; i < N / 2; ++i) {\n        const\
    \ uint u = a[i];\n        if ((a[i] += a[i + N / 2]) >= MOD) a[i] -= MOD;\n  \
    \      if ((a[i + N / 2] = u + MOD - a[i + N / 2]) >= MOD) a[i + N / 2] -= MOD;\n\
    \    }\n}\n// clang-format off\ntemplate<int... Is>\nvoid ButterflyHelper(uint\
    \ a[], int n, const uint root[], std::integer_sequence<int, Is...>)\n{ ([&] {\
    \ if (n == (1 << Is)) ButterflyRec<(1 << Is)>(a, root); }(), ...); }\ntemplate<int...\
    \ Is>\nvoid InvButterflyHelper(uint a[], int n, const uint root[], std::integer_sequence<int,\
    \ Is...>)\n{ ([&] { if (n == (1 << Is)) InvButterflyRec<(1 << Is)>(a, root); }(),\
    \ ...); }\n// clang-format on\n} // namespace detail\n\nvoid Butterfly(uint a[],\
    \ int n, const uint root[]) {\n    detail::ButterflyHelper(a, n, root, std::make_integer_sequence<int,\
    \ LOG2_ORD + 1>{});\n}\nvoid InvButterfly(uint a[], int n, const uint root[])\
    \ {\n    detail::InvButterflyHelper(a, n, root, std::make_integer_sequence<int,\
    \ LOG2_ORD + 1>{});\n}\n\nint GetFFTSize(int n) {\n    int len = 1;\n    while\
    \ (len < n) len *= 2;\n    return len;\n}\n\nvoid FFT(uint a[], int n, const uint\
    \ root[]) { Butterfly(a, n, root); }\n\nvoid InvFFT(uint a[], int n, const uint\
    \ root[]) {\n    InvButterfly(a, n, root);\n    const uint invn = InvMod(n);\n\
    \    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invn % MOD;\n}\n\nstd::vector<uint>\
    \ FPSComp(std::vector<uint> f, std::vector<uint> g, int n) {\n    assert(empty(g)\
    \ || g[0] == 0);\n    const int N = GetFFTSize(n);\n    std::vector<uint> root,\
    \ inv_root;\n    tie(root, inv_root) = GetFFTRoot(N * 4);\n    // [y^(-1)] (f(y)\
    \ / (-g(x) + y)) mod x^n in R[x]((y^(-1)))\n    const auto KinoshitaLi = [&root\
    \ = as_const(root), &inv_root = as_const(inv_root)](\n                       \
    \          auto &&KinoshitaLi, std::vector<uint> &P, std::vector<uint> Q,\n  \
    \                               int d, int n) {\n        assert((int)size(P) ==\
    \ d * n * 2);\n        assert((int)size(Q) == d * n * 2);\n        if (n == 1)\
    \ return;\n        Q.resize(d * n * 4);\n        Q[d * n * 2] = 1;\n        FFT(data(Q),\
    \ d * n * 4, data(root));\n        if (n > 2) {\n            std::vector<uint>\
    \ V(d * n * 2);\n            for (int i = 0; i < d * n * 4; i += 2) V[i / 2] =\
    \ (ull)Q[i] * Q[i + 1] % MOD;\n            InvFFT(data(V), d * n * 2, data(inv_root));\n\
    \            assert(V[0] == 1);\n            V[0] = 0;\n            for (int i\
    \ = 0; i < d * 2; ++i)\n                std::memset(data(V) + i * n + n / 2, 0,\
    \ sizeof(uint) * (n / 2));\n            KinoshitaLi(KinoshitaLi, P, std::move(V),\
    \ d * 2, n / 2);\n        }\n        FFT(data(P), d * n * 2, data(root));\n  \
    \      for (int i = 0; i < d * n * 4; i += 2) {\n            const uint u = Q[i];\n\
    \            Q[i]         = (ull)P[i / 2] * Q[i + 1] % MOD;\n            Q[i +\
    \ 1]     = (ull)P[i / 2] * u % MOD;\n        }\n        InvFFT(data(Q), d * n\
    \ * 4, data(inv_root));\n        for (int i = 0; i < d; ++i) {\n            uint\
    \ *const u = data(P) + i * n * 2;\n            std::memcpy(u, data(Q) + (i + d)\
    \ * (n * 2), sizeof(uint) * n);\n            std::memset(u + n, 0, sizeof(uint)\
    \ * n);\n        }\n    };\n    f.resize(N * 2);\n    g.resize(N * 2);\n    for\
    \ (int i = N - 1; i >= 0; --i) f[i * 2] = f[i], f[i * 2 + 1] = 0;\n    for (int\
    \ i = 0; i < N; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);\n    std::memset(data(g)\
    \ + N, 0, sizeof(uint) * N);\n    KinoshitaLi(KinoshitaLi, f, std::move(g), 1,\
    \ N);\n    f.resize(n);\n    return f;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<uint>\
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
    \ {root, inv_root};\n}\n\nnamespace detail {\ntemplate<int N> void ButterflyRecPrime(uint[],\
    \ const uint[], int);\ntemplate<> void ButterflyRecPrime<1>(uint[], const uint[],\
    \ int) {}\ntemplate<int N> void ButterflyRecPrime(uint a[], const uint root[],\
    \ int lv) {\n    for (int i = 0; i < N / 2; ++i) {\n        const uint u = a[i];\n\
    \        a[i + N / 2] = (ull)a[i + N / 2] * root[lv] % MOD;\n        if ((a[i]\
    \ += a[i + N / 2]) >= MOD) a[i] -= MOD;\n        if ((a[i + N / 2] = u + MOD -\
    \ a[i + N / 2]) >= MOD) a[i + N / 2] -= MOD;\n    }\n    ButterflyRecPrime<N /\
    \ 2>(a, root, lv * 2);\n    ButterflyRecPrime<N / 2>(a + N / 2, root, lv * 2 +\
    \ 1);\n}\ntemplate<int N> void ButterflyRec(uint[], const uint[]);\ntemplate<>\
    \ void ButterflyRec<1>(uint[], const uint[]) {}\ntemplate<int N> void ButterflyRec(uint\
    \ a[], const uint root[]) {\n    for (int i = 0; i < N / 2; ++i) {\n        const\
    \ uint u = a[i];\n        if ((a[i] += a[i + N / 2]) >= MOD) a[i] -= MOD;\n  \
    \      if ((a[i + N / 2] = u + MOD - a[i + N / 2]) >= MOD) a[i + N / 2] -= MOD;\n\
    \    }\n    ButterflyRec<N / 2>(a, root);\n    ButterflyRecPrime<N / 2>(a + N\
    \ / 2, root, 1);\n}\ntemplate<int N> void InvButterflyRecPrime(uint[], const uint[],\
    \ int);\ntemplate<> void InvButterflyRecPrime<1>(uint[], const uint[], int) {}\n\
    template<int N> void InvButterflyRecPrime(uint a[], const uint root[], int lv)\
    \ {\n    InvButterflyRecPrime<N / 2>(a, root, lv * 2);\n    InvButterflyRecPrime<N\
    \ / 2>(a + N / 2, root, lv * 2 + 1);\n    for (int i = 0; i < N / 2; ++i) {\n\
    \        const uint u = a[i];\n        if ((a[i] += a[i + N / 2]) >= MOD) a[i]\
    \ -= MOD;\n        a[i + N / 2] = (ull)(u + MOD - a[i + N / 2]) * root[lv] % MOD;\n\
    \    }\n}\ntemplate<int N> void InvButterflyRec(uint[], const uint[]);\ntemplate<>\
    \ void InvButterflyRec<1>(uint[], const uint[]) {}\ntemplate<int N> void InvButterflyRec(uint\
    \ a[], const uint root[]) {\n    InvButterflyRec<N / 2>(a, root);\n    InvButterflyRecPrime<N\
    \ / 2>(a + N / 2, root, 1);\n    for (int i = 0; i < N / 2; ++i) {\n        const\
    \ uint u = a[i];\n        if ((a[i] += a[i + N / 2]) >= MOD) a[i] -= MOD;\n  \
    \      if ((a[i + N / 2] = u + MOD - a[i + N / 2]) >= MOD) a[i + N / 2] -= MOD;\n\
    \    }\n}\n// clang-format off\ntemplate<int... Is>\nvoid ButterflyHelper(uint\
    \ a[], int n, const uint root[], std::integer_sequence<int, Is...>)\n{ ([&] {\
    \ if (n == (1 << Is)) ButterflyRec<(1 << Is)>(a, root); }(), ...); }\ntemplate<int...\
    \ Is>\nvoid InvButterflyHelper(uint a[], int n, const uint root[], std::integer_sequence<int,\
    \ Is...>)\n{ ([&] { if (n == (1 << Is)) InvButterflyRec<(1 << Is)>(a, root); }(),\
    \ ...); }\n// clang-format on\n} // namespace detail\n\nvoid Butterfly(uint a[],\
    \ int n, const uint root[]) {\n    detail::ButterflyHelper(a, n, root, std::make_integer_sequence<int,\
    \ LOG2_ORD + 1>{});\n}\nvoid InvButterfly(uint a[], int n, const uint root[])\
    \ {\n    detail::InvButterflyHelper(a, n, root, std::make_integer_sequence<int,\
    \ LOG2_ORD + 1>{});\n}\n\nint GetFFTSize(int n) {\n    int len = 1;\n    while\
    \ (len < n) len *= 2;\n    return len;\n}\n\nvoid FFT(uint a[], int n, const uint\
    \ root[]) { Butterfly(a, n, root); }\n\nvoid InvFFT(uint a[], int n, const uint\
    \ root[]) {\n    InvButterfly(a, n, root);\n    const uint invn = InvMod(n);\n\
    \    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invn % MOD;\n}\n\nstd::vector<uint>\
    \ FPSComp(std::vector<uint> f, std::vector<uint> g, int n) {\n    assert(empty(g)\
    \ || g[0] == 0);\n    const int N = GetFFTSize(n);\n    std::vector<uint> root,\
    \ inv_root;\n    tie(root, inv_root) = GetFFTRoot(N * 4);\n    // [y^(-1)] (f(y)\
    \ / (-g(x) + y)) mod x^n in R[x]((y^(-1)))\n    const auto KinoshitaLi = [&root\
    \ = as_const(root), &inv_root = as_const(inv_root)](\n                       \
    \          auto &&KinoshitaLi, std::vector<uint> &P, std::vector<uint> Q,\n  \
    \                               int d, int n) {\n        assert((int)size(P) ==\
    \ d * n * 2);\n        assert((int)size(Q) == d * n * 2);\n        if (n == 1)\
    \ return;\n        Q.resize(d * n * 4);\n        Q[d * n * 2] = 1;\n        FFT(data(Q),\
    \ d * n * 4, data(root));\n        if (n > 2) {\n            std::vector<uint>\
    \ V(d * n * 2);\n            for (int i = 0; i < d * n * 4; i += 2) V[i / 2] =\
    \ (ull)Q[i] * Q[i + 1] % MOD;\n            InvFFT(data(V), d * n * 2, data(inv_root));\n\
    \            assert(V[0] == 1);\n            V[0] = 0;\n            for (int i\
    \ = 0; i < d * 2; ++i)\n                std::memset(data(V) + i * n + n / 2, 0,\
    \ sizeof(uint) * (n / 2));\n            KinoshitaLi(KinoshitaLi, P, std::move(V),\
    \ d * 2, n / 2);\n        }\n        FFT(data(P), d * n * 2, data(root));\n  \
    \      for (int i = 0; i < d * n * 4; i += 2) {\n            const uint u = Q[i];\n\
    \            Q[i]         = (ull)P[i / 2] * Q[i + 1] % MOD;\n            Q[i +\
    \ 1]     = (ull)P[i / 2] * u % MOD;\n        }\n        InvFFT(data(Q), d * n\
    \ * 4, data(inv_root));\n        for (int i = 0; i < d; ++i) {\n            uint\
    \ *const u = data(P) + i * n * 2;\n            std::memcpy(u, data(Q) + (i + d)\
    \ * (n * 2), sizeof(uint) * n);\n            std::memset(u + n, 0, sizeof(uint)\
    \ * n);\n        }\n    };\n    f.resize(N * 2);\n    g.resize(N * 2);\n    for\
    \ (int i = N - 1; i >= 0; --i) f[i * 2] = f[i], f[i * 2 + 1] = 0;\n    for (int\
    \ i = 0; i < N; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);\n    std::memset(data(g)\
    \ + N, 0, sizeof(uint) * N);\n    KinoshitaLi(KinoshitaLi, f, std::move(g), 1,\
    \ N);\n    f.resize(n);\n    return f;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n;\n    std::cin >> n;\n    std::vector<uint>\
    \ f(n), g(n);\n    for (int i = 0; i < n; ++i) std::cin >> f[i];\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> g[i];\n    const auto fg = FPSComp(f, g, n);\n\
    \    for (int i = 0; i < n; ++i) std::cout << fg[i] << ' ';\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
  requiredBy: []
  timestamp: '2025-08-18 20:32:34+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
layout: document
redirect_from:
- /verify/standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
- /verify/standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp.html
title: standalone_test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
---
