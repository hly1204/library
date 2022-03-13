#ifndef FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP
#define FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP

#include <algorithm>
#include <cassert>
#include <vector>

#include "prime_binomial.hpp"

namespace lib {

// f(0), f(1), …, f(n-1) => 下降幂多项式系数
template <typename mod_t, typename ConvolveFuncType>
std::vector<mod_t> sample_points_to_FFP(const std::vector<mod_t> &pts, ConvolveFuncType &&f) {
  int n = pts.size();
  assert(n <= mod_t::get_mod());
  PrimeBinomial<mod_t> bi(n);
  std::vector<mod_t> emx(n), pts_egf(n);
  for (int i = 0; i < n; ++i) {
    pts_egf[i] = pts[i] * (emx[i] = bi.ifac_unsafe(i));
    if (i & 1) emx[i] = -emx[i];
  }
  pts_egf = f(emx, pts_egf);
  pts_egf.resize(n);
  return pts_egf;
}

// 下降幂多项式系数 => f(0), f(1), …, f(n-1)
// 素数模数且多项式度数小于模数！
template <typename mod_t, typename ConvolveFuncType>
std::vector<mod_t> FFP_to_sample_points(int n, const std::vector<mod_t> &ffp,
                                        ConvolveFuncType &&f) {
  assert(ffp.size() <= mod_t::get_mod());
  PrimeBinomial<mod_t> bi(n);
  std::vector<mod_t> ex(n);
  for (int i = 0; i < n; ++i) ex[i] = bi.ifac_unsafe(i);
  if (ffp.size() > n) ex = f(ex, std::vector<mod_t>(ffp.begin(), ffp.begin() + n));
  else
    ex = f(ex, ffp);
  for (int i = 0; i < n; ++i) ex[i] *= bi.fac_unsafe(i);
  ex.resize(n);
  return ex;
}

// 下降幂多项式乘法
template <typename mod_t, typename ConvolveFuncType>
std::vector<mod_t> convolve_FFP(const std::vector<mod_t> &lhs, const std::vector<mod_t> &rhs,
                                ConvolveFuncType &&f) {
  int d = lhs.size() + rhs.size() - 1;
  std::vector<mod_t> lhs_pts(FFP_to_sample_points(d, lhs, f)),
      rhs_pts(FFP_to_sample_points(d, rhs, f));
  for (int i = 0; i < d; ++i) lhs_pts[i] *= rhs_pts[i];
  return sample_points_to_FFP(lhs_pts, f);
}

// 下降幂多项式平移
template <typename mod_t, typename ConvolveFuncType>
std::vector<mod_t> shift_FFP(const std::vector<mod_t> &ffp, mod_t c, ConvolveFuncType &&f) {
  assert(ffp.size() <= mod_t::get_mod());
  int n = ffp.size();
  PrimeBinomial<mod_t> bi(n);
  std::vector<mod_t> A(ffp), B(n);
  mod_t c_i(1);
  for (int i = 0; i < n; ++i)
    A[i] *= bi.fac_unsafe(i), B[i] = c_i * bi.ifac_unsafe(i), c_i *= c - mod_t(i);
  std::reverse(A.begin(), A.end());
  A = f(A, B);
  A.resize(n);
  std::reverse(A.begin(), A.end());
  for (int i = 0; i < n; ++i) A[i] *= bi.ifac_unsafe(i);
  return A;
}

} // namespace lib

#endif