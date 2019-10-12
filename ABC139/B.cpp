// 解説前
#include <iostream>

int solve_B() {
  int A, B;
  std::cin >> A >> B;

  // n * (A - 1) + 1 >= B
  // ⇒ n >= (B - 1) / (A - 1)
  // ⇒ n = (B - 1 + A - 1 - 1) / (A - 1)
  std::cout << ((B + A - 3) / (A - 1));

  return 0;
}
