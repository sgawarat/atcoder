// 本戦
#include <algorithm>
#include <iostream>

int solve_A() {
  int A, B;
  std::cin >> A >> B;
  std::cout << std::max(0, A - 2 * B);  
  return 0;
}
