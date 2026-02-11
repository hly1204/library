// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/log_of_formal_power_series

#include <algorithm>
#include <cassert>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

using uint         = unsigned;
using ull          = unsigned long long;
constexpr uint MOD = 998244353;

constexpr uint PowMod(uint a, ull e) {
    for (uint res = 1;; a = (ull)a * a % MOD) {
        if (e & 1) res = (ull)res * a % MOD;
        if ((e /= 2) == 0) return res;
    }
}

constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

constexpr uint QUAD_NONRESIDUE = 3;
constexpr int LOG2_ORD         = __builtin_ctz(MOD - 1);
constexpr uint ZETA            = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);
constexpr uint INV_ZETA        = InvMod(ZETA);

std::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int n) {
    assert((n & (n - 1)) == 0);
    if (n / 2 == 0) return {};
    std::vector<uint> root(n / 2), inv_root(n / 2);
    root[0] = inv_root[0] = 1;
    for (int i = 0; (1 << i) < n / 2; ++i)
        root[1 << i]               = PowMod(ZETA, 1LL << (LOG2_ORD - i - 2)),
                  inv_root[1 << i] = PowMod(INV_ZETA, 1LL << (LOG2_ORD - i - 2));
    for (int i = 1; i < n / 2; ++i)
        root[i]     = (ull)root[i - (i & (i - 1))] * root[i & (i - 1)] % MOD,
        inv_root[i] = (ull)inv_root[i - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;
    return {root, inv_root};
}

namespace detail {
template<int N> void ButterflyRecPrime(uint[], const uint[], int);
template<> void ButterflyRecPrime<1>(uint[], const uint[], int) {}
template<int N> void ButterflyRecPrime(uint a[], const uint root[], int lv) {
    for (int i = 0; i < N / 2; ++i) {
        const uint u = a[i];
        a[i + N / 2] = (ull)a[i + N / 2] * root[lv] % MOD;
        if ((a[i] += a[i + N / 2]) >= MOD) a[i] -= MOD;
        if ((a[i + N / 2] = u + MOD - a[i + N / 2]) >= MOD) a[i + N / 2] -= MOD;
    }
    ButterflyRecPrime<N / 2>(a, root, lv * 2);
    ButterflyRecPrime<N / 2>(a + N / 2, root, lv * 2 + 1);
}
template<int N> void ButterflyRec(uint[], const uint[]);
template<> void ButterflyRec<1>(uint[], const uint[]) {}
template<int N> void ButterflyRec(uint a[], const uint root[]) {
    for (int i = 0; i < N / 2; ++i) {
        const uint u = a[i];
        if ((a[i] += a[i + N / 2]) >= MOD) a[i] -= MOD;
        if ((a[i + N / 2] = u + MOD - a[i + N / 2]) >= MOD) a[i + N / 2] -= MOD;
    }
    ButterflyRec<N / 2>(a, root);
    ButterflyRecPrime<N / 2>(a + N / 2, root, 1);
}
template<int N> void InvButterflyRecPrime(uint[], const uint[], int);
template<> void InvButterflyRecPrime<1>(uint[], const uint[], int) {}
template<int N> void InvButterflyRecPrime(uint a[], const uint root[], int lv) {
    InvButterflyRecPrime<N / 2>(a, root, lv * 2);
    InvButterflyRecPrime<N / 2>(a + N / 2, root, lv * 2 + 1);
    for (int i = 0; i < N / 2; ++i) {
        const uint u = a[i];
        if ((a[i] += a[i + N / 2]) >= MOD) a[i] -= MOD;
        a[i + N / 2] = (ull)(u + MOD - a[i + N / 2]) * root[lv] % MOD;
    }
}
template<int N> void InvButterflyRec(uint[], const uint[]);
template<> void InvButterflyRec<1>(uint[], const uint[]) {}
template<int N> void InvButterflyRec(uint a[], const uint root[]) {
    InvButterflyRec<N / 2>(a, root);
    InvButterflyRecPrime<N / 2>(a + N / 2, root, 1);
    for (int i = 0; i < N / 2; ++i) {
        const uint u = a[i];
        if ((a[i] += a[i + N / 2]) >= MOD) a[i] -= MOD;
        if ((a[i + N / 2] = u + MOD - a[i + N / 2]) >= MOD) a[i + N / 2] -= MOD;
    }
}
// clang-format off
template<int... Is>
void ButterflyHelper(uint a[], int n, const uint root[], std::integer_sequence<int, Is...>)
{ ([&] { if (n == (1 << Is)) ButterflyRec<(1 << Is)>(a, root); }(), ...); }
template<int... Is>
void InvButterflyHelper(uint a[], int n, const uint root[], std::integer_sequence<int, Is...>)
{ ([&] { if (n == (1 << Is)) InvButterflyRec<(1 << Is)>(a, root); }(), ...); }
// clang-format on
} // namespace detail

void Butterfly(uint a[], int n, const uint root[]) {
    detail::ButterflyHelper(a, n, root, std::make_integer_sequence<int, LOG2_ORD + 1>{});
}
void InvButterfly(uint a[], int n, const uint root[]) {
    detail::InvButterflyHelper(a, n, root, std::make_integer_sequence<int, LOG2_ORD + 1>{});
}

int GetFFTSize(int n) {
    int len = 1;
    while (len < n) len *= 2;
    return len;
}

void FFT(uint a[], int n, const uint root[]) { Butterfly(a, n, root); }

void InvFFT(uint a[], int n, const uint root[]) {
    InvButterfly(a, n, root);
    const uint invN = InvMod(n);
    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invN % MOD;
}

// see:
// [1]: Joris van der Hoeven. Relaxed multiplication using the middle product. ISSAC 2003: 143-147
//      https://www.texmacs.org/joris/issac03/issac03.pdf
template<typename Fn>
std::enable_if_t<std::is_invocable_r_v<uint, Fn, int, const std::vector<uint> &>, std::vector<uint>>
SemiRelaxedConv(const std::vector<uint> &a, Fn g, int n) {
    assert(n >= 0);
    if (n == 0) return {};
    enum { Threshold = 32 };
    assert((Threshold & (Threshold - 1)) == 0);
    const int N                 = GetFFTSize(n);
    const auto [root, inv_root] = GetFFTRoot(N);
    std::vector<std::vector<uint>> dftA;
    for (int i = Threshold * 2; i <= N; i *= 2) {
        auto &&aa = dftA.emplace_back(i);
        copy(begin(a), min(begin(a) + i, end(a)), begin(aa));
        FFT(data(aa), i, data(root));
    }
    std::vector<uint> b(n), ab(n);
    b[0] = g(0, ab);
    if (!empty(a)) ab[0] = (ull)a[0] * b[0] % MOD;
    for (int i = 1; i < n; ++i) {
        if (i % Threshold == 0) {
            const int lv = __builtin_ctz(i / Threshold);
            const int NN = Threshold << (lv + 1);
            std::vector<uint> c(NN);
            copy(begin(b) + i - NN / 2, begin(b) + i, begin(c));
            FFT(data(c), NN, data(root));
            for (int j = 0; j < NN; ++j) c[j] = (ull)c[j] * dftA[lv][j] % MOD;
            InvFFT(data(c), NN, data(inv_root));
            for (int j = 0; j < std::min(NN / 2, n - i); ++j)
                if ((ab[i + j] += c[j + NN / 2]) >= MOD) ab[i + j] -= MOD;
        }
        for (int j = std::max(i - i % Threshold, i - (int)size(a) + 1); j < i; ++j)
            ab[i] = (ab[i] + (ull)a[i - j] * b[j]) % MOD;
        b[i] = g(i, ab);
        if (!empty(a)) ab[i] = (ab[i] + (ull)a[0] * b[i]) % MOD;
    }
    return b;
}

std::vector<uint> Deriv(const std::vector<uint> &a) {
    const int n = (int)size(a) - 1;
    if (n <= 0) return {};
    std::vector<uint> res(n);
    for (int i = 1; i <= n; ++i) res[i - 1] = (ull)a[i] * i % MOD;
    return res;
}

std::vector<uint> Integr(const std::vector<uint> &a, uint c = 0) {
    const int n = size(a) + 1;
    std::vector<uint> res(n);
    res[0] = c;
    for (int i = 1; i < n; ++i) res[i] = (ull)a[i - 1] * InvMod(i) % MOD;
    return res;
}

std::vector<uint> FPSDiv(const std::vector<uint> &a, const std::vector<uint> &b, int n) {
    assert(!empty(b) && b[0] != 0);
    if (n == 0) return {};
    const auto g = [&, invB0 = InvMod(b[0])](int n, const std::vector<uint> &c) -> uint {
        if (n < (int)size(a)) return (ull)(a[n] + MOD - c[n]) * invB0 % MOD;
        return (ull)(MOD - c[n]) * invB0 % MOD;
    };
    return SemiRelaxedConv(b, g, n);
}

std::vector<uint> FPSLog(const std::vector<uint> &a, int n) {
    return Integr(FPSDiv(Deriv(a), a, n - 1));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<uint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    const auto logA = FPSLog(a, n);
    for (int i = 0; i < n; ++i) std::cout << logA[i] << ' ';
    return 0;
}
