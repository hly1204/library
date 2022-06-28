#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"
#define ERROR

#include "math/formal_power_series.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>
#include <iterator>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  long long m; // I don't want to deal with the case that `m` is too large.
  std::cin >> n >> m;
  using mint = lib::mm30<998244353>;
  lib::fps<mint> f([it = std::istream_iterator<mint>(std::cin)](int) mutable { return *it++; });
  auto iv = f.pow(static_cast<int>(m));
  for (int i = 0; i != n; ++i) std::cout << iv[i] << ' ';
  return 0;
}