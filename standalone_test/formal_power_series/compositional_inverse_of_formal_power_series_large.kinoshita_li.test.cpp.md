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
    PROBLEM: https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large
    links:
    - https://arxiv.org/abs/2404.05177
    - https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large
    - https://www.texmacs.org/joris/issac03/issac03.pdf
  bundledCode: "#line 1 \"standalone_test/formal_power_series/compositional_inverse_of_formal_power_series_large.kinoshita_li.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstring>\n#include <iostream>\n\
    #include <tuple>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nusing uint         = unsigned;\nusing ull          = unsigned long long;\nconstexpr\
    \ uint MOD = 998244353;\n\nconstexpr uint PowMod(uint a, ull e) {\n    for (uint\
    \ res = 1;; a = (ull)a * a % MOD) {\n        if (e & 1) res = (ull)res * a % MOD;\n\
    \        if ((e /= 2) == 0) return res;\n    }\n}\n\nconstexpr uint InvMod(uint\
    \ a) { return PowMod(a, MOD - 2); }\n\nconstexpr uint QUAD_NONRESIDUE = 3;\nconstexpr\
    \ int LOG2_ORD         = __builtin_ctz(MOD - 1);\nconstexpr uint ZETA        \
    \    = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);\nconstexpr uint INV_ZETA\
    \        = InvMod(ZETA);\n\nstd::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int\
    \ n) {\n    assert((n & (n - 1)) == 0);\n    if (n / 2 == 0) return {};\n    std::vector<uint>\
    \ root(n / 2), inv_root(n / 2);\n    root[0] = inv_root[0] = 1;\n    for (int\
    \ i = 0; (1 << i) < n / 2; ++i)\n        root[1 << i]               = PowMod(ZETA,\
    \ 1LL << (LOG2_ORD - i - 2)),\n                  inv_root[1 << i] = PowMod(INV_ZETA,\
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
    // [1]: Yasunori Kinoshita, Baitian Li.\n//      Power Series Composition in Near-Linear\
    \ Time. FOCS 2024: 2180-2185\n//      https://arxiv.org/abs/2404.05177\n// Power\
    \ Projection: [x^(n-1)] (fg^i) for i=0,..,n-1\nstd::vector<uint> PowProj(std::vector<uint>\
    \ f, std::vector<uint> g, int n) {\n    assert(empty(g) || g[0] == 0);\n    const\
    \ int N = GetFFTSize(n);\n    std::vector<uint> root, inv_root;\n    tie(root,\
    \ inv_root) = GetFFTRoot(N * 4);\n    // [x^(n-1)] (f(x) / (-g(x) + y)) in R[x]((y^(-1)))\n\
    \    const auto KinoshitaLi = [&](std::vector<uint> &P, std::vector<uint> &Q,\
    \ int d, int n) {\n        assert((int)size(P) == d * n * 2);\n        assert((int)size(Q)\
    \ == d * n * 2);\n        P.insert(begin(P), d * n * 2, 0u);\n        Q.resize(d\
    \ * n * 4);\n        std::vector<uint> nextP(d * n * 4);\n        for (; n > 1;\
    \ d *= 2, n /= 2) {\n            Q[d * n * 2] = 1;\n            FFT(data(P), d\
    \ * n * 4, data(inv_root));\n            FFT(data(Q), d * n * 4, data(root));\n\
    \            uint *const nP = data(nextP) + d * n * 2;\n            for (int i\
    \ = 0; i < d * n * 4; i += 2) {\n                if ((nP[i / 2] = ((ull)P[i] *\
    \ Q[i + 1] + (ull)P[i + 1] * Q[i]) % MOD) & 1)\n                    nP[i / 2]\
    \ += MOD;\n                nP[i / 2] /= 2;\n                Q[i / 2] = (ull)Q[i]\
    \ * Q[i + 1] % MOD;\n            }\n            InvFFT(nP, d * n * 2, data(root));\n\
    \            InvFFT(data(Q), d * n * 2, data(inv_root));\n            assert(Q[0]\
    \ == 1);\n            Q[0] = 0;\n            for (int i = 0; i < d * 2; ++i) {\n\
    \                std::memset(nP + i * n, 0, sizeof(uint) * (n / 2));\n       \
    \         std::memset(data(Q) + i * n + n / 2, 0, sizeof(uint) * (n / 2));\n \
    \           }\n            P.swap(nextP);\n            std::memset(data(P), 0,\
    \ sizeof(uint) * (d * n * 2));\n            std::memset(data(Q) + d * n * 2, 0,\
    \ sizeof(uint) * (d * n * 2));\n        }\n        P.erase(begin(P), begin(P)\
    \ + d * n * 2);\n    };\n    f.insert(begin(f), N - n, 0);\n    f.resize(N);\n\
    \    reverse(begin(f), end(f));\n    f.insert(begin(f), N, 0u);\n    g.resize(N\
    \ * 2);\n    for (int i = 0; i < N; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);\n\
    \    std::memset(data(g) + N, 0, sizeof(uint) * N);\n    KinoshitaLi(f, g, 1,\
    \ N);\n    for (int i = 0; i < N; ++i) f[i] = f[i * 2 + 1];\n    f.resize(n);\n\
    \    return f;\n}\n\n// see:\n// [1]: Joris van der Hoeven. Relaxed mltiplication\
    \ using the middle product. ISSAC 2003: 143-147\n//      https://www.texmacs.org/joris/issac03/issac03.pdf\n\
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
    \ * i % MOD;\n    return res;\n}\n\nstd::vector<uint> Integr(const std::vector<uint>\
    \ &a, uint c = 0) {\n    const int n = size(a) + 1;\n    std::vector<uint> res(n);\n\
    \    res[0] = c;\n    for (int i = 1; i < n; ++i) res[i] = (ull)a[i - 1] * InvMod(i)\
    \ % MOD;\n    return res;\n}\n\nstd::vector<uint> FPSDiv(const std::vector<uint>\
    \ &a, const std::vector<uint> &b, int n) {\n    assert(!empty(b) && b[0] != 0);\n\
    \    if (n == 0) return {};\n    const auto g = [&, invB0 = InvMod(b[0])](int\
    \ n, const std::vector<uint> &c) -> uint {\n        if (n < (int)size(a)) return\
    \ (ull)(a[n] + MOD - c[n]) * invB0 % MOD;\n        return (ull)(MOD - c[n]) *\
    \ invB0 % MOD;\n    };\n    return SemiRelaxedConv(b, g, n);\n}\n\nstd::vector<uint>\
    \ FPSLog(const std::vector<uint> &a, int n) {\n    return Integr(FPSDiv(Deriv(a),\
    \ a, n - 1));\n}\n\nstd::vector<uint> FPSExp(const std::vector<uint> &a, int n)\
    \ {\n    const auto g = [](int n, const std::vector<uint> &c) -> uint {\n    \
    \    if (n == 0) return 1;\n        return (ull)c[n - 1] * InvMod(n) % MOD;\n\
    \    };\n    return SemiRelaxedConv(Deriv(a), g, n);\n}\n\nstd::vector<uint> FPSPow1(const\
    \ std::vector<uint> &a, uint e, int n) {\n    assert(!empty(a) && a[0] == 1);\n\
    \    auto logA = FPSLog(a, n);\n    for (int i = 0; i < n; ++i) logA[i] = (ull)logA[i]\
    \ * e % MOD;\n    return FPSExp(logA, n);\n}\n\nstd::vector<uint> FPSRev(std::vector<uint>\
    \ f, int n) {\n    assert(size(f) >= 2 && f[0] == 0 && f[1] != 0);\n    if (n\
    \ == 1) return std::vector<uint>{0u};\n    f.resize(n);\n    const uint invF1\
    \ = InvMod(f[1]);\n    uint invF1p      = 1;\n    for (int i = 0; i < n; ++i)\
    \ f[i] = (ull)f[i] * invF1p % MOD, invF1p = (ull)invF1p * invF1 % MOD;\n    std::vector<uint>\
    \ inv(n);\n    inv[1] = 1;\n    for (int i = 2; i < n; ++i) inv[i] = (ull)(MOD\
    \ - MOD / i) * inv[MOD % i] % MOD;\n    auto proj = PowProj(std::vector<uint>{1u},\
    \ f, n);\n    for (int i = 1; i < n; ++i) proj[i] = (ull)proj[i] * (n - 1) % MOD\
    \ * inv[i] % MOD;\n    reverse(begin(proj), end(proj));\n    auto res = FPSPow1(proj,\
    \ InvMod(MOD + 1 - n), n - 1);\n    for (int i = 0; i < n - 1; ++i) res[i] = (ull)res[i]\
    \ * invF1 % MOD;\n    res.insert(begin(res), 0u);\n    return res;\n}\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n;\n    std::cin >> n;\n    std::vector<uint> f(n);\n    for (int i = 0; i <\
    \ n; ++i) std::cin >> f[i];\n    const auto revF = FPSRev(f, n);\n    for (int\
    \ i = 0; i < n; ++i) std::cout << revF[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstring>\n#include <iostream>\n\
    #include <tuple>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nusing uint         = unsigned;\nusing ull          = unsigned long long;\nconstexpr\
    \ uint MOD = 998244353;\n\nconstexpr uint PowMod(uint a, ull e) {\n    for (uint\
    \ res = 1;; a = (ull)a * a % MOD) {\n        if (e & 1) res = (ull)res * a % MOD;\n\
    \        if ((e /= 2) == 0) return res;\n    }\n}\n\nconstexpr uint InvMod(uint\
    \ a) { return PowMod(a, MOD - 2); }\n\nconstexpr uint QUAD_NONRESIDUE = 3;\nconstexpr\
    \ int LOG2_ORD         = __builtin_ctz(MOD - 1);\nconstexpr uint ZETA        \
    \    = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);\nconstexpr uint INV_ZETA\
    \        = InvMod(ZETA);\n\nstd::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int\
    \ n) {\n    assert((n & (n - 1)) == 0);\n    if (n / 2 == 0) return {};\n    std::vector<uint>\
    \ root(n / 2), inv_root(n / 2);\n    root[0] = inv_root[0] = 1;\n    for (int\
    \ i = 0; (1 << i) < n / 2; ++i)\n        root[1 << i]               = PowMod(ZETA,\
    \ 1LL << (LOG2_ORD - i - 2)),\n                  inv_root[1 << i] = PowMod(INV_ZETA,\
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
    // [1]: Yasunori Kinoshita, Baitian Li.\n//      Power Series Composition in Near-Linear\
    \ Time. FOCS 2024: 2180-2185\n//      https://arxiv.org/abs/2404.05177\n// Power\
    \ Projection: [x^(n-1)] (fg^i) for i=0,..,n-1\nstd::vector<uint> PowProj(std::vector<uint>\
    \ f, std::vector<uint> g, int n) {\n    assert(empty(g) || g[0] == 0);\n    const\
    \ int N = GetFFTSize(n);\n    std::vector<uint> root, inv_root;\n    tie(root,\
    \ inv_root) = GetFFTRoot(N * 4);\n    // [x^(n-1)] (f(x) / (-g(x) + y)) in R[x]((y^(-1)))\n\
    \    const auto KinoshitaLi = [&](std::vector<uint> &P, std::vector<uint> &Q,\
    \ int d, int n) {\n        assert((int)size(P) == d * n * 2);\n        assert((int)size(Q)\
    \ == d * n * 2);\n        P.insert(begin(P), d * n * 2, 0u);\n        Q.resize(d\
    \ * n * 4);\n        std::vector<uint> nextP(d * n * 4);\n        for (; n > 1;\
    \ d *= 2, n /= 2) {\n            Q[d * n * 2] = 1;\n            FFT(data(P), d\
    \ * n * 4, data(inv_root));\n            FFT(data(Q), d * n * 4, data(root));\n\
    \            uint *const nP = data(nextP) + d * n * 2;\n            for (int i\
    \ = 0; i < d * n * 4; i += 2) {\n                if ((nP[i / 2] = ((ull)P[i] *\
    \ Q[i + 1] + (ull)P[i + 1] * Q[i]) % MOD) & 1)\n                    nP[i / 2]\
    \ += MOD;\n                nP[i / 2] /= 2;\n                Q[i / 2] = (ull)Q[i]\
    \ * Q[i + 1] % MOD;\n            }\n            InvFFT(nP, d * n * 2, data(root));\n\
    \            InvFFT(data(Q), d * n * 2, data(inv_root));\n            assert(Q[0]\
    \ == 1);\n            Q[0] = 0;\n            for (int i = 0; i < d * 2; ++i) {\n\
    \                std::memset(nP + i * n, 0, sizeof(uint) * (n / 2));\n       \
    \         std::memset(data(Q) + i * n + n / 2, 0, sizeof(uint) * (n / 2));\n \
    \           }\n            P.swap(nextP);\n            std::memset(data(P), 0,\
    \ sizeof(uint) * (d * n * 2));\n            std::memset(data(Q) + d * n * 2, 0,\
    \ sizeof(uint) * (d * n * 2));\n        }\n        P.erase(begin(P), begin(P)\
    \ + d * n * 2);\n    };\n    f.insert(begin(f), N - n, 0);\n    f.resize(N);\n\
    \    reverse(begin(f), end(f));\n    f.insert(begin(f), N, 0u);\n    g.resize(N\
    \ * 2);\n    for (int i = 0; i < N; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);\n\
    \    std::memset(data(g) + N, 0, sizeof(uint) * N);\n    KinoshitaLi(f, g, 1,\
    \ N);\n    for (int i = 0; i < N; ++i) f[i] = f[i * 2 + 1];\n    f.resize(n);\n\
    \    return f;\n}\n\n// see:\n// [1]: Joris van der Hoeven. Relaxed mltiplication\
    \ using the middle product. ISSAC 2003: 143-147\n//      https://www.texmacs.org/joris/issac03/issac03.pdf\n\
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
    \ * i % MOD;\n    return res;\n}\n\nstd::vector<uint> Integr(const std::vector<uint>\
    \ &a, uint c = 0) {\n    const int n = size(a) + 1;\n    std::vector<uint> res(n);\n\
    \    res[0] = c;\n    for (int i = 1; i < n; ++i) res[i] = (ull)a[i - 1] * InvMod(i)\
    \ % MOD;\n    return res;\n}\n\nstd::vector<uint> FPSDiv(const std::vector<uint>\
    \ &a, const std::vector<uint> &b, int n) {\n    assert(!empty(b) && b[0] != 0);\n\
    \    if (n == 0) return {};\n    const auto g = [&, invB0 = InvMod(b[0])](int\
    \ n, const std::vector<uint> &c) -> uint {\n        if (n < (int)size(a)) return\
    \ (ull)(a[n] + MOD - c[n]) * invB0 % MOD;\n        return (ull)(MOD - c[n]) *\
    \ invB0 % MOD;\n    };\n    return SemiRelaxedConv(b, g, n);\n}\n\nstd::vector<uint>\
    \ FPSLog(const std::vector<uint> &a, int n) {\n    return Integr(FPSDiv(Deriv(a),\
    \ a, n - 1));\n}\n\nstd::vector<uint> FPSExp(const std::vector<uint> &a, int n)\
    \ {\n    const auto g = [](int n, const std::vector<uint> &c) -> uint {\n    \
    \    if (n == 0) return 1;\n        return (ull)c[n - 1] * InvMod(n) % MOD;\n\
    \    };\n    return SemiRelaxedConv(Deriv(a), g, n);\n}\n\nstd::vector<uint> FPSPow1(const\
    \ std::vector<uint> &a, uint e, int n) {\n    assert(!empty(a) && a[0] == 1);\n\
    \    auto logA = FPSLog(a, n);\n    for (int i = 0; i < n; ++i) logA[i] = (ull)logA[i]\
    \ * e % MOD;\n    return FPSExp(logA, n);\n}\n\nstd::vector<uint> FPSRev(std::vector<uint>\
    \ f, int n) {\n    assert(size(f) >= 2 && f[0] == 0 && f[1] != 0);\n    if (n\
    \ == 1) return std::vector<uint>{0u};\n    f.resize(n);\n    const uint invF1\
    \ = InvMod(f[1]);\n    uint invF1p      = 1;\n    for (int i = 0; i < n; ++i)\
    \ f[i] = (ull)f[i] * invF1p % MOD, invF1p = (ull)invF1p * invF1 % MOD;\n    std::vector<uint>\
    \ inv(n);\n    inv[1] = 1;\n    for (int i = 2; i < n; ++i) inv[i] = (ull)(MOD\
    \ - MOD / i) * inv[MOD % i] % MOD;\n    auto proj = PowProj(std::vector<uint>{1u},\
    \ f, n);\n    for (int i = 1; i < n; ++i) proj[i] = (ull)proj[i] * (n - 1) % MOD\
    \ * inv[i] % MOD;\n    reverse(begin(proj), end(proj));\n    auto res = FPSPow1(proj,\
    \ InvMod(MOD + 1 - n), n - 1);\n    for (int i = 0; i < n - 1; ++i) res[i] = (ull)res[i]\
    \ * invF1 % MOD;\n    res.insert(begin(res), 0u);\n    return res;\n}\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n;\n    std::cin >> n;\n    std::vector<uint> f(n);\n    for (int i = 0; i <\
    \ n; ++i) std::cin >> f[i];\n    const auto revF = FPSRev(f, n);\n    for (int\
    \ i = 0; i < n; ++i) std::cout << revF[i] << ' ';\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: standalone_test/formal_power_series/compositional_inverse_of_formal_power_series_large.kinoshita_li.test.cpp
  requiredBy: []
  timestamp: '2025-08-24 01:45:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: standalone_test/formal_power_series/compositional_inverse_of_formal_power_series_large.kinoshita_li.test.cpp
layout: document
redirect_from:
- /verify/standalone_test/formal_power_series/compositional_inverse_of_formal_power_series_large.kinoshita_li.test.cpp
- /verify/standalone_test/formal_power_series/compositional_inverse_of_formal_power_series_large.kinoshita_li.test.cpp.html
title: standalone_test/formal_power_series/compositional_inverse_of_formal_power_series_large.kinoshita_li.test.cpp
---
