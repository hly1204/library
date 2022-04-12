#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include <iostream>
#include <vector>

#include "math/formal_power_series/radix_2_NTT.hpp"
#include "modint/Montgomery_modint.hpp"

template <typename mod_t>
std::vector<mod_t> inv_helper_func(std::vector<mod_t> Q) {
  int n = Q.size();
  if (n == 1) return {Q.front().inv()};
  // Q(x)Q(-x)=V(x^2)
  // 递归求 1/V(x) 的前 n/2 项，还原出 1/V(x^2) 的前 n 项，与 Q(-x) 卷积截取前 n 项即可
  Q.resize(n << 1, mod_t(0));
  lib::dft(n << 1, Q.data());
  std::vector<mod_t> V(n);
  for (int i = 0; i != n << 1; i += 2) V[i >> 1] = Q[i] * Q[i + 1];
  lib::idft(n, V.data());
  V.resize(n >> 1);
  auto S = inv_helper_func(V);
  S.resize(n, mod_t(0));
  lib::dft(n, S.data());
  std::vector<mod_t> res(n << 1);
  for (int i = 0; i != n << 1; ++i) res[i] = Q[i ^ 1] * S[i >> 1];
  lib::idft(n << 1, res.data());
  return res.resize(n), res;
}

template <typename mod_t>
std::vector<mod_t> inv(std::vector<mod_t> x) {
  int n = x.size(), len = lib::get_ntt_len(n);
  x.resize(len);
  auto res = inv_helper_func(x);
  return res.resize(n), res;
}

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  int n;
  std::cin >> n;
  std::vector<mint> s(n);
  for (auto &i : s) std::cin >> i;
  for (auto i : inv(s)) std::cout << i << ' ';
  return 0;
}