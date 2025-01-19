#pragma once

#include <iostream>
#include <type_traits>

template<unsigned long long Mod, bool Odd = (Mod & 1)> class ModLong;

// clang-format off
template<unsigned long long Mod> class ModLong<Mod, true> {
    using LL  = long long;
    using ULL = unsigned long long;

    static_assert((Mod >> 63) == 0, "`Mod` must less than 2^(63)");
    static_assert((Mod & 1) == 1, "`Mod` must be odd");

    template<typename Int> static std::enable_if_t<std::is_integral_v<Int>, ULL> safe_mod(Int v) { using D = std::common_type_t<Int, LL>; return (v %= (LL)Mod) < 0 ? (D)(v + (LL)Mod) : (D)v; }
    static ULL norm(LL x) { return x < 0 ? x + (LL)Mod : x; }
    static ULL norm(ULL x) { return x + (Mod & -(x >> 63)); }
    struct PrivateConstructor {} static inline private_constructor;
    ModLong(PrivateConstructor, ULL v) : v_(v) {}
    ULL v_;
    static constexpr ULL r() { ULL t = 2, iv = Mod * (t - Mod * Mod); iv *= t - Mod * iv, iv *= t - Mod * iv, iv *= t - Mod * iv; return iv * (t - Mod * iv); }
    static constexpr ULL r2() { ULL iv = -Mod % Mod; for (int i = 0; i < 64; ++i) if ((iv *= 2) >= Mod) iv -= Mod; return iv; }
    static ULL mul_high(ULL x, ULL y) { const ULL a = x >> 32, b = x & -1U, c = y >> 32, d = y & -1U, ad = a * d, bc = b * c; return a * c + (ad >> 32) + (bc >> 32) + (((ad & -1U) + (bc & -1U) + (b * d >> 32)) >> 32); }
    // Montgomery reduction
    static ULL redc_mul(ULL x, ULL y) { return norm(mul_high(x, y) - mul_high(x * y * R, Mod)); }
    static constexpr ULL R  = r();
    static constexpr ULL R2 = r2();

public:
    static unsigned long long mod() { return Mod; }
    static ModLong from_raw(unsigned long long v) { return ModLong(private_constructor, redc_mul(v, R2)); }
    static ModLong zero() { return ModLong(private_constructor, 0); }
    static ModLong one() { return from_raw(1); }
    bool is_zero() const { return *this == zero(); }
    bool is_one() const { return *this == one(); }
    ModLong() : v_() {}
    template<typename Int, typename std::enable_if_t<std::is_signed_v<Int>, int> = 0> ModLong(Int v) : v_(redc_mul(safe_mod(v), R2)) {}
    template<typename Int, typename std::enable_if_t<std::is_unsigned_v<Int>, int> = 0> ModLong(Int v) : v_(redc_mul(v % Mod, R2)) {}
    unsigned long long val() const { return norm(-mul_high(v_ * R, Mod)); }
    ModLong operator-() const { return ModLong(private_constructor, v_ == 0 ? v_ : Mod - v_); }
    ModLong pow(long long e) const { if (e < 0) return inv().pow(-e); for (ModLong x(*this), res(from_raw(1));; x *= x) { if (e & 1) res *= x; if ((e >>= 1) == 0) return res; }}
    ModLong inv() const { LL x1 = 1, x3 = 0, a = val(), b = Mod; while (b) { const LL q = a / b, x1_old = x1, a_old = a; x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q; } return from_raw(norm(x1)); }
    ModLong div_by_2() const { if (v_ & 1) return ModLong(private_constructor, (v_ + Mod) >> 1); return ModLong(private_constructor, v_ >> 1); }
    ModLong &operator+=(const ModLong &a) { v_ = norm(v_ + a.v_ - Mod); return *this; }
    ModLong &operator-=(const ModLong &a) { v_ = norm(v_ - a.v_); return *this; }
    ModLong &operator*=(const ModLong &a) { v_ = redc_mul(v_, a.v_); return *this; }
    ModLong &operator/=(const ModLong &a) { return *this *= a.inv(); }
    ModLong &operator++() { return *this += one(); }
    ModLong operator++(int) { ModLong o(*this); *this += one(); return o; }
    ModLong &operator--() { return *this -= one(); }
    ModLong operator--(int) { ModLong o(*this); *this -= one(); return o; }
    friend ModLong operator+(const ModLong &a, const ModLong &b) { return ModLong(a) += b; }
    friend ModLong operator-(const ModLong &a, const ModLong &b) { return ModLong(a) -= b; }
    friend ModLong operator*(const ModLong &a, const ModLong &b) { return ModLong(a) *= b; }
    friend ModLong operator/(const ModLong &a, const ModLong &b) { return ModLong(a) /= b; }
    friend bool operator==(const ModLong &a, const ModLong &b) { return a.v_ == b.v_; }
    friend bool operator!=(const ModLong &a, const ModLong &b) { return a.v_ != b.v_; }
    friend std::istream &operator>>(std::istream &a, ModLong &b) { LL v; a >> v; b.v_ = redc_mul(safe_mod(v), R2); return a; }
    friend std::ostream &operator<<(std::ostream &a, const ModLong &b) { return a << b.val(); }
};
// clang-format on
