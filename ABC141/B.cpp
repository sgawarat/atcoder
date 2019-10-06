#include <iostream>
#include <string>

int solve_B() {
  std::string s;
  std::cin >> s;

  bool is_even = false;
  for (auto c : s) {
    if ((c == 'L' && !is_even) ||
        (c == 'R' && is_even)) {
      std::cout << "No";
      return 0;
    }
    is_even = !is_even;
  }

  std::cout << "Yes";
  return 0;
}
