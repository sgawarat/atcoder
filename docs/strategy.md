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
