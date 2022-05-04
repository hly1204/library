#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "math/czt.hpp"
#include "math/radix2_ntt.hpp"
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
  int len = lib::ntt_len(n + m - 1);
  const mint PR(3), c(PR.pow((mint::mod() - 1) / len));
  auto a_czt = lib::czt(a, c, len);
  auto b_czt = lib::czt(b, c, len);
  for (int i = 0; i != len; ++i) a_czt[i] *= b_czt[i];
  auto ab = lib::czt(a_czt, c.inv(), len);
  ab.resize(n + m - 1);
  const mint iv(mint(len).inv());
  for (auto &&i : ab) std::cout << i * iv << ' ';
  return 0;
}