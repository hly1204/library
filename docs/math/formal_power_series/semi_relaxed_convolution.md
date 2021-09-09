## 半在线卷积

我们使用 $R(n)$ 和 $Q(n)$ 分别表示 $n$ 长在线和半在线卷积的时间，且只考虑在 $\mathbb{F} _ p\lbrack x\rbrack$ 中的多项式。在 Hoeven 论文中提到我们只需倍增的进行半在线卷积即可得到在线卷积，有

$$
R(n)=R(n/2)+2Q(n)+M(n)
$$

其中 $M(n)$ 表示离线的 $n$ 长卷积的时间，一般可以 NTT/FFT 时 $M(n)=\Theta(n\log n)$ 与牛顿法的时间计算方法类似，我们有

$$
R(n)=O(Q(n))
$$

也就是只需要考虑快速的半在线算法即可得到一个同样时间的在线算法，这并不复杂。

在 EI 的讲课视频中提到，如果我们使用 $B$ 叉分治，那么有

$$
T(n)=B\cdot T(n/B)+B\cdot M(n/B)+B\cdot n
$$

第二项为计算 $B$ 块 $n/B$ 大小的 FFT/NTT 的时间，注意逆变换也同样需要这么多次，那么常数我们忽略。而第三项为朴素计算 FFT/NTT block 之间乘法的时间，有 $B$ 块所以需要 $B^2$ 次块与块之间的乘法（ Hadamard 积），那么 $B^2\cdot \frac{n}{B}=n\cdot B$ 。如果我们取 $B=\log n$ 那么

$$
\begin{aligned}
T(n)&=T\left(\frac{n}{\log n}\right)\cdot \log n+n\log n\\
&\leq 2T(n/2)+n\log n
\end{aligned}
$$

显然是比分治 FFT 的 $\Theta(n\log ^2n)$ 快的，但我不会算（或许是考虑递归树的树高？如果只考虑这一点的话，我们可以令 $T(n)=T(n/\log n)+1$ 如同 [stackoverflow](https://stackoverflow.com/questions/30826040/calculating-the-recurrence-relation-tn-tn-log-n-%CE%981/) 提到的一样，这个解为 $T(n)=\Theta(\log n/\log \log n)$ 但是证明需要用另一个上界来等价替换），参考文献三和四给出了这个时间。在 Hoeven 的论文中给出了另外的时间和证明。

但是我们在实现时一般也不取 $B=\log n$ 而是近似的 $B\in\lbrace 4,8,16,32\rbrace$ 。

**补充**：对于二叉分治半在线卷积有

$$
\begin{aligned}
T(n)&=2\cdot T\left(\frac{n}{2}\right)+n\log n \\
&=\sum _ {i=0}^{\log n}n\log \frac{n}{2^i} \\
&=n\log \left(\prod _ {i=0}^{\log n}\frac{n}{2^i}\right),\quad \left(\because \log_aA+\log_aB=\log_{a}(AB)\right) \\
&=n\log \left(\frac{n^{\log n}}{2^{((1+\log n)\log n)/2}}\right) \\
&=n\log n\cdot \log\left(\frac{n}{2^{(1+\log n)/2}}\right),\quad \left(\because \log_aA^b=b\log_aA\right) \\
&=n\log n\cdot \log\left(\frac{n}{\sqrt{2}\cdot \sqrt{n}}\right) \\
&=\Theta(n\log ^2n),\quad \left(\because \log\left(\frac{n}{\sqrt{2}\sqrt{n}}\right)=\frac{1}{2}\log\left(\frac{n}{2}\right)=\frac{1}{2}(\log n-\log 2)=\Theta(\log n)\right)
\end{aligned}
$$

另外注意对于半在线卷积，一般也都是计算截断前 $n$ 项的，也就是只需计算下三角形的贡献，但是在线卷积就需要计算完整的正方形的贡献。

**笔记**：注意参考文献的最后一篇论文，我们在使用二叉分治半在线卷积时可以利用 middle product 的技巧减少常数，在这里多叉分治也可以应用，具体的我们对于每一次的递归只处理下三角形的贡献，然后使用 middle product 补充缺失的部分，最后仍计算了下三角形的贡献，这种方法易修改为迭代的。若不使用 middle product 亦不会显著增加处理 DFT 的时间，但会消耗更多加法与乘法的时间和更精细的实现，虽然我实现了但代码已经弃用，注释在下面。

```cpp
#ifndef SEMI_RELAXED_CONVOLUTION_HEADER_HPP
#define SEMI_RELAXED_CONVOLUTION_HEADER_HPP

/**
 * @brief semi-relaxed convolution
 * @docs docs/math/formal_power_series/semi_relaxed_convolution.md
 */

#include <algorithm>
#include <functional>
#include <vector>

#include "radix_2_NTT.hpp"

namespace lib {

/**
 * @note 在计算完下三角形的贡献后，上三角形的贡献累积入同一个 level 的数组即变量 level_dft_sum_cache 后
 *       将 idft 交给下一次去计算，如此获得了使用 middle product 技巧差不多的 dft 长度和次数。
 *       但这个实现的乘法和加法次数是冗余更多的！若不使用上述技巧则会使得 idft 次数多出一半。
 */
template <typename mod_t, typename HandleFuncType>
std::vector<mod_t> semi_relaxed_convolve(int n, const std::vector<mod_t> &A, std::vector<mod_t> &B,
                                         HandleFuncType &&relax) {
  int g_len = get_ntt_len(n);
  std::vector<mod_t> contribution(g_len << 1, mod_t(0)), A_cpy(A);
  std::vector<std::vector<std::vector<mod_t>>> dft_A_cache, level_dft_sum_cache;
  A_cpy.resize(g_len, mod_t(0));
  B.resize(g_len, mod_t(0));

  constexpr int THRESHOLD = 32;
  /**
   * @brief 计算 A[0,g_len) * B[l,r) 的贡献
   * @note 为了能计算幂级数倒数等，需要在获取句柄前先计算完对角线上的贡献
   */
  std::function<void(int, int, int)> run_rec = [&](int l, int r, int lv) {
    int len = r - l;
    if (r - l <= THRESHOLD) {
      for (int i = 0; i < len; ++i) {
        for (int j = 1; j <= i; ++j) contribution[i + l] += A_cpy[j] * B[i + l - j];
        if (i + l < n) contribution[i + l] += A_cpy[0] * (B[i + l] = relax(i + l, contribution));
      }
      if (r != g_len)
        for (int i = len; i < (len << 1) - 1; ++i)
          for (int j = i + 1 - len; j < len; ++j) contribution[i + l] += A_cpy[j] * B[i + l - j];
      return;
    }
    const int block = 16, block_size = len >> 4;
    if (l == 0) {
      auto &dft_block = dft_A_cache.emplace_back();
      for (int i = 1; i < block; ++i) {
        dft_block.emplace_back(A_cpy.begin() + i * block_size, A_cpy.begin() + (i + 1) * block_size)
            .resize(block_size << 1, mod_t(0));
        dft(dft_block.back());
      }
      level_dft_sum_cache.emplace_back(
          std::vector<std::vector<mod_t>>(block, std::vector<mod_t>(block_size << 1, mod_t(0))));
    } else {
      idft(level_dft_sum_cache[lv][0]);
      for (int i = 0; i != (block_size << 1) - 1; ++i)
        contribution[l + i] += level_dft_sum_cache[lv][0][i];
      std::fill_n(level_dft_sum_cache[lv].back().begin(), block_size << 1, mod_t(0));
    }
    std::vector<std::vector<mod_t>> dft_B_cache;
    for (int i = 0; i < block; ++i) {
      run_rec(l + i * block_size, l + (i + 1) * block_size, lv + 1);
      if (r == g_len && i == block - 1) return;
      dft_B_cache.emplace_back(B.begin() + l + i * block_size, B.begin() + l + (i + 1) * block_size)
          .resize(block_size << 1, mod_t(0));
      dft(dft_B_cache.back());
      if (i != block - 1) {
        std::vector<mod_t> &sum_temp = level_dft_sum_cache[lv][i + 1];
        for (int j = 0; j <= i; ++j)
          for (int k = 0; k != block_size << 1; ++k)
            sum_temp[k] += dft_A_cache[lv][i - j][k] * dft_B_cache[j][k];
        idft(sum_temp);
        for (int j = 0, offset = l + (i + 1) * block_size; j != (block_size << 1) - 1; ++j)
          contribution[offset + j] += sum_temp[j];
      }
    }
    for (int i = block; i < (block << 1) - 1; ++i) {
      std::vector<mod_t> &sum_temp = level_dft_sum_cache[lv][i - block];
      std::fill_n(sum_temp.begin(), block_size << 1, mod_t(0));
      for (int j = i + 1 - block; j < block; ++j)
        for (int k = 0; k != block_size << 1; ++k)
          sum_temp[k] += dft_A_cache[lv][i - 1 - j][k] * dft_B_cache[j][k];
    }
  };
  run_rec(0, g_len, 0);
  contribution.resize(n);
  B.resize(n);
  return contribution;
}

} // namespace lib


#endif
```

现在我已经将整个算法改写为迭代。

## 半在线卷积完成幂级数的基本操作

给出部分代码片段。

```cpp
#include <vector>

#include "math/formal_power_series/prime_binomial.hpp"
#include "math/formal_power_series/semi_relaxed_convolution.hpp"

template <typename mod_t>
std::vector<mod_t> fps_inv(int n, const std::vector<mod_t> &x) {
  std::vector<mod_t> res;
  mod_t iv = mod_t(1) / x[0];
  lib::SemiRelaxedConvolution<mod_t> rc(
      x, res, [&iv](int idx, const std::vector<mod_t> &c) { return idx == 0 ? iv : -c[idx] * iv; });
  while (n--) rc.next();
  return res;
}

template <typename mod_t>
std::vector<mod_t> fps_deriv(const std::vector<mod_t> &x) {
  int n = x.size();
  if (n <= 1) return std::vector<mod_t>(1, mod_t(0));
  std::vector<mod_t> res(n - 1);
  for (int i = 1; i < n; ++i) res[i - 1] = x[i] * mod_t(i);
  return res;
}

template <typename mod_t>
std::vector<mod_t> fps_integral(const std::vector<mod_t> &x, mod_t c = mod_t(0)) {
  int n = x.size();
  std::vector<mod_t> res(n + 1);
  res[0] = c;
  lib::PrimeBinomial<mod_t> bi(n + 1);
  for (int i = 1; i <= n; ++i) res[i] = x[i - 1] * bi.inv_unsafe(i);
  return res;
}

template <typename mod_t>
std::vector<mod_t> fps_exp(int n, const std::vector<mod_t> &x) {
  std::vector<mod_t> x_cpy(x), res;
  lib::PrimeBinomial<mod_t> bi(n);
  lib::SemiRelaxedConvolution<mod_t> rc(
      fps_deriv(x), res, [&bi](int idx, const std::vector<mod_t> &c) {
        return idx == 0 ? mod_t(1) : c[idx - 1] * bi.inv_unsafe(idx);
      });
  while (n--) rc.next();
  return res;
}

template <typename mod_t>
std::vector<mod_t> fps_quo(int n, const std::vector<mod_t> &x, const std::vector<mod_t> &y) {
  std::vector<mod_t> res;
  mod_t iv = mod_t(1) / y[0];
  lib::SemiRelaxedConvolution<mod_t> rc(y, res, [&iv, &x](int idx, const std::vector<mod_t> &c) {
    return (idx == 0 ? x[0] : (idx < static_cast<int>(x.size()) ? x[idx] : mod_t(0)) - c[idx]) * iv;
  });
  while (n--) rc.next();
  return res;
}

template <typename mod_t>
std::vector<mod_t> fps_log(int n, const std::vector<mod_t> &x) {
  return fps_integral(fps_quo(n - 1, fps_deriv(x), x));
}
```

### 指数

求 $\exp(f)$ 考虑

$$
\mathfrak{D}(\exp(f))=\exp(f)\cdot \mathfrak{D}(f)
$$

即得。

### 倒数

求 $f^{-1}$ 考虑

$$
f\cdot f^{-1}=1
$$

那么令 $g=f^{-1}=\sum _ {i\geq 0}g_ix^i$ 和 $f=\sum _ {i\geq 0}f_ix^i$ 有

$$
g_i=
\begin{cases}
f_0^{-1},&i=0,\\
-f_0^{-1}\cdot \sum _ {j=1}^if_ig _ {i-j},&i\neq 0.
\end{cases}
$$

即得。

### 商数或对数

求 $fg^{-1}$ 考虑

$$
(fg^{-1})g=f
$$

即得。

### 平方根

求 $f^2=g$ 无需考虑已经得到了解。

## 参考文献

- van der Hoeven, J., 2003a. [New algorithms for relaxed multiplication](http://www.texmacs.org/joris/newrelax/newrelax.html). Tech. Rep. 2003–44, Universit´e Paris-Sud, Orsay, France.
- J. van der Hoeven. Relax, but don't be too lazy. JSC, 34:479–542, 2002.
- Elegia and Athekatelan. 信息学竞赛中的⽣成函数计算理论框架.
- Elegia 的讲课[视频](https://www.bilibili.com/video/BV1kA41187dQ). （约 50 分钟左右，半在线卷积的具体实现及常见幂级数算法表示为半在线卷积， $O\left(\frac{n\log ^2n}{\log \log n}\right)$ ）
- fjzzq2002. [一个更好的多项式模板](https://fjzzq2002.blog.uoj.ac/blog/7281).
- van der Hoeven, J., August 2003b. Relaxed multiplication using the middle product. In: Bronstein, M. (Ed.), Proc. ISSAC’03. Philadelphia, USA, pp. 143–147.