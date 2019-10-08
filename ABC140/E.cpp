// 解説前
#include <iostream>
#include <vector>

int solve_E() {
  size_t N = 0;
  std::cin >> N;

  std::vector<uint64_t> P(N);
  for (auto& p : P) {
    std::cin >> p;
  }

  uint64_t result = 0;
  for (size_t l = 0; l < N - 1; ++l) {
    uint64_t first = P[l], second = 0;
    for (size_t r = l + 1; r < N; ++r) {
      if (P[r] > first) {
        second = first;
        first = P[r];
      } else if (P[r] > second) {
        second = P[r];
      }
      result += second;
    }
  }

  std::cout << result;
  return 0;
}
