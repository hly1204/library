#ifndef RADIX_2_NTT_HEADER_HPP
#define RADIX_2_NTT_HEADER_HPP

/**
 * @brief radix-2 NTT / 基-2 数论变换
 * @docs docs/math/formal_power_series/radix_2_NTT.md
 */

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

#include "../../traits/modint.hpp"

namespace lib {

/**
 * @note 必须用 NTT 友好的模数！！！
 */
template <typename mod_t>
class NTT {
public:
  NTT() = delete;

  static void set_root(int len) {
    static int lim = 0;
    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());
    if (lim == 0) {
      constexpr int offset = 20;
      rt.resize(1 << offset);
      irt.resize(1 << offset);
      rt[0] = irt[0] = 1;
      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod() >> (offset + 1)), ig_t = g_t.inv();
      rt[1 << (offset - 1)] = g_t, irt[1 << (offset - 1)] = ig_t;
      for (int i = offset - 2; i >= 0; --i) {
        g_t *= g_t, ig_t *= ig_t;
        rt[1 << i] = g_t, irt[1 << i] = ig_t;
      }
      lim = 1;
    }
    for (; (lim << 1) < len; lim <<= 1) {
      mod_t g = rt[lim], ig = irt[lim];
      for (int i = lim + 1, e = lim << 1; i < e; ++i) {
        rt[i]  = rt[i - lim] * g;
        irt[i] = irt[i - lim] * ig;
      }
    }
  }

  static void dft(int n, mod_t *x) {
    for (int j = 0, l = n >> 1; j != l; ++j) {
      mod_t u = x[j], v = x[j + l];
      x[j] = u + v, x[j + l] = u - v;
    }
    for (int i = n >> 1; i >= 2; i >>= 1) {
      for (int j = 0, l = i >> 1; j != l; ++j) {
        mod_t u = x[j], v = x[j + l];
        x[j] = u + v, x[j + l] = u - v;
      }
      for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
        mod_t root = rt[m];
        for (int k = 0; k != l; ++k) {
          mod_t u = x[j + k], v = x[j + k + l] * root;
          x[j + k] = u + v, x[j + k + l] = u - v;
        }
      }
    }
  }

  static void idft(int n, mod_t *x) {
    for (int i = 2; i < n; i <<= 1) {
      for (int j = 0, l = i >> 1; j != l; ++j) {
        mod_t u = x[j], v = x[j + l];
        x[j] = u + v, x[j + l] = u - v;
      }
      for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
        mod_t root = irt[m];
        for (int k = 0; k != l; ++k) {
          mod_t u = x[j + k], v = x[j + k + l];
          x[j + k] = u + v, x[j + k + l] = (u - v) * root;
        }
      }
    }
    mod_t iv(mod_t(n).inv());
    for (int j = 0, l = n >> 1; j != l; ++j) {
      mod_t u = x[j] * iv, v = x[j + l] * iv;
      x[j] = u + v, x[j + l] = u - v;
    }
  }

  static void even_dft(int n, mod_t *x) {
    static constexpr mod_t IT(mod_t(2).inv());
    for (int i = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * (x[i] + x[i + 1]);
  }

  static void odd_dft(int n, mod_t *x) {
    static constexpr mod_t IT(mod_t(2).inv());
    for (int i = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * irt[j] * (x[i] - x[i + 1]);
  }

  static void dft_doubling(int n, mod_t *x) {
    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());
    std::copy_n(x, n, x + n);
    idft(n, x + n);
    mod_t k(1), t(g.pow((modint_traits<mod_t>::get_mod() - 1) / (n << 1)));
    for (int i = 0; i != n; ++i) x[n + i] *= k, k *= t;
    dft(n, x + n);
  }

private:
  static inline std::vector<mod_t> rt, irt;
};

std::uint32_t get_ntt_len(std::uint32_t n) {
  --n;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  return (n | n >> 16) + 1;
}

/**
 * @brief 接收一个多项式，返回二进制翻转后的 DFT 序列，即 x(1), x(-1) 等，
 *        对于下标 i 和 i^1 必然是两个互为相反数的点值
 *
 * @tparam mod_t
 * @param n
 * @param x
 */
template <typename mod_t>
void dft(int n, mod_t *x) {
  NTT<mod_t>::set_root(n);
  NTT<mod_t>::dft(n, x);
}

/**
 * @brief 接收二进制翻转后的 DFT 序列，返回多项式序列 mod (x^n - 1)
 *
 * @tparam mod_t
 * @param n
 * @param x
 */
template <typename mod_t>
void idft(int n, mod_t *x) {
  NTT<mod_t>::set_root(n);
  NTT<mod_t>::idft(n, x);
}

template <typename mod_t>
void dft(std::vector<mod_t> &x) {
  NTT<mod_t>::set_root(x.size());
  NTT<mod_t>::dft(x.size(), x.data());
}

template <typename mod_t>
void idft(std::vector<mod_t> &x) {
  NTT<mod_t>::set_root(x.size());
  NTT<mod_t>::idft(x.size(), x.data());
}

} // namespace lib

#endif