#ifndef CHIRP_Z_HEADER_HPP
#define CHIRP_Z_HEADER_HPP

/**
 * @brief chirp z transform
 * @docs docs/math/formal_power_series/chirp_z.md
 */

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#include "radix_2_NTT.hpp"

namespace lib {

/**
 * @brief chirp z 变换
 * @tparam mod_t 为 NTT 友好的模数
 * @param n czt 的长度
 * @param A 多项式
 * @param c
 * @return std::vector<mod_t> A(1), A(c), A(c^2), …, A(c^{n-1})
 */
template <typename mod_t>
std::vector<mod_t> czt(int n, const std::vector<mod_t> &A, mod_t c) {
  const mod_t ZERO(0);
  assert(c != ZERO);
  assert(!A.empty());
  int m = A.size();
  while (m > 0 && A[m - 1] == ZERO) --m;
  if (m <= 1) return std::vector<mod_t>(n, A.front());
  int sz = n + m - 1, len = get_ntt_len(sz), nm_max = std::max(n, m);
  std::vector<mod_t> A_0(A);
  A_0.resize(len, ZERO);
  mod_t c_tmp(1), ic = mod_t(1) / c, ic_tmp(1);
  std::vector<mod_t> c_choose(sz), ic_choose(nm_max);
  for (int i = 0; i < 2 && i < sz; ++i) c_choose[i] = c_tmp;
  for (int i = 2; i < sz; ++i) c_choose[i] = c_choose[i - 1] * (c_tmp *= c);
  for (int i = 0; i < 2 && i < nm_max; ++i) ic_choose[i] = ic_tmp;
  for (int i = 2; i < nm_max; ++i) ic_choose[i] = ic_choose[i - 1] * (ic_tmp *= ic);
  c_choose.resize(len, ZERO);
  for (int i = 0; i < m; ++i) A_0[i] *= ic_choose[i];
  std::reverse(A_0.begin(), A_0.begin() + m);
  dft(A_0), dft(c_choose);
  for (int i = 0; i < len; ++i) c_choose[i] *= A_0[i];
  idft(c_choose);
  c_choose.erase(c_choose.begin(), c_choose.begin() + m - 1);
  c_choose.resize(n);
  for (int i = 0; i < n; ++i) c_choose[i] *= ic_choose[i];
  return c_choose;
}

} // namespace lib

#endif