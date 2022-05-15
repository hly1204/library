#ifndef RUNTIME_MODINT_HPP
#define RUNTIME_MODINT_HPP

#include "../common.hpp"

#ifdef LIB_DEBUG
  #include <stdexcept>
#endif
#include <cstdint>
#include <iostream>
#include <type_traits>

LIB_BEGIN

template <int /* IdT */>
class runtime_modint31 {
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  u32 v_{};

  static inline u32 norm(i32 x) { return x + (-(x < 0) & MOD); }
  static inline u32 redc(u64 x) {
    u32 t = (x + static_cast<u64>(static_cast<u32>(x) * R) * MOD_ODD) >> 32;
    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));
  }
  static inline u32 tsf(u32 x) {
    return redc(static_cast<u64>(x % MOD_ODD) * R2) << OFFSET | (x & MASK);
  }

  static u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;
  static i32 SMOD;

public:
  static inline bool set_mod(u32 m) {
    if (m == 1 || m >> 31 != 0) return false;
    for (MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0; ++OFFSET, MOD_ODD >>= 1) {}
    MASK = (1 << OFFSET) - 1, SMOD = static_cast<i32>(MOD);
    {
      // compute R
      u32 t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);
      iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv;
      R = iv * (MOD_ODD * iv - t);
    }
    // compute R2
    R2 = -static_cast<u64>(MOD_ODD) % MOD_ODD;
    return true;
  }
  static inline u32 mod() { return MOD; }
  static inline i32 smod() { return SMOD; }
  runtime_modint31() {}
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  runtime_modint31(IntT v) : v_(tsf(norm(v % SMOD))) {}
  u32 val() const {
    u32 h = redc(v_ >> OFFSET);
    return ((h - v_) * R & MASK) * MOD_ODD + h;
  }
  i32 sval() const { return val(); }
  bool is_zero() const { return v_ == 0; }
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  explicit operator IntT() const {
    return static_cast<IntT>(val());
  }
  runtime_modint31 operator-() const {
    runtime_modint31 res;
    u32 h  = v_ >> OFFSET;
    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-v_ & MASK);
    return res;
  }
  runtime_modint31 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
#ifdef LIB_DEBUG
    if (a != 1) throw std::runtime_error("modular inverse error");
#endif
    return runtime_modint31(x1);
  }
  runtime_modint31 &operator+=(const runtime_modint31 &rhs) {
    u32 h = (v_ >> OFFSET) + (rhs.v_ >> OFFSET) - MOD_ODD;
    v_    = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ + rhs.v_) & MASK);
    return *this;
  }
  runtime_modint31 &operator-=(const runtime_modint31 &rhs) {
    u32 h = (v_ >> OFFSET) - (rhs.v_ >> OFFSET);
    v_    = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ - rhs.v_) & MASK);
    return *this;
  }
  runtime_modint31 &operator*=(const runtime_modint31 &rhs) {
    v_ = (redc(static_cast<u64>(v_ >> OFFSET) * (rhs.v_ >> OFFSET)) << OFFSET) |
         ((v_ * rhs.v_) & MASK);
    return *this;
  }
  runtime_modint31 &operator/=(const runtime_modint31 &rhs) { return operator*=(rhs.inv()); }
  runtime_modint31 pow(u64 e) const {
    for (runtime_modint31 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  void swap(runtime_modint31 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend runtime_modint31 operator+(const runtime_modint31 &lhs, const runtime_modint31 &rhs) {
    return runtime_modint31(lhs) += rhs;
  }
  friend runtime_modint31 operator-(const runtime_modint31 &lhs, const runtime_modint31 &rhs) {
    return runtime_modint31(lhs) -= rhs;
  }
  friend runtime_modint31 operator*(const runtime_modint31 &lhs, const runtime_modint31 &rhs) {
    return runtime_modint31(lhs) *= rhs;
  }
  friend runtime_modint31 operator/(const runtime_modint31 &lhs, const runtime_modint31 &rhs) {
    return runtime_modint31(lhs) /= rhs;
  }
  friend bool operator==(const runtime_modint31 &lhs, const runtime_modint31 &rhs) {
    return lhs.v_ == rhs.v_;
  }
  friend bool operator!=(const runtime_modint31 &lhs, const runtime_modint31 &rhs) {
    return lhs.v_ != rhs.v_;
  }
  friend std::istream &operator>>(std::istream &is, runtime_modint31 &rhs) {
    i32 x;
    is >> x;
    rhs = runtime_modint31(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const runtime_modint31 &rhs) {
    return os << rhs.val();
  }
};

template <int IdT>
typename runtime_modint31<IdT>::u32 runtime_modint31<IdT>::R;
template <int IdT>
typename runtime_modint31<IdT>::u32 runtime_modint31<IdT>::R2;
template <int IdT>
typename runtime_modint31<IdT>::u32 runtime_modint31<IdT>::MOD;
template <int IdT>
typename runtime_modint31<IdT>::u32 runtime_modint31<IdT>::MOD_ODD;
template <int IdT>
typename runtime_modint31<IdT>::u32 runtime_modint31<IdT>::OFFSET;
template <int IdT>
typename runtime_modint31<IdT>::u32 runtime_modint31<IdT>::MASK;
template <int IdT>
typename runtime_modint31<IdT>::i32 runtime_modint31<IdT>::SMOD;

template <int IdT>
using rm31 = runtime_modint31<IdT>;

LIB_END

#endif