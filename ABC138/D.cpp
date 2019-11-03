// 解説前
#include <iostream>
#include <vector>

// ある頂点に対して行われる操作はそれ自身とその親に対するもののみである。
// => 深さ優先探索を用いて、頂点のカウンターの値を親から順に累積的に計算すれば良い。
int solve_D() {
  size_t N;  // 頂点の数
  size_t Q;  // 操作の回数
  std::cin >> N >> Q;

  // 辺で接続する頂点のリストを作る
  std::vector<std::vector<size_t>> graph(N);
  for (size_t i = 0; i < N - 1; ++i) {
    size_t a, b;
    std::cin >> a >> b;

    // 親子関係が降順である場合にも対応するため、a->bとb->aの両方を登録しておく。
    // 親子関係が逆順であった方は探索アルゴリズムにより無視される。
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }

  // カウンターに足す点数のリストを作る
  std::vector<uint64_t> scores(N);
  for (size_t i = 0; i < Q; ++i) {
    size_t p;
    uint64_t x;
    std::cin >> p >> x;
    scores[p - 1] += x;  // 同じ頂点に対する操作を合算しておく
  }

  // 頂点のカウンターの値を深さ優先で累積的に計算する
  std::vector<size_t> stack;
  stack.reserve(N);
  std::vector<bool> visited(N);
  std::vector<uint64_t> total_scores(N);

  stack.push_back(0);
  visited[0] = true;
  total_scores[0] = scores[0];

  while (true) {
    const auto v = stack.back();

    // 未訪問の子供に訪問する
    auto& children = graph[v];
    bool all_visited = true;
    while (!children.empty()) {
      const auto child = children.back();

      // 訪問済みの子供を再度チェックしないようにリストから除外する
      children.pop_back();

      // 子供が訪問済みでない場合
      if (!visited[child]) {
        // その子供にも訪問するためにスタックに積む
        stack.push_back(child);
        visited[child] = true;

        // その頂点のカウンターの値を累積的に計算する
        total_scores[child] = total_scores[v] + scores[child];

        all_visited = false;
        break;
      }
    }

    // すべての子供が訪問済みである場合
    if (all_visited) {
      // ひとつ前に戻る
      stack.pop_back();

      // すべてに訪問すれば終了
      if (stack.empty()) break;
    }
  }

  // 結果発表
  for (const auto score : total_scores) {
    std::cout << score << ' ';
  }

  return 0;
}
