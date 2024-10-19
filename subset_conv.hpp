#pragma once

#include <cassert>
#include <vector>

template <typename Tp>
inline std::vector<std::vector<Tp>> to_ranked(const std::vector<Tp> &A) {
    const int N = A.size();
    int LogN    = 0;
    while ((1 << LogN) != N) ++LogN;
    std::vector res(LogN + 1, std::vector<Tp>(N));
    for (int i = 0; i < N; ++i) res[__builtin_popcount(i)][i] = A[i];
    return res;
}

template <typename Tp>
inline std::vector<Tp> from_ranked(const std::vector<std::vector<Tp>> &A) {
    const int N = A[0].size();
    std::vector<Tp> res(N);
    for (int i = 0; i < N; ++i) res[i] = A[__builtin_popcount(i)][i];
    return res;
}

template <typename Iterator>
inline void subset_zeta_n(Iterator a, int n) {
    assert((n & (n - 1)) == 0);
    for (int i = 2; i <= n; i *= 2)
        for (int j = 0; j < n; j += i)
            for (int k = j; k < j + i / 2; ++k) a[k + i / 2] += a[k];
}

template <typename Tp>
inline void subset_zeta(std::vector<Tp> &a) {
    subset_zeta_n(a.begin(), a.size());
}

template <typename Iterator>
inline void subset_moebius_n(Iterator a, int n) {
    assert((n & (n - 1)) == 0);
    for (int i = 2; i <= n; i *= 2)
        for (int j = 0; j < n; j += i)
            for (int k = j; k < j + i / 2; ++k) a[k + i / 2] -= a[k];
}

template <typename Tp>
inline void subset_moebius(std::vector<Tp> &a) {
    subset_moebius_n(a.begin(), a.size());
}

template <typename Tp>
inline std::vector<Tp> subset_convolution(const std::vector<Tp> &A, const std::vector<Tp> &B) {
    assert(A.size() == B.size());
    const int N = A.size();
    int LogN    = 0;
    while ((1 << LogN) != N) ++LogN;
    auto rankedA = to_ranked(A);
    auto rankedB = to_ranked(B);

    // One can replace subset_zeta here to sps_fft
    for (int i = 0; i <= LogN; ++i) {
        subset_zeta(rankedA[i]);
        subset_zeta(rankedB[i]);
    }

    std::vector rankedAB(LogN + 1, std::vector<Tp>(N));
    for (int i = 0; i <= LogN; ++i)
        for (int j = 0; i + j <= LogN; ++j)
            for (int k = 0; k < N; ++k) rankedAB[i + j][k] += rankedA[i][k] * rankedB[j][k];

    // One can replace subset_moebius here to sps_inv_fft
    for (int i = 0; i <= LogN; ++i) subset_moebius(rankedAB[i]);

    return from_ranked(rankedAB);
}
