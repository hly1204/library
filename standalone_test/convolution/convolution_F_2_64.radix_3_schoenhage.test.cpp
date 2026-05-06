// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_F_2_64

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <smmintrin.h>
#include <utility>
#include <vector>
#include <wmmintrin.h>

// Requires +, -(both minus and negate), *, +=, -= for Tp
template<typename Tp> struct Radix3Schoenhage {
    static bool IsPowOf3(int a) {
        int b = 1;
        while (b < a) b *= 3;
        return a == b;
    }
    static int PowOf3(int e) {
        for (int x = 3, res = 1;; x *= x) {
            if (e & 1) res *= x;
            if ((e /= 2) == 0) return res;
        }
    }
    static int Log3Ceil(int a) {
        int e = 0;
        for (int c = 1; c < a; c *= 3) ++e;
        return e;
    }
    static int Log3Floor(int a) {
        const int e = Log3Ceil(a);
        return a == PowOf3(e) ? e : e - 1;
    }
    static void MultipliedByXToTheN(Tp a[], int d, int n) {
        // One could optimize this function to reduce some memory movement & calculation.
        if ((n %= d * 3) < 0) n += d * 3;
        const auto n_leq_d = [](Tp a[], int d, int n) {
            assert(n <= d);
            std::rotate(a, a + d * 2 - n, a + d * 2);
            for (int i = 0; i < n; ++i) a[i + d] += (a[i] = -a[i]);
        };
        for (; n >= d; n -= d) n_leq_d(a, d, d);
        if (n) n_leq_d(a, d, n);
    }
    static void FFT3(Tp a[], int d, int delta, int E) {
        assert(delta <= d);
        assert(E % delta == 0);
        if (delta == 1) return;
        const int n = d * 2 * (delta / 3);
        for (int i = 0; i < delta / 3; ++i) {
            Tp *const b[] = {a + i * d * 2, a + i * d * 2 + n, a + i * d * 2 + n * 2};
            for (int j = 1; j <= 2; ++j) MultipliedByXToTheN(b[j], d, E / 3 * j);
            for (int j = 0; j < d; ++j) {
                enum { L = 0, H = 1 };
                const Tp A[] = {b[0][j], b[0][j + d]};
                const Tp B[] = {b[1][j], b[1][j + d]};
                const Tp C[] = {b[2][j], b[2][j + d]};
                b[0][j]      = A[L] + B[L] + C[L];
                b[0][j + d]  = A[H] + B[H] + C[H];
                b[1][j]      = A[L] - B[H] - C[L] + C[H];
                b[1][j + d]  = A[H] + B[L] - B[H] - C[L];
                b[2][j]      = A[L] - B[L] + B[H] - C[H];
                b[2][j + d]  = A[H] - B[L] + C[L] - C[H];
            }
        }
        for (int i = 0; i < 3; ++i) FFT3(a + n * i, d, delta / 3, E / 3 + d * i);
    }
    static void FFT(Tp a[], int d, int delta) {
        Tp *const b = a + delta * 2 * d;
        for (int i = 0; i < delta; ++i) {
            Tp *const c[] = {a + i * d * 2, b + i * d * 2};
            for (int j = 0; j < d; ++j) {
                enum { L = 0, H = 1 };
                const Tp A[] = {c[0][j], c[0][j + d]};
                const Tp B[] = {c[1][j], c[1][j + d]};
                c[0][j]      = A[L] - B[H];
                c[0][j + d]  = A[H] + B[L] - B[H];
                c[1][j]      = A[L] - B[L] + B[H];
                c[1][j + d]  = A[H] - B[L];
            }
        }
        FFT3(a, d, delta, d), FFT3(b, d, delta, d * 2);
    }
    static void InvFFT3(Tp a[], int d, int delta, int E) {
        assert(delta <= d);
        assert(E % delta == 0);
        if (delta == 1) return;
        const int n = d * 2 * (delta / 3);
        for (int i = 0; i < 3; ++i) InvFFT3(a + n * i, d, delta / 3, E / 3 + d * i);
        for (int i = 0; i < delta / 3; ++i) {
            Tp *const b[] = {a + i * d * 2, a + i * d * 2 + n, a + i * d * 2 + n * 2};
            for (int j = 0; j < d; ++j) {
                enum { L = 0, H = 1 };
                const Tp A[] = {b[0][j], b[0][j + d]};
                const Tp B[] = {b[1][j], b[1][j + d]};
                const Tp C[] = {b[2][j], b[2][j + d]};
                b[0][j]      = A[L] + B[L] + C[L];
                b[0][j + d]  = A[H] + B[H] + C[H];
                b[1][j]      = A[L] - B[L] + B[H] - C[H];
                b[1][j + d]  = A[H] - B[L] + C[L] - C[H];
                b[2][j]      = A[L] - B[H] - C[L] + C[H];
                b[2][j + d]  = A[H] + B[L] - B[H] - C[L];
            }
            for (int j = 1; j <= 2; ++j) MultipliedByXToTheN(b[j], d, E / 3 * -j);
        }
    }
    static void InvFFT(Tp a[], int d, int delta) {
        Tp *const b = a + delta * 2 * d;
        InvFFT3(a, d, delta, d), InvFFT3(b, d, delta, d * 2);
        for (int i = 0; i < delta; ++i) {
            Tp *const c[] = {a + i * d * 2, b + i * d * 2};
            for (int j = 0; j < d; ++j) {
                enum { L = 0, H = 1 };
                const Tp A[] = {c[0][j], c[0][j + d]};
                const Tp B[] = {c[1][j], c[1][j + d]};
                c[0][j]      = A[L] + A[H] + B[L] + B[L] - B[H];
                c[0][j + d]  = -A[L] + A[H] + A[H] + B[L] + B[H];
                c[1][j]      = -A[L] + A[H] + A[H] + B[L] - B[H] - B[H];
                c[1][j + d]  = -A[L] - A[L] + A[H] + B[L] + B[L] - B[H];
            }
        }
    }
    // reduce #*, but it may be slower if cost of * is small.
    static int KaratsubaForNLeq3(const Tp a[], const Tp b[], Tp ab[], int n) {
        // see:
        // [1]: André Weimerskirch, Christof Paar:
        //      Generalizations of the Karatsuba Algorithm for Efficient Implementations.
        //      IACR Cryptol. ePrint Arch. 2006: 224 (2006)
        //      https://eprint.iacr.org/2006/224

        // ab mod (x^2 + x + 1), deg(a) < 2, deg(b) < 2
        const auto karatsuba_for_degree_1 = [](const Tp a[], const Tp b[], Tp ab[]) {
            const Tp D0  = a[0] * b[0];
            const Tp D1  = a[1] * b[1];
            const Tp D01 = (a[0] + a[1]) * (b[0] + b[1]);
            ab[0] += D0 - D1;
            ab[1] += D01 - D0 - D1 - D1;
        };
        // ab mod (x^6 + x^3 + 1), deg(a) < 6, deg(b) < 6
        const auto karatsuba_for_degree_5 = [](const Tp a[], const Tp b[], Tp ab[]) {
            // ab, deg(a) < 3, deg(b) < 3
            const auto karatsuba_for_degree_2 = [](const Tp a[], const Tp b[], Tp ab[]) {
                const Tp D0  = a[0] * b[0];
                const Tp D1  = a[1] * b[1];
                const Tp D2  = a[2] * b[2];
                const Tp D01 = (a[0] + a[1]) * (b[0] + b[1]);
                const Tp D02 = (a[0] + a[2]) * (b[0] + b[2]);
                const Tp D12 = (a[1] + a[2]) * (b[1] + b[2]);
                ab[0] += D0;
                ab[1] += D01 - D1 - D0;
                ab[2] += D02 - D2 - D0 + D1;
                ab[3] += D12 - D1 - D2;
                ab[4] += D2;
            };
            const Tp A01[] = {a[0] + a[3], a[1] + a[4], a[2] + a[5]};
            const Tp B01[] = {b[0] + b[3], b[1] + b[4], b[2] + b[5]};
            Tp D0[6], D1[6], D01[6];
            karatsuba_for_degree_2(a, b, D0);
            karatsuba_for_degree_2(a + 3, b + 3, D1);
            karatsuba_for_degree_2(A01, B01, D01);
            for (int i = 0; i < 6; ++i) D01[i] -= D0[i] + D1[i];
            MultipliedByXToTheN(D01, 3, 3);
            MultipliedByXToTheN(D1, 3, 6);
            for (int i = 0; i < 6; ++i) ab[i] += D0[i] + D01[i] + D1[i];
        };
        if (n == 1) {
            karatsuba_for_degree_1(a, b, ab);
        } else if (n == 3) {
            karatsuba_for_degree_5(a, b, ab);
        } else {
            __builtin_unreachable();
        }
        return 0;
    }
    // Compute 3^e * ab mod (x^(2*n) + x^n + 1) and return e
    static int Schoenhage(const Tp a[], const Tp b[], Tp ab[], int n) {
        assert(IsPowOf3(n));
        enum { Threshold = 3 }; // set Threshold as small as possible to reduce #*
        static_assert(Threshold >= 3);
        if (n <= Threshold) return KaratsubaForNLeq3(a, b, ab, n);
        const int k     = Log3Ceil(n);
        const int d     = PowOf3((k + 1) / 2);
        const int delta = n / d;
        std::vector<Tp> a_hat(n * 4), b_hat(n * 4), ab_hat(n * 4);
        for (int i = 0; i < delta * 2; ++i)
            for (int j = 0; j < d; ++j)
                a_hat[i * d * 2 + j] = a[i * d + j], b_hat[i * d * 2 + j] = b[i * d + j];
        FFT(data(a_hat), d, delta), FFT(data(b_hat), d, delta);
        int cnt;
        for (int i = 0; i < delta * 2; ++i)
            cnt = Schoenhage(data(a_hat) + i * d * 2, data(b_hat) + i * d * 2,
                             data(ab_hat) + i * d * 2, d);
        InvFFT(data(ab_hat), d, delta);
        for (int i = 0; i < delta * 2; ++i)
            for (int j = 0; j < d * 2; ++j)
                if (i * d + j < n * 2) {
                    ab[i * d + j] += ab_hat[i * d * 2 + j];
                } else if (i * d + j < n * 3) {
                    ab[i * d + j - n * 1] -= ab_hat[i * d * 2 + j];
                    ab[i * d + j - n * 2] -= ab_hat[i * d * 2 + j];
                } else {
                    __builtin_unreachable();
                }
        return cnt + delta + 1;
    }
    static std::pair<std::vector<Tp>, int> Product(std::vector<Tp> a, std::vector<Tp> b) {
        if (empty(a) || empty(b)) return {};
        const int n = size(a), m = size(b);
        int N = 1;
        while (N < n) N *= 3;
        while (N < m) N *= 3;
        a.resize(N * 2), b.resize(N * 2);
        std::vector<Tp> ab(N * 2);
        const int cnt = Schoenhage(data(a), data(b), data(ab), N);
        ab.resize(n + m - 1);
        return std::make_pair(std::move(ab), cnt);
    }
};

// Store P(x) mod (x^64 + x^4 + x^3 + x + 1)
class F_2_64 {
    std::uint64_t p = 0;

public:
    // clang-format off
    F_2_64 operator-() const { return *this; }
    F_2_64 &operator+=(const F_2_64 &r) { p ^= r.p; return *this; }
    F_2_64 &operator-=(const F_2_64 &r) { return operator+=(r); }
    // clang-format on
    [[gnu::target("pclmul,sse4.1")]] F_2_64 &operator*=(const F_2_64 &r) {
        // see:
        // https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=_mm_clmulepi64_si128&ig_expand=754
        __m128i v = _mm_clmulepi64_si128(_mm_set_epi64x(0, p), _mm_set_epi64x(0, r.p), 0);
        // see:
        // https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=_mm_extract_epi64&ig_expand=2931
        std::uint64_t low  = (std::uint64_t)_mm_extract_epi64(v, 0);
        std::uint64_t high = (std::uint64_t)_mm_extract_epi64(v, 1);
        enum : std::uint64_t { k = 0b11011 };
        // clang-format off
        static constexpr std::uint64_t t[] =
            { 0, k, k << 1, k ^ (k << 1), k << 2, k ^ (k << 2), (k << 1) ^ (k << 2), k ^ (k << 1) ^ (k << 2) };
        // clang-format on
        high ^= high << 1;
        p = low ^ high ^ (high << 3) ^ t[high >> 61];
        return *this;
    }
    friend F_2_64 operator+(const F_2_64 &l, const F_2_64 &r) { return F_2_64(l) += r; }
    friend F_2_64 operator-(const F_2_64 &l, const F_2_64 &r) { return F_2_64(l) -= r; }
    friend F_2_64 operator*(const F_2_64 &l, const F_2_64 &r) { return F_2_64(l) *= r; }
    friend std::istream &operator>>(std::istream &l, F_2_64 &r) { return l >> r.p; }
    friend std::ostream &operator<<(std::ostream &l, const F_2_64 &r) { return l << r.p; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<F_2_64> a(n), b(m);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];
    const auto [ab, cnt] = Radix3Schoenhage<F_2_64>::Product(std::move(a), std::move(b));
    for (int i = 0; i < n + m - 1; ++i) std::cout << ab[i] << ' ';
    return 0;
}
