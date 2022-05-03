#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include "../common.hpp"
#include "truncated_fourier_transform.hpp"

#include <algorithm>
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

LIB_END

#endif