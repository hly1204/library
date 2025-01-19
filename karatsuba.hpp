#pragma once

#include "fft.hpp"
#include <algorithm>
#include <vector>

// see:
// [1]: Daniel J. Bernstein. Multidigit multiplication for mathematicians.
//      https://cr.yp.to/papers.html#m3
template<typename Tp>
inline std::vector<Tp> convolution_karatsuba(const std::vector<Tp> &a, const std::vector<Tp> &b) {
    const int n = a.size();
    const int m = b.size();
    if (std::min(n, m) < 60) return convolution_naive(a, b);
    const int half = (std::max(n, m) + 1) / 2;
    const std::vector a0(a.begin(), a.begin() + std::min(n, half));
    const std::vector a1(a.begin() + std::min(n, half), a.end());
    const std::vector b0(b.begin(), b.begin() + std::min(m, half));
    const std::vector b1(b.begin() + std::min(m, half), b.end());
    // Let y := x^(half)
    // a = a0 + a1y, b = b0 + b1y
    // ab = a0b0 + (a0b1 + a1b0)y + (a1b1)y^2
    // ab = a0b0 + ((a0 + a1)(b0 + b1) - a0b0 - a1b1)y + (a1b1)y^2
    // ab mod (y^2 - y) = a0b0 + (a0b1 + a1b0)y + a1b1y
    // R[x] -> R[x][y]/(y^2 - y)

    // eval for y = 0
    const auto low = convolution_karatsuba(a0, b0);

    auto add = [](std::vector<Tp> a, const std::vector<Tp> &b) {
        if (a.size() < b.size()) a.resize(b.size());
        for (int i = 0; i < (int)b.size(); ++i) a[i] += b[i];
        return a;
    };
    // eval for y = 1
    const auto mid = convolution_karatsuba(add(a0, a1), add(b0, b1));
    // If we want to compute ab mod (y^2 - y), we only need to extract low from mid.
    // To restore the full product, we need to eval at inf.
    // eval for y = inf
    const auto hig = convolution_karatsuba(a1, b1);

    // restore ab
    std::vector<Tp> ab(n + m - 1);
    for (int i = 0; i < (int)low.size(); ++i) ab[i] += low[i], ab[i + half] -= low[i];
    for (int i = 0; i < (int)mid.size(); ++i) ab[i + half] += mid[i];
    for (int i = 0; i < (int)hig.size(); ++i) ab[i + half] -= hig[i], ab[i + half * 2] += hig[i];
    return ab;
}
