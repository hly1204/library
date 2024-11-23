// C++11 Compatible
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
namespace detail {

template <typename Int>
Int inv_mod(Int r, Int mod) {
    using SInt = typename std::make_signed<Int>::type;
    SInt s = 1, t = 0, a = r, b = mod;
    while (b) {
        const SInt q = a / b;
        std::swap(s -= t * q, t);
        std::swap(a -= b * q, b);
    }
    assert(a == 1);
    if (s < 0) s += (SInt)mod;
    return s;
}

int deBruijn_log2(std::uint64_t n) {
    static constexpr std::uint64_t deBruijn = 0x022fdd63cc95386d;
    static constexpr int convert[64]        = {
        0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28, 62, 5,  39, 46, 44, 42,
        22, 9,  24, 35, 59, 56, 49, 18, 29, 11, 63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21,
        23, 58, 17, 10, 51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12,
    };
    return convert[n * deBruijn >> 58];
}

int bsf(std::uint64_t n) { return deBruijn_log2(n & ~(n - 1)); }

template <unsigned Mod>
class ZZ {
    static_assert((Mod >> 31) == 0, "`Mod` must less than 2^(31)");
    template <typename Int>
    static unsigned safe_mod(Int a) {
        if ((a %= (int)Mod) < 0) a += (int)Mod;
        return a;
    }
    struct PrivateCtor {};
    static PrivateCtor p;
    ZZ(PrivateCtor, unsigned a) : a_(a) {}
    unsigned a_;

public:
    static unsigned mod() { return Mod; }
    static ZZ from_raw(unsigned a) { return ZZ(p, a); }
    ZZ() : a_() {}
    template <typename Int>
    ZZ(Int a) : a_(safe_mod(a)) {}
    unsigned val() const { return a_; }
    ZZ operator-() const { return from_raw(a_ == 0 ? a_ : Mod - a_); }
    ZZ pow(long long e) const {
        if (e < 0) return inv().pow(-e);
        for (ZZ x(*this), y(from_raw(1));; x *= x) {
            if (e & 1) y *= x;
            if ((e /= 2) == 0) return y;
        }
    }
    ZZ inv() const { return from_raw(inv_mod(a_, Mod)); }
    ZZ &operator+=(const ZZ &R) {
        if ((a_ += R.a_) >= Mod) a_ -= Mod;
        return *this;
    }
    ZZ &operator-=(const ZZ &R) {
        if ((a_ += Mod - R.a_) >= Mod) a_ -= Mod;
        return *this;
    }
    ZZ &operator*=(const ZZ &R) {
        a_ = (unsigned long long)a_ * R.a_ % Mod;
        return *this;
    }
    ZZ &operator/=(const ZZ &R) { return *this *= R.inv(); }
    friend ZZ operator+(const ZZ &L, const ZZ &R) { return ZZ(L) += R; }
    friend ZZ operator-(const ZZ &L, const ZZ &R) { return ZZ(L) -= R; }
    friend ZZ operator*(const ZZ &L, const ZZ &R) { return ZZ(L) *= R; }
    friend ZZ operator/(const ZZ &L, const ZZ &R) { return ZZ(L) /= R; }
    friend bool operator==(const ZZ &L, const ZZ &R) { return L.a_ == R.a_; }
    friend bool operator!=(const ZZ &L, const ZZ &R) { return L.a_ != R.a_; }
    friend std::istream &operator>>(std::istream &L, ZZ &R) {
        int a;
        L >> a;
        R.a_ = safe_mod(a);
        return L;
    }
    friend std::ostream &operator<<(std::ostream &L, const ZZ &R) { return L << R.a_; }
};

template <unsigned Mod>
typename ZZ<Mod>::PrivateCtor ZZ<Mod>::p;

} // namespace detail

using detail::bsf;
using detail::inv_mod;
using MInt = detail::ZZ<998244353>;

std::vector<MInt> batch_inv(const std::vector<MInt> &a) {
    const int n = a.size();
    std::vector<MInt> b(n);
    MInt v = 1;
    for (int i = 0; i < n; ++i) b[i] = v, v *= a[i];
    assert(v != 0);
    v = v.inv();
    for (int i = n - 1; i >= 0; --i) b[i] *= v, v *= a[i];
    return b;
}

struct FftInfo {
    int log2_ord;
    std::vector<MInt> zeta;
    std::vector<MInt> inv_zeta;
    std::vector<MInt> dw;
    std::vector<MInt> inv_dw;

    FftInfo() : log2_ord(bsf(MInt::mod() - 1)) {
        MInt z = 2;
        for (;; z += 1)
            if (z.pow((MInt::mod() - 1) / 2) == -1) break;
        z = z.pow((MInt::mod() - 1) >> log2_ord);
        zeta.resize(log2_ord + 1);
        zeta[log2_ord] = z;
        for (int i = log2_ord - 1; i >= 0; --i) zeta[i] = zeta[i + 1] * zeta[i + 1];
        inv_zeta = batch_inv(zeta);
        dw.resize(std::max(0, log2_ord - 2));
        if (!dw.empty()) {
            dw[0] = zeta[3];
            for (int i = 1; i < log2_ord - 2; ++i)
                dw[i] = dw[i - 1] * inv_zeta[i + 1] * zeta[i + 3];
            inv_dw = batch_inv(dw);
        }
    }

    void dft_n(std::vector<MInt>::iterator a, int n) const {
        assert((n & (n - 1)) == 0);
        assert((unsigned long long)n <= (1ULL << log2_ord));
        const int bn = bsf(n);
        if (bn & 1) {
            for (int i = 0; i < n / 2; ++i) {
                const MInt a0 = a[i], a1 = a[i + n / 2];
                a[i] = a0 + a1, a[i + n / 2] = a0 - a1;
            }
        }
        for (int i = n >> (bn & 1); i >= 4; i /= 4) {
            const int i4 = i / 4;
            for (int k = 0; k < i4; ++k) {
                const MInt a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
                const MInt a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
                const MInt a02p = a0 + a2, a02m = a0 - a2;
                const MInt a13p = a1 + a3, a13m = (a1 - a3) * zeta[2];
                a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;
                a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;
            }
            MInt r = 1;
            for (int j = i, m = 0; j < n; j += i) {
                r *= dw[bsf(++m)];
                const MInt r2 = r * r, r3 = r2 * r;
                for (int k = j; k < j + i4; ++k) {
                    const MInt a0 = a[k + i4 * 0], a1 = a[k + i4 * 1] * r;
                    const MInt a2 = a[k + i4 * 2] * r2, a3 = a[k + i4 * 3] * r3;
                    const MInt a02p = a0 + a2, a02m = a0 - a2;
                    const MInt a13p = a1 + a3, a13m = (a1 - a3) * zeta[2];
                    a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;
                    a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;
                }
            }
        }
    }

    void idft_n(std::vector<MInt>::iterator a, int n) const {
        assert((n & (n - 1)) == 0);
        assert((unsigned long long)n <= (1ULL << log2_ord));
        const int bn = bsf(n);
        for (int i = 4; i <= (n >> (bn & 1)); i *= 4) {
            const int i4 = i / 4;
            for (int k = 0; k < i4; ++k) {
                const MInt a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
                const MInt a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
                const MInt a01p = a0 + a1, a01m = a0 - a1;
                const MInt a23p = a2 + a3, a23m = (a2 - a3) * zeta[2];
                a[k + i4 * 0] = a01p + a23p, a[k + i4 * 1] = a01m - a23m;
                a[k + i4 * 2] = a01p - a23p, a[k + i4 * 3] = a01m + a23m;
            }
            MInt r = 1;
            for (int j = i, m = 0; j < n; j += i) {
                r *= inv_dw[bsf(++m)];
                const MInt r2 = r * r, r3 = r2 * r;
                for (int k = j; k < j + i4; ++k) {
                    const MInt a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
                    const MInt a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
                    const MInt a01p = a0 + a1, a01m = a0 - a1;
                    const MInt a23p = a2 + a3, a23m = (a2 - a3) * zeta[2];
                    a[k + i4 * 0] = a01p + a23p, a[k + i4 * 1] = (a01m - a23m) * r;
                    a[k + i4 * 2] = (a01p - a23p) * r2, a[k + i4 * 3] = (a01m + a23m) * r3;
                }
            }
        }
        if (bn & 1) {
            for (int i = 0; i < n / 2; ++i) {
                const MInt a0 = a[i], a1 = a[i + n / 2];
                a[i] = a0 + a1, a[i + n / 2] = a0 - a1;
            }
        }
        const MInt iv = MInt(n).inv();
        for (int i = 0; i < n; ++i) a[i] *= iv;
    }

    void dft(std::vector<MInt> &a) const { dft_n(a.begin(), a.size()); }
    void idft(std::vector<MInt> &a) const { idft_n(a.begin(), a.size()); }
} const fft;

int fft_len(int n) {
    --n, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8;
    return (n | n >> 16) + 1;
}

std::vector<MInt> square_fft(std::vector<MInt> A) {
    if (A.empty()) return {};
    const int n   = A.size();
    const int len = fft_len(n * 2 - 1);
    A.resize(len);
    fft.dft(A);
    for (int i = 0; i < len; ++i) A[i] *= A[i];
    fft.idft(A);
    A.resize(n * 2 - 1);
    return A;
}

std::vector<MInt> convolution_naive(const std::vector<MInt> &A, const std::vector<MInt> &B) {
    if (A.empty() || B.empty()) return {};
    const int n = A.size();
    const int m = B.size();
    std::vector<MInt> AB(n + m - 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) AB[i + j] += A[i] * B[j];
    return AB;
}

std::vector<MInt> convolution_fft(std::vector<MInt> A, std::vector<MInt> B) {
    if (A.empty() || B.empty()) return {};
    const int n   = A.size();
    const int m   = B.size();
    const int len = fft_len(n + m - 1);
    A.resize(len);
    B.resize(len);
    fft.dft(A);
    fft.dft(B);
    for (int i = 0; i < len; ++i) A[i] *= B[i];
    fft.idft(A);
    A.resize(n + m - 1);
    return A;
}

std::vector<MInt> convolution(const std::vector<MInt> &A, const std::vector<MInt> &B) {
    if (std::min(A.size(), B.size()) <= 60) return convolution_naive(A, B);
    if (std::addressof(A) == std::addressof(B)) return square_fft(A);
    return convolution_fft(A, B);
}

////////////////////////////////////////////////////////////////////////////////
