// 本戦
#include <iostream>

// 10進数の桁数を計算する
template <typename T>
T digit10(T n) noexcept {
  T d = 1;
  while (n >= 10) {
    n /= 10;
    d++;
  }
  return d;
}

// 整数nの値段を計算する
template <typename T>
T price(T n, T a, T b) noexcept {
  return a * n + b * digit10(n);
}

// 整数の価格は最大で10^18程度なので、64ビット整数に十分収まる
// ある値以下で最も大きい値を求めたいので、二分探索が使える
int solve_C() {
  uint64_t A, B, X;
  std::cin >> A >> B >> X;

  uint64_t min = 1;
  uint64_t max = 1'000'000'000;
  if (X < price(min, A, B)) {
    // 所持金Xで整数1を購入できなければ、いずれも購入できない
    std::cout << '0';
  } else if (X >= price(max, A, B)) {
    // 所持金Xで整数10^9を購入できれば、いずれも購入できる
    std::cout << max;
  } else {
    // 所持金Xで購入できる整数の境界を二分探索を用いて探す
    while (true) {
      // 範囲[min, max]の中間値に対する価格と所持金との関係に応じて範囲を狭める
      const uint64_t mid = min + (max - min) / 2;
      const uint64_t mid_price = price(mid, A, B);
      if (mid_price < X) {
        // 中間値の価格が所持金より小さいならば、見る範囲を小さい方に狭める
        min = mid;
      } else if (mid_price > X) {
        // 中間値の価格が所持金より大きいならば、見る範囲を大きい方に狭める
        max = mid;
      } else {
        // 所持金ピッタリで購入できる整数を見つけた
        std::cout << mid;
        break;
      }

      // これ以上に範囲を小さくできない場合
      if (max - min == 1) {
        std::cout << min;
        break;
      }
    }
  }

  return 0;
}
