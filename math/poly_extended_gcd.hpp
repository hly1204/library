#ifndef POLY_EXTENDED_GCD_HPP
#define POLY_EXTENDED_GCD_HPP

#include "../common.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <optional>
#include <utility>

LIB_BEGIN

// helper class for Euclidean algorithm
template <typename PolyT>
class polynomial_gcd_matrix : public std::array<std::array<PolyT, 2>, 2> {
  using MyBase = std::array<std::array<PolyT, 2>, 2>;

public:
  polynomial_gcd_matrix(const PolyT &m00, const PolyT &m01, const PolyT &m10, const PolyT &m11)
      : MyBase{std::array<PolyT, 2>{m00, m01}, std::array<PolyT, 2>{m10, m11}} {}
  polynomial_gcd_matrix operator*(const polynomial_gcd_matrix &rhs) const {
    return polynomial_gcd_matrix((*this)[0][0] * rhs[0][0] + (*this)[0][1] * rhs[1][0],
                                 (*this)[0][0] * rhs[0][1] + (*this)[0][1] * rhs[1][1],
                                 (*this)[1][0] * rhs[0][0] + (*this)[1][1] * rhs[1][0],
                                 (*this)[1][0] * rhs[0][1] + (*this)[1][1] * rhs[1][1]);
  }
  std::array<PolyT, 2> operator*(const std::array<PolyT, 2> &rhs) const {
    return {(*this)[0][0] * rhs[0] + (*this)[0][1] * rhs[1],
            (*this)[1][0] * rhs[0] + (*this)[1][1] * rhs[1]};
  }
};

namespace detail {

template <typename PolyT>
polynomial_gcd_matrix<PolyT> hgcd(const PolyT &A, const PolyT &B) {
  assert(A.deg() > B.deg());
  assert(!B.is_zero());
  int m = (A.deg() + 1) >> 1;
  if (B.deg() < m) return polynomial_gcd_matrix<PolyT>({1}, {}, {}, {1});
  auto R      = hgcd(PolyT(A.cbegin() + m, A.cend()), PolyT(B.cbegin() + m, B.cend()));
  auto [C, D] = R * std::array<PolyT, 2>{A, B};
  if (D.deg() < m) return R;
  auto [Q, E] = C.div_with_rem(D);
  if (E.deg() < m) return polynomial_gcd_matrix<PolyT>({}, {1}, {1}, -Q) * R;
  int k = (m << 1) - D.deg();
  return hgcd(PolyT(D.cbegin() + k, D.cend()), PolyT(E.cbegin() + k, E.cend())) *
         polynomial_gcd_matrix<PolyT>({}, {1}, {1}, -Q) * R;
}

template <typename PolyT>
polynomial_gcd_matrix<PolyT> cogcd(const PolyT &A, const PolyT &B) {
  assert(A.deg() > B.deg());
  assert(!B.is_zero());
  polynomial_gcd_matrix<PolyT> M({1}, {}, {}, {1});
  PolyT A_cpy(A), B_cpy(B);
  for (;;) {
    M           = hgcd(A_cpy, B_cpy) * M;
    auto [C, D] = M * std::array<PolyT, 2>{A_cpy, B_cpy};
    if (D.is_zero()) return M;
    auto [Q, E] = C.div_with_rem(D);
    M           = polynomial_gcd_matrix<PolyT>({}, {1}, {1}, -Q) * M;
    if (E.is_zero()) return M;
    A_cpy.swap(D), B_cpy.swap(E);
  }
}

} // namespace detail

template <typename PolyT>
polynomial_gcd_matrix<PolyT> poly_ext_gcd(const PolyT &A, const PolyT &B) {
  if (B.is_zero()) return polynomial_gcd_matrix<PolyT>({1}, {}, {}, {1});
  if (A.is_zero()) return polynomial_gcd_matrix<PolyT>({}, {1}, {1}, {});
  auto [Q, R] = A.div_with_rem(B);
  polynomial_gcd_matrix<PolyT> M({}, {1}, {1}, -Q);
  return R.is_zero() ? M : detail::cogcd(B, R) * M;
}

template <typename PolyT>
std::optional<PolyT> poly_inv(const PolyT &A, const PolyT &modular) {
  auto M = poly_ext_gcd(A, modular);
  auto d = M[0][0] * A + M[0][1] * modular;
  if (d.deg() != 0) return {};
  std::for_each(M[0][0].begin(), M[0][0].end(), [iv = d.front().inv()](auto &v) { v *= iv; });
  return M[0][0];
}

LIB_END

#endif