// 解説後
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

// ・互いに区別できるN本の棒から三角形を作る。
// ・2つの三角形を比べたとき、使われる棒が1つでも一方のみに存在する場合、それらの三角形は異なる。
// ・このときに取り得る三角形の個数を計算したい。
// 
// 三角形を作る3つの棒の長さをa,b,c（a <= b <= c）とする。
// cは与えられた条件からa-b < b-a < c < a+bである。
// このとき、b-a <= bなので、b <= c < a+bとなる
// => 長さが[b, a+b)の範囲にある棒の個数を求めれば良い
// 
// 棒の長さのリストをソートすれば、二分探索を使って境界値へのポインタを得られる。
// => 全体としてO(N^2 * logN)で計算できる
int solve_D() {
  size_t N;
  std::cin >> N;

  std::vector<uint32_t> L(N);
  for (auto& L_i : L) {
    std::cin >> L_i;
  }

  // 1. 全探索
  //    O(N^3)くらい => TLE
  auto solver1 = [&]() -> uint64_t {
    struct Triangle {
      Triangle(uint32_t x, uint32_t y, uint32_t z) noexcept {
        if (x > y) std::swap(x, y);
        if (x > z) std::swap(x, z);
        if (y > z) std::swap(y, z);
        a = x;
        b = y;
        c = z;
      }

      bool operator<(const Triangle& other) const noexcept {
        if (a < other.a) return true;
        if (a > other.a) return false;
        if (b < other.b) return true;
        if (b > other.b) return false;
        return c < other.c;
      }

      uint32_t a, b, c;
    };

    std::set<Triangle> set;
    for (size_t i = 0; i < L.size() - 2; ++i) {
      const auto a = L[i];
      for (size_t j = i + 1; j < L.size() - 1; ++j) {
        const auto b = L[j];
        for (size_t k = j + 1; k < L.size(); ++k) {
          const auto c = L[k];
          if (a < b + c &&
              b < c + a &&
              c < a + b) {
            set.emplace(a, b, c);
          }
        }
      }
    }
    return set.size();
  };

  // 2. 二辺の長さから取り得る三角形の個数を数える方法
  auto solver2 = [&]() -> uint64_t {
    constexpr uint32_t MAX_LENGTH = 1000;

    // ソート
    std::sort(L.begin(), L.end());

    // 長さをインデックスとした棒の個数のリストを作る
    std::vector<uint32_t> counts(1001);
    for (const auto L_i : L) {
      counts[L_i]++;
    }

    // 長さをインデックスとした棒の個数の累積和のリストを作る
    std::vector<uint32_t> prefix_sums(counts.size());
    prefix_sums[0] = counts[0];
    for (size_t i = 1; i < counts.size(); ++i) {
      prefix_sums[i] = prefix_sums[i - 1] + counts[i];
    }

    // 取り得るすべての三角形の個数を計算する
    uint64_t result = 0;
    std::vector<uint32_t> used_a(counts.size());
    std::vector<uint32_t> used_b(counts.size());
    for (size_t i = 0; i < N - 1; ++i) {
      const auto a = L[i];

      // 使用済みの棒を数える
      used_a[a]++;

      used_b = used_a;
      for (size_t j = i + 1; j < N; ++j) {
        const auto b = L[j];

        // 使用済みの棒を数える
        used_b[b]++;

        //　b <= c <= (a+b-1)となる三角形の個数を計上する
        result += prefix_sums[std::min(a + b - 1, MAX_LENGTH)] - prefix_sums[b - 1];

        // 組み合わせの重複を避けるため、使用済みの長さbの棒をを差し引く
        result -= used_b[b];
      }
    }

    return result;
  };

  std::cout << solver2();

  return 0;
}

int main() {
  return solve_D();
}
