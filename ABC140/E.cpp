// 解説後
#include <iostream>
#include <set>
#include <vector>

// $l < i$として$P_i$より大きい値$P_l$が現れるとき、その$l$を大きな順に$L_1, L_2, \dots$とおく
// 同様に、$r > i$として$P_i$より大きい値$P_r$が現れるとき、その$r$を小さな順に$R_1, R_2, \dots$とおく
// すると、$\dots < L_2 < L_1 < i < R_1 < R_2 < \dots$となる
//
// $X_{L,R} = P_i$となるには、$L$から$R$までの間に$P_i$より大きい値が1つだけ含まれていれば良い
// つまり、$L_2 < L \le L_1$かつ$i \le R < R_1$の場合と$L_1 < L \le i$かつ$R_1 \le R < R_2$の場合である
// すると、$X_{L,R} = P_i$となる$L$と$R$の組み合わせの数は$C_i = (L_1 - L_2) \times (R_1 - i) + (i - L_1) \times (R_2 - R_1)$となる
//
// $\sum_{L=1}^{N-1} \sum_{R=L+1}^N X_{L,R}$は$1 \le L < R \le N$のときのすべての$L$と$R$の組み合わせを1つだけ含む
// よって、$\sum_{L=1}^{N-1} \sum_{R=L+1}^N X_{L,R} = \sum_{i=1}^N P_i \times C_i$である
//
// また、Pは${1, 2, \dots, N}$の順列なので、$\sum_{i=1}^N P_i \times C_i = \sum_{p \in P} p \times C_i$（ここで、$i$は$P[i] = p$）である
int solve_E() {
  size_t N = 0;  // Pの大きさ
  std::cin >> N;

  std::vector<uint64_t> P(N + 1);
  for (size_t i = 1; i <= N; ++i) {
    std::cin >> P[i];
  }

  // Pの値からインデックスを探すためのリストを作る
  std::vector<size_t> indexes(N + 1);
  for (size_t i = 1; i <= N; ++i) {
    indexes[static_cast<size_t>(P[i])] = i;
  }

  // X_{L,R}の総和を求める
  uint64_t result = 0;
  std::multiset<size_t> set{0, 0, N + 1, N + 1};  // pより大きな値のインデックスを格納するset。初期値として両端を指すインデックスを含む
  for (size_t p = N - 1; p > 0; --p) {
    const size_t i = indexes[p];

    // pより大きな値を持つインデックスのsetを累積的に構築する
    set.insert(indexes[p + 1]);

    // 境界のインデックスを取得する
    auto l2_iter = ++set.lower_bound(i);
    auto r2_iter = l2_iter--;
    auto r1_iter = l2_iter--;
    auto l1_iter = l2_iter--;

    // C_iを求める
    const size_t c = (*l1_iter - *l2_iter) * (*r1_iter - i) +
                     (i - *l1_iter) * (*r2_iter - *r1_iter);

    // 総数を求める
    result += p * c;
  }

  // 結果発表
  std::cout << result;
  return 0;
}
