// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_formal_power_series

#include <cassert>
#include <cstring>
#include <iostream>
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

std::vector<uint> FPSInv(const std::vector<uint> &a, int n) {
    assert(!empty(a) && a[0] != 0);
    assert(n >= 0);
    if (n == 0) return {};
    const int N                 = GetFFTSize(n);
    const auto [root, inv_root] = GetFFTRoot(N);
    std::vector<uint> invA(N), shopA(N), shopB(N);
    invA[0] = InvMod(a[0]);
    for (int i = 2; i <= N; i *= 2) {
        std::memcpy(data(shopA), data(a), sizeof(uint) * std::min((int)size(a), i));
        if ((int)size(a) < i)
            std::memset(data(shopA) + (int)size(a), 0, sizeof(uint) * (i - (int)size(a)));
        std::memcpy(data(shopB), data(invA), sizeof(uint) * i);
        FFT(data(shopA), i, data(root));
        FFT(data(shopB), i, data(root));
        for (int j = 0; j < i; ++j) shopA[j] = (ull)shopA[j] * shopB[j] % MOD;
        InvFFT(data(shopA), i, data(inv_root));
        std::memset(data(shopA), 0, sizeof(uint) * (i / 2));
        FFT(data(shopA), i, data(root));
        for (int j = 0; j < i; ++j) shopA[j] = (ull)shopA[j] * shopB[j] % MOD;
        InvFFT(data(shopA), i, data(inv_root));
        for (int j = i / 2; j < i; ++j) invA[j] = shopA[j] != 0 ? MOD - shopA[j] : shopA[j];
    }
    invA.resize(n);
    return invA;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<uint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    const auto invA = FPSInv(a, n);
    for (int i = 0; i < n; ++i) std::cout << invA[i] << ' ';
    return 0;
}
