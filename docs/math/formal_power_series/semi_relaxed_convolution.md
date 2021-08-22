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

## 参考文献

- van der Hoeven, J., 2003a. [New algorithms for relaxed multiplication](http://www.texmacs.org/joris/newrelax/newrelax.html). Tech. Rep. 2003–44, Universit´e Paris-Sud, Orsay, France.
- J. van der Hoeven. Relax, but don't be too lazy. JSC, 34:479–542, 2002.
- Elegia and Athekatelan. 信息学竞赛中的⽣成函数计算理论框架.
- Elegia 的讲课[视频](https://www.bilibili.com/video/BV1kA41187dQ). （约 50 分钟左右，半在线卷积的具体实现及常见幂级数算法表示为半在线卷积， $O\left(\frac{n\log ^2n}{\log \log n}\right)$ ）
- fjzzq2002. [一个更好的多项式模板](https://fjzzq2002.blog.uoj.ac/blog/7281).