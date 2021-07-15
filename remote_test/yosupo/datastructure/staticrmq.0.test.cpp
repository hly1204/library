#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <iostream>
#include <vector>

#include "datastructure/basic/sparse_table.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, q;
  std::cin >> n >> q;
  std::vector<int> A(n);
  for (auto &i : A) std::cin >> i;
  auto st = lib::make_rmq_sparse_table(A);
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    std::cout << st.fold(l, r - 1) << '\n';
  }
  return 0;
}