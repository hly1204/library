#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include "common.hpp"
#include "radix2_ntt.hpp"

#include <algorithm>
#include <vector>

LIB_BEGIN

template <typename ModIntT>
std::vector<ModIntT> convolution(const std::vector<ModIntT> &lhs, std::vector<ModIntT> &rhs) {
  int n = static_cast<int>(lhs.size()), m = static_cast<int>(rhs.size());
  if (n == 0 || m == 0) return std::vector<ModIntT>{};
  if (std::min(n, m) <= 32) {
    std::vector<ModIntT> res(n + m - 1, ModIntT());
    for (int i = 0; i != n; ++i)
      for (int j = 0; j != m; ++j) res[i + j] += lhs[i] * rhs[j];
    return res;
  }
  int len = ntt_len(n + m - 1);
  std::vector<ModIntT> lhs_cpy(len), rhs_cpy(len);
  std::fill(std::copy_n(lhs.cbegin(), n, lhs_cpy.begin()), lhs_cpy.end(), ModIntT());
  std::fill(std::copy_n(rhs.cbegin(), m, rhs_cpy.begin()), rhs_cpy.end(), ModIntT());
  dft_n(lhs_cpy.begin(), len), dft_n(rhs_cpy.begin(), len);
  for (int i = 0; i != len; ++i) lhs_cpy[i] *= rhs_cpy[i];
  idft_n(lhs_cpy.begin(), len);
  lhs_cpy.resize(n + m - 1);
  return lhs_cpy;
}

LIB_END

#endif