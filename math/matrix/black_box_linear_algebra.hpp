#ifndef BLACK_BOX_LINEAR_ALGEBRA_HEADER_HPP
#define BLACK_BOX_LINEAR_ALGEBRA_HEADER_HPP

/**
 * @brief black box linear algebra / 黑盒线性代数
 * @docs docs/math/matrix/black_box_linear_algebra.md
 */

#include <algorithm>
#include <cassert>
#include <functional>
#include <numeric>
#include <random>
#include <vector>

#include "../modulo/find_shortest_LFSR_Berlekamp_Massey.hpp"

namespace lib {

template <typename T, typename GenFunc>
std::vector<T> get_rand_vec(int s, GenFunc &gen) {
  std::vector<T> res(s);
  std::generate(res.begin(), res.end(), gen);
  return res;
}

/**
 * @brief 获取矩阵的最小多项式（随机化算法）
 * @note 必须为有限域
 * @ref Douglas H. Wiedemann (1986). Solving Sparse Linear Equations Over Finite Fields.
 * @return std::vector<Type> 首一多项式
 */
template <typename MatType, typename Type = typename MatType::value_type>
std::vector<Type> black_box_minpoly(const MatType &m) {

  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<typename Type::value_type> dis(1, Type::get_mod() - 1);

  auto gen1 = [&dis]() { return dis(gen); };
  auto gen2 = std::bind(get_rand_vec<Type, decltype(gen1)>, std::placeholders::_1, gen1);

  const Type ZERO(0);
  int n = m.row();
  assert(n == m.col());
  std::vector<Type> u(gen2(n)), v(gen2(n)), bilinear_projection(n << 1);
  for (int i = 0; i < (n << 1); ++i) {
    bilinear_projection[i] = std::inner_product(u.begin(), u.end(), v.begin(), ZERO);
    v = m.apply(v); // 不需要写成 std::move 因为编译器会自动优化！
  }
  std::vector<Type> res = find_LFSR(bilinear_projection);
  // 系数翻转！因为在这里 LFSR 返回关系多项式
  // 为了不在数组的开头插入元素故使用 LFSR 中定义的关系多项式更方便
  // 而最小多项式则只需翻转其系数即首一的最小多项式
  std::reverse(res.begin(), res.end());
  return res;
}

/**
 * @brief 获取矩阵的行列式（随机化算法）
 * @note 必须为有限域
 * @ref Douglas H. Wiedemann (1986). Solving Sparse Linear Equations Over Finite Fields.
 */
template <typename MatType, typename Type = typename MatType::value_type>
Type black_box_det(const MatType &m) {

  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<typename Type::value_type> dis(1, Type::get_mod() - 1);

  auto gen1 = [&dis]() { return dis(gen); };
  auto gen2 = std::bind(get_rand_vec<Type, decltype(gen1)>, std::placeholders::_1, gen1);

  const Type ZERO(0);
  int n = m.row();
  assert(n == m.col());
  std::vector<Type> u(gen2(n)), v(gen2(n)), diag(gen2(n)), bilinear_projection(n << 1);
  for (int i = 0; i < (n << 1); ++i) {
    bilinear_projection[i] = std::inner_product(u.begin(), u.end(), v.begin(), ZERO);
    for (int i = 0; i < n; ++i) v[i] *= diag[i];
    v = m.apply(v);
  }
  std::vector<Type> mp = find_LFSR(bilinear_projection);
  Type res = mp.back() / std::accumulate(diag.begin(), diag.end(), Type(1), std::multiplies<>());
  return (n & 1) == 1 ? -res : res;
}

} // namespace lib

#endif