// 本戦
#include <iostream>

int solve_C() {
  int N;
  std::cin >> N;

  size_t result = 0;
  char prev_color = 0;
  for (int i = 0; i < N; ++i) {
    char color;
    std::cin >> color;
    if (color != prev_color) {
      result++;
      prev_color = color;
    }
  }
  
  std::cout << result;
  return 0;
}
