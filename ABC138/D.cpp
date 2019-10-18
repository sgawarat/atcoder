// 解説前
#include <iostream>
#include <unordered_set>
#include <vector>

int solve_D() {
  size_t N, Q;
  std::cin >> N >> Q;

  std::vector<std::vector<size_t>> graph(N);
  for (size_t i = 0; i < N - 1; ++i) {
    size_t a, b;
    std::cin >> a >> b;
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }

  std::vector<uint64_t> scores(N);
  for (size_t i = 0; i < Q; ++i) {
    size_t p;
    uint64_t x;
    std::cin >> p >> x;
    scores[p - 1] += x;
  }

  // 子が連続するようにソートする
  std::vector<size_t> stack;
  stack.reserve(N);
  std::vector<bool> visited(N);
  std::vector<uint64_t> total_scores(N);

  stack.push_back(0);
  visited[0] = true;
  total_scores[0] = scores[0];
  while (true) {
    const auto v = stack.back();

    bool all_visited = true;
    for (const auto& child : graph[v]) {
      if (!visited[child]) {
        stack.push_back(child);
        visited[child] = true;
        total_scores[child] = total_scores[v] + scores[child];
        all_visited = false;
        break;
      }
    }

    if (all_visited) {
      stack.pop_back();
      if (stack.empty()) break;
    }
  }

  // 結果発表
  for (const auto score : total_scores) {
    std::cout << score << ' ';
  }

  return 0;
}

int main() {
  return solve_D();
}
