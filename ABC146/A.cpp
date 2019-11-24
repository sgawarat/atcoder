// 本戦
#include <iostream>
#include <string>

int solve_A() {
  std::string S;
  std::cin >> S;

  switch (S[0]) {
    case 'S':  // SUN or SAT
      switch (S[1]) {
        case 'U':  // SUN
          std::cout << '7';
          break;
        case 'A':  // SAT
          std::cout << '1';
          break;
      }
      break;
    case 'M':  // MON
      std::cout << '6';
      break;
    case 'T':  // TUE or THU
      switch (S[1]) {
        case 'U':  // TUE
          std::cout << '5';
          break;
        case 'H':  // THU
          std::cout << '3';
          break;
      }
      break;
    case 'W':  // WED
      std::cout << '4';
      break;
    case 'F':  // FRI
      std::cout << '2';
      break;
  }
  return 0;
}
