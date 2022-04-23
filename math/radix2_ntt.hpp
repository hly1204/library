#ifndef RADIX2_NTT_HPP
#define RADIX2_NTT_HPP

#include "../common.hpp"

#include <array>
#include <cassert>
#include <type_traits>
#include <vector>

LIB_BEGIN

namespace detail {

template <typename IntT>
constexpr std::enable_if_t<std::is_integral_v<IntT>, int> bsf(IntT v) {
  if (static_cast<std::make_signed_t<IntT>>(v) <= 0) return -1;
  int res = 0;
  for (; (v & 1) == 0; ++res) v >>= 1;
  return res;
}

template <typename ModIntT>
constexpr ModIntT quadratic_nonresidue_prime() {
  auto mod = ModIntT::mod();
  for (int i = 2;; ++i)
    if (ModIntT(i).pow(mod >> 1) == mod - 1) return ModIntT(i);
}

template <typename ModIntT>
constexpr ModIntT gen_of_sylow_2_subgroup() {
  auto mod = ModIntT::mod();
  return quadratic_nonresidue_prime<ModIntT>().pow(mod >> bsf(mod - 1));
}

template <typename ModIntT>
constexpr std::array<ModIntT, bsf(ModIntT::mod() - 1) - 1> root() {
  std::array<ModIntT, bsf(ModIntT::mod() - 1) - 1> rt; // order(`rt[i]`) = 2^(i + 2).
  rt.back() = gen_of_sylow_2_subgroup<ModIntT>();
  for (int i = bsf(ModIntT::mod() - 1) - 3; i >= 0; --i) rt[i] = rt[i + 1] * rt[i + 1];
  return rt;
}

template <typename ModIntT>
constexpr std::array<ModIntT, bsf(ModIntT::mod() - 1) - 1> iroot() {
  std::array<ModIntT, bsf(ModIntT::mod() - 1) - 1> irt;
  irt.back() = gen_of_sylow_2_subgroup<ModIntT>().inv();
  for (int i = bsf(ModIntT::mod() - 1) - 3; i >= 0; --i) irt[i] = irt[i + 1] * irt[i + 1];
  return irt;
}

} // namespace detail

// Input:  integer `n`.
// Output: 2^(⌈log_2(`n`)⌉).
int ntt_len(int n) {
  --n;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  return (n | n >> 16) + 1;
}

// Input:           f(x) = `a[0]` + `a[1]`x + ... + `a[n - 1]`x^(`n` - 1) where `n` is power of 2.
// Output(inplace): reversed binary permutation of [f(ζ^0), f(ζ), f(ζ^2), ..., f(ζ^(`n` - 1))].
template <typename IterT>
void dft_n(IterT a, int n) {
  assert((n & (n - 1)) == 0);
  using T                  = typename std::iterator_traits<IterT>::value_type;
  static constexpr auto rt = detail::root<T>();
  static std::vector<T> root(1);
  if (int s = static_cast<int>(root.size()); s << 1 < n) {
    root.resize(n >> 1);
    for (int i = detail::bsf(s); (1 << i) < (n >> 1); ++i) {
      int j   = 1 << i;
      root[j] = rt[i];
      for (int k = j + 1; k < (j << 1); ++k) root[k] = root[k - j] * root[j];
    }
  }
  for (int j = 0, l = n >> 1; j != l; ++j) {
    T u(a[j]), v(a[j + l]);
    a[j] = u + v, a[j + l] = u - v;
  }
  for (int i = n >> 1; i >= 2; i >>= 1) {
    for (int j = 0, l = i >> 1; j != l; ++j) {
      T u(a[j]), v(a[j + l]);
      a[j] = u + v, a[j + l] = u - v;
    }
    for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
      for (int k = j; k != j + l; ++k) {
        T u(a[k]), v(a[k + l] * root[m]);
        a[k] = u + v, a[k + l] = u - v;
      }
    }
  }
}

// Input:           reversed binary permutation of [f(ζ^0), f(ζ), f(ζ^2), ..., f(ζ^(`n` - 1))].
// Output(inplace): f(x) = `a[0]` + `a[1]`x + ... + `a[n - 1]`x^(`n` - 1) where `n` is power of 2.
template <typename IterT>
void idft_n(IterT a, int n) {
  assert((n & (n - 1)) == 0);
  using T                  = typename std::iterator_traits<IterT>::value_type;
  static constexpr auto rt = detail::iroot<T>();
  static std::vector<T> root(1);
  if (int s = static_cast<int>(root.size()); s << 1 < n) {
    root.resize(n >> 1);
    for (int i = detail::bsf(s); (1 << i) < (n >> 1); ++i) {
      int j   = 1 << i;
      root[j] = rt[i];
      for (int k = j + 1; k < (j << 1); ++k) root[k] = root[k - j] * root[j];
    }
  }
  for (int i = 2; i < n; i <<= 1) {
    for (int j = 0, l = i >> 1; j != l; ++j) {
      T u(a[j]), v(a[j + l]);
      a[j] = u + v, a[j + l] = u - v;
    }
    for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
      for (int k = j; k != j + l; ++k) {
        T u(a[k]), v(a[k + l]);
        a[k] = u + v, a[k + l] = (u - v) * root[m];
      }
    }
  }
  const T iv(T::mod() - T::mod() / n);
  for (int j = 0, l = n >> 1; j != l; ++j) {
    T u(a[j] * iv), v(a[j + l] * iv);
    a[j] = u + v, a[j + l] = u - v;
  }
}

template <typename ContainerT>
void dft(ContainerT &a) {
  dft_n(a.begin(), a.size());
}

template <typename ContainerT>
void idft(ContainerT &a) {
  idft_n(a.begin(), a.size());
}

LIB_END

#endif