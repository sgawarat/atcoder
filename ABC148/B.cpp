// 本戦
#include <iostream>
#include <string>

int solve_B() {
  int N;
  std::string S, T;
  std::cin >> N >> S >> T;

  for (int i = 0; i < N; ++i) {
    std::cout << S[i] << T[i];
  }

  return 0;
}
