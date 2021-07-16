#ifndef FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP
#define FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP

/**
 * @brief falling factorial polynomial multiplication / 下降幂多项式乘法
 * @docs docs/math/formal_power_series/falling_factorial_polynomial_multiplication.md
 */

#include <vector>

#include "NTT_binomial.hpp"

namespace lib {

/**
 * @brief 样本点转换为下降幂多项式
 *
 * @tparam PolyType 多项式类
 * @tparam PolyType::value_type NTT 友好的模数
 * @param pts f(0), f(1), …, f(n-1)
 * @return PolyType 下降幂多项式
 */
template <typename PolyType, typename mod_t = typename PolyType::value_type>
PolyType sample_points_to_FFP(const std::vector<mod_t> &pts) {
  int n = pts.size();
  NTTBinomial<mod_t> bi(n);
  PolyType emx(n), pts_egf(n);
  for (int i = 0; i < n; ++i) {
    pts_egf[i] = pts[i] * (emx[i] = bi.ifac_unsafe(i));
    if (i & 1) emx[i] = -emx[i];
  }
  return (emx * pts_egf).slice(n);
}

/**
 * @brief 下降幂多项式转换为样本点
 *
 * @tparam PolyType
 * @tparam PolyType::value_type
 * @param n
 * @param ffp 下降幂多项式
 * @return std::vector<mod_t> f(0), f(1), …, f(n-1)
 */
template <typename PolyType, typename mod_t = typename PolyType::value_type>
std::vector<mod_t> FFP_to_sample_points(int n, const PolyType &ffp) {
  NTTBinomial<mod_t> bi(n);
  PolyType ex(n);
  for (int i = 0; i < n; ++i) ex[i] = bi.ifac_unsafe(i);
  ex *= ffp.slice(n);
  std::vector<mod_t> pts(n);
  for (int i = 0; i < n; ++i) pts[i] = ex[i] * bi.fac_unsafe(i);
  return pts;
}

/**
 * @brief 下降幂多项式乘法
 */
template <typename PolyType, typename mod_t = typename PolyType::value_type>
PolyType mul_FFP(const PolyType &lhs, const PolyType &rhs) {
  int d = lhs.size() + rhs.size() - 1;
  std::vector<mod_t> lhs_pts(FFP_to_sample_points(d, lhs)), rhs_pts(FFP_to_sample_points(d, rhs));
  for (int i = 0; i < d; ++i) lhs_pts[i] *= rhs_pts[i];
  return sample_points_to_FFP<PolyType>(lhs_pts);
}

} // namespace lib

#endif