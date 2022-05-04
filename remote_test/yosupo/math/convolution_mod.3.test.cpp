#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "math/relaxed_convolution.hpp"
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
  std::vector<mint> a, b;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));
  std::copy_n(std::istream_iterator<mint>(std::cin), m, std::back_inserter(b));
  lib::relaxed_convolution<mint> rc(
      [&a](int n) { return n < static_cast<int>(a.size()) ? a[n] : mint(); },
      [&b](int n) { return n < static_cast<int>(b.size()) ? b[n] : mint(); });
  for (int i = 0; i != n + m - 1; ++i) std::cout << rc[i] << ' ';
  return 0;
}