// C++11 Compatible
#include <algorithm>
#include <array>
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

// clang-format off
template <unsigned Mod>
class ZZ {
    static_assert((Mod >> 31) == 0, "`Mod` must less than 2^(31)");
    template <typename Int>
    static unsigned safe_mod(Int a) { if ((a %= (int)Mod) < 0) a += (int)Mod; return a; }
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
    ZZ &operator+=(const ZZ &R) { if ((a_ += R.a_) >= Mod) a_ -= Mod; return *this; }
    ZZ &operator-=(const ZZ &R) { if ((a_ += Mod - R.a_) >= Mod) a_ -= Mod; return *this; }
    ZZ &operator*=(const ZZ &R) { a_ = (unsigned long long)a_ * R.a_ % Mod; return *this; }
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
// clang-format on

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

void print_fft_info() {
    const int log2_ord = bsf(MInt::mod() - 1);
    MInt zeta          = 2;
    for (;; zeta += 1)
        if (zeta.pow((MInt::mod() - 1) / 2) == -1) break;
    zeta = zeta.pow((MInt::mod() - 1) >> log2_ord);
    std::vector<MInt> ZETA(log2_ord + 1);
    for (int i = 0; i <= log2_ord; ++i) ZETA[i] = zeta.pow(1ULL << (log2_ord - i));
    std::vector<MInt> DW(std::max(0, log2_ord - 2));
    if (!DW.empty()) {
        DW[0] = ZETA[3];
        for (int i = 1; i < log2_ord - 2; ++i) DW[i] = DW[i - 1] * ZETA[i + 1].inv() * ZETA[i + 3];
    }

    std::cout << "const int ORD_LOG2 = " << log2_ord << ";\n";
    auto print_array = [](const char *name, const std::vector<MInt> &V) {
        std::cout << "const std::array<MInt, " << V.size() << "> " << name << " = {";
        for (int i = 0; i < (int)V.size(); ++i) std::cout << V[i] << ", ";
        std::cout << "};\n";
    };
    print_array("ZETA", ZETA);
    print_array("INV_ZETA", batch_inv(ZETA));
    print_array("DW", DW);
    print_array("INV_DW", batch_inv(DW));
}

// replace begin
const int ORD_LOG2              = 23;
const std::array<MInt, 24> ZETA = {
    1,         998244352, 911660635, 372528824, 929031873, 452798380, 922799308, 781712469,
    476477967, 166035806, 258648936, 584193783, 63912897,  350007156, 666702199, 968855178,
    629671588, 24514907,  996173970, 363395222, 565042129, 733596141, 267099868, 15311432,
};
const std::array<MInt, 24> INV_ZETA = {
    1,         998244352, 86583718,  509520358, 337190230, 87557064,  609441965, 135236158,
    304459705, 685443576, 381598368, 335559352, 129292727, 358024708, 814576206, 708402881,
    283043518, 3707709,   121392023, 704923114, 950391366, 428961804, 382752275, 469870224,
};
const std::array<MInt, 21> DW = {
    372528824, 337190230, 454590761, 816400692, 578227951, 180142363, 83780245,
    6597683,   70046822,  623238099, 183021267, 402682409, 631680428, 344509872,
    689220186, 365017329, 774342554, 729444058, 102986190, 128751033, 395565204,
};
const std::array<MInt, 21> INV_DW = {
    509520358, 929031873, 170256584, 839780419, 282974284, 395914482, 444904435,
    72135471,  638914820, 66769500,  771127074, 985925487, 262319669, 262341272,
    625870173, 768022760, 859816005, 914661783, 430819711, 272774365, 530924681,
};
// replace end

void fft_n(std::vector<MInt>::iterator a, int n) {
    assert((n & (n - 1)) == 0);
    assert((unsigned long long)n <= (1ULL << ORD_LOG2));
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
            const MInt a13p = a1 + a3, a13m = (a1 - a3) * ZETA[2];
            a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;
            a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;
        }
        MInt r = 1;
        for (int j = i, m = 0; j < n; j += i) {
            r *= DW[bsf(++m)];
            const MInt r2 = r * r, r3 = r2 * r;
            for (int k = j; k < j + i4; ++k) {
                const MInt a0 = a[k + i4 * 0], a1 = a[k + i4 * 1] * r;
                const MInt a2 = a[k + i4 * 2] * r2, a3 = a[k + i4 * 3] * r3;
                const MInt a02p = a0 + a2, a02m = a0 - a2;
                const MInt a13p = a1 + a3, a13m = (a1 - a3) * ZETA[2];
                a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;
                a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;
            }
        }
    }
}

void inv_fft_n(std::vector<MInt>::iterator a, int n) {
    assert((n & (n - 1)) == 0);
    assert((unsigned long long)n <= (1ULL << ORD_LOG2));
    const int bn = bsf(n);
    for (int i = 4; i <= (n >> (bn & 1)); i *= 4) {
        const int i4 = i / 4;
        for (int k = 0; k < i4; ++k) {
            const MInt a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
            const MInt a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
            const MInt a01p = a0 + a1, a01m = a0 - a1;
            const MInt a23p = a2 + a3, a23m = (a2 - a3) * ZETA[2];
            a[k + i4 * 0] = a01p + a23p, a[k + i4 * 1] = a01m - a23m;
            a[k + i4 * 2] = a01p - a23p, a[k + i4 * 3] = a01m + a23m;
        }
        MInt r = 1;
        for (int j = i, m = 0; j < n; j += i) {
            r *= INV_DW[bsf(++m)];
            const MInt r2 = r * r, r3 = r2 * r;
            for (int k = j; k < j + i4; ++k) {
                const MInt a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];
                const MInt a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];
                const MInt a01p = a0 + a1, a01m = a0 - a1;
                const MInt a23p = a2 + a3, a23m = (a2 - a3) * ZETA[2];
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

void fft(std::vector<MInt> &A) { fft_n(A.begin(), A.size()); }
void inv_fft(std::vector<MInt> &A) { inv_fft_n(A.begin(), A.size()); }

int fft_len(int n) {
    --n, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8;
    return (n | n >> 16) + 1;
}

std::vector<MInt> square_fft(std::vector<MInt> A) {
    if (A.empty()) return {};
    const int n   = A.size();
    const int len = fft_len(n * 2 - 1);
    A.resize(len);
    fft(A);
    for (int i = 0; i < len; ++i) A[i] *= A[i];
    inv_fft(A);
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
    fft(A);
    fft(B);
    for (int i = 0; i < len; ++i) A[i] *= B[i];
    inv_fft(A);
    A.resize(n + m - 1);
    return A;
}

std::vector<MInt> convolution(const std::vector<MInt> &A, const std::vector<MInt> &B) {
    if (std::min(A.size(), B.size()) <= 60) return convolution_naive(A, B);
    if (std::addressof(A) == std::addressof(B)) return square_fft(A);
    return convolution_fft(A, B);
}

////////////////////////////////////////////////////////////////////////////////
