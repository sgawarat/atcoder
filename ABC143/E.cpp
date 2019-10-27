// 解説後
#include <algorithm>
#include <iostream>
#include <vector>

constexpr uint64_t INVALID_DISTANCE = UINT64_MAX;
constexpr uint64_t INVALID_COUNT = UINT64_MAX;

int solve_E() {
  size_t N, M;
  uint64_t L;
  std::cin >> N >> M >> L;

  std::vector<uint64_t> distances(N * N, INVALID_DISTANCE);
  for (size_t i = 0; i < N; ++i) {
    distances[i * N + i] = 0;
  }

  std::vector<std::vector<size_t>> graph(N);
  for (size_t i = 0; i < M; ++i) {
    size_t a, b;
    uint64_t c;
    std::cin >> a >> b >> c;
    graph[a - 1].push_back(b - 1);
    distances[(a - 1) * N + (b - 1)] = c;
    graph[b - 1].push_back(a - 1);
    distances[(b - 1) * N + (a - 1)] = c;
  }

  for (size_t k = 0; k < N; ++k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        const auto i2k_distance = distances[i * N + k];
        const auto k2j_distance = distances[k * N + j];
        if (i2k_distance != INVALID_DISTANCE && k2j_distance != INVALID_DISTANCE) {
          distances[i * N + j] = std::min(distances[i * N + j], i2k_distance + k2j_distance);
        }
      }
    }
  }

  std::vector<uint64_t> refueling_counts(distances.size(), INVALID_COUNT);
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (i == j) {
        refueling_counts[i * N + j] = 0;
      } else if (distances[i * N + j] <= L) {
        refueling_counts[i * N + j] = 1;
      }
    }
  }

  for (size_t k = 0; k < N; ++k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        const auto i2k_refueling_count = refueling_counts[i * N + k];
        const auto k2j_refueling_count = refueling_counts[k * N + j];
        if (i2k_refueling_count != INVALID_COUNT && k2j_refueling_count != INVALID_COUNT) {
          refueling_counts[i * N + j] = std::min(refueling_counts[i * N + j], i2k_refueling_count + k2j_refueling_count);
        }
      }
    }
  }

  size_t Q;
  std::cin >> Q;
  
  std::vector<int64_t> results(Q, -1);
  for (auto& result : results) {
    size_t s, t;
    std::cin >> s >> t;

    const auto s2t_refueling_count = refueling_counts[(s - 1) * N + (t - 1)];
    if (s2t_refueling_count != INVALID_COUNT) {
      result = static_cast<int64_t>(s2t_refueling_count) - 1;
    }
  }

  for (const auto result : results) {
    std::cout << result << '\n';
  }

  return 0;
}

int main() { return solve_E(); }
