#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series_large"

#include <cassert>
#include <cstring>
#include <iostream>
#include <tuple>
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
// [1]: Yasunori Kinoshita, Baitian Li.
//      Power Series Composition in Near-Linear Time. FOCS 2024: 2180-2185
//      https://arxiv.org/abs/2404.05177
std::vector<uint> FPSComp(std::vector<uint> f, std::vector<uint> g, int n) {
    assert(empty(g) || g[0] == 0);
    const int N = GetFFTSize(n);
    std::vector<uint> root, inv_root;
    tie(root, inv_root) = GetFFTRoot(N * 4);
    // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n in R[x]((y^(-1)))
    const auto KinoshitaLi = [&root = as_const(root), &inv_root = as_const(inv_root)](
                                 auto &&KinoshitaLi, std::vector<uint> &P, std::vector<uint> Q,
                                 int d, int n) {
        assert((int)size(P) == d * n * 2);
        assert((int)size(Q) == d * n * 2);
        if (n == 1) return;
        Q.resize(d * n * 4);
        Q[d * n * 2] = 1;
        FFT(data(Q), d * n * 4, data(root));
        if (n > 2) {
            std::vector<uint> V(d * n * 2);
            for (int i = 0; i < d * n * 4; i += 2) V[i / 2] = (ull)Q[i] * Q[i + 1] % MOD;
            InvFFT(data(V), d * n * 2, data(inv_root));
            assert(V[0] == 1);
            V[0] = 0;
            for (int i = 0; i < d * 2; ++i)
                std::memset(data(V) + i * n + n / 2, 0, sizeof(uint) * (n / 2));
            KinoshitaLi(KinoshitaLi, P, std::move(V), d * 2, n / 2);
        }
        FFT(data(P), d * n * 2, data(root));
        for (int i = 0; i < d * n * 4; i += 2) {
            const uint u = Q[i];
            Q[i]         = (ull)P[i / 2] * Q[i + 1] % MOD;
            Q[i + 1]     = (ull)P[i / 2] * u % MOD;
        }
        InvFFT(data(Q), d * n * 4, data(inv_root));
        for (int i = 0; i < d; ++i) {
            uint *const u = data(P) + i * n * 2;
            std::memcpy(u, data(Q) + (i + d) * (n * 2), sizeof(uint) * n);
            std::memset(u + n, 0, sizeof(uint) * n);
        }
    };
    f.resize(N * 2);
    g.resize(N * 2);
    for (int i = N - 1; i >= 0; --i) f[i * 2] = f[i], f[i * 2 + 1] = 0;
    for (int i = 0; i < N; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
    std::memset(data(g) + N, 0, sizeof(uint) * N);
    KinoshitaLi(KinoshitaLi, f, std::move(g), 1, N);
    f.resize(n);
    return f;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<uint> f(n), g(n);
    for (int i = 0; i < n; ++i) std::cin >> f[i];
    for (int i = 0; i < n; ++i) std::cin >> g[i];
    const auto fg = FPSComp(f, g, n);
    for (int i = 0; i < n; ++i) std::cout << fg[i] << ' ';
    return 0;
}
