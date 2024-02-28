#ifndef SUBSET_CONVOLUTION_HPP
#define SUBSET_CONVOLUTION_HPP

#include "../common.hpp"
#include "radix2_ntt.hpp"
#include "zeta_transform.hpp"

#include <cassert>
#include <vector>

LIB_BEGIN

struct set_power_series {
  set_power_series() = delete;

  template <typename ModIntT>
  static std::vector<std::vector<ModIntT>> add_rank(const std::vector<ModIntT> &x) {
    const int n = static_cast<int>(x.size());
    assert((n & (n - 1)) == 0);
    const int rank = detail::bsf(x.size()) + 1;
    std::vector rz(rank, std::vector<ModIntT>(x.size()));
    for (int i = 0; i != n; ++i) rz[popcount(static_cast<unsigned>(i))][i] = x[i];
    return rz;
  }

  template <typename ModIntT>
  static std::vector<ModIntT> remove_rank(const std::vector<std::vector<ModIntT>> &x) {
    const int rank = static_cast<int>(x.size());
    assert(rank != 0);
    const int n = static_cast<int>(x.front().size());
    assert((n & (n - 1)) == 0);
    std::vector<ModIntT> z(n);
    for (int i = 0; i != n; ++i) z[i] = x[popcount(static_cast<unsigned>(i))][i];
    return z;
  }

  template <typename ModIntT>
  static std::vector<ModIntT> subset_convolution(const std::vector<ModIntT> &x,
                                                 const std::vector<ModIntT> &y) {
    // https://codeforces.com/blog/entry/126418
    // 0 -> 1 -> 3 -> 7 -> 15
    // 2 -> 5 -> 11
    // ...
    static const int map[] = {0, 0, 1, 0, 2, 1, 3, 0, 4,  2, 5,  1,
                              6, 3, 7, 0, 8, 4, 9, 2, 10, 5, 11, 1};

    const int n = static_cast<int>(x.size());

    assert(static_cast<int>(y.size()) == n);
    auto rx        = add_rank(x);
    auto ry        = add_rank(y);
    const int rank = static_cast<int>(rx.size());
    for (auto &&i : rx) zeta_transform(i);
    for (auto &&i : ry) zeta_transform(i);

    std::vector<std::vector<ModIntT>> rxy(rank / 2 + 1, std::vector<ModIntT>(x.size()));

    for (int i = 0; i != rank; ++i)
      for (int j = i; j >= 0; --j)
        for (int k = 0; k != n; ++k) rxy[map[i]][k] += rx[i][k] * ry[i - j][k];

    for (auto &&i : rxy) moebius_transform(i);
    std::vector<ModIntT> res(n);
    for (int i = 0; i != n; ++i) res[i] = rxy[map[popcount(static_cast<unsigned>(i))]][i];
    return res;
  }
};

LIB_END

#endif
