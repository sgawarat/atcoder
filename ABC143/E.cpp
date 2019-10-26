// 解説前
#include <algorithm>
#include <iostream>
#include <vector>

int solve_E() {
  size_t N, M;
  uint64_t L;
  std::cin >> N >> M >> L;

  uint64_t costs[301][301];
  for (size_t i = 0; i < 301; ++i) {
    for (size_t j = 0; j < 301; ++j) {
      costs[i][j] = INT64_MAX;
    }
  }

  std::vector<std::vector<size_t>> graph(N + 1);
  for (size_t i = 0; i < M; ++i) {
    size_t a, b;
    uint64_t c;
    std::cin >> a >> b >> c;
    if (c <= L) {
      graph[a].push_back(b);
      graph[b].push_back(a);
      costs[a][b] = c;
      costs[b][a] = c;
    }
  }

  size_t Q;
  std::cin >> Q;
  for (size_t i = 0; i < Q; ++i) {
    size_t s, t;
    std::cin >> s >> t;

    std::vector<size_t> stack;
    stack.reserve(N + 1);
    std::vector<bool> visited(N + 1);
    stack.push_back(s);
    visited[s] = true;
    while (true) {
      const auto v = stack.back();
      bool all_visited = true;
      for (const auto child : graph[v]) {
        if (!visited[child]) {
          const auto v2c_cost = costs[v][child];
          const auto s2v_cost = costs[s][v];
          const auto thres = (s2v_cost + L - 1) / L * L;
          const auto s2c_cost = s2v_cost + v2c_cost;
          if (s2c_cost <= thres) {
            costs[s][child] = std::min(costs[s][child], s2c_cost);
          } else {
            costs[s][child] = std::min(costs[s][child], thres + v2c_cost);
          }

          stack.push_back(child);
          visited[child] = true;
          all_visited = false;
          break;
        }
      }

      if (all_visited) {
        stack.pop_back();
        if (stack.empty()) break;
      }
    }

    if (visited[t]) {
      const auto cost = costs[s][t];
      std::cout << (cost > 0 ? ((cost - 1) / L) : 0) << '\n';
    } else {
      std::cout << "-1\n";
    }
  }

  return 0;
}

int main() { return solve_E(); }
