// 解説前、TLE
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int solve_E() {
  size_t N;
  std::string S;
  std::cin >> N >> S;

  size_t result = 0;
  for (size_t l1 = 0; l1 < N - 1; ++l1) {
    for (size_t l2 = l1 + 1; l2 < N; ++l2) {
      const size_t len = std::min(l2 - l1, N - l2);
      size_t i = 0;
      for (; i < len; ++i) {
        if (S[l1 + i] != S[l2 + i]) break;
      }
      result = std::max(result, i);
    }
  }

  std::cout << result;
  return 0;
}
