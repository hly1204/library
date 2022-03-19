#ifndef WEIGHTED_DISJOINT_SET_HEADER_HPP
#define WEIGHTED_DISJOINT_SET_HEADER_HPP

#include <optional>
#include <utility>
#include <vector>

namespace lib {

template <typename Type>
class WeightedDisjointSet {
public:
  WeightedDisjointSet() = default;
  WeightedDisjointSet(int n) : p_(n + 1), sz_(n + 1, 1), diff_(n + 1, Type()) {
    for (int i = 0; i <= n; ++i) p_[i] = i;
  }
  ~WeightedDisjointSet() = default;

  void make_set(int n) {
    p_.resize(n + 1);
    sz_.assign(n + 1, 1);
    diff_.assign(n + 1, Type());
    for (int i = 0; i <= n; ++i) p_[i] = i;
  }

  bool relate(int u, int v, Type w) { // 假设 Type 满足交换律，令 val(v) - val(u) = w
    auto [uf, ud] = find(u);
    auto [vf, vd] = find(v);
    if (uf == vf) return vd - ud == w;
    if (sz_[uf] < sz_[vf]) {
      sz_[p_[uf] = vf] += sz_[uf];
      diff_[uf] = vd - ud - w;
    } else {
      sz_[p_[vf] = uf] += sz_[vf];
      diff_[vf] = ud - vd + w;
    }
    return true;
  }

  bool is_related(int u, int v) { return find(u).first == find(v).first; }
  bool is_related(int u, int v, Type w) {
    auto [uf, ud] = find(u);
    auto [vf, vd] = find(v);
    return uf == vf && vd - ud == w;
  }
  std::optional<Type> diff(int u, int v) { // 求出 val(v) - val(u)
    auto [uf, ud] = find(u);
    auto [vf, vd] = find(v);
    return uf == vf ? std::make_optional<Type>(vd - ud) : std::optional<Type>();
  }

private:
  std::vector<int> p_, sz_;
  std::vector<Type> diff_;
  std::pair<int, Type> find(int u) {
    Type d = diff_[u];
    while (p_[u] != p_[p_[u]]) {
      diff_[u] += diff_[p_[u]];
      d += diff_[p_[u]];
      d += diff_[u = p_[u] = p_[p_[u]]];
    }
    return std::make_pair(p_[u], d);
  }
};

} // namespace lib

#endif