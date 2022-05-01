#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include "datastructure/cartesian_tree.hpp"

#include <iostream>
#include <tuple>
#include <vector>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (auto &&i : a) std::cin >> i;
  std::tie(std::ignore, std::ignore, a) = lib::build_cartesian_tree(a);
  for (int i = 0; i != n; ++i) std::cout << (a[i] == -1 ? i : a[i]) << ' ';
  return 0;
}