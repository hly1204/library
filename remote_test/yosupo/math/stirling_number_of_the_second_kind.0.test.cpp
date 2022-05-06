#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"

#include "math/polynomial.hpp"
#include "math/stirling_numbers.hpp"
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
  std::cin >> n;
  auto res = lib::stirling2nd_row<lib::polynomial<mint>>(n);
  std::copy(res.cbegin(), res.cend(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}