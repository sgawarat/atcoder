// 本戦
#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <vector>
#include <queue>

int solve_F() {
  uint64_t N;
  scanf("%" SCNu64, &N);

  // 各値の個数を数える
  std::vector<uint64_t> counts(static_cast<size_t>(N));
  for (size_t i = 0; i < N; ++i) {
    uint64_t A;
    scanf("%" SCNu64, &A);
    counts[static_cast<size_t>(A - 1)]++;
  }

  // 0個の値を取り除く
  counts.erase(std::remove(counts.begin(), counts.end(), 0), counts.end());

  // 1. 実際に差し引いてみる方法
  //    O(N^3)より大きい
  auto solver1 = [&]() {
    std::priority_queue<uint64_t> queue(counts.begin(), counts.end());
    std::vector<uint64_t> buf;
    buf.reserve(counts.size());
    for (size_t K = 2; K <= counts.size(); ++K) {
      buf.resize(K - 1);
      auto q = queue;
      uint64_t result = 0;
      while (q.size() >= K) {
        for (auto& value : buf) {
          value = q.top();
          q.pop();
        }

        const uint64_t m = q.top();
        q.pop();

        for (const auto value : buf) {
          if (value > m) q.push(value - m);
        }

        result += m;
      }

      printf("%" PRIu64 "\n", result);
    }
  };

  // A. 個数に対する最大長から考える方法
  //    読み込みがO(N^2)、書き込みがO(N)
  //
  // 
  auto answer = [&]() {
    std::vector<uint64_t> counts2(static_cast<size_t>(N) + 1);
    for (const auto c : counts) {
      counts2[static_cast<size_t>(c)]++;
    }

    uint64_t u = 0;
    for (size_t i = 1; i <= N; ++i) {
      u += counts2[i];
    }

    std::vector<uint64_t> lengths(static_cast<size_t>(N));
    uint64_t l = 0;
    uint64_t K = 1;
    for (uint64_t i = 1; i <= N; ++i) {
      const auto c2 = counts2[static_cast<size_t>(i)];
      l += i * c2;
      u -= c2;
      lengths[static_cast<size_t>(i) - 1] = (l + i * u) / i;
    }

    for (uint64_t k = 2; k <= counts.size(); ++k) {
      for (size_t i = 1; i < lengths.size(); ++i) {
        if (k > lengths[i]) {
          printf("%zu\n", i);
          break;
        }
      }
    }
  };

  // K=1
  printf("%" PRIu64 "\n", N);

  answer();

  // その他
  for (uint64_t K = counts.size() + 1; K <= N; ++K) {
    printf("0\n");
  }

  return 0;
}
