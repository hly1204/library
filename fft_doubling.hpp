#pragma once

#include "fft.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

template <typename Iterator>
inline void fft_doubling_n(Iterator a, int n) {
    using Tp = typename std::iterator_traits<Iterator>::value_type;
    assert((n & (n - 1)) == 0);
    std::copy_n(a, n, a + n);
    inv_fft_n(a + n, n);
    Tp k         = 1;
    const auto t = FftInfo<Tp>::get().root(n).at(n / 2);
    for (int i = 0; i < n; ++i) a[i + n] *= k, k *= t;
    fft_n(a + n, n);
}

template <typename Tp>
inline void fft_doubling(std::vector<Tp> &a) {
    const int n = a.size();
    a.resize(n * 2);
    fft_doubling_n(a.begin(), n);
}
