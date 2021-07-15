#ifndef CHARACTERISTIC_POLYNOMIAL_HEADER_HPP
#define CHARACTERISTIC_POLYNOMIAL_HEADER_HPP

/**
 * @brief characteristic polynomial / 特征多项式
 *
 */

#include <vector>

namespace lib {

/**
 * @brief 获取方阵的特征多项式
 * @note 特征多项式 det(xI-m) 而非 det(m-xI)
 * @tparam Type 方阵中的元素
 * @param m 方阵 m
 * @return std::vector<Type>
 */
template <typename MatType, typename Type = typename MatType::value_type>
std::vector<Type> get_charpoly(const MatType &m) {
  auto h = m.to_upper_Hessenberg();
  int n  = m.row();
  std::vector<std::vector<Type>> p(n + 1);
  p[0] = {Type(1)};
  for (int i = 1; i <= n; ++i) {
    const std::vector<Type> &pi_1 = p[i - 1];
    std::vector<Type> &pi         = p[i];
    pi.resize(i + 1, Type(0));
    Type v = -h.at(i - 1, i - 1);
    for (int j = 0; j < i; ++j) {
      pi[j] += pi_1[j] * v;
      pi[j + 1] += pi_1[j];
    }
    Type t(1);
    for (int j = 1; j < i; ++j) {
      t *= h.at(i - j, i - j - 1);
      Type prod = t * h.at(i - j - 1, i - 1);
      if (prod == Type(0)) continue;
      for (int k = 0; k <= i - j - 1; ++k) pi[k] -= prod * p[i - j - 1][k];
    }
  }
  return p[n];
}

} // namespace lib

#endif
