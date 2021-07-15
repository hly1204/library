#ifndef STATIC_TREE_BINARY_LIFTING_HEADER_HPP
#define STATIC_TREE_BINARY_LIFTING_HEADER_HPP

/**
 * @brief static tree binary lifting / 树上倍增法
 *
 */

#include <cassert>
#include <queue>
#include <vector>

namespace lib {

/**
 * @brief 静态树 LCA 和 LA 的回答，每次在 O(\log n) 时间，需要 O(n\log n) 时间预处理
 *
 */
class StaticTreeBinaryLifting {
public:
  /**
   * @param parent 注意设置 parent[root]=-1
   */
  StaticTreeBinaryLifting(const std::vector<int> &parent) : depth_(parent.size(), -1) {
    int n = parent.size(), root, lg2_n = 0;
    assert(n > 0);
    while ((1 << lg2_n) < n) ++lg2_n;
    parent_.assign(lg2_n, std::vector<int>(n, -1));
    std::vector<int> g(n), idx(n + 1, 0);
    for (int i = 0; i < n; ++i)
      if (parent[i] != -1) {
        ++idx[parent[i]];
      } else {
        root = i;
      }
    for (int i = 0, sum = 0; i <= n; ++i) sum += idx[i], idx[i] = sum - idx[i];
    for (int i = 0; i < n; ++i)
      if (parent[i] != -1) g[idx[parent[i]]++] = i;
    for (int i = n - 1; i > 0; --i) idx[i] = idx[i - 1];
    idx[0] = 0;
    std::queue<int> q;
    q.push(root);
    for (int dep = 1; !q.empty(); ++dep)
      for (int s = q.size(); s != 0; --s) {
        int t = q.front();
        q.pop();
        depth_[t] = dep;
        for (int i = 1; (1 << i) < dep; ++i) parent_[i][t] = parent_[i - 1][parent_[i - 1][t]];
        for (int i = idx[t], ie = idx[t + 1]; i < ie; ++i)
          if (depth_[g[i]] == -1) {
            parent_[0][g[i]] = t;
            q.push(g[i]);
          }
      }
  }
  ~StaticTreeBinaryLifting() = default;

  int query_la(int x, int k) const {
    assert(k < depth_[x]);
    for (int i = 0; (1 << i) <= k; ++i)
      if (1 << i & k) x = parent_[i][x];
    return x;
  }

  int query_lca(int x, int y) const {
    if (depth_[x] < depth_[y]) std::swap(x, y);
    if ((x = query_la(x, depth_[x] - depth_[y])) == y) return x;
    for (int i = parent_.size() - 1; i >= 0; --i)
      if (parent_[i][x] != parent_[i][y]) x = parent_[i][x], y = parent_[i][y];
    return parent_[0][x];
  }

private:
  std::vector<int> depth_;
  std::vector<std::vector<int>> parent_;
};

} // namespace lib

#endif