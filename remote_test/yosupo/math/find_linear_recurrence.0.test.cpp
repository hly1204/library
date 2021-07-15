#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include <iostream>
#include <vector>

#include "math/modulo/find_shortest_LFSR_Berlekamp_Massey.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  std::vector<lib::MontModInt<998244353>> s(n);
  for (auto &i : s) std::cin >> i;
  auto rec = lib::find_LFSR(s);
  std::cout << rec.size() - 1 << '\n';
  for (int i = 1, ie = rec.size(); i < ie; ++i) std::cout << -rec[i] << ' ';
  return 0;
}