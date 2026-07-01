#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <utility>
#include <vector>

inline namespace Schoenhage {
namespace detail {
// Compute a * x^n mod (x^d + 1)
// Note that x^(2*d) = 1 mod (x^d + 1)
template<typename Tp, int d> inline void multiplied_by_x_to_the_n(Tp a[], int n) {
    if ((n %= d * 2) < 0) n += d * 2;
    const auto n_leq_d = [](Tp a[], int n) {
        assert(n <= d);
        std::rotate(a, a + d - n, a + d);
        for (int i = 0; i < n; ++i) a[i] = -a[i];
    };
    for (; n >= d; n -= d) n_leq_d(a, d);
    if (n) n_leq_d(a, n);
}

template<typename Tp, int d, int delta> inline void butterfly(Tp a[], int e) {
    static_assert(delta <= d);
    if constexpr (delta != 0) assert(e % delta == 0);
    if constexpr (delta == 1) return;
    constexpr int n = d * (delta / 2);
    for (int i = 0; i < delta / 2; ++i) {
        Tp *const b[] = {a + i * d, a + i * d + n};
        multiplied_by_x_to_the_n<Tp, d>(b[1], e / 2);
        for (int j = 0; j < d; ++j) {
            const Tp u = b[0][j];
            b[0][j] += b[1][j], b[1][j] = u - b[1][j];
        }
    }
    butterfly<Tp, d, delta / 2>(a, e / 2);
    butterfly<Tp, d, delta / 2>(a + n, e / 2 + d);
}

template<typename Tp, int d, int delta> inline void inv_butterfly(Tp a[], int e) {
    static_assert(delta <= d);
    if constexpr (delta != 0) assert(e % delta == 0);
    if constexpr (delta == 1) return;
    constexpr int n = d * (delta / 2);
    inv_butterfly<Tp, d, delta / 2>(a, e / 2);
    inv_butterfly<Tp, d, delta / 2>(a + n, e / 2 + d);
    for (int i = 0; i < delta / 2; ++i) {
        Tp *const b[] = {a + i * d, a + i * d + n};
        for (int j = 0; j < d; ++j) {
            const Tp u = b[0][j];
            b[0][j] += b[1][j], b[1][j] = u - b[1][j];
        }
        multiplied_by_x_to_the_n<Tp, d>(b[1], -e / 2);
    }
}
} // namespace detail

// Apply radix-2 FFT over (R[x] / (x^d + 1))[y] / (y^delta - x^e)
template<typename Tp, int d, int delta> inline void fft(Tp a[], int e) {
    detail::butterfly<Tp, d, delta>(a, e);
}

// Constraints: 1/2 in R
template<typename Tp, int d, int delta> inline void inv_fft(Tp a[], int e) {
    detail::inv_butterfly<Tp, d, delta>(a, e);
    const Tp inv_delta = Tp(delta).inv();
    for (int i = 0; i < d * delta; ++i) a[i] *= inv_delta;
}

namespace detail {
// Compute ab mod (x^n + 1)
template<typename Tp, int n> inline void mul_inplace(Tp a[], const Tp b[]) {
    static_assert(__builtin_popcount(n) == 1);
    enum { Threshold = 32 };
    static_assert(Threshold >= 4, "If Threshold < 4, this algorithm will never halt.");
    if constexpr (n <= Threshold) {
        std::array<Tp, n> ab;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - i; ++j) ab[i + j] += a[i] * b[j];
            for (int j = n - i; j < n; ++j) ab[i + j - n] -= a[i] * b[j];
        }
        std::copy(begin(ab), end(ab), a);
        return;
    }
    constexpr int k = __builtin_ctz(n), d = 1 << (k / 2), delta = n / d;
    std::vector<Tp> a_hat(n * 2), b_hat(n * 2);
    for (int i = 0; i < delta; ++i)
        for (int j = 0; j < d; ++j)
            a_hat[i * d * 2 + j] = a[i * d + j], b_hat[i * d * 2 + j] = b[i * d + j];
    fft<Tp, d * 2, delta>(data(a_hat), d * 2), fft<Tp, d * 2, delta>(data(b_hat), d * 2);
    for (int i = 0; i < delta; ++i)
        mul_inplace<Tp, d * 2>(data(a_hat) + i * d * 2, data(b_hat) + i * d * 2);
    inv_fft<Tp, d * 2, delta>(data(a_hat), d * 2);
    std::fill(a, a + n, Tp());
    for (int i = 0; i < delta; ++i)
        for (int j = 0; j < d * 2; ++j)
            if (i * d + j < n) a[i * d + j] += a_hat[i * d * 2 + j];
            else { a[i * d + j - n] -= a_hat[i * d * 2 + j]; }
}
// clang-format off
template<typename Tp, int... Is>
inline void mul_inplace_helper(Tp a[], const Tp b[], int n, std::integer_sequence<int, Is...>)
{ ([&] { if (n == (1 << Is)) mul_inplace<Tp, (1 << Is)>(a, b); }(), ...); }
// clang-format on
} // namespace detail

template<typename Tp> inline void mul_inplace(Tp a[], const Tp b[], int n) {
    detail::mul_inplace_helper(a, b, n, std::make_integer_sequence<int, 22>{});
}
} // namespace Schoenhage

namespace detail {
template<typename Tp>
inline std::vector<Tp> convolution_naive(const std::vector<Tp> &a, const std::vector<Tp> &b) {
    if (empty(a) || empty(b)) return {};
    const int m = size(a), n = size(b);
    std::vector<Tp> ab(m + n - 1);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) ab[i + j] += a[i] * b[j];
    return ab;
}

template<typename Tp> inline std::vector<Tp> convolution_fft(std::vector<Tp> a, std::vector<Tp> b) {
    if (empty(a) || empty(b)) return {};
    const int m = size(a), n = size(b);
    int len = 1;
    while (len < m + n - 1) len *= 2;
    a.resize(len), b.resize(len);
    mul_inplace(data(a), data(b), len);
    a.resize(m + n - 1);
    return a;
}
} // namespace detail

template<typename Tp> inline auto is_zero(const Tp &v) noexcept(noexcept(v.is_zero()))
    -> decltype(v.is_zero()) {
    return v.is_zero();
}

template<typename Tp> inline std::vector<Tp> trunc(const std::vector<Tp> &a, int R) {
    std::vector<Tp> b(R);
    for (int i = 0; i < std::min(R, (int)size(a)); ++i) b[i] = a[i];
    return b;
}

template<typename Tp> inline std::vector<Tp> slice(const std::vector<Tp> &a, int L, int R) {
    std::vector<Tp> b(R - L);
    for (int i = L; i < std::min(R, (int)size(a)); ++i) b[i - L] = a[i];
    return b;
}

template<typename Tp>
inline std::vector<Tp> convolution(const std::vector<Tp> &a, const std::vector<Tp> &b) {
    if (std::min(size(a), size(b)) < 60) return detail::convolution_naive(a, b);
    return detail::convolution_fft(a, b);
}

template<typename Tp> inline int order(const std::vector<Tp> &a) {
    for (int i = 0; i < (int)size(a); ++i)
        if (!is_zero(a[i])) return i;
    return -1;
}

template<typename Tp> inline std::vector<Tp> fps_inv(const std::vector<Tp> &A, int n) {
    assert(order(A) == 0);
    int N = 1;
    while (N < n) N *= 2;
    std::vector<Tp> invA = {A[0].inv()};
    invA.reserve(N);
    while ((int)size(invA) < N) {
        const int len = (int)size(invA);
        invA.resize(len * 2);
        std::vector<Tp> A_hat = trunc(A, len * 2);
        mul_inplace(data(A_hat), data(invA), len * 2);
        fill(begin(A_hat), begin(A_hat) + len, Tp());
        mul_inplace(data(A_hat), data(invA), len * 2);
        for (int i = len; i < len * 2; ++i) invA[i] = -A_hat[i];
    }
    invA.resize(n);
    return invA;
}

template<typename Tp>
inline std::vector<Tp> fps_div(const std::vector<Tp> &A, const std::vector<Tp> &B, int n) {
    if (n == 0) return {};
    if (n == 1) return {A[0] / B[0]};
    int N = 1;
    while (N < n) N *= 2;
    std::vector<Tp> AdivB(N), invB = fps_inv(B, N / 2), A_hat = trunc(A, N / 2);
    invB.resize(N), A_hat.resize(N);
    mul_inplace(data(A_hat), data(invB), N);
    copy(begin(A_hat), begin(A_hat) + N / 2, begin(AdivB));
    mul_inplace(data(A_hat), data(trunc(B, N)), N);
    fill(begin(A_hat), begin(A_hat) + N / 2, Tp());
    for (int i = N / 2; i < N; ++i) A_hat[i] -= A[i];
    mul_inplace(data(A_hat), data(invB), N);
    for (int i = N / 2; i < N; ++i) AdivB[i] = -A_hat[i];
    AdivB.resize(n);
    return AdivB;
}

template<typename Tp> inline int degree(const std::vector<Tp> &a) {
    int n = (int)size(a) - 1;
    while (n >= 0 && is_zero(a[n])) --n;
    return n;
}

template<typename Tp> inline void shrink(std::vector<Tp> &a) { a.resize(degree(a) + 1); }

template<typename Tp> inline std::array<std::vector<Tp>, 2>
euclidean_div_naive(const std::vector<Tp> &A, const std::vector<Tp> &B) {
    const int degA = degree(A), degB = degree(B), degQ = degA - degB;
    assert(degB >= 0);
    if (degQ < 0) return {std::vector<Tp>{Tp()}, A};
    std::vector<Tp> Q(degQ + 1), R = A;
    const Tp inv = B[degB].inv();
    for (int i = degQ, n = degA; i >= 0; --i)
        if (!is_zero(Q[i] = R[n--] * inv))
            for (int j = 0; j <= degB; ++j) R[i + j] -= Q[i] * B[j];
    R.resize(degB);
    return {Q, R};
}

template<typename Tp> inline std::vector<Tp>
euclidean_div_quotient_naive(const std::vector<Tp> &A, const std::vector<Tp> &B) {
    const int degA = degree(A), degB = degree(B), degQ = degA - degB;
    assert(degB >= 0);
    if (degQ < 0) return {Tp()};
    const Tp inv = B[degB].inv();
    std::vector<Tp> Q(degQ + 1);
    for (int i = 0; i <= degQ; ++i) {
        for (int j = 1; j <= std::min(i, degB); ++j) Q[degQ - i] += B[degB - j] * Q[degQ - i + j];
        Q[degQ - i] = (A[degA - i] - Q[degQ - i]) * inv;
    }
    return Q;
}

template<typename Tp> inline std::array<std::vector<Tp>, 2>
euclidean_div(const std::vector<Tp> &A, const std::vector<Tp> &B) {
    const int degA = degree(A), degB = degree(B), degQ = degA - degB;
    assert(degB >= 0);
    if (degQ < 0) return {std::vector<Tp>{Tp()}, A};
    if (degQ < 60 || degB < 60) return euclidean_div_naive(A, B);
    std::vector Q = fps_div(std::vector(rend(A) - (degA + 1), rend(A)),
                            std::vector(rend(B) - (degB + 1), rend(B)), degQ + 1);
    reverse(begin(Q), end(Q));
    const auto make_cyclic = [](const std::vector<Tp> &a, int n) {
        assert((n & (n - 1)) == 0);
        std::vector<Tp> b(n);
        for (int i = 0; i < (int)size(a); ++i) b[i & (n - 1)] += a[i];
        return b;
    };
    int N = 1;
    while (N < degB) N *= 2;
    const std::vector cyclicA = make_cyclic(A, N);
    const std::vector cyclicB = make_cyclic(B, N);
    std::vector cyclicQ       = make_cyclic(Q, N);
    mul_inplace(data(cyclicQ), data(cyclicB), N);
    std::vector<Tp> R(degB);
    for (int i = 0; i < degB; ++i) R[i] = cyclicA[i] - cyclicQ[i];
    return {Q, R};
}

template<typename Tp>
inline std::vector<Tp> euclidean_div_quotient(const std::vector<Tp> &A, const std::vector<Tp> &B) {
    const int degA = degree(A), degB = degree(B), degQ = degA - degB;
    assert(degB >= 0);
    if (degQ < 0) return {Tp()};
    if (std::min(degQ, degB) < 60) return euclidean_div_quotient_naive(A, B);
    std::vector Q = fps_div(std::vector(rend(A) - (degA + 1), rend(A)),
                            std::vector(rend(B) - (degB + 1), rend(B)), degQ + 1);
    reverse(begin(Q), end(Q));
    return Q;
}
