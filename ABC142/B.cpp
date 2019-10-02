// 本戦
#include <iostream>

int solve_B() {
  int N, K;
  std::cin >> N >> K;

  size_t count = 0;
  for (int i = 0; i < N; ++i) {
    int h;
    std::cin >> h;
    if (h >= K) count++;
  }

  std::cout << count;
  return 0;
}
