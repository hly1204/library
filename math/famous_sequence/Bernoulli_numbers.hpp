#ifndef BERNOULLI_NUMBERS_HEADER_HPP
#define BERNOULLI_NUMBERS_HEADER_HPP

/**
 * @brief Bernoulli number
 * @docs docs/math/famous_sequence/Bernoulli_numbers.md
 */

#include "../formal_power_series/prime_binomial.hpp"

namespace lib {

template <typename PolyType>
void Bernoulli_numbers(int n, PolyType &res) {
  using mod_t = typename PolyType::value_type;
  res.resize(n);
  PrimeBinomial<mod_t> bi(n + 1);
  for (int i = 0; i < n; ++i) res[i] = bi.ifac_unsafe(i + 1);
  res = res.inv(n);
  for (int i = 0; i < n; ++i) res[i] *= bi.fac_unsafe(i);
}

} // namespace lib

#endif