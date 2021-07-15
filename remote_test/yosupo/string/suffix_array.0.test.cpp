#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <iostream>
#include <string>
#include <vector>

#include "string/suffix_array_sais.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::string s;
  std::cin >> s;
  for (auto i : lib::get_sa(s)) std::cout << i << ' ';
  return 0;
}