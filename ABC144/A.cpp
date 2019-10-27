// 本戦
#include <iostream>

int solve_A() {
  int A, B;
  std::cin >> A >> B;

  if (A >= 1 && A <= 9 && B >= 1 && B <= 9) {
    std::cout << (A * B);
  } else {
    std::cout << "-1";
  }
  return 0;
}
