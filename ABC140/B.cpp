// 解説前
#include <iostream>
#include <vector>

int solve_B() {
  int N;
  std::cin >> N;

  std::vector<int> A(N);
  for (auto& a : A) {
    std::cin >> a;
  }

  std::vector<int> B(N);
  for (auto& b : B) {
    std::cin >> b;
  }

  std::vector<int> C(N - 1);
  for (auto& c : C) {
    std::cin >> c;
  }

  int result = 0;
  int prev_a = N;
  for (const auto& a : A) {
    result += B[a - 1];
    if (a == prev_a + 1) result += C[prev_a - 1];
    prev_a = a;
  }

  std::cout << result;
  return 0;
}
