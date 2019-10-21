// 解説後
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

// ・互いに区別できるN本の棒から三角形を作る。
// ・2つの三角形を比べたとき、使われる棒が1つでも一方のみに存在する場合、それらの三角形は異なる。
// ・このときに取り得る三角形の個数を計算したい。
// => N個の棒から3つを選び、三角形を作ることができる組み合わせの個数を求める。
// 
// 三角形を作る3つの棒の長さをa,b,c（a < b < c）とする。
// cは与えられた条件からa-b < b-a < c < a+bである。
// このとき、b-a < bなので、b < c < a+bとなる。
// => 棒を2つ固定したとき、その長さをa,b（a < b）とすると、
//    取り得る三角形の個数は長さcが(b, a+b)の範囲にあるときの棒の個数で求められる。
// 棒は同じ長さのものが複数個用意され得るので、その組み合わせ分を考慮する必要がある。
// また、a == bやb == cまたはその両方の場合も個別に考える必要がある。
// => 合わせて、a == b == c、a == b != c、a != b == c、a != b != cの4パターンを考える必要がある。
//
// 棒の長さのリストをソートすれば、二分探索を使って境界値への距離を得られる。
// => 全体としてO(N^2 * logN)で計算できる。
//
// 累積和を計算しておけば、連続する要素の総和をO(1)で計算できる。
// => 全体としてO(N^2)で計算できる。
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
  //    O(N^2)だが、重い処理を含む
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

  // A1. 二辺の長さから取り得る三角形の個数を数える方法（高速バージョン）
  //     O(N^2)で、ソートや大量のコピーを伴わない
  auto answer1 = [&]() -> uint64_t {
    constexpr uint32_t MAX_LENGTH = 1000;

    // 棒の長さをインデックスとした棒の個数のリストを作る
    std::vector<uint32_t> counts(1001);
    for (const auto L_i : L) {
      counts[L_i]++;
    }

    // 棒の長さをインデックスとした棒の個数の累積和のリストを作る
    std::vector<uint32_t> prefix_sums(counts.size());
    prefix_sums[0] = counts[0];
    for (size_t i = 1; i < counts.size(); ++i) {
      prefix_sums[i] = prefix_sums[i - 1] + counts[i];
    }

    // 取り得るすべての三角形の個数を計算する
    uint64_t result = 0;
    for (uint32_t a = 1; a <= MAX_LENGTH; ++a) {
      const auto a_count = counts[a];

      // 棒が無ければ三角形を作れないので、処理を省略する
      if (a_count == 0) continue;

      // 長さaの棒の個数が十分にある場合
      if (a_count >= 2) {
        // a == b != cの場合の組み合わせの数を計上する
        const auto c_sum = prefix_sums[std::min(a + a - 1, MAX_LENGTH)] - prefix_sums[a];  //　a < c < 2aの範囲の棒の数
        const auto ab_comb = a_count * (a_count - 1) / 2;  // a_count個から2つ選ぶときの組み合わせの数
        result += c_sum * ab_comb;

        // 長さaの棒の個数がさらに十分にある場合
        if (a_count >= 3) {
          // a == b == cの場合の組み合わせの数を計上する
          const auto abc_comb = ab_comb * (a_count - 2) / 3;  // a_count個から3つ選ぶときの組み合わせの数
          result += abc_comb;
        }
      }

      // a < bのときに取り得る三角形の個数を計算する
      for (uint32_t b = a + 1; b <= MAX_LENGTH; ++b) {
        const auto b_count = counts[b];

        // 棒が無ければ三角形を作れないので、処理を省略する
        if (b_count == 0) continue;

        // a != b != cの場合の組み合わせの数を計上する
        const auto c_sum = prefix_sums[std::min(a + b - 1, MAX_LENGTH)] - prefix_sums[b];  //　b < c < a+bの範囲の棒の数
        const auto ab_comb = a_count * b_count;  // a_count個とb_count個から1つずつ選ぶときの組み合わせの数
        result += c_sum * ab_comb;

        // 長さbの棒の個数が十分にある場合
        if (b_count >= 2) {
          // a != b == cの場合の組み合わせの数を計上する
          const auto abc_comb = ab_comb * (b_count - 1) / 2;  // a_count個から1つ、b_count個から2つを選ぶときの組み合わせの数
          result += abc_comb;
        }
      }
    }

    return result;
  };

  std::cout << answer1();

  return 0;
}

int main() {
  return solve_D();
}
