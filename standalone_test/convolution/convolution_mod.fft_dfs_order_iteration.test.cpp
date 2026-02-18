// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

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

int GetFFTSize(int n) {
    int len = 1;
    while (len < n) len *= 2;
    return len;
}

void FFT(uint a[], int n, const uint root[]) {
    for (int L = __builtin_ctz(n), C = 0;;) {
        uint *const b = a + (C << L);
        for (int i = 0, N = 1 << (L - 1); i < N; ++i) {
            const uint u = b[i];
            if (C) b[i + N] = (ull)b[i + N] * root[C] % MOD;
            if ((b[i] += b[i + N]) >= MOD) b[i] -= MOD;
            if ((b[i + N] = u + MOD - b[i + N]) >= MOD) b[i + N] -= MOD;
        }
        if (C == n / 2 - 1) break;
        if (L != 1) --L, C *= 2;
        else { L += __builtin_ctz(C + 1), C = (C >> __builtin_ctz(C + 1)) + 1; }
    }
}

void InvFFT(uint a[], int n, const uint root[]) {
    for (int L = 1, C = 0;;) {
        uint *const b = a + (C << L);
        for (int i = 0, N = 1 << (L - 1); i < N; ++i) {
            const uint u = b[i];
            if ((b[i] += b[i + N]) >= MOD) b[i] -= MOD;
            if (C) b[i + N] = (ull)(u + MOD - b[i + N]) * root[C] % MOD;
            else if ((b[i + N] = u + MOD - b[i + N]) >= MOD) { b[i + N] -= MOD; }
        }
        if (L == __builtin_ctz(n)) break;
        if (C & 1) ++L, C /= 2;
        else { C = (C << (L - 1) | ((1 << (L - 1)) - 1)) + 1, L = 1; }
    }
    const uint invN = InvMod(n);
    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invN % MOD;
}

std::vector<uint> Product(std::vector<uint> a, std::vector<uint> b) {
    if (empty(a) || empty(b)) return {};
    const int n = a.size(), m = b.size();
    const int N                 = GetFFTSize(n + m - 1);
    const auto [root, inv_root] = GetFFTRoot(N);
    a.resize(N), b.resize(N);
    FFT(data(a), N, data(root)), FFT(data(b), N, data(root));
    for (int i = 0; i < N; ++i) a[i] = (ull)a[i] * b[i] % MOD;
    InvFFT(data(a), N, data(inv_root));
    a.resize(n + m - 1);
    return a;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<uint> a(n), b(m);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];
    const auto ab = Product(a, b);
    for (int i = 0; i < n + m - 1; ++i) std::cout << ab[i] << ' ';
    return 0;
}
