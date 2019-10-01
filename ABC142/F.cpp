#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// 入次数と出次数がともに1である ⇒ 辺の向きが揃ったループ（v1 -> v2 -> ... -> vn -> v1）
// ⇒ ある点を出発して戻って来られるかを調べる
// 
// ループを構成する経路が複数あれば、より短い方が条件を満たす（v1 -> v2 -> v3, v1 -> v3の場合、条件に合わない(v1,v2,v3)を採用しない）
int main_F() {
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

  // ループを探す
  std::vector<bool> visited(N + 1);  // 1度目の訪問を記録するフラグ列
  std::vector<bool> finished(N + 1);  // 2度目の訪問を記録するフラグ列
  std::vector<int> path;  // 見つけた頂点をたどる経路
  path.reserve(N + 1);

  // 最初の頂点を追加する
  path.push_back(1);
  visited[1] = true;

  bool quit = false;  // 処理を終了するためのフラグ
  while (true) {
    // まだ訪問していない子頂点に訪問する
    bool pushed = false;  // 子頂点に訪問したか
    for (const auto& child : children_map[path.back()]) {
      if (!visited[child]) {
        // 1回目の訪問ならば、その先も訪問する
        path.push_back(child);
        visited[child] = true;
        pushed = true;
        break;
      } else if (!finished[child]) {
        // 2回目の訪問ならば、そこにループがある
        quit = true;

        // 経路を見つけたループのみに切り詰める
        path.erase(path.begin(), std::find(path.begin(), path.end(), child));
        break;
      }
    }

    // ループが見つかれば、そこで終了する
    if (quit) break;

    // すべての子頂点が訪問済みとなれば、その頂点以降にループが存在しないことがわかる
    if (!pushed) {
      finished[path.back()] = true;
      path.pop_back();

      // すべての頂点を見ても見つからなければ、調査を終了する
      if (path.empty()) break;
    }
  }

  // 結果発表
  if (path.empty()) {
    // ループが見つからなかった場合
    std::cout << "-1";
  } else {
    // ループを見つけた場合

    // ループにショートカットがあればそちらを採用する
    std::vector<bool> unused(path.size());  // 実際には使われない頂点かどうかのフラグ列
    for (size_t i = 0; i < path.size(); ++i) {
      if (!unused[i]) {
        // 探しやすいようにsetを作る
        const auto& children = children_map[path[i]];
        std::unordered_set<int> child_set(children.begin(), children.end());

        // 経路上で最も離れた頂点との辺を探す（[i+1,i+#paths)を逆順に）
        for (size_t j = path.size() - 1 + i; j > i; --j) {
          if (child_set.find(path[j % path.size()]) != child_set.end()) {
            // その2頂点でループを短絡する（[i+1, j-1]を取り除く）
            for (size_t k = j - 1; k > i; --k) {
              unused[k % path.size()] = true;
            }
            break;
          }
        }
      }
    }

    // 実際に使われる頂点の個数を数える
    size_t count = 0;
    for (auto b : unused) {
      if (!b) count++;
    }

    // ループの内の頂点を表示する
    std::cout << count << '\n';
    for (size_t i = 0; i < path.size(); ++i) {
      if (!unused[i]) std::cout << path[i] << '\n';
    }
  }

  return 0;
}
