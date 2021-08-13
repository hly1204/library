#ifndef RUNTIME_MONTGOMERY_MODINT_HEADER_HPP
#define RUNTIME_MONTGOMERY_MODINT_HEADER_HPP

/**
 * @brief runtime Montgomery modint
 *
 */

#include <cstdint>
#include <iostream>
#include <type_traits>

namespace lib {

/**
 * @brief 运行时 Montgomery 取模类
 * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp
 * @author Nyaan
 * @note 约定不使用模板中 int 为负数的对象
 */
template <int>
class RuntimeMontgomeryModInt {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;
  using m32 = RuntimeMontgomeryModInt;

  using value_type = u32;

  static u32 get_mod() { return mod; }

  static bool set_mod(u32 m) {
    if ((m & 1) == 0 || m == 1 || (m & (3U << 30)) != 0) return false;
    mod = m, mod2 = mod << 1;
    u32 two = 2, iv = mod * (two - mod * mod);
    iv *= two - mod * iv;
    iv *= two - mod * iv;
    r  = iv * (mod * iv - two);
    r2 = -u64(mod) % mod;
    return true;
  }

  RuntimeMontgomeryModInt()  = default;
  ~RuntimeMontgomeryModInt() = default;

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  RuntimeMontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod)) * r2)) {}

  RuntimeMontgomeryModInt(const m32 &) = default;

  u32 get() const { return norm(reduce(v_)); }

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit operator T() const {
    return T(get());
  }

  m32 operator-() const {
    m32 res;
    res.v_ = (mod2 & -(v_ != 0)) - v_;
    return res;
  }

  m32 inv() const {
    i32 x1 = 1, x3 = 0, a = get(), b = mod;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return m32(x1);
  }

  m32 &operator=(const m32 &) = default;

  m32 &operator+=(const m32 &rhs) {
    v_ += rhs.v_ - mod2;
    v_ += mod2 & -(v_ >> 31);
    return *this;
  }
  m32 &operator-=(const m32 &rhs) {
    v_ -= rhs.v_;
    v_ += mod2 & -(v_ >> 31);
    return *this;
  }
  m32 &operator*=(const m32 &rhs) {
    v_ = reduce(u64(v_) * rhs.v_);
    return *this;
  }
  m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv()); }
  friend m32 operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs) += rhs; }
  friend m32 operator-(const m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }
  friend m32 operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }
  friend m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }
  friend bool operator==(const m32 &lhs, const m32 &rhs) { return norm(lhs.v_) == norm(rhs.v_); }
  friend bool operator!=(const m32 &lhs, const m32 &rhs) { return norm(lhs.v_) != norm(rhs.v_); }

  friend std::istream &operator>>(std::istream &is, m32 &rhs) {
    i32 x;
    is >> x;
    rhs = m32(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return os << rhs.get(); }

  m32 pow(u64 y) const {
    m32 res(1), x(*this);
    for (; y != 0; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }

private:
  static u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod) >> 32; }
  static u32 norm(u32 x) { return x - (mod & -((mod - 1 - x) >> 31)); }

  u32 v_;

  static inline u32 r, r2, mod, mod2;
};

// 别名
template <int id>
using RuntimeMontModInt = RuntimeMontgomeryModInt<id>;

} // namespace lib

#endif