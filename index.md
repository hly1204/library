---
data:
  libraryCategories:
  - name: .
    pages:
    - icon: ':question:'
      path: common.hpp
      title: common.hpp
  - name: datastructure
    pages:
    - icon: ':heavy_check_mark:'
      path: datastructure/cartesian_tree.hpp
      title: Cartesian Tree
    - icon: ':heavy_check_mark:'
      path: datastructure/disjoint_set.hpp
      title: Disjoint Set
    - icon: ':heavy_check_mark:'
      path: datastructure/weighted_disjoint_set.hpp
      title: Weighted Disjoint Set
  - name: math
    pages:
    - icon: ':question:'
      path: math/binomial.hpp
      title: Binomial Coefficient (in $\mathbb{F} _ p$)
    - icon: ':heavy_check_mark:'
      path: math/binomial_convolution.hpp
      title: Binomial Convolution (in $\mathbb{Z} / m \mathbb{Z}$)
    - icon: ':heavy_check_mark:'
      path: math/convolution.hpp
      title: Convolution (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
    - icon: ':heavy_check_mark:'
      path: math/convolution_mod.hpp
      title: Convolution (in $\mathbb{Z} m / \mathbb{Z} \lbrack z \rbrack$)
    - icon: ':x:'
      path: math/cra.hpp
      title: Chinese Remainder Algorithm (in $\mathbb{Z} / m \mathbb{Z}$)
    - icon: ':heavy_check_mark:'
      path: math/czt.hpp
      title: Chirp Z-transform (Bluestein's algorithm) (in $\mathbb{F} _ p \lbrack
        z \rbrack$ for FFT prime $p$)
    - icon: ':question:'
      path: math/extended_gcd.hpp
      title: Extended Euclidean Algorithm (in $\mathbb{Z}$)
    - icon: ':heavy_check_mark:'
      path: math/formal_power_series.hpp
      title: Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$
        for FFT prime $p$)
    - icon: ':heavy_check_mark:'
      path: math/integer_factorization.hpp
      title: Integer Factorization (Pollard's rho algorithm) (in $\mathbb{Z}$)
    - icon: ':x:'
      path: math/linear_sieve.hpp
      title: Linear Sieve
    - icon: ':heavy_check_mark:'
      path: math/multivariate_convolution.hpp
      title: Multivariate Convolution (in $\mathbb{F} _ p \lbrack z_1, \dots, z_d
        \rbrack \left/ \left( z_1^{l_1}, \dots, z_d^{l_d} \right)\right.$ for FFT
        prime $p$)
    - icon: ':heavy_check_mark:'
      path: math/poly_extended_gcd.hpp
      title: Extended Euclidean Algorithm (in $\mathbb{F} _ p$ for FFT prime $p$)
    - icon: ':question:'
      path: math/polynomial.hpp
      title: Polynomial (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
    - icon: ':question:'
      path: math/radix2_ntt.hpp
      title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
    - icon: ':question:'
      path: math/random.hpp
      title: Pseudo Random Number Generator
    - icon: ':heavy_check_mark:'
      path: math/relaxed_convolution.hpp
      title: Relaxed Convolution (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$
        for FFT prime $p$)
    - icon: ':question:'
      path: math/semi_relaxed_convolution.hpp
      title: Semi-Relaxed Convolution (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT
        prime $p$)
    - icon: ':warning:'
      path: math/shift_sample_points_single.hpp
      title: Shift Sample Points (Single) (in $\mathbb{F} _ p \lbrack z \rbrack$)
    - icon: ':question:'
      path: math/sqrt_mod.hpp
      title: Square Roots (in $\mathbb{F} _ p$)
    - icon: ':x:'
      path: math/stirling_numbers.hpp
      title: Stirling Numbers (in $\mathbb{F} _ p$ for FFT prime $p$)
    - icon: ':heavy_check_mark:'
      path: math/subproduct_tree.hpp
      title: Multipoint Evaluation and Interpolation (in $\mathbb{F} _ p$ for FFT
        prime $p$)
    - icon: ':question:'
      path: math/taylor_shift.hpp
      title: Polynomial Taylor Shift (in $\mathbb{F} _ p$ for FFT prime $p$)
    - icon: ':question:'
      path: math/truncated_formal_power_series.hpp
      title: Truncated Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack
        \rbrack$ for FFT prime $p$)
    - icon: ':question:'
      path: math/truncated_fourier_transform.hpp
      title: Truncated Fourier Transform (in $\mathbb{F} _ p \lbrack z \rbrack$ for
        FFT prime $p$)
  - name: modint
    pages:
    - icon: ':heavy_check_mark:'
      path: modint/long_montgomery_modint.hpp
      title: Long Montgomery ModInt
    - icon: ':question:'
      path: modint/montgomery_modint.hpp
      title: Montgomery ModInt
    - icon: ':heavy_check_mark:'
      path: modint/runtime_long_montgomery_modint.hpp
      title: Runtime Long Montgomery ModInt
    - icon: ':x:'
      path: modint/runtime_modint.hpp
      title: Runtime ModInt
    - icon: ':warning:'
      path: modint/runtime_montgomery_modint.hpp
      title: Runtime Montgomery ModInt
  - name: string
    pages:
    - icon: ':heavy_check_mark:'
      path: string/suffix_array.hpp
      title: Suffix Array (SA-IS)
    - icon: ':heavy_check_mark:'
      path: string/z_function.hpp
      title: Z Function
  verificationCategories:
  - name: remote_test/aizu/datastructure
    pages:
    - icon: ':heavy_check_mark:'
      path: remote_test/aizu/datastructure/weighted_union_find.0.test.cpp
      title: remote_test/aizu/datastructure/weighted_union_find.0.test.cpp
  - name: remote_test/aizu/number_theory
    pages:
    - icon: ':heavy_check_mark:'
      path: remote_test/aizu/number_theory/binary_pow.0.test.cpp
      title: remote_test/aizu/number_theory/binary_pow.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp
      title: remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp
  - name: remote_test/yosupo/datastructure
    pages:
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp
      title: remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/datastructure/union_find.0.test.cpp
      title: remote_test/yosupo/datastructure/union_find.0.test.cpp
  - name: remote_test/yosupo/math
    pages:
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/convolution_mod.0.test.cpp
      title: remote_test/yosupo/math/convolution_mod.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/convolution_mod.1.test.cpp
      title: remote_test/yosupo/math/convolution_mod.1.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/convolution_mod.2.test.cpp
      title: remote_test/yosupo/math/convolution_mod.2.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/convolution_mod.3.test.cpp
      title: remote_test/yosupo/math/convolution_mod.3.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
      title: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
      title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/exp_of_formal_power_series.0.test.cpp
      title: remote_test/yosupo/math/exp_of_formal_power_series.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
      title: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/factorize.0.test.cpp
      title: remote_test/yosupo/math/factorize.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
      title: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
      title: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
      title: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
      title: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
      title: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
      title: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
      title: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/multivariate_convolution.0.test.cpp
      title: remote_test/yosupo/math/multivariate_convolution.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/partition_function.0.test.cpp
      title: remote_test/yosupo/math/partition_function.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
      title: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
      title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
      title: remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
      title: remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
      title: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
      title: remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
    - icon: ':x:'
      path: remote_test/yosupo/math/sqrt_mod.0.test.cpp
      title: remote_test/yosupo/math/sqrt_mod.0.test.cpp
    - icon: ':x:'
      path: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
      title: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
    - icon: ':x:'
      path: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
      title: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
    - icon: ':x:'
      path: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
      title: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - name: remote_test/yosupo/string
    pages:
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/string/suffix_array.0.test.cpp
      title: remote_test/yosupo/string/suffix_array.0.test.cpp
    - icon: ':heavy_check_mark:'
      path: remote_test/yosupo/string/z_algorithm.0.test.cpp
      title: remote_test/yosupo/string/z_algorithm.0.test.cpp
  - name: remote_test/yuki/math
    pages:
    - icon: ':x:'
      path: remote_test/yuki/math/187.0.test.cpp
      title: remote_test/yuki/math/187.0.test.cpp
layout: toppage
---
[![License](https://img.shields.io/github/license/hly1204/library)](https://github.com/hly1204/library/blob/master/LICENSE) ![Standard](https://img.shields.io/badge/C%2B%2B-17-green)

## Links

- [GitHub issues](https://github.com/hly1204/library/issues)