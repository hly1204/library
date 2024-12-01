#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <memory>
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
        : ordlog2_(__builtin_ctzll(Tp::mod() - 1)),
          zeta_(least_quadratic_nonresidue().pow((Tp::mod() - 1) >> ordlog2_)),
          invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL << (ordlog2_ - 2))), invimag_(-imag_),
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
                root_[j]    = zeta_.pow(1LL << (ordlog2_ - i - 2));
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
                invroot_[j] = invzeta_.pow(1LL << (ordlog2_ - i - 2));
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
inline void fft(std::vector<Tp> &a) {
    fft_n(a.begin(), a.size());
}

template <typename Iterator>
inline void inv_fft_n(Iterator a, int n) {
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
inline void inv_fft(std::vector<Tp> &a) {
    inv_fft_n(a.begin(), a.size());
}

template <typename Tp>
inline std::vector<Tp> convolution_fft(std::vector<Tp> a, std::vector<Tp> b) {
    if (a.empty() || b.empty()) return {};
    const int n   = a.size();
    const int m   = b.size();
    const int len = fft_len(n + m - 1);
    a.resize(len);
    b.resize(len);
    fft(a);
    fft(b);
    for (int i = 0; i < len; ++i) a[i] *= b[i];
    inv_fft(a);
    a.resize(n + m - 1);
    return a;
}

template <typename Tp>
inline std::vector<Tp> square_fft(std::vector<Tp> a) {
    if (a.empty()) return {};
    const int n   = a.size();
    const int len = fft_len(n * 2 - 1);
    a.resize(len);
    fft(a);
    for (int i = 0; i < len; ++i) a[i] *= a[i];
    inv_fft(a);
    a.resize(n * 2 - 1);
    return a;
}

template <typename Tp>
inline std::vector<Tp> convolution_naive(const std::vector<Tp> &a, const std::vector<Tp> &b) {
    if (a.empty() || b.empty()) return {};
    const int n = a.size();
    const int m = b.size();
    std::vector<Tp> res(n + m - 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) res[i + j] += a[i] * b[j];
    return res;
}

template <typename Tp>
inline std::vector<Tp> convolution(const std::vector<Tp> &a, const std::vector<Tp> &b) {
    if (std::min(a.size(), b.size()) < 60) return convolution_naive(a, b);
    if (std::addressof(a) == std::addressof(b)) return square_fft(a);
    return convolution_fft(a, b);
}
