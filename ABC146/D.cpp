// 解説前
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

// 向きを持たない辺
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

// 入力されるグラフは木構造なので、各頂点は親を1つだけ持つ
// => 幅優先探索を用いて親との辺以外の色を子との辺に割り当てれば良い
// => 必要な色数は頂点に接続される辺の最大数になる
int solve_D() {
  size_t N;
  std::cin >> N;

  // グラフを読み取る
  std::vector<std::vector<size_t>> graph(N + 1);
  std::vector<Edge> edges(N - 1);  // 入力順の辺情報
  for (size_t i = 0; i < N - 1; ++i) {
    std::cin >> edges[i].a >> edges[i].b;
    graph[edges[i].a].push_back(edges[i].b);
  }

  // 色を塗る
  // 親頂点が処理済みの状態で子供を処理すればいいので、FIFOでもFILOでも問題なく行える
  std::vector<size_t> indices;  // 頂点番号を格納するのスタック
  std::vector<size_t> parent_colors;  // 親との辺の色を格納するスタック
  indices.reserve(N);
  parent_colors.reserve(N);
  std::map<Edge, size_t> color_map;  // 辺に割り当てた色を格納するマップ
  size_t num_colors = 0;  // 必要となる色数

  // ルート頂点の子供にそれぞれ異なる色を割り当てる
  size_t color = 1;
  for (const auto child : graph[1]) {
    // 辺に割り当てた色を記録する
    const auto child_color = color++;
    color_map.emplace(Edge{1, child}, child_color);

    // 子供の子供を処理するために子頂点をスタックに積む
    indices.push_back(child);
    parent_colors.push_back(child_color);
  }

  // 親を持たない場合の色数を数える
  num_colors = std::max(num_colors, graph[1].size());

  // 各頂点の子供にそれぞれ異なる色を割り当てる
  while (!indices.empty()) {
    // 親頂点の情報をスタックから取り出す
    const auto parent = indices.back();
    const auto parent_color = parent_colors.back();
    indices.pop_back();
    parent_colors.pop_back();
    
    // 子との辺に色を割り当てる
    size_t color = 1;
    const auto& children = graph[parent];
    for (const auto child : children) {
      // 親との辺と同じ色をスキップする
      if (color == parent_color) color++;

      // 辺に割り当てた色を記録する
      const auto child_color = color++;
      color_map.emplace(Edge{parent, child}, child_color);

      // 子供の子供を処理するために子頂点をスタックに積む
      indices.push_back(child);
      parent_colors.push_back(child_color);
    }

    // 親を持つ場合の色数を数える
    num_colors = std::max(num_colors, children.size() + 1);
  }

  // 結果発表
  std::cout << num_colors << '\n';
  for (const auto& edge : edges) {
    std::cout << color_map[edge] << '\n';
  }

  return 0;
}

int main() {
  return solve_D();
}
