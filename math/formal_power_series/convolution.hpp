#ifndef CONVOLUTION_HEADER_HPP
#define CONVOLUTION_HEADER_HPP

/**
 * @brief convolution
 *
 */

#include <cassert>
#include <memory>
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
  std::fill(std::copy_n(x.begin(), n, res.begin()), res.end(), mod_t(0));
  dft(res);
  if (&x == &y) {
    for (int i = 0; i < len; ++i) res[i] *= res[i];
  } else {
    std::vector<mod_t> y_tmp(len);
    std::fill(std::copy_n(y.begin(), m, y_tmp.begin()), y_tmp.end(), mod_t(0));
    dft(y_tmp);
    for (int i = 0; i < len; ++i) res[i] *= y_tmp[i];
  }
  idft(res);
  res.resize(n + m - 1);
  return res;
}

/**
 * @brief NTT 模数循环卷积
 * @param x
 * @param y
 * @param cyclen 必须为 2 的幂次！
 * @return std::vector<mod_t> convolve(x, y) mod (x^cyclen - 1)
 */
template <typename mod_t>
std::vector<mod_t> convolve_cyclic(const std::vector<mod_t> &x, const std::vector<mod_t> &y,
                                   int cyclen) {
  assert((cyclen & (cyclen - 1)) == 0);
  int n = x.size(), m = y.size(), mask = cyclen - 1;
  if (cyclen >= n + m - 1) return convolve(x, y);
  if (std::min(n, m) <= 32) {
    std::vector<mod_t> res(cyclen, mod_t(0));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) res[(i + j) & mask] += x[i] * y[j];
    return res;
  }
  std::vector<mod_t> res(cyclen, mod_t(0));
  for (int i = 0; i < n; ++i) res[i & mask] += x[i];
  dft(res);
  if (&x == &y) {
    for (int i = 0; i < cyclen; ++i) res[i] *= res[i];
  } else {
    std::vector<mod_t> y_tmp(cyclen, mod_t(0));
    for (int i = 0; i < m; ++i) y_tmp[i & mask] += y[i];
    dft(y_tmp);
    for (int i = 0; i < cyclen; ++i) res[i] *= y_tmp[i];
  }
  idft(res);
  return res;
}

} // namespace lib

#endif