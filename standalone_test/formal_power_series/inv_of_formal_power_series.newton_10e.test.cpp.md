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
    PROBLEM: https://judge.yosupo.jp/problem/inv_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/inv_of_formal_power_series
  bundledCode: "#line 1 \"standalone_test/formal_power_series/inv_of_formal_power_series.newton_10e.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n\n#include <cassert>\n#include <cstring>\n#include <iostream>\n#include <utility>\n\
    #include <vector>\n\nusing uint         = unsigned;\nusing ull          = unsigned\
    \ long long;\nconstexpr uint MOD = 998244353;\n\nconstexpr uint PowMod(uint a,\
    \ ull e) {\n    for (uint res = 1;; a = (ull)a * a % MOD) {\n        if (e & 1)\
    \ res = (ull)res * a % MOD;\n        if ((e /= 2) == 0) return res;\n    }\n}\n\
    \nconstexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }\n\nconstexpr uint\
    \ QUAD_NONRESIDUE = 3;\nconstexpr int LOG2_ORD         = __builtin_ctz(MOD - 1);\n\
    constexpr uint ZETA            = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);\n\
    constexpr uint INV_ZETA        = InvMod(ZETA);\n\nstd::pair<std::vector<uint>,\
    \ std::vector<uint>> GetFFTRoot(int n) {\n    assert((n & (n - 1)) == 0);\n  \
    \  if (n / 2 == 0) return {};\n    std::vector<uint> root(n / 2), inv_root(n /\
    \ 2);\n    root[0] = inv_root[0] = 1;\n    for (int i = 0; (1 << i) < n / 2; ++i)\n\
    \        root[1 << i]               = PowMod(ZETA, 1LL << (LOG2_ORD - i - 2)),\n\
    \                  inv_root[1 << i] = PowMod(INV_ZETA, 1LL << (LOG2_ORD - i -\
    \ 2));\n    for (int i = 1; i < n / 2; ++i)\n        root[i]     = (ull)root[i\
    \ - (i & (i - 1))] * root[i & (i - 1)] % MOD,\n        inv_root[i] = (ull)inv_root[i\
    \ - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;\n    return {root, inv_root};\n\
    }\n\nnamespace detail {\ntemplate<int N> void ButterflyRecPrime(uint[], const\
    \ uint[], int);\ntemplate<> void ButterflyRecPrime<1>(uint[], const uint[], int)\
    \ {}\ntemplate<int N> void ButterflyRecPrime(uint a[], const uint root[], int\
    \ lv) {\n    for (int i = 0; i < N / 2; ++i) {\n        const uint u = a[i];\n\
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
    \ root[]) {\n    InvButterfly(a, n, root);\n    const uint invN = InvMod(n);\n\
    \    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invN % MOD;\n}\n\nstd::vector<uint>\
    \ FPSInv(const std::vector<uint> &a, int n) {\n    assert(!empty(a) && a[0] !=\
    \ 0);\n    assert(n >= 0);\n    if (n == 0) return {};\n    const int N      \
    \           = GetFFTSize(n);\n    const auto [root, inv_root] = GetFFTRoot(N);\n\
    \    std::vector<uint> invA(N), shopA(N), shopB(N);\n    invA[0] = InvMod(a[0]);\n\
    \    for (int i = 2; i <= N; i *= 2) {\n        std::memcpy(data(shopA), data(a),\
    \ sizeof(uint) * std::min((int)size(a), i));\n        if ((int)size(a) < i)\n\
    \            std::memset(data(shopA) + (int)size(a), 0, sizeof(uint) * (i - (int)size(a)));\n\
    \        std::memcpy(data(shopB), data(invA), sizeof(uint) * i);\n        FFT(data(shopA),\
    \ i, data(root));\n        FFT(data(shopB), i, data(root));\n        for (int\
    \ j = 0; j < i; ++j) shopA[j] = (ull)shopA[j] * shopB[j] % MOD;\n        InvFFT(data(shopA),\
    \ i, data(inv_root));\n        std::memset(data(shopA), 0, sizeof(uint) * (i /\
    \ 2));\n        FFT(data(shopA), i, data(root));\n        for (int j = 0; j <\
    \ i; ++j) shopA[j] = (ull)shopA[j] * shopB[j] % MOD;\n        InvFFT(data(shopA),\
    \ i, data(inv_root));\n        for (int j = i / 2; j < i; ++j) invA[j] = shopA[j]\
    \ != 0 ? MOD - shopA[j] : shopA[j];\n    }\n    invA.resize(n);\n    return invA;\n\
    }\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n;\n    std::cin >> n;\n    std::vector<uint> a(n);\n    for (int i =\
    \ 0; i < n; ++i) std::cin >> a[i];\n    const auto invA = FPSInv(a, n);\n    for\
    \ (int i = 0; i < n; ++i) std::cout << invA[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n\n#include <cassert>\n#include <cstring>\n#include <iostream>\n#include <utility>\n\
    #include <vector>\n\nusing uint         = unsigned;\nusing ull          = unsigned\
    \ long long;\nconstexpr uint MOD = 998244353;\n\nconstexpr uint PowMod(uint a,\
    \ ull e) {\n    for (uint res = 1;; a = (ull)a * a % MOD) {\n        if (e & 1)\
    \ res = (ull)res * a % MOD;\n        if ((e /= 2) == 0) return res;\n    }\n}\n\
    \nconstexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }\n\nconstexpr uint\
    \ QUAD_NONRESIDUE = 3;\nconstexpr int LOG2_ORD         = __builtin_ctz(MOD - 1);\n\
    constexpr uint ZETA            = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);\n\
    constexpr uint INV_ZETA        = InvMod(ZETA);\n\nstd::pair<std::vector<uint>,\
    \ std::vector<uint>> GetFFTRoot(int n) {\n    assert((n & (n - 1)) == 0);\n  \
    \  if (n / 2 == 0) return {};\n    std::vector<uint> root(n / 2), inv_root(n /\
    \ 2);\n    root[0] = inv_root[0] = 1;\n    for (int i = 0; (1 << i) < n / 2; ++i)\n\
    \        root[1 << i]               = PowMod(ZETA, 1LL << (LOG2_ORD - i - 2)),\n\
    \                  inv_root[1 << i] = PowMod(INV_ZETA, 1LL << (LOG2_ORD - i -\
    \ 2));\n    for (int i = 1; i < n / 2; ++i)\n        root[i]     = (ull)root[i\
    \ - (i & (i - 1))] * root[i & (i - 1)] % MOD,\n        inv_root[i] = (ull)inv_root[i\
    \ - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;\n    return {root, inv_root};\n\
    }\n\nnamespace detail {\ntemplate<int N> void ButterflyRecPrime(uint[], const\
    \ uint[], int);\ntemplate<> void ButterflyRecPrime<1>(uint[], const uint[], int)\
    \ {}\ntemplate<int N> void ButterflyRecPrime(uint a[], const uint root[], int\
    \ lv) {\n    for (int i = 0; i < N / 2; ++i) {\n        const uint u = a[i];\n\
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
    \ root[]) {\n    InvButterfly(a, n, root);\n    const uint invN = InvMod(n);\n\
    \    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invN % MOD;\n}\n\nstd::vector<uint>\
    \ FPSInv(const std::vector<uint> &a, int n) {\n    assert(!empty(a) && a[0] !=\
    \ 0);\n    assert(n >= 0);\n    if (n == 0) return {};\n    const int N      \
    \           = GetFFTSize(n);\n    const auto [root, inv_root] = GetFFTRoot(N);\n\
    \    std::vector<uint> invA(N), shopA(N), shopB(N);\n    invA[0] = InvMod(a[0]);\n\
    \    for (int i = 2; i <= N; i *= 2) {\n        std::memcpy(data(shopA), data(a),\
    \ sizeof(uint) * std::min((int)size(a), i));\n        if ((int)size(a) < i)\n\
    \            std::memset(data(shopA) + (int)size(a), 0, sizeof(uint) * (i - (int)size(a)));\n\
    \        std::memcpy(data(shopB), data(invA), sizeof(uint) * i);\n        FFT(data(shopA),\
    \ i, data(root));\n        FFT(data(shopB), i, data(root));\n        for (int\
    \ j = 0; j < i; ++j) shopA[j] = (ull)shopA[j] * shopB[j] % MOD;\n        InvFFT(data(shopA),\
    \ i, data(inv_root));\n        std::memset(data(shopA), 0, sizeof(uint) * (i /\
    \ 2));\n        FFT(data(shopA), i, data(root));\n        for (int j = 0; j <\
    \ i; ++j) shopA[j] = (ull)shopA[j] * shopB[j] % MOD;\n        InvFFT(data(shopA),\
    \ i, data(inv_root));\n        for (int j = i / 2; j < i; ++j) invA[j] = shopA[j]\
    \ != 0 ? MOD - shopA[j] : shopA[j];\n    }\n    invA.resize(n);\n    return invA;\n\
    }\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n;\n    std::cin >> n;\n    std::vector<uint> a(n);\n    for (int i =\
    \ 0; i < n; ++i) std::cin >> a[i];\n    const auto invA = FPSInv(a, n);\n    for\
    \ (int i = 0; i < n; ++i) std::cout << invA[i] << ' ';\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: standalone_test/formal_power_series/inv_of_formal_power_series.newton_10e.test.cpp
  requiredBy: []
  timestamp: '2025-11-29 22:45:00+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: standalone_test/formal_power_series/inv_of_formal_power_series.newton_10e.test.cpp
layout: document
redirect_from:
- /verify/standalone_test/formal_power_series/inv_of_formal_power_series.newton_10e.test.cpp
- /verify/standalone_test/formal_power_series/inv_of_formal_power_series.newton_10e.test.cpp.html
title: standalone_test/formal_power_series/inv_of_formal_power_series.newton_10e.test.cpp
---
