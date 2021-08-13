#ifndef PARTITION_FUNCTION_P_HEADER_HPP
#define PARTITION_FUNCTION_P_HEADER_HPP

/**
 * @brief partition function P / 分拆数 P
 *
 */

namespace lib {

/**
 * @brief 前 n 个分拆数
 * @see http://oeis.org/A000041
 * @see https://mathworld.wolfram.com/PartitionFunctionP.html
 */
template <typename PolyType>
void partition_function_P(int n, PolyType &res) {
  if (n == 0) {
    res = PolyType{};
    return;
  }
  PolyType t(n, 0);
  t[0] = 1;
  for (int i = 1, k = 1;; ++i) {
    long long t0 = i * (3LL * i - 1) / 2;
    long long t1 = -i * (-3LL * i - 1) / 2;
    if (t0 >= n) break;
    t[t0] = ((++k) & 2) ? -1 : 1;
    if (t1 >= n) break;
    t[t1] = ((++k) & 2) ? -1 : 1;
  }
  res = t.inv(n);
}

} // namespace lib

#endif