#ifndef WEIGHTED_DISJOINT_SET_HPP
#define WEIGHTED_DISJOINT_SET_HPP

#include "../common.hpp"

#include <numeric>
#include <optional>
#include <utility>
#include <vector>

LIB_BEGIN

template <typename TypeT>
class weighted_disjoint_set {
  // assume `TypeT`(a) + `TypeT`(b) = `TypeT`(b) + `TypeT`(a).
  mutable std::vector<int> p_{};   // parent
  std::vector<int> s_{};           // size
  mutable std::vector<TypeT> d_{}; // difference

  std::pair<int, TypeT> find_pair(int u) const {
    TypeT d = d_[u];
    while (p_[u] != p_[p_[u]]) {
      d_[u] += d_[p_[u]];
      d += d_[p_[u]];
      d += d_[u = p_[u] = p_[p_[u]]];
    }
    return std::make_pair(p_[u], d);
  }

public:
  weighted_disjoint_set() = default;
  explicit weighted_disjoint_set(int n) : p_(n), s_(n, 1), d_(n) {
    std::iota(p_.begin(), p_.end(), 0);
  }
  void make_set(int n) {
    p_.resize(n);
    s_.assign(n, 1);
    d_.assign(n, TypeT());
    std::iota(p_.begin(), p_.end(), 0);
  }
  int find(int u) const { return find_pair(u).first; }
  bool relate(int u, int v, TypeT w) {
    // let val(v) - val(u) = w.
    auto [uf, ud] = find_pair(u);
    auto [vf, vd] = find_pair(v);
    if (uf == vf) return vd - ud == w;
    if (s_[uf] < s_[vf]) {
      s_[p_[uf] = vf] += s_[uf];
      d_[uf] = vd - ud - w;
    } else {
      s_[p_[vf] = uf] += s_[vf];
      d_[vf] = ud - vd + w;
    }
    return true;
  }
  bool is_related(int u, int v) const { return find(u) == find(v); }
  bool is_related(int u, int v, TypeT w) const {
    auto [uf, ud] = find_pair(u);
    auto [vf, vd] = find_pair(v);
    return uf == vf && vd - ud == w;
  }
  // returns val(v) - val(u).
  std::optional<TypeT> diff(int u, int v) const {
    auto [uf, ud] = find_pair(u);
    auto [vf, vd] = find_pair(v);
    return uf == vf ? std::make_optional<TypeT>(vd - ud) : std::optional<TypeT>();
  }
  int get_component_size(int u) const { return s_[find(u)]; }
};

LIB_END

#endif
