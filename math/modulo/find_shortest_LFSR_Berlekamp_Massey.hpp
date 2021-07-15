#ifndef FIND_SHORTEST_LFSR_BERLEKAMP_MASSEY_HEADER_HPP
#define FIND_SHORTEST_LFSR_BERLEKAMP_MASSEY_HEADER_HPP

/**
 * @brief find shortest LFSR Berlekamp-Massey / 寻找最短线性递推 Berlekamp-Massey 算法
 * @docs docs/math/modulo/find_shortest_LFSR_Berlekamp_Massey.md
 */

#include <numeric>
#include <utility>
#include <vector>

namespace lib {

/**
 * @brief 寻找最短 LFSR （但仅当 L*2 <= N 时唯一）
 * @ref J.L. Massey, Shift register synthesis and BCH decoding,
 *      IEEE Trans. Inform. Theory, vol. IT-15, 122–127 (1969).
 * @tparam mod_t 有除法，必须为域
 * @param s s_0, s_1, …, s_{n-1}
 * @return std::vector<mod_t> C(x)=1+c_{1}*x+c_{2}*x^{2}+ … +c_{L}*x^{L}
 *         对于所有 i>=L 和 s = s_0, s_1, …, s_{L-1}
 *         满足 s_{i} + c_{1}*s_{i-1} + c_{2}*s_{i-2} + … + c_{L}*s_{i-L} = 0
 */
template <typename mod_t>
std::vector<mod_t> find_LFSR(const std::vector<mod_t> &s) {
  const mod_t ZERO(0);
  std::vector<mod_t> C{mod_t(1)}, B(C);
  mod_t b(1);
  for (int N = 0, n = s.size(), L = 0, x = 1; N < n; ++N) {
    mod_t d(s[N]);
    for (int i = 1; i <= L; ++i) d += C[i] * s[N - i];
    if (d == ZERO) {
      ++x;
    } else if ((L << 1) > N) {
      // C(D)=C(D)-d/bD^xB(D)
      if (C.size() < B.size() + x) C.resize(B.size() + x, ZERO);
      mod_t coef = d / b;
      for (int i = x, ie = B.size() + x; i < ie; ++i) C[i] -= coef * B[i - x];
      ++x;
    } else {
      std::vector<mod_t> T(C); // 记录 next discrepancy
      // C(D)=C(D)-d/bD^xB(D)
      if (C.size() < B.size() + x) C.resize(B.size() + x, ZERO);
      mod_t coef = d / b;
      for (int i = x, ie = B.size() + x; i < ie; ++i) C[i] -= coef * B[i - x];
      L = N + 1 - L, B = std::move(T), b = d, x = 1;
    }
  }
  return C;
}

} // namespace lib

#endif