#pragma once

#include "fft.hpp"
#include <cassert>
#include <vector>

// returns max[0 <= j < a.size()](len(a[i]))
template <typename Tp>
inline int max_len_x_ks(const std::vector<std::vector<Tp>> &a) {
    int len = -1;
    for (int i = 0; i < (int)a.size(); ++i) len = std::max<int>(len, a[i].size());
    return len;
}

// returns a(x, x^N) where a(x,y) in R[x][y]
template <typename Tp>
inline std::vector<Tp> pack_2d_ks(const std::vector<std::vector<Tp>> &a, int N) {
    assert(N > 0);
    // y |-> x^N
    std::vector<Tp> b(N * a.size());
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)a[i].size(); ++j) b[i * N + j] += a[i][j]; // if N < a[i].size()
    return b;
}

template <typename Tp>
inline std::vector<std::vector<Tp>> unpack_2d_ks(const std::vector<Tp> &a, int N) {
    assert(N > 0);
    // x^N |-> y
    std::vector<std::vector<Tp>> b((a.size() + (N - 1)) / N, std::vector<Tp>(N));
    for (int i = 0; i < (int)((a.size() + N - 1) / N); ++i)
        for (int j = 0; j < N && i * N + j < (int)a.size(); ++j) b[i][j] = a[i * N + j];
    return b;
}

template <typename Tp>
inline std::vector<std::vector<Tp>> convolution_2d_naive(const std::vector<std::vector<Tp>> &a,
                                                         const std::vector<std::vector<Tp>> &b) {
    if (a.empty() || b.empty()) return {};
    const int lenA = max_len_x_ks(a);
    const int lenB = max_len_x_ks(b);
    if (lenA == 0 || lenB == 0) return std::vector<std::vector<Tp>>(a.size() + b.size() - 1);
    const int N = lenA + lenB - 1;
    std::vector<std::vector<Tp>> ab(a.size() + b.size() - 1, std::vector<Tp>(N));
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)b.size(); ++j) {
            const auto aibj = convolution(a[i], b[j]);
            for (int k = 0; k < (int)aibj.size(); ++k) ab[i + j][k] += aibj[k];
        }
    return ab;
}

// standard Kronecker substitution
template <typename Tp>
inline std::vector<std::vector<Tp>> convolution_2d_ks(const std::vector<std::vector<Tp>> &a,
                                                      const std::vector<std::vector<Tp>> &b) {
    if (a.empty() || b.empty()) return {};
    const int lenA = max_len_x_ks(a);
    const int lenB = max_len_x_ks(b);
    if (lenA == 0 || lenB == 0) return std::vector<std::vector<Tp>>(a.size() + b.size() - 1);
    const int N = lenA + lenB - 1;
    auto res    = convolution(pack_2d_ks(a, N), pack_2d_ks(b, N));
    res.resize((a.size() + b.size() - 1) * N);
    return unpack_2d_ks(res, N);
}
