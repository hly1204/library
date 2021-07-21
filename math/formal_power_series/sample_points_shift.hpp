#ifndef SAMPLE_POINTS_SHIFT_HEADER_HPP
#define SAMPLE_POINTS_SHIFT_HEADER_HPP

/**
 * @brief sample points shift / 样本点平移
 * @docs docs/math/formal_power_series/sample_points_shift.md
 */

#include <cassert>
#include <functional>
#include <numeric>
#include <vector>

#include "falling_factorial_polynomial_multiplication.hpp"
#include "prime_binomial.hpp"

namespace lib {

/**
 * @brief 样本点平移（通过下降幂多项式平移）
 *
 * @tparam mod_t 素数模数且点数不能超过模数！
 * @tparam ConvolveFuncType
 * @param n 返回值的点数，需大于零
 * @param pts f(0), f(1), …, f(k-1) 确定一个唯一多项式 mod x^{\underline{k}}
 * @param m 平移距离 f(x) => f(x+m)
 * @param f 卷积函数
 * @return std::vector<mod_t> f(m), f(m+1), …, f(m+n-1)
 */
template <typename mod_t, typename ConvolveFuncType>
std::vector<mod_t> shift_sample_points_via_FFP(int n, const std::vector<mod_t> &pts, mod_t m,
                                               ConvolveFuncType f) {
  return FFP_to_sample_points(n, shift_FFP(sample_points_to_FFP(pts, f), m, f));
}

template <typename mod_t, typename ConvolveFuncType>
std::vector<mod_t> shift_sample_points_via_FFP(const std::vector<mod_t> &pts, mod_t m,
                                               ConvolveFuncType f) {
  return shift_sample_points_via_FFP(pts.size(), pts, m, f);
}

/**
 * @brief 样本点平移（通过拉格朗日插值公式）
 * @note 不安全的算法
 * @tparam mod_t 素数模数且点数不能超过模数！
 * @tparam ConvolveCyclicFuncType
 * @param n 返回值的点数，需大于零
 * @param pts f(0), f(1), …, f(k-1) 确定一个唯一多项式 mod x^{\underline{k}}
 * @param m 平移距离 f(x) => f(x+m)
 * @param f 循环卷积函数
 * @return std::vector<mod_t> f(m), f(m+1), …, f(m+n-1)
 */
template <typename mod_t, typename ConvolveCyclicFuncType>
std::vector<mod_t> shift_sample_points_unsafe(int n, const std::vector<mod_t> &pts, mod_t m,
                                              ConvolveCyclicFuncType f) {
  int s = pts.size(), deg_A = s - 1;
  PrimeBinomial<mod_t> bi(s);
  std::vector<mod_t> A(s), B(deg_A + n), p_sum(deg_A + n);
  for (int i = 0; i < s; ++i) {
    A[i] = pts[i] * bi.ifac_unsafe(i) * bi.ifac_unsafe(deg_A - i);
    if ((deg_A - i) & 1) A[i] = -A[i];
  }
  const mod_t ZERO(0);
  for (int i = 0; i < deg_A + n; ++i) {
    B[i] = m + mod_t(i - deg_A);
    assert(B[i] != ZERO);
  }
  std::partial_sum(B.begin(), B.end(), p_sum.begin(), std::multiplies<>());
  mod_t p_inv = mod_t(1) / p_sum.back();
  for (int i = deg_A + n - 1; i > 0; --i) {
    mod_t t = p_inv * B[i];
    B[i]    = p_inv * p_sum[i - 1];
    p_inv   = t;
  }
  B[0] = p_inv;
  A    = f(A, B, get_ntt_len(s + s - 1 + n - (s < 2 ? 0 : deg_A - 1) - 1));
  mod_t coeff(m);
  for (int i = 1; i < s; ++i) coeff *= m - mod_t(i);
  for (int i = 0; i < n; ++i) A[i] = A[deg_A + i] * coeff, coeff *= (m + mod_t(i + 1)) * B[i];
  A.resize(n);
  return A;
}

template <typename mod_t, typename ConvolveCyclicFuncType>
std::vector<mod_t> shift_sample_points_unsafe(const std::vector<mod_t> &pts, mod_t m,
                                              ConvolveCyclicFuncType f) {
  return shift_sample_points_unsafe(pts.size(), pts, m, f);
}

} // namespace lib

#endif