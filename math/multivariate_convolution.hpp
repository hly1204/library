#ifndef MULTIVARIATE_CONVOLUTION_HPP
#define MULTIVARIATE_CONVOLUTION_HPP

#include "../common.hpp"
#include "truncated_fourier_transform.hpp"

#include <algorithm>
#include <cassert>
#include <vector>

LIB_BEGIN

template <typename ModIntT>
std::vector<ModIntT> multivariate_convolution(const std::vector<ModIntT> &lhs,
                                              const std::vector<ModIntT> &rhs,
                                              const std::vector<int> n) {
  const int d   = std::max(1, static_cast<int>(n.size()));
  const int len = static_cast<int>(lhs.size());
  assert(rhs.size() == len);
  std::vector<int> base(d - 1);
  if (d > 1) base.front() = n.front();
  for (int i = 1; i < d - 1; ++i) base[i] = base[i - 1] * n[i];
  auto chi_mod = [&base, d](int i) {
    int x = 0;
    for (int v : base) x += i / v;
    return x % d;
  };
  std::vector<int> chi(len);
  for (int i = 0; i != len; ++i) chi[i] = chi_mod(i);
  std::vector<std::vector<ModIntT>> a(d, std::vector<ModIntT>(len << 1)),
      b(d, std::vector<ModIntT>(len << 1)), ab(d, std::vector<ModIntT>(len << 1));
  for (int i = 0; i != len; ++i) a[chi[i]][i] = lhs[i], b[chi[i]][i] = rhs[i];
  for (auto &&i : a) tft(i);
  for (auto &&i : b) tft(i);
  for (int i = 0; i != d; ++i)
    for (int j = 0; j != d; ++j)
      for (int k = 0, l = i + j < d ? i + j : i + j - d; k != len << 1; ++k)
        ab[l][k] += a[i][k] * b[j][k];
  for (auto &&i : ab) itft(i);
  std::vector<ModIntT> res(len);
  for (int i = 0; i != len; ++i) res[i] = ab[chi[i]][i];
  return res;
}

LIB_END

#endif