// 本戦
#include <iostream>

int solve_A() {
  int N;
  std::cin >> N;

  std::cout << (static_cast<double>((N + 1) / 2) / static_cast<double>(N));
  return 0;
}
