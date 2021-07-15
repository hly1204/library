#ifndef SOLVE_LINEAR_EQUATIONS_LANCZOS_HEADER_HPP
#define SOLVE_LINEAR_EQUATIONS_LANCZOS_HEADER_HPP

/**
 * @brief solve linear equations Lanczos / 求解线性方程组 Lanczos 算法
 *
 */

#include <algorithm>
#include <cassert>
#include <functional>
#include <numeric>
#include <optional>
#include <random>
#include <vector>

namespace lib::internal {

/**
 * @brief 标准 Lanczos 算法
 * @note 要求 M 为对称方阵即转置为自身的方阵
 *       该算法未测试！
 */
template <typename MatType, typename Type = typename MatType::value_type>
std::optional<std::vector<Type>> standard_Lanczos(const MatType &A, const std::vector<Type> &b) {
  int n = b.size();

  assert(A.col() == A.row());
  assert(n == A.row());

  const Type ZERO(0);

  auto is_zero_vec = [ZERO](const std::vector<Type> &v) -> bool {
    return std::count(v.begin(), v.end(), ZERO) == v.size();
  };

  auto dot_product = [ZERO](const std::vector<Type> &a, const std::vector<Type> &b) -> Type {
    // 返回 a^T b 标准的内积
    return std::inner_product(a.begin(), a.end(), b.begin(), ZERO);
  };

  if (is_zero_vec(b)) return std::vector<Type>(n, ZERO);

  Type t_m1(1);
  std::vector<Type> w_m1(n, ZERO), w_0(b);
  std::vector<Type> v_0(w_m1), v_1(A.apply(w_0));
  Type t_0 = dot_product(v_1, w_0);

  if (t_0 == ZERO) return {};

  std::vector<Type> x(b);
  Type tmp_0 = dot_product(w_0, b) / t_0;
  for (auto &i : x) i *= tmp_0;
  for (;;) {
    Type tmp_1 = dot_product(v_1, v_1) / t_0, tmp_2 = dot_product(v_1, v_0) / t_m1;
    for (int i = 0; i < n; ++i) w_m1[i] = v_1[i] - tmp_1 * w_0[i] - tmp_2 * w_m1[i];
    std::swap(w_m1, w_0);
    if (is_zero_vec(w_0)) return A.apply(x) == b ? std::make_optional(x) : std::nullopt;
    std::swap(v_0 = A.apply(w_0), v_1);
    std::swap(t_m1 = dot_product(v_1, w_0), t_0);
    if (t_0 == ZERO) return {};
    Type tmp_3 = dot_product(w_0, b) / t_0;
    for (int i = 0; i < n; ++i) x[i] += tmp_3 * w_0[i];
  }
}

template <typename MatType, typename Type = typename MatType::value_type>
std::optional<std::vector<Type>> randomize_b_Lanczos(const MatType &A, const std::vector<Type> &b) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<typename Type::value_type> dis(1, Type::get_mod() - 1);

  auto gen1 = [&dis](int n) {
    std::vector<Type> res(n);
    for (auto &i : res) i = dis(gen);
    return res;
  };

  int n = b.size();

  std::vector<Type> gamma(gen1(n)), b_hat(A.apply(gamma)); // b_hat = A*gamma + b
  for (int i = 0; i < n; ++i) b_hat[i] += b[i];
  auto res = standard_Lanczos(A, b_hat);
  if (!res) return res;
  for (int i = 0; i < n; ++i) res.value()[i] -= gamma[i];
  return res;
}

} // namespace lib::internal

namespace lib {

// TODO

// /**
//  * @brief 求解线性方程组的随机化 Lanczos 算法
//  * @note 对矩阵不要求其为方阵
//  * @ref Wayne Eberly and Erich Kaltofen. On Randomized Lanczos Algorithms. 1997.
//  * @param A
//  * @param b
//  * @return std::optional<std::vector<Type>> 向量 x 满足 Ax=b
//  */
// template <typename MatType, typename Type = typename MatType::value_type>
// std::optional<std::vector<Type>> solve_linear_equations_Lanczos(const MatType &A,
//                                                                 const std::vector<Type> &b) {
//   return internal::standard_Lanczos(A, b);
// }

} // namespace lib

#endif