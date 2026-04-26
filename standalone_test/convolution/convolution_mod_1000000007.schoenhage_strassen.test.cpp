// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod_1000000007

#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using uint         = unsigned;
using ull          = unsigned long long;
constexpr uint MOD = 1000000007;

constexpr uint PowMod(uint a, ull e) {
    for (uint res = 1;; a = (ull)a * a % MOD) {
        if (e & 1) res = (ull)res * a % MOD;
        if ((e /= 2) == 0) return res;
    }
}

constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

int GetFFTSize(int n) {
    int len = 1;
    while (len < n) len *= 2;
    return len;
}

// (R[x] / (x^d + 1)) / (y^delta - x^d)
//  -> (R[x] / (x^d + 1)) / (y^(delta/2) - x^(d/2))   // e[0] = 1,
//  ×  (R[x] / (x^d + 1)) / (y^(delta/2) - x^(3*d/2)) // e[1] = 3,
// ...
void FFT(uint a[], int d, int delta) {
    assert(delta <= d);
    for (int i = delta; i >= 2; i /= 2) {
        const int block = delta / i;
        std::vector<int> e(block);
        e[0] = 1;
        for (int j = 1; j < block; ++j) e[j] = e[j & (j - 1)] + (block >> __builtin_ctz(j));
        for (int j = 0; j < block; ++j) {
            const int o   = d / (block * 2) * e[j] % d;
            const int n   = d * (i / 2);
            uint *const b = a + j * n * 2;
            for (int k = 0; k < i / 2; ++k) {
                uint *const c = b + n + k * d;
                std::rotate(c, c + d - o, c + d);
                for (int l = 0; l < o; ++l)
                    if (c[l]) c[l] = MOD - c[l];
            }
            for (int k = 0; k < n; ++k) {
                const uint u = b[k];
                if ((b[k] += b[k + n]) >= MOD) b[k] -= MOD;
                if ((b[k + n] = u + MOD - b[k + n]) >= MOD) b[k + n] -= MOD;
            }
        }
    }
}

// Constraints: 2^(-1) in R
void InvFFT(uint a[], int d, int delta) {
    assert(delta <= d);
    for (int i = 2; i <= delta; i *= 2) {
        const int block = delta / i;
        std::vector<int> e(block);
        e[0] = 1;
        for (int j = 1; j < block; ++j) e[j] = e[j & (j - 1)] + (block >> __builtin_ctz(j));
        for (int j = 0; j < block; ++j) {
            const int o   = d / (block * 2) * e[j] % d;
            const int n   = d * (i / 2);
            uint *const b = a + j * n * 2;
            for (int k = 0; k < n; ++k) {
                const uint u = b[k];
                if ((b[k] += b[k + n]) >= MOD) b[k] -= MOD;
                if ((b[k + n] = u + MOD - b[k + n]) >= MOD) b[k + n] -= MOD;
            }
            for (int k = 0; k < i / 2; ++k) {
                uint *const c = b + n + k * d;
                for (int l = 0; l < o; ++l)
                    if (c[l]) c[l] = MOD - c[l];
                std::rotate(c, c + o, c + d);
            }
        }
    }
    const uint inv_delta = InvMod(delta);
    for (int i = 0; i < d * delta; ++i) a[i] = (ull)a[i] * inv_delta % MOD;
}

// Compute ab mod (x^n + 1)
// see:
// [1]: Daniel J. Bernstein. "Multidigit multiplication for mathematicians."
//      Accepted to Advances in Applied Mathematics,
//      but withdrawn by author to prevent irreparable mangling by Academic Press.
//      https://cr.yp.to/papers.html#m3
// [2]: Alin Bostan, Frédéric Chyzak, Marc Giusti, Romain Lebreton,
//      Grégoire Lecerf, Bruno Salvy et Éric Schost.
//      Algorithmes Efficaces en Calcul Formel. 686 pages.
//      Imprimé par CreateSpace. Aussi disponible en version électronique.
//      Palaiseau : Frédéric Chyzak (auto-édit.), sept. 2017. isbn : 979-10-699-0947-2.
//      https://hal.science/AECF/
void SchoenhageStrassen(const uint a[], const uint b[], uint ab[], int n) {
    assert(__builtin_popcount(n) == 1);
    enum { Threshold = 32 };
    if (n <= Threshold) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - i; ++j) ab[i + j] = (ab[i + j] + (ull)a[i] * b[j]) % MOD;
            for (int j = n - i; j < n; ++j)
                if ((ab[i + j - n] += MOD - (ull)a[i] * b[j] % MOD) >= MOD) ab[i + j - n] -= MOD;
        }
        return;
    }
    const int k = __builtin_ctz(n);
    assert(k > 2);
    const int d     = 1 << (k / 2); // d     = 2^floor(k / 2)
    const int delta = n / d;        // delta = 2^ceil(k / 2)
    // R[x] / (x^(d * delta) + 1) -> (R[x][y] / (y^delta + 1)) / (y - x^d)
    // Lifting to R[x][y] / (y^delta + 1)
    // Since polynomials in R[x][y] / (y^delta + 1) have x-degree < d,
    // We could mapping to (R[x] / (x^(2*d) + 1)) / (y^delta + 1)
    //   = (R[x] / (x^(2*d) + 1)) / (y^delta - x^(2*d)), delta <= 2*d
    //   = S / (y^delta - x^(2*d)), where S = R[x] / (x^(2*d) + 1),
    // Since delta is a power of 2,
    //   = S / (y^(delta/2) - x^d) × S / (y^(delta/2) + x^d)
    //   = S / (y^(delta/2) - x^d) × S / (y^(delta/2) - x^(3d))
    std::vector<uint> a_hat(n * 2), b_hat(n * 2), ab_hat(n * 2);
    for (int i = 0; i < delta; ++i)
        for (int j = 0; j < d; ++j)
            a_hat[i * d * 2 + j] = a[i * d + j], b_hat[i * d * 2 + j] = b[i * d + j];
    FFT(data(a_hat), d * 2, delta), FFT(data(b_hat), d * 2, delta);
    for (int i = 0; i < delta; ++i)
        SchoenhageStrassen(data(a_hat) + i * d * 2, data(b_hat) + i * d * 2,
                           data(ab_hat) + i * d * 2, d * 2);
    InvFFT(data(ab_hat), d * 2, delta);
    for (int i = 0; i < delta; ++i)
        for (int j = 0; j < d * 2; ++j)
            if (i * d + j < n) {
                if ((ab[i * d + j] += ab_hat[i * d * 2 + j]) >= MOD) ab[i * d + j] -= MOD;
            } else {
                if ((ab[i * d + j - n] += MOD - ab_hat[i * d * 2 + j]) >= MOD)
                    ab[i * d + j - n] -= MOD;
            }
}

std::vector<uint> Product(std::vector<uint> a, std::vector<uint> b) {
    if (empty(a) || empty(b)) return {};
    const int n = size(a), m = size(b);
    const int N = GetFFTSize(n + m - 1);
    a.resize(N), b.resize(N);
    std::vector<uint> ab(N);
    SchoenhageStrassen(data(a), data(b), data(ab), N);
    ab.resize(n + m - 1);
    return ab;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<uint> a(n), b(m);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];
    const auto ab = Product(std::move(a), std::move(b));
    for (int i = 0; i < n + m - 1; ++i) std::cout << ab[i] << ' ';
    return 0;
}
