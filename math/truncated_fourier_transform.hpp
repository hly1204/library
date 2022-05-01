#ifndef TRUNCATED_FOURIER_TRANSFORM_HPP
#define TRUNCATED_FOURIER_TRANSFORM_HPP

#include "../common.hpp"
#include "radix2_ntt.hpp"

#include <type_traits>
#include <utility>
#include <vector>

LIB_BEGIN

template <typename ContainerT>
void tft(ContainerT &&a) {
  using Container          = std::remove_cv_t<std::remove_reference_t<ContainerT>>;
  using T                  = typename Container::value_type;
  static constexpr auto rt = detail::root<T>();
  static std::vector<T> root(1);
  const int n = static_cast<int>(a.size());
  if ((n & (n - 1)) == 0) return dft(std::forward<ContainerT>(a));
  const int len = ntt_len(n);
  if (int s = static_cast<int>(root.size()); s << 1 < len) {
    root.resize(len >> 1);
    for (int i = detail::bsf(s), j; 1 << i < len >> 1; ++i) {
      root[j = 1 << i] = rt[i];
      for (int k = j + 1; k < j << 1; ++k) root[k] = root[k - j] * root[j];
    }
  }
  a.resize(len);
  for (int j = 0, l = len >> 1; j != l; ++j) {
    T u(a[j]), v(a[j + l]);
    a[j] = u + v, a[j + l] = u - v;
  }
  for (int i = len >> 1; i >= 2; i >>= 1) {
    for (int j = 0, l = i >> 1; j != l; ++j) {
      T u(a[j]), v(a[j + l]);
      a[j] = u + v, a[j + l] = u - v;
    }
    for (int j = i, l = i >> 1, m = 1; j < n && j != len; j += i, ++m)
      for (int k = j; k != j + l; ++k) {
        T u(a[k]), v(a[k + l] * root[m]);
        a[k] = u + v, a[k + l] = u - v;
      }
  }
  a.resize(n);
}

template <typename ContainerT>
void itft(ContainerT &&a) {
  using Container           = std::remove_cv_t<std::remove_reference_t<ContainerT>>;
  using T                   = typename Container::value_type;
  static constexpr auto rt  = detail::root<T>();
  static constexpr auto irt = detail::iroot<T>();
  static std::vector<T> root{T(1)}, iroot{T(1)};
  const int n = static_cast<int>(a.size());
  if ((n & (n - 1)) == 0) return idft(std::forward<ContainerT>(a));
  const int len = ntt_len(n);
  if (int s = static_cast<int>(root.size()); s << 1 < len) {
    root.resize(len >> 1);
    iroot.resize(len >> 1);
    for (int i = detail::bsf(s), j; 1 << i < len >> 1; ++i) {
      root[j = 1 << i] = rt[i], iroot[j] = irt[i];
      for (int k = j + 1; k < j << 1; ++k)
        root[k] = root[k - j] * root[j], iroot[k] = iroot[k - j] * iroot[j];
    }
  }
  a.resize(len);
  struct itft_rec {
    itft_rec(Container &a) : a_(a), i2_(T(2).inv()) {}
    // [`head`, `tail`), [`tail`, `last`)
    void run(int head, int tail, int last) {
      if (head >= tail) return;
      if (int mid = (last - head) / 2 + head, len = mid - head; mid <= tail) {
        // pull up [`head`, `mid`)
        T i2p(1);
        for (int i = 1; i != len; i <<= 1, i2p *= i2_)
          for (int j = head, m = head / (i << 1); j != mid; j += i << 1, ++m)
            for (int k = j; k != j + i; ++k) {
              T u(a_[k]), v(a_[k + i]);
              a_[k] = u + v, a_[k + i] = (u - v) * iroot[m];
            }
        for (int i = head; i != mid; ++i) a_[i] *= i2p;
        // push down [`tail`, `last`)
        T r(root[head / (len << 1)] * 2);
        for (int i = tail; i != last; ++i) a_[i] = a_[i - len] - a_[i] * r;
        run(mid, tail, last);
        // pull up [`head`, `last`)
        r = iroot[head / (len << 1)] * i2_;
        for (int i = head; i != mid; ++i) {
          T u(a_[i]), v(a_[i + len]);
          a_[i] = (u + v) * i2_, a_[i + len] = (u - v) * r;
        }
      } else {
        T r(root[head / (len << 1)]);
        // push down [`tail`, `mid`)
        for (int i = tail; i != mid; ++i) a_[i] += a_[i + len] * r;
        run(head, tail, mid);
        // pull up [`head`, `mid`)
        for (int i = head; i != mid; ++i) a_[i] -= a_[i + len] * r;
      }
    }
    Container &a_;
    const T i2_;
  } rec(a);
  rec.run(0, n, len);
  a.resize(n);
}

LIB_END

#endif