#ifndef ROLLBACKABLE_DISJOINT_SET_HEADER_HPP
#define ROLLBACKABLE_DISJOINT_SET_HEADER_HPP

#include <stack>
#include <vector>

namespace lib {

class RollbackableDisjointSet {
public:
  RollbackableDisjointSet() = default;
  RollbackableDisjointSet(int n) : p_(n + 1), sz_(n + 1, 1) {
    for (int i = 0; i <= n; ++i) p_[i] = i;
  }
  ~RollbackableDisjointSet() = default;

  void make_set(int n) {
    p_.resize(n + 1);
    sz_.assign(n + 1, 1);
    while (!stk_.empty()) stk_.pop();
    for (int i = 0; i <= n; ++i) p_[i] = i;
  }

  int find(int u) const {
    while (u != p_[u]) u = p_[u];
    return u;
  }

  bool same(int u, int v) const { return find(u) == find(v); }

  int unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return u;
    return link(u, v);
  }

  int get_component_size(int u) const { return sz_[find(u)]; }

  // 撤销上一次成功的 unite
  // 只能撤销成功的 unite 如果不成功是不能撤销的
  void undo() {
    int u = stk_.top(); // 取出小树，修改小树的 parent
    stk_.pop();
    sz_[p_[u]] -= sz_[u];
    p_[u] = u;
  }

  void rollback(int k) {
    while (k--) undo();
  }

private:
  std::vector<int> p_, sz_;
  std::stack<int, std::vector<int>> stk_;

  int link(int u, int v) {
    if (sz_[u] > sz_[v]) return link(v, u);
    sz_[v] += sz_[u];
    stk_.push(u);     // 将小树放入栈中
    return p_[u] = v; // u 是小树， v 是大树，把小树接到大树上
  }
};

} // namespace lib

#endif