#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "math/integer_factorization.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int Q;
  std::cin >> Q;
  while (Q--) {
    long long a;
    std::cin >> a;
    std::cout << (lib::is_prime(a) ? "Yes\n" : "No\n");
  }
  return 0;
}
