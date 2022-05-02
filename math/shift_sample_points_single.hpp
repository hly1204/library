#ifndef SHIFT_SAMPLE_POINTS_SINGLE_HPP
#define SHIFT_SAMPLE_POINTS_SINGLE_HPP

#include "../common.hpp"

#include <vector>

LIB_BEGIN

template <typename ModIntT>
ModIntT shift_sample_points(const std::vector<ModIntT> &f, ModIntT c) {
  const int n = static_cast<int>(f.size());
  if (n == 0) return ModIntT();
  std::vector<ModIntT> inv(n), k(n);
  ModIntT v(1);
  for (int i = 1; i != n; ++i) inv[i] = v, v *= i;
  v = v.inv();
  for (int i = n - 1; i != 0; --i) inv[i] *= v, v *= i;
  k.front() = f.front();
  for (int i = 1; i != n; ++i) k[i] = f[i] * (v *= (c - (i - 1)) * inv[i]);
  ModIntT res(k.back());
  v = 1;
  for (int i = n - 2; i >= 0; --i) res += k[i] * (v *= -(c - (i + 1)) * inv[n - 1 - i]);
  return res;
}

LIB_END

#endif