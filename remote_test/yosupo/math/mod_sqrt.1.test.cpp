#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include <iostream>
#include <random>
#include <tuple>
#include <utility>
#include <vector>

#include "modint/runtime_Montgomery_modint.hpp"

template <typename mod_t>
std::vector<mod_t> sqrt_mod_prime(const mod_t u) {
  // Cipolla 算法
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

  mod_t r, r2_u;

  do { // 随机一个 r 满足 r^2-u 为二次非剩余
    r    = dis(gen);
    r2_u = r * r - u;
    if (r2_u == ZERO) return {r, -r}; // 足够幸运时
  } while (r2_u.pow(p >> 1) != MINUS_ONE);

  // 计算 (r-x)^((p+1)/2) mod (x^2-(r^2-u)) 即为解
  // 或者计算 (r+x)^((p+1)/2) mod (x^2-(r^2-u)) 也是一样的
  // lib::sqrt_mod_prime 使用了另一种 Cipolla 算法
  mod_t a(ONE), b(ZERO), c(r), d(ONE); // res=a+bx

  for (auto e = (p + 1) >> 1; e != 0; e >>= 1) {
    if (e & 1) std::tie(a, b) = std::make_pair(a * c + b * d * r2_u, b * c + a * d);
    mod_t cd       = c * d;
    std::tie(c, d) = std::make_pair(c * c + d * d * r2_u, cd + cd);
  }
  return {a, -a};
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