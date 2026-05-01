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

// Let S := (R[x] / (x^(2*d) + x^d + 1)),
// Compute S[y] / (y^delta - x^(E_MULTIPLIER * 1 * d))
//   -> S[y] / (y^(delta/3) - x^(E_MULTIPLIER * 1 * d/3))
//   ×  S[y] / (y^(delta/3) - x^(E_MULTIPLIER * 4 * d/3))
//   ×  S[y] / (y^(delta/3) - x^(E_MULTIPLIER * 7 * d/3))
// ...
template<int E_MULTIPLIER> void FFT_(ull a[], int d, int delta) {
    static_assert(E_MULTIPLIER == 1 || E_MULTIPLIER == 2);
    assert(delta <= d);
    for (int i = delta; i >= 3; i /= 3) {
        const int block = delta / i;
        std::vector<int> e(block);
        for (int j = e[0] = 1; j < block; ++j)
            e[j] = e[j - PowOf3(Log3Floor(j))] + block / PowOf3(Log3Floor(j));
        for (int j = 0; j < block; ++j) {
            const int o  = e[j] * (d / (block * 3)) % (d * 3);
            const int n  = d * 2 * (i / 3);
            ull *const b = a + j * n * 3;
            for (int k = 0; k < i / 3; ++k) {
                ull *const c[] = {b + n * 0 + k * d * 2, b + n * 1 + k * d * 2,
                                  b + n * 2 + k * d * 2};
                MultipliedByXToTheN(c[1], d, o * 1 * E_MULTIPLIER);
                MultipliedByXToTheN(c[2], d, o * 2 * E_MULTIPLIER);
                for (int l = 0; l < d; ++l) {
                    enum { L = 0, H = 1 };
                    const ull A[] = {c[0][l], c[0][l + d]};
                    const ull B[] = {c[1][l], c[1][l + d]};
                    const ull C[] = {c[2][l], c[2][l + d]};
                    if constexpr (E_MULTIPLIER == 1) {
                        // [1 0  1  0  1  0] [ A[L] ]
                        // [0 1  0  1  0  1] [ A[H] ]
                        // [1 0  0 -1 -1  1] [ B[L] ]
                        // [0 1  1 -1 -1  0] [ B[H] ]
                        // [1 0 -1  1  0 -1] [ C[L] ]
                        // [0 1 -1  0  1 -1] [ C[H] ]
                        c[0][l]     = A[L] + B[L] + C[L];
                        c[0][l + d] = A[H] + B[H] + C[H];
                        c[1][l]     = A[L] - B[H] - C[L] + C[H];
                        c[1][l + d] = A[H] + B[L] - B[H] - C[L];
                        c[2][l]     = A[L] - B[L] + B[H] - C[H];
                        c[2][l + d] = A[H] - B[L] + C[L] - C[H];
                    } else if constexpr (E_MULTIPLIER == 2) {
                        // [1 0  1  0  1  0] [ A[L] ]
                        // [0 1  0  1  0  1] [ A[H] ]
                        // [1 0 -1  1  0 -1] [ B[L] ]
                        // [0 1 -1  0  1 -1] [ B[H] ]
                        // [1 0  0 -1 -1  1] [ C[L] ]
                        // [0 1  1 -1 -1  0] [ C[H] ]
                        c[0][l]     = A[L] + B[L] + C[L];
                        c[0][l + d] = A[H] + B[H] + C[H];
                        c[1][l]     = A[L] - B[L] + B[H] - C[H];
                        c[1][l + d] = A[H] - B[L] + C[L] - C[H];
                        c[2][l]     = A[L] - B[H] - C[L] + C[H];
                        c[2][l + d] = A[H] + B[L] - B[H] - C[L];
                    }
                }
            }
        }
    }
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
    FFT_<1>(a, d, delta), FFT_<2>(b, d, delta);
}

template<int E_MULTIPLIER> void InvFFT_(ull a[], int d, int delta) {
    static_assert(E_MULTIPLIER == 1 || E_MULTIPLIER == 2);
    assert(delta <= d);
    for (int i = 3; i <= delta; i *= 3) {
        const int block = delta / i;
        std::vector<int> e(block);
        for (int j = e[0] = 1; j < block; ++j)
            e[j] = e[j - PowOf3(Log3Floor(j))] + block / PowOf3(Log3Floor(j));
        for (int j = 0; j < block; ++j) {
            const int o  = e[j] * (d / (block * 3)) % (d * 3);
            const int n  = d * 2 * (i / 3);
            ull *const b = a + j * n * 3;
            for (int k = 0; k < i / 3; ++k) {
                ull *const c[] = {b + n * 0 + k * d * 2, b + n * 1 + k * d * 2,
                                  b + n * 2 + k * d * 2};
                for (int l = 0; l < d; ++l) {
                    enum { L = 0, H = 1 };
                    const ull A[] = {c[0][l], c[0][l + d]};
                    const ull B[] = {c[1][l], c[1][l + d]};
                    const ull C[] = {c[2][l], c[2][l + d]};
                    // Find the inverse matrix in FFT
                    if constexpr (E_MULTIPLIER == 1) {
                        c[0][l]     = A[L] + B[L] + C[L];
                        c[0][l + d] = A[H] + B[H] + C[H];
                        c[1][l]     = A[L] - B[L] + B[H] - C[H];
                        c[1][l + d] = A[H] - B[L] + C[L] - C[H];
                        c[2][l]     = A[L] - B[H] - C[L] + C[H];
                        c[2][l + d] = A[H] + B[L] - B[H] - C[L];
                    } else if constexpr (E_MULTIPLIER == 2) {
                        c[0][l]     = A[L] + B[L] + C[L];
                        c[0][l + d] = A[H] + B[H] + C[H];
                        c[1][l]     = A[L] - B[H] - C[L] + C[H];
                        c[1][l + d] = A[H] + B[L] - B[H] - C[L];
                        c[2][l]     = A[L] - B[L] + B[H] - C[H];
                        c[2][l + d] = A[H] - B[L] + C[L] - C[H];
                    }
                }
                MultipliedByXToTheN(c[1], d, o * -1 * E_MULTIPLIER);
                MultipliedByXToTheN(c[2], d, o * -2 * E_MULTIPLIER);
            }
        }
    }
    const ull inv_delta = InvMod(delta);
    for (int i = 0; i < d * 2 * delta; ++i) a[i] *= inv_delta;
}

void InvFFT(ull a[], int d, int delta) {
    ull *const b = a + delta * 2 * d;
    InvFFT_<1>(a, d, delta), InvFFT_<2>(b, d, delta);
    const ull inv_3 = InvMod(3);
    for (int i = 0; i < delta; ++i) {
        ull *const c[] = {a + i * d * 2, b + i * d * 2};
        for (int j = 0; j < d; ++j) {
            enum { L = 0, H = 1 };
            const ull A[] = {c[0][j] * inv_3, c[0][j + d] * inv_3};
            const ull B[] = {c[1][j] * inv_3, c[1][j + d] * inv_3};
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
                const ull B[] = {b[j], b[j + n]};
                ab[i + j] += A[L] * B[L];
                ab[i + j] -= A[H] * B[H];
                const ull c = A[L] * B[H] + A[H] * B[L] - A[H] * B[H];
                if (i + j < n) {
                    ab[i + j + n] += c;
                } else {
                    ab[i + j] -= c;
                    ab[i + j - n] -= c;
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
