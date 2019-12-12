// 本戦
#define _USE_MATH_DEFINES
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>

inline double to_degree(double rad) noexcept {
  return rad * 180.0 / M_PI;
}

int solve_D() {
  double a, b, x;
  std::cin >> a >> b >> x;

  const auto y = x / a;
  const auto ab = a * b;

  double result = 0.0;
  if (y < ab / 2.0) {
    // 底が見える場合
    const auto b2 = b * b;
    const auto rad = atan2(b * b, 2.0 * y);
    result = to_degree(rad);
  } else {
    // 底が見えない場合
    const auto rad = atan2(2.0 * (ab - y), a * a);
    result = to_degree(rad);
  }

  //result = std::min(result, 90.0);
  //result = std::max(result, 0.0);
  std::cout << std::setprecision(20) << result;

  return 0;
}
