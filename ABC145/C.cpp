// 本戦
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

int solve_C() {
  size_t N;
  std::cin >> N;

  std::vector<double> x(N);
  std::vector<double> y(N);
  for (size_t i = 0; i < N; ++i) {
	std::cin >> x[i] >> y[i];
  }
  
  // すべての町間距離を計算する
  std::vector<double> distances(N * N);
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      const double dx = x[i] - x[j];
      const double dy = y[i] - y[j];
      distances[i * N + j] = std::sqrt(dx * dx + dy * dy);
    }
  }

  // 距離の総和を計算する
  size_t n = 0;  // 順列の個数
  double result = 0.0;
  std::vector<size_t> indices(N);
  for (size_t i = 0; i < N; ++i) {
    indices[i] = i;
  }
  while (true) {
	for (size_t k = 1; k < N; ++k) {
      const auto i = indices[k - 1];
      const auto j = indices[k];
      result += distances[i * N + j];
    }
    n++;
    if (!std::next_permutation(indices.begin(), indices.end())) break;
  }

  // 結果発表
  std::cout << std::setprecision(20) << (result / double(n));
  return 0;
}
