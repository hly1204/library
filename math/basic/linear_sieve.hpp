#ifndef LINEAR_SIEVE_HEADER_HPP
#define LINEAR_SIEVE_HEADER_HPP

/**
 * @brief linear sieve / 线性筛法
 *
 */

#include <vector>

namespace lib {

/**
 * @brief 获取 [0, n) 的素数表
 *
 * @param n
 * @return std::vector<int>
 */
std::vector<int> prime_table(int n) {
  std::vector<bool> is_comp(n, false);
  std::vector<int> res;
  for (int i = 2; i < n; ++i) {
    if (!is_comp[i]) res.push_back(i);
    // 令合数 q=ip 其中 p 为最小的素因子且 i>=p 这些 p 已经记录在 res 中，
    // 我们令小于 i 的任何素数都不能整除 i 这样就保证了 p 是 q 最小的素因子， q 只会被筛去一次
    for (int j = 0, je = res.size(); j < je && i * res[j] < n; ++j) {
      is_comp[i * res[j]] = true;
      if (i % res[j] == 0) break;
    }
  }
  return res;
}

} // namespace lib

#endif