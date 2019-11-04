# アルゴリズム

## グラフ理論

### 深さ優先探索

深い（ルートから遠い）方から順にグラフ（主に木構造）のすべての頂点を処理する

- 入力：グラフ$G = (V, E)$
- 時間計算量：$O(|E|)$
- 空間計算量：$O(|V|)$

#### 概要

1. 指定の頂点に訪問してスタックに積む
2. スタックの先頭の頂点を$V_i$とする
3. 未訪問の子頂点が$V_i$にあれば、それに訪問してスタックに積む
4. 未訪問の子頂点が$V_i$になければ、$V_i$をスタックから取り出す
5. スタックが空であれば終了し、そうでなければ2に戻る

##### 閉路の検出

スタックに積まれた頂点に再び訪問しようとする場合、その頂点を含む閉路が存在することが分かる。このときのスタックは閉路を構成する頂点の列である。

#### コード

```cpp
using Graph = std::vector<std::vector<size_t>>;

// 頂点を訪問するときに呼び出される関数
// 頂点は行きがけ順に呼び出される
void enter(const Graph& graph, size_t vertex) {
  ...
}

// すべての子頂点を訪問し終わったときに呼び出される関数
// 頂点は帰りがけ順に呼び出される
void leave(const Graph& graph, size_t vertex) {
  ...
}

// スタックを使わない深さ優先探索
void stackless_depth_first_search(const Graph& graph, size_t root) {
  std::vector<size_t> stack;  // 訪問中の頂点を格納するための配列
  stack.reserve(graph.size());
  std::vector<bool> visited(graph.size());  // 各頂点が訪問済みかどうかのビットセット

  // ルートに訪問する
  stack.push_back(root);
  visited[root] = true;
  enter(graph, root);

  while (true) {
    const size_t parent = stack.back();

    // 未訪問の子供に訪問する
    bool all_visited = true;  // すべての子供が訪問済みであったかどうか
    for (const size_t child : graph[parent]) {
      // 子供が訪問済みでない場合
      if (!visited[child]) {
        // その子供に訪問する
        stack.push_back(child);
        visited[child] = true;
        enter(graph, child);

        // 子供の子供を訪問しに行く
        all_visited = false;
        break;
      }
    }

    // すべての子供が訪問済みである場合
    if (all_visited) {
      leave(graph, parent);

      // 別の分岐先の頂点を訪問するため、ひとつ前に戻る
      stack.pop_back();

      // すべてが訪問済みであれば終了する
      if (stack.empty()) break;
    }
  }
}
```

### ワーシャルフロイド法

重み付きグラフにおけるすべての頂点間の最短経路を計算する

- 入力：グラフ$G = (V, E)$
- 出力：$i,j \in V$間の最短経路
- 時間計算量：$O(|V|^3)$
- 空間計算量：$O(|V|^2)$

#### 概要

$k \in V$として、すべての$i,j \in V$に対して、

- $i$から$j$への経路$p_{i,j}$を通るコスト$c_{i,j}$と
- $i$から$k$を経由して$j$へ向かう経路$p_{i,k,j}$を通るコスト$c_{i,k,j}$

の小さい方を$i$から$j$への経路のコストとして選択する。
これをすべての$k$について行うと、すべての$i,j\in V$に対する最短経路を得られる。

##### 解釈

$k = n$のとき、$c_{i,j}$は$p_{i,j}$の道中に頂点${0, 1, ..., n-1, n}$のみを含むときの最短経路を表す。

#### コード

```cpp
// グラフ
class Graph {
public:
  // 頂点v_sから頂点v_eへの辺を持っているか
  bool has_edge(size_t v_s, size_t v_e) const;

  // 頂点v_sから頂点v_eへの辺の重み
  size_t weight(size_t v_s, size_t v_e) const;

  // 頂点の数
  size_t vertex_count() const noexcept;

private:
  ...
};

// 動的な二次元配列
class DynArray2D {
  ...
};

// V = {0, 1, ..., N - 1}のときのワーシャルフロイド法
DynArray2D<uint64_t> warshall_floyd(const Graph& graph) {
  constexpr uint64_t INVALID_DISTANCE = UINT64_MAX;  // 無効な距離
  const size_t N = graph.vertex_count();  // 頂点数
  DynArray2D<uint64_t> distances(N, N);  // NxNの2次元配列

  // 初期化
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (i == j) {
        // 自分自身への距離は0になる
        distances[i][j] = 0;
      } else if (graph.has_edge(i, j)) {
        // グラフがiからjへの辺を持っていれば、その辺の重みを使う
        distances[i][j] = graph.weight(i, j);
      } else {
        // それ以外ならば、到達できないことを表す大きな値を使う
        distances[i][j] = INVALID_DISTANCE;
      }
    }
  }

  // 最短経路を計算する
  for (size_t k = 0; k < N; ++k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        if (distances[i][k] != INVALID_DISTANCE &&
            distances[k][j] != INVALID_DISTANCE) {
          distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
        }
      }
    }
  }

  return distances;
}
```
