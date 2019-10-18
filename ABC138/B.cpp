// 解説前
#include <iostream>
#include <iomanip>

int solve_B() {
  int N;
  std::cin >> N;

  double denom = 0.0;
  for (int i = 0; i < N; ++i) {
    int A;
    std::cin >> A;
    denom += 1.0 / A;
  }

  std::cout << std::setprecision(20) << (1.0 / denom);

  return 0;
}

int main() {
  return solve_B();
}
