// 解説後
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// 試合の識別子を作る関数
// a<bのときをb優先で数えたときの値を返す
inline uint32_t make_id(uint32_t a, uint32_t b, uint32_t N) noexcept {
  if (a > b) std::swap(a, b);
  const uint32_t offset = a + 1 + a * (a + 1) / 2;  // a>=bのときを数えないためのオフセット。初項1、公差1の等比数列のn=a+1までの和
  return a * N + b - offset;
}

// 全日程を完遂するには試合日程の前後関係が矛盾しなければ良い
// => 試合日程の前後関係をグラフにしたとき、閉路が存在しなければ良い
//
// 全試合の日数はそれ以前にやるべき試合がないものから順にこなしていくことで計算できる
// => 試合日程の前後関係のグラフにおいて、入次数が0の頂点を順々にグラフから切り離していく操作に相当する
// => 全試合の日数は最大経路の頂点数に等しい
int solve_E() {
  uint32_t N = 0;  // 選手の人数
  std::cin >> N;
  const uint32_t num_ids = (N - 1) + (N - 1) * (N - 2) / 2;
  const uint32_t max_id = num_ids - 1;

  // 試合日程の前後関係の有向グラフを作る
  std::unordered_map<uint32_t, std::vector<uint32_t>> graph;
  for (uint32_t i = 0; i < N; ++i) {
    uint32_t a;
    std::cin >> a;
    for (uint32_t j = 1; j <  N - 1; ++j) {
      uint32_t b;
      std::cin >> b;
      graph[make_id(i, a - 1, N)].push_back(make_id(i, b - 1, N));
      a = b;
    }
  }

  // 試合日程の前後関係のグラフの最長経路を調べる
  std::vector<uint32_t> stack;
  stack.reserve(num_ids);
  std::vector<bool> visited(num_ids);
  std::vector<bool> finished(num_ids);
  std::vector<size_t> distances(num_ids);  // idから終点までの経路長
  size_t result = 0;  // 経路の最大長
  for (uint32_t start_id = 0; start_id < num_ids; ++start_id) {
    // 頂点が訪問済みでなければ、そこからの最長経路を計算する
    if (!visited[start_id]) {
      // 深さ優先探索
      stack.push_back(start_id);
      visited[start_id] = true;
      while (true) {
        const uint32_t id = stack.back();

        // 子供を調べる
        bool all_visited = true;  // すべての子供が訪問済みかどうか
        size_t max_distance = 0;  // 子供の経路の最大長
        for (auto child : graph[id]) {
          // 未訪問でれば、それに訪問する
          if (!visited[child]) {
            stack.push_back(child);
            visited[child] = true;
            all_visited = false;
            break;
          }

          // 閉路が存在すれば、その日程は完遂できない
          if (!finished[child]) {
            std::cout << "-1";
            return 0;
          }

          // 子から終点までの最大長を計算する
          max_distance = std::max(max_distance, distances[child]);
        }

        // すべての子供に訪問済みであれば、ひとつ前に戻る
        if (all_visited) {
          stack.pop_back();
          finished[id] = true;
          distances[id] = max_distance + 1;
          if (stack.empty()) break;
        }
      }
    }

    // グラフ全体での経路の最大長を計算する
    result = std::max(result, distances[start_id]);
  }

  // 結果発表
  std::cout << result;
  return 0;
}
