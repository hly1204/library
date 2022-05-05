#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "math/binomial_convolution.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, c;
  const int modular = 998244353;
  std::cin >> n >> c;
  std::vector<int> p, ecx(n);
  std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(p));
  lib::bin_conv bc(modular);
  long long v = 1;
  for (int i = 0; i != n; ++i) ecx[i] = v, v = v * c % modular;
  auto res = bc.bapply(ecx, p);
  std::copy(res.cbegin(), res.cend(), std::ostream_iterator<int>(std::cout, " "));
  return 0;
}