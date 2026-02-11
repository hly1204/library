// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/suffixarray

#include "suffix_array.hpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    const auto sa = suffix_array(s);
    for (int i = 0; i < (int)sa.size(); ++i) std::cout << sa[i] << ' ';
    return 0;
}
