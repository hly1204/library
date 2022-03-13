#ifndef BURROWS_WHEELER_TRANSFORMATION_HEADER_HPP
#define BURROWS_WHEELER_TRANSFORMATION_HEADER_HPP

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include "suffix_array_sais.hpp"

namespace lib {

// 获取 BWT 数组（字符串）
template <typename Container>
Container bwt(const Container &v, const std::vector<int> &SA) {
  int n = v.size();
  Container res;
  res.resize(n + 1);
  for (int i = 0; i < n; ++i) res[i + 1] = SA[i] != 0 ? v[SA[i] - 1] : 0;
  res[0] = v.back();
  return res;
}

// 获取 BWT 数组（字符串）
// v 字符串数组，必须保证 0 是未出现的最小值
template <typename Container>
Container bwt(const Container &v) {
  return bwt(v, get_sa(v));
}

// 参见：M. Burrows and D. J. Wheeler. A block-sorting lossless data compression algorithm.
//      Technical Report 124, Digital Equipment Corporation, Palo Alto, California, 1994.
template <typename Container>
Container ibwt(const Container &v) {
  int n = v.size();
  int K = *std::max_element(v.begin(), v.end()) + 1;
  Container res;
  res.resize(n); // 为了 std::string 特殊处理
  // C[i] 为字符 i 出现的次数， P[i] 为 v[i] 在前缀中出现的次数（不包含）
  std::vector<int> C(K, 0), P(n, 0);
  int I = -1; // 记录终止符号位置
  for (int i = 0; i < n; ++i) {
    P[i] = C[v[i]]++;
    if (v[i] == 0) I = i;
  }
  assert(I != -1);
  for (int i = 0, sum = 0; i < K; ++i) sum += C[i], C[i] = sum - C[i];
  for (int i = I, j = n - 1; j >= 0; --j) res[j] = v[i], i = P[i] + C[v[i]];
  res.pop_back();
  return res;
}

// 从 BWT 数组计算原数组（字符串）的特化
template <>
std::string ibwt<std::string>(const std::string &v) {
  int n = v.size();
  std::string res;
  res.resize(n);
  // C[i] 为字符 i 出现的次数， P[i] 为 v[i] 在前缀中出现的次数（不包含）
  std::vector<int> C(128, 0), P(n, 0);
  int I = -1; // 记录终止符号位置
  for (int i = 0; i < n; ++i) {
    P[i] = C[v[i]]++;
    if (v[i] == 0) I = i;
  }
  assert(I != -1);
  for (int i = 0, sum = 0; i < 128; ++i) sum += C[i], C[i] = sum - C[i];
  for (int i = I, j = n - 1; j >= 0; --j) res[j] = v[i], i = P[i] + C[v[i]];
  res.pop_back();
  return res;
}

} // namespace lib

#endif