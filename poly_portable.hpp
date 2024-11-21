// C++11 Compitable
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>

////////////////////////////////////////////////////////////////////////////////
namespace detail {

template <typename Int>
std::array<Int, 2> inv_gcd(Int a, Int b) {
    Int s = 1, t = 0;
    while (b) {
        Int q = a / b;
        std::swap(s -= t * q, t);
        std::swap(a -= b * q, b);
    }
    return {s, a};
}

template <typename Int>
Int inv_mod(Int a, Int mod) {
    const auto A = inv_gcd(a, mod);
    assert(A[1] == 1);
    return A[0] < 0 ? A[0] + mod : A[0];
}

int deBruijn_log2(std::uint64_t n) {
    static constexpr std::uint64_t deBruijn = 0x022fdd63cc95386d;
    static constexpr int convert[64]        = {
        0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28, 62, 5,  39, 46, 44, 42,
        22, 9,  24, 35, 59, 56, 49, 18, 29, 11, 63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21,
        23, 58, 17, 10, 51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12};
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
    ZZ inv() const { return from_raw(inv_mod<int>(a_, Mod)); }
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

using MInt = detail::ZZ<998244353>;

////////////////////////////////////////////////////////////////////////////////
