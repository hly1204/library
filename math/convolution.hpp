#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include "../common.hpp"
#include "../modint/long_montgomery_modint.hpp"
#include "truncated_fourier_transform.hpp"

#include <algorithm>
#include <cstdint>
#include <type_traits>
#include <vector>

LIB_BEGIN

template <typename ModIntT>
std::vector<ModIntT> convolution(const std::vector<ModIntT> &lhs, const std::vector<ModIntT> &rhs) {
  int n = static_cast<int>(lhs.size()), m = static_cast<int>(rhs.size());
  if (n == 0 || m == 0) return {};
  if (std::min(n, m) <= 32) {
    std::vector<ModIntT> res(n + m - 1);
    for (int i = 0; i != n; ++i)
      for (int j = 0; j != m; ++j) res[i + j] += lhs[i] * rhs[j];
    return res;
  }
  int len = n + m - 1;
  std::vector<ModIntT> lhs_cpy(len), rhs_cpy(len);
  std::copy_n(lhs.cbegin(), n, lhs_cpy.begin());
  std::copy_n(rhs.cbegin(), m, rhs_cpy.begin());
  tft(lhs_cpy), tft(rhs_cpy);
  for (int i = 0; i != len; ++i) lhs_cpy[i] *= rhs_cpy[i];
  itft(lhs_cpy);
  return lhs_cpy;
}

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