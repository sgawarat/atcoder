#include <iostream>

int solve_A() {
  char c;
  std::cin >> c;

  switch (c) {
    case 'S':
      std::cout << "Cloudy";
      break;
    case 'C':
      std::cout << "Rainy";
      break;
    case 'R':
      std::cout << "Sunny";
      break;
  }

  return 0;
}
