// 解説前
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

// スライムは自分より小さい体力を持ったスライムを生成する
// ⇒ 可能な限り体力の大きいスライムから順に生成するとして調べれば良い
//
// スライムの増殖回数の合計は$\sum_{t=1}^{N} 2^{t-1} = 2^N$となる
// S_iより小さく最も近い値を探すにはおおよそ$O(\log 2^N)$かかる
// ⇒ 全体の計算量はおおよそ$O(2^N \log 2^N)$となる
// このとき、$2^N \le 2^18 = 262144 < 10^6$なので、制限時間に十分に間に合うだろう
// （参考：https://cppx.hatenablog.com/entry/2017/08/06/104144）
int solve_F() {
  size_t N = 0;  // スライムの増殖回数
  std::cin >> N;
  const size_t total_slime_count = size_t(1) << N;

  // Sを読み取る
  std::multiset<uint64_t> unspawned_slime_set;  // まだ生まれていないスライムのセット
  for (size_t i = 0; i < total_slime_count; ++i) {
    uint64_t slime = 0;
    std::cin >> slime;
    unspawned_slime_set.insert(slime);
  }

  // 最も体力の大きなスライムを最初の一体として生成する
  std::vector<uint64_t> spawned_slimes;  // 生まれたスライムの配列
  spawned_slimes.reserve(total_slime_count);
  spawned_slimes.push_back(*--unspawned_slime_set.end());
  unspawned_slime_set.erase(--unspawned_slime_set.end());

  // スライムを増殖させる
  for (size_t t = 0; t < N; ++t) {
    const size_t slime_count = spawned_slimes.size();
    spawned_slimes.resize(slime_count * 2);
    for (size_t j = 0; j < slime_count; ++j) {
      // 自身より小さく最も近い体力を持つ未生成のスライムを探す
      // iterはその1つ先を指す
      auto iter = unspawned_slime_set.lower_bound(spawned_slimes[j]);

      // 自身より小さい体力を持つスライムが存在しない場合、
      // スライムの体力をSに一致させることができない
      if (iter == unspawned_slime_set.begin()) {
        std::cout << "No";
        return 0;
      }

      // そのスライムを生成する
      spawned_slimes[slime_count + j] = *--iter;
      unspawned_slime_set.erase(iter);
    }
  }

  std::cout << "Yes";
  return 0;
}
