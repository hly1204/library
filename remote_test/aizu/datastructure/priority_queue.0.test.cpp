#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C"

#include "datastructure/height_based_leftist_tree.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  auto cmp = [](long long a, long long b) { return a > b; };
  lib::hblt<long long, decltype(cmp)> h(cmp);
  for (;;) {
    char cmd[20];
    std::cin >> cmd;
    if (cmd[2] == 's') {
      long long v;
      std::cin >> v;
      h.push(v);
    } else if (cmd[2] == 't') {
      std::cout << h.pop() << '\n';
    } else {
      break;
    }
  }
  return 0;
}