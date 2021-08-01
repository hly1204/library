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

  static int deBruijn_log2(std::uint64_t n) {
    static constexpr std::uint64_t deBruijn = 0x022fdd63cc95386d;
    static constexpr int convert[64]        = {
        0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28, 62, 5,  39, 46, 44, 42,
        22, 9,  24, 35, 59, 56, 49, 18, 29, 11, 63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21,
        23, 58, 17, 10, 51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12};
    return convert[n * deBruijn >> 58];
  }

  /**
   * @brief 返回二进制中尾零的个数，若为零也会返回零
   * @see https://docs.microsoft.com/en-us/cpp/intrinsics/bitscanforward-bitscanforward64
   * @see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
   * @param n
   * @return int
   */
  static int bsf(std::uint64_t n) { return deBruijn_log2(n & ~(n - 1)); }

  static void set_root() {
    if (!dw_.empty()) return;
    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());
    auto mod = modint_traits<mod_t>::get_mod();
    int lv   = bsf(mod - 1);
    rt_.resize(lv - 1), irt_.resize(lv - 1), dw_.resize(lv - 1), idw_.resize(lv - 1);
    rt_.back() = g.pow(mod >> lv);
    for (int i = lv - 3; i >= 0; --i) rt_[i] = rt_[i + 1] * rt_[i + 1];
    mod_t v(1);
    irt_.back() = v / rt_.back();
    for (int i = lv - 3; i >= 0; --i) irt_[i] = irt_[i + 1] * irt_[i + 1];
    for (int i = 0; i < lv - 1; ++i) dw_[i] = v * rt_[i], v *= irt_[i];
    v = mod_t(1);
    for (int i = 0; i < lv - 1; ++i) idw_[i] = v * irt_[i], v *= rt_[i];
  }

  static void dft(int n, mod_t *x) {
    set_root();
    for (int j = 0, l = n >> 1; j != l; ++j) {
      mod_t u = x[j], v = x[j + l];
      x[j] = u + v, x[j + l] = u - v;
    }
    for (int i = n >> 1; i >= 2; i >>= 1) {
      for (int j = 0, l = i >> 1; j != l; ++j) {
        mod_t u = x[j], v = x[j + l];
        x[j] = u + v, x[j + l] = u - v;
      }
      mod_t root(dw_[0]);
      for (int j = i, l = i >> 1, m = 1; j != n; j += i) {
        for (int k = j; k != j + l; ++k) {
          mod_t u = x[k], v = x[k + l] * root;
          x[k] = u + v, x[k + l] = u - v;
        }
        root *= dw_[bsf(++m)];
      }
    }
  }

  static void idft(int n, mod_t *x) {
    set_root();
    for (int i = 2; i < n; i <<= 1) {
      for (int j = 0, l = i >> 1; j != l; ++j) {
        mod_t u = x[j], v = x[j + l];
        x[j] = u + v, x[j + l] = u - v;
      }
      mod_t root(idw_[0]);
      for (int j = i, l = i >> 1, m = 1; j != n; j += i) {
        for (int k = j; k != j + l; ++k) {
          mod_t u = x[k], v = x[k + l];
          x[k] = u + v, x[k + l] = (u - v) * root;
        }
        root *= idw_[bsf(++m)];
      }
    }
    const mod_t iv(mod_t(n).inv());
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
    mod_t root(1);
    for (int i = 0, j = 0; i != n; i += 2, ++j)
      x[j] = IT * root * (x[i] - x[i + 1]), root *= idw_[bsf(~static_cast<std::uint64_t>(j))];
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
  static inline std::vector<mod_t> rt_, irt_, dw_, idw_;
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
  NTT<mod_t>::idft(n, x);
}

template <typename mod_t>
void dft(std::vector<mod_t> &x) {
  NTT<mod_t>::dft(x.size(), x.data());
}

template <typename mod_t>
void idft(std::vector<mod_t> &x) {
  NTT<mod_t>::idft(x.size(), x.data());
}

} // namespace lib

#endif