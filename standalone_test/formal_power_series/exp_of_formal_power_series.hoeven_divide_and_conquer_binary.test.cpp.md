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
    PROBLEM: https://judge.yosupo.jp/problem/exp_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/exp_of_formal_power_series
    - https://www.texmacs.org/joris/issac03/issac03.pdf
  bundledCode: "#line 1 \"standalone_test/formal_power_series/exp_of_formal_power_series.hoeven_divide_and_conquer_binary.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/exp_of_formal_power_series\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <type_traits>\n\
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
    \ root[]) {\n    InvButterfly(a, n, root);\n    const uint invN = InvMod(n);\n\
    \    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invN % MOD;\n}\n\n// see:\n\
    // [1]: Joris van der Hoeven. Relaxed multiplication using the middle product.\
    \ ISSAC 2003: 143-147\n//      https://www.texmacs.org/joris/issac03/issac03.pdf\n\
    template<typename Fn>\nstd::enable_if_t<std::is_invocable_r_v<uint, Fn, int, const\
    \ std::vector<uint> &>, std::vector<uint>>\nSemiRelaxedConv(const std::vector<uint>\
    \ &a, Fn g, int n) {\n    assert(n >= 0);\n    if (n == 0) return {};\n    enum\
    \ { Threshold = 32 };\n    assert((Threshold & (Threshold - 1)) == 0);\n    const\
    \ int N                 = GetFFTSize(n);\n    const auto [root, inv_root] = GetFFTRoot(N);\n\
    \    std::vector<std::vector<uint>> dftA;\n    for (int i = Threshold * 2; i <=\
    \ N; i *= 2) {\n        auto &&aa = dftA.emplace_back(i);\n        copy(begin(a),\
    \ min(begin(a) + i, end(a)), begin(aa));\n        FFT(data(aa), i, data(root));\n\
    \    }\n    std::vector<uint> b(n), ab(n);\n    b[0] = g(0, ab);\n    if (!empty(a))\
    \ ab[0] = (ull)a[0] * b[0] % MOD;\n    for (int i = 1; i < n; ++i) {\n       \
    \ if (i % Threshold == 0) {\n            const int lv = __builtin_ctz(i / Threshold);\n\
    \            const int NN = Threshold << (lv + 1);\n            std::vector<uint>\
    \ c(NN);\n            copy(begin(b) + i - NN / 2, begin(b) + i, begin(c));\n \
    \           FFT(data(c), NN, data(root));\n            for (int j = 0; j < NN;\
    \ ++j) c[j] = (ull)c[j] * dftA[lv][j] % MOD;\n            InvFFT(data(c), NN,\
    \ data(inv_root));\n            for (int j = 0; j < std::min(NN / 2, n - i); ++j)\n\
    \                if ((ab[i + j] += c[j + NN / 2]) >= MOD) ab[i + j] -= MOD;\n\
    \        }\n        for (int j = std::max(i - i % Threshold, i - (int)size(a)\
    \ + 1); j < i; ++j)\n            ab[i] = (ab[i] + (ull)a[i - j] * b[j]) % MOD;\n\
    \        b[i] = g(i, ab);\n        if (!empty(a)) ab[i] = (ab[i] + (ull)a[0] *\
    \ b[i]) % MOD;\n    }\n    return b;\n}\n\nstd::vector<uint> Deriv(const std::vector<uint>\
    \ &a) {\n    const int n = (int)size(a) - 1;\n    if (n <= 0) return {};\n   \
    \ std::vector<uint> res(n);\n    for (int i = 1; i <= n; ++i) res[i - 1] = (ull)a[i]\
    \ * i % MOD;\n    return res;\n}\n\nstd::vector<uint> FPSExp(const std::vector<uint>\
    \ &a, int n) {\n    const auto g = [](int n, const std::vector<uint> &c) -> uint\
    \ {\n        if (n == 0) return 1;\n        return (ull)c[n - 1] * InvMod(n) %\
    \ MOD;\n    };\n    return SemiRelaxedConv(Deriv(a), g, n);\n}\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int n;\n\
    \    std::cin >> n;\n    std::vector<uint> a(n);\n    for (int i = 0; i < n; ++i)\
    \ std::cin >> a[i];\n    const auto expA = FPSExp(a, n);\n    for (int i = 0;\
    \ i < n; ++i) std::cout << expA[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/exp_of_formal_power_series\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <type_traits>\n\
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
    \ root[]) {\n    InvButterfly(a, n, root);\n    const uint invN = InvMod(n);\n\
    \    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invN % MOD;\n}\n\n// see:\n\
    // [1]: Joris van der Hoeven. Relaxed multiplication using the middle product.\
    \ ISSAC 2003: 143-147\n//      https://www.texmacs.org/joris/issac03/issac03.pdf\n\
    template<typename Fn>\nstd::enable_if_t<std::is_invocable_r_v<uint, Fn, int, const\
    \ std::vector<uint> &>, std::vector<uint>>\nSemiRelaxedConv(const std::vector<uint>\
    \ &a, Fn g, int n) {\n    assert(n >= 0);\n    if (n == 0) return {};\n    enum\
    \ { Threshold = 32 };\n    assert((Threshold & (Threshold - 1)) == 0);\n    const\
    \ int N                 = GetFFTSize(n);\n    const auto [root, inv_root] = GetFFTRoot(N);\n\
    \    std::vector<std::vector<uint>> dftA;\n    for (int i = Threshold * 2; i <=\
    \ N; i *= 2) {\n        auto &&aa = dftA.emplace_back(i);\n        copy(begin(a),\
    \ min(begin(a) + i, end(a)), begin(aa));\n        FFT(data(aa), i, data(root));\n\
    \    }\n    std::vector<uint> b(n), ab(n);\n    b[0] = g(0, ab);\n    if (!empty(a))\
    \ ab[0] = (ull)a[0] * b[0] % MOD;\n    for (int i = 1; i < n; ++i) {\n       \
    \ if (i % Threshold == 0) {\n            const int lv = __builtin_ctz(i / Threshold);\n\
    \            const int NN = Threshold << (lv + 1);\n            std::vector<uint>\
    \ c(NN);\n            copy(begin(b) + i - NN / 2, begin(b) + i, begin(c));\n \
    \           FFT(data(c), NN, data(root));\n            for (int j = 0; j < NN;\
    \ ++j) c[j] = (ull)c[j] * dftA[lv][j] % MOD;\n            InvFFT(data(c), NN,\
    \ data(inv_root));\n            for (int j = 0; j < std::min(NN / 2, n - i); ++j)\n\
    \                if ((ab[i + j] += c[j + NN / 2]) >= MOD) ab[i + j] -= MOD;\n\
    \        }\n        for (int j = std::max(i - i % Threshold, i - (int)size(a)\
    \ + 1); j < i; ++j)\n            ab[i] = (ab[i] + (ull)a[i - j] * b[j]) % MOD;\n\
    \        b[i] = g(i, ab);\n        if (!empty(a)) ab[i] = (ab[i] + (ull)a[0] *\
    \ b[i]) % MOD;\n    }\n    return b;\n}\n\nstd::vector<uint> Deriv(const std::vector<uint>\
    \ &a) {\n    const int n = (int)size(a) - 1;\n    if (n <= 0) return {};\n   \
    \ std::vector<uint> res(n);\n    for (int i = 1; i <= n; ++i) res[i - 1] = (ull)a[i]\
    \ * i % MOD;\n    return res;\n}\n\nstd::vector<uint> FPSExp(const std::vector<uint>\
    \ &a, int n) {\n    const auto g = [](int n, const std::vector<uint> &c) -> uint\
    \ {\n        if (n == 0) return 1;\n        return (ull)c[n - 1] * InvMod(n) %\
    \ MOD;\n    };\n    return SemiRelaxedConv(Deriv(a), g, n);\n}\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int n;\n\
    \    std::cin >> n;\n    std::vector<uint> a(n);\n    for (int i = 0; i < n; ++i)\
    \ std::cin >> a[i];\n    const auto expA = FPSExp(a, n);\n    for (int i = 0;\
    \ i < n; ++i) std::cout << expA[i] << ' ';\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: standalone_test/formal_power_series/exp_of_formal_power_series.hoeven_divide_and_conquer_binary.test.cpp
  requiredBy: []
  timestamp: '2025-09-14 23:18:06+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: standalone_test/formal_power_series/exp_of_formal_power_series.hoeven_divide_and_conquer_binary.test.cpp
layout: document
redirect_from:
- /verify/standalone_test/formal_power_series/exp_of_formal_power_series.hoeven_divide_and_conquer_binary.test.cpp
- /verify/standalone_test/formal_power_series/exp_of_formal_power_series.hoeven_divide_and_conquer_binary.test.cpp.html
title: standalone_test/formal_power_series/exp_of_formal_power_series.hoeven_divide_and_conquer_binary.test.cpp
---
