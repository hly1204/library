#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include "fps_basic.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

template <typename Tp>
inline int degree(const std::vector<Tp> &a) {
    int n = (int)a.size() - 1;
    while (n >= 0 && a[n] == 0) --n;
    return n;
}

template <typename Tp>
inline void shrink(std::vector<Tp> &a) {
    a.resize(degree(a) + 1);
}

template <typename Tp>
inline std::vector<Tp> taylor_shift(std::vector<Tp> a, Tp c) {
    const int n = a.size();
    auto &&bin  = Binomial<Tp>::get(n);
    for (int i = 0; i < n; ++i) a[i] *= bin.factorial(i);
    Tp cc = 1;
    std::vector<Tp> b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = cc * bin.inv_factorial(i);
        cc *= c;
    }
    std::reverse(a.begin(), a.end());
    auto ab = convolution(a, b);
    ab.resize(n);
    std::reverse(ab.begin(), ab.end());
    for (int i = 0; i < n; ++i) ab[i] *= bin.inv_factorial(i);
    return ab;
}

// returns (quotient, remainder)
template <typename Tp>
inline std::pair<std::vector<Tp>, std::vector<Tp>> euclidean_div(const std::vector<Tp> &A,
                                                                 const std::vector<Tp> &B) {
    // returns a mod (x^n-1)
    auto make_cyclic = [](const std::vector<Tp> &a, int n) {
        assert((n & (n - 1)) == 0);
        std::vector<Tp> b(n);
        for (int i = 0; i < (int)a.size(); ++i) b[i & (n - 1)] += a[i];
        return b;
    };

    const int degA = degree(A);
    const int degB = degree(B);
    assert(degB >= 0);
    // A = Q*B + R => A/B = Q + R/B in R((x^(-1)))
    const int degQ = degA - degB;
    if (degQ < 0) return {std::vector<Tp>{Tp(0)}, A};

    auto Q = div(std::vector(A.rend() - (degA + 1), A.rend()),
                 std::vector(B.rend() - (degB + 1), B.rend()), degQ + 1);
    std::reverse(Q.begin(), Q.end());

    const int len      = fft_len(std::max(degB, 1));
    const auto cyclicA = make_cyclic(A, len);
    auto cyclicB       = make_cyclic(B, len);
    auto cyclicQ       = make_cyclic(Q, len);

    fft(cyclicQ);
    fft(cyclicB);
    for (int i = 0; i < len; ++i) cyclicQ[i] *= cyclicB[i];
    inv_fft(cyclicQ);

    // R = A - QB mod (x^n-1) (n >= degB)
    std::vector<Tp> R(degB);
    for (int i = 0; i < degB; ++i) R[i] = cyclicA[i] - cyclicQ[i];
    return {Q, R};
}

template <typename Tp>
inline std::vector<Tp> euclidean_div_quotient(const std::vector<Tp> &A, const std::vector<Tp> &B) {
    const int degA = degree(A);
    const int degB = degree(B);
    assert(degB >= 0);
    // A = Q*B + R => A/B = Q + R/B in R((x^(-1)))
    const int degQ = degA - degB;
    if (degQ < 0) return {Tp(0)};

    auto Q = div(std::vector(A.rend() - (degA + 1), A.rend()),
                 std::vector(B.rend() - (degB + 1), B.rend()), degQ + 1);
    std::reverse(Q.begin(), Q.end());
    return Q;
}
