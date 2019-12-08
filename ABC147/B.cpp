// 本戦
#include <iostream>
#include <string>

int solve_B() {
  std::string S;
  std::cin >> S;

  size_t i = 0;
  size_t j = S.size() - 1;
  size_t result = 0;
  while (i < j) {
    if (S[i] != S[j]) result++;
    i++;
    j--;
  }

  std::cout << result;

  return 0;
}
