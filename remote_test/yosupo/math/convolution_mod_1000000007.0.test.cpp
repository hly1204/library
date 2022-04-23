#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "math/convolution.hpp"
#include "modint/long_montgomery_modint.hpp"

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
  std::vector<int> a, b;
  std::copy_n(std::istream_iterator<int>(std::cin), n, std::back_inserter(a));
  std::copy_n(std::istream_iterator<int>(std::cin), m, std::back_inserter(b));
  auto ab = lib::convolution_mod(a, b, 1000000007);
  std::copy(ab.begin(), ab.end(), std::ostream_iterator<int>(std::cout, " "));
  return 0;
}