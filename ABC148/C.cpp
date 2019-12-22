// 本戦
#include <iostream>

int solve_C() {
  uint64_t A, B;
  std::cin >> A >> B;

  if (A > B) std::swap(A, B);

  uint64_t n = B;
  for (uint64_t i = 0; i < A; ++i) {
    if (n % A == 0) break;
    n += B;
  }

  std::cout << n;
  return 0;
}
