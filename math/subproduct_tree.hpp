#ifndef SUBPRODUCT_TREE_HPP
#define SUBPRODUCT_TREE_HPP

#include "../common.hpp"
#include "radix2_ntt.hpp"

#include <cassert>
#include <utility>
#include <vector>

LIB_BEGIN

template <typename PolyT>
class subproduct_tree {
  using T = typename PolyT::value_type;

  struct poly_info {
    PolyT poly_, cached_dft_;
    poly_info(PolyT &&poly, PolyT &&cached_dft)
        : poly_(std::move(poly)), cached_dft_(std::move(cached_dft)) {}
    poly_info(const PolyT &poly, const PolyT &cached_dft) : poly_(poly), cached_dft_(cached_dft) {}
    explicit poly_info(const poly_info &) = default;
  };

  std::vector<std::vector<poly_info>> tree_{};

public:
  explicit subproduct_tree(const std::vector<T> &x) {
    if (x.empty()) return;
    auto &l0 = tree_.emplace_back();
    for (auto &&i : x) l0.emplace_back(PolyT{-i, T(1)}, PolyT{1 - i});
    while (tree_.back().size() != 1) {
      auto &a     = tree_.back();
      const int n = static_cast<int>(a.size());
      std::vector<poly_info> b;
      for (int i = 0; i + 1 < n; i += 2) {
        const auto &aif  = a[i].poly_;
        auto &ais        = a[i].cached_dft_;
        const auto &ai1f = a[i + 1].poly_;
        auto &ai1s       = a[i + 1].cached_dft_;
        dft_doubling(aif, ais);
        while (ai1s.size() < ais.size()) dft_doubling(ai1f, ai1s);
        auto v = ais;
        for (int j = 0, je = static_cast<int>(v.size()); j != je; ++j) v[j] *= ai1s[j];
        auto dv = v;
        idft(v);
        auto vs = aif.size() + ai1f.size() - 1;
        if (v.size() < vs) v.front() -= v.emplace_back(1);
        v.resize(vs);
        b.emplace_back(std::move(v), std::move(dv));
      }
      if (n & 1) b.emplace_back(a.back());
      tree_.emplace_back(std::move(b));
    }
  }
  std::vector<T> evaluate(const PolyT &a) const;
  PolyT interpolate(const std::vector<T> &y) const;
};

template <typename PolyT>
std::vector<typename PolyT::value_type> subproduct_tree<PolyT>::evaluate(const PolyT &a) const {
  if (tree_.empty()) return {};
  if (a.is_zero()) return std::vector<T>(tree_.front().size());
  const int n = static_cast<int>(tree_.front().size()), m = a.deg();
  // Compute `a`/((x - `x.front()`)...(x - `x.back()`)) and
  // take the coefficients of x^(-1), ..., x^(-`n`)
  const auto irev_x =
      PolyT(tree_.back().front().poly_.crbegin(), tree_.back().front().poly_.crend()).inv(m + 1);
  auto aix = a * PolyT(irev_x.crbegin(), irev_x.crend());
  if (m - n < -1) aix.resize(m + n);
  aix.erase(aix.begin(), aix.begin() + m);
  aix.resize(n);
  std::vector<PolyT> resp{aix};
  {
    auto t        = tree_.rbegin() + 1;
    const auto te = tree_.rend();
    for (; t != te; ++t) {
      std::vector<PolyT> res;
      const int ts = static_cast<int>(t->size());
      for (int i = 0, ie = static_cast<int>(resp.size()); i != ie; ++i)
        if ((i << 1 | 1) < ts) {
          auto &l       = t->at(i << 1);
          auto &r       = t->at(i << 1 | 1);
          const int len = static_cast<int>(l.cached_dft_.size());
          resp[i].resize(len);
          dft(resp[i]);
          auto respi_cpy = resp[i];
          for (int j = 0; j != len; ++j)
            resp[i][j] *= r.cached_dft_[j], respi_cpy[j] *= l.cached_dft_[j];
          res.emplace_back(std::move(resp[i]));
          auto &rr = res.emplace_back(std::move(respi_cpy));
          auto &lr = *(res.rbegin() + 1);
          idft(lr), idft(rr);
          lr.erase(lr.begin(), lr.begin() + r.poly_.deg());
          lr.resize(l.poly_.deg());
          rr.erase(rr.begin(), rr.begin() + l.poly_.deg());
          rr.resize(r.poly_.deg());
        } else {
          res.emplace_back(std::move(resp[i]));
        }
      resp.swap(res);
    }
  }
  std::vector<T> res(n);
  for (int i = 0; i != n; ++i) res[i] = resp[i].front();
  return res;
}

template <typename PolyT>
PolyT subproduct_tree<PolyT>::interpolate(const std::vector<T> &y) const {
  assert(y.size() == tree_.front().size());
  const int n = static_cast<int>(y.size());
  auto yp     = evaluate(tree_.back().front().poly_.deriv());
  std::vector<T> iyp(yp.size());
  {
    T v(1);
    for (int i = 0; i != n; ++i) iyp[i] = v, v *= yp[i];
    v = v.inv();
    for (int i = n - 1; i >= 0; --i) iyp[i] *= v, v *= yp[i];
  }
  std::vector<PolyT> resp;
  resp.reserve(n);
  for (int i = 0; i != n; ++i) resp.emplace_back(PolyT{y[i] * iyp[i]});
  for (auto t = tree_.begin(); resp.size() != 1; ++t) {
    assert(t->size() == resp.size());
    std::vector<PolyT> res;
    for (int i = 0, ie = static_cast<int>(resp.size()); i + 1 < ie; i += 2) {
      auto &l = t->at(i).cached_dft_;
      auto &r = t->at(i + 1).cached_dft_;
      dft_doubling(resp[i]);
      const int len = static_cast<int>(l.size());
      {
        auto respi1 = resp[i + 1];
        idft(respi1);
        while (static_cast<int>(resp[i + 1].size()) < len) dft_doubling(respi1, resp[i + 1]);
      }
      auto &rr = res.emplace_back(std::move(resp[i]));
      for (int j = 0; j != len; ++j) rr[j] = rr[j] * r[j] + resp[i + 1][j] * l[j];
    }
    if (t->size() & 1) res.emplace_back(std::move(resp.back()));
    resp.swap(res);
  }
  idft(resp.front());
  resp.front().shrink();
  return resp.front();
}

template <typename PolyT>
std::vector<typename PolyT::value_type>
evaluation(const PolyT &a, const std::vector<typename PolyT::value_type> &x) {
  return subproduct_tree<PolyT>(x).evaluate(a);
}

template <template <typename> typename PolyT, typename ModIntT>
PolyT<ModIntT> interpolation(const std::vector<ModIntT> &x, const std::vector<ModIntT> &y) {
  return subproduct_tree<PolyT<ModIntT>>(x).interpolate(y);
}

LIB_END

#endif