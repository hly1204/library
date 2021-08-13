#ifndef RANDOM_XOSHIRO256STARSTAR_HEADER_HPP
#define RANDOM_XOSHIRO256STARSTAR_HEADER_HPP

/**
 * @brief pseudo random generator
 *
 */

#include <cassert>
#include <cstdint>
#include <type_traits>

namespace lib {

/**
 * @brief xoshiro256starstar
 * @see https://prng.di.unimi.it/xoshiro256starstar.c
 */
class Random {
private:
  using u64 = std::uint64_t;

public:
  /**
   * @brief 创建一个新的随机数对象，共用同一个种子
   * @param x 种子
   * @see https://prng.di.unimi.it/splitmix64.c
   */
  Random(u64 x = 0) {
    for (int i = 0; i < 4; ++i) {
      u64 z = (x += 0x9e3779b97f4a7c15);
      z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
      z     = (z ^ (z >> 27)) * 0x94d049bb133111eb;
      s[i]  = z ^ (z >> 31);
    }
  }
  ~Random() = default;

  /**
   * @brief 返回 [0, upper] 中均匀分布的一个整数
   * @tparam T
   * @param upper 上界，可以取到
   * @return std::enable_if_t<std::is_integral_v<T>, T>
   */
  template <typename T>
  std::enable_if_t<std::is_integral_v<T>, T> uniform_int(T upper) {
    assert(upper > 0);
    u64 mask = u64(upper);
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    mask |= mask >> 8;
    mask |= mask >> 16;
    if constexpr (sizeof(T) > 4) mask |= mask >> 32;
    for (;;) {
      u64 res = next() & mask;
      if (res <= upper) return T(res);
    }
  }

  /**
   * @brief 返回 [lower, upper] 中均匀分布的一个整数
   * @note 输入可能会越界，但这里不处理
   * @tparam T
   * @param lower 下界，可以取到
   * @param upper 上界，可以取到
   * @return std::enable_if_t<std::is_integral_v<T>, T>
   */
  template <typename T>
  std::enable_if_t<std::is_integral_v<T>, T> uniform_int(T lower, T upper) { // [lower, upper]
    assert(upper > lower);
    return uniform_int(upper - lower) + lower;
  }

  void jump() { // 等价于调用 2^128 次 next()
    static const u64 JUMP[] = {0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa,
                               0x39abdc4529b1661c};
    u64 s0                  = 0;
    u64 s1                  = 0;
    u64 s2                  = 0;
    u64 s3                  = 0;
    for (int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
      for (int b = 0; b < 64; b++) {
        if (JUMP[i] & UINT64_C(1) << b) {
          s0 ^= s[0];
          s1 ^= s[1];
          s2 ^= s[2];
          s3 ^= s[3];
        }
        next();
      }
    s[0] = s0;
    s[1] = s1;
    s[2] = s2;
    s[3] = s3;
  }
  void long_jump() { // 等价于调用 2^192 次 next() 与上述区别在于 2^64 次调用
    static const u64 LONG_JUMP[] = {0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241,
                                    0x39109bb02acbe635};
    u64 s0                       = 0;
    u64 s1                       = 0;
    u64 s2                       = 0;
    u64 s3                       = 0;
    for (int i = 0; i < sizeof LONG_JUMP / sizeof *LONG_JUMP; i++)
      for (int b = 0; b < 64; b++) {
        if (LONG_JUMP[i] & UINT64_C(1) << b) {
          s0 ^= s[0];
          s1 ^= s[1];
          s2 ^= s[2];
          s3 ^= s[3];
        }
        next();
      }
    s[0] = s0;
    s[1] = s1;
    s[2] = s2;
    s[3] = s3;
  }

private:
  u64 s[4];
  static inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64 - k)); }
  u64 next() {
    const u64 result = rotl(s[1] * 5, 7) * 9;
    const u64 t      = s[1] << 17;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 45);
    return result;
  }
};

} // namespace lib

#endif