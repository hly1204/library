#pragma once

#include "fft.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// see:
// [1]: Guillaume Hanrot, Michel Quercia, Paul Zimmermann. The Middle Product Algorithm I.
// [2]: Alin Bostan, Grégoire Lecerf, Éric Schost. Tellegen's principle into practice.

// returns (fg)_(n-1),...,(fg)_(m-1)
// f: f_0 + ... + f_(m-1)x^(m-1)
// g: g_0 + ... + g_(n-1)x^(n-1)
// m >= n
template <typename Tp>
inline std::vector<Tp> middle_product(std::vector<Tp> f, std::vector<Tp> g) {
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
