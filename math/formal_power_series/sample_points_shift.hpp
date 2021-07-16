#ifndef SAMPLE_POINTS_SHIFT_HEADER_HPP
#define SAMPLE_POINTS_SHIFT_HEADER_HPP

/**
 * @brief sample points shift / 样本点平移
 *
 */

#include <type_traits>
#include <vector>

#include "falling_factorial_polynomial_multiplication.hpp"

namespace lib {

/**
 * @brief 样本点平移（通过下降幂多项式平移）
 *
 * @tparam PolyType 多项式类
 * @tparam mod_t NTT 友好的模数
 * @param n 返回值的点数，需大于零
 * @param pts f(0), f(1), …, f(k-1) 确定一个唯一多项式 mod x^{\underline{k}}
 * @param m 平移距离 f(x) => f(x+m)
 * @return std::vector<mod_t> f(m), f(m+1), …, f(m+n-1)
 */
template <typename PolyType, typename mod_t>
std::enable_if_t<std::is_same_v<typename PolyType::value_type, mod_t>, std::vector<mod_t>>
shift_sample_points_via_FFP(int n, const std::vector<mod_t> &pts, mod_t m) {
  return FFP_to_sample_points(n, shift_FFP(sample_points_to_FFP<PolyType>(pts), m));
}

} // namespace lib

#endif