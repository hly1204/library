#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <cstdint>
#include <iostream>
#include <vector>

#include "math/formal_power_series/radix_4_NTT.hpp"
#include "modint/long_Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using u64                      = std::uint64_t;
  constexpr u64 M1               = 0x3f9a000000000001;
  constexpr u64 M2               = 0x3fc6000000000001;
  constexpr auto mod             = UINT32_C(1000000007);
  using mint1                    = lib::LongMontModInt<M1>;
  using mint2                    = lib::LongMontModInt<M2>;
  constexpr mint2 IM1            = mint2(M1).inv();
  constexpr decltype(mod) M1_mod = static_cast<decltype(mod)>(M1 % mod);
  int n, m;
  std::cin >> n >> m;
  std::vector<int> A(n), B(m);
  for (auto &i : A) std::cin >> i;
  for (auto &i : B) std::cin >> i;
  int res_len = n + m - 1;
  int ntt_len = 1;
  while (ntt_len < res_len) ntt_len <<= 1;
  std::vector<mint1> A1(A.begin(), A.end()), B1(B.begin(), B.end());
  std::vector<mint2> A2(A.begin(), A.end()), B2(B.begin(), B.end());
  A1.resize(ntt_len, mint1(0));
  B1.resize(ntt_len, mint1(0));
  A2.resize(ntt_len, mint2(0));
  B2.resize(ntt_len, mint2(0));
  lib::NTT4<mint1>::dft(ntt_len, A1.data());
  lib::NTT4<mint1>::dft(ntt_len, B1.data());
  lib::NTT4<mint2>::dft(ntt_len, A2.data());
  lib::NTT4<mint2>::dft(ntt_len, B2.data());
  for (int i = 0; i < ntt_len; ++i) A1[i] *= B1[i], A2[i] *= B2[i];
  lib::NTT4<mint1>::idft(ntt_len, A1.data());
  lib::NTT4<mint2>::idft(ntt_len, A2.data());
  for (int i = 0; i < res_len; ++i)
    std::cout << static_cast<decltype(mod)>(
                     (static_cast<u64>(A1[i]) +
                      static_cast<u64>((A2[i] - static_cast<u64>(A1[i])) * IM1) % mod * M1_mod) %
                     mod)
              << ' ';
  return 0;
}