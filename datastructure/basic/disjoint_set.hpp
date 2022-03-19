#ifndef DISJOINT_SET_HEADER_HPP
#define DISJOINT_SET_HEADER_HPP

#include <vector>

namespace lib {

class DisjointSet {
public:
  DisjointSet() = default;
  DisjointSet(int n) : p_(n + 1), sz_(n + 1, 1) {
    for (int i = 0; i <= n; ++i) p_[i] = i;
  }
  ~DisjointSet() = default;

  void make_set(int n) {
    p_.resize(n + 1);
    sz_.assign(n + 1, 1);
    for (int i = 0; i <= n; ++i) p_[i] = i;
  }

  int find(int u) { // path havling
    while (p_[u] != p_[p_[u]]) u = p_[u] = p_[p_[u]];
    return p_[u];
  }

  bool same(int u, int v) { return find(u) == find(v); }

  int unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return u;
    if (sz_[u] < sz_[v]) {
      sz_[v] += sz_[u];
      return p_[u] = v;
    } else {
      sz_[u] += sz_[v];
      return p_[v] = u;
    }
  }

  int get_component_size(int u) { return sz_[find(u)]; }

private:
  std::vector<int> p_, sz_;
};

} // namespace lib

#endif