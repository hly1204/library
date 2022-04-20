#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "math/truncated_formal_power_series.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>
#include <iterator>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  using mint = lib::mm30<998244353>;
  lib::tfps<mint> a, b;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));
  std::copy_n(std::istream_iterator<mint>(std::cin), m, std::back_inserter(b));
  auto res = a * b;
  std::copy_n(res.begin(), n + m - 1, std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}