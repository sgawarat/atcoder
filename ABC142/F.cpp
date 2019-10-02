// 解説後
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// 入次数と出次数がともに1である ⇒ 辺の向きが揃ったループ（v1 -> v2 -> ... -> vn -> v1）
// ⇒ ある点を出発して戻って来られるかを調べる
//
// ループを構成する経路が複数あれば、より短い方が条件を満たす（(v1 -> v2 -> v3, v1 -> v3)の場合、条件に合わない(v1,v2,v3)を採用しない）
// ⇒最短経路のループを探せば良い
int solve_F() {
  int N;  // 頂点の数
  int M;  // 辺の数
  std::cin >> N >> M;

  // 頂点の親子関係のマップを作る
  std::unordered_map<int, std::vector<int>> children_map;  // 親頂点から子供を探すためのマップ
  for (int i = 0; i < M; ++i) {
    int A, B;  // AからBへの辺
    std::cin >> A >> B;
    children_map[A].push_back(B);
  }

  // 最短のループを探す
  std::vector<bool> visited(N + 1);  // 訪問を記録するフラグ列
  std::vector<int> path;             // 現在たどっている頂点の経路
  std::vector<int> shortest_path;    // 見つけたループの最短経路
  path.reserve(N + 1);
  shortest_path.reserve(N + 1);
  bool quit = false;  // 処理を終了するためのフラグ
  for (int start = 1; start <= N; ++start) {
    // 初期化
    std::fill(visited.begin(), visited.end(), false);
    path.clear();
    visited[start] = true;
    path.push_back(start);

    while (true) {
      // まだ訪問していない子頂点に訪問する
      bool all_visited = true;  // すべての子頂点が訪問済みだったか
      for (const auto& child : children_map[path.back()]) {
        if (child == start) {
          // 始点に戻ってこられる最短経路を記録する
          if (shortest_path.empty() || path.size() < shortest_path.size()) {
            shortest_path = path;

            // これ以上ない最短経路が見つかれば、そこで終了する
            if (shortest_path.size() == 2) {
              quit = true;
              break;
            }
          }
        } else if (!visited[child]) {
          // 未訪問の子頂点があれば、その先も訪問する
          path.push_back(child);
          visited[child] = true;
          all_visited = false;
          break;
        }
      }

      // これ以上ない最短経路が見つかれば、そこで終了する
      if (quit) break;

      // すべての子頂点が訪問済みとなれば、1つ前の頂点に戻る
      if (all_visited) {
        path.pop_back();

        // すべての頂点を確認し終えたら調査を終了する
        if (path.empty()) break;
      }
    }

    // これ以上ない最短経路が見つかれば、そこで終了する
    if (quit) break;
  }

  // 結果発表
  if (shortest_path.empty()) {
    // ループが見つからなかった場合
    std::cout << "-1";
  } else {
    // ループを見つけた場合
    std::cout << shortest_path.size() << '\n';
    for (const auto& v : shortest_path) {
      std::cout << v << '\n';
    }
  }

  return 0;
}
