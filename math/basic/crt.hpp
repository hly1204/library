#ifndef CHINESE_REMAINDER_THEOREM_HEADER_HPP
#define CHINESE_REMAINDER_THEOREM_HEADER_HPP

/**
 * @brief Chinese remainder theorem / 中国剩余定理
 * @docs docs/math/basic/crt.md
 */

#include <cassert>
#include <cstdint>
#include <optional>
#include <vector>

#include "binary_mul.hpp"
#include "exgcd.hpp"

namespace lib {

/**
 * @brief 中国剩余定理合并模数互素的同余式（ Garner 算法）
 * @note 如果多次合并同样模数的可以预处理
 */
template <typename T>
class CoprimeCRT {
public:
  using u64 = std::uint64_t;

  CoprimeCRT() = default;

  /**
   * @note 假设 m 数组中所有元素的乘积在 std::int64_t 表示范围内
   */
  CoprimeCRT(const std::vector<T> &m) : m_(m), C_(m.size()) {
    int n    = m_.size();
    u64 prod = 1;
    for (int i = 0; i < n; ++i) {
      C_[i] = inv_mod(prod % m_[i], m_[i]);
      prod *= m_[i];
    }
  }

  ~CoprimeCRT() = default;

  void set_m(const std::vector<T> &m) {
    m_    = m;
    int n = m_.size();
    C_.resize(n);
    u64 prod = 1;
    for (int i = 0; i < n; ++i) {
      C_[i] = inv_mod(prod % m_[i], m_[i]);
      prod *= m_[i];
    }
  }

  u64 operator()(const std::vector<T> &v) const {
    int n = m_.size();
    assert(v.size() == n);
    u64 x = 0, prod = 1;
    for (int i = 0; i < n; ++i) {
      x += mul_mod(v[i] + m_[i] - x % m_[i], C_[i], m_[i]) * prod;
      prod *= m_[i];
    }
    return x;
  }

private:
  std::vector<T> m_, C_;
};

template <typename T>
std::optional<std::pair<std::uint64_t, std::uint64_t>> crt2(T a1, T m1, T a2, T m2) {
  using u64 = std::uint64_t;
  using i64 = std::int64_t;
  using S   = std::make_signed_t<T>;

  if (m1 < m2) return crt2(a2, m2, a1, m1);

  S d, x, y;
  std::tie(d, x, y) = exgcd(m1, m2);
  S a2_a1           = S(a2) - S(a1);
  S a2_a1_d         = a2_a1 / d;
  if (a2_a1 != a2_a1_d * d) return {};
  S m2_d = m2 / d;
  S k1   = i64(x % m2_d) * (a2_a1_d % m2_d) % m2_d;
  if (k1 < 0) k1 += m2_d;
  return std::make_pair(u64(k1) * m1 + a1, u64(m1) * m2_d);
}

/**
 * @brief 中国剩余定理合并同余式
 *
 * @tparam T 元素类型
 * @param v 余数
 * @param m 模数
 * @return std::optional<std::pair<T, T>> 若无解则返回 std::nullopt 否则返回 (remainder, modular)
 */
template <typename T>
std::optional<std::pair<std::uint64_t, std::uint64_t>> crt(const std::vector<T> &v,
                                                           const std::vector<T> &m) {
  int n = v.size();
  assert(n == m.size());
  std::uint64_t V = 0, M = 1;
  for (int i = 0; i < n; ++i) {
    auto res = crt2<std::int64_t>(v[i], m[i], V, M);
    if (!res) return {};
    std::tie(V, M) = res.value();
  }
  return std::make_pair(V, M);
}

} // namespace lib

#endif