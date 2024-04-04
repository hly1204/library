#ifndef ENUM_KTH_TERM_OF_POWER_HPP
#define ENUM_KTH_TERM_OF_POWER_HPP

#include "../common.hpp"
#include "truncated_formal_power_series.hpp"

#include <algorithm>
#include <utility>
#include <vector>

LIB_BEGIN

// returns [x^k]g(x), [x^k]g(x)f(x), ..., [x^k]g(x)f(x)^(n-1)
// [x^k](g(x)/(1-yf(x)))
// reference: noshi91's blog: https://noshi91.hatenablog.com/entry/2024/03/16/224034
template <typename ModIntT>
lib::tfps<ModIntT> enum_kth_term_of_power(const tfps<ModIntT> &f, const tfps<ModIntT> &g, int k,
                                          int n) {
  if (k < 0 || n <= 0) return {};
  lib::tfps<ModIntT> P(k + 1), Q((k + 1) << 1);
  std::copy_n(g.cbegin(), std::min(P.size(), g.size()), P.begin());
  Q.front() = ModIntT(1);
  if (const int s = static_cast<int>(f.size()))
    for (int i = k + 1, j = 0; j != s && i != (k + 1) << 1;) Q[i++] = -f[j++];

  auto get_root_div_2 = [](int n) -> decltype(auto) {
    // modified from idft
    static std::vector<ModIntT> root = {ModIntT(2).inv()};
    static constexpr auto rt         = detail::iroot<ModIntT>();
    if (int s = static_cast<int>(root.size()); s < n) {
      root.resize(n);
      for (int i = detail::bsf(s), j; 1 << i < n; ++i) {
        root[j = 1 << i] = rt[i];
        for (int k = j + 1; k < j << 1; ++k) root[k] = root[k - j] * root[j];
        root[j] *= root.front();
      }
    }
    return (root);
  };

  for (int d = 1; k != 0; d <<= 1, k >>= 1) {
    const int len = ntt_len((d << 1 | 1) * ((k + 1) << 1) - 1);
    lib::tfps<ModIntT> dftP(len), dftQ(len), U(len >> 1), V(len >> 1);
    for (int i = 0; i != d; ++i)
      std::copy_n(P.cbegin() + i * (k + 1), k + 1, dftP.begin() + i * ((k + 1) << 1));
    for (int i = 0; i <= d; ++i)
      std::copy_n(Q.cbegin() + i * (k + 1), k + 1, dftQ.begin() + i * ((k + 1) << 1));
    dft(dftP);
    dft(dftQ);
    // apply dft trick from Bostan&Mori's paper
    if (k & 1) {
      auto &&root = get_root_div_2(len >> 1);
      for (int i = 0; i != len; i += 2) {
        U[i >> 1] = (dftP[i] * dftQ[i + 1] - dftP[i + 1] * dftQ[i]) * root[i >> 1];
        V[i >> 1] = dftQ[i] * dftQ[i + 1];
      }
    } else {
      auto &&root = get_root_div_2(1);
      for (int i = 0; i != len; i += 2) {
        U[i >> 1] = (dftP[i] * dftQ[i + 1] + dftP[i + 1] * dftQ[i]) * root.front();
        V[i >> 1] = dftQ[i] * dftQ[i + 1];
      }
    }
    idft(U);
    idft(V);
    P.assign((d << 1) * ((k >> 1) + 1), ModIntT());
    for (int i = 0; i != d << 1; ++i)
      std::copy_n(U.cbegin() + (i * (k + 1)), (k >> 1) + 1, P.begin() + (i * ((k >> 1) + 1)));
    Q.assign((d << 1 | 1) * ((k >> 1) + 1), ModIntT());
    for (int i = 0; i <= d << 1; ++i)
      std::copy_n(V.cbegin() + (i * (k + 1)), (k >> 1) + 1, Q.begin() + (i * ((k >> 1) + 1)));
  }

  return P.div(Q, n);
}

// returns [y^k](g(y)/1-yf(x)) = [y^k](1 + g(y)yf(x) + g(y)y^2f(x)^2 + ...)
// reference: noshi91's blog: https://noshi91.hatenablog.com/entry/2024/03/16/224034
template <typename ModIntT>
lib::tfps<ModIntT> kth_term(const tfps<ModIntT> &f, const tfps<ModIntT> &g, int k, int n) {
  if (k < 0 || n <= 0) return {};
  // returns [y^0](g(y^(-1))/1-yf(x))
  struct coeff_of_y0_rec {
    coeff_of_y0_rec(tfps<ModIntT> &&P, int k) : P_(std::move(P)), k_(k) {}
    tfps<ModIntT> run(const tfps<ModIntT> Q, int d, int n) {
      // [0,n] => [y^(-d+1)]Q, [n+1,2n+1] => [y^(-1)]Q, ..., [y^0]Q
      if (d > k_ && n == 0) {
        // [-d+1,0] => [0,d-1]
        tfps<ModIntT> res(d);
        std::copy_n(P_.cbegin(), std::min(P_.size(), res.size()), res.rbegin());
        return res.div(Q, d);
      }
      // let y=x^(2n+2) => [0,2n+2) = [y^0]Q, ...
      // y^0[0,2n+2), y^1[2n+2,4n+4), ..., y^(2d)[2d(2n+2),(2d+1)(2n+2)-1)
      const int len = ntt_len((d << 1 | 1) * ((n + 1) << 1) - 1);
      tfps<ModIntT> dftQ(len), VV(len >> 1), V((d << 1 | 1) * ((n >> 1) + 1));
      for (int i = 0; i <= d; ++i)
        std::copy_n(Q.cbegin() + i * (n + 1), n + 1, dftQ.begin() + i * ((n + 1) << 1));
      dft(dftQ);
      // apply dft trick from Bostan&Mori's paper
      for (int i = 0; i != len; i += 2) VV[i >> 1] = dftQ[i] * dftQ[i + 1];
      idft(VV);
      for (int i = 0; i <= d << 1; ++i)
        std::copy_n(VV.cbegin() + i * (n + 1), (n >> 1) + 1, V.begin() + i * ((n >> 1) + 1));
      const auto TT = run(std::move(V), d << 1, n >> 1);
      VV.assign(len >> 1, ModIntT());
      for (int i = 0; i != d << 1; ++i)
        std::copy_n(TT.cbegin() + i * ((n >> 1) + 1), (n >> 1) + 1, VV.begin() + i * (n + 1));
      dft(VV);
      auto &&T = dftQ;
      // apply dft trick from Bostan&Mori's paper
      for (int i = 0; i != len; i += 2) {
        auto l = VV[i >> 1] * dftQ[i + 1], r = VV[i >> 1] * dftQ[i];
        T[i] = l, T[i + 1] = r;
      }
      idft(T);
      auto &&U = VV;
      U.assign(d * (n + 1), ModIntT());
      // [y^(-d+1..0)]T => [y^(d..2d-1)]T
      for (int i = 0; i != d; ++i)
        std::copy_n(T.cbegin() + (i + d) * ((n + 1) << 1), n + 1, U.begin() + i * (n + 1));
      return U;
    }

  private:
    const tfps<ModIntT> P_;
    const int k_;
  };

  // [y^k](g(y)/1-yf(x)) => [y^0](y^(-k)g(y)/1-yf(x))
  tfps<ModIntT> P(k + 1), Q(n << 1); // [0,n)=1, [n,2n)=-g
  std::copy_n(g.cbegin(), std::min(P.size(), g.size()), P.rbegin());
  Q.front() = ModIntT(1);
  if (const int s = static_cast<int>(f.size()))
    for (int i = n, j = 0; j != s && i != n << 1;) Q[i++] = -f[j++];
  return coeff_of_y0_rec(std::move(P), k).run(std::move(Q), 1, n - 1);
}

LIB_END

#endif
