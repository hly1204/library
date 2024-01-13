#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "datastructure/sliding_window_aggregator.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  using mint = lib::mm30<998244353>;
  struct linear_function {
    mint a, b;
    mint operator()(const mint &x) const { return a * x + b; }
    linear_function operator()(const linear_function &rhs) const {
      return {a * rhs.a, a * rhs.b + b};
    }
  };

  int Q;
  std::cin >> Q;

  auto c = [](const linear_function &lhs, const linear_function &rhs) { return rhs(lhs); };
  lib::swag<linear_function, decltype(c)> agg(c);
  while (Q--) {
    int cmd;
    std::cin >> cmd;
    if (cmd == 0) {
      mint a, b;
      std::cin >> a >> b;
      agg.push({a, b});
    } else if (cmd == 1) {
      agg.pop();
    } else {
      mint x;
      std::cin >> x;
      std::cout << agg.query().value_or(linear_function{1, 0})(x) << '\n';
    }
  }
  return 0;
}
