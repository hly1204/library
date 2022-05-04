#ifndef BINOMIAL_PRIME
#define BINOMIAL_PRIME

#include "../common.hpp"

#include <vector>

LIB_BEGIN

// helper class for precomputation of factorials and multiplicative inverse of them.
template <typename ModIntT>
class binomial {
  mutable std::vector<ModIntT> factorial_{ModIntT(1)}, invfactorial_{ModIntT(1)};

public:
  explicit binomial(int n) { preprocess(n); }
  binomial() {}
  void preprocess(int n) const {
    if (int nn = static_cast<int>(factorial_.size()); nn <= n) {
      int k = nn;
      while (k <= n) k <<= n;
      factorial_.resize(k);
      invfactorial_.resize(k);
      for (int i = nn; i != k; ++i) factorial_[i] = factorial_[i - 1] * i;
      invfactorial_.back() = factorial_.back().inv();
      for (int i = k - 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i + 1] * (i + 1);
    }
  }
  // binomial coefficient `n`C`m`
  ModIntT binom(int n, int m) const {
    return n < m ? ModIntT()
                 : (preprocess(n), factorial_[n] * invfactorial_[m] * invfactorial_[n - m]);
  }
  ModIntT inv(int n) const { return preprocess(n), factorial_[n - 1] * invfactorial_[n]; }
  ModIntT factorial(int n) const { return preprocess(n), factorial_[n]; }
  ModIntT inv_factorial(int n) const { return preprocess(n), invfactorial_[n]; }
};

LIB_END

#endif