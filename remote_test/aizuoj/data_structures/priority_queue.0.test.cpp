#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C"

#include <iostream>

#include "datastructure/heap/priority_queue.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  auto cmp = [](long long a, long long b) -> bool { return a > b; };
  lib::PriorityQueue<long long, decltype(cmp)> pq(cmp);
  char cmd[10];
  while (std::cin >> cmd && cmd[2] != 'd') {
    if (cmd[0] == 'i') {
      long long v;
      std::cin >> v;
      pq.insert(v);
    } else {
      std::cout << pq.find_min() << '\n';
      pq.delete_min();
    }
  }
  return 0;
}