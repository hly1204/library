#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "string/z_function.hpp"

#include <iostream>
#include <string>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s;
  std::cin >> s;
  for (auto i : lib::z_function(s)) std::cout << i << ' ';
  return 0;
}