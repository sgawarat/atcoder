#include <iostream>
#include <queue>

// 割引率は1枚につき50%
// 品物を最も安く買える割引券の使い方を見つけたい
// ⇒ 割引券はできる限り割り引かれる値段が大きくなるように使われるはず
// ⇒ 1枚ずつ最も価格の大きな品物に適用していく
int solve_D() {
  uint64_t N, M;
  std::cin >> N >> M;

  std::priority_queue<uint64_t> prices;
  for (uint64_t i = 0; i < N; ++i) {
    uint64_t price;
    std::cin >> price;
    prices.push(price);
  }

  // 割引券を1枚ずつ最も大きな価格の品物に適用する
  for (uint64_t i = 0; i < M; ++i) {
    const uint64_t price = prices.top() / 2;
    prices.pop();
    prices.push(price);
  }

  uint64_t result = 0;
  while (!prices.empty()) {
    result += prices.top();
    prices.pop();
  }

  std::cout << result;

  return 0;
}
