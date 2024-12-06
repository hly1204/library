#pragma once

#include <cassert>
#include <iterator>
#include <vector>

// set power series = R[x_1,...,x_n]/(x_1^2,...,x_n^2)
// FFT is computing F({0,1}^n)

template <typename Iterator>
inline void sps_fft_n(Iterator a, int n) {
    assert((n & (n - 1)) == 0);
    for (int i = 2; i <= n; i *= 2)
        for (int j = 0; j < n; j += i)
            for (int k = j; k < j + i / 2; ++k) {
                const auto u = a[k], v = a[k + i / 2];
                a[k] = u + v, a[k + i / 2] = u - v;
            }
}

template <typename Tp>
inline void sps_fft(std::vector<Tp> &a) {
    sps_fft_n(a.begin(), a.size());
}

template <typename Iterator>
inline void sps_inv_fft_n(Iterator a, int n) {
    using Tp = typename std::iterator_traits<Iterator>::value_type;
    sps_fft_n(a, n);
    const Tp iv = Tp::mod() - (Tp::mod() - 1) / n;
    for (int i = 0; i < n; ++i) a[i] *= iv;
}

template <typename Tp>
inline void sps_inv_fft(std::vector<Tp> &a) {
    sps_inv_fft_n(a.begin(), a.size());
}
