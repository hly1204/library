#ifndef Z_ALGORITHM_HEADER_HPP
#define Z_ALGORITHM_HEADER_HPP

#include <algorithm>
#include <vector>

namespace lib {

template <typename Container>
std::vector<int> get_z(const Container &s) {
  int n = s.size();
  std::vector<int> z(n, 0);
  if (n == 0) return z;
  z[0] = n;
  for (int i = 1, l = 0, r = 0; i != n; ++i) {
    if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
    while (z[i] + i < n && s[z[i]] == s[z[i] + i]) ++z[i];
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}

} // namespace lib

#endif