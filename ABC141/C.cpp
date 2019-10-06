#include <iostream>
#include <vector>

int solve_C() {
  int N, K, Q;
  std::cin >> N >> K >> Q;

  std::vector<int> scores(N, K - Q);  // 1回も正解できなかった場合の点数で初期化する
  for (int i = 0; i < Q; ++i) {
    int A;
    std::cin >> A;
    scores[A - 1]++;  // 正解分を加点
  }

  for (auto score : scores) {
    std::cout << (score > 0 ? "Yes" : "No") << '\n';
  }

  return 0;
}
