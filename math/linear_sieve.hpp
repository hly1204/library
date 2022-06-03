#ifndef LINEAR_SIEVE_HPP
#define LINEAR_SIEVE_HPP

#include "../common.hpp"

#include <vector>

LIB_BEGIN

// Output: primes in [0, `n`) (sorted).
std::vector<int> prime_table(int n) {
  std::vector<bool> is_comp(n, false);
  std::vector<int> res;
  for (int i = 2; i < n; ++i) {
    if (!is_comp[i]) res.push_back(i);
    for (int j = 0, je = res.size(); j < je && i * res[j] < n; ++j) {
      is_comp[i * res[j]] = true;
      if (i % res[j] == 0) break;
    }
  }
  return res;
}

template <typename ModIntT>
std::vector<ModIntT> pow_table(int e, int n) {
  std::vector<bool> is_comp(n, false);
  std::vector<int> p;
  std::vector<ModIntT> res(n);
  if (n >= 1) {
    res.front() = (e == 0 ? ModIntT(1) : ModIntT()); // 0^0 = 1
    if (n >= 2) res[1] = ModIntT(1);
  }
  for (int i = 2; i < n; ++i) {
    if (!is_comp[i]) {
      p.push_back(i);
      res[i] = ModIntT(i).pow(e);
    }
    for (int j = 0, je = static_cast<int>(p.size()); j < je && i * p[j] < n; ++j) {
      is_comp[i * p[j]] = true;
      res[i * p[j]]     = res[i] * res[p[j]];
      if (i % p[j] == 0) break;
    }
  }
  return res;
}

LIB_END

#endif