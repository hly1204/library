#define PROBLEM "https://yukicoder.me/problems/no/502"

#include <iostream>

#include "math/modulo/factorial_modulo_prime.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<1000000007>;
  long long v;
  std::cin >> v;
  std::cout << lib::PrimeFactorial<mint>().fac(v) << '\n';
  return 0;
}