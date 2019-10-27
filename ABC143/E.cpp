// 解説後
#include <algorithm>
#include <iostream>
#include <vector>

constexpr uint64_t INVALID_DISTANCE = UINT64_MAX;  // 無効な距離
constexpr uint64_t INVALID_COUNT = UINT64_MAX;  // 無効な給油回数

// クエリは互いにスタートとゴールが異なる
// => すべての町間移動の最小給油回数が知りたいので、クエリの個数分のループを被せる必要がある
// => ループ中に探索すると計算量が跳ね上がりそう
//
// 辺の数は最大でN^2=3*10^4になる
// => 深さ優先探索はO(N^2*Q) = O(N^4)になるので、制限時間内に収まらなさそう
// 頂点の数が最大でN=300 <=> N^3は10^7程度になる
// => O(N^3)以下の全探索アルゴリズムが使えそう
// 
// 町間移動の最小給油回数を知りたい
// => 各経路で給油が必要かどうかが分かれば、そのグラフの最短経路を求めれば良い
// 経路の長さがL以下であれば、給油せずに通ることができる
// => 経路で給油が必要かどうかを知るには、その経路が長さL以下かどうかを調べれば良い
// => すべての経路の最短距離を知りたい
int solve_E() {
  size_t N;  // 頂点の数
  size_t M;  // 辺の数
  uint64_t L;  // 給油1回あたりの最大移動可能距離
  std::cin >> N >> M >> L;

  // 最短距離の配列を初期化する
  std::vector<uint64_t> distances(N * N, INVALID_DISTANCE);
  for (size_t i = 0; i < N; ++i) {
    distances[i * N + i] = 0;  // 自分自身への距離は0
  }

  // グラフを構築する
  std::vector<std::vector<size_t>> graph(N);
  for (size_t i = 0; i < M; ++i) {
    size_t a, b;
    uint64_t c;
    std::cin >> a >> b >> c;
    graph[a - 1].push_back(b - 1);
    distances[(a - 1) * N + (b - 1)] = c;

    // 道は双方向なので、逆順も登録する
    graph[b - 1].push_back(a - 1);
    distances[(b - 1) * N + (a - 1)] = c;
  }

  // ワーシャルフロイド法を用いて、すべての最短距離を計算する
  for (size_t k = 0; k < N; ++k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        const auto i2k_distance = distances[i * N + k];  // iからkまでの距離
        const auto k2j_distance = distances[k * N + j];  // kからjまでの距離
        if (i2k_distance != INVALID_DISTANCE && k2j_distance != INVALID_DISTANCE) {
          distances[i * N + j] = std::min(distances[i * N + j], i2k_distance + k2j_distance);
        }
      }
    }
  }

  // 最小給油回数の配列を初期化する
  // その燃料タンクでは通行できない経路には無効値が入る
  std::vector<uint64_t> refueling_counts(distances.size(), INVALID_COUNT);
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (i == j) {
        // 自分自身へは給油せずに行ける
        refueling_counts[i * N + j] = 0;
      } else if (distances[i * N + j] <= L) {
        // 距離がL以下の経路は1回の給油で通れる
        refueling_counts[i * N + j] = 1;
      }
    }
  }

  // ワーシャルフロイド法を用いて、すべての最小給油回数を計算する
  for (size_t k = 0; k < N; ++k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        const auto i2k_refueling_count = refueling_counts[i * N + k];  // iからkでの最小給油回数
        const auto k2j_refueling_count = refueling_counts[k * N + j];  // kからjでの最小給油回数
        if (i2k_refueling_count != INVALID_COUNT && k2j_refueling_count != INVALID_COUNT) {
          refueling_counts[i * N + j] = std::min(refueling_counts[i * N + j], i2k_refueling_count + k2j_refueling_count);
        }
      }
    }
  }

  // クエリに答える
  size_t Q;
  std::cin >> Q;  
  for (size_t i = 0; i < Q; ++i) {
    size_t s;  // 出発地
    size_t t;  // 目的地
    std::cin >> s >> t;

    // sからtへたどり着くことができれば、そのときの最小給油回数を表示する
    const auto s2t_refueling_count = refueling_counts[(s - 1) * N + (t - 1)];
    if (s2t_refueling_count != INVALID_COUNT) {
      // 開始時のタンクは満タンなので、1回分の給油回数を際し引いて表示する
      std::cout << (s2t_refueling_count - 1) << '\n';
    } else {
      std::cout << "-1\n";
    }
  }

  return 0;
}

int main() { return solve_E(); }
