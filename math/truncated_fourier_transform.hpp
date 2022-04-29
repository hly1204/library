#ifndef TRUNCATED_FOURIER_TRANSFORM_HPP
#define TRUNCATED_FOURIER_TRANSFORM_HPP

#include "../common.hpp"
#include "radix2_ntt.hpp"

#include <vector>

LIB_BEGIN

template <typename ContainerT>
void tft(ContainerT &&a, int n) {
  using T                  = typename ContainerT::value_type;
  static constexpr auto rt = detail::root<T>();
  static std::vector<T> root(1);
  int len = ntt_len(std::max(n, static_cast<int>(a.size())));
  if (int s = static_cast<int>(root.size()); s << 1 < len) {
    root.resize(len >> 1);
    for (int i = detail::bsf(s), j; 1 << i < len >> 1; ++i) {
      root[j = 1 << i] = rt[i];
      for (int k = j + 1; k < j << 1; ++k) root[k] = root[k - j] * root[j];
    }
  }
  a.resize(len);
  for (int j = 0, l = len >> 1; j != l; ++j) {
    T u(a[j]), v(a[j + l]);
    a[j] = u + v, a[j + l] = u - v;
  }
  for (int i = len >> 1; i >= 2; i >>= 1) {
    for (int j = 0, l = i >> 1; j != l; ++j) {
      T u(a[j]), v(a[j + l]);
      a[j] = u + v, a[j + l] = u - v;
    }
    for (int j = i, l = i >> 1, m = 1; j < n && j != len; j += i, ++m)
      for (int k = j; k != j + l; ++k) {
        T u(a[k]), v(a[k + l] * root[m]);
        a[k] = u + v, a[k + l] = u - v;
      }
  }
  a.resize(n);
}

LIB_END

#endif