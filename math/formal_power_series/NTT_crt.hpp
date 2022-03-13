#ifndef NTT_CRT_HEADER_HPP
#define NTT_CRT_HEADER_HPP

#include <cstdint>
#include <type_traits>

namespace lib {

template <std::uint32_t M0, std::uint32_t M1, std::uint32_t M2,
          std::enable_if_t<(M0 < M1) && ((M0 | M1 | M2) < (1U << 31)) &&
                               ((M0 & M1 & M2 & 1) == 1) && (M0 != M1) && (M0 != M2) && (M1 != M2),
                           int> = 0>
class NTTCRT3 {
public:
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  constexpr NTTCRT3(u32 mod) : m_(mod), M0M1_mod_m_(static_cast<u64>(M0) * M1 % mod) {}
  ~NTTCRT3() = default;

  constexpr u32 operator()(u32 a, u32 b, u32 c) const {
    // x mod M0 = a, x mod M1 = b, x mod M2 = c
    // a + k0M0 = b + k1M1 => k0 = (b - a) / M0 (mod M1)
    // x = a + k0M0 (mod M0M1) => a + k0M0 + k01M0M1 = c + k2M2
    // => k01 = (c - (a + k0M0)) / (M0M1) (mod M2)
    // => x mod M0M1M2 = a + k0M0 + k01M0M1
    u32 k0 = b - a;
    if (static_cast<int>(k0) < 0) k0 += M1;
    k0      = static_cast<u64>(k0) * M0_inv_M1_ % M1;
    u64 d   = a + static_cast<u64>(k0) * M0;
    u32 k01 = c - d % M2;
    if (static_cast<int>(k01) < 0) k01 += M2;
    // NTT 模数都小于 (1U << 31) 所以在这里可以使用加法后再取模
    return (d + static_cast<u64>(k01) * M0M1_inv_M2_ % M2 * M0M1_mod_m_) % m_;
  }

  static constexpr u32 get_inv(u32 x, u32 mod) {
    u32 res = 1;
    for (u32 e = mod - 2; e != 0; e >>= 1) {
      if (e & 1) res = static_cast<u64>(res) * x % mod;
      x = static_cast<u64>(x) * x % mod;
    }
    return res;
  }

private:
  u32 m_, M0M1_mod_m_;
  static constexpr u32 M0_inv_M1_   = get_inv(M0, M1);
  static constexpr u32 M0M1_inv_M2_ = get_inv(static_cast<u64>(M0) * M1 % M2, M2);
};

} // namespace lib

#endif