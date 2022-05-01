#ifndef CARTESIAN_TREE_HPP
#define CARTESIAN_TREE_HPP

#include "../common.hpp"

#include <functional>
#include <stack>
#include <tuple>
#include <vector>

LIB_BEGIN

template <typename ContainerT, typename CmpT = std::less<>>
std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>
build_cartesian_tree(ContainerT &&a) {
  int n = static_cast<int>(a.size());
  CmpT cmp;
  std::vector<int> l(n, -1), r(n, -1), p(n, -1);
  std::stack<int, std::vector<int>> s;
  for (int i = 0; i != n; ++i) {
    int last_poped = -1;
    while (!s.empty() && cmp(a[i], a[s.top()])) last_poped = s.top(), s.pop();
    if (last_poped != -1) p[l[i] = last_poped] = i;
    if (!s.empty()) r[p[i] = s.top()] = i;
    s.push(i);
  }
  return {l, r, p};
}

LIB_END

#endif