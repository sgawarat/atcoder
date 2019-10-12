// 解説前
#include <iostream>

int solve_A() {
  char S[3];
  std::cin.read(S, 3);

  std::cin.get();  // 改行を読み飛ばす
  
  char T[3];
  std::cin.read(T, 3);

  size_t result = 0;
  for (size_t i = 0; i < 3; ++i) {
    if (S[i] == T[i]) result++;
  }

  std::cout << result;
  return 0;
}
