// 本戦
#include <algorithm>
#include <iostream>
#include <vector>

int solve_B() {
  int N;
  std::cin >> N;
  
  std::vector<int> vec(N);
  for (auto& v : vec) {
    std::cin >> v;
  }
  
  int result = 0;
  for (int i = 0; i < N - 1; ++i) {
	for (int j = i + 1; j < N; ++j) {
      result += vec[i] * vec[j];
    }
  }
  
  std::cout << result;
  return 0;
}
