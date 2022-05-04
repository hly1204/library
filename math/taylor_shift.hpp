#ifndef TAYLOR_SHIFT_HPP
#define TAYLOR_SHIFT_HPP

#include "../common.hpp"
#include "binomial.hpp"

#include <algorithm>

LIB_BEGIN

template <typename PolyT>
PolyT taylor_shift(const PolyT &a, typename PolyT::value_type c) {
  using T     = typename PolyT::value_type;
  const int n = static_cast<int>(a.size());
  binomial<T> b(n);
  PolyT rev_a_cpy(n), pc(n);
  for (int i = 0; i != n; ++i) rev_a_cpy[n - 1 - i] = a[i] * b.factorial(i);
  T cc(1);
  for (int i = 0; i != n; ++i) pc[i] = cc * b.inv_factorial(i), cc *= c;
  (rev_a_cpy *= pc).resize(n);
  std::reverse(rev_a_cpy.begin(), rev_a_cpy.end());
  for (int i = 0; i != n; ++i) rev_a_cpy[i] *= b.inv_factorial(i);
  return rev_a_cpy;
}

LIB_END

#endif