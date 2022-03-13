#ifndef STIRLING_NUMBERS_HEADER_HPP
#define STIRLING_NUMBERS_HEADER_HPP

#include "../formal_power_series/prime_binomial.hpp"

namespace lib {

// 第一类无符号斯特林数-行
template <typename PolyType>
void Stirling1st_row(int n, PolyType &res) {
  using mod_t = typename PolyType::value_type;
  if (n == 0) {
    res = PolyType{mod_t(1)};
    return;
  }
  int mask = 1 << 30;
  while ((mask & n) == 0) mask >>= 1;
  res = PolyType{mod_t(0), mod_t(1)};
  for (int d = 1; d != n;) {
    res *= res.shift(mod_t(d));
    d <<= 1;
    if ((mask >>= 1) & n) res *= PolyType{mod_t(d), mod_t(1)}, d |= 1;
  }
}

// 第二类斯特林数-行
template <typename PolyType>
void Stirling2nd_row(int n, PolyType &res) {
  using mod_t = typename PolyType::value_type;
  if (n == 0) {
    res = PolyType{mod_t(1)};
    return;
  }
  PrimeBinomial<mod_t> bi(n + 1);
  std::vector<bool> is_comp(n + 1, false);
  std::vector<int> prime;
  PolyType pow_table;
  pow_table.resize(n + 1);
  pow_table[0] = mod_t(0);
  pow_table[1] = mod_t(1);
  for (int i = 2; i <= n; ++i) {
    if (!is_comp[i]) {
      prime.push_back(i);
      pow_table[i] = mod_t(i).pow(n);
    }
    for (int j = 0, je = prime.size(); j < je && i * prime[j] <= n; ++j) {
      is_comp[i * prime[j]]   = true;
      pow_table[i * prime[j]] = pow_table[i] * pow_table[prime[j]];
      if (i % prime[j] == 0) break;
    }
  }
  res.resize(n + 1);
  for (int i = 0; i <= n; ++i) {
    pow_table[i] *= (res[i] = bi.ifac_unsafe(i));
    if (i & 1) res[i] = -res[i];
  }
  (res *= pow_table).resize(n + 1);
}

} // namespace lib

#endif