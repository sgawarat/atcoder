// 解説前
#include <iostream>
#include <string>

int solve_A() {
  int a;
  std::cin >> a;

  if (a >= 3200) {
    std::string s;
    std::cin >> s;
    std::cout << s;
  } else {
    std::cout << "red";
  }

  return 0;
}

int main() {
  return solve_A();
}
