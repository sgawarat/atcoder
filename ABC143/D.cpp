// 解説前
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int solve_D() {
  size_t N;
  std::cin >> N;

  std::vector<uint32_t> lines(N);
  for (auto& line : lines) {
    std::cin >> line;
  }

  // 1. 全探索
  //    O(N^3)くらい => TLE
  auto solver1 = [&]() -> size_t {
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
    for (size_t i = 0; i < lines.size() - 2; ++i) {
      const auto a = lines[i];
      for (size_t j = i + 1; j < lines.size() - 1; ++j) {
        const auto b = lines[j];
        for (size_t k = j + 1; k < lines.size(); ++k) {
          const auto c = lines[k];
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
  auto solver2 = [&]() -> size_t {
    constexpr uint32_t MAX_LENGTH = 1000;

    // 長さをインデックスとした棒の個数のリストを作る
    std::vector<uint32_t> edge_counts(1001);
    for (const auto line : lines) {
      edge_counts[line]++;
    }

    // 長さをインデックスとした三角形の個数の累積和のリストを作る
    std::vector<uint32_t> triangle_counts(1001);
    for (size_t i = 1; i < triangle_counts.size(); ++i) {
      triangle_counts[i] = triangle_counts[i - 1] + (edge_counts[i] > 0 ? 1 : 0);
    }

    // 取り得るすべての三角形の個数を計算する
    // ここでは、同じ三角形を重複して数えないように各辺の長さをa <= b <= cとする
    size_t result = 0;
    for (uint32_t a = 1; a <= MAX_LENGTH; ++a) {
      const auto a_count = edge_counts[a];

      // 長さaの棒が1つもなければ、三角形は1つも作れない
      if (a_count == 0) continue;

      // a == bのとき、長さaの棒が2本以上ある場合
      if (a_count >= 2) {
        // 0 < c < 2aの間に取り得る三角形の個数を計上する
        // a <= cなので、0 < c < 2a => a <= c <= (2a-1)
        const auto lhs = a;
        const auto rhs = std::min(a + a - 1, MAX_LENGTH);
        result += triangle_counts[rhs] - triangle_counts[lhs - 1];

        // cが長さaの棒を使えない場合、その三角形を差し引く
        if (a_count == 2) result--;
      }

      // a < bのときに取り得る三角形の個数を計算する
      for (uint32_t b = a + 1; b <= MAX_LENGTH; ++b) {
        const auto b_count = edge_counts[b];

        // 長さbの棒が1つもなければ、三角形は1つも作れない
        if (b_count == 0) continue;

        //　b-a < c < a+bの間に取り得る三角形の個数を計上する
        // b-a < bかつb <= cなので、b-a < c < a+b => b <= c <= (a+b-1)
        const auto lhs = b;
        const auto rhs = std::min(a + b - 1, MAX_LENGTH);
        result += triangle_counts[rhs] - triangle_counts[lhs - 1];

        // cが長さbの棒を使えない場合、その三角形を差し引く
        if (b_count == 1) result--;
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
