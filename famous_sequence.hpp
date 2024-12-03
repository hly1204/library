#pragma once

#include "fft.hpp"
#include "fps_basic.hpp"
#include "fps_composition.hpp"
#include "fps_polya.hpp"
#include "poly_basic.hpp"
#include "pow_table.hpp"
#include <cassert>
#include <vector>

// returns P([0..n)) s.t. P(n)=#(ways writing an integer n as sum of positive integers)
// see: https://mathworld.wolfram.com/PartitionFunctionP.html
// see also Pentagonal number
template <typename Tp>
inline std::vector<Tp> partition_function(int n) {
    assert(n >= 0);
    std::vector<Tp> I(n);
    for (int i = 1; i < n; ++i) I[i] = 1;
    return polya_exp(I, n);
}

// returns |s(n,0)|, ..., |s(n,n)|
// unsigned Stirling numbers of the first kind
template <typename Tp>
inline std::vector<Tp> unsigned_stirling_numbers_1st_row(int n) {
    assert(n >= 0);
    if (n == 0) return {Tp(1)};
    int mask = 1 << 30;
    while ((mask & n) == 0) mask >>= 1;
    std::vector<Tp> res{Tp(0), Tp(1)};
    for (int d = 1; d != n;) {
        res = convolution(res, taylor_shift(res, Tp(d)));
        d <<= 1;
        if ((mask >>= 1) & n) {
            res = convolution(res, std::vector<Tp>{Tp(d), Tp(1)});
            d |= 1;
        }
    }
    return res;
}

// returns |s(0,k)|, ..., |s(n-1,k)|
template <typename Tp>
inline std::vector<Tp> unsigned_stirling_numbers_1st_column(int k, int n) {
    assert(n >= 0);
    auto &&bin = Binomial<Tp>::get(n);
    std::vector<Tp> I(n);
    for (int i = 1; i < n; ++i) I[i] = bin.inv(i);
    auto res = fps_pow(I, k, n);
    Tp v     = 1;
    for (int i = 1; i <= k; ++i) v *= i;
    v = v.inv();
    for (int i = 0; i < n; ++i) res[i] *= bin.factorial(i) * v;
    return res;
}

// returns s(0,k), ..., s(n-1,k)
template <typename Tp>
inline std::vector<Tp> signed_stirling_numbers_1st_column(int k, int n) {
    auto S = unsigned_stirling_numbers_1st_column<Tp>(k, n);
    for (int i = 0; i < n; ++i)
        if ((k - i) & 1) S[i] = -S[i];
    return S;
}

// returns s(n,0), ..., s(n,n)
template <typename Tp>
inline std::vector<Tp> signed_stirling_numbers_1st_row(int n) {
    auto S = unsigned_stirling_numbers_1st_row<Tp>(n);
    for (int i = 0; i <= n; ++i)
        if ((n - i) & 1) S[i] = -S[i];
    return S;
}

// returns S(n,0), ..., S(n,n)
template <typename Tp>
inline std::vector<Tp> stirling_numbers_2nd_row(int n) {
    assert(n >= 0);
    std::vector<Tp> res(n + 1), R(n + 1);
    auto &&bin   = Binomial<Tp>::get(n + 1);
    const auto T = pow_table<Tp>(n, n + 1);
    for (int i = 0; i <= n; ++i) {
        R[i] = T[i] * (res[i] = bin.inv_factorial(i));
        if (i & 1) res[i] = -res[i];
    }
    res = convolution(res, R);
    res.resize(n + 1);
    return res;
}

// returns S(0,k), ..., S(n-1,k)
template <typename Tp>
inline std::vector<Tp> stirling_numbers_2nd_column(int k, int n) {
    assert(n >= 0);
    if (n == 0) return {};
    if (n <= k) return std::vector<Tp>(n);
    if (k == 0) {
        std::vector<Tp> res(n);
        res[0] = 1;
        return res;
    }
    int mask = 1 << 30;
    while ((mask & k) == 0) mask >>= 1;
    std::vector<Tp> res{Tp(-1), Tp(1)};
    for (int d = 1; d != k;) {
        res = convolution(res, taylor_shift(res, -Tp(d)));
        d <<= 1;
        if ((mask >>= 1) & k) res = convolution(res, std::vector<Tp>{-Tp(d |= 1), Tp(1)});
    }
    res = fps_inv(std::vector(res.rbegin(), res.rend()), n - k);
    res.insert(res.begin(), k, Tp(0));
    return res;
}

// Eulerian numbers (OEIS) https://oeis.org/wiki/Eulerian_numbers,_triangle_of
// returns A(n,0), ..., A(n,n)
template <typename Tp>
inline std::vector<Tp> eulerian_numbers_row(int n) {
    std::vector<Tp> A(n + 1);
    for (int i = 0; i <= n; ++i) A[i] = Tp(i + 1).pow(n);
    auto AA = convolution(A, fps_pow(std::vector{Tp(1), Tp(-1)}, n + 1, n + 1));
    AA.resize(n + 1);
    return AA;
}

// returns A(0,k), ..., A(m-1,k)
// see:
// [1]: Entropy Increaser. 平移指数基变换.
//      https://blog.csdn.net/EI_Captain/article/details/108586699
template <typename Tp>
inline std::vector<Tp> eulerian_numbers_column(int k, int m) {
    std::vector<Tp> A(k + 1), B(k + 1);
    auto &&bin = Binomial<Tp>::get(std::max(k + 1, m));
    for (int i = 0; i <= k; ++i) A[k - i] = Tp(-i - 1).pow(k - i) * bin.inv_factorial(k - i);
    for (int i = 1; i <= k; ++i) B[k - i] = Tp(-i).pow(k - i) * bin.inv_factorial(k - i);
    std::vector<Tp> xe_neg_x(m); // xe^(-x)
    for (int i = 1; i < m; ++i) {
        xe_neg_x[i] = bin.inv_factorial(i - 1);
        if ((i - 1) & 1) xe_neg_x[i] = -xe_neg_x[i];
    }
    auto AA = convolution(composition(A, xe_neg_x, m), fps_exp(std::vector{Tp(0), Tp(k + 1)}, m));
    auto BB = convolution(composition(B, xe_neg_x, m), fps_exp(std::vector{Tp(0), Tp(k)}, m));
    for (int i = 0; i < m; ++i) AA[i] = (AA[i] - BB[i]) * bin.factorial(i);
    AA.resize(m);
    return AA;
}

template <typename Tp>
inline std::vector<Tp> bell_numbers(int n) {
    auto &&bin = Binomial<Tp>::get(n);
    std::vector<Tp> ex(n);
    for (int i = 1; i < n; ++i) ex[i] = bin.inv_factorial(i);
    auto res = fps_exp(ex, n);
    for (int i = 0; i < n; ++i) res[i] *= bin.factorial(i);
    return res;
}
