#ifndef RADIX_4_NTT_HEADER_HPP
#define RADIX_4_NTT_HEADER_HPP

/**
 * @brief radix-4 NTT / 基-4 数论变换
 * @docs docs/math/formal_power_series/radix_4_NTT.md
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
class NTT4 {
public:
  NTT4() = delete;

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
    assert(lv >= 3);
    rt_.resize(lv - 1), irt_.resize(lv - 1), dw_.resize(lv - 2), idw_.resize(lv - 2);
    rt_.back() = g.pow(mod >> lv);
    for (int i = lv - 3; i >= 0; --i) rt_[i] = rt_[i + 1] * rt_[i + 1];
    irt_.back() = mod_t(1) / rt_.back();
    for (int i = lv - 3; i >= 0; --i) irt_[i] = irt_[i + 1] * irt_[i + 1];
    dw_[0] = rt_[1];
    for (int i = 1; i < lv - 2; ++i) dw_[i] = dw_[i - 1] * irt_[i - 1] * rt_[i + 1];
    idw_[0] = irt_[1];
    for (int i = 1; i < lv - 2; ++i) idw_[i] = idw_[i - 1] * rt_[i - 1] * irt_[i + 1];
  }

  static void dft(int n, mod_t *x) {
    set_root();
    int bn           = bsf(n);
    const mod_t imag = rt_[0];
    if (bn & 1)
      for (int i = 0, l = n >> 1; i != l; ++i) {
        mod_t u = x[i], v = x[i + l];
        x[i] = u + v, x[i + l] = u - v;
      }
    for (int i = n >> (bn & 1); i >= 4; i >>= 2) {
      for (int j = 0, l = i >> 2; j != l; ++j) {
        mod_t xd     = x[j + 0 * l];
        mod_t xc     = x[j + 1 * l];
        mod_t xb     = x[j + 2 * l];
        mod_t xa     = x[j + 3 * l];
        mod_t xapxc  = xa + xc;
        mod_t ixamxc = (xa - xc) * imag;
        mod_t xbpxd  = xb + xd;
        mod_t xdmxb  = xd - xb;
        x[j + 0 * l] = xbpxd + xapxc;
        x[j + 1 * l] = xbpxd - xapxc;
        x[j + 2 * l] = xdmxb - ixamxc;
        x[j + 3 * l] = xdmxb + ixamxc;
      }
      mod_t root(dw_[0]);
      for (int j = i, l = i >> 2, m = 1; j != n; j += i) {
        mod_t root2 = root * root, root3 = root2 * root;
        for (int k = j; k != j + l; ++k) {
          mod_t xd     = x[k + 0 * l];
          mod_t xc     = x[k + 1 * l] * root;
          mod_t xb     = x[k + 2 * l] * root2;
          mod_t xa     = x[k + 3 * l] * root3;
          mod_t xapxc  = xa + xc;
          mod_t ixamxc = (xa - xc) * imag;
          mod_t xbpxd  = xb + xd;
          mod_t xdmxb  = xd - xb;
          x[k + 0 * l] = xbpxd + xapxc;
          x[k + 1 * l] = xbpxd - xapxc;
          x[k + 2 * l] = xdmxb - ixamxc;
          x[k + 3 * l] = xdmxb + ixamxc;
        }
        root *= dw_[bsf(++m)];
      }
    }
  }

  static void idft(int n, mod_t *x) {
    set_root();
    int bn           = bsf(n);
    const mod_t imag = rt_[0];
    for (int i = 4; i <= (n >> (bn & 1)); i <<= 2) {
      for (int j = 0, l = i >> 2; j != l; ++j) {
        mod_t xw     = x[j + 0 * l];
        mod_t xx     = x[j + 1 * l];
        mod_t xy     = x[j + 2 * l];
        mod_t xz     = x[j + 3 * l];
        mod_t xwpxx  = xw + xx;
        mod_t xwmxx  = xw - xx;
        mod_t xypxz  = xy + xz;
        mod_t ixymxz = (xy - xz) * imag;
        x[j + 0 * l] = xwpxx + xypxz;
        x[j + 1 * l] = xwmxx - ixymxz;
        x[j + 2 * l] = xwpxx - xypxz;
        x[j + 3 * l] = xwmxx + ixymxz;
      }
      mod_t root(idw_[0]);
      for (int j = i, l = i >> 2, m = 1; j != n; j += i) {
        mod_t root2 = root * root, root3 = root2 * root;
        for (int k = j; k != j + l; ++k) {
          mod_t xw     = x[k + 0 * l];
          mod_t xx     = x[k + 1 * l];
          mod_t xy     = x[k + 2 * l];
          mod_t xz     = x[k + 3 * l];
          mod_t xwpxx  = xw + xx;
          mod_t xwmxx  = xw - xx;
          mod_t xypxz  = xy + xz;
          mod_t ixymxz = (xy - xz) * imag;
          x[k + 0 * l] = xwpxx + xypxz;
          x[k + 1 * l] = (xwmxx - ixymxz) * root;
          x[k + 2 * l] = (xwpxx - xypxz) * root2;
          x[k + 3 * l] = (xwmxx + ixymxz) * root3;
        }
        root *= idw_[bsf(++m)];
      }
    }
    const mod_t iv(mod_t(n).inv());
    if (bn & 1)
      for (int i = 0, l = n >> 1; i != l; ++i) {
        mod_t u = x[i] * iv, v = x[i + l] * iv;
        x[i] = u + v, x[i + l] = u - v;
      }
    else
      for (int i = 0; i != n; ++i) x[i] *= iv;
  }

private:
  static inline std::vector<mod_t> rt_, irt_, dw_, idw_;
};

} // namespace lib

#endif