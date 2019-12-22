// 本戦
#include <iostream>

int solve_D() {
  uint64_t N;
  std::cin >> N;

  // 指定の並びを満たすレンガの個数を計算する
  uint64_t count = 0;  // 採用された個数
  for (uint64_t i = 0; i < N; ++i) {
    uint64_t a = 0;
    std::cin >> a;

    // 採用された個数+1の番号を持つレンガを採用する
    if (a == count + 1) count++;
  }

  // 結果発表
  if (count == 0) {
    std::cout << "-1";
  } else {
    std::cout << (N - count);
  }

  return 0;
}

int main() {
  return solve_D();
}
