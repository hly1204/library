#define PROBLEM "https://judge.yosupo.jp/problem/multivariate_convolution"

#include "math/multivariate_convolution.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>
#include <iterator>
#include <vector>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int d, N = 1;
  std::cin >> d;
  std::vector<int> n(d);
  for (auto &&i : n) {
    std::cin >> i;
    N *= i;
  }
  using mint = lib::mm30<998244353>;
  std::vector<mint> a, b;
  std::copy_n(std::istream_iterator<mint>(std::cin), N, std::back_inserter(a));
  std::copy_n(std::istream_iterator<mint>(std::cin), N, std::back_inserter(b));
  auto ab = lib::multivariate_convolution(a, b, n);
  std::copy_n(ab.begin(), N, std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}