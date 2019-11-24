// 本戦
#include <iostream>

template <typename T>
T digit10(T n) noexcept {
  T d = 1;
  while (n >= 10) {
    n /= 10;
    d++;
  }
  return d;
}

template <typename T>
T price(T n, T a, T b) noexcept {
  return a * n + b * digit10(n);
}

int solve_C() {
  uint64_t A, B, X;
  std::cin >> A >> B >> X;

  uint64_t min = 1;
  uint64_t max = 1'000'000'000;
  if (X < price(min, A, B)) {
    std::cout << '0';
  } else if (X >= price(max, A, B)) {
    std::cout << max;
  } else {
    while (true) {
      const uint64_t mid = min + (max - min) / 2;
      const uint64_t mid_price = A * mid + B * digit10(mid);
      if (mid_price < X) {
        min = mid;
      } else if (mid_price > X) {
        max = mid;
      } else {
        std::cout << mid;
        break;
      }

      if (max - min == 1) {
        std::cout << min;
        break;
      }
    }
  }

  return 0;
}
