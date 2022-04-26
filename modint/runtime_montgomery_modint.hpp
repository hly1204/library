#ifndef MONTGOMERY_MODINT_HPP
#define MONTGOMERY_MODINT_HPP

#include "../common.hpp"

#ifdef LIB_DEBUG
  #include <stdexcept>
#endif
#include <cstdint>
#include <iostream>
#include <type_traits>

LIB_BEGIN

template <int /* IdT */>
class runtime_montgomery_modint30 {
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  u32 v_{};

  static u32 redc(u64 x) { return (x + static_cast<u64>(static_cast<u32>(x) * R) * MOD) >> 32; }
  static u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }

  static u32 MOD, MOD2, R, R2;
  static i32 SMOD;

public:
  static bool set_mod(u32 m) {
    if ((m & 1) == 0 || m == 1 || m >> 30 != 0) return false;
    MOD = m, MOD2 = MOD << 1;
    {
      // compute R
      u32 t = 2, iv = MOD * (t - MOD * MOD);
      iv *= t - MOD * iv, iv *= t - MOD * iv;
      R = iv * (MOD * iv - t);
    }
    // compute R2
    R2   = -static_cast<u64>(MOD) % MOD;
    SMOD = static_cast<i32>(MOD);
    return true;
  }
  static u32 mod() { return MOD; }
  static i32 smod() { return SMOD; }
  runtime_montgomery_modint30() {}
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  runtime_montgomery_modint30(IntT v) : v_(redc(static_cast<u64>(v % SMOD + SMOD) * R2)) {}
  u32 val() const { return norm(redc(v_)); }
  i32 sval() const { return norm(redc(v_)); }
  bool is_zero() const { return v_ == 0 || v_ == MOD; }
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  explicit operator IntT() const {
    return static_cast<IntT>(val());
  }
  runtime_montgomery_modint30 operator-() const {
    runtime_montgomery_modint30 res;
    res.v_ = (MOD2 & -(v_ != 0)) - v_;
    return res;
  }
  runtime_montgomery_modint30 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
#ifdef LIB_DEBUG
    if (a != 1) throw std::runtime_error("modular inverse error");
#endif
    return runtime_montgomery_modint30(x1);
  }
  runtime_montgomery_modint30 &operator+=(const runtime_montgomery_modint30 &rhs) {
    v_ += rhs.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  runtime_montgomery_modint30 &operator-=(const runtime_montgomery_modint30 &rhs) {
    v_ -= rhs.v_, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  runtime_montgomery_modint30 &operator*=(const runtime_montgomery_modint30 &rhs) {
    v_ = redc(static_cast<u64>(v_) * rhs.v_);
    return *this;
  }
  runtime_montgomery_modint30 &operator/=(const runtime_montgomery_modint30 &rhs) {
    return operator*=(rhs.inv());
  }
  runtime_montgomery_modint30 pow(u64 e) const {
    for (runtime_montgomery_modint30 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  void swap(runtime_montgomery_modint30 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend runtime_montgomery_modint30 operator+(const runtime_montgomery_modint30 &lhs,
                                               const runtime_montgomery_modint30 &rhs) {
    return runtime_montgomery_modint30(lhs) += rhs;
  }
  friend runtime_montgomery_modint30 operator-(const runtime_montgomery_modint30 &lhs,
                                               const runtime_montgomery_modint30 &rhs) {
    return runtime_montgomery_modint30(lhs) -= rhs;
  }
  friend runtime_montgomery_modint30 operator*(const runtime_montgomery_modint30 &lhs,
                                               const runtime_montgomery_modint30 &rhs) {
    return runtime_montgomery_modint30(lhs) *= rhs;
  }
  friend runtime_montgomery_modint30 operator/(const runtime_montgomery_modint30 &lhs,
                                               const runtime_montgomery_modint30 &rhs) {
    return runtime_montgomery_modint30(lhs) /= rhs;
  }
  friend bool operator==(const runtime_montgomery_modint30 &lhs,
                         const runtime_montgomery_modint30 &rhs) {
    return norm(lhs.v_) == norm(rhs.v_);
  }
  friend bool operator!=(const runtime_montgomery_modint30 &lhs,
                         const runtime_montgomery_modint30 &rhs) {
    return norm(lhs.v_) != norm(rhs.v_);
  }
  friend std::istream &operator>>(std::istream &is, runtime_montgomery_modint30 &rhs) {
    i32 x;
    is >> x;
    rhs = runtime_montgomery_modint30(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const runtime_montgomery_modint30 &rhs) {
    return os << rhs.val();
  }
};

template <int IdT>
typename runtime_montgomery_modint30<IdT>::u32 runtime_montgomery_modint30<IdT>::MOD;
template <int IdT>
typename runtime_montgomery_modint30<IdT>::u32 runtime_montgomery_modint30<IdT>::MOD2;
template <int IdT>
typename runtime_montgomery_modint30<IdT>::u32 runtime_montgomery_modint30<IdT>::R;
template <int IdT>
typename runtime_montgomery_modint30<IdT>::u32 runtime_montgomery_modint30<IdT>::R2;
template <int IdT>
typename runtime_montgomery_modint30<IdT>::i32 runtime_montgomery_modint30<IdT>::SMOD;

template <int IdT>
using rmm30 = runtime_montgomery_modint30<IdT>;

LIB_END

#endif