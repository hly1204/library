#ifndef EGF_HEADER_HPP
#define EGF_HEADER_HPP

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

#include "../../modint/long_Montgomery_modint.hpp"
#include "../basic/exgcd.hpp"
#include "radix_2_NTT.hpp"

namespace lib {

class ExponentialGeneratingFunction {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  using value_type = u32;

  using mod1 = LongMontModInt<0x3f9a000000000001>;
  using mod2 = LongMontModInt<0x3fc6000000000001>;

  ExponentialGeneratingFunction(u32 mod) : mod_(mod) {
    for (u32 i = 2; i * i <= mod; ++i)
      if (mod % i == 0) {
        int e       = 0;
        u32 mod_old = mod;
        do { mod /= i, ++e; } while (mod % i == 0);
        fact_.emplace_back(i, e, mod_old / mod);
      }
    if (mod != 1) fact_.emplace_back(mod, 1, mod);
  }
  ~ExponentialGeneratingFunction() = default;

  u32 get_mod() const { return mod_; }

  struct FactorInfo {
    u32 p, e, pe; // p^e=pe
    std::vector<mod1> p_pow1, ip_pow1;
    std::vector<mod2> p_pow2, ip_pow2;
    std::vector<u32> v, fac, ifac; // fac[i]=i!/p^(v[i])
    FactorInfo(u32 p, u32 e, u32 pe)
        : p(p), e(e), pe(pe), p_pow1{mod1(1), mod1(p)}, ip_pow1{mod1(1), mod1(p).inv()},
          p_pow2{mod2(1), mod2(p)}, ip_pow2{mod2(1), mod2(p).inv()}, v{0}, fac{1}, ifac{1} {}
    ~FactorInfo() = default;
    void preprocess(int n) {
      {
        int old_size = v.size();
        if (old_size < n) {
          v.resize(n);
          fac.resize(n);
          ifac.resize(n);
        }
        for (int i = old_size; i < n; ++i) {
          v[i]  = v[i - 1];
          int j = i;
          for (; j % p == 0; j /= p) ++v[i];
          fac[i]  = static_cast<u64>(fac[i - 1]) * j % pe;
          ifac[i] = inv_mod(fac[i], pe);
        }
      }
      {
        int old_size = p_pow1.size();
        if (old_size < n) {
          p_pow1.resize(n);
          ip_pow1.resize(n);
          p_pow2.resize(n);
          ip_pow2.resize(n);
        }
        for (int i = old_size; i < n; ++i) {
          p_pow1[i]  = p_pow1[i - 1] * p_pow1[1];
          ip_pow1[i] = ip_pow1[i - 1] * ip_pow1[1];
          p_pow2[i]  = p_pow2[i - 1] * p_pow2[1];
          ip_pow2[i] = ip_pow2[i - 1] * ip_pow2[1];
        }
      }
    }
  };

  template <typename Type>
  std::vector<Type> &shrink(std::vector<Type> &x) {
    Type ZERO(0);
    while (x.back() == ZERO) x.pop_back();
    if (x.empty()) x.emplace_back(ZERO);
    return x;
  }

  template <typename Type>
  std::vector<Type> binom_convolve(const std::vector<Type> &x, const std::vector<Type> &y) {
    int n = x.size(), m = y.size();
    std::vector<u32> x_cpy(n), y_cpy(m);
    for (int i = 0; i < n; ++i) x_cpy[i] = static_cast<u32>(x[i]);
    for (int i = 0; i < m; ++i) y_cpy[i] = static_cast<u32>(y[i]);
    int res_len = n + m - 1;
    u32 mod     = 1;
    std::vector<u32> res(res_len, 0);
    auto crt = [res_len](std::vector<u32> &x, u32 m, const std::vector<u32> &y, u32 m2) {
      u32 im1 = inv_mod(m, m2);
      for (int i = 0; i != res_len; ++i)
        x[i] += static_cast<u64>((y[i] + m2 - x[i] % m2) % m2) * im1 % m2 * m;
    };
    for (int i = 0, e = fact_.size(); i < e; ++i) {
      crt(res, mod, convolve(x_cpy, y_cpy, i), fact_[i].pe);
      mod *= fact_[i].pe;
    }
    return std::vector<Type>(res.begin(), res.end());
  }

  template <typename Type>
  std::vector<Type> binom_convolveT(const std::vector<Type> &x, const std::vector<Type> &y) {
    int n = x.size(), m = y.size();
    std::vector<u32> x_cpy(n), y_cpy(m);
    for (int i = 0; i < n; ++i) x_cpy[i] = static_cast<u32>(x[i]);
    for (int i = 0; i < m; ++i) y_cpy[i] = static_cast<u32>(y[i]);
    int res_len = n;
    u32 mod     = 1;
    std::vector<u32> res(res_len, 0);
    auto crt = [res_len](std::vector<u32> &x, u32 m, const std::vector<u32> &y, u32 m2) {
      u32 im1 = inv_mod(m, m2);
      for (int i = 0; i != res_len; ++i)
        x[i] += static_cast<u64>((y[i] + m2 - x[i] % m2) % m2) * im1 % m2 * m;
    };
    for (int i = 0, e = fact_.size(); i < e; ++i) {
      crt(res, mod, convolveT(x_cpy, y_cpy, i), fact_[i].pe);
      mod *= fact_[i].pe;
    }
    return std::vector<Type>(res.begin(), res.end());
  }

private:
  std::vector<FactorInfo> fact_;
  const u32 mod_;

  std::vector<u32> convolve(const std::vector<u32> &x, const std::vector<u32> &y, int idx) {
    int n = x.size(), m = y.size(), res_len = n + m - 1, len = get_ntt_len(res_len);
    fact_[idx].preprocess(res_len + 1);
    const auto &fact = fact_[idx];
    const auto pe    = fact.pe;
    std::vector<mod1> x1(len), y1(len);
    std::vector<mod2> x2(len), y2(len);
    for (int i = 0; i < n; ++i) {
      u64 x_hat = static_cast<u64>(x[i]) * fact.ifac[i] % pe;
      x1[i]     = x_hat * fact.ip_pow1[fact.v[i]];
      x2[i]     = x_hat * fact.ip_pow2[fact.v[i]];
    }
    for (int i = 0; i < m; ++i) {
      u64 y_hat = static_cast<u64>(y[i]) * fact.ifac[i] % pe;
      y1[i]     = y_hat * fact.ip_pow1[fact.v[i]];
      y2[i]     = y_hat * fact.ip_pow2[fact.v[i]];
    }
    std::fill(x1.begin() + n, x1.end(), mod1(0)), std::fill(y1.begin() + m, y1.end(), mod1(0)),
        std::fill(x2.begin() + n, x2.end(), mod2(0)), std::fill(y2.begin() + m, y2.end(), mod2(0));
    dft(x1), dft(y1), dft(x2), dft(y2);
    for (int i = 0; i != len; ++i) x1[i] *= y1[i], x2[i] *= y2[i];
    idft(x1), idft(x2);
    auto crt_mod_pe = [pe](mod1 x, mod2 y) -> u64 {
      static mod1 ip2(mod1(mod2::get_mod()).inv());
      static u64 p2_mod_pe = mod2::get_mod() % pe;
      u64 uy               = static_cast<u64>(y);
      return (static_cast<u64>((x - uy) * ip2) % pe * p2_mod_pe + uy) % pe;
    };
    std::vector<u32> res(res_len);
    for (int i = 0; i != res_len; ++i)
      res[i] = crt_mod_pe(x1[i] * fact.p_pow1[fact.v[i]], x2[i] * fact.p_pow2[fact.v[i]]) *
               fact.fac[i] % pe;
    return res;
  }

  std::vector<u32> convolveT(const std::vector<u32> &x, const std::vector<u32> &y, int idx) {
    int n = x.size(), m = y.size(), res_len = n, len = get_ntt_len(n + m - 1);
    assert(m >= n);
    fact_[idx].preprocess(n + 1);
    const auto &fact = fact_[idx];
    const auto pe    = fact.pe;
    std::vector<mod1> x1(len), y1(len);
    std::vector<mod2> x2(len), y2(len);
    for (int i = 0; i < n; ++i) {
      u64 x_hat     = static_cast<u64>(x[i]) * fact.fac[i] % pe;
      x1[n - 1 - i] = x_hat * fact.p_pow1[fact.v[i]];
      x2[n - 1 - i] = x_hat * fact.p_pow2[fact.v[i]];
    }
    for (int i = 0; i < m; ++i) {
      u64 y_hat = static_cast<u64>(y[i]) * fact.ifac[i] % pe;
      y1[i]     = y_hat * fact.ip_pow1[fact.v[i]];
      y2[i]     = y_hat * fact.ip_pow2[fact.v[i]];
    }
    std::fill(x1.begin() + n, x1.end(), mod1(0)), std::fill(y1.begin() + m, y1.end(), mod1(0)),
        std::fill(x2.begin() + n, x2.end(), mod2(0)), std::fill(y2.begin() + m, y2.end(), mod2(0));
    dft(x1), dft(y1), dft(x2), dft(y2);
    for (int i = 0; i != len; ++i) x1[i] *= y1[i], x2[i] *= y2[i];
    idft(x1), idft(x2);
    auto crt_mod_pe = [pe](mod1 x, mod2 y) -> u64 {
      static mod1 ip2(mod1(mod2::get_mod()).inv());
      static u64 p2_mod_pe = mod2::get_mod() % pe;
      u64 uy               = static_cast<u64>(y);
      return (static_cast<u64>((x - uy) * ip2) % pe * p2_mod_pe + uy) % pe;
    };
    std::vector<u32> res(res_len);
    for (int i = 0; i != res_len; ++i)
      res[i] = crt_mod_pe(x1[res_len - 1 - i] * fact.ip_pow1[fact.v[i]],
                          x2[res_len - 1 - i] * fact.ip_pow2[fact.v[i]]) *
               fact.ifac[i] % pe;
    return res;
  }
};

using EGF = ExponentialGeneratingFunction;

} // namespace lib

#endif