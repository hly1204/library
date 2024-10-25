#pragma once

#include "subset_conv.hpp"
#include <cassert>
#include <vector>

template <typename Tp>
void convolution_ranked_inplace(std::vector<std::vector<Tp>> &rankedA,
                                const std::vector<std::vector<Tp>> &rankedB, int LogN) {
    const int N = (1 << LogN);
    for (int i = LogN; i >= 0; --i) {
        for (int j = 0; j < N; ++j) rankedA[i][j] *= rankedB[0][j];
        for (int j = 1; j <= i; ++j)
            for (int k = (1 << j) - 1; k < N; ++k)
                rankedA[i][k] += rankedA[i - j][k] * rankedB[j][k];
    }
}

template <typename Tp>
inline std::vector<Tp> sps_inv(const std::vector<Tp> &A) {
    const int N = A.size();
    assert(N > 0);
    assert((N & (N - 1)) == 0);
    assert(A[0] != 0);
    int LogN = 0;
    while ((1 << LogN) != N) ++LogN;
    std::vector<Tp> res(N);
    res[0] = A[0].inv();
    std::vector rankedInvA(LogN, std::vector<Tp>(N / 2));
    for (int i = 0; i < LogN; ++i) {
        std::vector rankedA(i + 1, std::vector<Tp>(1 << i));
        for (int j = 0; j < (1 << i); ++j) rankedA[__builtin_popcount(j)][j] = A[j + (1 << i)];
        for (int j = 0; j <= i; ++j) subset_zeta(rankedA[j]);

        for (int j = (1 << i) / 2; j < (1 << i); ++j) rankedInvA[__builtin_popcount(j)][j] = res[j];
        for (int j = 0; j <= i; ++j) {
            subset_zeta_n(rankedInvA[j].begin() + (1 << i) / 2, (1 << i) / 2);
            for (int k = 0; k < (1 << i) / 2; ++k)
                rankedInvA[j][k + (1 << i) / 2] += rankedInvA[j][k];
        }

        convolution_ranked_inplace(rankedA, rankedInvA, i);
        convolution_ranked_inplace(rankedA, rankedInvA, i);

        for (int j = 0; j <= i; ++j) subset_moebius(rankedA[j]);
        for (int j = 0; j < (1 << i); ++j) res[j + (1 << i)] = -rankedA[__builtin_popcount(j)][j];
    }
    return res;
}

template <typename Tp>
inline std::vector<Tp> sps_log(const std::vector<Tp> &A) {
    const int N = A.size();
    assert(N > 0);
    assert((N & (N - 1)) == 0);
    assert(A[0] == 1);
    int LogN = 0;
    while ((1 << LogN) != N) ++LogN;
    std::vector<Tp> res(N);
    std::vector<Tp> invA = {Tp(1)};
    invA.resize(N / 2);
    std::vector rankedInvA(LogN, std::vector<Tp>(N / 2));
    for (int i = 0; i < LogN; ++i) {
        std::vector rankedA(i + 1, std::vector<Tp>(1 << i));
        for (int j = 0; j < (1 << i); ++j) rankedA[__builtin_popcount(j)][j] = A[j + (1 << i)];
        for (int j = 0; j <= i; ++j) subset_zeta(rankedA[j]);

        for (int j = (1 << i) / 2; j < (1 << i); ++j)
            rankedInvA[__builtin_popcount(j)][j] = invA[j];
        for (int j = 0; j <= i; ++j) {
            subset_zeta_n(rankedInvA[j].begin() + (1 << i) / 2, (1 << i) / 2);
            for (int k = 0; k < (1 << i) / 2; ++k)
                rankedInvA[j][k + (1 << i) / 2] += rankedInvA[j][k];
        }

        convolution_ranked_inplace(rankedA, rankedInvA, i);
        auto rankedLogA = rankedA;
        for (int j = 0; j <= i; ++j) subset_moebius(rankedLogA[j]);
        for (int j = 0; j < (1 << i); ++j) res[j + (1 << i)] = rankedLogA[__builtin_popcount(j)][j];
        if (i == LogN - 1) break;
        convolution_ranked_inplace(rankedA, rankedInvA, i);

        for (int j = 0; j <= i; ++j) subset_moebius(rankedA[j]);
        for (int j = 0; j < (1 << i); ++j) invA[j + (1 << i)] = -rankedA[__builtin_popcount(j)][j];
    }
    return res;
}

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
                for (int l = (1 << k) - 1; l < (1 << i); ++l)
                    ExpAA[map[j + k]][l] += rankedExpA[j][l] * rankedA[k][l];
        for (int j = 0; j <= i / 2; ++j) subset_moebius(ExpAA[j]);

        for (int j = 0; j < (1 << i); ++j) res[j + (1 << i)] = ExpAA[map[__builtin_popcount(j)]][j];
    }
    return res;
}
