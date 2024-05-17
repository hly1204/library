#pragma once

#include "fft.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// see:
// [1] Guillaume Hanrot, Michel Quercia, Paul Zimmermann. The Middle Product Algorithm I.
// [2] Alin Bostan, Grégoire Lecerf, Éric Schost. Tellegen's principle into practice.

template <typename Tp>
inline std::vector<Tp> middle_product_naive(const std::vector<Tp> &a, const std::vector<Tp> &b) {
    const int n = a.size();
    const int m = b.size();
    // MUL  : n, m     -> n+m-1
    // MUL^T: n, n+m-1 -> m
    assert(m >= n);
    std::vector<Tp> res(m - n + 1);
    for (int i = 0; i < m - n; ++i)
        for (int j = 0; j < n; ++j) res[i] += a[j] * b[n + i - j];
    for (int j = 1; j < n; ++j) res[m - n] += a[j] * b[m - j];
    return res;
}

template <typename Tp>
inline std::vector<Tp> middle_product_fft(std::vector<Tp> a, std::vector<Tp> b) {
    const int n = a.size();
    const int m = b.size();
    assert(m >= n);
    const int len = fft_len(m + 1);
    a.resize(len);
    b.resize(len);
    fft(a);
    fft(b);
    for (int i = 0; i < len; ++i) a[i] *= b[i];
    inv_fft(a);
    a.erase(a.begin(), a.begin() + n);
    a.resize(m - n + 1);
    return a;
}

template <typename Tp>
inline std::vector<Tp> middle_product(const std::vector<Tp> &a, const std::vector<Tp> &b) {
    if (std::min((int)b.size() - (int)a.size() + 1, (int)a.size()) < 60)
        return middle_product_naive(a, b);
    return middle_product_fft(a, b);
}
