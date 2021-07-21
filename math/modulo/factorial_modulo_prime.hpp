#ifndef FACTORIAL_MODULO_PRIME_HEADER_HPP
#define FACTORIAL_MODULO_PRIME_HEADER_HPP

/**
 * @brief factorial modulo prime / 阶乘模素数
 * @docs docs/math/modulo/factorial_modulo_prime.md
 */

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

#include "../../traits/modint.hpp"
#include "../formal_power_series/arbitrary_modulo_convolution.hpp"
#include "../formal_power_series/sample_points_shift.hpp"

namespace lib {

/**
 * @brief 素数模数的阶乘计算
 * @note 在 O(p^{1/2}\log p) 时间预处理，单次询问 O(p^{1/2})
 * @tparam mod_t 素数模数
 */
template <typename mod_t>
class PrimeFactorial {
public:
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;
  PrimeFactorial() : v_(u64(std::sqrt(modint_traits<mod_t>::get_mod()))) {
    const mod_t ONE(1);
    mod_t mv = mod_t(v_), iv = ONE / mv;
    fac_table_ = std::vector<mod_t>{ONE, mv + ONE};
    fac_table_.reserve(v_ + 1);
    u64 mask = u64(1) << 63;
    while ((mask & v_) == 0) mask >>= 1;
    mask >>= 1;
    for (u32 d = 1; d != v_; mask >>= 1) {
      std::vector<mod_t> g0(shift_sample_points(
          d, fac_table_, mod_t(d + 1),
          std::bind(lib::convolve_cyclic_mod<mod_t>, std::placeholders::_1, std::placeholders::_2,
                    modint_traits<mod_t>::get_mod(), std::placeholders::_3)));
      std::vector<mod_t> g1(shift_sample_points(
          d << 1 | 1, fac_table_, mod_t(d) * iv,
          std::bind(lib::convolve_cyclic_mod<mod_t>, std::placeholders::_1, std::placeholders::_2,
                    modint_traits<mod_t>::get_mod(), std::placeholders::_3)));
      std::copy(g0.begin(), g0.end(), std::back_inserter(fac_table_));
      d <<= 1;
      for (int i = 0; i <= d; ++i) fac_table_[i] *= g1[i];
      if (mask & v_) {
        mod_t k(d | 1), dpv(v_ * k), prod(ONE);
        for (int i = 1; i <= d; ++i) prod *= (dpv += ONE);
        fac_table_.emplace_back(prod);
        d |= 1;
        for (int i = 0; i <= d; ++i) fac_table_[i] *= k, k += mv;
      }
    }
    std::partial_sum(fac_table_.begin(), fac_table_.end(), fac_table_.begin(), std::multiplies<>());
  }
  ~PrimeFactorial() = default;

  mod_t fac(u64 n) const {
    if (n >= modint_traits<mod_t>::get_mod()) return mod_t(0);
    mod_t res(1);
    u64 pass = n / v_;
    if (pass != 0) res *= fac_table_[pass - 1];
    for (mod_t ONE(1), mpass(pass * v_), mn(n); mpass != mn;) res *= (mpass += ONE);
    return res;
  }

private:
  const u64 v_;
  std::vector<mod_t> fac_table_;
};

} // namespace lib

#endif