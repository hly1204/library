#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <iostream>
#include <vector>

#include "math/formal_power_series/chirp_z.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  int n, m;
  std::cin >> n >> m;
  std::vector<mint> a(n), b(m);
  int len = lib::get_ntt_len(n + m - 1);
  mint pr(3), c(pr.pow((pr.get_mod() - 1) / len));
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  auto C = lib::czt(len, a, c), D = lib::czt(len, b, c);
  for (int i = 0; i < len; ++i) C[i] *= D[i];
  auto ab = lib::czt(len, C, c.inv());
  mint iv(len);
  iv = iv.inv();
  ab.resize(n + m - 1);
  for (auto i : ab) std::cout << i * iv << ' ';
  return 0;
}