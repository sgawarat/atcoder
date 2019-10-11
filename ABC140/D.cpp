// 解説前
#include <algorithm>
#include <iostream>
#include <vector>

// 同じ方向を向いて連続するx人のうち、x-1人が幸福である
// パターンA：端を含まない連続するx人を操作すると、幸福な人は2人増える（x-1 -> x+1）
// パターンB：端を含む連続するx人を操作すると、幸福な人は1人増える（x-1 -> x）
// ⇒ 幸福な人数を最大にしたいので、まずAの場合を可能な限り行い、次にBの場合を行う
int solve_D() {
  size_t N = 0;  // 人数
  size_t K = 0;  // 操作回数の上限
  std::cin >> N >> K;

  std::vector<char> S(N);
  for (size_t i = 0; i < N; ++i) {
    std::cin >> S[i];
  }

  // 初期状態を調べる
  size_t pair_count = 0;  // LとRの連続部分のペアの個数
  size_t happiness = 0;  // 幸福度
  auto head_iter = S.cbegin();  // 連続部分の先頭のイテレータ
  for (auto iter = ++S.cbegin(); iter != S.cend(); ++iter) {
    if (*iter != *head_iter) {
      if (*head_iter != S.front()) pair_count++;
      happiness += (iter - head_iter) - 1;
      head_iter = iter;
    }
  }
  if (*head_iter != S.front()) pair_count++;
  happiness += (S.cend() - head_iter) - 1;

  if (S.front() == S.back()) {
    // 端を含む連続部分が同じ方向を向いている場合、
    // すべての連続部分をその向きに揃えるように可能な限り操作を行う
    const size_t a = 2 * std::min(pair_count, K);  // パターンA
    happiness += a;
  } else {
    // 端を含む連続部分が異なる方向を向いている場合、
    // どちらかの向きに揃えるように可能な限り操作を行う
    const size_t n = pair_count - 1;
    const size_t a = 2 * std::min(n, K);  // パターンA
    const size_t b = n < K ? 1 : 0;  // パターンB（操作回数が余る場合のみ）
    happiness += a + b;
  }

  // 結果発表
  std::cout << happiness;

  return 0;
}
