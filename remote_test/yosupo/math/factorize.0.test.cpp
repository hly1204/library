#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include <iostream>

#include "math/basic/integer_factorization_Pollard_rho.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int Q;
  std::cin >> Q;
  while (Q--) {
    long long a;
    std::cin >> a;
    std::vector<long long> factor;
    auto mp = lib::factorize(a);
    for (auto i : mp) {
      for (int j = i.second; j > 0; --j) factor.push_back(i.first);
    }
    std::cout << factor.size() << ' ';
    for (auto i : factor) std::cout << i << ' ';
    std::cout << '\n';
  }
  return 0;
}