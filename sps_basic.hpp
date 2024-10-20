#pragma once

#include "subset_conv.hpp"
#include <cassert>
#include <vector>

// returns exp(0 + tx_1 + ...) in R[x_1,...,x_n]/(x_1^2,...,x_n^2)
template <typename Tp>
inline std::vector<Tp> sps_exp(const std::vector<Tp> &A) {
    const int N = A.size();
    assert(N > 0);
    assert((N & (N - 1)) == 0);
    assert(A[0] == 0);
    int LogN = 0;
    while ((1 << LogN) != N) ++LogN;
    std::vector<Tp> res(N);
    res[0] = 1;
    std::vector rankedExpA(LogN, std::vector<Tp>(N / 2));
    for (int i = 0; i < LogN; ++i) {
        std::vector rankedA(i + 1, std::vector<Tp>(1 << i));
        for (int j = 0; j < (1 << i); ++j) rankedA[__builtin_popcount(j)][j] = A[j + (1 << i)];
        for (int j = 0; j <= i; ++j) subset_zeta(rankedA[j]);

        for (int j = (1 << i) / 2; j < (1 << i); ++j) rankedExpA[__builtin_popcount(j)][j] = res[j];
        for (int j = 0; j <= i; ++j) {
            subset_zeta_n(rankedExpA[j].begin() + (1 << i) / 2, (1 << i) / 2);
            for (int k = 0; k < (1 << i) / 2; ++k)
                rankedExpA[j][k + (1 << i) / 2] += rankedExpA[j][k];
        }

        std::vector<int> map(i + 1);
        for (int j = 0; j <= i; ++j) map[j] = (j & 1) ? map[j / 2] : j / 2;

        std::vector ExpAA(i / 2 + 1, std::vector<Tp>(1 << i));
        for (int j = 0; j <= i; ++j)
            for (int k = 0; j + k <= i; ++k)
                for (int l = 0; l < (1 << i); ++l)
                    ExpAA[map[j + k]][l] += rankedExpA[j][l] * rankedA[k][l];
        for (int j = 0; j <= i / 2; ++j) subset_moebius(ExpAA[j]);

        for (int j = 0; j < (1 << i); ++j) res[j + (1 << i)] = ExpAA[map[__builtin_popcount(j)]][j];
    }
    return res;
}
