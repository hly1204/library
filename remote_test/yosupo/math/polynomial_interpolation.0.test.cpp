#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "math/polynomial.hpp"
#include "math/subproduct_tree.hpp"
#include "modint/montgomery_modint.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  using mint = lib::mm30<998244353>;
  std::vector<mint> x, y;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(x));
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(y));
  auto res = lib::interpolation<lib::polynomial>(x, y);
  res.resize(n);
  std::copy(res.cbegin(), res.cend(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}