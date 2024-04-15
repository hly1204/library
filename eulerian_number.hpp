#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include "fps_basic.hpp"
#include "fps_composition.hpp"
#include <vector>

// Eulerian numbers (OEIS) https://oeis.org/wiki/Eulerian_numbers,_triangle_of

// returns A(n,0), ..., A(n,n)
template <typename Tp>
inline std::vector<Tp> eulerian_number_row(int n) {
    std::vector<Tp> A(n + 1), B(pow(std::vector<Tp>{Tp(1), Tp(-1)}, n + 1, n + 1));
    for (int i = 0; i <= n; ++i) A[i] = Tp(i + 1).pow(n);
    auto AB = convolution_fft(A, B);
    AB.resize(n + 1);
    return AB;
}

// returns A(0,k), ..., A(m-1,k)
// see: https://blog.csdn.net/EI_Captain/article/details/108586699
// Entropy Increaser. 平移指数基变换.
template <typename Tp>
inline std::vector<Tp> eulerian_number_column(int k, int m) {
    std::vector<Tp> A(k + 1), B(k + 1);
    auto &&bin = Binomial<Tp>::get(m + 1);
    for (int i = 0; i <= k; ++i) A[k - i] = Tp(-i - 1).pow(k - i) * bin.inv_factorial(k - i);
    for (int i = 1; i <= k; ++i) B[k - i] = Tp(-i).pow(k - i) * bin.inv_factorial(k - i);
    std::vector<Tp> xe_neg_x(m); // xe^(-x)
    for (int i = 1; i < m; ++i) {
        xe_neg_x[i] = bin.inv_factorial(i - 1);
        if ((i - 1) & 1) xe_neg_x[i] = -xe_neg_x[i];
    }
    auto AA = convolution_fft(composition(A, xe_neg_x, m), exp(std::vector{Tp(0), Tp(k + 1)}, m));
    auto BB = convolution_fft(composition(B, xe_neg_x, m), exp(std::vector{Tp(0), Tp(k)}, m));
    for (int i = 0; i < m; ++i) AA[i] = (AA[i] - BB[i]) * bin.factorial(i);
    AA.resize(m);
    return AA;
}
