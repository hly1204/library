#ifndef ARBITRARY_CONVOLUTION_HEADER_HPP
#define ARBITRARY_CONVOLUTION_HEADER_HPP

#include <cstdint>
#include <type_traits>
#include <vector>

#include "../../modint/Montgomery_modint.hpp"
#include "NTT_crt.hpp"
#include "convolution.hpp"

namespace lib {

// 任意模数卷积
// 只适用于模数为 32 位
template <typename Int>
std::vector<Int> convolve_mod(const std::vector<Int> &x, const std::vector<Int> &y,
                              std::uint32_t mod) {
  using u32               = std::uint32_t;
  using Type              = std::conditional_t<(sizeof(Int) <= 4), std::uint32_t, std::uint64_t>;
  static constexpr u32 M0 = 880803841, M1 = 897581057, M2 = 998244353;
  NTTCRT3<M0, M1, M2> crt(mod);
  using mod_t0 = MontModInt<M0>;
  using mod_t1 = MontModInt<M1>;
  using mod_t2 = MontModInt<M2>;
  int n = x.size(), m = y.size();
  std::vector<mod_t0> x0(n), y0(m);
  std::vector<mod_t1> x1(n), y1(m);
  std::vector<mod_t2> x2(n), y2(m);
  for (int i = 0; i < n; ++i) {
    u32 v = static_cast<Type>(x[i]);
    x0[i] = v, x1[i] = v, x2[i] = v;
  }
  for (int i = 0; i < m; ++i) {
    u32 v = static_cast<Type>(y[i]);
    y0[i] = v, y1[i] = v, y2[i] = v;
  }
  auto res0 = convolve(x0, y0);
  auto res1 = convolve(x1, y1);
  auto res2 = convolve(x2, y2);
  int nm    = res0.size();
  std::vector<Int> res;
  res.reserve(nm);
  for (int i = 0; i < nm; ++i) res.emplace_back(crt(u32(res0[i]), u32(res1[i]), u32(res2[i])));
  return res;
}

template <typename Int>
std::vector<Int> convolve_cyclic_mod(const std::vector<Int> &x, const std::vector<Int> &y,
                                     std::uint32_t mod, int cyclen) {
  using u32               = std::uint32_t;
  using Type              = std::conditional_t<(sizeof(Int) <= 4), std::uint32_t, std::uint64_t>;
  static constexpr u32 M0 = 880803841, M1 = 897581057, M2 = 998244353;
  NTTCRT3<M0, M1, M2> crt(mod);
  using mod_t0 = MontModInt<M0>;
  using mod_t1 = MontModInt<M1>;
  using mod_t2 = MontModInt<M2>;
  int n = x.size(), m = y.size();
  std::vector<mod_t0> x0(n), y0(m);
  std::vector<mod_t1> x1(n), y1(m);
  std::vector<mod_t2> x2(n), y2(m);
  for (int i = 0; i < n; ++i) {
    u32 v = static_cast<Type>(x[i]);
    x0[i] = v, x1[i] = v, x2[i] = v;
  }
  for (int i = 0; i < m; ++i) {
    u32 v = static_cast<Type>(y[i]);
    y0[i] = v, y1[i] = v, y2[i] = v;
  }
  auto res0 = convolve_cyclic(x0, y0, cyclen);
  auto res1 = convolve_cyclic(x1, y1, cyclen);
  auto res2 = convolve_cyclic(x2, y2, cyclen);
  int nm    = res0.size();
  std::vector<Int> res;
  res.reserve(nm);
  for (int i = 0; i < nm; ++i) res.emplace_back(crt(u32(res0[i]), u32(res1[i]), u32(res2[i])));
  return res;
}

} // namespace lib

#endif