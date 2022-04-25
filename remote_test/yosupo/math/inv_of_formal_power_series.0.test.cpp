#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "math/radix2_ntt.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>
#include <iterator>
#include <vector>

template <typename ModIntT>
std::vector<ModIntT> inv_helper_func(std::vector<ModIntT> Q) {
  int n = static_cast<int>(Q.size());
  if (n == 1) return std::vector<ModIntT>{Q.front().inv()};
  // `Q`(x) * `Q`(-x) = `V`(x^2)
  // We could restore 1/`V`(x^2) by taking first `n`/2 terms of 1/`V`(x).
  // `Q`(x)^(-1) = `Q`(-x)/`V`(x^2)
  Q.resize(n << 1);
  lib::dft(Q);
  std::vector<ModIntT> V(n);
  for (int i = 0; i != n << 1; i += 2) V[i >> 1] = Q[i] * Q[i + 1];
  lib::idft(V);
  V.resize(n >> 1);
  auto S = inv_helper_func(V);
  S.resize(n);
  lib::dft(S);
  std::vector<ModIntT> res(n << 1);
  for (int i = 0; i != n << 1; ++i) res[i] = Q[i ^ 1] * S[i >> 1];
  lib::idft(res);
  res.resize(n);
  return res;
}

template <typename ModIntT>
std::vector<ModIntT> inv(std::vector<ModIntT> x) {
  int n = static_cast<int>(x.size()), len = lib::ntt_len(n);
  x.resize(len);
  auto res = inv_helper_func(x);
  res.resize(n);
  return res;
}

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
  auto ia = inv(a);
  std::copy(ia.cbegin(), ia.cend(), std::ostream_iterator<mint>(std::cout, " "));
  return 0;
}