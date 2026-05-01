// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod_2_64

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using ull = unsigned long long;

constexpr ull InvMod(int a) {
    ull res = 1;
    for (int i = 0; i < 6; ++i) res *= 2ULL - a * res;
    return res;
}

bool IsPowOf3(int a) {
    int b = 1;
    while (b < a) b *= 3;
    return a == b;
}

int PowOf3(int e) {
    int res = 1;
    for (int x = 3;; x *= x) {
        if (e & 1) res *= x;
        if ((e /= 2) == 0) return res;
    }
}

int Log3Ceil(int a) {
    int e = 0;
    for (int c = 1; c < a; c *= 3) ++e;
    return e;
}

int Log3Floor(int a) {
    const int e = Log3Ceil(a);
    return a == PowOf3(e) ? e : e - 1;
}

// Compute a * x^n mod (x^(2*d) + x^d + 1)
// Note that x^(3*d) = 1 mod (x^(2*d) + x^d + 1)
void MultipliedByXToTheN(ull a[], int d, int n) {
    if ((n %= d * 3) < 0) n += d * 3;
    const auto n_leq_d = [](ull a[], int d, int n) {
        assert(n <= d);
        std::rotate(a, a + d * 2 - n, a + d * 2);
        for (int i = 0; i < n; ++i) a[i + d] += (a[i] = -a[i]);
    };
    for (; n >= d; n -= d) n_leq_d(a, d, d);
    if (n) n_leq_d(a, d, n);
}

void FFT3(ull a[], int d, int delta, int E) {
    assert(delta <= d);
    assert(E % delta == 0);
    if (delta == 1) return;
    const int n = d * 2 * (delta / 3);
    for (int i = 0; i < delta / 3; ++i) {
        ull *const b[] = {a + i * d * 2, a + i * d * 2 + n, a + i * d * 2 + n * 2};
        MultipliedByXToTheN(b[1], d, E / 3 * 1);
        MultipliedByXToTheN(b[2], d, E / 3 * 2);
        for (int j = 0; j < d; ++j) {
            enum { L = 0, H = 1 };
            const ull A[] = {b[0][j + 0], b[0][j + d]};
            const ull B[] = {b[1][j + 0], b[1][j + d]};
            const ull C[] = {b[2][j + 0], b[2][j + d]};
            b[0][j + 0]   = A[L] + B[L] + C[L];
            b[0][j + d]   = A[H] + B[H] + C[H];
            b[1][j + 0]   = A[L] - B[H] - C[L] + C[H];
            b[1][j + d]   = A[H] + B[L] - B[H] - C[L];
            b[2][j + 0]   = A[L] - B[L] + B[H] - C[H];
            b[2][j + d]   = A[H] - B[L] + C[L] - C[H];
        }
    }
    for (int i = 0; i < 3; ++i) FFT3(a + n * i, d, delta / 3, E / 3 + d * i);
}

// (R[x] / (x^(2*d) + x^(d) + 1))[y] / (y^(2*delta) + y^(delta) + 1)
//   -> (R[x] / (x^(2*d) + x^d + 1))[y] / (y^delta - x^d)
//   ×  (R[x] / (x^(2*d) + x^d + 1))[y] / (y^delta - x^(2*d))
// then apply radix-3 FFT over (R[x] / (x^(2*d) + x^d + 1))[y] / (y^delta - x^d)
//                    and over (R[x] / (x^(2*d) + x^d + 1))[y] / (y^delta - x^(2*d))
void FFT(ull a[], int d, int delta) {
    ull *const b = a + delta * 2 * d;
    for (int i = 0; i < delta; ++i) {
        ull *const c[] = {a + i * d * 2, b + i * d * 2};
        for (int j = 0; j < d; ++j) {
            enum { L = 0, H = 1 };
            const ull A[] = {c[0][j], c[0][j + d]};
            const ull B[] = {c[1][j], c[1][j + d]};
            c[0][j]       = A[L] - B[H];
            c[0][j + d]   = A[H] + B[L] - B[H];
            c[1][j]       = A[L] - B[L] + B[H];
            c[1][j + d]   = A[H] - B[L];
        }
    }
    // a[] stores S[y] / (y^delta - x^d), b[] stores S[y] / (y^delta - x^(2*d))
    FFT3(a, d, delta, d), FFT3(b, d, delta, d * 2);
}

void InvFFT3(ull a[], int d, int delta, int E) {
    assert(delta <= d);
    assert(E % delta == 0);
    if (delta == 1) return;
    const int n = d * 2 * (delta / 3);
    for (int i = 0; i < 3; ++i) InvFFT3(a + n * i, d, delta / 3, E / 3 + d * i);
    for (int i = 0; i < delta / 3; ++i) {
        ull *const b[] = {a + i * d * 2, a + i * d * 2 + n, a + i * d * 2 + n * 2};
        for (int j = 0; j < d; ++j) {
            enum { L = 0, H = 1 };
            const ull A[] = {b[0][j + 0], b[0][j + d]};
            const ull B[] = {b[1][j + 0], b[1][j + d]};
            const ull C[] = {b[2][j + 0], b[2][j + d]};
            b[0][j + 0]   = A[L] + B[L] + C[L];
            b[0][j + d]   = A[H] + B[H] + C[H];
            b[1][j + 0]   = A[L] - B[L] + B[H] - C[H];
            b[1][j + d]   = A[H] - B[L] + C[L] - C[H];
            b[2][j + 0]   = A[L] - B[H] - C[L] + C[H];
            b[2][j + d]   = A[H] + B[L] - B[H] - C[L];
        }
        MultipliedByXToTheN(b[1], d, E / 3 * -1);
        MultipliedByXToTheN(b[2], d, E / 3 * -2);
    }
}

void InvFFT(ull a[], int d, int delta) {
    ull *const b = a + delta * 2 * d;
    InvFFT3(a, d, delta, d), InvFFT3(b, d, delta, d * 2);
    const ull inv_3_delta = InvMod(delta * 3);
    for (int i = 0; i < delta; ++i) {
        ull *const c[] = {a + i * d * 2, b + i * d * 2};
        for (int j = 0; j < d; ++j) {
            enum { L = 0, H = 1 };
            const ull A[] = {c[0][j] * inv_3_delta, c[0][j + d] * inv_3_delta};
            const ull B[] = {c[1][j] * inv_3_delta, c[1][j + d] * inv_3_delta};
            c[0][j]       = A[L] + A[H] + B[L] + B[L] - B[H];
            c[0][j + d]   = -A[L] + A[H] + A[H] + B[L] + B[H];
            c[1][j]       = -A[L] + A[H] + A[H] + B[L] - B[H] - B[H];
            c[1][j + d]   = -A[L] - A[L] + A[H] + B[L] + B[L] - B[H];
        }
    }
}

// Compute ab mod (x^(2*n) + x^n + 1)
// see:
// [1]: Daniel J. Bernstein. "Multidigit multiplication for mathematicians."
//      Accepted to Advances in Applied Mathematics,
//      but withdrawn by author to prevent irreparable mangling by Academic Press.
//      https://cr.yp.to/papers.html#m3
void Schoenhage(const ull a[], const ull b[], ull ab[], int n) {
    assert(IsPowOf3(n));
    enum { Threshold = 3 * 3 * 3 };
    static_assert(Threshold >= 3);
    if (n <= Threshold) {
        // (a[L] + a[H]*x^n) * (b[L] + b[H]*x^n)
        //   = (a[L]*b[L]) + (a[L]*b[H] + a[H]*b[L])*x^n + a[H]*b[H]*(-x^n - 1))
        for (int i = 0; i < n; ++i) {
            enum { L = 0, H = 1 };
            const ull A[] = {a[i], a[i + n]};
            for (int j = 0; j < n; ++j) {
                const ull B[]  = {b[j], b[j + n]};
                const ull ALBL = A[L] * B[L];
                const ull AHBH = A[H] * B[H];
                const ull c    = (A[L] + A[H]) * (B[L] + B[H]) - ALBL - AHBH;
                if (i + j < n) {
                    ab[i + j] += ALBL - AHBH;
                    ab[i + j + n] += c - AHBH;
                } else {
                    ab[i + j] += ALBL - c;
                    ab[i + j - n] -= c - AHBH;
                }
            }
        }
        return;
    }
    const int k     = Log3Ceil(n);
    const int d     = PowOf3((k + 1) / 2);
    const int delta = n / d;
    // R[x] / (x^(2 * d * delta) + x^(d * delta) + 1) ->
    //   (R[x][y] / (y^(2 * delta) + y^delta + 1)) / (y - x^d)
    // Lift to R[x][y] / (y^(2 * delta) + y^delta + 1)
    // Since polynomials in R[x][y] / (y^(2*delta) + y^delta + 1) have x-degree < d
    // We could map to (R[x] / (x^(2*d) + x^d + 1))[y] / (y^(2*delta) + y^delta + 1)
    std::vector<ull> a_hat(n * 4), b_hat(n * 4), ab_hat(n * 4);
    for (int i = 0; i < delta * 2; ++i)
        for (int j = 0; j < d; ++j)
            a_hat[i * d * 2 + j] = a[i * d + j], b_hat[i * d * 2 + j] = b[i * d + j];
    FFT(data(a_hat), d, delta), FFT(data(b_hat), d, delta);
    for (int i = 0; i < delta * 2; ++i)
        Schoenhage(data(a_hat) + i * d * 2, data(b_hat) + i * d * 2, data(ab_hat) + i * d * 2, d);
    InvFFT(data(ab_hat), d, delta);
    for (int i = 0; i < delta * 2; ++i)
        for (int j = 0; j < d * 2; ++j)
            if (i * d + j < n * 2) {
                ab[i * d + j] += ab_hat[i * d * 2 + j];
            } else if (i * d + j < n * 3) {
                // x^(2*n) = -x^n - 1
                ab[i * d + j - n * 1] -= ab_hat[i * d * 2 + j];
                ab[i * d + j - n * 2] -= ab_hat[i * d * 2 + j];
            } else {
                ab[i * d + j - n * 3] += ab_hat[i * d * 2 + j];
            }
}

std::vector<ull> Product(std::vector<ull> a, std::vector<ull> b) {
    if (empty(a) || empty(b)) return {};
    const int n = size(a), m = size(b);
    int N = 1;
    while (N < n) N *= 3;
    while (N < m) N *= 3;
    a.resize(N * 2), b.resize(N * 2);
    std::vector<ull> ab(N * 2);
    Schoenhage(data(a), data(b), data(ab), N);
    ab.resize(n + m - 1);
    return ab;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<ull> a(n), b(m);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];
    const auto ab = Product(std::move(a), std::move(b));
    for (int i = 0; i < n + m - 1; ++i) std::cout << ab[i] << ' ';
    return 0;
}
