#ifndef LINEARLY_RECURRENT_SEQUENCE_BOSTAN_MORI_HEADER_HPP
#define LINEARLY_RECURRENT_SEQUENCE_BOSTAN_MORI_HEADER_HPP

/**
 * @brief linearly recurrent sequence Bostan-Mori / 常系数线性递推序列 Bostan-Mori 算法
 *
 */

#include <numeric>

#include "radix_2_NTT.hpp"

namespace lib {

template <typename mod_t>
class LinearlyRecurrentSequence {
public:
  /**
   * @brief 线性递推序列
   * @param rec_seq 递推式 rec_seq = {c_0, c_1, c_2, ..., c_{d-1}}
   * @param init_val 初值 init_val = {u_0, u_1, u_2, ..., u_{d-1}}
   * @note d 阶的递推 u_d = c_0u_0 + c_1u_1 + ... + c_{d-1}u_{d-1}
   */
  LinearlyRecurrentSequence(const std::vector<mod_t> &rec_seq, const std::vector<mod_t> &init_val)
      : p_(init_val) {
    int d = rec_seq.size();
    q_.resize(d + 1);
    q_[0] = 1;
    for (int i = 1; i <= d; ++i) q_[i] = -rec_seq[d - i];
    // q_ = 1 - c_{d-1}x - c_{d-2}x^2 - ... - c_0x^d
    std::vector<mod_t> q_cpy(q_);
    int len = get_ntt_len((d << 1) + 1);
    q_cpy.resize(len, mod_t(0));
    p_.resize(len, mod_t(0));
    dft(q_cpy), dft(p_);
    for (int i = 0; i != len; ++i) p_[i] *= q_cpy[i];
    idft(p_);
    p_.resize(d);
  }
  ~LinearlyRecurrentSequence() = default;

  /**
   * @brief 幂级数展开的第 n 项
   * @param n
   * @return mod_t [x^n]p(x)/q(x)
   */
  mod_t operator[](unsigned long long n) const {
    if (n == 0) return p_[0];
    std::vector<mod_t> p_cpy(p_), q_cpy(q_);
    int len = get_ntt_len((q_cpy.size() << 1) - 1);
    p_cpy.resize(len, mod_t(0));
    q_cpy.resize(len, mod_t(0));
    dft(p_cpy), dft(q_cpy);
    for (;; n >>= 1) {                                         // p(x)/q(x) = p(x)q(-x)/(q(x)q(-x))
      for (int i = 0; i != len; ++i) p_cpy[i] *= q_cpy[i ^ 1]; // p(x)q(-x) 分子
      if (n & 1) NTT<mod_t>::odd_dft(len, p_cpy.data());       // 长度会变为原先的一半
      else
        NTT<mod_t>::even_dft(len, p_cpy.data());
      for (int i = 0; i != len; i += 2) q_cpy[i] = q_cpy[i + 1] = q_cpy[i] * q_cpy[i + 1];
      NTT<mod_t>::even_dft(len, q_cpy.data());
      if (n == 1) // [x^0](q(x)q(-x))=1 ，使用第一种类型的 accumulate 即从左开始 fold 并累加答案
        return std::accumulate(p_cpy.begin(), p_cpy.begin() + (len >> 1), mod_t(0)) /
               mod_t(len >> 1);
      // 若要实现任意模数，我们在用 3 模数的同时，在 dft_doubling 的时候用 CRT
      // 合并出当前准确的值即可，而不用去浪费时间真的做完整的乘法
      NTT<mod_t>::dft_doubling(len >> 1, q_cpy.data());
      NTT<mod_t>::dft_doubling(len >> 1, p_cpy.data());
    }
  }

private:
  std::vector<mod_t> p_, q_; // p(x)/q(x)
};

} // namespace lib

#endif