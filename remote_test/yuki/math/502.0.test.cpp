#define PROBLEM "https://yukicoder.me/problems/no/502"

#include <iostream>

#include "math/formal_power_series/arbitrary_modulo_convolution.hpp"
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
  std::cout << lib::PrimeFactorial<mint>([](const std::vector<mint> &x, const std::vector<mint> &y,
                                            int c) {
                 return lib::convolve_cyclic_mod(x, y, mint::get_mod(), c);
               }).fac(v)
            << '\n';
  return 0;
}