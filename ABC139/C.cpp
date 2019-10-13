// 解説前
#include <iostream>

int solve_C() {
  int N;
  std::cin >> N;

  int result = 0;
  int count = 0;
  int curr;
  std::cin >> curr;
  for (int i = 1; i < N; ++i) {
    int next;
    std::cin >> next;
    if (next <= curr) {
      count++;
    } else {
      result = count > result ? count : result;
      count = 0;
    }
    curr = next;
  }
  result = count > result ? count : result;

  std::cout << result;
  return 0;
}
