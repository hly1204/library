#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "math/truncated_formal_power_series.hpp"
#include "modint/montgomery_modint.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  long long m;
  std::cin >> n >> m;
  using mint = lib::mm30<998244353>;
  lib::tfps<mint> a;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));
  auto ia = a.pow(n, m);
  std::copy(ia.cbegin(), ia.cend(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}