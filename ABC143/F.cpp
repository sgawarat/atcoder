// 本戦
#include <algorithm>
#include <iostream>
#include <vector>

int solve_F() {
  size_t N;
  std::cin >> N;

  std::vector<size_t> counts(N);
  for (size_t i = 0; i < N; ++i) {
    size_t a;
    std::cin >> a;
    counts[a - 1]++;
  }
  counts.erase(std::remove(counts.begin(), counts.end(), 0), counts.end());
  std::sort(counts.begin(), counts.end());

  std::vector<size_t> deltas(counts.size());
  deltas[0] = counts[0];
  for (size_t i = 1; i < counts.size(); ++i) {
    deltas[i] = counts[i] - counts[i - 1];
  }

  const size_t M = counts.size();
  for (size_t K = 1; K <= N; ++K) {
    size_t result = 0;
    if (M >= K) {
      for (size_t i = 0; i <= M - K; ++i) {
        const size_t n = (M - i) / K;
        result += deltas[i] * n;
      }
    }
    std::cout << result << '\n';
  }

  return 0;
}

int main() {
  return solve_F();
}
