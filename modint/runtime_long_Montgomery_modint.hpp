#ifndef RUNTIME_LONG_MONTGOMERY_MODINT_HEADER_HPP
#define RUNTIME_LONG_MONTGOMERY_MODINT_HEADER_HPP

#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <type_traits>

#ifdef _MSC_VER
  #include <intrin.h>
#endif

namespace lib {

// 参见：https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp
template <int>
class RuntimeLongMontgomeryModInt {
public:
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;
  using m64 = RuntimeLongMontgomeryModInt;

  using value_type = u64;

  static u64 get_mod() { return mod; }

  static bool set_mod(u64 m) {
    if ((m & 1) == 0 || m == 1 || (m & (1ULL << 63)) != 0) return false;
    mod = m;
    r   = get_r();
    r2  = get_r2();
    return true;
  }

  RuntimeLongMontgomeryModInt()  = default;
  ~RuntimeLongMontgomeryModInt() = default;

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  RuntimeLongMontgomeryModInt(T v) : v_(reduce(mul(norm(v % i64(mod)), r2))) {}

  RuntimeLongMontgomeryModInt(const m64 &) = default;

  u64 get() const { return reduce({0, v_}); }

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit operator T() const {
    return T(get());
  }

  m64 operator-() const {
    m64 res;
    res.v_ = (mod & -(v_ != 0)) - v_;
    return res;
  }

  m64 inv() const {
    i64 x1 = 1, x3 = 0, a = get(), b = mod;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return m64(x1);
  }

  m64 &operator=(const m64 &) = default;

  m64 &operator+=(const m64 &rhs) {
    v_ += rhs.v_ - mod;
    v_ += mod & -(v_ >> 63);
    return *this;
  }
  m64 &operator-=(const m64 &rhs) {
    v_ -= rhs.v_;
    v_ += mod & -(v_ >> 63);
    return *this;
  }
  m64 &operator*=(const m64 &rhs) {
    v_ = reduce(mul(v_, rhs.v_));
    return *this;
  }
  m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv()); }
  friend m64 operator+(const m64 &lhs, const m64 &rhs) { return m64(lhs) += rhs; }
  friend m64 operator-(const m64 &lhs, const m64 &rhs) { return m64(lhs) -= rhs; }
  friend m64 operator*(const m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }
  friend m64 operator/(const m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }
  friend bool operator==(const m64 &lhs, const m64 &rhs) { return lhs.v_ == rhs.v_; }
  friend bool operator!=(const m64 &lhs, const m64 &rhs) { return lhs.v_ != rhs.v_; }

  friend std::istream &operator>>(std::istream &is, m64 &rhs) {
    i64 x;
    is >> x;
    rhs = m64(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const m64 &rhs) { return os << rhs.get(); }

  m64 pow(u64 y) const {
    for (m64 res(1), x(*this);; x *= x) {
      if (y & 1) res *= x;
      if ((y >>= 1) == 0) return res;
    }
  }

private:
  static std::pair<u64, u64> mul(u64 x, u64 y) {
#ifdef __GNUC__
    unsigned __int128 res = (unsigned __int128)x * y;
    return {u64(res >> 64), u64(res)};
#elif defined(_MSC_VER)
    u64 h, l = _umul128(x, y, &h);
    return {h, l};
#else
    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;
    return {a * c + (ad >> 32) + (bc >> 32) +
                (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32),
            x * y};
#endif
  }

  static u64 mulh(u64 x, u64 y) {
#ifdef __GNUC__
    return u64((unsigned __int128)x * y >> 64);
#elif defined(_MSC_VER)
    return __umulh(x, y);
#else
    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) +
           (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32);
#endif
  }

  static u64 get_r() {
    u64 two = 2, iv = mod * (two - mod * mod);
    iv *= two - mod * iv;
    iv *= two - mod * iv;
    iv *= two - mod * iv;
    return iv * (two - mod * iv);
  }

  static u64 get_r2() {
    u64 iv = -u64(mod) % mod;
    for (int i = 0; i != 64; ++i)
      if ((iv <<= 1) >= mod) iv -= mod;
    return iv;
  }

  static u64 reduce(const std::pair<u64, u64> &x) {
    u64 res = x.first - mulh(x.second * r, mod);
    return res + (mod & -(res >> 63));
  }

  static u64 norm(i64 x) { return x + (mod & -(x < 0)); }

  u64 v_;

  static inline u64 mod, r, r2;
};

template <int id>
using RuntimeLongMontModInt = RuntimeLongMontgomeryModInt<id>;

} // namespace lib

#endif