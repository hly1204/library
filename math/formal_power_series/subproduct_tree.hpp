#ifndef SUBPRODUCT_TREE_HEADER_HPP
#define SUBPRODUCT_TREE_HEADER_HPP

/**
 * @brief multi-point evaluation & interpolation
 * @docs docs/math/formal_power_series/subproduct_tree.md
 */

#include <cassert>
#include <functional>
#include <numeric>
#include <vector>

namespace lib {

template <typename mod_t, typename PolyType>
class SubproductTree {
public:
  SubproductTree(const std::vector<mod_t> &x_set) : tree_(x_set.size() << 2) {
    assert(!tree_.empty());
    // tree_ 为 1-indexed
    std::function<void(int, int, int)> build_tree = [&](int idx, int l, int r) {
      if (l == r - 1) {
        tree_[idx] = PolyType{-x_set[l], mod_t(1)};
      } else {
        build_tree(idx << 1, l, (l + r) >> 1), build_tree(idx << 1 | 1, (l + r) >> 1, r);
        tree_[idx] = tree_[idx << 1] * tree_[idx << 1 | 1];
      }
    };
    build_tree(1, 0, x_set.size());
  }
  ~SubproductTree() = default;

  std::vector<mod_t> godown(const PolyType &f) const {
    std::vector<mod_t> res;
    res.reserve(tree_.size() >> 2);
    std::function<void(int, int, int, const PolyType &)> dfs = [&](int idx, int l, int r,
                                                                   const PolyType &t) {
      PolyType t_mod = t % tree_[idx];
      if (l == r - 1) {
        res.emplace_back(t_mod[0]);
      } else {
        dfs(idx << 1, l, (l + r) >> 1, t_mod), dfs(idx << 1 | 1, (l + r) >> 1, r, t_mod);
      }
    };
    dfs(1, 0, tree_.size() >> 2, f);
    return res;
  }

  PolyType goup(const std::vector<mod_t> &y_set) const {
    assert(y_set.size() == (tree_.size() >> 2));
    std::vector<mod_t> in_set = godown(tree_[1].deriv());
    std::vector<mod_t> p_sum(in_set.size()), n_set(in_set.size());
    std::partial_sum(in_set.begin(), in_set.end(), p_sum.begin(), std::multiplies<>());
    mod_t p_inv = mod_t(1) / p_sum.back();
    for (int i = int(n_set.size()) - 1; i > 0; --i)
      n_set[i] = p_sum[i - 1] * y_set[i] * p_inv, p_inv *= in_set[i];
    n_set[0]                                   = y_set[0] * p_inv;
    std::function<PolyType(int, int, int)> dfs = [&](int idx, int l, int r) {
      if (l == r - 1) {
        return PolyType{n_set[l]};
      } else {
        return dfs(idx << 1, l, (l + r) >> 1) * tree_[idx << 1 | 1] +
               dfs(idx << 1 | 1, (l + r) >> 1, r) * tree_[idx << 1];
      }
    };
    return dfs(1, 0, y_set.size());
  }

private:
  std::vector<PolyType> tree_;
};

template <typename PolyType, typename mod_t>
std::vector<mod_t> evaluate(const PolyType &f, const std::vector<mod_t> &x_set) {
  return SubproductTree<mod_t, PolyType>(x_set).godown(f);
}

template <typename PolyType, typename mod_t>
void interpolate(const std::vector<mod_t> &x_set, const std::vector<mod_t> &y_set, PolyType &res) {
  res = SubproductTree<mod_t, PolyType>(x_set).goup(y_set);
}

} // namespace lib

#endif