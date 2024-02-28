#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"

#include "math/set_power_series.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>
#include <iterator>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  using mint = lib::mm30<998244353>;
  int n;
  std::cin >> n;
  std::vector<mint> x, y;
  std::copy_n(std::istream_iterator<mint>(std::cin), 1 << n, std::back_inserter(x));
  std::copy_n(std::istream_iterator<mint>(std::cin), 1 << n, std::back_inserter(y));
  auto xy = lib::set_power_series::subset_convolution(x, y);
  std::copy(xy.begin(), xy.end(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}
