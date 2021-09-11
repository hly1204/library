#ifndef SAMPLE_POINTS_SHIFT_HEADER_HPP
#define SAMPLE_POINTS_SHIFT_HEADER_HPP

/**
 * @brief sample points shift
 * @docs docs/math/formal_power_series/sample_points_shift.md
 */

#include <cassert>
#include <cstdint>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

#include "prime_binomial.hpp"
#include "radix_2_NTT.hpp"

namespace lib::internal {

/**
 * @brief 样本点平移（通过拉格朗日插值公式）
 * @note 不安全的算法
 * @tparam mod_t 素数模数且点数不能超过模数！
 * @tparam ConvolveCyclicFuncType
 * @param n 返回值的点数
 * @param pts f(0), f(1), …, f(k-1) 确定一个唯一的度数小于 k 的多项式
 * @param m 平移距离 f(x) => f(x+m)
 * @param f 循环卷积函数
 * @return std::vector<mod_t> f(m), f(m+1), …, f(m+n-1)
 */
template <typename mod_t, typename ConvolveCyclicFuncType>
std::vector<mod_t> shift_sample_points_unsafe(int n, const std::vector<mod_t> &pts, mod_t m,
                                              ConvolveCyclicFuncType &&f) {
  if (n == 0) return {};
  int s = pts.size(), deg_A = s - 1;
  PrimeBinomial<mod_t> bi(s);
  std::vector<mod_t> A(s), B(deg_A + n), p_sum(deg_A + n);
  for (int i = 0; i < s; ++i) {
    A[i] = pts[i] * bi.ifac_unsafe(i) * bi.ifac_unsafe(deg_A - i);
    if ((deg_A - i) & 1) A[i] = -A[i];
  }
  for (int i = 0; i < deg_A + n; ++i) B[i] = m + mod_t(i - deg_A);
  std::partial_sum(B.begin(), B.end(), p_sum.begin(), std::multiplies<>());
  assert(p_sum.back() != mod_t(0));
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
                                              ConvolveCyclicFuncType &&f) {
  return shift_sample_points_unsafe(pts.size(), pts, m, f);
}

} // namespace lib::internal

namespace lib {

template <typename mod_t, typename ConvolveCyclicFuncType>
std::vector<mod_t> shift_sample_points(int n, const std::vector<mod_t> &pts, mod_t m,
                                       ConvolveCyclicFuncType &&f) {
  assert(static_cast<typename mod_t::value_type>(n) <= mod_t::get_mod());
  assert(pts.size() <= mod_t::get_mod());
  if (n == 0) return {};
  using u64 = std::uint64_t;
  u64 m_64 = static_cast<u64>(m), k = pts.size(), nm1 = static_cast<u64>(m + mod_t(n - 1));
  if (m_64 < k) {        // f(0), …, f(m), …, f(k-1)
    if (m_64 + n <= k) { // f(0), …, f(m), …, f(n+m-1), …, f(k-1)
      return std::vector<mod_t>(pts.begin() + m_64, pts.begin() + m_64 + n);
    } else if (nm1 < k) { // f(0), …, f(n+m-1), …, f(m), …, f(k-1), …, f(mod-1)
      std::vector<mod_t> res;
      res.reserve(n);
      std::copy_n(
          pts.begin(), nm1 + 1,
          std::copy_n(
              internal::shift_sample_points_unsafe(mod_t::get_mod() - k, pts, mod_t(k), f).begin(),
              mod_t::get_mod() - k,
              std::copy_n(pts.begin() + m_64, k - m_64, std::back_inserter(res))));
      return res;
    } else { // f(0), …, f(m), …, f(k-1), …, f(n+m-1)
      std::vector<mod_t> res;
      res.reserve(n);
      std::copy_n(internal::shift_sample_points_unsafe(m_64 + n - k, pts, mod_t(k), f).begin(),
                  m_64 + n - k, std::copy_n(pts.begin() + m_64, k - m_64, std::back_inserter(res)));
      return res;
    }
  } else {             // f(0), …, f(k-1), …, f(m)
    if (nm1 >= m_64) { // f(0), …, f(k-1), …, f(m), …, f(n+m-1), …, f(mod-1)
      return internal::shift_sample_points_unsafe(n, pts, m, f);
    } else if (nm1 < k) { // f(0), …, f(n+m-1), …, f(k-1), …, f(m), …, f(mod-1)
      std::vector<mod_t> res;
      res.reserve(n);
      std::copy_n(
          pts.begin(), nm1 + 1,
          std::copy_n(internal::shift_sample_points_unsafe(static_cast<int>(-m), pts, m, f).begin(),
                      static_cast<int>(-m), std::back_inserter(res)));
      return res;
    } else { // f(0), …, f(k-1), …, f(n+m-1), …, f(m), …, f(mod-1)
      std::vector<mod_t> res;
      res.reserve(n);
      std::copy_n(
          internal::shift_sample_points_unsafe(nm1 - k + 1, pts, mod_t(k), f).begin(), nm1 - k + 1,
          std::copy_n(
              pts.begin(), k,
              std::copy_n(
                  internal::shift_sample_points_unsafe(static_cast<int>(-m), pts, m, f).begin(),
                  static_cast<int>(-m), std::back_inserter(res))));
      return res;
    }
  }
}

template <typename mod_t, typename ConvolveCyclicFuncType>
std::vector<mod_t> shift_sample_points(const std::vector<mod_t> &pts, mod_t m,
                                       ConvolveCyclicFuncType &&f) {
  return shift_sample_points(pts.size(), pts, m, f);
}

/**
 * @brief 线性时间连续点值（特殊点值）的单点插值
 * @param pts f(0), f(1), …, f(k-1) 确定一个唯一的度数小于 k 的多项式
 * @param c
 * @return mod_t f(c)
 */
template <typename mod_t>
mod_t shift_sample_points_single(const std::vector<mod_t> &pts, mod_t c) {
  using u64 = std::uint64_t;
  int n     = pts.size();
  u64 uc    = static_cast<u64>(c);
  if (uc < static_cast<u64>(n)) return pts[uc];
  std::vector<mod_t> prefix(n), suffix(n);
  const mod_t ONE(1);
  mod_t pc(c), res(0);
  std::for_each_n(prefix.begin(), n, [&pc, &ONE](mod_t &v) { v = pc, pc -= ONE; });
  std::exclusive_scan(prefix.rbegin(), prefix.rend(), suffix.rbegin(), ONE, std::multiplies<>());
  std::exclusive_scan(prefix.begin(), prefix.end(), prefix.begin(), ONE, std::multiplies<>());
  PrimeBinomial<mod_t> bi(n);
  for (int i = 0; i < n; ++i)
    if ((n - 1 - i) & 1)
      res -= pts[i] * prefix[i] * suffix[i] * bi.ifac_unsafe(i) * bi.ifac_unsafe(n - 1 - i);
    else
      res += pts[i] * prefix[i] * suffix[i] * bi.ifac_unsafe(i) * bi.ifac_unsafe(n - 1 - i);
  return res;
}

} // namespace lib

#endif