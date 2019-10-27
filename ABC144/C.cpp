// 本戦
#include <algorithm>
#include <iostream>

int solve_C() {
  uint64_t N;
  std::cin >> N;

  uint64_t result = N + 1;
  for (uint64_t i = 2; i * i <= N; ++i) {
    if (N % i == 0) {
      const uint64_t j = N / i;
      result = std::min(result, i + j);
    }
  }

  std::cout << (result - 2);
  return 0;
}
