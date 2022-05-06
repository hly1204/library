#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"

#include "math/polynomial.hpp"
#include "math/stirling_numbers.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  using mint = lib::mm30<998244353>;
  int n;
  std::cin >> n;
  auto res = lib::stirling1st_row<lib::polynomial<mint>>(n);
  for (int i = 0; i <= n; ++i) std::cout << (((n - i) & 1) ? -res[i] : res[i]) << ' ';
  return 0;
}