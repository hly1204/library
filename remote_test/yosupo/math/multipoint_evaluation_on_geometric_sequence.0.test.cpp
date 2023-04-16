#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

#include "math/czt.hpp"
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
  using mint = lib::mm30<998244353>;
  int n, m;
  mint a, r;
  std::cin >> n >> m >> a >> r;
  std::vector<mint> f;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(f));
  std::transform(f.cbegin(), f.cend(), f.begin(), [aa = mint(1), &a](const mint &x) mutable {
    mint xx = x * aa;
    aa *= a;
    return xx;
  });
  auto ff = lib::czt(f, r, m);
  std::copy(ff.cbegin(), ff.cend(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}
