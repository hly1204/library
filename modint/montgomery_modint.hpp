#ifndef MONTGOMERY_MODINT_HPP
#define MONTGOMERY_MODINT_HPP

#include "common.hpp"

#ifdef LIB_DEBUG
  #include <exception>
#endif
#include <cstdint>
#include <iostream>
#include <type_traits>

LIB_BEGIN

template <std::uint32_t ModT>
class montgomery_modint30 {
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  u32 v_;

  static constexpr u32 get_r() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
  }
  static constexpr u32 redc(u64 x) {
    return (x + static_cast<u64>(static_cast<u32>(x) * R) * MOD) >> 32;
  }
  static constexpr u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }

  enum : u32 { MOD = ModT, MOD2 = MOD * 2, R = get_r(), R2 = -static_cast<u64>(MOD) % MOD };
  enum : i32 { SMOD = MOD };

  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);

public:
  static constexpr u32 mod() { return MOD; }
  static constexpr i32 smod() { return SMOD; }
  constexpr montgomery_modint30() : v_() {}
  template <typename Int, std::enable_if_t<std::is_integral_v<Int>, int> = 0>
  constexpr montgomery_modint30(Int v) : v_(redc(static_cast<u64>(v % SMOD + SMOD) * R2)) {}
  constexpr u32 val() const { return norm(redc(v_)); }
  constexpr i32 sval() const { return norm(redc(v_)); }
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  explicit constexpr operator IntT() const {
    return static_cast<IntT>(val());
  }
  constexpr montgomery_modint30 operator-() const {
    montgomery_modint30 res;
    res.v_ = (MOD2 & -(v_ != 0)) - v_;
    return res;
  }
  constexpr montgomery_modint30 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
#ifdef LIB_DEBUG
    if (a != 1) throw std::runtime_error("modular inverse error");
#endif
    return montgomery_modint30(x1);
  }
  constexpr montgomery_modint30 &operator+=(const montgomery_modint30 &rhs) {
    v_ += rhs.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr montgomery_modint30 &operator-=(const montgomery_modint30 &rhs) {
    v_ -= rhs.v_, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr montgomery_modint30 &operator*=(const montgomery_modint30 &rhs) {
    v_ = redc(static_cast<u64>(v_) * rhs.v_);
    return *this;
  }
  constexpr montgomery_modint30 &operator/=(const montgomery_modint30 &rhs) {
    return operator*=(rhs.inv());
  }
  constexpr montgomery_modint30 pow(u64 e) const {
    for (montgomery_modint30 res(1u), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  constexpr void swap(montgomery_modint30 &rhs) {
    u32 v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend constexpr montgomery_modint30 operator+(const montgomery_modint30 &lhs,
                                                 const montgomery_modint30 &rhs) {
    return montgomery_modint30(lhs) += rhs;
  }
  friend constexpr montgomery_modint30 operator-(const montgomery_modint30 &lhs,
                                                 const montgomery_modint30 &rhs) {
    return montgomery_modint30(lhs) -= rhs;
  }
  friend constexpr montgomery_modint30 operator*(const montgomery_modint30 &lhs,
                                                 const montgomery_modint30 &rhs) {
    return montgomery_modint30(lhs) *= rhs;
  }
  friend constexpr montgomery_modint30 operator/(const montgomery_modint30 &lhs,
                                                 const montgomery_modint30 &rhs) {
    return montgomery_modint30(lhs) /= rhs;
  }
  friend constexpr bool operator==(const montgomery_modint30 &lhs, const montgomery_modint30 &rhs) {
    return norm(lhs.v_) == norm(rhs.v_);
  }
  friend constexpr bool operator!=(const montgomery_modint30 &lhs, const montgomery_modint30 &rhs) {
    return norm(lhs.v_) != norm(rhs.v_);
  }
  friend std::istream &operator>>(std::istream &is, montgomery_modint30 &rhs) {
    i32 x;
    is >> x;
    rhs = montgomery_modint30(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const montgomery_modint30 &rhs) {
    return os << rhs.val();
  }
};

template <std::uint32_t MOD>
using mm30 = montgomery_modint30<MOD>;

LIB_END

#endif