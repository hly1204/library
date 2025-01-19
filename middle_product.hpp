#pragma once

#include "fft.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// see:
// [1]: Guillaume Hanrot, Michel Quercia, Paul Zimmermann. The Middle Product Algorithm I.
// [2]: Alin Bostan, Grégoire Lecerf, Éric Schost. Tellegen's principle into practice.

template<typename Tp>
inline std::vector<Tp> middle_product_naive(const std::vector<Tp> &f, const std::vector<Tp> &g) {
    const int m = f.size();
    const int n = g.size();
    assert(m >= n);
    std::vector<Tp> res(m - n + 1);
    for (int i = n - 1; i < m; ++i)
        for (int j = i - (n - 1); j <= i; ++j) res[i - (n - 1)] += f[j] * g[i - j];
    return res;
}

template<typename Tp>
inline std::vector<Tp> middle_product_fft(std::vector<Tp> f, std::vector<Tp> g) {
    const int m = f.size();
    const int n = g.size();
    assert(m >= n);
    std::reverse(g.begin(), g.end());
    const int len = fft_len(m);
    f.resize(len);
    g.resize(len);
    transposed_inv_fft(f);
    fft(g);
    for (int i = 0; i < len; ++i) f[i] *= g[i];
    transposed_fft(f);
    f.resize(m - n + 1);
    return f;
}

// returns (fg)_(n-1),...,(fg)_(m-1)
// f: f_0 + ... + f_(m-1)x^(m-1)
// g: g_0 + ... + g_(n-1)x^(n-1)
// requires m >= n
template<typename Tp>
inline std::vector<Tp> middle_product(const std::vector<Tp> &f, const std::vector<Tp> &g) {
    assert(f.size() >= g.size());
    if (f.size() < 60) return middle_product_naive(f, g);
    return middle_product_fft(f, g);
}
