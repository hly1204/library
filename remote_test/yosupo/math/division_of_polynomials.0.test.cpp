#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "math/polynomial.hpp"
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
  int n, m;
  std::cin >> n >> m;
  using mint = lib::mm30<998244353>;
  lib::polynomial<mint> a, b;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));
  std::copy_n(std::istream_iterator<mint>(std::cin), m, std::back_inserter(b));
  auto [q, r] = a.div_with_rem(b);
  std::cout << q.deg() + 1 << ' ' << r.deg() + 1 << '\n';
  std::copy(q.cbegin(), q.cend(), std::ostream_iterator<mint>(std::cout, " "));
  std::cout << '\n';
  std::copy(r.cbegin(), r.cend(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}