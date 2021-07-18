#ifndef FACTORIAL_MODULO_PRIME_HEADER_HPP
#define FACTORIAL_MODULO_PRIME_HEADER_HPP

/**
 * @brief factorial modulo prime / 阶乘模素数
 *
 */

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

#include "../../traits/modint.hpp"
#include "../formal_power_series/sample_points_shift.hpp"

namespace lib {

/**
 * @brief NTT 友好模数的阶乘计算
 *
 * @tparam mod_t NTT 友好的模数
 */
template <typename mod_t>
class NTTPrimeFactorial {
public:
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;
  NTTPrimeFactorial() : v_(1) {
    while (v_ * v_ < modint_traits<mod_t>::get_mod()) v_ <<= 1;
    mod_t iv   = mod_t(1) / mod_t(v_);
    fac_table_ = std::vector<mod_t>{mod_t(1), mod_t(v_ + 1)};
    fac_table_.reserve(v_ + 1);
    for (u64 d = 1; d != v_; d <<= 1) {
      std::vector<mod_t> g0(shift_sample_points_unsafe(d, fac_table_, mod_t(d + 1)));
      std::vector<mod_t> g1(shift_sample_points_unsafe(d << 1 | 1, fac_table_, mod_t(d) * iv));
      std::copy(g0.begin(), g0.end(), std::back_inserter(fac_table_));
      for (int i = 0; i <= (d << 1); ++i) fac_table_[i] *= g1[i];
    }
    std::partial_sum(fac_table_.begin(), fac_table_.end(), fac_table_.begin(), std::multiplies<>());
  }
  ~NTTPrimeFactorial() = default;

  mod_t fac(mod_t n) const {
    mod_t res(1);
    u64 pass = u64(n) / v_;
    if (pass != 0) res *= fac_table_[pass - 1];
    for (mod_t ONE(1), mpass(pass * v_); mpass != n;) res *= (mpass += ONE);
    return res;
  }

private:
  u64 v_;
  std::vector<mod_t> fac_table_;
};

} // namespace lib

#endif