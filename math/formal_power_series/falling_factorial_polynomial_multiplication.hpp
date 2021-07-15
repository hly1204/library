#ifndef FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP
#define FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP

/**
 * @brief falling factorial polynomial multiplication / 下降幂多项式乘法
 *
 */

#include <vector>

#include "radix_2_NTT.hpp"

namespace lib {

/**
 * @brief 样本点转换为下降幂多项式
 *
 * @tparam mod_t NTT 友好的模数
 * @tparam PolyType 多项式类
 * @param pts f(0), f(1), …, f(n-1)
 * @param ffp 下降幂多项式 f 满足 deg(f)<n
 */
template <typename mod_t, typename PolyType>
void sample_points_to_FFP(const std::vector<mod_t> &pts, PolyType &ffp) {}

/**
 * @brief 下降幂多项式转换为样本点
 *
 * @tparam mod_t NTT 友好的模数
 * @tparam PolyType 多项式类
 * @param ffp 下降幂多项式 f 满足 deg(f)<n
 * @param pts f(0), f(1), …, f(n-1)
 */
template <typename mod_t, typename PolyType>
void FFP_to_sample_points(const PolyType &ffp, std::vector<mod_t> &pts) {}

/**
 * @brief 下降幂多项式乘法
 */
template <typename PolyType>
PolyType mul_FFP(const PolyType &lhs, const PolyType &rhs) {}

} // namespace lib

#endif