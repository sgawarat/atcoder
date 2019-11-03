// 解説前
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>

// 価値を減らしつつ総和を大きくする問題ので、損失を抑えるためにその時点で最も小さい値で操作を行うのが良い
int solve_C() {
  size_t N;
  std::cin >> N;

  std::priority_queue<double, std::vector<double>, std::greater<>> values;
  for (size_t i = 0; i < N; ++i) {
    uint32_t value;
    std::cin >> value;
    values.push(static_cast<double>(value));
  }

  for (size_t i = 0; i < N - 1; ++i) {
    const double x = values.top();
    values.pop();
    const double y = values.top();
    values.pop();
    values.push((x + y) / 2.0);
  }

  std::cout << std::setprecision(20) << values.top();
  return 0;
}
