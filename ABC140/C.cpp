// 解説前
#include <algorithm>
#include <iostream>

int solve_C() {
  int N;
  std::cin >> N;

  int result = 0;
  int prev_b = 100000;
  for (int i = 0; i < N - 1; ++i) {
    int b;
    std::cin >> b;
    result += std::min(prev_b, b);
    prev_b = b;
  }
  result += prev_b;

  std::cout << result;
  return 0;
}
