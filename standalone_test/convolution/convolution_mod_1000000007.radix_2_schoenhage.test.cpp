// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod_1000000007

#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using uint         = unsigned;
using ull          = unsigned long long;
constexpr uint MOD = 1000000007;

constexpr uint InvMod(uint a_) {
    int x1 = 1, x3 = 0, a = a_, b = MOD;
    while (b) {
        const int q = a / b, x1_old = x1, a_old = a;
        x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return x1 < 0 ? x1 + (int)MOD : x1;
}

int GetFFTSize(int n) {
    int len = 1;
    while (len < n) len *= 2;
    return len;
}

// Compute a * x^n mod (x^d + 1)
// Note that x^(2*d) = 1 mod (x^d + 1)
void MultipliedByXToTheN(uint a[], int d, int n) {
    if ((n %= d * 2) < 0) n += d * 2;
    const auto n_leq_d = [](uint a[], int d, int n) {
        assert(n <= d);
        std::rotate(a, a + d - n, a + d);
        for (int i = 0; i < n; ++i)
            if (a[i]) a[i] = MOD - a[i];
    };
    for (; n >= d; n -= d) n_leq_d(a, d, d);
    if (n) n_leq_d(a, d, n);
}

// Apply radix-2 FFT over (R[x] / (x^d + 1))[y] / (y^delta - x^E)
void FFT(uint a[], int d, int delta, int E) {
    assert(delta <= d);
    assert(E % delta == 0);
    if (delta == 1) return;
    const int n = d * (delta / 2);
    for (int i = 0; i < delta / 2; ++i) {
        uint *const b[] = {a + i * d, a + i * d + n};
        MultipliedByXToTheN(b[1], d, E / 2);
        for (int j = 0; j < d; ++j) {
            const uint u = b[0][j];
            if ((b[0][j] += b[1][j]) >= MOD) b[0][j] -= MOD;
            if ((b[1][j] = u + MOD - b[1][j]) >= MOD) b[1][j] -= MOD;
        }
    }
    for (int i = 0; i < 2; ++i) FFT(a + n * i, d, delta / 2, E / 2 + d * i);
}

// Constraints: 1/2 in R
void InvFFT(uint a[], int d, int delta, int E) {
    const auto inv_fft = [](auto &&inv_fft, uint a[], int d, int delta, int E) {
        assert(delta <= d);
        assert(E % delta == 0);
        if (delta == 1) return;
        const int n = d * (delta / 2);
        for (int i = 0; i < 2; ++i) inv_fft(inv_fft, a + n * i, d, delta / 2, E / 2 + d * i);
        for (int i = 0; i < delta / 2; ++i) {
            uint *const b[] = {a + i * d, a + i * d + n};
            for (int j = 0; j < d; ++j) {
                const uint u = b[0][j];
                if ((b[0][j] += b[1][j]) >= MOD) b[0][j] -= MOD;
                if ((b[1][j] = u + MOD - b[1][j]) >= MOD) b[1][j] -= MOD;
            }
            MultipliedByXToTheN(b[1], d, -E / 2);
        }
    };
    inv_fft(inv_fft, a, d, delta, E);
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
void Schoenhage(const uint a[], const uint b[], uint ab[], int n) {
    // This function should be called Schönhage's algorithm, see [1].
    assert(__builtin_popcount(n) == 1);
    enum { Threshold = 32 };
    static_assert(Threshold >= 4, "If Threshold < 4, this algorithm will never halt.");
    if (n <= Threshold) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - i; ++j) ab[i + j] = (ab[i + j] + (ull)a[i] * b[j]) % MOD;
            for (int j = n - i; j < n; ++j)
                if ((ab[i + j - n] += MOD - (ull)a[i] * b[j] % MOD) >= MOD) ab[i + j - n] -= MOD;
        }
        return;
    }
    const int k     = __builtin_ctz(n);
    const int d     = 1 << (k / 2);
    const int delta = n / d;
    // R[x] / (x^(d * delta) + 1) -> (R[x][y] / (y^delta + 1)) / (y - x^d)
    // Lift to R[x][y] / (y^delta + 1)
    // Since polynomials in R[x][y] / (y^delta + 1) have x-degree < d,
    // We could map to (R[x] / (x^(2*d) + 1))[y] / (y^delta + 1)
    //   = (R[x] / (x^(2*d) + 1))[y] / (y^delta - x^(2*d)), delta <= 2*d
    //   = S[y] / (y^delta - x^(2*d)), where S = R[x] / (x^(2*d) + 1),
    // Since delta is a power of 2,
    //   = S[y] / (y^(delta/2) - x^d) × S[y] / (y^(delta/2) + x^d)
    //   = S[y] / (y^(delta/2) - x^d) × S[y] / (y^(delta/2) - x^(3d))
    std::vector<uint> a_hat(n * 2), b_hat(n * 2), ab_hat(n * 2);
    for (int i = 0; i < delta; ++i)
        for (int j = 0; j < d; ++j)
            a_hat[i * d * 2 + j] = a[i * d + j], b_hat[i * d * 2 + j] = b[i * d + j];
    FFT(data(a_hat), d * 2, delta, d * 2), FFT(data(b_hat), d * 2, delta, d * 2);
    for (int i = 0; i < delta; ++i)
        Schoenhage(data(a_hat) + i * d * 2, data(b_hat) + i * d * 2, data(ab_hat) + i * d * 2,
                   d * 2);
    InvFFT(data(ab_hat), d * 2, delta, d * 2);
    for (int i = 0; i < delta; ++i)
        for (int j = 0; j < d * 2; ++j)
            if (i * d + j < n) {
                if ((ab[i * d + j] += ab_hat[i * d * 2 + j]) >= MOD) ab[i * d + j] -= MOD;
            } else {
                if ((ab[i * d + j - n] += MOD - ab_hat[i * d * 2 + j]) >= MOD)
                    ab[i * d + j - n] -= MOD;
            }
}

// Compute ab mod (x^n - 1)
// ref: Schoenhage
void CyclicSchoenhage(const uint a[], const uint b[], uint ab[], int n) {
    assert(__builtin_popcount(n) == 1);
    enum { Threshold = 32 };
    static_assert(Threshold >= 4, "If Threshold < 4, this algorithm will never halt.");
    if (n <= Threshold) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - i; ++j) ab[i + j] = (ab[i + j] + (ull)a[i] * b[j]) % MOD;
            for (int j = n - i; j < n; ++j)
                ab[i + j - n] = (ab[i + j - n] + (ull)a[i] * b[j]) % MOD;
        }
        return;
    }
    const int k     = __builtin_ctz(n);
    const int d     = 1 << (k / 2);
    const int delta = n / d;
    // R[x] / (x^(d * delta) - 1) -> (R[x][y] / (y^delta - 1)) / (y - x^d)
    // Lift to R[x][y] / (y^delta - 1)
    // Map to (R[x] / (x^(2*d) + 1))[y] / (y^delta - 1)
    std::vector<uint> a_hat(n * 2), b_hat(n * 2), ab_hat(n * 2);
    for (int i = 0; i < delta; ++i)
        for (int j = 0; j < d; ++j)
            a_hat[i * d * 2 + j] = a[i * d + j], b_hat[i * d * 2 + j] = b[i * d + j];
    FFT(data(a_hat), d * 2, delta, 0), FFT(data(b_hat), d * 2, delta, 0);
    // Call the original Schönhage's algorithm (NOT CyclicSchoenhage).
    for (int i = 0; i < delta; ++i)
        Schoenhage(data(a_hat) + i * d * 2, data(b_hat) + i * d * 2, data(ab_hat) + i * d * 2,
                   d * 2);
    InvFFT(data(ab_hat), d * 2, delta, 0);
    for (int i = 0; i < delta; ++i)
        for (int j = 0; j < d * 2; ++j)
            if (i * d + j < n) {
                if ((ab[i * d + j] += ab_hat[i * d * 2 + j]) >= MOD) ab[i * d + j] -= MOD;
            } else {
                if ((ab[i * d + j - n] += ab_hat[i * d * 2 + j]) >= MOD) ab[i * d + j - n] -= MOD;
            }
}

std::vector<uint> Product(std::vector<uint> a, std::vector<uint> b) {
    if (empty(a) || empty(b)) return {};
    const int n = size(a), m = size(b);
    const int N = GetFFTSize(n + m - 1);
    a.resize(N), b.resize(N);
    std::vector<uint> ab(N);
    CyclicSchoenhage(data(a), data(b), data(ab), N);
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
