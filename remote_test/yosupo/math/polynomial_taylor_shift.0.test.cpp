#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "math/polynomial.hpp"
#include "math/taylor_shift.hpp"
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
  using mint = lib::mm30<998244353>;
  int n;
  mint c;
  std::cin >> n >> c;
  lib::polynomial<mint> f;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(f));
  auto fc = lib::taylor_shift(f, c);
  std::copy(fc.cbegin(), fc.cend(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}