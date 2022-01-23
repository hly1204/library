#ifndef CARTESIAN_TREE_HEADER_HPP
#define CARTESIAN_TREE_HEADER_HPP

/**
 * @brief Cartesian tree
 *
 */

#include <functional>
#include <stack>
#include <tuple>
#include <vector>

namespace lib {

/**
 * @brief 计算笛卡尔树，空节点为 -1
 */
template <typename Type, typename Comp = std::less<>>
std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>
build_Cartesian_tree(const std::vector<Type> &a) {
  int n = a.size();
  Comp comp;
  std::vector<int> l(n, -1), r(n, -1), p(n, -1);
  std::stack<int, std::vector<int>> s;
  for (int i = 0; i != n; ++i) {
    int last_poped = -1;
    while (!s.empty() && comp(a[i], a[s.top()])) last_poped = s.top(), s.pop();
    if (last_poped != -1) p[l[i] = last_poped] = i;
    if (!s.empty()) r[p[i] = s.top()] = i;
    s.push(i);
  }
  return {l, r, p};
}

} // namespace lib

#endif