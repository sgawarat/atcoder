# 戦略

## ある条件下での総和を求める

- 各条件を満たすかどうかを状態として、状態ごとの総和を計算する[@ABC138F]
  - 1つの入力に対して状態が1つに定まれば、総和を分割しても重複して数えることはない
  - 総和は動的計画法により各状態の中間値を用いて累積的に計算される

```cpp
// すべての条件を満たすときのビットセット
constexpr uint32_t COND_ALL_BITS = ...;

uint64_t sum(size_t N) {
  std::vector<std::array<uint64_t, COND_ALL_BITS + 1>> counts(N + 1);
  for (size_t i = 0; i < N; ++i) {
    for (uint32_t cond = 0; cond <= COND_ALL_BITS; ++cond) {
      // i番目にcondの状態のものがi+1番目にnew_condの状態となる場合の数を記録する
      uint32_t new_cond = ...;
      counts[i + 1][new_cond] += counts[i][cond];
    }
  }
  return counts[N][COND_ALL_BITS];
}
```

## 二次元配列を一次元に展開する

- 総当りの組み合わせをグラフの頂点に対応させるためのIDを計算する[@ABC137E]

```cpp
// 初項a、公差dの等差数列のnまでの和を計算する
template <typename T>
constexpr T arithmetic_series(T n, T a_1, T d) noexcept {
  return n * (2 * a_1 + (n - 1) * d) / 2;
}

// 組み合わせ(a, b)の線形インデックスを計算する
// 戻り値はa<bのときをb優先で数えたときの値に相当する
//
// n=4の場合（(a,b)は(b,a)と等価）
// a\b| 0 1 2 3 4
// --------------
//  0 | * 0 1 2 3
//  1 | * * 4 5 6
//  2 | * * * 7 8
//  3 | * * * * 9
//  4 | * * * * *
template <typename T>
constexpr T make_linear_index(T n, T a, T b) noexcept {
  if (a > b) std::swap(a, b);
  const T offset = arithmetic_series(a + 1, 1, 1);  // 列aまでにa>=bとなる要素の数
  return a * N + b - offset;
}
```

## 剰余演算を含めた組み合わせの数を求める

- ${}_n C_r \text{ mod } p$（$p$は$r$と互いに素な素数）を求めたい[@ABC145D]

組み合わせの数は階乗を伴うために計算機上では容易にオーバーフローするので、剰余演算を階乗内部に織り込むことを考える。

### 前知識

剰余演算は四則演算の中で分配と似た操作を行うことができる。

- $(a+b) \text{ mod } n = ((a \text{ mod } n) + (b \text{ mod } n)) \text{ mod } n$
- $ab \text{ mod } n = ((a \text{ mod } n)(b \text{ mod } n)) \text{ mod } n$
- $\frac{a}{b} \text{ mod } n = ((a \text{ mod } n)(b^{-1} \text{ mod } n)) \text{ mod } n$

ここで、$b^{-1}$はモジュラ逆数と呼ばれる乗法逆元である。

- $((b \text{ mod } n)(b^{-1} \text{ mod } n)) \text{ mod } n = 1$

また、フェルマーの小定理により、素数$p$と互いに素な$a$に関して、

$$
\begin{array}{ll}
& a^{p-1} \text{ mod } p = 1 \\
\Rightarrow & (a^{p-2} a) \text{ mod } p = 1 \\
\Rightarrow & ((a^{p-2} \text{ mod } p)(a \text{ mod } p)) \text{ mod } p = 1
\end{array}
$$

が成り立ち、$a$のモジュラ逆数が$a^{p-2}$であることが分かる。

### 概要

${}_n C_r \text{ mod } p$は以下のように変形できる。

$$
\begin{array}{ll}
{}_n C_r \text{ mod } p &= \frac{\prod_{i=1}^r (n-i+1)}{r!} \text{ mod } p \\
&= \left( \left( \prod_{i=1}^r (n-i+1) \right) \text{ mod } p \right) \left( {r!}^{-1} \text{ mod } p \right) \text{ mod } p \\
&= \left( \left( \prod_{i=1}^r (n-i+1) \right) \text{ mod } p \right) \left({r!}^{p-2} \text{ mod } p \right) \text{ mod } p \\
\end{array}
$$

したがって、${}_n C_r$は$\prod_i z_i$の形で表され、${}_n C_r \text{ mod } p$を計算するには乗算に関わる値すべてで剰余を取れば良い。

### 実装

まとめると、以下に注意しながら数式を実装すれば良い。

- 乗算ごとに剰余を取る
- 分母の逆数を$r!^{p-2}$として計算する

```cpp
// ナイーブな剰余付き累乗の計算
// 計算量：O(y)
// template <typename T>
// T pow(T x, T y, T m) noexcept {
//   T r = 1;
//   for (size_t i = 0; i < y; ++i) {
//     r *= x;
//     if (r >= m) r %= m;
//   }
// }

// 高速な剰余付き累乗の計算（指数を2の累乗の和として考える）
// 計算量：最大O(sizeof(T) * 8)
template <typename T>
T pow(T x, T y, T m) noexcept {
  T r = 1;
  if (x >= m) x %= m;
  while (y > 0) {
    // yのiビット目が1であれば、結果にx^{2^i}をかける
    if (y & 1) {
      r *= x;
      if (r >= m) r %= m;
    }

    // xの2^i乗を累積的に計算する
    x *= x;
    if (x >= m) x %= m;

    y >>= 1;
  }
}

// 剰余付き組み合わせ数を計算する
// （pは素数、rはpと互いに素）
template <typename T>
T combination(T n, T r, T p) noexcept {
  // 分子を計算する
  T num = 1;
  for (size_t i = 0; i < r; ++i) {
    num *= n - i;
    if (num >= p) num %= p;
  }

  // 分母を計算する
  T denom = 1;
  for (size_t i = 2; i <= r; ++i) {
    denom *= i;
    if (denom >= p) denom %= p;
  }

  // 分母の逆数を計算する
  T denom_inv = pow(denom, p - 2, p);

  return (num * denom_inv) % p;
}
```

### 参考文献

- [nCr mod m の求め方 --- いかたこのたこつぼ](https://ikatakos.com/pot/programming_algorithm/number_theory/mod_combination)
- [Calculating pow(a,b) mod n --- Stackoverflow](https://stackoverflow.com/questions/8496182/calculating-powa-b-mod-n)
