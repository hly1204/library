#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "math/semi_relaxed_convolution.hpp"
#include "modint/montgomery_modint.hpp"

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
  std::vector<mint> a;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));
  lib::semi_relaxed_convolution src(a, [iv = a.front().inv()](int n, const std::vector<mint> &c) {
    return n == 0 ? iv : -c[n] * iv;
  });
  std::copy_n(src.await(n).get_multiplier().begin(), n,
              std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}