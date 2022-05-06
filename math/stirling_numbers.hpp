#ifndef STIRLING_NUMBERS_HPP
#define STIRLING_NUMBERS_HPP

#include "../common.hpp"
#include "binomial.hpp"
#include "linear_sieve.hpp"
#include "taylor_shift.hpp"

LIB_BEGIN

// unsigned Stirling numbers of the first kind.
template <typename PolyT>
PolyT stirling1st_row(int n) {
  using T = typename PolyT::value_type;
  if (n == 0) return {T(1)};
  int mask = 1 << 30;
  while ((mask & n) == 0) mask >>= 1;
  PolyT res{T(0), T(1)};
  for (int d = 1; d != n;) {
    res *= taylor_shift(res, T(d)), d <<= 1;
    if ((mask >>= 1) & n) res *= PolyT{T(d), 1}, ++d;
  }
  return res;
}

template <typename PolyT>
PolyT stirling2nd_row(int n) {
  using T = typename PolyT::value_type;
  if (n == 0) return {T(1)};
  PolyT res(n + 1), rhs(n + 1);
  binomial<T> bi(n);
  const auto pt = pow_table<T>(n, n + 1);
  for (int i = 0; i <= n; ++i) {
    rhs[i] = pt[i] * (res[i] = bi.inv_factorial(i));
    if (i & 1) res[i] = -res[i];
  }
  (res *= rhs).resize(n + 1);
  return res;
}

LIB_END

#endif