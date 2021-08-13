#ifndef POLYNOMIAL_GCD_HEADER_HPP
#define POLYNOMIAL_GCD_HEADER_HPP

/**
 * @brief polynomial Euclidean algorithm
 * @docs docs/math/formal_power_series/poly_gcd.md
 */

#include <algorithm>
#include <cassert>
#include <optional>
#include <utility>

namespace lib {

template <typename PolyType>
struct PolyGCDMat {
public:
  PolyType m00, m01, m10, m11;
  /*
   * 2×2 的矩阵形如
   * [m00 m01]
   * [m10 m11]
   */
  PolyGCDMat(const PolyType &m00, const PolyType &m01, const PolyType &m10, const PolyType &m11)
      : m00(m00), m01(m01), m10(m10), m11(m11) {}
  ~PolyGCDMat()                  = default;
  PolyGCDMat(const PolyGCDMat &) = default;
  PolyGCDMat &operator=(const PolyGCDMat &) = default;
  bool is_identity_matrix() const {
    return m01.deg() == -1 && m10.deg() == -1 && m00.deg() == 0 && m00[0] == 1 && m11.deg() == 0 &&
           m11[0] == 1;
  }
  PolyGCDMat operator*(const PolyGCDMat &rhs) const {
    if (is_identity_matrix()) return rhs;
    if (rhs.is_identity_matrix()) return *this;
    return PolyGCDMat(m00 * rhs.m00 + m01 * rhs.m10, m00 * rhs.m01 + m01 * rhs.m11,
                      m10 * rhs.m00 + m11 * rhs.m10, m10 * rhs.m01 + m11 * rhs.m11);
  }
  std::pair<PolyType, PolyType> operator*(const std::pair<PolyType, PolyType> &rhs) const {
    if (is_identity_matrix()) return rhs;
    return std::make_pair(m00 * rhs.first + m01 * rhs.second, m10 * rhs.first + m11 * rhs.second);
  }
};

template <typename PolyType>
PolyGCDMat<PolyType> hgcd(const PolyType &A, const PolyType &B) {
  assert(A.deg() > B.deg());
  assert(B.deg() >= 0);
  int m = ((A.deg() - 1) >> 1) + 1;
  if (B.deg() < m) return PolyGCDMat<PolyType>({1}, {0}, {0}, {1});
  auto R      = hgcd<PolyType>(PolyType(A.begin() + m, A.end()), PolyType(B.begin() + m, B.end()));
  auto [C, D] = R * std::make_pair(A, B);
  if (D.deg() < m) return R;
  auto [Q, E] = C.divmod(D);
  if (E.deg() < m) return PolyGCDMat<PolyType>({0}, {1}, {1}, -Q) * R;
  int k = (m << 1) - D.deg();
  return hgcd<PolyType>(PolyType(D.begin() + k, D.end()), PolyType(E.begin() + k, E.end())) *
         PolyGCDMat<PolyType>({0}, {1}, {1}, -Q) * R;
}

template <typename PolyType>
PolyGCDMat<PolyType> cogcd(const PolyType &A, const PolyType &B) {
  assert(A.deg() > B.deg());
  assert(B.deg() >= 0);
  auto M1     = hgcd<PolyType>(A, B);
  auto [C, D] = M1 * std::make_pair(A, B);
  if (D.deg() == -1) return M1;
  auto [Q, E] = C.divmod(D);
  if (E.deg() == -1) return PolyGCDMat<PolyType>({0}, {1}, {1}, -Q) * M1;
  return cogcd<PolyType>(D, E) * PolyGCDMat<PolyType>({0}, {1}, {1}, -Q) * M1;
}

template <typename PolyType>
std::optional<PolyType> poly_inv(const PolyType &A, const PolyType &mod) {
  auto A_mod     = A % mod;
  auto M         = cogcd<PolyType>(mod, A_mod);
  auto gcd_A_mod = M.m00 * mod + M.m01 * A_mod;
  if (gcd_A_mod.deg() != 0) return {};
  auto t = gcd_A_mod[0].inv();
  std::for_each(M.m01.begin(), M.m01.end(), [&t](auto &v) { v *= t; });
  return M.m01;
}

} // namespace lib

#endif