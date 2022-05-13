#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "string/suffix_array.hpp"

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
  for (auto i : lib::suffix_array(s)) std::cout << i << ' ';
  return 0;
}