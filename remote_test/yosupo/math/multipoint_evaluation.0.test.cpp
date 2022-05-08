#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

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
  int n, m;
  std::cin >> n >> m;
  using mint = lib::mm30<998244353>;
  lib::polynomial<mint> a;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));
  std::vector<mint> x;
  std::copy_n(std::istream_iterator<mint>(std::cin), m, std::back_inserter(x));
  auto res = lib::evaluation(a, x);
  std::copy(res.cbegin(), res.cend(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}