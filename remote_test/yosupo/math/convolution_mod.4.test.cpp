#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "math/truncated_fourier_transform.hpp"
#include "modint/montgomery_modint.hpp"

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
  std::vector<mint> a, b;
  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));
  std::copy_n(std::istream_iterator<mint>(std::cin), m, std::back_inserter(b));
  int len = n + m - 1;
  a.resize(len);
  b.resize(len);
  lib::tft(a);
  lib::tft(b);
  for (int i = 0; i != len; ++i) a[i] *= b[i];
  lib::itft(a);
  std::copy(a.begin(), a.end(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}