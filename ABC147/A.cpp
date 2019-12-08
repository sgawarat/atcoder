// 本戦
#include <iostream>

int main() {
  int A1, A2, A3;
  std::cin >> A1 >> A2 >> A3;

  if (A1 + A2 + A3 >= 22) {
    std::cout << "bust";
  } else {
    std::cout << "win";
  }

  return 0;
}
