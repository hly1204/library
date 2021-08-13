#ifndef FACTORIAL_MODULO_PRIME_HEADER_HPP
#define FACTORIAL_MODULO_PRIME_HEADER_HPP

/**
 * @brief factorial modulo prime
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
#include "../formal_power_series/sample_points_shift.hpp"

namespace lib {

/**
 * @brief 素数模数的阶乘计算
 * @note 在 O(p^{1/2}\log p) 时间预处理，单次询问 O(p^{1/2})
 * @tparam mod_t 素数模数
 */
template <typename mod_t>
class FactorialModPrime {
public:
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  template <typename ConvolveCyclicFuncType>
  FactorialModPrime(ConvolveCyclicFuncType &&conv)
      : v_(static_cast<u64>(std::sqrt(modint_traits<mod_t>::get_mod()))) {
    const mod_t ONE(1);
    mod_t mv = mod_t(v_), iv = ONE / mv;
    block_prod_ = std::vector<mod_t>{ONE, mv + ONE};
    block_prod_.reserve(v_ + 1);
    u64 mask = UINT64_C(1) << 63;
    while ((mask & v_) == 0) mask >>= 1;
    for (u32 d = 1; d != v_;) {
      std::vector<mod_t> g0(shift_sample_points(d, block_prod_, mod_t(d + 1), conv));
      std::vector<mod_t> g1(shift_sample_points(d << 1 | 1, block_prod_, mod_t(d) * iv, conv));
      std::copy(g0.begin(), g0.end(), std::back_inserter(block_prod_));
      d <<= 1;
      for (int i = 0; i <= d; ++i) block_prod_[i] *= g1[i];
      if ((mask >>= 1) & v_) {
        mod_t k(d | 1), dpv(v_ * k), prod(ONE);
        for (int i = 0; i < d; ++i) prod *= (dpv += ONE);
        block_prod_.emplace_back(prod);
        d |= 1;
        for (int i = 0; i <= d; ++i) block_prod_[i] *= k, k += mv;
      }
    }
    std::partial_sum(block_prod_.begin(), block_prod_.end(), block_prod_.begin(),
                     std::multiplies<>());
  }
  ~FactorialModPrime() = default;

  mod_t fac(u64 n) const {
    if (n >= modint_traits<mod_t>::get_mod()) return mod_t(0);
    mod_t res(1);
    u64 pass = n / v_;
    if (pass != 0) res *= block_prod_[pass - 1];
    for (mod_t ONE(1), mpass(pass * v_), mn(n); mpass != mn;) res *= (mpass += ONE);
    return res;
  }

private:
  const u64 v_;
  std::vector<mod_t> block_prod_;
};

} // namespace lib

#endif