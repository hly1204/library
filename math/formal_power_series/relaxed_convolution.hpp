#ifndef RELAXED_CONVOLUTION_HEADER_HPP
#define RELAXED_CONVOLUTION_HEADER_HPP

/**
 * @brief relaxed convolution / 在线卷积
 * @docs docs/math/formal_power_series/relaxed_convolution.md
 */

#include <algorithm>
#include <iterator>
#include <vector>

namespace lib {

/**
 * @brief 在线卷积
 * @ref J. van der Hoeven. Relax, but don't be too lazy. JSC, 34:479–542, 2002.
 * @tparam mod_t
 * @note 时间为 O(nlog^2 n) 且常数很大
 */
template <typename mod_t, typename ConvFuncType>
class RelaxedConvolution {
public:
  RelaxedConvolution(const std::vector<mod_t> &A, const std::vector<mod_t> &B, ConvFuncType &&f)
      : A_(A), B_(B), n_(0), conv_(f) {}
  ~RelaxedConvolution() = default;

  mod_t next() {
    // enlarge prod
    int sz = 1;
    while (sz <= (n_ << 1)) sz <<= 1;
    if (prod_.size() < sz) prod_.resize(sz, mod_t(0));
    // accumulate
    int k = (n_ + 2) << 1, p = -1;
    while ((k & 1) == 0) {
      k >>= 1, ++p;
      int a0 = (1 << p) - 1, b0 = (1 << (p + 1)) - 1;
      int a1 = ((k - 1) << p) - 1, b1 = (k << p) - 1;
      auto t0 = conv_(cut(A_, a0, b0), cut(B_, a1, b1));
      for (int offset = (k << p) - 2, i = offset,
               ie = std::min(((k + 2) << p) - 3, static_cast<int>(t0.size()) + offset);
           i < ie; ++i)
        prod_[i] += t0[i - offset];
      if (k == 2) return prod_[n_++];
      auto t1 = conv_(cut(B_, a0, b0), cut(A_, a1, b1));
      for (int offset = (k << p) - 2, i = offset,
               ie = std::min(((k + 2) << p) - 3, static_cast<int>(t1.size()) + offset);
           i < ie; ++i)
        prod_[i] += t1[i - offset];
    }
    return prod_[n_++];
  }

private:
  const std::vector<mod_t> &A_, &B_;
  std::vector<mod_t> prod_;
  int n_;
  ConvFuncType &&conv_;

  std::vector<mod_t> cut(const std::vector<mod_t> &x, int s, int e) const { // [s, e)
    int n = x.size();
    if (e <= n) return std::vector<mod_t>(x.begin() + s, x.begin() + e);
    if (n <= s) return {};
    return std::vector<mod_t>(x.begin() + s, x.end());
  }
};

} // namespace lib

#endif