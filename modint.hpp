#pragma once

#include <iostream>
#include <type_traits>

template <unsigned Mod>
class ModInt {
    static_assert((Mod >> 31) == 0, "`Mod` must less than 2^(31)");
    static unsigned safe_mod(int v) {
        if ((v %= (int)Mod) < 0) v += (int)Mod;
        return v;
    }

    struct PrivateConstructor {};
    static inline PrivateConstructor private_constructor{};
    ModInt(PrivateConstructor, unsigned v) : v_(v) {}

    unsigned v_;

public:
    static unsigned mod() { return Mod; }
    static ModInt from_raw(unsigned v) { return ModInt(private_constructor, v); }
    ModInt() : v_() {}
    ModInt(int v) : v_(safe_mod(v)) {}
    unsigned val() const { return v_; }

    ModInt operator-() const { return from_raw(v_ == 0 ? v_ : Mod - v_); }
    ModInt pow(int e) const {
        if (e < 0) return inv().pow(-e);
        for (ModInt x(*this), res(from_raw(1));; x *= x) {
            if (e & 1) res *= x;
            if ((e >>= 1) == 0) return res;
        }
    }
    ModInt inv() const {
        int x1 = 1, x3 = 0, a = v_, b = Mod;
        while (b) {
            int q = a / b, x1_old = x1, a_old = a;
            x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
        }
        return from_raw(x1 < 0 ? x1 + (int)Mod : x1);
    }
    std::enable_if_t<(Mod & 1), ModInt> div_by_2() const {
        if (v_ & 1) return from_raw((v_ + Mod) >> 1);
        return from_raw(v_ >> 1);
    }

    ModInt &operator+=(const ModInt &a) {
        if ((v_ += a.v_) >= Mod) v_ -= Mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &a) {
        if ((v_ += Mod - a.v_) >= Mod) v_ -= Mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &a) {
        v_ = (unsigned long long)v_ * a.v_ % Mod;
        return *this;
    }
    ModInt &operator/=(const ModInt &a) { return *this *= a.inv(); }

    friend ModInt operator+(const ModInt &a, const ModInt &b) { return ModInt(a) += b; }
    friend ModInt operator-(const ModInt &a, const ModInt &b) { return ModInt(a) -= b; }
    friend ModInt operator*(const ModInt &a, const ModInt &b) { return ModInt(a) *= b; }
    friend ModInt operator/(const ModInt &a, const ModInt &b) { return ModInt(a) /= b; }
    friend bool operator==(const ModInt &a, const ModInt &b) { return a.v_ == b.v_; }
    friend bool operator!=(const ModInt &a, const ModInt &b) { return a.v_ != b.v_; }
    friend std::istream &operator>>(std::istream &a, ModInt &b) {
        int v;
        a >> v;
        b.v_ = safe_mod(v);
        return a;
    }
    friend std::ostream &operator<<(std::ostream &a, const ModInt &b) { return a << b.v_; }
};
