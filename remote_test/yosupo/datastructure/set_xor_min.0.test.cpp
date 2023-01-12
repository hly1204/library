#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include "datastructure/binary_trie.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  lib::binary_trie<30> t;
  while (n--) {
    int cmd, x;
    std::cin >> cmd >> x;
    if (cmd == 0) {
      if (!t.contains(x)) t.insert(x);
    } else if (cmd == 1) {
      t.erase(x);
    } else {
      std::cout << t.xor_min(x) << '\n';
    }
  }
  return 0;
}
