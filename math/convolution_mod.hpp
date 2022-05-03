#ifndef CONVOLUTION_MOD_HPP
#define CONVOLUTION_MOD_HPP

#include "../common.hpp"
#include "../modint/long_montgomery_modint.hpp"
#include "convolution.hpp"

#include <cstdint>
#include <type_traits>
#include <vector>

LIB_BEGIN

template <typename IntT>
std::enable_if_t<std::is_integral_v<IntT> && sizeof(IntT) <= sizeof(std::int32_t),
                 std::vector<IntT>>
convolution_mod(const std::vector<IntT> &lhs, const std::vector<IntT> &rhs, const IntT modular) {
  using mint0 = mm63<0x3F9A000000000001>;
  using mint1 = mm63<0x3FC6000000000001>;
  auto res0   = convolution(std::vector<mint0>(lhs.begin(), lhs.end()),
                          std::vector<mint0>(rhs.begin(), rhs.end()));
  auto res1   = convolution(std::vector<mint1>(lhs.begin(), lhs.end()),
                          std::vector<mint1>(rhs.begin(), rhs.end()));
  const int n = res0.size();
  std::vector<IntT> res(n);
  //    a mod m_0 = a_0, a mod m_1 = a_1
  // -> a_0 + k_0m_0 = a_1 + k_1m_1
  // -> a_0 - a_1 ≡ k_1m_1 (mod m_0)
  // -> k_1 ≡ (a_0 - a_1) / m_1 (mod m_0)
  static constexpr mint0 im1_mod_m0(mint0(mint1::mod()).inv());
  const IntT m1_mod_modular = mint1::mod() % modular;
  for (int i = 0; i != n; ++i) {
    mint0 k1((res0[i] - res1[i].val()) * im1_mod_m0);
    res[i] = (k1.val() % modular * m1_mod_modular + res1[i].val()) % modular;
  }
  return res;
}

LIB_END

#endif