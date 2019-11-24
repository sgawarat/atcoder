// 解説前
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Edge {
  Edge() = default;

  Edge(size_t a, size_t b) {
    if (a > b) std::swap(a, b);
    this->a = a;
    this->b = b;
  }

  bool operator<(const Edge& other) const noexcept {
    if (a < other.a) return true;
    if (a > other.a) return false;
    return b < other.b;
  }

  size_t a = 0;
  size_t b = 0;
};

// 木構造 = 親は1つ = それ以外を子との辺に割り当てる
int main() {
  size_t N;
  std::cin >> N;

  std::vector<std::vector<size_t>> graph(N + 1);
  std::vector<Edge> edges(N - 1);
  for (size_t i = 0; i < N - 1; ++i) {
    std::cin >> edges[i].a >> edges[i].b;
    graph[edges[i].a].push_back(edges[i].b);
  }

  // 幅優先で色を塗る
  const size_t INVALID_COLOR = N + 1;
  std::vector<size_t> indices;
  std::vector<size_t> parent_colors;
  indices.reserve(N);
  parent_colors.reserve(N);
  std::map<Edge, size_t> color_map;
    
  size_t num_colors = 0;

  size_t color = 1;
  for (const auto child : graph[1]) {
    const auto child_color = color++;
    color_map.emplace(Edge{1, child}, child_color);
    indices.push_back(child);
    parent_colors.push_back(child_color);
  }
  num_colors = std::max(num_colors, graph[1].size());

  while (!indices.empty()) {
    const auto parent = indices.back();
    const auto parent_color = parent_colors.back();
    indices.pop_back();
    parent_colors.pop_back();
    
    size_t color = 1;
    const auto& children = graph[parent];
    for (const auto child : children) {
      if (color == parent_color) color++;

      const auto child_color = color++;
      color_map.emplace(Edge{parent, child}, child_color);
      indices.push_back(child);
      parent_colors.push_back(child_color);
    }

    // 色の数は頂点に接続される辺の最大数に等しい
    num_colors = std::max(num_colors, children.size() + 1);
  }

  std::cout << num_colors << '\n';
  for (const auto& edge : edges) {
    std::cout << color_map[edge] << '\n';
  }

  return 0;
}
