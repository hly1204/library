#pragma once

#include "fft.hpp"
#include <cassert>
#include <iterator>
#include <vector>

// same as fft_n(a, n)
template <typename Iterator>
inline void radix4_fft_n(Iterator a, int n) {
    using Tp = typename std::iterator_traits<Iterator>::value_type;
    assert((n & (n - 1)) == 0);
    const int bn = __builtin_ctz(n);
    if (bn & 1) {
        for (int i = 0; i < n / 2; ++i) {
            const auto a0 = a[i], a1 = a[i + n / 2];
            a[i] = a0 + a1, a[i + n / 2] = a0 - a1;
        }
    }
    auto &&root = FftInfo<Tp>::get().root(n / 2);
    for (int i = n >> (bn & 1); i >= 4; i /= 4) {
        const int i4 = i / 4;
        for (int k = 0; k < i4; ++k) {
            const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
            const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
            const auto a02p = a0 + a2, a02m = a0 - a2;
            const auto a13p = a1 + a3, a13m = (a1 - a3) * FftInfo<Tp>::get().imag();
            a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;
            a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;
        }
        for (int j = i, m = 2; j < n; j += i, m += 2) {
            const auto r = root[m], r2 = r * r, r3 = r2 * r;
            for (int k = j; k < j + i4; ++k) {
                const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1] * r;
                const auto a2 = a[k + i4 * 2] * r2, a3 = a[k + i4 * 3] * r3;
                const auto a02p = a0 + a2, a02m = a0 - a2;
                const auto a13p = a1 + a3, a13m = (a1 - a3) * FftInfo<Tp>::get().imag();
                a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;
                a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;
            }
        }
    }
}

template <typename Tp>
inline void radix4_fft(std::vector<Tp> &a) {
    radix4_fft_n(a.begin(), a.size());
}

// same as inv_fft_n(a, n)
template <typename Iterator>
inline void radix4_inv_fft_n(Iterator a, int n) {
    using Tp = typename std::iterator_traits<Iterator>::value_type;
    assert((n & (n - 1)) == 0);
    const int bn = __builtin_ctz(n);
    auto &&root  = FftInfo<Tp>::get().inv_root(n / 2);
    for (int i = 4; i <= (n >> (bn & 1)); i *= 4) {
        const int i4 = i / 4;
        for (int k = 0; k < i4; ++k) {
            const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
            const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
            const auto a01p = a0 + a1, a01m = a0 - a1;
            const auto a23p = a2 + a3, a23m = (a2 - a3) * FftInfo<Tp>::get().imag();
            a[k + i4 * 0] = a01p + a23p, a[k + i4 * 1] = a01m - a23m;
            a[k + i4 * 2] = a01p - a23p, a[k + i4 * 3] = a01m + a23m;
        }
        for (int j = i, m = 2; j < n; j += i, m += 2) {
            const auto r = root[m], r2 = r * r, r3 = r2 * r;
            for (int k = j; k < j + i4; ++k) {
                const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
                const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
                const auto a01p = a0 + a1, a01m = a0 - a1;
                const auto a23p = a2 + a3, a23m = (a2 - a3) * FftInfo<Tp>::get().imag();
                a[k + i4 * 0] = a01p + a23p, a[k + i4 * 1] = (a01m - a23m) * r;
                a[k + i4 * 2] = (a01p - a23p) * r2, a[k + i4 * 3] = (a01m + a23m) * r3;
            }
        }
    }
    if (bn & 1) {
        for (int i = 0; i < n / 2; ++i) {
            const auto a0 = a[i], a1 = a[i + n / 2];
            a[i] = a0 + a1, a[i + n / 2] = a0 - a1;
        }
    }
    const Tp iv = Tp::mod() - (Tp::mod() - 1) / n;
    for (int i = 0; i < n; ++i) a[i] *= iv;
}

template <typename Tp>
inline void radix4_inv_fft(std::vector<Tp> &a) {
    radix4_inv_fft_n(a.begin(), a.size());
}
