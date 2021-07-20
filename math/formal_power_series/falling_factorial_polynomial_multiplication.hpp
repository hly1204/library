#ifndef FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP
#define FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP

/**
 * @brief falling factorial polynomial multiplication / 下降幂多项式乘法
 * @docs docs/math/formal_power_series/falling_factorial_polynomial_multiplication.md
 */

#include <algorithm>
#include <type_traits>
#include <utility>
#include <vector>

#include "convolution.hpp"
#include "prime_binomial.hpp"

namespace lib {

/**
 * @brief 样本点转换为下降幂多项式
 *
 * @tparam mod_t NTT 友好的模数
 * @param pts f(0), f(1), …, f(n-1)
 * @return std::vector<mod_t> 下降幂多项式系数
 */
template <typename mod_t>
std::vector<mod_t> sample_points_to_FFP(const std::vector<mod_t> &pts) {
  int n = pts.size();
  PrimeBinomial<mod_t> bi(n);
  std::vector<mod_t> emx(n), pts_egf(n);
  for (int i = 0; i < n; ++i) {
    pts_egf[i] = pts[i] * (emx[i] = bi.ifac_unsafe(i));
    if (i & 1) emx[i] = -emx[i];
  }
  pts_egf = std::move(convolve(emx, pts_egf));
  pts_egf.resize(n);
  return pts_egf;
}

/**
 * @brief 下降幂多项式转换为样本点
 *
 * @tparam mod_t NTT 友好的模数
 * @param n
 * @param ffp 下降幂多项式
 * @return std::vector<mod_t> f(0), f(1), …, f(n-1)
 */
template <typename mod_t>
std::vector<mod_t> FFP_to_sample_points(int n, const std::vector<mod_t> &ffp) {
  PrimeBinomial<mod_t> bi(n);
  std::vector<mod_t> ex(n);
  for (int i = 0; i < n; ++i) ex[i] = bi.ifac_unsafe(i);
  if (ffp.size() > n) {
    ex = std::move(convolve(ex, std::vector<mod_t>(ffp.begin(), ffp.begin() + n)));
  } else {
    ex = std::move(convolve(ex, ffp));
  }
  for (int i = 0; i < n; ++i) ex[i] *= bi.fac_unsafe(i);
  ex.resize(n);
  return ex;
}

/**
 * @brief 下降幂多项式乘法
 * @note 这里若展开写可以节省一次 DFT
 */
template <typename mod_t>
std::vector<mod_t> convolve_FFP(const std::vector<mod_t> &lhs, const std::vector<mod_t> &rhs) {
  int d = lhs.size() + rhs.size() - 1;
  std::vector<mod_t> lhs_pts(FFP_to_sample_points(d, lhs)), rhs_pts(FFP_to_sample_points(d, rhs));
  for (int i = 0; i < d; ++i) lhs_pts[i] *= rhs_pts[i];
  return sample_points_to_FFP(lhs_pts);
}

/**
 * @brief 下降幂多项式平移
 */
template <typename mod_t>
std::vector<mod_t> shift_FFP(const std::vector<mod_t> &ffp, mod_t c) {
  int n = ffp.size();
  PrimeBinomial<mod_t> bi(n);
  std::vector<mod_t> A(ffp), B(n);
  mod_t c_i(1);
  for (int i = 0; i < n; ++i)
    A[i] *= bi.fac_unsafe(i), B[i] = c_i * bi.ifac_unsafe(i), c_i *= c - mod_t(i);
  std::reverse(A.begin(), A.end());
  A = std::move(convolve(A, B));
  A.resize(n);
  std::reverse(A.begin(), A.end());
  for (int i = 0; i < n; ++i) A[i] *= bi.ifac_unsafe(i);
  return A;
}

} // namespace lib

#endif