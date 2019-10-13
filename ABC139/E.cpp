// 解説前
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>

int A[1001][1001];

// 問題文通りに手前から試合を消費していく
// => 同じ選手との試合が複数通り取れる場合にどうするか
//
// N = 1000なので N^3でもぎりぎり行けそう？
//
// 行列操作？
int solve_E() {
  size_t N;
  std::cin >> N;

  for (size_t i = 1; i <= N; ++i) {
    for (size_t j = 1; j <=  N - 1; ++j) {
      std::cin >> A[i][j];
    }
  }

  std::vector<size_t> heads(N + 1, 1);  // 現在見ているA[i]の先頭のインデックス
  std::unordered_set<size_t> matches;  // 試合を組んだ選手の番号
  size_t result = 0;  // 総日数
  size_t remains = N * (N - 1);  // 残りの試合数 * 2
  while (true) {
    matches.clear();
    for (size_t i = 1; i <= N; ++i) {
      const auto head = heads[i];

      // 試合予定が組まれていない場合
      if (matches.find(i) == matches.end()) {
        // 試合予定が残っている場合
        if (head <= N - 1) {
          const int opponent = A[i][head];
          const int opponent_opponent = A[opponent][heads[opponent]];

          // 互いが互いを対戦相手としていれば、その試合を組む
          if (i == opponent_opponent) {
            matches.insert(i);
            matches.insert(opponent);
          }
        }
      }
    }

    // 試合を組めない場合
    if (matches.empty()) {
      std::cout << "-1";
      return 0;
    }

    // 日程を進める
    for (auto m : matches) {
      heads[m]++;
      remains--;
    }
    result++;

    // すべての試合を組んだら終了
    if (remains == 0) break;
  }

  std::cout << result;
  return 0;
}

int main() { return solve_E(); }
