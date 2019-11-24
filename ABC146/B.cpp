// 本戦
#include <iostream>
#include <string>

int solve_B() {
  int N;
  std::string S;
  std::cin >> N >> S;

  for (const char c : S) {
    const int i = int(c) - 'A';
    const int rot_i = (i + N) % 26;
    std::cout << char(rot_i + 'A');
  }

  return 0;
}
