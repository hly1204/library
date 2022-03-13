#ifndef DISCRETE_LOG_BSGS_HEADER_HPP
#define DISCRETE_LOG_BSGS_HEADER_HPP

#include <cmath>
#include <numeric>
#include <unordered_map>

namespace lib {

// 离散对数，计算最小的 x 满足 a^x=b (mod m) ，若无解则返回 -1
// 参见：https://cp-algorithms.com/algebra/discrete-log.html
int discrete_log(int a, int b, int m) {
  a %= m, b %= m;
  int add = 0, k = 1, g;
  while ((g = std::gcd(a, m)) > 1) {
    if (b == k) return add; // 包含了 a=0 且 b=1 的情况
    if (b % g != 0) return -1;
    b /= g, m /= g, ++add;
    k = static_cast<long long>(k) * (a / g) % m;
  }
  int n  = static_cast<int>(std::ceil(std::sqrt(m)));
  int an = 1;
  for (int i = 0; i != n; ++i) an = static_cast<long long>(an) * a % m;
  std::unordered_map<int, int> mp;
  for (int q = 0; q <= n; ++q, b = static_cast<long long>(b) * a % m) mp[b] = q;
  for (int p = 1, cur = k; p <= n; ++p)
    if (mp.find(cur = static_cast<long long>(cur) * an % m) != mp.end())
      return n * p - mp[cur] + add;
  return -1;
}

} // namespace lib

#endif