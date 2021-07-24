#ifndef BINOMIAL_COEFFICIENT_MOD_HEADER_HPP
#define BINOMIAL_COEFFICIENT_MOD_HEADER_HPP

/**
 * @brief binomial coefficient mod / 二项式系数取模
 *
 */

#include <cassert>
#include <cstdint>
#include <tuple>
#include <vector>

#include "../basic/binary_pow.hpp"
#include "../basic/crt.hpp"
#include "../basic/exgcd.hpp"

namespace lib {

class BinomialCoefficientModSmall {
public:
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  /**
   * @brief 二项式系数取模
   * @param mod 素因数分解后所有素数幂次的因数和不能太大
   */
  BinomialCoefficientModSmall(u32 mod) {
    for (u32 i = 2; i * i <= mod; ++i) {
      if (mod % i == 0) {
        u32 e = 0, old_mod = mod;
        do {
          ++e;
          mod /= i;
        } while (mod % i == 0);
        u32 ie = old_mod / mod;
        factor_.push_back({i, e, ie, {}, {}});
        auto &fac  = std::get<3>(factor_.back());
        auto &ifac = std::get<4>(factor_.back());
        fac.resize(ie);
        ifac.resize(ie);
        if (e == 1) {
          fac[0] = ifac[0] = 1;
          for (int j = 1; j != ie; ++j) fac[j] = static_cast<u64>(fac[j - 1]) * j % ie;
          ifac[ie - 1] = ie - 1; // Wilson's theorem
          for (int j = ie - 2; j > 0; --j) ifac[j] = static_cast<u64>(ifac[j + 1]) * (j + 1) % ie;
        } else {
          ifac[0] = fac[0] = 1;
          for (int j = 1; j != ie; ++j) {
            fac[j]  = (j % i == 0) ? fac[j - 1] : static_cast<u64>(fac[j - 1]) * j % ie;
            ifac[j] = static_cast<u64>(fac[j]) * ifac[j - 1] % ie;
          }
          u32 ivie = inv_mod(ifac[ie - 1], ie);
          for (int j = ie - 1; j > 0; --j)
            ifac[j] = static_cast<u64>(ivie) * ifac[j - 1] % ie,
            ivie    = static_cast<u64>(ivie) * fac[j] % ie;
        }
      }
    }
    if (mod != 1) {
      u32 ie = mod;
      factor_.push_back({mod, 1, mod, {}, {}});
      auto &fac  = std::get<3>(factor_.back());
      auto &ifac = std::get<4>(factor_.back());
      fac.resize(ie);
      ifac.resize(ie);
      fac[0] = ifac[0] = 1;
      for (int j = 1; j != ie; ++j) fac[j] = static_cast<u64>(fac[j - 1]) * j % ie;
      ifac[ie - 1] = ie - 1; // Wilson's theorem
      for (int j = ie - 2; j > 0; --j) ifac[j] = static_cast<u64>(ifac[j + 1]) * (j + 1) % ie;
    }
    std::vector<u32> factor(factor_.size());
    for (int i = 0, e = factor_.size(); i < e; ++i) factor[i] = std::get<2>(factor_[i]);
    crt_.set_m(factor);
  }

  ~BinomialCoefficientModSmall() = default;

  /**
   * @brief 返回 nCm 对 mod 取模
   * @todo 注意这里 n 这个上指标可以为负数，但我并未实现
   * @param n
   * @param m
   * @return u32
   */
  u32 operator()(u64 n, u64 m) const {
    if (n < m) return 0;
    std::vector<u32> v;
    for (auto &i : factor_) {
      u32 p = std::get<0>(i), q = std::get<1>(i), pq = std::get<2>(i);
      const std::vector<u32> &fac = std::get<3>(i), &ifac = std::get<4>(i);
      u64 n_t = n, m_t = m, res = 1;
      if (q == 1) {
        for (; n_t; n_t /= p, m_t /= p) {
          if (n_t % p < m_t % p) {
            res = 0;
            break;
          }
          res = res * fac[n_t % p] % p * ifac[m_t % p] % p * ifac[n_t % p - m_t % p] % p;
        }
      } else {
        u64 r = n_t - m_t, k = 0;
        for (u64 n1 = n_t / p; n1; n1 /= p) k += n1;
        for (u64 m1 = m_t / p; m1; m1 /= p) k -= m1;
        for (u64 r1 = r / p; r1; r1 /= p) k -= r1;
        if (k >= q) {
          res = 0;
        } else {
          u32 pk          = lib::pow(p, k);
          u64 is_negative = 0;
          for (; n_t; n_t /= p, m_t /= p, r /= p) {
            res = res * fac[n_t % pq] % pq * ifac[m_t % pq] % pq * ifac[r % pq] % pq;
            is_negative += n_t / pq + m_t / pq + r / pq;
          }
          if ((p == 2 && q >= 3) || (is_negative & 1) == 0) res = res * pk % pq;
          else
            res = (pq - res) * pk % pq;
        }
      }
      v.push_back(res);
    }
    return crt_(v);
  }

private:
  std::vector<std::tuple<u32, u32, u32, std::vector<u32>, std::vector<u32>>> factor_;
  CoprimeCRT<u32> crt_;
};

} // namespace lib

#endif