#ifndef RADIX_2_WALSH_TRANSFORM_HEADER_HPP
#define RADIX_2_WALSH_TRANSFORM_HEADER_HPP

/**
 * @brief radix-2 Walsh transform
 * @docs docs/math/Walsh_transform_relatives/radix_2_Walsh_transform.md
 */

#include <algorithm>
#include <vector>

namespace lib {

template <typename mod_t>
void Walsh_trans(int n, mod_t *x) {
  for (int i = n; i >= 2; i >>= 1)
    for (int j = 0, l = i >> 1; j != n; j += i)
      for (int k = j; k != j + l; ++k) {
        mod_t u = x[k], v = x[k + l];
        x[k] = u + v, x[k + l] = u - v;
      }
}

template <typename mod_t>
void Walsh_itrans(int n, mod_t *x) {
  for (int i = 2; i < n; i <<= 1)
    for (int j = 0, l = i >> 1; j != n; j += i)
      for (int k = j; k != j + l; ++k) {
        mod_t u = x[k], v = x[k + l];
        x[k] = u + v, x[k + l] = u - v;
      }
  const mod_t iv(mod_t(n).inv());
  for (int j = 0, l = n >> 1; j != l; ++j) {
    mod_t u = x[j] * iv, v = x[j + l] * iv;
    x[j] = u + v, x[j + l] = u - v;
  }
}

/**
 * @brief XOR 卷积
 */
template <typename mod_t>
std::vector<mod_t> dyadic_convolve(const std::vector<mod_t> &x, const std::vector<mod_t> &y) {
  int len = 1, mlen = std::max(x.size(), y.size());
  while (len < mlen) len <<= 1;
  std::vector<mod_t> res(len);
  std::copy(x.begin(), x.end(), res.begin());
  std::fill(res.begin() + x.size(), res.end(), mod_t(0));
  Walsh_trans(len, res.data());
  if (&x == &y) {
    for (int i = 0; i < len; ++i) res[i] *= res[i];
  } else {
    std::vector<mod_t> y_tmp(len);
    std::copy(y.begin(), y.end(), y_tmp.begin());
    std::fill(y_tmp.begin() + y.size(), y_tmp.end(), mod_t(0));
    Walsh_trans(len, y_tmp.data());
    for (int i = 0; i < len; ++i) res[i] *= y_tmp[i];
  }
  Walsh_itrans(len, res.data());
  return res;
}

} // namespace lib

#endif