#ifndef RUNTIME_LONG_MONTGOMERY_MODINT_HPP
#define RUNTIME_LONG_MONTGOMERY_MODINT_HPP

#include "../common.hpp"

#ifdef LIB_DEBUG
  #include <stdexcept>
#endif
#include <cstdint>
#include <iostream>
#include <type_traits>

LIB_BEGIN

template <int /* IdT */>
class runtime_montgomery_modint63 {
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  u64 v_{};

  static u64 get_r2() {}
  static u64 mul_high(u64 x, u64 y) {
    u64 a = x >> 32, b = static_cast<u32>(x), c = y >> 32, d = static_cast<u32>(y), ad = a * d,
        bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) +
           (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static u64 redc_mul(u64 x, u64 y) {
    u64 res = mul_high(x, y) - mul_high(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static u64 norm(i64 x) { return x + (MOD & -(x < 0)); }

  static u64 MOD, R, R2;
  static i64 SMOD;

public:
  static bool set_mod(u64 m) {
    if ((m & 1) == 0 || m == 1 || m >> 63 != 0) return false;
    MOD = m;
    {
      // compute R
      u64 t = 2, iv = MOD * (t - MOD * MOD);
      iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;
      R = iv * (t - MOD * iv);
    }
    {
      // compute R2
      R2 = -MOD % MOD;
      for (int i = 0; i != 64; ++i)
        if ((R2 <<= 1) >= MOD) R2 -= MOD;
    }
    SMOD = static_cast<i64>(MOD);
    return true;
  }
  static u64 mod() { return MOD; }
  static i64 smod() { return SMOD; }
  runtime_montgomery_modint63() {}
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  runtime_montgomery_modint63(IntT v) : v_(redc_mul(norm(v % SMOD), R2)) {}
  u64 val() const {
    u64 res = -mul_high(v_ * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  i64 sval() const { return val(); }
  bool is_zero() const { return v_ == 0; }
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  explicit operator IntT() const {
    return static_cast<IntT>(val());
  }
  runtime_montgomery_modint63 operator-() const {
    runtime_montgomery_modint63 res;
    res.v_ = (MOD & -(v_ != 0)) - v_;
    return res;
  }
  runtime_montgomery_modint63 inv() const {
    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
#ifdef LIB_DEBUG
    if (a != 1) throw std::runtime_error("modular inverse error");
#endif
    return runtime_montgomery_modint63(x1);
  }
  runtime_montgomery_modint63 &operator+=(const runtime_montgomery_modint63 &rhs) {
    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  runtime_montgomery_modint63 &operator-=(const runtime_montgomery_modint63 &rhs) {
    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  runtime_montgomery_modint63 &operator*=(const runtime_montgomery_modint63 &rhs) {
    v_ = redc_mul(v_, rhs.v_);
    return *this;
  }
  runtime_montgomery_modint63 &operator/=(const runtime_montgomery_modint63 &rhs) {
    return operator*=(rhs.inv());
  }
  runtime_montgomery_modint63 pow(u64 e) const {
    for (runtime_montgomery_modint63 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  void swap(runtime_montgomery_modint63 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend runtime_montgomery_modint63 operator+(const runtime_montgomery_modint63 &lhs,
                                               const runtime_montgomery_modint63 &rhs) {
    return runtime_montgomery_modint63(lhs) += rhs;
  }
  friend runtime_montgomery_modint63 operator-(const runtime_montgomery_modint63 &lhs,
                                               const runtime_montgomery_modint63 &rhs) {
    return runtime_montgomery_modint63(lhs) -= rhs;
  }
  friend runtime_montgomery_modint63 operator*(const runtime_montgomery_modint63 &lhs,
                                               const runtime_montgomery_modint63 &rhs) {
    return runtime_montgomery_modint63(lhs) *= rhs;
  }
  friend runtime_montgomery_modint63 operator/(const runtime_montgomery_modint63 &lhs,
                                               const runtime_montgomery_modint63 &rhs) {
    return runtime_montgomery_modint63(lhs) /= rhs;
  }
  friend bool operator==(const runtime_montgomery_modint63 &lhs,
                         const runtime_montgomery_modint63 &rhs) {
    return lhs.v_ == rhs.v_;
  }
  friend bool operator!=(const runtime_montgomery_modint63 &lhs,
                         const runtime_montgomery_modint63 &rhs) {
    return lhs.v_ != rhs.v_;
  }
  friend std::istream &operator>>(std::istream &is, runtime_montgomery_modint63 &rhs) {
    i64 x;
    is >> x;
    rhs = runtime_montgomery_modint63(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const runtime_montgomery_modint63 &rhs) {
    return os << rhs.val();
  }
};

template <int IdT>
typename runtime_montgomery_modint63<IdT>::u64 runtime_montgomery_modint63<IdT>::MOD;
template <int IdT>
typename runtime_montgomery_modint63<IdT>::u64 runtime_montgomery_modint63<IdT>::R;
template <int IdT>
typename runtime_montgomery_modint63<IdT>::u64 runtime_montgomery_modint63<IdT>::R2;
template <int IdT>
typename runtime_montgomery_modint63<IdT>::i64 runtime_montgomery_modint63<IdT>::SMOD;

template <int IdT>
using rmm63 = runtime_montgomery_modint63<IdT>;

LIB_END

#endif