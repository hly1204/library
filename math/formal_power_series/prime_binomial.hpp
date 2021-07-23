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
  PrimeBinomial(int lim) {
    static std::uint64_t mod = 0;
    if (mod != mod_t::get_mod()) {
      mod = mod_t::get_mod();
      fac_table.clear();
      ifac_table.clear();
    }
    if (fac_table.empty()) {
      fac_table.emplace_back(1);
      ifac_table.emplace_back(1);
    }
    init(lim);
  }
  ~PrimeBinomial() = default;

  /**
   * @brief 预处理 [0, n) 的阶乘和其逆元
   */
  static void init(int n) {
    if (int(fac_table.size()) < n) {
      int old_size = fac_table.size();
      fac_table.resize(n);
      ifac_table.resize(n);
      for (int i = old_size; i < n; ++i) fac_table[i] = fac_table[i - 1] * mod_t(i);
      ifac_table.back() = mod_t(1) / fac_table.back();
      for (int i = n - 2; i >= old_size; --i) ifac_table[i] = ifac_table[i + 1] * mod_t(i + 1);
    }
  }

  mod_t fac_unsafe(int n) const { return fac_table[n]; }
  mod_t ifac_unsafe(int n) const { return ifac_table[n]; }
  mod_t inv_unsafe(int n) const { return ifac_table[n] * fac_table[n - 1]; }
  mod_t choose_unsafe(int n, int k) const {
    // 返回 binom{n}{k} 注意上指标可以为负数但这里并未实现！
    return n >= k ? fac_table[n] * ifac_table[k] * ifac_table[n - k] : mod_t(0);
  }

private:
  static inline std::vector<mod_t> fac_table, ifac_table;
};

} // namespace lib

#endif