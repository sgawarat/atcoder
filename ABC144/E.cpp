// 解説後
#include <algorithm>
#include <iostream>
#include <vector>

// N <= 2*10^5なので、O(N^2)ではおそらくTLEする
// => せめてO(NlogN)でやりたい
//
// チームの成績は完食にかかる時間（消化コスト*食べにくさ）の最大値
// => 成績を小さくには全体として完食にかかる時間を小さくする必要がある
// => 成績は掛け算なので一方を小さい順に、もう一方を大きい順に選ぶと最も小さくなる
// => メンバーを昇順に、食べ物を降順に選べば良い
//
// 求めたい値は成績の最小値
// => 「成績の最小値がxとなり得るか」に対して、その境界値を二分探索で計算すれば良い
//
// メンバーをA_i、食べ物をF_iとする。（ここで、i<jのとき、A_i<=A_jでありF_i>=F_j）
// 修行回数を節約しつつ完食にかかる時間をX以下とするには、各人の消化コストをB_i=X/F_iとする必要がある。
// F_i>=F_jなので、B_i<=B_jとなり、修行後の消化コストは昇順を維持する。
// => 修行後でも食べ物の割当を変えることなく成績の最小値が得られる。
// => Σ(A_i-B_i)がK以下であれば、修行によって成績をX以下にまで下げることができると分かる。
int solve_E() {
  size_t N = 0;  // チームの人数
  uint64_t K = 0;  // 修行できる最大回数
  std::cin >> N >> K;

  std::vector<uint64_t> costs(N);  // メンバーの消化コストの配列
  for (auto& cost : costs) {
    std::cin >> cost;
  }

  std::vector<uint64_t> foods(N);  // 食べ物の食べにくさの配列
  for (auto& food : foods) {
    std::cin >> food;
  }

  // 配列をソートする
  std::sort(costs.begin(), costs.end(), std::less<>{});  // 昇順
  std::sort(foods.begin(), foods.end(), std::greater<>{});  // 降順

  // 取りうる成績の最大値を計算する
  uint64_t max = 0;
  for (size_t i = 0; i < N; ++i) {
    max = std::max(max, costs[i] * foods[i]);
  }

  // 成績の最小値が取り得る境界を二分探索で探す
  uint64_t min = 0;
  while (min < max) {
    const uint64_t mid = min + (max - min) / 2;

    // 成績がx以下となるように修行できるかを確かめる
    const auto check = [&](uint64_t x) -> bool {
      uint64_t k = 0;
      for (size_t i = 0; i < N; ++i) {
        // 成績がx以下になるような修行回数を累積的に計算する
        const auto new_cost = x / foods[i];
        if (costs[i] > new_cost) {
          k += costs[i] - new_cost;
        }

        // 最大修行回数に収まらなければ、成績をx以下にできないことが分かる
        if (k > K) return false;
      }

      // K回以下で成績をx以下にできることが分かった
      return true;
    };
    if (check(mid)) {
      max = mid;
    } else {
      min = mid + 1;
    }
  }

  // 結果発表
  std::cout << min;

  return 0;
}

int main() { return solve_E(); }
