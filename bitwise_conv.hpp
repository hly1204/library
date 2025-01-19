#pragma once

#include "sps_fft.hpp"
#include "subset_conv.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

template<typename Tp>
inline std::vector<Tp> bitwise_or_convolution(std::vector<Tp> a, std::vector<Tp> b) {
    assert(a.size() == b.size());
    const int n = a.size();
    assert((n & (n - 1)) == 0);
    assert(n > 0);
    subset_zeta(a);
    subset_zeta(b);
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    subset_moebius(a);
    return a;
}

template<typename Tp>
inline std::vector<Tp> bitwise_and_convolution(const std::vector<Tp> &a, const std::vector<Tp> &b) {
    auto ab = bitwise_or_convolution(std::vector(a.rbegin(), a.rend()),
                                     std::vector(b.rbegin(), b.rend()));
    std::reverse(ab.begin(), ab.end());
    return ab;
}

template<typename Tp>
inline std::vector<Tp> bitwise_xor_convolution(std::vector<Tp> a, std::vector<Tp> b) {
    assert(a.size() == b.size());
    const int n = a.size();
    assert((n & (n - 1)) == 0);
    assert(n > 0);
    sps_fft(a);
    sps_fft(b);
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    sps_inv_fft(a);
    return a;
}
