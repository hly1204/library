#ifndef Z_ALGORITHM_HEADER_HPP
#define Z_ALGORITHM_HEADER_HPP

/**
 * @brief Z algorithm
 *
 */

#include <algorithm>
#include <vector>

namespace lib {

/**
 * @brief 获取 z 数组
 * @note z[i] 为 s 从 i 开始的后缀与 s 的最长公共前缀的长度
 * @tparam Container 容器
 * @param s 字符串
 * @return std::vector<int>
 */
template <typename Container>
std::vector<int> get_z(const Container &s) {
  int n = s.size();
  std::vector<int> z(n, 0);
  if (n == 0) return z;
  z[0] = n;
  // Z-box 即 s[l..r]=s[0..r-l+1]
  // 我们维护 r 最右的 Z-box
  // 当当前索引 i 在 Z-box 中时，可以利用前面计算完毕的 z[i-l] 值来扩展
  // 但是注意，若 l+z[i-l] > r 了，也必须从 Z-box 的 r 开始扩展，因为后面的字符压根没有扫描到！
  // 若 z[i-l] 的 Z-box 的 r 没有当前的 r 大，其实不用再扩展了，这里没有显式写出
  for (int i = 1, l = 0, r = 0; i != n; ++i) {
    if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
    while (z[i] + i < n && s[z[i]] == s[z[i] + i]) ++z[i];
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}

} // namespace lib

#endif