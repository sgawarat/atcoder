// 本戦
#include <iostream>
#include <vector>
#include <cstdint>

int main() {
  uint64_t X, Y;
  std::cin >> X >> Y;
  
  if (X > Y) std::swap(X, Y);

  const auto distance = X + Y;
  
  if (distance % 3 != 0) {
    std::cout << '0';
  } else {
	const auto depth = distance / 3;
	const auto level = X - depth;
    
    uint64_t result = 1;
    for (uint64_t i = 0; i < level; ++i) {
      result *= depth - i;
    }

    std::cout << (result % 1000000007);
  }
  return 0;
}
