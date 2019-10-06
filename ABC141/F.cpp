// 解説前
#include <algorithm>
#include <iostream>
#include <vector>

int solve_F() {
  size_t N = 0;
  std::cin >> N;

  std::vector<uint64_t> A(N);
  uint64_t mask = 0;
  for (auto& a : A) {
    std::cin >> a;
    mask ^= a;
  }

  uint64_t result = mask;
  std::vector<uint64_t> reds;
  reds.push_back(0);
  for (size_t i = 0; i < N; ++i) {
    const size_t size = reds.size();
    reds.resize(2 * size);
    for (size_t j = 0; j < size; ++j) {
      const uint64_t red = reds[j] ^ A[i];
      reds[size + j] = red;
      result = std::max(result, red + (mask ^ red));
    }
  }

  std::cout << result;
  return 0;
}
