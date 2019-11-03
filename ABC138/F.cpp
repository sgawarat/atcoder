// 解説後
#include <array>
#include <iostream>

// xのMSBをn、yのMSBをmとする。
// n>mとすると、x>yとなり条件（x<=y）と矛盾するので、無視して良い。
// n<mとすると、y^x>x>(y mod x)となるので、数えなくて良い。
// => n=mのときだけを考えれば良い。

// このとき、y/xの商は1なので、(y mod x) = y-xとなり、考慮すべき条件はy-x=y^xとなる。
// => すべての桁において繰り下がりが起こらない組を数えれば良い。
// => i∈[0,m)において、i桁目のビット(x_i, y_i)が(1, 0)でない組を数えれば良い。
//
// 計算の効率性を高めるため、個数を累積的に数えたい。
// => 各条件が真かどうかで個数を分割して記録することを考える。
//    その条件は「x>=L」、「y<=R」、「MSBが一致する」の3つ。
//
// iビット目までを見たとき、(i+1)ビット目に値を加えるとする。
// (i+1)ビットまでを見たときの個数を加えた値によって変化した条件とともに記録する。
// => 最終的に、63ビット目までを見たときに条件がすべて真となる組の個数を計算できる。

// 条件を満たすかどうかのフラグ
constexpr uint32_t COND_L_BIT = 0b100;     // xがL以上かどうか
constexpr uint32_t COND_R_BIT = 0b010;     // yがR以下かどうか
constexpr uint32_t COND_MSB_BIT = 0b001;   // MSBが一致するか
constexpr uint32_t COND_ALL_BITS = 0b111;  // すべてを満たすか

template <typename T, size_t ROWS, size_t COLUMNS>
using Array2D = std::array<std::array<T, COLUMNS>, ROWS>;

int solve_F() {
  uint64_t L;  // 下限
  uint64_t R;  // 上限
  std::cin >> L >> R;

  // 0ビット目に値を加えたときの個数を記録する
  Array2D<uint64_t, 64, 8> counts{};  // [見た最大ビット][条件フラグのビットセット]
  auto f0 = [&](uint64_t x, uint64_t y) {
    uint32_t cond = 0;
    if (x >= (L & 1)) cond |= COND_L_BIT;
    if (y <= (R & 1)) cond |= COND_R_BIT;
    if (x == y) cond |= COND_MSB_BIT;

    counts[0][cond] += 1;
  };
  f0(0, 0);
  f0(0, 1);
  f0(1, 1);

  // 各条件に沿った組の個数を累積的に計算する
  for (size_t i = 0; i < counts.size() - 1; ++i) {
    const uint64_t l = (L >> (i + 1)) & 1;  // Lの(i+1)ビット目の値
    const uint64_t r = (R >> (i + 1)) & 1;  // Rの(i+1)ビット目の値

    for (uint32_t cond = 0; cond < 8; ++cond) {
      // condの状態の組の(i+1)ビット目に(x, y)を付け加えたときの個数を累積的に記録する
      auto f = [&, l, r](uint64_t x, uint64_t y) {
        uint32_t new_cond = 0;
        if (x == l) {
          new_cond |= cond & COND_L_BIT;
        } else if (x >= l) {
          new_cond |= COND_L_BIT;
        }

        if (y == r) {
          new_cond |= cond & COND_R_BIT;
        } else if (y <= r) {
          new_cond |= COND_R_BIT;
        }

        if (x == 0 && y == 0) {
          new_cond |= cond & COND_MSB_BIT;
        } else if (x == 1 && y == 1) {
          new_cond |= COND_MSB_BIT;
        }

          counts[i + 1][new_cond] += counts[i][cond] % 1'000'000'007;
        };
        f(0, 0);
        f(0, 1);
        f(1, 1);
      }
    }

    // 結果発表
    std::cout << counts[63][COND_ALL_BITS];

    return 0;
  }

  int main() { return solve_F(); }
