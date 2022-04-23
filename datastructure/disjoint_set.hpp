#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include "../common.hpp"

#include <numeric>
#include <vector>

LIB_BEGIN

class disjoint_set {
  mutable std::vector<int> p_{}; // parent
  std::vector<int> s_{};         // size

public:
  disjoint_set() {}
  explicit disjoint_set(int n) : p_(n), s_(n, 1) { std::iota(p_.begin(), p_.end(), 0); }
  void make_set(int n) {
    p_.resize(n);
    s_.assign(n, 1);
    std::iota(p_.begin(), p_.end(), 0);
  }
  int find(int u) const {
    // path havling
    while (p_[u] != p_[p_[u]]) u = p_[u] = p_[p_[u]];
    return p_[u];
  }
  bool is_same(int u, int v) const { return find(u) == find(v); }
  int unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return u;
    if (s_[u] < s_[v]) {
      s_[v] += s_[u];
      return p_[u] = v;
    } else {
      s_[u] += s_[v];
      return p_[v] = u;
    }
  }
  int get_component_size(int u) const { return s_[find(u)]; }
};

LIB_END

#endif