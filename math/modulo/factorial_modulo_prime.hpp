#ifndef FACTORIAL_MODULO_PRIME_HEADER_HPP
#define FACTORIAL_MODULO_PRIME_HEADER_HPP

/**
 * @brief factorial modulo prime / 阶乘模素数
 *
 */

#include <cstdint>
#include <utility>
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
      std::vector<mod_t> g(shift_sample_points_via_FFP(d, fac_table_, mod_t(d + 1)));
      for (auto i : g) fac_table_.emplace_back(i);
      g = std::move(shift_sample_points_via_FFP(d << 1 | 1, fac_table_, mod_t(d) * iv));
      for (int i = 0; i <= (d << 1); ++i) fac_table_[i] *= g[i];
    }
  }
  ~NTTPrimeFactorial() = default;

  mod_t fac(mod_t n) const {
    mod_t res(1);
    u64 pass = 0, in = u64(n);
    for (int i = 0; pass + v_ <= in; pass += v_) res *= fac_table_[i++];
    for (mod_t ONE(1), mpass(pass); mpass != n;) res *= (mpass += ONE);
    return res;
  }

private:
  u64 v_;
  std::vector<mod_t> fac_table_;
};

} // namespace lib

#endif