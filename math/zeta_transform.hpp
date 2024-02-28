#ifndef ZETA_TRANSFORM_HPP
#define ZETA_TRANSFORM_HPP

#include "../common.hpp"

#include <cassert>
#include <vector>

#ifdef _MSC_VER
  #include <intrin.h>
#endif

LIB_BEGIN

int popcount(unsigned int c) {
#ifdef _MSC_VER
  return __popcnt(c);
#else
  return __builtin_popcount(c);
#endif
}

int popcount(unsigned long c) {
#ifdef _MSC_VER
  return sizeof(unsigned long) == 8 ? __popcnt64(c) : __popcnt(c);
#else
  return __builtin_popcountl(c);
#endif
}

int popcount(unsigned long long c) {
#ifdef _MSC_VER
  return __popcnt64(c);
#else
  return __builtin_popcountll(c);
#endif
}

// Input:           f(x) = `a[0]` + `a[1]`x_1 + ... + `a[n - 1]`x_1...x_n.
// Output(inplace): [f mod (x_1,...,x_n), f mod (x_1-1,x_2,...,x_n), ..., f mod (x_1-1,...,x_n-1)].
template <typename ModIntT>
void zeta_transform(std::vector<ModIntT> &x) {
  const int n = static_cast<int>(x.size());
  assert((n & (n - 1)) == 0);
  // assume a + b = b + a
  for (int i = 1; i < n; i <<= 1)
    for (int j = i; j < n; j = (j + 1) | i) x[j] += x[j ^ i];
}

// Input:           [f mod (x_1,...,x_n), f mod (x_1-1,x_2,...,x_n), ..., f mod (x_1-1,...,x_n-1)].
// Output(inplace): f(x) = `a[0]` + `a[1]`x_1 + ... + `a[n - 1]`x_1...x_n.
template <typename ModIntT>
void moebius_transform(std::vector<ModIntT> &x) {
  const int n = static_cast<int>(x.size());
  assert((n & (n - 1)) == 0);
  // assume a + b = b + a
  for (int i = n >> 1; i != 0; i >>= 1)
    for (int j = i; j < n; j = (j + 1) | i) x[j] -= x[j ^ i];
}

LIB_END

#endif
