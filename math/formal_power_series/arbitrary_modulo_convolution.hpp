#ifndef ARBITRARY_CONVOLUTION_HEADER_HPP
#define ARBITRARY_CONVOLUTION_HEADER_HPP

/**
 * @brief arbitrary modulo convolution / 任意模数卷积
 *
 */

#include <cstdint>
#include <vector>

#include "NTT_crt.hpp"
#include "convolution.hpp"
#include "modint/Montgomery_modint.hpp"

namespace lib {

/**
 * @brief 任意模数卷积
 * @note 只适用于模数为 32 位
 */
template <typename Int, typename ModType>
std::enable_if_t<std::is_integral_v<ModType> && (sizeof(ModType) <= 4) && std::is_integral_v<Int>,
                 std::vector<Int>>
convolve_mod(const std::vector<Int> &x, const std::vector<Int> &y, ModType mod) {
  using u32               = std::uint32_t;
  static constexpr u32 M0 = 880803841, M1 = 897581057, M2 = 998244353;
  NTTCRT3<M0, M1, M2> crt(mod);
  using mod_t0 = MontModInt<M0>;
  using mod_t1 = MontModInt<M1>;
  using mod_t2 = MontModInt<M2>;
  auto res0 =
      convolve(std::vector<mod_t0>(x.begin(), x.end()), std::vector<mod_t0>(y.begin(), y.end()));
  auto res1 =
      convolve(std::vector<mod_t1>(x.begin(), x.end()), std::vector<mod_t1>(y.begin(), y.end()));
  auto res2 =
      convolve(std::vector<mod_t2>(x.begin(), x.end()), std::vector<mod_t2>(y.begin(), y.end()));
  int n = res0.size();
  std::vector<Int> res;
  res.reserve(n);
  for (int i = 0; i < n; ++i) res.emplace_back(crt(u32(res0[i]), u32(res1[i]), u32(res2[i])));
  return res;
}

} // namespace lib

#endif