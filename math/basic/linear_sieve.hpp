#ifndef LINEAR_SIEVE_HEADER_HPP
#define LINEAR_SIEVE_HEADER_HPP

#include <vector>

namespace lib {

// 获取 [0, n) 的素数表
std::vector<int> prime_table(int n) {
  // 令合数 q=ip 其中 p 为最小的素因子且 i>=p 这些 p 已经记录在 res 中，
  // 令小于 i 的任何素数都不能整除 i 这样就保证了 p 是 q 最小的素因子， q 只会被筛去一次
  std::vector<bool> is_comp(n, false);
  std::vector<int> res;
  for (int i = 2; i < n; ++i) {
    if (!is_comp[i]) res.push_back(i);
    for (int j = 0, je = res.size(); j < je && i * res[j] < n; ++j) {
      is_comp[i * res[j]] = true;
      if (i % res[j] == 0) break;
    }
  }
  return res;
}

} // namespace lib

#endif