#ifndef LONG_MONTGOMERY_MODINT_HEADER_HPP
#define LONG_MONTGOMERY_MODINT_HEADER_HPP

/**
 * @brief long Montgomery modint / 长整型 Montgomery 取模类
 * @docs docs/modint/long_Montgomery_modint.md
 */

#include <cstdint>
#include <iostream>
#include <tuple>
#include <type_traits>

namespace lib {

/**
 * @brief 长整型 Montgomery 取模类
 * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp
 * @author Nyaan
 * @tparam mod 为奇数且大于 1
 */
template <std::uint64_t mod>
class LongMontgomeryModInt {
public:
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;
  using m64 = LongMontgomeryModInt;

  using value_type = u64;

  static constexpr u64 get_mod() { return mod; }

  static constexpr u64 get_primitive_root_prime() {
    u64 tmp[64]   = {};
    int cnt       = 0;
    const u64 phi = mod - 1;
    u64 m         = phi;
    for (u64 i = 2; i * i <= m; ++i) {
      if (m % i == 0) {
        tmp[cnt++] = i;
        do { m /= i; } while (m % i == 0);
      }
    }
    if (m != 1) tmp[cnt++] = m;
    for (m64 res = 2;; res += 1) {
      bool f = true;
      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi / tmp[i]) != 1;
      if (f) return u32(res);
    }
  }

  constexpr LongMontgomeryModInt() = default;
  ~LongMontgomeryModInt()          = default;

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  constexpr LongMontgomeryModInt(T v) : v_(reduce(mul(norm(v % i64(mod)), r2))) {}

  constexpr LongMontgomeryModInt(const m64 &) = default;

  constexpr u64 get() const { return reduce({0, v_}); }

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit constexpr operator T() const {
    return T(get());
  }

  constexpr m64 operator-() const {
    m64 res;
    res.v_ = (mod & -(v_ != 0)) - v_;
    return res;
  }

  constexpr m64 inv() const {
    i64 x1 = 1, x3 = 0, a = get(), b = mod;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return m64(x1);
  }

  constexpr m64 &operator=(const m64 &) = default;

  constexpr m64 &operator+=(const m64 &rhs) {
    v_ += rhs.v_ - mod;
    v_ += mod & -(v_ >> 63);
    return *this;
  }
  constexpr m64 &operator-=(const m64 &rhs) {
    v_ -= rhs.v_;
    v_ += mod & -(v_ >> 63);
    return *this;
  }
  constexpr m64 &operator*=(const m64 &rhs) {
    v_ = reduce(mul(v_, rhs.v_));
    return *this;
  }
  constexpr m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv()); }
  friend constexpr m64 operator+(const m64 &lhs, const m64 &rhs) { return m64(lhs) += rhs; }
  friend constexpr m64 operator-(const m64 &lhs, const m64 &rhs) { return m64(lhs) -= rhs; }
  friend constexpr m64 operator*(const m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }
  friend constexpr m64 operator/(const m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }
  friend constexpr bool operator==(const m64 &lhs, const m64 &rhs) { return lhs.v_ == rhs.v_; }
  friend constexpr bool operator!=(const m64 &lhs, const m64 &rhs) { return lhs.v_ != rhs.v_; }

  friend std::istream &operator>>(std::istream &is, m64 &rhs) {
    i64 x;
    is >> x;
    rhs = m64(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const m64 &rhs) { return os << rhs.get(); }

  constexpr m64 pow(u64 y) const {
    m64 res(1), x(*this);
    for (; y != 0; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }

private:
  static constexpr std::pair<u64, u64> mul(u64 x, u64 y) {
#ifdef __GNUC__
    unsigned __int128 res = (unsigned __int128)x * y;
    return {u64(res >> 64), u64(res)};
#else
    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;
    return {a * c + (ad >> 32) + (bc >> 32) +
                (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32),
            x * y};
#endif
  }

  static constexpr u64 mulh(u64 x, u64 y) {
#ifdef __GNUC__
    return u64((unsigned __int128)x * y >> 64);
#else
    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) +
           (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32);
#endif
  }

  static constexpr u64 get_r() {
    u64 two = 2, iv = mod * (two - mod * mod);
    iv *= two - mod * iv;
    iv *= two - mod * iv;
    iv *= two - mod * iv;
    return iv * (two - mod * iv);
  }

  static constexpr u64 get_r2() {
    u64 iv = -u64(mod) % mod;
    for (int i = 0; i != 64; ++i)
      if ((iv <<= 1) >= mod) iv -= mod;
    return iv;
  }

  static constexpr u64 reduce(const std::pair<u64, u64> &x) {
    u64 res = x.first - mulh(x.second * r, mod);
    return res + (mod & -(res >> 63));
  }

  static constexpr u64 norm(i64 x) { return x + (mod & -(x < 0)); }

  u64 v_;

  static constexpr u64 r  = get_r();
  static constexpr u64 r2 = get_r2();

  static_assert((mod & 1) == 1, "mod % 2 == 0\n");
  static_assert(r * mod == 1, "???\n");
  static_assert((mod & (1ULL << 63)) == 0, "mod >= (1ULL << 63)\n");
  static_assert(mod != 1, "mod == 1\n");
};

template <std::uint64_t mod>
using LongMontModInt = LongMontgomeryModInt<mod>;

} // namespace lib

#endif