#ifndef FPS_COMPOSITION_HPP
#define FPS_COMPOSITION_HPP

#include "../common.hpp"
#include "binomial.hpp"
#include "enum_kth_term_of_power.hpp"
#include "truncated_formal_power_series.hpp"

#include <algorithm>

LIB_BEGIN

// returns f(g) mod x^n
// reference: noshi91's blog: https://noshi91.hatenablog.com/entry/2024/03/16/224034
template <typename ModIntT>
tfps<ModIntT> composition(tfps<ModIntT> f, const tfps<ModIntT> &g, int n) {
  f.resize(n);
  std::reverse(f.begin(), f.end());
  return kth_term_of_y(g, f, n - 1, n);
}

template <typename ModIntT>
tfps<ModIntT> compositional_inverse(tfps<ModIntT> f, int n) {
  if (n <= 0 || f.size() < 2) return {};
  const auto f1 = f[1].inv();
  if (n == 1) return {ModIntT()};
  f.resize(n);
  {
    f[1] *= f1;
    auto c = f1;
    for (int i = 2; i != n; ++i) f[i] *= c *= f1;
  }
  auto a = kth_term_of_x(f, {ModIntT(1)}, n - 1, n);
  binomial<ModIntT> bin(n);
  const ModIntT c(n - 1);
  for (int i = 1; i != n; ++i) a[i] *= c * bin.inv(i);
  return tfps<ModIntT>(a.rbegin(), a.rend() - 1).pow(n - 1, (-c.inv()).val()) *
         tfps<ModIntT>{ModIntT(0), f1};
}

LIB_END

#endif
