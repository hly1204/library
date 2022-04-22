#ifndef CZT_HPP
#define CZT_HPP

#include "../common.hpp"
#include "radix2_ntt.hpp"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

LIB_BEGIN

// Chirp Z-transform
// Input:  A(x) = `a[0]` + `a[1]`x + ..., constant `c`, and integer `n`.
// Output: [A(1), A(c), A(c^2), ..., A(c^(n - 1))].
template <typename ModIntT>
std::vector<ModIntT> czt(const std::vector<ModIntT> &a, const ModIntT &c, int n) {
  assert(n >= 0);
  if (n == 0) return std::vector<ModIntT>{};
  int m = static_cast<int>(a.size());
  while (m > 0 && a[m - 1].is_zero()) --m;
  if (m == 0) return std::vector<ModIntT>(n);
  if (c.is_zero()) {
    std::vector<ModIntT> res(n, a.front());
    res.front() = std::accumulate(a.begin(), a.begin() + m, ModIntT());
    return res;
  }
  const int sz = n + m - 1, len = ntt_len(sz), nm_max = std::max(n, m);
  std::vector<ModIntT> a_cpy(len), c_binom{1, 1}, ic_binom{1, 1};
  c_binom.resize(len);
  ic_binom.resize(nm_max);
  {
    const ModIntT ic(c.inv());
    ModIntT c_temp(1), ic_temp(1);
    for (int i = 2; i < sz; ++i) c_binom[i] = c_binom[i - 1] * (c_temp *= c);
    for (int i = 2; i < nm_max; ++i) ic_binom[i] = ic_binom[i - 1] * (ic_temp *= ic);
  }
  for (int i = 0; i != m; ++i) a_cpy[m - 1 - i] = a[i] * ic_binom[i];
  dft(a_cpy), dft(c_binom);
  for (int i = 0; i != len; ++i) a_cpy[i] *= c_binom[i];
  idft(a_cpy);
  a_cpy.erase(a_cpy.begin(), a_cpy.begin() + m - 1);
  a_cpy.resize(n);
  for (int i = 0; i != n; ++i) a_cpy[i] *= ic_binom[i];
  return a_cpy;
}

LIB_END

#endif