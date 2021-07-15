#ifndef CONVOLUTION_HEADER_HPP
#define CONVOLUTION_HEADER_HPP

/**
 * @brief convolution / 卷积
 *
 */

#include <vector>

#include "radix_2_NTT.hpp"

namespace lib {

/**
 * @brief NTT 模数卷积
 * @tparam mod_t NTT 友好的模数类
 */
template <typename mod_t>
std::vector<mod_t> convolve(const std::vector<mod_t> &x, const std::vector<mod_t> &y) {
  int n = x.size(), m = y.size();
  if (std::min(n, m) <= 32) {
    std::vector<mod_t> res(n + m - 1, mod_t(0));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) res[i + j] += x[i] * y[j];
    return res;
  }
  int len = get_ntt_len(n + m - 1);
  std::vector<mod_t> res(len);
  std::copy_n(x.begin(), n, res.begin());
  std::fill(res.begin() + n, res.end(), mod_t(0));
  dft(res);
  if (&x == &y) {
    for (int i = 0; i < len; ++i) res[i] *= res[i];
  } else {
    std::vector<mod_t> y_tmp(len);
    std::copy_n(y.begin(), m, y_tmp.begin());
    std::fill(y_tmp.begin() + m, y_tmp.end(), mod_t(0));
    dft(y_tmp);
    for (int i = 0; i < len; ++i) res[i] *= y_tmp[i];
  }
  idft(res);
  res.resize(n + m - 1);
  return res;
}

} // namespace lib

#endif