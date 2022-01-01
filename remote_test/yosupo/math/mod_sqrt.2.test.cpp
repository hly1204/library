#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include <iostream>
#include <random>
#include <tuple>
#include <utility>
#include <vector>

#include "modint/runtime_Montgomery_modint.hpp"

template <typename mod_t>
std::vector<mod_t> sqrt_mod_prime(const mod_t u) {
  // Legendre 算法
  const auto p = mod_t::get_mod();
  const mod_t ONE(1), MINUS_ONE(-ONE), ZERO(0);
  if (u == ZERO) return {ZERO};
  if (u.pow(p >> 1) == MINUS_ONE) return {};
  if ((p & 3) == 3) {
    mod_t res = u.pow((p + 1) >> 2);
    return {res, -res};
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<decltype(p)> dis(2, p - 1);

  mod_t r(dis(gen)); // 随机一个 r 满足 r^2-u 为二次非剩余
  while ((r * r - u).pow(p >> 1) != MINUS_ONE) r = dis(gen);

  // 计算 (r-x)^((p-1)/2) mod (x^2-u) 结果 x 的系数即为解的倒数
  mod_t a(ONE), b(ZERO), c(r), d(MINUS_ONE); // res=a+bx

  for (auto e = (p - 1) >> 1; e != 0; e >>= 1) {
    if (e & 1) std::tie(a, b) = std::make_pair(a * c + b * d * u, b * c + a * d);
    mod_t cd       = c * d;
    std::tie(c, d) = std::make_pair(c * c + d * d * u, cd + cd);
  }
  b = b.inv();
  return {b, -b};
}

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::RuntimeMontgomeryModInt<-1>;
  int t;
  std::cin >> t;
  while (t--) {
    int k, p;
    std::cin >> k >> p;
    if (p == 2) {
      std::cout << k << '\n';
      continue;
    }
    mint::set_mod(p);
    auto res = sqrt_mod_prime(mint(k));
    if (res.empty()) std::cout << "-1\n";
    else
      std::cout << res[0] << '\n';
  }
  return 0;
}