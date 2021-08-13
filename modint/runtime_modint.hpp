#ifndef RUNTIME_MODINT_HEADER_HPP
#define RUNTIME_MODINT_HEADER_HPP

/**
 * @brief runtime modint
 *
 */

#include <cstdint>
#include <iostream>
#include <type_traits>

namespace lib {

template <int>
class RuntimeModInt {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;
  using m32 = RuntimeModInt;

  using value_type = u32;

  static u32 get_mod() { return mod; }

  static bool set_mod(u32 m) {
    if (m == 1 || (m & (1U << 31)) != 0) return false;
    mod = mod_odd = m, offset = 0;
    while ((mod_odd & 1) == 0) ++offset, mod_odd >>= 1;
    mask    = (1 << offset) - 1;
    u32 two = 2, iv = mod_odd * (two - mod_odd * mod_odd);
    iv *= two - mod_odd * iv;
    iv *= two - mod_odd * iv;
    r  = iv * (mod_odd * iv - two);
    r2 = -u64(mod_odd) % mod_odd;
    return true;
  }

  RuntimeModInt()  = default;
  ~RuntimeModInt() = default;

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  RuntimeModInt(T v) : v_(transform(norm(v %= i32(mod)))) {}

  RuntimeModInt(const m32 &) = default;

  u32 get() const {
    u32 h = reduce(v_ >> offset);
    return ((h - v_) * r & mask) * mod_odd + h;
  }

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit operator T() const {
    return T(get());
  }

  m32 operator-() const {
    m32 res;
    u32 h  = v_ >> offset;
    res.v_ = (((mod_odd & -(h != 0)) - h) << offset) | (-(v_ & mask) & mask);
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
    u32 h = (v_ >> offset) + (rhs.v_ >> offset) - mod_odd;
    v_    = ((h + (mod_odd & -(h >> 31))) << offset) | ((v_ + rhs.v_) & mask);
    return *this;
  }
  m32 &operator-=(const m32 &rhs) {
    u32 h = (v_ >> offset) - (rhs.v_ >> offset);
    v_    = ((h + (mod_odd & -(h >> 31))) << offset) | ((v_ - rhs.v_) & mask);
    return *this;
  }
  m32 &operator*=(const m32 &rhs) {
    v_ = (reduce(u64(v_ >> offset) * (rhs.v_ >> offset)) << offset) | ((v_ * rhs.v_) & mask);
    return *this;
  }
  m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv()); }
  friend m32 operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs) += rhs; }
  friend m32 operator-(const m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }
  friend m32 operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }
  friend m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }
  friend bool operator==(const m32 &lhs, const m32 &rhs) { return lhs.v_ == rhs.v_; }
  friend bool operator!=(const m32 &lhs, const m32 &rhs) { return lhs.v_ != rhs.v_; }

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
  static u32 norm(i32 x) { return x + (-(x < 0) & mod); }

  static u32 reduce(u64 x) {
    u32 t = (x + u64(u32(x) * r) * mod_odd) >> 32;
    return t - (mod_odd & -((mod_odd - 1 - t) >> 31));
  }
  static u32 transform(u32 x) { return (reduce(u64(x) % mod_odd * r2) << offset) | (x & mask); }

  u32 v_;
  static inline u32 r, r2, mod, mod_odd, offset, mask;
};

} // namespace lib

#endif