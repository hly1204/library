#pragma once

#include <cassert>
#include <iterator>
#include <vector>

template <typename Tp>
class FftInfo {
    static Tp least_quadratic_nonresidue() {
        for (int i = 2;; ++i)
            if (Tp(i).pow((Tp::mod() - 1) / 2) == -1) return Tp(i);
    }

    const int ordlog2_;
    const Tp zeta_;
    const Tp invzeta_;
    const Tp imag_;
    const Tp invimag_;

    mutable std::vector<Tp> root_;
    mutable std::vector<Tp> invroot_;

    FftInfo()
        : ordlog2_(__builtin_ctz(Tp::mod() - 1)),
          zeta_(least_quadratic_nonresidue().pow((Tp::mod() - 1) >> ordlog2_)),
          invzeta_(zeta_.inv()), imag_(zeta_.pow(1 << (ordlog2_ - 2))), invimag_(-imag_),
          root_{Tp(1), imag_}, invroot_{Tp(1), invimag_} {}

public:
    static const FftInfo &get() {
        static FftInfo info;
        return info;
    }

    Tp imag() const { return imag_; }
    Tp inv_imag() const { return invimag_; }
    Tp zeta() const { return zeta_; }
    Tp inv_zeta() const { return invzeta_; }
    const std::vector<Tp> &root(int n) const {
        // [0, n)
        assert((n & (n - 1)) == 0);
        if (const int s = root_.size(); s < n) {
            root_.resize(n);
            for (int i = __builtin_ctz(s); (1 << i) < n; ++i) {
                const int j = 1 << i;
                root_[j]    = zeta_.pow(1 << (ordlog2_ - i - 2));
                for (int k = j + 1; k < j * 2; ++k) root_[k] = root_[k - j] * root_[j];
            }
        }
        return root_;
    }
    const std::vector<Tp> &inv_root(int n) const {
        // [0, n)
        assert((n & (n - 1)) == 0);
        if (const int s = invroot_.size(); s < n) {
            invroot_.resize(n);
            for (int i = __builtin_ctz(s); (1 << i) < n; ++i) {
                const int j = 1 << i;
                invroot_[j] = invzeta_.pow(1 << (ordlog2_ - i - 2));
                for (int k = j + 1; k < j * 2; ++k) invroot_[k] = invroot_[k - j] * invroot_[j];
            }
        }
        return invroot_;
    }
};

inline int fft_len(int n) {
    --n;
    n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8;
    return (n | n >> 16) + 1;
}

template <typename Iterator>
inline void fft_n(Iterator a, int n) {
    using Tp = typename std::iterator_traits<Iterator>::value_type;
    assert((n & (n - 1)) == 0);
    for (int j = 0; j != n / 2; ++j) {
        auto u = a[j], v = a[j + n / 2];
        a[j] = u + v, a[j + n / 2] = u - v;
    }
    auto &&root = FftInfo<Tp>::get().root(n / 2);
    for (int i = n / 2; i >= 2; i /= 2) {
        for (int j = 0; j < i / 2; ++j) {
            auto u = a[j], v = a[j + i / 2];
            a[j] = u + v, a[j + i / 2] = u - v;
        }
        for (int j = i, m = 1; j < n; j += i, ++m)
            for (int k = j; k < j + i / 2; ++k) {
                auto u = a[k], v = a[k + i / 2] * root[m];
                a[k] = u + v, a[k + i / 2] = u - v;
            }
    }
}

template <typename Tp>
inline void fft(std::vector<Tp> &a) {
    fft_n(a.begin(), a.size());
}

template <typename Iterator>
inline void inv_fft_n(Iterator a, int n) {
    using Tp = typename std::iterator_traits<Iterator>::value_type;
    assert((n & (n - 1)) == 0);
    auto &&root = FftInfo<Tp>::get().inv_root(n / 2);
    for (int i = 2; i < n; i *= 2) {
        for (int j = 0; j < i / 2; ++j) {
            auto u = a[j], v = a[j + i / 2];
            a[j] = u + v, a[j + i / 2] = u - v;
        }
        for (int j = i, m = 1; j < n; j += i, ++m)
            for (int k = j; k < j + i / 2; ++k) {
                auto u = a[k], v = a[k + i / 2];
                a[k] = u + v, a[k + i / 2] = (u - v) * root[m];
            }
    }
    const Tp iv(Tp::mod() - Tp::mod() / n);
    for (int j = 0; j < n / 2; ++j) {
        auto u = a[j] * iv, v = a[j + n / 2] * iv;
        a[j] = u + v, a[j + n / 2] = u - v;
    }
}

template <typename Tp>
void inv_fft(std::vector<Tp> &a) {
    inv_fft_n(a.begin(), a.size());
}
