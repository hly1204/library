#ifndef PRIME_BINOMIAL_HEADER_HPP
#define PRIME_BINOMIAL_HEADER_HPP

/**
 * @brief prime binomial / 素数用二项式系数
 *
 */

#include <cstdint>
#include <vector>

namespace lib {

template <typename mod_t>
class PrimeBinomial {
public:
  PrimeBinomial(int lim = 0) {
    static std::uint64_t mod = 0;
    if (mod != mod_t::get_mod()) {
      mod = mod_t::get_mod();
      fac_.clear();
      ifac_.clear();
    }
    if (fac_.empty()) {
      fac_.emplace_back(1);
      ifac_.emplace_back(1);
    }
    init(lim);
  }
  ~PrimeBinomial() = default;

  /**
   * @brief 预处理 [0, n) 的阶乘和其逆元
   */
  static void init(int n) {
    if (int(fac_.size()) < n) {
      int old_size = fac_.size();
      fac_.resize(n);
      ifac_.resize(n);
      for (int i = old_size; i < n; ++i) fac_[i] = fac_[i - 1] * mod_t(i);
      ifac_.back() = mod_t(1) / fac_.back();
      for (int i = n - 2; i >= old_size; --i) ifac_[i] = ifac_[i + 1] * mod_t(i + 1);
    }
  }

  mod_t fac_unsafe(int n) const { return fac_[n]; }
  mod_t ifac_unsafe(int n) const { return ifac_[n]; }
  mod_t inv_unsafe(int n) const { return ifac_[n] * fac_[n - 1]; }
  mod_t choose_unsafe(int n, int k) const {
    // 返回 binom{n}{k} 注意上指标可以为负数但这里并未实现！
    return n >= k ? fac_[n] * ifac_[k] * ifac_[n - k] : mod_t(0);
  }

private:
  static inline std::vector<mod_t> fac_, ifac_;
};

} // namespace lib

#endif