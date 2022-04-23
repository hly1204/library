#ifndef LONG_MONTGOMERY_MODINT_HPP
#define LONG_MONTGOMERY_MODINT_HPP

#include "../common.hpp"

#ifdef LIB_DEBUG
  #include <stdexcept>
#endif
#include <cstdint>
#include <iostream>
#include <type_traits>

LIB_BEGIN

template <std::uint64_t ModT>
class montgomery_modint63 {
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  u64 v_{};

  static constexpr u64 get_r() {
    u64 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (t - MOD * iv);
  }
  static constexpr u64 get_r2() {
    u64 iv = -u64(MOD) % MOD;
    for (int i = 0; i != 64; ++i)
      if ((iv <<= 1) >= MOD) iv -= MOD;
    return iv;
  }
  static constexpr u64 mul_high(u64 x, u64 y) {
    u64 a = x >> 32, b = static_cast<u32>(x), c = y >> 32, d = static_cast<u32>(y), ad = a * d,
        bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) +
           (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static constexpr u64 redc_mul(u64 x, u64 y) {
    u64 res = mul_high(x, y) - mul_high(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static constexpr u64 norm(i64 x) { return x + (MOD & -(x < 0)); }

  static constexpr u64 MOD  = ModT;
  static constexpr u64 R    = get_r();
  static constexpr u64 R2   = get_r2();
  static constexpr i64 SMOD = static_cast<i64>(MOD);

  static_assert(MOD & 1);
  static_assert(R * MOD == 1);
  static_assert((MOD >> 63) == 0);
  static_assert(MOD != 1);

public:
  static constexpr u64 mod() { return MOD; }
  static constexpr i64 smod() { return SMOD; }
  constexpr montgomery_modint63() {}
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  constexpr montgomery_modint63(IntT v) : v_(redc_mul(norm(v % SMOD), R2)) {}
  constexpr u64 val() const {
    u64 res = -mul_high(v_ * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  constexpr i64 sval() const { return val(); }
  constexpr bool is_zero() const { return v_ == 0; }
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  explicit constexpr operator IntT() const {
    return static_cast<IntT>(val());
  }
  constexpr montgomery_modint63 operator-() const {
    montgomery_modint63 res;
    res.v_ = (MOD & -(v_ != 0)) - v_;
    return res;
  }
  constexpr montgomery_modint63 inv() const {
    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
#ifdef LIB_DEBUG
    if (a != 1) throw std::runtime_error("modular inverse error");
#endif
    return montgomery_modint63(x1);
  }
  constexpr montgomery_modint63 &operator+=(const montgomery_modint63 &rhs) {
    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr montgomery_modint63 &operator-=(const montgomery_modint63 &rhs) {
    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr montgomery_modint63 &operator*=(const montgomery_modint63 &rhs) {
    v_ = redc_mul(v_, rhs.v_);
    return *this;
  }
  constexpr montgomery_modint63 &operator/=(const montgomery_modint63 &rhs) {
    return operator*=(rhs.inv());
  }
  constexpr montgomery_modint63 pow(u64 e) const {
    for (montgomery_modint63 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  constexpr void swap(montgomery_modint63 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend constexpr montgomery_modint63 operator+(const montgomery_modint63 &lhs,
                                                 const montgomery_modint63 &rhs) {
    return montgomery_modint63(lhs) += rhs;
  }
  friend constexpr montgomery_modint63 operator-(const montgomery_modint63 &lhs,
                                                 const montgomery_modint63 &rhs) {
    return montgomery_modint63(lhs) -= rhs;
  }
  friend constexpr montgomery_modint63 operator*(const montgomery_modint63 &lhs,
                                                 const montgomery_modint63 &rhs) {
    return montgomery_modint63(lhs) *= rhs;
  }
  friend constexpr montgomery_modint63 operator/(const montgomery_modint63 &lhs,
                                                 const montgomery_modint63 &rhs) {
    return montgomery_modint63(lhs) /= rhs;
  }
  friend constexpr bool operator==(const montgomery_modint63 &lhs, const montgomery_modint63 &rhs) {
    return lhs.v_ == rhs.v_;
  }
  friend constexpr bool operator!=(const montgomery_modint63 &lhs, const montgomery_modint63 &rhs) {
    return lhs.v_ != rhs.v_;
  }
  friend std::istream &operator>>(std::istream &is, montgomery_modint63 &rhs) {
    i64 x;
    is >> x;
    rhs = montgomery_modint63(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const montgomery_modint63 &rhs) {
    return os << rhs.val();
  }
};

template <std::uint64_t ModT>
using mm63 = montgomery_modint63<ModT>;

LIB_END

#endif